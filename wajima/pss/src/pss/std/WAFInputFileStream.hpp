#include <streambuf>
#include <ios>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/lexical_cast.hpp>
#include <windows.h>
#include "Logger.hpp"



namespace pss {
	namespace std {
		template <class Elem, class Tr = ::std::char_traits<Elem> >
		class basic_waf_filebuf : public ::std::basic_streambuf<Elem, Tr> {
		public:
			/**
			 * ファイルの保存モード
			 * NORMAL		通常ファイル
			 * WAF_NORMAL	WAFファイル非圧縮
			 * WAF_ZLIB		WAFファイルZLIB
			 */
			enum ARCHIVE_MODE {NORMAL,WAF_NORMAL,WAF_ZLIB};
			/**
			 * アーカイブファイルヘッダ構造体
			 */
			struct Header {
				DWORD	size_;
				ARCHIVE_MODE	mode_;
				char	filename_[260];
			};
			/**
			 * 要素型
			 */
			typedef Elem char_type;
			/**
			 * Elemeの特性型
			 */
			typedef Tr traits_type;
			typedef typename traits_type::int_type int_type;
			typedef typename traits_type::off_type off_type;
			typedef typename traits_type::pos_type pos_type;
			typedef typename ::std::ios_base ios_base;
			/**
			 * デフォルトコンストラクタ
			 */
			basic_waf_filebuf() : file_(NULL) {
			}
			/**
			 * コンストラクタ
			 * @param _Filepath ファイルパス
			 * @param _Which オープンモード
			 */
			basic_waf_filebuf(::boost::filesystem::path _Filepath,  ios_base::openmode _Which = ios_base::in) : file_(NULL) {
				open(_Filepath, _Which);
			}
			/**
			 * ファイルクローズ
			 */
			basic_waf_filebuf *close() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "close begin.");

				if (is_open()) {
					LOG4CXX_DEBUG(log, "CloseHandle");
					::CloseHandle(file_);
					file_ = NULL;
					buffer_.resize(0);	
				}

				LOG4CXX_DEBUG(log, "close end.");
				return this;
			}
			/**
			 * ファイルオープンしているか
			 */
			bool is_open( ) {
				return file_ != NULL;
			}
			/**
			 * ファイルオープン
			 * ファイルサイズ	4byte
			 * ファイルモード	4byte
			 * ファイルサイズ	260byte
			 * データ			ファイルサイズ
			 */
			basic_waf_filebuf *open(::boost::filesystem::path _Filepath,  ios_base::openmode _Which = ios_base::in ) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "open begin.");
				// とりあえず、以前に開いていたファイルをクローズ
				close();

				// ファイルのパスをフルパスに変換
				::boost::filesystem::path file = ::boost::filesystem::complete(::boost::filesystem::path(_Filepath));

				if (::boost::filesystem::exists(file)) {
					// _Filepathで指定されたファイルが存在する場合、以下の処理を実行

					LOG4CXX_DEBUG(log, "open normal file.");
					LOG4CXX_DEBUG(log, file.string());
					file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if (INVALID_HANDLE_VALUE  == file_) {
						// ファイルハンドルが無効の場合
						file_ = NULL;
						return NULL;
					}

					// モード：ノーマル
					mode_ = NORMAL;
					// バッファ確保
					buffer_.resize(getBufferSize() * sizeof(char_type));
					// バッファサイズを設定
					setg(&buffer_[0], &buffer_[0], &buffer_[0]);
					// ファイルの先頭位置
					begin_ = 0;
					// ファイルの終端位置
					end_ = ::GetFileSize(file_, NULL);
					// バッファの先頭位置
					bufferPos_ = 0;

					return this;

				} else {
					// _Filepathで指定されたファイル画存在しない場合は、以下の処理を実行。

					// アーカイブ内ファイル名
					::std::string inner_file = file.leaf();

					// アーカイブファイル名
					file = ::boost::filesystem::change_extension(file.branch_path(), get_extension());
					
					if (::boost::filesystem::exists(file)) {
						// _Filepathの上位ディレクトリにWAFファイルが存在する場合

						LOG4CXX_DEBUG(log, "file is waf file.");
						LOG4CXX_DEBUG(log, file.string());

						file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if (INVALID_HANDLE_VALUE  == file_) {
							// ファイルハンドルが無効の場合の処理
							file_ = NULL;
							return NULL;
						}

						// アーカイブファイルのヘッダ情報
						Header header;
						DWORD readSize;
						
						while (1) {
							// アーカイブの先頭から順次読み込み
							if (0 == ::ReadFile(file_, &header, sizeof(header), &readSize, NULL) || readSize != sizeof(header)) {
								// ヘッダが読み込めない。
								close();
								return NULL;
							}
							LOG4CXX_DEBUG(log, "header.size = " + ::boost::lexical_cast<::std::string>(header.size_));
							LOG4CXX_DEBUG(log, "header.mode = " + ::boost::lexical_cast<::std::string>(header.mode_));
							LOG4CXX_DEBUG(log, "header.filename = " + ::boost::lexical_cast<::std::string>(header.filename_));

							if (header.size_ == -1) {
								// サイズ-1なのでファイル終端
								close();
								return NULL;
							}
							if (inner_file == ::std::string(header.filename_)) {
								// ファイル名が同じならそのアーカイブを利用

								// ファイルの先頭設定
								DWORD modeSize = ::SetFilePointer(file_, 0 , NULL, FILE_CURRENT);

								// ファイルの先頭設定
								begin_ = modeSize;
								if (modeSize == INVALID_SET_FILE_POINTER) {
									// 無効なファイルポインタ
									close();
									return NULL;
								}

								// ファイルの終端設定
								end_ = begin_ + (::std::streamoff) header.size_;

								// モード設定
								mode_ = header.mode_;

								break;
							}
						}

						// バッファを確保
						buffer_.resize(getBufferSize() * sizeof(char_type));

						// バッファサイズを設定
						setg(&buffer_[0], &buffer_[0], &buffer_[0]);

						// バッファ先頭位置設定
						bufferPos_ = 0;
						return this;
					} else {
						// ファイルが存在しない場合。

						LOG4CXX_DEBUG(log, "file not exits");
						LOG4CXX_DEBUG(log, file.string());
						return NULL;
					}
				}
			}
		protected:
			/**
			 * 文字を１文字読み戻す。uflow()のキャンセル操作
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof) {
				// 今回は未実装
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "pbackfail begin.");
				LOG4CXX_DEBUG(log, "pbackfail end.");
				return traits_type::eof();
			}
			/**
			 * 読み込み位置を移動する。
			 */
			virtual pos_type seekoff(off_type _Off, ios_base::seekdir _Way, ios_base::openmode _Which = ios_base::in) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "seekoff begin.");

				if (!is_open()) {
					LOG4CXX_DEBUG(log, "file is close.");
					LOG4CXX_DEBUG(log, "seekoff end.");
					return pos_type(-1);
				}

				if (_Which != ios_base::in) {
					LOG4CXX_DEBUG(log, "illegal argument.");
					LOG4CXX_DEBUG(log, "seekoff end.");
					return pos_type(-1);
				}

				DWORD result = 0;
				if (_Way == ios_base::beg) {
					LOG4CXX_DEBUG(log, "offset + begin = " + ::boost::lexical_cast<::std::string>(begin_ + (::std::streamoff) (sizeof(char_type) * _Off)));
					LOG4CXX_DEBUG(log, "offset = " + ::boost::lexical_cast<::std::string>((::std::streamoff) (sizeof(char_type) * _Off)));
					result = ::SetFilePointer(file_, begin_ + (::std::streamoff) (sizeof(char_type) * _Off), NULL, FILE_BEGIN);
					bufferPos_ = result - begin_;
				} else if (_Way == ios_base::cur) {
					LOG4CXX_DEBUG(log, "offset + begin = " + ::boost::lexical_cast<::std::string>(begin_ + bufferPos_ + (::std::streamoff) (sizeof(char_type) * _Off)));
					LOG4CXX_DEBUG(log, "offset = " + ::boost::lexical_cast<::std::string>(bufferPos_ + (::std::streamoff) (sizeof(char_type) * _Off)));
					result = ::SetFilePointer(file_, begin_ + bufferPos_ + (::std::streamoff) (sizeof(char_type) * _Off), NULL, FILE_BEGIN);
					bufferPos_ = result - begin_;
				} else {
					LOG4CXX_DEBUG(log, "offset + begin = " + ::boost::lexical_cast<::std::string>(end_ + (::std::streamoff) (sizeof(char_type) * _Off)));
					LOG4CXX_DEBUG(log, "offset = " + ::boost::lexical_cast<::std::string>(end_ - begin_ + (::std::streamoff) (sizeof(char_type) * _Off)));
					result = ::SetFilePointer(file_, end_ + (::std::streamoff) (sizeof(char_type) * _Off), NULL, FILE_BEGIN);
					bufferPos_ = result - begin_;
				}

				if (result == INVALID_SET_FILE_POINTER) {
					LOG4CXX_DEBUG(log, "INVALID_SET_FILE_POINTER");
					LOG4CXX_DEBUG(log, "seekoff end.");
					return pos_type(-1);
				}

				LOG4CXX_DEBUG(log, "point = " + ::boost::lexical_cast<::std::string>(result));

				// バッファ先頭位置を設定
				DWORD readSize = 0;
				// ファイル読み込み
				::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);


				if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
					// ファイル位置、設定が、終端より大きくなるので、調整
					readSize = end_ - begin_ - bufferPos_;
				}

				// ファイルバッファを設定
				setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)] );
				LOG4CXX_DEBUG(log, "readSize = " + ::boost::lexical_cast<::std::string>(readSize));
				LOG4CXX_DEBUG(log, "bufferSize = " + ::boost::lexical_cast<::std::string>(readSize / sizeof(char_type)));
				LOG4CXX_DEBUG(log, "seekoff end.");

				return result;
			}
			/**
			 * 読み込み位置を移動する
			 */
			virtual pos_type seekpos( pos_type _Sp, ios_base::openmode _Which = ios_base::in) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "seekpos begin.");

				if (!is_open()) {
					LOG4CXX_DEBUG(log, "file is close.");
					LOG4CXX_DEBUG(log, "seekpos end.");
					return pos_type(-1);
				}

				if (_Which != ios_base::in) {
					LOG4CXX_DEBUG(log, "illegal argument.");
					LOG4CXX_DEBUG(log, "seekpos end.");
					return pos_type(-1);
				}

				DWORD result = ::SetFilePointer(file_, begin_ + (::std::streamoff) (sizeof(char_type) * _Sp), NULL, FILE_BEGIN);
				if (result == INVALID_SET_FILE_POINTER) {
					LOG4CXX_DEBUG(log, "seekpos end.");
					return pos_type(-1);
				}

				// バッファ先頭位置を設定
				bufferPos_ = result;

				DWORD readSize = 0;
				// ファイル読み込み
				::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);
				if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
					// ファイル位置、設定が、終端より大きくなるので、調整
					readSize = end_ - begin_ - bufferPos_;
				}

				// ファイルバッファを設定
				setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)] );				

				LOG4CXX_DEBUG(log, "seekpos end.");
				return result;
			}
			/**
			 * 文字を１文字読み取る。
			 */
			virtual int_type underflow() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "underflow begin.");

				if (!is_open()) {
					LOG4CXX_DEBUG(log, "file is close.");
					LOG4CXX_DEBUG(log, "underflow end.");
					return traits_type::eof();
				}

				if (egptr() <= gptr()) {
					// 読み取りポインタの移動できる終端位置 < 現在の読み取りポインタの位置の場合の処理

					if (getSize() < bufferPos_ + (::std::streamoff)((gptr() - egptr()) * sizeof(char_type))) {
						// ファイルの終端なので、エラー
						LOG4CXX_DEBUG(log, "size = " + ::boost::lexical_cast<::std::string>(getSize()));
						LOG4CXX_DEBUG(log, "pos = " + ::boost::lexical_cast<::std::string>(bufferPos_ + (::std::streamoff)((gptr() - egptr()) * sizeof(char_type))));
						LOG4CXX_DEBUG(log, "read error.");
						LOG4CXX_DEBUG(log, "underflow end.");
						return traits_type::eof();					
					}

					LOG4CXX_DEBUG(log, "file read.");
					DWORD readSize = 0;
					// ファイル読み込み
					bufferPos_ += (egptr() - eback()) * sizeof(char_type);
					::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);

					LOG4CXX_DEBUG(log, "bufferPos_ = " + ::boost::lexical_cast<::std::string>(bufferPos_));
					LOG4CXX_DEBUG(log, "readSize = " + ::boost::lexical_cast<::std::string>(readSize));
					LOG4CXX_DEBUG(log, "end_ = " + ::boost::lexical_cast<::std::string>(end_));

					if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
						// ファイル位置、設定が、終端より大きくなるので、調整
						readSize = end_ - begin_ - bufferPos_;
					}

					// ファイルバッファを設定
					setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)]);

					if (egptr() <= gptr()) {
						LOG4CXX_DEBUG(log, "file eof.");
						LOG4CXX_DEBUG(log, "underflow end.");
						// ファイルの終端なので、エラー
						return traits_type::eof();
					}
				}

				LOG4CXX_DEBUG(log, "underflow end.");
				// 現在のポインタの位置を返す。
				return Tr::to_int_type(*gptr());
			}
			/**
			 * 文字を１文字読み取り、ポインタを一つ進める。
			 */
			virtual int_type uflow() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "uflow begin.");

				if (!is_open()) {
					LOG4CXX_DEBUG(log, "uflow end.");
					return traits_type::eof();
				}

				int_type result = underflow();
				gbump(1);

				LOG4CXX_DEBUG(log, "uflow end.");
				return result;
			}
		private:
			/**
			 * アーカイブファイルの拡張子取得
			 */
			::std::string get_extension() const {
				return ".waf";
			}
			/**
			 * バッファサイズの取得
			 * \retval バッファサイズ[sizeof(char_type)]
			 */
			int getBufferSize() const {
				return 1024 * 4;
			}
			/**
			 * ファイルサイズの取得
			 * \retval ファイルサイズ[byte]
			 */
			int getSize() const {
				return end_ - begin_;
			}
			/**
			 * ファイルハンドル
			 */
			HANDLE		file_;
			/**
			 * file_の先頭アドレス [byte]
			 */
			pos_type		begin_;
			/**
			 * file_の終端アドレス+1 [byte]
			 */
			pos_type		end_;
			/**
			 * バッファの先頭位置(各ファイルの先頭からの) [byte]
			 */
			pos_type		bufferPos_;
			/**
			 * ファイルの保存モード
			 */
			ARCHIVE_MODE	mode_;
			/**
			 * バッファ
			 */
			::std::vector< char_type > buffer_;
		};

		template <class Elem, class Tr = ::std::char_traits<Elem> >
		class basic_waf_ifstream : public ::std::basic_istream<Elem, Tr> {
		public:
			typedef typename ::std::ios_base ios_base;

			/**
			 * デフォルトコンストラクタ
			 */
			basic_waf_ifstream() : ::std::basic_istream<Elem, Tr>(new ::pss::std::basic_waf_filebuf<Elem, Tr>()){
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream begin.");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream end.");
			}
			/**
			 * コンストラクタ
			 */
			explicit basic_waf_ifstream(::boost::filesystem::path _Filename, ::std::ios_base::openmode _Mode = ios_base::in) : ::std::basic_istream<Elem, Tr>(new ::pss::std::basic_waf_filebuf<Elem, Tr>(_Filepath, _Which)) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream begin.");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream end.");
			}
			/**
			 * デストラクタ
			 */
			virtual ~basic_waf_ifstream() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "~basic_waf_ifstream begin.");
				delete rdbuf();
				LOG4CXX_DEBUG(log, "~basic_waf_ifstream end.");
			}
			/**
			 * ファイルクローズ
			 */
			void close() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "close begin.");
				((::pss::std::basic_waf_filebuf<Elem, Tr>*) rdbuf())->close();
				LOG4CXX_DEBUG(log, "close end.");
			}
			/**
			 * ファイルオープン中か
			 * @retval true オープン
			 * @retval false 非オープン
			 */
			bool is_open() {
				return rdbuf()->is_open();
			}
			/**
			 * ファイルオープン
			 */
			::pss::std::basic_waf_filebuf<Elem, Tr>* open(::boost::filesystem::path _Filename, ::std::ios_base::openmode _Mode = ios_base::in) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "open begin.");
				::pss::std::basic_waf_filebuf<Elem, Tr>* result = ((::pss::std::basic_waf_filebuf<Elem, Tr>*) rdbuf())->open(_Filename, _Mode);
				if (result == NULL) {
					setstate(::std::ios::failbit);
				}
				LOG4CXX_DEBUG(log, "close end.");
				return result;
			}
		};
	}
}