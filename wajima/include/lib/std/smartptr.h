////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// Last update: May 19, 2002

#ifndef smart_ptr_INC_
#define smart_ptr_INC_

#include <algorithm>
#include "typemanip.h"
////////////////////////////////////////////////////////////////////////////////
// IMPORTANT NOTE
// Due to threading issues, the OwnershipPolicy has been changed as follows:
//     Release() returns a boolean saying if that was the last release
//        so the pointer can be deleted by the StoragePolicy
//     IsUnique() was removed
////////////////////////////////////////////////////////////////////////////////

namespace zefiro_std
{

////////////////////////////////////////////////////////////////////////////////
// class template DefaultSPStorage
// Implementation of the StoragePolicy used by smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class DefaultSPStorage
    {
    protected:
        typedef T* StoredType;    // the type of the pointee_ object
        typedef T* PointerType;   // type returned by operator->
        typedef T& ReferenceType; // type returned by operator*
        
    public:
        DefaultSPStorage() : pointee_(Default()) 
        {}

        // The storage policy doesn't initialize the stored pointer 
        //     which will be initialized by the OwnershipPolicy's Clone fn
        DefaultSPStorage(const DefaultSPStorage&)
        {}

        template <class U>
        DefaultSPStorage(const DefaultSPStorage<U>&) 
        {}
        
        DefaultSPStorage(const StoredType& p) : pointee_(p) {}
        
        PointerType operator->() const { return pointee_; }
        
        ReferenceType operator*() const { return *pointee_; }
        
        void Swap(DefaultSPStorage& rhs)
        { std::swap(pointee_, rhs.pointee_); }
    
        // Accessors
        friend inline PointerType GetImpl(const DefaultSPStorage& sp)
        { return sp.pointee_; }
        
        friend inline const StoredType& GetImplRef(const DefaultSPStorage& sp)
        { return sp.pointee_; }

        friend inline StoredType& GetImplRef(DefaultSPStorage& sp)
        { return sp.pointee_; }

    protected:
        // Destroys the data stored
        // (Destruction might be taken over by the OwnershipPolicy)
        void Destroy()
        { delete pointee_; }
        
        // Default value to initialize the pointer
        static StoredType Default()
        { return 0; }
    
    private:
        // Data
        StoredType pointee_;
    };

////////////////////////////////////////////////////////////////////////////////
// class template RefCounted
// Implementation of the OwnershipPolicy used by smart_ptr
// Provides a classic external reference counting implementation
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    class RefCounted
    {
    public:
        RefCounted() 
        {
            pCount_ = new unsigned int;
            // TODO: assert(pCount_);
            *pCount_ = 1;
        }
        
        RefCounted(const RefCounted& rhs) 
        : pCount_(rhs.pCount_)
        {}
        
        // MWCW lacks template friends, hence the following kludge
        template <typename P1>
        RefCounted(const RefCounted<P1>& rhs) 
        : pCount_(reinterpret_cast<const RefCounted&>(rhs).pCount_)
        {}
        
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
        { std::swap(pCount_, rhs.pCount_); }
    
        enum { destructiveCopy = false };

    private:
        // Data
        unsigned int* pCount_;
    };
    

////////////////////////////////////////////////////////////////////////////////
// class template COMRefCounted
// Implementation of the OwnershipPolicy used by smart_ptr
// Adapts COM intrusive reference counting to OwnershipPolicy-specific syntax
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    class COMRefCounted
    {
    public:
        COMRefCounted()
        {}
        
        template <class U>
        COMRefCounted(const COMRefCounted<U>&)
        {}
        
        static P Clone(const P& val)
        {
            val->AddRef();
            return val;
        }
        
        static bool Release(const P& val, bool KP_reject = false)
        { if (!KP_reject) val->Release(); return false; }
        
        enum { destructiveCopy = false };
        
        static void Swap(COMRefCounted&)
        {}
    };

////////////////////////////////////////////////////////////////////////////////
// class template DeepCopy
// Implementation of the OwnershipPolicy used by smart_ptr
// Implements deep copy semantics, assumes existence of a Clone() member 
//     function of the pointee type
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct DeepCopy
    {
        DeepCopy()
        {}
        
        template <class P1>
        DeepCopy(const DeepCopy<P1>&)
        {}
        
        static P Clone(const P& val)
        { return val->Clone(); }
        
        static bool Release(const P&, bool = false)
        { return true; }
        
        static void Swap(DeepCopy&)
        {}
        
        enum { destructiveCopy = false };
    };
    
////////////////////////////////////////////////////////////////////////////////
// class template RefLinked
// Implementation of the OwnershipPolicy used by smart_ptr
// Implements reference linking
////////////////////////////////////////////////////////////////////////////////

    namespace Private
    {
        class RefLinkedBase
        {
        public:
            RefLinkedBase() 
            { prev_ = next_ = this; }
            
            RefLinkedBase(const RefLinkedBase& rhs) 
            {
                prev_ = &rhs;
                next_ = rhs.next_;
                prev_->next_ = this;
                next_->prev_ = this;
            }
            
            bool Release()
            {
                if (next_ == this)
                {   
                    // TODO: assert(prev_ == this);
                    return true;
                }
                prev_->next_ = next_;
                next_->prev_ = prev_;
                return false;
            }
            
            void Swap(RefLinkedBase& rhs)
            {
                if (next_ == this)
                {
                    // TODO: assert(prev_ == this);
                    if (rhs.next_ == &rhs)
                    {
                        // TODO: assert(rhs.prev_ == &rhs);
                        // both lists are empty, nothing 2 do
                        return;
                    }
                    prev_ = rhs.prev_;
                    next_ = rhs.next_;
                    prev_->next_ = next_->prev_ = this;
                    rhs.next_ = rhs.prev_ = &rhs;
                    return;
                }
                if (rhs.next_ == &rhs)
                {
                    rhs.Swap(*this);
                    return;
                }
                std::swap(prev_, rhs.prev_);
                std::swap(next_, rhs.next_);
                std::swap(prev_->next_, rhs.prev_->next_);
                std::swap(next_->prev_, rhs.next_->prev_);
            }
                
            enum { destructiveCopy = false };

        private:
            mutable const RefLinkedBase* prev_;
            mutable const RefLinkedBase* next_;
        };
    }
    
    template <class P>
    class RefLinked : public Private::RefLinkedBase
    {
    public:
        RefLinked()
        {}
        
        template <class P1>
        RefLinked(const RefLinked<P1>& rhs) 
        : Private::RefLinkedBase(rhs)
        {}

        static P Clone(const P& val)
        { return val; }

        bool Release(const P&, bool = false)
        { return Private::RefLinkedBase::Release(); }
    };
    
////////////////////////////////////////////////////////////////////////////////
// class template DestructiveCopy
// Implementation of the OwnershipPolicy used by smart_ptr
// Implements destructive copy semantics (a la std::auto_ptr)
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    class DestructiveCopy
    {
    public:
        DestructiveCopy()
        {}
        
        template <class P1>
        DestructiveCopy(const DestructiveCopy<P1>&)
        {}
        
        template <class P1>
        static P Clone(P1& val)
        {
            P result(val);
            val = P1();
            return result;
        }
        
        static bool Release(const P&, bool = false)
        { return true; }
        
        static void Swap(DestructiveCopy&)
        {}
        
        enum { destructiveCopy = true };
    };
    
////////////////////////////////////////////////////////////////////////////////
// class template NoCopy
// Implementation of the OwnershipPolicy used by smart_ptr
// Implements a policy that doesn't allow copying objects
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    class NoCopy
    {
    public:
        NoCopy()
        {}
        
        template <class P1>
        NoCopy(const NoCopy<P1>&)
        {}
        
        static P Clone(const P&)
        {
            // TODO: STATIC_CHECK(false, This_Policy_Disallows_Value_Copying);
        }
        
        static bool Release(const P&, bool = false)
        { return true; }
        
        static void Swap(NoCopy&)
        {}
        
        enum { destructiveCopy = false };
    };
    
////////////////////////////////////////////////////////////////////////////////
// class template AllowConversion
// Implementation of the ConversionPolicy used by smart_ptr
// Allows implicit conversion from smart_ptr to the pointee type
////////////////////////////////////////////////////////////////////////////////

    struct AllowConversion
    {
        enum { allow = true };

        void Swap(AllowConversion&)
        {}
    };

////////////////////////////////////////////////////////////////////////////////
// class template DisallowConversion
// Implementation of the ConversionPolicy used by smart_ptr
// Does not allow implicit conversion from smart_ptr to the pointee type
// You can initialize a DisallowConversion with an AllowConversion
////////////////////////////////////////////////////////////////////////////////

    struct DisallowConversion
    {
        DisallowConversion()
        {}
        
        DisallowConversion(const AllowConversion&)
        {}
        
        enum { allow = false };

        void Swap(DisallowConversion&)
        {}
    };

////////////////////////////////////////////////////////////////////////////////
// class template NoCheck
// Implementation of the CheckingPolicy used by smart_ptr
// Well, it's clear what it does :o)
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct NoCheck
    {
        NoCheck()
        {}
        
        template <class P1>
        NoCheck(const NoCheck<P1>&)
        {}
        
        static void OnDefault(const P&)
        {}

        static void OnInit(const P&)
        {}

        static void OnDereference(const P&)
        {}

        static void Swap(NoCheck&)
        {}
    };


////////////////////////////////////////////////////////////////////////////////
// class template AssertCheck
// Implementation of the CheckingPolicy used by smart_ptr
// Checks the pointer before dereference
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct AssertCheck
    {
        AssertCheck()
        {}
        
        template <class P1>
        AssertCheck(const AssertCheck<P1>&)
        {}
        
        template <class P1>
        AssertCheck(const NoCheck<P1>&)
        {}
        
        static void OnDefault(const P&)
        {}

        static void OnInit(const P&)
        {}

        static void OnDereference(P val)
        { //TODO: assert(val); (void)val; 
		}

        static void Swap(AssertCheck&)
        {}
    };

////////////////////////////////////////////////////////////////////////////////
// class template AssertCheckStrict
// Implementation of the CheckingPolicy used by smart_ptr
// Checks the pointer against zero upon initialization and before dereference
// You can initialize an AssertCheckStrict with an AssertCheck 
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct AssertCheckStrict
    {
        AssertCheckStrict()
        {}
        
        template <class U>
        AssertCheckStrict(const AssertCheckStrict<U>&)
        {}
        
        template <class U>
        AssertCheckStrict(const AssertCheck<U>&)
        {}
        
        template <class P1>
        AssertCheckStrict(const NoCheck<P1>&)
        {}
        
        static void OnDefault(P val)
        { //TODO: assert(val);
		}
        
        static void OnInit(P val)
        { //TODO: assert(val); 
		}
        
        static void OnDereference(P val)
        { //TODO: assert(val);
		}
        
        static void Swap(AssertCheckStrict&)
        {}
    };
       
////////////////////////////////////////////////////////////////////////////////
// class template RejectNullStatic
// Implementation of the CheckingPolicy used by smart_ptr
// Checks the pointer upon initialization and before dereference
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct RejectNullStatic
    {
        RejectNullStatic()
        {}
        
        template <class P1>
        RejectNullStatic(const RejectNullStatic<P1>&)
        {}
        
        template <class P1>
        RejectNullStatic(const NoCheck<P1>&)
        {}
        
        template <class P1>
        RejectNullStatic(const AssertCheck<P1>&)
        {}
        
        template <class P1>
        RejectNullStatic(const AssertCheckStrict<P1>&)
        {}
        
        static void OnDefault(const P&)
        {
            // TODO: STATIC_CHECK(false, This_Policy_Does_Not_Allow_Default_Initialization);
        }
        
        static void OnInit(const P& val)
		{ 
			if (!val){
			// TODO: throw NullPointerException();
			}
		}
        
        static void OnDereference(const P& val)
        { 
			if (!val){
			//TODO: throw NullPointerException();
			}
		}
        
        static void Swap(RejectNullStatic&)
        {}
    };

////////////////////////////////////////////////////////////////////////////////
// class template RejectNull
// Implementation of the CheckingPolicy used by smart_ptr
// Checks the pointer before dereference
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct RejectNull
    {
        RejectNull()
        {}
        
        template <class P1>
        RejectNull(const RejectNull<P1>&)
        {}
        
        static void OnInit(P val)
        { 
			if (!val){
				// TODO: throw NullPointerException();
			}
		}

        static void OnDefault(P val)
        { OnInit(val); }
        
        void OnDereference(P val)
        { OnInit(val); }
        
        void Swap(RejectNull&)
        {}        
    };

////////////////////////////////////////////////////////////////////////////////
// class template RejectNullStrict
// Implementation of the CheckingPolicy used by smart_ptr
// Checks the pointer upon initialization and before dereference
////////////////////////////////////////////////////////////////////////////////

    template <class P>
    struct RejectNullStrict
    {
        RejectNullStrict()
        {}
        
        template <class P1>
        RejectNullStrict(const RejectNullStrict<P1>&)
        {}
        
        template <class P1>
        RejectNullStrict(const RejectNull<P1>&)
        {}
        
        static void OnInit(P val)
        {
			if (!val){
				// TODO: throw NullPointerException();
			}
		}

        void OnDereference(P val)
        { OnInit(val); }
        
        void Swap(RejectNullStrict&)
        {}        
    };

////////////////////////////////////////////////////////////////////////////////
// class template ByRef
// Transports a reference as a value
// Serves to implement the Colvin/Gibbons trick for smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class ByRef
    {
    public:
        ByRef(T& v) : value_(v) {}
        operator T&() { return value_; }
        // gcc doesn't like this:
        operator const T&() const { return value_; }

    private:
        ByRef(const ByRef &);
        ByRef& operator=(const ByRef &);

        T& value_;
    };


////////////////////////////////////////////////////////////////////////////////
// class template WrapTemplate (definition)
// suggested workaround for vc7 limitation with template template arguments
////////////////////////////////////////////////////////////////////////////////
template<template<typename> class C>
struct WrapTemplate
{
    template<typename T>
    struct In
    {
        typedef C<T> type;
    };

    // VC7 BUG - cannot access protected typedef
    template<typename T>
    struct PointerType : private C<T>
    {
        typedef typename C<T>::PointerType type;
    };

    // VC7 BUG - cannot access protected typedef
    template<typename T>
    struct StoredType : private C<T>
    {
        typedef typename C<T>::StoredType type;
    };
};

////////////////////////////////////////////////////////////////////////////////
// class template smart_ptr (declaration)
// The reason for all the fuss above
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OwnershipPolicy = WrapTemplate<RefCounted>,
        class ConversionPolicy = DisallowConversion,
        class CheckingPolicy = WrapTemplate<AssertCheck>,
        class StoragePolicy = WrapTemplate<DefaultSPStorage>
    >
    class smart_ptr;

////////////////////////////////////////////////////////////////////////////////
// class template smart_ptr_def (definition)
// this class added to adjust the ported smart_ptr to the original one.
// instead of writing smart_ptr<T,OP,CP,KP,SP> write smart_ptr_def<T,OP,CP,KP,SP>::type
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        template <class> class OwnershipPolicy = RefCounted,
        class ConversionPolicy = DisallowConversion,
        template <class> class CheckingPolicy = AssertCheck,
        template <class> class StoragePolicy = DefaultSPStorage
    >
    struct smart_ptr_def
    {
        typedef smart_ptr
        <
            T,
            WrapTemplate<OwnershipPolicy>,
            ConversionPolicy,
            WrapTemplate<CheckingPolicy>,
            WrapTemplate<StoragePolicy>
        >
        type;
    };

////////////////////////////////////////////////////////////////////////////////
// class template smart_ptr (definition)
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OwnershipPolicy,
        class ConversionPolicy,
        class CheckingPolicy,
        class StoragePolicy
    >
    class smart_ptr
        : public StoragePolicy::In<T>::type
        , public OwnershipPolicy::In<typename StoragePolicy::template PointerType<T>::type>::type
        , public CheckingPolicy ::In<typename StoragePolicy::template StoredType<T>::type>::type
        , public ConversionPolicy
    {
        typedef typename StoragePolicy::template In<T>::type SP;
        typedef typename OwnershipPolicy::template In<typename SP::PointerType>::type OP;
        typedef typename CheckingPolicy::template  In<typename SP::StoredType>::type  KP;
        typedef ConversionPolicy CP;
        
        // VC7 bug
        enum { OP_destructiveCopy = OP::destructiveCopy };
        enum { CP_allow = CP::allow };

    public:
        typedef typename SP::PointerType PointerType;
        typedef typename SP::StoredType StoredType;
        typedef typename SP::ReferenceType ReferenceType;
        

        typedef typename Select<OP_destructiveCopy, smart_ptr, const smart_ptr >::Result CopyArg;
    
   private:
        void OnKPReject()
        {
            if (OP::Release(GetImpl(*static_cast<SP*>(this)), true))
            {
                // if KP::IsDestructive(GetImpl(*this))
                // call SP::Destroy() ?
            }
        }

        class smart_ptrGuard
        {
        public:
            typedef void (smart_ptr::*action_t)();

            smart_ptrGuard(smart_ptr &sptr, action_t action)
                : sptr_(sptr), action_(action), guard_(true)
            {}

            void Dismiss() { guard_ = false; }

            ~smart_ptrGuard()
            { if (guard_) (sptr_.*action_)(); }

        private:
            smart_ptrGuard(const smart_ptrGuard &);
            smart_ptrGuard& operator=(const smart_ptrGuard &);

        private:
            smart_ptr    &sptr_;
            action_t    action_;
            bool        guard_;
        };

    public:

        smart_ptr()
        { 
            smart_ptrGuard KPGuard(*this, &smart_ptr::OnKPReject);
            KP::OnDefault(GetImpl(*this)); 
            KPGuard.Dismiss();
        }
        
        //
        // This constructor has exception safety problem
        // If OP constructor throw - p might be leaked
        // One solution is to add method to OP named OnInit with the following usage:
        // OP::OnInit(GetImpl(*this), implicit_cast<SP&>(*this)); 
        // The OP default constructor will have no throw guaranty 
        // and the OP::OnInit will decide if destroy should be invoked upon exception
        //
        smart_ptr(const StoredType& p) : SP(p)
        { 
            //
            // The following try catch only solve part of the exception safety problem.
            // The solution might be wrong because KP might reject illegal pointers (not destructible via destroy like null com pointer).
            // The complete solution might involve more tight connections between KP, OP and SP.
            //
            smart_ptrGuard KPGuard(*this, &smart_ptr::OnKPReject);
            KP::OnInit(GetImpl(*this)); 
            KPGuard.Dismiss();
        }
        
        smart_ptr(CopyArg& rhs)
        : SP(rhs), OP(rhs), KP(rhs), CP(rhs)
        { GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); }

        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        smart_ptr(const smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs)
        : SP(rhs), OP(rhs), KP(rhs), CP(rhs)
        { GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); }

        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        smart_ptr(smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs)
        : SP(rhs), OP(rhs), KP(rhs), CP(rhs)
        { GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); }

        smart_ptr(ByRef<smart_ptr> rhs)
        : SP(rhs), OP(rhs), KP(rhs), CP(rhs)
        {}
        
        operator ByRef<smart_ptr>()
        { return ByRef<smart_ptr>(*this); }

        smart_ptr& operator=(CopyArg& rhs)
        {
            smart_ptr temp(rhs);
            temp.Swap(*this);
            return *this;
        }

        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        smart_ptr& operator=(const smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs)
        {
            smart_ptr temp(rhs);
            temp.Swap(*this);
            return *this;
        }
        
        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        smart_ptr& operator=(smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs)
        {
            smart_ptr temp(rhs);
            temp.Swap(*this);
            return *this;
        }
        
        void Swap(smart_ptr& rhs)
        {
            OP::Swap(rhs);
            CP::Swap(rhs);
            KP::Swap(rhs);
            SP::Swap(rhs);
        }
        
        ~smart_ptr()
        {
            if (OP::Release(GetImpl(*static_cast<SP*>(this))))
            {
                SP::Destroy();
            }
        }
        
        friend inline void Release(smart_ptr& sp, typename SP::StoredType& p)
        {
            p = GetImplRef(sp);
            GetImplRef(sp) = SP::Default();
        }
        
        friend inline void Reset(smart_ptr& sp, typename SP::StoredType p)
        { smart_ptr(p).Swap(sp); }

        PointerType operator->()
        {
            KP::OnDereference(GetImplRef(*this));
            return SP::operator->();
        }

        PointerType operator->() const
        {
            KP::OnDereference(GetImplRef(*this));
            return SP::operator->();
        }

        ReferenceType operator*()
        {
            KP::OnDereference(GetImplRef(*this));
            return SP::operator*();
        }
        
        ReferenceType operator*() const
        {
            KP::OnDereference(GetImplRef(*this));
            return SP::operator*();
        }
        
        bool operator!() const // Enables "if (!sp) ..."
        { return GetImpl(*this) == 0; }
        
        inline friend bool operator==(const smart_ptr& lhs,
            const T* rhs)
        { return GetImpl(lhs) == rhs; }
        
        inline friend bool operator==(const T* lhs,
            const smart_ptr& rhs)
        { return rhs == lhs; }
        
        inline friend bool operator!=(const smart_ptr& lhs,
            const T* rhs)
        { return !(lhs == rhs); }
        
        inline friend bool operator!=(const T* lhs,
            const smart_ptr& rhs)
        { return rhs != lhs; }

        // Ambiguity buster
        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        bool operator==(const smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs) const
        { return *this == GetImpl(rhs); }

        // Ambiguity buster
        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        bool operator!=(const smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs) const
        { return !(*this == rhs); }

        // Ambiguity buster
        template
        <
            typename T1,
            class OP1,
            class CP1,
            class KP1,
            class SP1
        >
        bool operator<(const smart_ptr<T1, OP1, CP1, KP1, SP1>& rhs) const
        { return *this < GetImpl(rhs); }

    private:
        // Helper for enabling 'if (sp)'
        struct Tester
        {
            Tester() {}
        private:
            void operator delete(void*);
        };
        
    public:
        // enable 'if (sp)'
        operator const volatile Tester*() const
        {
            if (!*this) return 0;
            static Tester t;
            return &t;
        }

    private:
        // Helper for disallowing automatic conversion
        struct Insipid
        {
            Insipid(PointerType) {}
        };
        

        typedef typename Select<CP_allow, PointerType, Insipid>::Result
            AutomaticConversionResult;
    
    public:        
        operator AutomaticConversionResult() const
        { return GetImpl(*this); }
    };

////////////////////////////////////////////////////////////////////////////////
// free comparison operators for class template smart_ptr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// operator== for lhs = smart_ptr, rhs = raw pointer
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator==(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs)
    { return GetImpl(lhs) == rhs; }
    
////////////////////////////////////////////////////////////////////////////////
// operator== for lhs = raw pointer, rhs = smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator==(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs)
    { return rhs == lhs; }

////////////////////////////////////////////////////////////////////////////////
// operator!= for lhs = smart_ptr, rhs = raw pointer
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator!=(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs)
    { return !(lhs == rhs); }
    
////////////////////////////////////////////////////////////////////////////////
// operator!= for lhs = raw pointer, rhs = smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator!=(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs)
    { return rhs != lhs; }

////////////////////////////////////////////////////////////////////////////////
// operator< for lhs = smart_ptr, rhs = raw pointer -- NOT DEFINED
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator<(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs);
        
////////////////////////////////////////////////////////////////////////////////
// operator< for lhs = raw pointer, rhs = smart_ptr -- NOT DEFINED
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator<(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs);
        
////////////////////////////////////////////////////////////////////////////////
// operator> for lhs = smart_ptr, rhs = raw pointer -- NOT DEFINED
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator>(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs)
    { return rhs < lhs; }
        
////////////////////////////////////////////////////////////////////////////////
// operator> for lhs = raw pointer, rhs = smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator>(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs)
    { return rhs < lhs; }
  
////////////////////////////////////////////////////////////////////////////////
// operator<= for lhs = smart_ptr, rhs = raw pointer
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator<=(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs)
    { return !(rhs < lhs); }
        
////////////////////////////////////////////////////////////////////////////////
// operator<= for lhs = raw pointer, rhs = smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator<=(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs)
    { return !(rhs < lhs); }

////////////////////////////////////////////////////////////////////////////////
// operator>= for lhs = smart_ptr, rhs = raw pointer
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator>=(const smart_ptr<T, OP, CP, KP, SP>& lhs,
        const U* rhs)
    { return !(lhs < rhs); }
        
////////////////////////////////////////////////////////////////////////////////
// operator>= for lhs = raw pointer, rhs = smart_ptr
////////////////////////////////////////////////////////////////////////////////

    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP,
        typename U
    >
    inline bool operator>=(const U* lhs,
        const smart_ptr<T, OP, CP, KP, SP>& rhs)
    { return !(lhs < rhs); }

} // namespace Loki

////////////////////////////////////////////////////////////////////////////////
// specialization of std::less for smart_ptr
////////////////////////////////////////////////////////////////////////////////
#if 0
namespace std
{
    template
    <
        typename T,
        class OP,
        class CP,
        class KP,
        class SP
    >
    struct less< Loki::smart_ptr<T, OP, CP, KP, SP> >
        : public binary_function<Loki::smart_ptr<T, OP, CP, KP, SP>,
            Loki::smart_ptr<T, OP, CP, KP, SP>, bool>
    {
        bool operator()(const Loki::smart_ptr<T, OP, CP, KP, SP>& lhs,
            const Loki::smart_ptr<T, OP, CP, KP, SP>& rhs) const
        { return less<T*>()(GetImpl(lhs), GetImpl(rhs)); }
    };
}
#endif
////////////////////////////////////////////////////////////////////////////////
// Change log:
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
// May  10, 2002: ported by Rani Sharoni to VC7 (RTM - 9466)
////////////////////////////////////////////////////////////////////////////////

#endif // smart_ptr_INC_
