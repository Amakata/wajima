/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Attic/StoragePolicy.h,v 1.1 2002/11/20 23:12:34 ama Exp $
 */
#ifndef __STORAGEPOLICY_H__
#define __STORAGEPOLICY_H__

namespace zefiro_std{
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
        { delete pointee_; pointee_ = NULL; }
        
        // Default value to initialize the pointer
        static StoredType Default()
        { return 0; }
    
    private:
        // Data
        StoredType pointee_;
    };
};
#endif //__STORAGEPOLICY_H__