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
			 * �R���X�g���N�^
			 */
			basic_waf_filebuf() : file_(NULL) {
			}
			/**
			 * �t�@�C���N���[�Y
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
			 * �t�@�C���I�[�v�����Ă��邩
			 */
			bool is_open( ) {
				return file? != NULL;
			}
			/**
			 * �t�@�C���I�[�v��
			 */
			basic_waf_filebuf *open(::boost::filesystem::path _Filepath, ::std::ios_base::open_mode _Mode) {
				// �t�@�C���̃p�X���t���p�X�ɕϊ�
				::boost::filesystem::path file = ::boost::filesystem::complete(::boost::filesystem::path(_Filepath, ::boost::filesystem::windows_name));

				if (::boost::filesystem::exists(file)) {
					// _Filepath�Ŏw�肳�ꂽ�t�@�C�������݂���ꍇ
					file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if (INVALID_HANDLE_VALUE  == file_) {
						file_ = NULL;
						return NULL;
					}

					// ���[�h�F�m�[�}��
					mode_ = NORMAL;
					buffer_.resize(1024 * 4);
					setg(&buffer_[0], &buffer_[0], &buffer_[1024 * 4]);
					begin_ = 0;
					end_ = ::GetFileSize(file_, NULL);
					return this;
				} else {
					// _Filepath�Ŏw�肳�ꂽ�t�@�C���摶�݂��Ȃ��ꍇ�B

					// �A�[�J�C�u���t�@�C����
					::std::string inner_file = file.leaf();

					// �A�[�J�C�u�t�@�C����
					file = ::boost::filesystem::change_extension(file.branch_path(), get_extension());

					if (::boost::filesystem::exists(file)) {
						// _Filepath�̏�ʃf�B���N�g����WAF�t�@�C�������݂���ꍇ

						file_ = ::CreateFile(file.native_file_string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if (INVALID_HANDLE_VALUE  == file_) {
							file_ = NULL;
							return NULL;
						}

						// �A�[�J�C�u�t�@�C���̃w�b�_���
						struct Header {
							DWORD	size_;
							ARCHIVE_MODE	mode_;
							char	filename_[258];
						} header;

						DWORD readSize;
						while (1) {
							// �A�[�J�C�u�̐擪���珇���ǂݍ���
							if (0 == ::ReadFile(file_, &header, sizeof(header), &readSize, NULL) || readSize != sizeof(header)) {
								// �w�b�_���ǂݍ��߂Ȃ��B
								close();
								return NULL;
							}
							// �T�C�Y-1�Ȃ̂Ńt�@�C���I�[
							if (aize_ == -1) {
								close();
								return NULL;
							}
							// �t�@�C�����������Ȃ炻�̃A�[�J�C�u�𗘗p
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

						// �t�@�C�������݂��Ȃ��ꍇ�B
						return NULL;
					}
				}
			}
		protected:
			/**
			 * �������P�����ǂݖ߂��Buflow()�̃L�����Z������
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof) {
			}
			/**
			 * �ǂݍ��݈ʒu���ړ�����B
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
			 * �ǂݍ��݈ʒu���ړ�����
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
			 * �������P�����ǂݎ��B
			 */
			virtual int_type underflow() {
				return traits_type::eof;
			}
			/**
			 * �������P�����ǂݎ��A�|�C���^����i�߂�B
			 */
			virtual int_type uflow() {
				return traits_type::eof;
			}
		private:
			/**
			 * �A�[�J�C�u�t�@�C���̊g���q�擾
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
			 * �f�t�H���g�R���X�g���N�^
			 */
			basic_waf_ifstream();
			/**
			 * �R���X�g���N�^
			 */
			explicit basic_waf_ifstream(const char *_Filename,::std::ios_base::openmode _Mode = ::std::ios_base::in);
			/**
			 * �t�@�C���N���[�Y
			 */
			void close();
			/**
			 * �t�@�C���I�[�v������
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