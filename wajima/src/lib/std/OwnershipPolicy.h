/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/OwnershipPolicy.h,v 1.3 2002/11/22 17:07:54 ama Exp $
 */
#ifndef __OWNERSHIPPOLICY_H__
#define __OWNERSHIPPOLICY_H__

#include <SmallObj.h>

namespace zefiro_std {
	template <class P>
    class NoOwnerRefCounted;

	template <class P>
    class RefCounted
    {
		friend class NoOwnerRefCounted<P>;
	public:
        RefCounted() 
        {
            pCount_ = static_cast<unsigned int*>(Loki::SmallObject<>::operator new(sizeof(unsigned int)));
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
				Loki::SmallObject<>::operator delete(pCount_, sizeof(unsigned int));
                return true;
            }
            return false;
        }
        
        void Swap(RefCounted& rhs)
        { std::swap(pCount_, rhs.pCount_); }
    
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
        { std::swap(pCount_, rhs.pCount_); }
    
        enum { destructiveCopy = false };

    private:
        // Data
        unsigned int* pCount_;
    };
    


////////////////////////////////////////////////////////////////////////////////
// class template RefCountedMT
// Implementation of the OwnershipPolicy used by SmartPtr
// Implements external reference counting for multithreaded programs
////////////////////////////////////////////////////////////////////////////////
    template <template <class> class ThreadingModel>
    struct RefCountedMTAdj
    {
		template <class P>
		class NoOwnerRefCountedMT;

        template <class P>
        class RefCountedMT : public ThreadingModel< RefCountedMT<P> >
        {
            typedef ThreadingModel< RefCountedMT<P> > base_type;
            typedef typename base_type::IntType       CountType;
            typedef volatile CountType               *CountPtrType;

        public:
            RefCountedMT() 
            {
                pCount_ = static_cast<CountPtrType>(
					Loki::SmallObject<ThreadingModel>::operator new(
                        sizeof(*pCount_)));
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
			template <typename P1>
			RefCountedMT(const NoOwnerRefCountedMT<P1>& rhs)
			: pCount_(reinterpret_cast<const NoOwnerRefCountedMT<P1>&>(rhs).pCount_)
			{}
            P Clone(const P& val)
            {
                ThreadingModel<RefCountedMT>::AtomicIncrement(*pCount_);
                return val;
            }

            bool Release(const P&, bool = false)
            {
                if (!ThreadingModel<RefCountedMT>::AtomicDecrement(*pCount_))
                {
					Loki::SmallObject<ThreadingModel>::operator delete(
                        const_cast<CountType *>(pCount_), 
                        sizeof(*pCount_));
                    return true;
                }
                return false;
            }

            void Swap(RefCountedMT& rhs)
            { std::swap(pCount_, rhs.pCount_); }

            enum { destructiveCopy = false };

        private:
			friend class NoOwnerRefCountedMT<P>;
            // Data
            CountPtrType pCount_;
        };

		template <class P>
        class NoOwnerRefCountedMT : public ThreadingModel< NoOwnerRefCountedMT<P> >
        {
            typedef ThreadingModel< NoOwnerRefCountedMT<P> > base_type;
            typedef typename base_type::IntType       CountType;
            typedef volatile CountType               *CountPtrType;
        public:

            NoOwnerRefCountedMT(const NoOwnerRefCountedMT& rhs) 
            : pCount_(rhs.pCount_)
            {}

            //MWCW lacks template friends, hence the following kludge
            template <typename P1>
            NoOwnerRefCountedMT(const NoOwnerRefCountedMT<P1>& rhs) 
            : pCount_(reinterpret_cast<const NoOwnerRefCountedMT<P>&>(rhs).pCount_)
            {}
            template <typename P1>
            NoOwnerRefCountedMT(const RefCountedMT<P1>& rhs) 
            : pCount_(reinterpret_cast<const RefCountedMT<P1>&>(rhs).pCount_)
            {}

            P Clone(const P& val)
            {
                return val;
            }

            bool Release(const P&, bool = false)
            {
                return false;
            }

            void Swap(NoOwnerRefCountedMT& rhs)
            { std::swap(pCount_, rhs.pCount_); }

            enum { destructiveCopy = false };

        private:
			friend class RefCountedMT<P>;
            // Data
            CountPtrType pCount_;
        };
    };

};


#endif //__OWNERSHIPPOLICY_H__