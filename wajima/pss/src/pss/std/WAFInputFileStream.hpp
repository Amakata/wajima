#include <streambuf>
#include <ios>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <windows.h>

namespace pss {
	namespace std {
		template <class Elem, class Tr = ::std::char_traits<Elem> >
		class basic_waf_filebuf : public ::std::basic_streambuf<Elem, Tr> {
		public:
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
			 * コンストラクタ
			 */
			basic_waf_filebuf() : file_(NULL) {
			}
			/**
			 * ファイルクローズ
			 */
			basic_waf_filebuf *close() {
				if (is_open()) {
					::CloseHandle(file_);
					file_ = NULL;
					buffer_.resize(0);
					
				}
				return this;
			}
			/**
			 * ファイルオープンしているか
			 */
			bool is_open( ) {
				return file? != NULL;
			}
			/**
			 * ファイルオープン
			 */
			basic_waf_filebuf *open(::boost::filesystem::path _Filepath, ::std::ios_base::open_mode _Mode) {
				// ファイルのパスをフルパスに変換
				::boost::filesystem::path file = ::boost::filesystem::complete(::boost::filesystem::path(_Filepath, ::boost::filesystem::windows_name));

				if (::boost::filesystem::exists(file)) {
					// _Filepathで指定されたファイルが存在する場合
					file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if (INVALID_HANDLE_VALUE  == file_) {
						file_ = NULL;
						return NULL;
					}

					// モード：ノーマル
					mode_ = NORMAL;
					buffer_.resize(1024 * 4);
					setg(&buffer_[0], &buffer_[0], &buffer_[1024 * 4]);
					begin_ = 0;
					end_ = ::GetFileSize(file_, NULL);
					return this;
				} else {
					// _Filepathで指定されたファイル画存在しない場合。

					// アーカイブ内ファイル名
					::std::string inner_file = file.leaf();

					// アーカイブファイル名
					file = ::boost::filesystem::change_extension(file.branch_path(), get_extension());

					if (::boost::filesystem::exists(file)) {
						// _Filepathの上位ディレクトリにWAFファイルが存在する場合

						file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if (INVALID_HANDLE_VALUE  == file_) {
							file_ = NULL;
							return NULL;
						}

						// アーカイブファイルのヘッダ情報
						struct Header {
							DWORD	size_;
							ARCHIVE_MODE	mode_;
							char	filename_[258];
						} header;

						DWORD readSize;
						while (1) {
							// アーカイブの先頭から順次読み込み
							if (0 == ::ReadFile(file_, &header, sizeof(header), &readSize, NULL) || readSize != sizeof(header)) {
								// ヘッダが読み込めない。
								close();
								return NULL;
							}
							// サイズ-1なのでファイル終端
							if (aize_ == -1) {
								close();
								return NULL;
							}
							// ファイル名が同じならそのアーカイブを利用
							if (file_ == ::std::string(filename_)) {
								DWORD modeSize;
								begin_ = ::SetFilePointer(file_, 0 , NULL, FILE_CURRENT);
								if (begin_ == INVALID_SET_FILE_POINTER) {
									close();
									return NULL;
								}
								end_ = begin_ + header.size_;
								mode_ = header.mode_;
								break;
							}
						}
						buffer_.resize(1024 * 4);
						setg(&buffer_[0], &buffer_[0], &buffer_[1024 * 4]);
						return this;
					} else {

						// ファイルが存在しない場合。
						return NULL;
					}
				}
			}
		protected:
			/**
			 * 文字を１文字読み戻す。uflow()のキャンセル操作
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof) {
			}
			/**
			 * 読み込み位置を移動する。
			 */
			virtual pos_type seekoff(off_type _Off, ios_base::seekdir _Way, ios_base::openmode _Which = ios_base::in) {
				if (_Which == ios_base::in) {
					return pos_type(-1);
				}
				DWORD method;
				if (_Way == ios_base::beg) {
					method = FILE_BEGIN;
				} else if (_Way == ios_base::cur) {
					method = FILE_CURRENT;
				} else {
					method = FILE_END;
				}
				DWORD result = ::SetFilePointer(file_, begin_ + (::std::streamoff) (sizeof(char_type) * _Off), NULL, method);
				if (result == INVALID_SET_FILE_POINTER) {
					if (NO_ERROR == ::GetLastError()) {
						return pos_type(-1);
					}
				}
				return result;


			}
			/**
			 * 読み込み位置を移動する
			 */
			virtual pos_type seekpos( pos_type _Sp, ios_base::openmode _Which = ios_base::in) {
				if (_Which == ios_base::in) {
					return pos_type(-1);
				}
				DWORD result = ::SetFilePointer(file_, begin_ + (::std::streamoff) (sizeof(char_type) * _Sp), NULL, FILE_BEGIN);
				if (result == INVALID_SET_FILE_POINTER) {
					if (NO_ERROR == ::GetLastError()) {
						return pos_type(-1);
					}
				}
				return result;
			}
			/**
			 * 文字を１文字読み取る。
			 */
			virtual int_type underflow() {
				return traits_type::eof;
			}
			/**
			 * 文字を１文字読み取り、ポインタを一つ進める。
			 */
			virtual int_type uflow() {
				return traits_type::eof;
			}
		private:
			/**
			 * アーカイブファイルの拡張子取得
			 */
			::std::string get_extention() const {
				return ".waf";
			}
			enum ARCHIVE_MODE {NORMAL,WAF_NORMAL,WAF_ZLIB};
			HANDLE		file_;

			pos_type		begin_;
			pos_type		end_;
			ARCHIVE_MODE	mode_;
			::std::vector< char_type > buffer_;
		};

		template <class Elem, class Tr = ::std::char_traits<Elem> >
		class basic_waf_ifstream : public ::std::basic_istream<Elem, Tr> {
		public:
			/**
			 * デフォルトコンストラクタ
			 */
			basic_waf_ifstream();
			/**
			 * コンストラクタ
			 */
			explicit basic_waf_ifstream(const char *_Filename,::std::ios_base::openmode _Mode = ::std::ios_base::in);
			/**
			 * ファイルクローズ
			 */
			void close();
			/**
			 * ファイルオープン中か
			 */
			bool is_open();
			basic_waf_filebuf<Elem, Tr> *open(const char *_Filename,::std::ios_base::openmode _Mode) {
				basic_waf_filebuf<Elem, Tr> *result = rdbuf()->open(_Filename, _Mode);
				if (result == NULL) {
					setstate(::std::ios::failbit);
				}
				return result;
			}
			basic_waf_filebuf<Elem, Tr> *rdbuf() const;
		};
	}
}