/**
 * $ Header: $
 */

#include "SyncObject.h"
#include "std/Logger.h"
#include "std/Assert.h"

#include <algorithm>
#include <sstream>

namespace zefiro_system {
	SyncObject::SyncObject():
		waitSync_(new Win32Event),waitMutex_(new Mutex()),
		monitorSync_(new Win32Event()),monitorMutex_(new Mutex()),monitorOwnerID_(Thread::NULLTHREAD),
		countOfMonitorLock_(0),countOfMonitorLockWait_(0){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::SyncObject()" + toString());
		waitSync_->reset();
		monitorSync_->reset();
	}
	SyncObject::~SyncObject(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::~SyncObject()" + toString());
		delete waitSync_;
		delete monitorSync_;
		delete waitMutex_;
		delete monitorMutex_;
	}
	void SyncObject::notify(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() Begin" + toString());
		waitMutex_->lock();
		if( waitThreads_.size() > 0 ){
			waitThreads_.erase( waitThreads_.begin() );
			waitSync_->set();
		}
		waitMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() End" + toString());
	}
	void SyncObject::notifyAll(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() Begin" + toString());
		waitMutex_->lock();
		if( waitThreads_.size() > 0 ){
			waitThreads_.erase( waitThreads_.begin() , waitThreads_.end() );
			waitMutex_->unlock();
			waitSync_->set();
		}
		waitMutex_->unlock();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() End" + toString());
	}
	void SyncObject::wait(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() Begin" + toString());
		waitMutex_->lock();
		int countOfMonitorLock = countOfMonitorLock_;
		for( int count=0 ; count<countOfMonitorLock ; ++count ){
			this->unlock();
		}
		doWait();
		waitMutex_->unlock();
		this->lock();
		countOfMonitorLock_ = countOfMonitorLock;
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() End" + toString());
	}
	bool SyncObject::wait( int millisecond ){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) Begin" + toString());
		waitMutex_->lock();
		int countOfMonitorLock = countOfMonitorLock_;
		for( int count=0 ; count<countOfMonitorLock ; ++count ){
			this->unlock();
		}
		bool result = doWait( millisecond );
		waitMutex_->unlock();
		this->lock();
		countOfMonitorLock_ = countOfMonitorLock;
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) End" + toString());
		return result;
	}
	void SyncObject::lock() {
		int currentThreadID = Thread::getCurrentThreadID();
		monitorMutex_->lock();
		if( monitorOwnerID_ == currentThreadID ){	//	現在のスレッドがモニターロックの所有者なら、ロックカウントを増やす。
			++countOfMonitorLock_;
		}else{
			while( monitorOwnerID_ != Thread::NULLTHREAD ){	//	ロックが誰かに所有されている間、待つ
				++countOfMonitorLockWait_;
				monitorMutex_->unlock();
				monitorSync_->wait();
				monitorMutex_->lock();
			}
			monitorOwnerID_ = currentThreadID;	//	モニターロックの所有者を現在のスレッドにする。
			countOfMonitorLock_ = 1;			//	ロックカウントを1にする。
		}
		monitorMutex_->unlock();
	}
	void SyncObject::unlock() {
		int currentThreadID = Thread::getCurrentThreadID();
		monitorMutex_->lock();
		ZEFIRO_STD_ASSERT_EQUAL( currentThreadID , monitorOwnerID_ );	//	自分のスレッド以外のlockを解除したら例外を発生する。
		--countOfMonitorLock_;
		if( countOfMonitorLock_ == 0 ){	//	ロックが0なら、モニターロックの所有者をなしにする。
			monitorOwnerID_ = Thread::NULLTHREAD;
			if( countOfMonitorLockWait_ > 0 ){	//	誰かロックを待っているなら、waitをなくす。
				--countOfMonitorLockWait_;
				monitorMutex_->unlock();
				monitorSync_->pulse();
				return;
			}
		}
		monitorMutex_->unlock();
	}
	std::string SyncObject::toString() const {
		std::ostringstream ostrstr;

		ostrstr << " ( wait mutex = " << waitMutex_ << " , wait sync = " << waitSync_->toString() << 
					" , monitor owner id = " << monitorOwnerID_ << " , count of monitor lock = " <<  countOfMonitorLock_ << " , count of monitor lock wait = " << countOfMonitorLockWait_ <<
					" , monitor mutex = " << monitorMutex_ << " , monitor sync = "  << monitorSync_->toString() << 
					" , wait thread size = " << waitThreads_.size() << " ) "; 

		return ostrstr.str();
	}
	bool SyncObject::doWait( int millisecond ){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::doWait() Begin" + toString());
		waitThreads_.push_back( Thread::getCurrentThread() );
		while( waitThreads_.end() != std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
			waitMutex_->unlock();
			if( !waitSync_->wait( millisecond ) ){
				waitMutex_->lock();
				return false;
			}
			waitMutex_->lock();
		}
		waitSync_->reset();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::doWait() End" + toString());
		return true;
	}
};