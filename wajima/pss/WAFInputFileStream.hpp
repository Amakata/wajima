#include <streambuf>

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
			/**
			 * コンストラクタ
			 */
			basic_waf_filebuf();
			/**
			 * ファイルクローズ
			 */
			basic_waf_filebuf *close();
			/**
			 * ファイルオープンしているか
			 */
			bool is_open( );
			/**
			 * ファイルオープン
			 */
			basic_waf_filebuf *open(const char *_Filename, ::std::ios_base::openmode _Mode);
		protected:
			/**
			 * 文字を１文字読み戻す。uflow()のキャンセル操作
			 */
			virtual int_type pbackfail(int_type _Meta = traits_type::eof);
			/**
			 * 読み込み位置を移動する。
			 */
			virtual pos_type seekoff(off_type _Off, ::std::ios_base::seekdir _Way, ::std::ios_base::openmode _Which = ::std::ios_base::in);
			/**
			 * 読み込み位置を移動する
			 */
			virtual pos_type seekpos( pos_type _Sp, ::std::ios_base::openmode _Which = ::std::ios_base::in);
			/**
			 * 読み込み位置を移動する
			 */
			virtual basic_streambuf *setbuf(char_type *_Buffer, ::std::streamsize _Count);
			/**
			 * 文字を１文字読み取る。
			 */
			virtual int_type underflow();
			/**
			 * 文字を１文字読み取り、ポインタを一つ進める。
			 */
			virtual int_type uflow();
		}

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