/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/Attic/countptr.h,v 1.3 2002/04/29 16:28:42 ama Exp $
 */

#ifndef __COUNT_PTR
#define __COUNT_PTR

namespace zefiro_std{

/**
 *	�Q�ƃJ�E���^�t���X�}�[�g�|�C���^�̃e���v���[�g�ł���B
 *	�X�}�[�g�|�C���^�̓I�u�W�F�N�g���g���Ȃ��Ȃ�Ǝ����I��delete���s���B
 *	�W��C++�ł�auto_ptr<class X>����`����Ă��邪�Acount_ptr<class X>�́A
 *	auto_ptr<class X>���_��Ɉ�����悤�ɂȂ��Ă���B
 *	auto_ptr<class X>�̓R�s�[���s���ƃR�s�[���͖����ɂȂ邪�Acount_ptr<class X>�͖����ɂȂ�Ȃ��B
 *	���������āA���ׂẴ|�C���^���f�X�g���N�g���ꂽ�ꍇ�ɂ̂�delete�������悤�ɂȂ��Ă���B
 *	���̃��J�j�Y���́A���̃|�C���^�I�u�W�F�N�g�̓I�u�W�F�N�g�̃R�s�[�񐔂�ێ����Ă���A
 *	�R�s�[�񐔂�0�ɂȂ����Ƃ��̂݃|�C���^�̐�̃I�u�W�F�N�g�̃f�X�g���N�g���s���B
 */
template <class X>
class count_ptr {
	/**
	 *	X�I�u�W�F�N�g�ւ̃|�C���^
	 *	X�I�u�W�F�N�g�ւ̃|�C���^�ł���B�Ȃɂ��ێ����Ă��Ȃ��ꍇ��NULL�ɂȂ�B
	 */
	X*			ptr_;
	/**
	 *	�Q�ƃJ�E���^�ւ̃|�C���^
	 *	�Q�ƃJ�E���^�̓I�u�W�F�N�g���Q�ƃR�s�[����Ă������ێ�����ϐ��ł���B
	 */
	unsigned*	cnt_;
	/**
	 *	�Q�ƃJ�E���^�̃C���N�������g
	 *	@param r��this�I�u�W�F�N�g�ɃR�s�[����B�Q�ƃJ�E���^��0�łȂ���΃C���N�������g����B
	 */
	void inc_ref( const count_ptr& r );
	/**
	 *	�Q�ƃJ�E���^�̃f�N�������g
	 *	�Q�ƃJ�E���^��0�łȂ���΃f�N�������g���A���ʂ�0�Ȃ�X�I�u�W�F�N�g���f�X�g���N�g����B
	 */
	void dec_ref();
public:
	/**
	 *�@�R���X�g���N�^
	 *	@param p�͎Q�ƃJ�E���g�t���X�}�[�g�|�C���^�ň����I�u�W�F�N�g�ւ̃|�C���^�ł���B
	 */
	explicit count_ptr(X* p = 0):ptr_(p),cnt_(0){
		if( p ){  // �I�u�W�F�N�g����Ȃ�J�E���^�̍쐬
			cnt_ = new unsigned(1);
		}
	}
	/**
	 *	�R�s�[�R���X�g���N�^
	 *	@param r�̓R�s�[����I�u�W�F�N�g�ł���B
	 */
	count_ptr(const count_ptr& r){
		inc_ref(r);
	}
	/**
	 *	�f�X�g���N�^
	 */
	~count_ptr(){
		dec_ref();
	}
	/**
	 *	������Z�q
	 *	@param r�͑�����̃I�u�W�F�N�g�ł���B
	 *	@return �����̃I�u�W�F�N�g�ւ̃|�C���^�ł���B
	 */
	count_ptr& operator=(const count_ptr& r){
		if( this != &r ){
			dec_ref();
			inc_ref(r);
		}
		return *this;
	}
	/**
	 *	�|�C���^���Z�q
	 *	@return X�I�u�W�F�N�g�ւ̎Q�Ƃł���B
	 */
	X& operator*() const
	{
		return *ptr_;
	}
	/**
	 *	�����o�I�����Z�q
	 *	@return X�I�u�W�F�N�g�ւ̃|�C���^�ł���B
	 */
	X* operator->() const
	{
		return ptr_;
	}
	/**
	 *	�I�u�W�F�N�g�|�C���^�̎擾
	 *	@return X�I�u�W�F�N�g�ւ̃|�C���^�ł���B
	 */
	X* get() const
	{
		return ptr_;
	}
	/**
	 *	���j�[�N���̃`�F�b�N
	 *	\retval true ���j�[�N�ȃI�u�W�F�N�g
	 *	\retval false ���j�[�N�łȂ��I�u�W�F�N�g
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
