/**
 * $ Header: $
 */

#include "system/SyncObject.h"
#include "std/Logger.h"

#include <algorithm>
#include <sstream>

namespace zefiro_system {
	SyncObject::SyncObject():sync_(new Win32Event),syncObjectMutex_(new Mutex()),countOfHasNotified_(0){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::SyncObject()" + toString());
		sync_->reset();
	}
	SyncObject::~SyncObject(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::~SyncObject()" + toString());
		delete sync_;
		delete syncObjectMutex_;
	}
	void SyncObject::notify(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() Begin" + toString());
		syncObjectMutex_->lock();
		if( waitThreads_.size() > 0 ){
			waitThreads_.erase( waitThreads_.begin() );
		}
		++countOfHasNotified_;
		sync_->set();
		syncObjectMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() End" + toString());
	}
	void SyncObject::notifyAll(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() Begin" + toString());
		syncObjectMutex_->lock();
		if( waitThreads_.size() > 0 ){
			countOfHasNotified_ += waitThreads_.size();
			waitThreads_.erase( waitThreads_.begin() , waitThreads_.end() );
		}
		sync_->set();
		syncObjectMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() End" + toString());
	}
	void SyncObject::wait(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() Begin" + toString());
		syncObjectMutex_->lock();
		waitThreads_.push_back( Thread::getCurrentThread() );
		while( waitThreads_.end() != std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
			syncObjectMutex_->unlock();
			sync_->wait();
			syncObjectMutex_->lock();
		}
		--countOfHasNotified_;
		if( countOfHasNotified_ == 0 ){
			sync_->reset();
		}
		syncObjectMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() End" + toString());
	}
	bool SyncObject::wait( int millisecond ){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) Begin" + toString());
		syncObjectMutex_->lock();
		waitThreads_.push_back( Thread::getCurrentThread() );
		while( waitThreads_.end() != std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
			syncObjectMutex_->unlock();
			if( sync_->wait( millisecond ) ){
				syncObjectMutex_->lock();
				return false;
			}
			syncObjectMutex_->lock();
		}
		--countOfHasNotified_;
		if( countOfHasNotified_ == 0 ){
			sync_->reset();
		}
		syncObjectMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) End" + toString());
		return true;
	}
	void SyncObject::lock() {
		syncObjectMutex_->lock();
	}
	void SyncObject::unlock() {
		syncObjectMutex_->unlock();
	}
	std::string SyncObject::toString() const {
		std::ostringstream ostrstr;

		ostrstr << "count of has notified = " << countOfHasNotified_ << " , sync = " << sync_->toString() << " , wait thread size = " << waitThreads_.size(); 

		return ostrstr.str();
	}
};