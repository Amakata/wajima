#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <std/Exception.h>
#include <std/NotEqualException.h>
#include <sstream>

namespace zefiro_std{
	/** 表明の特性クラス
	 *	表明で比較をするオブジェクトの変換を行う。
	 */
	template <class T>
	struct assertion_traits
	{
		static bool equal( const T& x, const T& y )
		{
			return x == y;
		}
		/**
		 * x 文字列に変換するオブジェクト
		 */
		static std::string toString( const T& x ){
			std::ostringstream oss;
			oss << x;
			return oss.str();
		}
	};

	/**
	 *	表明。
	 *	プログラム内での条件チェックなどに用いる。
	 */
	namespace Assert {
		/**
		 * 表明の実装
		 * 呼び出されて、conditionがもしもfalseならzefiro_std::Exceptionがthrowされる。
		 * \param condition 評価の結果
		 * \param conditionExpression 評価式
		 * \param lineNumber	評価したソースファイルの行番号
		 * \param fileName		評価したソースファイル名	
		 * \throw zefiro_std::Exception 状態がfalseだった。
		 */
		void assertImplementation( bool         condition, 
			                       std::string  conditionExpression = "",
				                   long lineNumber = Exception::UNKNOWNLINENUMBER,
					               std::string  fileName = Exception::UNKNOWNFILENAME );
		/**
		 * 非等価式の表明の実装。
		 * 呼び出されると必ずzefiro_std::NotEqualExceptionがthrowされる。
		 * \param expected 予想値
		 * \param actual 現在値
		 * \param lineNumber	評価したソースファイルの行番号
		 * \param fileName		評価したソースファイル名	
		 * \throw zefiro_std::NotEqualException 必ず発生する。
		*/
		void assertNotEqualImplementation( std::string expected,
			                               std::string actual,
						                   long lineNumber = Exception::UNKNOWNLINENUMBER,
								           std::string  fileName = Exception::UNKNOWNFILENAME );
		/**
		 * 等価の表明
		 * expectedとactualの値を比較し、等価でなければ、zefiro_std::NotEqualExceptionを発生させる。
		 * \param expected 予想値
		 * \param actual 現在値
		 * \param lineNumber	評価したソースファイルの行番号
		 * \param fileName		評価したソースファイル名		 
		 * \throw zefiro_std::NotEqualException 予想値と現在値が異なった。
		 */
		template <class T>
		void assertEquals(	const T& expected ,
							const T& actual ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME ){
			if( ! assertion_traits<T>::equal( expected , actual ) ){
				assertNotEqualImplementation( assertion_traits<T>::toString(expected) , assertion_traits<T>::toString(actual) , lineNumber , fileName );
			}
		}
		/**
		 * 等価の表明
		 * expectedとactualの値を比較し、差の絶対値がdelta以下でなければ、
		 * zefiro_std::NotEqualExceptionを発生させる。
		 * \param expected 予想値
		 * \param actual 現在値
		 * \param delta 許容誤差
		 * \param lineNumber	評価したソースファイルの行番号
		 * \param fileName		評価したソースファイル名		 
		 * \throw zefiro_std::NotEqualException 予想値と現在値の差の絶対値がdeltaより多きかった。
		 */
		void assertEquals(	double expected ,
							double actual ,
							double delta ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME );
	}; // namespace Assert

/// 表明のマクロ
#	define ZEFIRO_STD_ASSERT( condition )\
	(zefiro_std::Assert::assertImplementation((condition),(#condition),\
		__LINE__,__FILE__))

/// 表明のマクロ（メッセージ指定付）
#	define ZEFIRO_STD_ASSERT_MESSAGE( message , condition )\
	(zefiro_std::Assert::assertImplementation( condition, \
												message, \
												__LINE__,\
												__FILE__ ) )
/// 表明のマクロ(等価評価)
#	define ZEFIRO_STD_ASSERT_EQUAL( expected , actual )\
	(zefiro_std::Assert::assertEquals( (epected),(actual),__LINE__,__FILE__))

	/// 表明のマクロ(等価評価、実数)
#	define ZEFIRO_STD_ASSERT_DOUBLES	_EQUAL( expected , actual , delta )\
	(zefiro_std::Assert::assertEquals( expected , actual , delta , __LINE__ , __FILE__ ))

};	// namespace zefiro_std



#endif //__ASSERT_H__