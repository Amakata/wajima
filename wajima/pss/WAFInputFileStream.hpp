#include <streambuf>

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
			/**
			 * �R���X�g���N�^
			 */
			basic_waf_filebuf();
			/**
			 * �t�@�C���N���[�Y
			 */
			basic_waf_filebuf *close();
			/**
			 * �t�@�C���I�[�v�����Ă��邩
			 */
			bool is_open( );
			/**
			 * �t�@�C���I�[�v��
			 */
			basic_waf_filebuf *open(const char *_Filename, ::std::ios_base::openmode _Mode);
		protected:
			/**
			 * �������P�����ǂݖ߂��Buflow()�̃L�����Z������
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof);
			/**
			 * �ǂݍ��݈ʒu���ړ�����B
			 */
			virtual pos_type seekoff(off_type _Off, ::std::ios_base::seekdir _Way, ::std::ios_base::openmode _Which = ::std::ios_base::in);
			/**
			 * �ǂݍ��݈ʒu���ړ�����
			 */
			virtual pos_type seekpos( pos_type _Sp, ::std::ios_base::openmode _Which = ::std::ios_base::in);
			/**
			 * �ǂݍ��݈ʒu���ړ�����
			 */
			virtual basic_streambuf *setbuf(char_type *_Buffer, ::std::streamsize _Count);
			/**
			 * �������P�����ǂݎ��B
			 */
			virtual int_type underflow();
			/**
			 * �������P�����ǂݎ��A�|�C���^����i�߂�B
			 */
			virtual int_type uflow();
		}

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