/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/Attic/countptr.h,v 1.3 2002/04/29 16:28:42 ama Exp $
 */

#ifndef __COUNT_PTR
#define __COUNT_PTR

namespace zefiro_std{

/**
 *	参照カウンタ付きスマートポインタのテンプレートである。
 *	スマートポインタはオブジェクトが使われなくなると自動的にdeleteを行う。
 *	標準C++ではauto_ptr<class X>が定義されているが、count_ptr<class X>は、
 *	auto_ptr<class X>より柔軟に扱えるようになっている。
 *	auto_ptr<class X>はコピーを行うとコピー元は無効になるが、count_ptr<class X>は無効にならない。
 *	したがって、すべてのポインタがデストラクトされた場合にのみdeleteがされるようになっている。
 *	このメカニズムは、このポインタオブジェクトはオブジェクトのコピー回数を保持しており、
 *	コピー回数が0になったときのみポインタの先のオブジェクトのデストラクトを行う。
 */
template <class X>
class count_ptr {
	/**
	 *	Xオブジェクトへのポインタ
	 *	Xオブジェクトへのポインタである。なにも保持していない場合はNULLになる。
	 */
	X*			ptr_;
	/**
	 *	参照カウンタへのポインタ
	 *	参照カウンタはオブジェクトが参照コピーされている個数を保持する変数である。
	 */
	unsigned*	cnt_;
	/**
	 *	参照カウンタのインクリメント
	 *	@param rをthisオブジェクトにコピーする。参照カウンタは0でなければインクリメントする。
	 */
	void inc_ref( const count_ptr& r );
	/**
	 *	参照カウンタのデクリメント
	 *	参照カウンタが0でなければデクリメントし、結果が0ならXオブジェクトをデストラクトする。
	 */
	void dec_ref();
public:
	/**
	 *　コンストラクタ
	 *	@param pは参照カウント付きスマートポインタで扱うオブジェクトへのポインタである。
	 */
	explicit count_ptr(X* p = 0):ptr_(p),cnt_(0){
		if( p ){  // オブジェクトが空ならカウンタの作成
			cnt_ = new unsigned(1);
		}
	}
	/**
	 *	コピーコンストラクタ
	 *	@param rはコピーするオブジェクトである。
	 */
	count_ptr(const count_ptr& r){
		inc_ref(r);
	}
	/**
	 *	デストラクタ
	 */
	~count_ptr(){
		dec_ref();
	}
	/**
	 *	代入演算子
	 *	@param rは代入元のオブジェクトである。
	 *	@return 代入先のオブジェクトへのポインタである。
	 */
	count_ptr& operator=(const count_ptr& r){
		if( this != &r ){
			dec_ref();
			inc_ref(r);
		}
		return *this;
	}
	/**
	 *	ポインタ演算子
	 *	@return Xオブジェクトへの参照である。
	 */
	X& operator*() const
	{
		return *ptr_;
	}
	/**
	 *	メンバ選択演算子
	 *	@return Xオブジェクトへのポインタである。
	 */
	X* operator->() const
	{
		return ptr_;
	}
	/**
	 *	オブジェクトポインタの取得
	 *	@return Xオブジェクトへのポインタである。
	 */
	X* get() const
	{
		return ptr_;
	}
	/**
	 *	ユニーク性のチェック
	 *	\retval true ユニークなオブジェクト
	 *	\retval false ユニークでないオブジェクト
	 */
	bool unique() const
	{
		return cnt_ ? *cnt_ == 1 : true;
	}
};

template<class X>
inline void count_ptr<X>::dec_ref()
{
	if( cnt_ ){
		if( --*cnt_ == 0 ){
			delete cnt_;
			delete ptr_;
		}
		cnt_ = 0;
		ptr_ = 0;
	}
}

template<class X>
inline void count_ptr<X>::inc_ref( const count_ptr<X>& r ){
	ptr_ = r.ptr_;
	cnt_ = r.cnt_;
	if( cnt_ ){
 		++*cnt_;
	}
}
}
#endif
