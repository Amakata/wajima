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
			 * �t�@�C���̕ۑ����[�h
			 * NORMAL		�ʏ�t�@�C��
			 * WAF_NORMAL	WAF�t�@�C���񈳏k
			 * WAF_ZLIB		WAF�t�@�C��ZLIB
			 */
			enum ARCHIVE_MODE {NORMAL,WAF_NORMAL,WAF_ZLIB};
			/**
			 * �A�[�J�C�u�t�@�C���w�b�_�\����
			 */
			struct Header {
				DWORD	size_;
				ARCHIVE_MODE	mode_;
				char	filename_[260];
			};
			/**
			 * �v�f�^
			 */
			typedef Elem char_type;
			/**
			 * Eleme�̓����^
			 */
			typedef Tr traits_type;
			typedef typename traits_type::int_type int_type;
			typedef typename traits_type::off_type off_type;
			typedef typename traits_type::pos_type pos_type;
			typedef typename ::std::ios_base ios_base;
			/**
			 * �f�t�H���g�R���X�g���N�^
			 */
			basic_waf_filebuf() : file_(NULL) {
			}
			/**
			 * �R���X�g���N�^
			 * @param _Filepath �t�@�C���p�X
			 * @param _Which �I�[�v�����[�h
			 */
			basic_waf_filebuf(::boost::filesystem::path _Filepath,  ios_base::openmode _Which = ios_base::in) : file_(NULL) {
				open(_Filepath, _Which);
			}
			/**
			 * �t�@�C���N���[�Y
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
			 * �t�@�C���I�[�v�����Ă��邩
			 */
			bool is_open( ) {
				return file_ != NULL;
			}
			/**
			 * �t�@�C���I�[�v��
			 * �t�@�C���T�C�Y	4byte
			 * �t�@�C�����[�h	4byte
			 * �t�@�C���T�C�Y	260byte
			 * �f�[�^			�t�@�C���T�C�Y
			 */
			basic_waf_filebuf *open(::boost::filesystem::path _Filepath,  ios_base::openmode _Which = ios_base::in ) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "open begin.");
				// �Ƃ肠�����A�ȑO�ɊJ���Ă����t�@�C�����N���[�Y
				close();

				// �t�@�C���̃p�X���t���p�X�ɕϊ�
				::boost::filesystem::path file = ::boost::filesystem::complete(::boost::filesystem::path(_Filepath));

				if (::boost::filesystem::exists(file)) {
					// _Filepath�Ŏw�肳�ꂽ�t�@�C�������݂���ꍇ�A�ȉ��̏��������s

					LOG4CXX_DEBUG(log, "open normal file.");
					LOG4CXX_DEBUG(log, file.string());
					file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if (INVALID_HANDLE_VALUE  == file_) {
						// �t�@�C���n���h���������̏ꍇ
						file_ = NULL;
						return NULL;
					}

					// ���[�h�F�m�[�}��
					mode_ = NORMAL;
					// �o�b�t�@�m��
					buffer_.resize(getBufferSize() * sizeof(char_type));
					// �o�b�t�@�T�C�Y��ݒ�
					setg(&buffer_[0], &buffer_[0], &buffer_[0]);
					// �t�@�C���̐擪�ʒu
					begin_ = 0;
					// �t�@�C���̏I�[�ʒu
					end_ = ::GetFileSize(file_, NULL);
					// �o�b�t�@�̐擪�ʒu
					bufferPos_ = 0;

					return this;

				} else {
					// _Filepath�Ŏw�肳�ꂽ�t�@�C���摶�݂��Ȃ��ꍇ�́A�ȉ��̏��������s�B

					// �A�[�J�C�u���t�@�C����
					::std::string inner_file = file.leaf();

					// �A�[�J�C�u�t�@�C����
					file = ::boost::filesystem::change_extension(file.branch_path(), get_extension());
					
					if (::boost::filesystem::exists(file)) {
						// _Filepath�̏�ʃf�B���N�g����WAF�t�@�C�������݂���ꍇ

						LOG4CXX_DEBUG(log, "file is waf file.");
						LOG4CXX_DEBUG(log, file.string());

						file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if (INVALID_HANDLE_VALUE  == file_) {
							// �t�@�C���n���h���������̏ꍇ�̏���
							file_ = NULL;
							return NULL;
						}

						// �A�[�J�C�u�t�@�C���̃w�b�_���
						Header header;
						DWORD readSize;
						
						while (1) {
							// �A�[�J�C�u�̐擪���珇���ǂݍ���
							if (0 == ::ReadFile(file_, &header, sizeof(header), &readSize, NULL) || readSize != sizeof(header)) {
								// �w�b�_���ǂݍ��߂Ȃ��B
								close();
								return NULL;
							}
							LOG4CXX_DEBUG(log, "header.size = " + ::boost::lexical_cast<::std::string>(header.size_));
							LOG4CXX_DEBUG(log, "header.mode = " + ::boost::lexical_cast<::std::string>(header.mode_));
							LOG4CXX_DEBUG(log, "header.filename = " + ::boost::lexical_cast<::std::string>(header.filename_));

							if (header.size_ == -1) {
								// �T�C�Y-1�Ȃ̂Ńt�@�C���I�[
								close();
								return NULL;
							}
							if (inner_file == ::std::string(header.filename_)) {
								// �t�@�C�����������Ȃ炻�̃A�[�J�C�u�𗘗p

								// �t�@�C���̐擪�ݒ�
								DWORD modeSize = ::SetFilePointer(file_, 0 , NULL, FILE_CURRENT);

								// �t�@�C���̐擪�ݒ�
								begin_ = modeSize;
								if (modeSize == INVALID_SET_FILE_POINTER) {
									// �����ȃt�@�C���|�C���^
									close();
									return NULL;
								}

								// �t�@�C���̏I�[�ݒ�
								end_ = begin_ + (::std::streamoff) header.size_;

								// ���[�h�ݒ�
								mode_ = header.mode_;

								break;
							}
						}

						// �o�b�t�@���m��
						buffer_.resize(getBufferSize() * sizeof(char_type));

						// �o�b�t�@�T�C�Y��ݒ�
						setg(&buffer_[0], &buffer_[0], &buffer_[0]);

						// �o�b�t�@�擪�ʒu�ݒ�
						bufferPos_ = 0;
						return this;
					} else {
						// �t�@�C�������݂��Ȃ��ꍇ�B

						LOG4CXX_DEBUG(log, "file not exits");
						LOG4CXX_DEBUG(log, file.string());
						return NULL;
					}
				}
			}
		protected:
			/**
			 * �������P�����ǂݖ߂��Buflow()�̃L�����Z������
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof) {
				// ����͖�����
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_filebuf");
				LOG4CXX_DEBUG(log, "pbackfail begin.");
				LOG4CXX_DEBUG(log, "pbackfail end.");
				return traits_type::eof();
			}
			/**
			 * �ǂݍ��݈ʒu���ړ�����B
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

				// �o�b�t�@�擪�ʒu��ݒ�
				DWORD readSize = 0;
				// �t�@�C���ǂݍ���
				::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);


				if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
					// �t�@�C���ʒu�A�ݒ肪�A�I�[���傫���Ȃ�̂ŁA����
					readSize = end_ - begin_ - bufferPos_;
				}

				// �t�@�C���o�b�t�@��ݒ�
				setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)] );
				LOG4CXX_DEBUG(log, "readSize = " + ::boost::lexical_cast<::std::string>(readSize));
				LOG4CXX_DEBUG(log, "bufferSize = " + ::boost::lexical_cast<::std::string>(readSize / sizeof(char_type)));
				LOG4CXX_DEBUG(log, "seekoff end.");

				return result;
			}
			/**
			 * �ǂݍ��݈ʒu���ړ�����
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

				// �o�b�t�@�擪�ʒu��ݒ�
				bufferPos_ = result;

				DWORD readSize = 0;
				// �t�@�C���ǂݍ���
				::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);
				if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
					// �t�@�C���ʒu�A�ݒ肪�A�I�[���傫���Ȃ�̂ŁA����
					readSize = end_ - begin_ - bufferPos_;
				}

				// �t�@�C���o�b�t�@��ݒ�
				setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)] );				

				LOG4CXX_DEBUG(log, "seekpos end.");
				return result;
			}
			/**
			 * �������P�����ǂݎ��B
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
					// �ǂݎ��|�C���^�̈ړ��ł���I�[�ʒu < ���݂̓ǂݎ��|�C���^�̈ʒu�̏ꍇ�̏���

					if (getSize() < bufferPos_ + (::std::streamoff)((gptr() - egptr()) * sizeof(char_type))) {
						// �t�@�C���̏I�[�Ȃ̂ŁA�G���[
						LOG4CXX_DEBUG(log, "size = " + ::boost::lexical_cast<::std::string>(getSize()));
						LOG4CXX_DEBUG(log, "pos = " + ::boost::lexical_cast<::std::string>(bufferPos_ + (::std::streamoff)((gptr() - egptr()) * sizeof(char_type))));
						LOG4CXX_DEBUG(log, "read error.");
						LOG4CXX_DEBUG(log, "underflow end.");
						return traits_type::eof();					
					}

					LOG4CXX_DEBUG(log, "file read.");
					DWORD readSize = 0;
					// �t�@�C���ǂݍ���
					bufferPos_ += (egptr() - eback()) * sizeof(char_type);
					::ReadFile(file_, &buffer_[0], getBufferSize() * sizeof(char_type), &readSize, NULL);

					LOG4CXX_DEBUG(log, "bufferPos_ = " + ::boost::lexical_cast<::std::string>(bufferPos_));
					LOG4CXX_DEBUG(log, "readSize = " + ::boost::lexical_cast<::std::string>(readSize));
					LOG4CXX_DEBUG(log, "end_ = " + ::boost::lexical_cast<::std::string>(end_));

					if (bufferPos_ + (::std::streamoff) readSize > end_ - begin_) {
						// �t�@�C���ʒu�A�ݒ肪�A�I�[���傫���Ȃ�̂ŁA����
						readSize = end_ - begin_ - bufferPos_;
					}

					// �t�@�C���o�b�t�@��ݒ�
					setg(&buffer_[0], &buffer_[0], &buffer_[readSize / sizeof(char_type)]);

					if (egptr() <= gptr()) {
						LOG4CXX_DEBUG(log, "file eof.");
						LOG4CXX_DEBUG(log, "underflow end.");
						// �t�@�C���̏I�[�Ȃ̂ŁA�G���[
						return traits_type::eof();
					}
				}

				LOG4CXX_DEBUG(log, "underflow end.");
				// ���݂̃|�C���^�̈ʒu��Ԃ��B
				return Tr::to_int_type(*gptr());
			}
			/**
			 * �������P�����ǂݎ��A�|�C���^����i�߂�B
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
			 * �A�[�J�C�u�t�@�C���̊g���q�擾
			 */
			::std::string get_extension() const {
				return ".waf";
			}
			/**
			 * �o�b�t�@�T�C�Y�̎擾
			 * \retval �o�b�t�@�T�C�Y[sizeof(char_type)]
			 */
			int getBufferSize() const {
				return 1024 * 4;
			}
			/**
			 * �t�@�C���T�C�Y�̎擾
			 * \retval �t�@�C���T�C�Y[byte]
			 */
			int getSize() const {
				return end_ - begin_;
			}
			/**
			 * �t�@�C���n���h��
			 */
			HANDLE		file_;
			/**
			 * file_�̐擪�A�h���X [byte]
			 */
			pos_type		begin_;
			/**
			 * file_�̏I�[�A�h���X+1 [byte]
			 */
			pos_type		end_;
			/**
			 * �o�b�t�@�̐擪�ʒu(�e�t�@�C���̐擪�����) [byte]
			 */
			pos_type		bufferPos_;
			/**
			 * �t�@�C���̕ۑ����[�h
			 */
			ARCHIVE_MODE	mode_;
			/**
			 * �o�b�t�@
			 */
			::std::vector< char_type > buffer_;
		};

		template <class Elem, class Tr = ::std::char_traits<Elem> >
		class basic_waf_ifstream : public ::std::basic_istream<Elem, Tr> {
		public:
			typedef typename ::std::ios_base ios_base;

			/**
			 * �f�t�H���g�R���X�g���N�^
			 */
			basic_waf_ifstream() : ::std::basic_istream<Elem, Tr>(new ::pss::std::basic_waf_filebuf<Elem, Tr>()){
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream begin.");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream end.");
			}
			/**
			 * �R���X�g���N�^
			 */
			explicit basic_waf_ifstream(::boost::filesystem::path _Filename, ::std::ios_base::openmode _Mode = ios_base::in) : ::std::basic_istream<Elem, Tr>(new ::pss::std::basic_waf_filebuf<Elem, Tr>(_Filepath, _Which)) {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream begin.");
				LOG4CXX_DEBUG(log, "basic_waf_ifstream end.");
			}
			/**
			 * �f�X�g���N�^
			 */
			virtual ~basic_waf_ifstream() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "~basic_waf_ifstream begin.");
				delete rdbuf();
				LOG4CXX_DEBUG(log, "~basic_waf_ifstream end.");
			}
			/**
			 * �t�@�C���N���[�Y
			 */
			void close() {
				LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("basic_waf_ifstream");
				LOG4CXX_DEBUG(log, "close begin.");
				((::pss::std::basic_waf_filebuf<Elem, Tr>*) rdbuf())->close();
				LOG4CXX_DEBUG(log, "close end.");
			}
			/**
			 * �t�@�C���I�[�v������
			 * @retval true �I�[�v��
			 * @retval false ��I�[�v��
			 */
			bool is_open() {
				return rdbuf()->is_open();
			}
			/**
			 * �t�@�C���I�[�v��
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