#include <loki/SmartPtr.h>
#include <loki/Singleton.h>
#include "pss/system/Thread.hpp"
#include "pss/system/ThreadingModel.hpp"
#include "Win32Exception.hpp"

namespace pss {
	namespace std {
		/**
		 * SmartPtrがNULLの場合に、::pss::std::NullPointerExceptionをthrowするポリシークラス
		 */
		template <class P>
		struct RejectNull
		{
			RejectNull()
			{}
	        
			template <class P1>
			RejectNull(const RejectNull<P1>&)
			{}
	        
			static void OnInit(P val){ 
				if (!val){
					PSS_THORW(::pss::std::NullPointerException,"");
				}
			}

			static void OnDefault(P val)
			{}
	        
			void OnDereference(P val){
				if (!val){
					PSS_THORW(::pss::std::NullPointerException,"");
				}
			}
			void Swap(RejectNull&)
			{}        
		};
		/**
		 * COMの初期化、シャットダウンクラス
		 */
		class Win32COM : public ::pss::system::ClassLevelCountedLockable<Win32COM> {	
		public:
			typedef ::Loki::SingletonHolder<Win32COM> SingleWin32Com;
			virtual ~Win32COM(){
			}
			void init(){
				Lock lock(*this);
				if( count_.empty() || count_ == 0 ){
					count_ = 0;
					HRESULT result = ::CoInitialize(NULL); 
					if( S_OK != result ){
						PSS_THROW_PARAM1( ::pss::std::Win32Error(result) , "");	
					}
				}
				count_ = count_ + 1;
			}
			void shutdown(){
				Lock lock(*this);
				if (count_.empty()) {
					return;
				}
				count_= count_-1;
				if (count_ == 0) {
					::CoUninitialize();
				}
			}
		protected:
			friend ::Loki::CreateUsingNew<Win32COM>;
			Win32COM(){
			}
		private:
			::pss::system::ThreadLocal<int> count_;
		};
		/**
		 * COMObjectをSmartPtrで保持するためのクラス
		 */
		template <class T>
		class COMObject {
		public:
			COMObject():obj_(NULL),comInit_(false){
			}
			virtual ~COMObject(){
				release();
			}
			void create(REFCLSID clsid,REFIID guid){
				if( NULL == obj_ ){
					Win32COM& com = Win32COM::SingleWin32Com::Instance();
					com.init();
					comInit_ = true;
					release();
					HRESULT result = ::CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, guid, (LPVOID*) &obj_);
					if( FAILED(result) ){
						obj_ = NULL;
						com.shutdown();
						PSS_THROW_PARAM1(::pss::std::Win32Error(result), "");	
					}
				}
			}
			T* get()const{
				return obj_;
			}
			void set( T* obj ){
				if( NULL == obj_ ){
					obj_ = obj;
				}
			}
			bool empty() const{
				return obj_ == NULL;
			}
			void release(){
				if( obj_ == NULL ){
					return;
				}
				obj_->Release();
				obj_ = NULL;
				if( comInit_ ){
					Win32COM& com = Win32COM::SingleWin32Com::Instance();
					com.shutdown();
					comInit_ = false;
				}
			}
			T& operator*() const  {return *obj_; }
			T* operator->() const {return obj_; }
		private:
			bool comInit_;
			T* obj_;
		};
		/**
		 * 非参照カウンターポリシー
		 */
		template <class P>
		class NoOwnerRefCounted;
		/**
		 * 参照カウンターポリシー
		 */
		template <class P>
		class RefCounted
		{
			friend class NoOwnerRefCounted<P>;
		public:
			RefCounted() 
			{
				pCount_ = new unsigned int;
				assert(pCount_);
				*pCount_ = 1;
			}       
			RefCounted(const RefCounted& rhs)
			: pCount_(rhs.pCount_)
			{}
			// MWCW lacks template friends, hence the following kludge
			template <typename P1>
			RefCounted(const RefCounted<P1>& rhs) 
			: pCount_(reinterpret_cast<const RefCounted&>(rhs).pCount_)
			{
			}     
			template <typename P1>
			RefCounted( const NoOwnerRefCounted<P1>& rhs)
			: pCount_(reinterpret_cast<const NoOwnerRefCounted<P1>&>(rhs).pCount_)
			{
			}
			P Clone(const P& val)
			{
				++*pCount_;
				return val;
			}
	        
			bool Release(const P&, bool = false)
			{
				if (!--*pCount_)
				{
					delete pCount_;
					return true;
				}
				return false;
			}
	        
			void Swap(RefCounted& rhs)
			{ ::std::swap(pCount_, rhs.pCount_); }
	    
			enum { destructiveCopy = false };

		private:
			// Data
			unsigned int* pCount_;
		};


		template <class P>
		class NoOwnerRefCounted
		{
			friend class RefCounted<P>;
		public:        
			NoOwnerRefCounted(const NoOwnerRefCounted& rhs) 
			: pCount_(rhs.pCount_)
			{}
			// MWCW lacks template friends, hence the following kludge
			template <typename P1>
			NoOwnerRefCounted(const NoOwnerRefCounted<P1>& rhs) 
			: pCount_(reinterpret_cast<const NoOwnerRefCounted&>(rhs).pCount_)
			{
			}
			template <typename P1>
			NoOwnerRefCounted(const RefCounted<P1>& rhs)
			: pCount_(reinterpret_cast<const RefCounted<P1>&>(rhs).pCount_)
			{
			}

			P Clone(const P& val)
			{
				return val;
			}
	        
			bool Release(const P&, bool = false)
			{
				return false;
			}
	        
			void Swap(NoOwnerRefCounted& rhs)
			{ ::std::swap(pCount_, rhs.pCount_); }
	    
			enum { destructiveCopy = false };

		private:
			// Data
			unsigned int* pCount_;
		};
		/**
		 * スレッド対応参照カウンタ
		 */
		template <template <class> class ThreadingModel>
		struct RefCountedMTAdj
		{
			template <class P>
			class RefCountedMT : public ThreadingModel< RefCountedMT<P> >
			{
				typedef ThreadingModel< RefCountedMT<P> > base_type;
				typedef typename base_type::IntType       CountType;
				typedef volatile CountType               *CountPtrType;

			public:
				RefCountedMT() 
				{
					pCount_ = new CountType;
					assert(pCount_);
					*pCount_ = 1;
				}

				RefCountedMT(const RefCountedMT& rhs) 
				: pCount_(rhs.pCount_)
				{}

				//MWCW lacks template friends, hence the following kludge
				template <typename P1>
				RefCountedMT(const RefCountedMT<P1>& rhs) 
				: pCount_(reinterpret_cast<const RefCountedMT<P>&>(rhs).pCount_)
				{}

				P Clone(const P& val)
				{
					Lock lock(*this);
					ThreadingModel<RefCountedMT>::AtomicIncrement(*pCount_);
					return val;
				}

				bool Release(const P&)
				{
					Lock lock(*this);
					if (!ThreadingModel<RefCountedMT>::AtomicDecrement(*pCount_))
					{
						delete  pCount_;
						return true;
					}
					return false;
				}

				void Swap(RefCountedMT& rhs)
				{ 	Lock lock(*this);
					::std::swap(pCount_, rhs.pCount_);
				}

				enum { destructiveCopy = false };

			private:
				// Data
				CountPtrType pCount_;
			};
		};
	}
}