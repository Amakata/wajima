#pragma once

#include <windows.h>
#include <mmsystem.h>
#include "loki/Singleton.h"
#include "pss/system/ThreadingModel.h"
#include "Win32DebugConsoleStream.hpp"

#pragma comment(lib,"winmm.lib")

// tolua_export
// tolua_begin
namespace pss{
namespace std{
// tolua_end

// タイマーは49日に一回リセットされてしまう。
// したがって、49日以降はこの関数を呼ぶと問題が発生する可能性がある。
class NativeTimer;
typedef Loki::SingletonHolder<NativeTimer,Loki::CreateUsingNew, Loki::DefaultLifetime,pss::system::ClassLevelCountedLockable> SingleNativeTimer;
// tolua_begin
class NativeTimer{
public:
	virtual ~NativeTimer(){
		if( isUseTimeGetTime_ ){
			::timeEndPeriod( timeCaps_.wPeriodMin );
		}
	}
	virtual unsigned int get() const{
		if( isUseTimeGetTime_ ){
			return ::timeGetTime();
		}else{
			return ::GetTickCount();
		}
	}
// tolua_end
protected:
	friend Loki::CreateUsingNew<NativeTimer>;
	NativeTimer(){
		MMRESULT result = timeGetDevCaps(&timeCaps_,sizeof(TIMECAPS));
		if( result != TIMERR_NOERROR ){
			timeCaps_.wPeriodMin = 1;
			isUseTimeGetTime_ = false;
			return;
		}
		if( timeCaps_.wPeriodMin >= 10 ){
			timeCaps_.wPeriodMin = 1;
			isUseTimeGetTime_ = false;
		}else{
			::timeBeginPeriod( timeCaps_.wPeriodMin );
			isUseTimeGetTime_ = true;
		}
	}
private:
	bool isUseTimeGetTime_;
	TIMECAPS timeCaps_;
// tolua_begin
};

class TimerBase{
public:
	virtual ~TimerBase(){
	}
	virtual void reset()=0;
	virtual unsigned int get() const =0;
	virtual void set(unsigned int time) = 0;
	virtual void stop() =0;
	virtual void restart() =0;
};


class Timer : public TimerBase {
public:
	Timer(){
		reset();
	}
	virtual ~Timer(){
	}
	virtual void reset(){
		NativeTimer& timer = SingleNativeTimer::Instance();
		offsetTime_ = timer.get();
		stopCount_ = 0;
	}
	virtual unsigned int get() const{
		NativeTimer& timer = SingleNativeTimer::Instance();
		return timer.get() - offsetTime_;
	}
	virtual void set(unsigned int time){
		NativeTimer& timer = SingleNativeTimer::Instance();
		offsetTime_ = timer.get() - time;
	}
	virtual void stop(){
		if(stopCount_++ == 0){
			NativeTimer& timer = SingleNativeTimer::Instance();
			stopTime_ = timer.get();
		}
	}
	virtual void restart(){
		if(--stopCount_ == 0){
			NativeTimer& timer = SingleNativeTimer::Instance();
			offsetTime_ += timer.get() - stopTime_;
		}
	}
// tolua_end
private:
	unsigned int offsetTime_;
	unsigned int stopTime_;
	unsigned int stopCount_;
// tolua_begin
};

class FixTimer : public TimerBase {
public:
	FixTimer():flushTime_(0){
	}
	virtual ~FixTimer(){
	}
	virtual void reset(){
		timer_.reset();
	}
	virtual unsigned int get() const{
		return flushTime_;
	}
	virtual void set(unsigned int time){
		timer_.set(time);
	}
	virtual void stop(){
		timer_.stop();
	}
	virtual void restart(){
		timer_.restart();
	}
	virtual void flush(){
		flushTime_ = timer_.get();
	}
// tolua_end
private:
	Timer timer_;
	unsigned int flushTime_;
// tolua_begin

};

class FPSTimer : public TimerBase {
public:
	FPSTimer():isSkip_(false),lastDrawTime_(0),frameCount_(1),timeForRealFPS_(0),realFPS_(0),drawCount_(0){
		setFPS(60);
	}
	virtual ~FPSTimer(){
	}
	virtual void setFPS(int fps){
		fps_ = fps;
		fpsWait_ = 1000.0/fps_; // [ms]
	}
	virtual int getFPS()const{
		return fps_;
	}
	virtual int getRealFPS()const{
		return realFPS_;
	}
	virtual void wait(){
		unsigned int currentTime = timer_.get();
		if( currentTime < frameCount_ * fpsWait_ ){
			isSkip_ = false;

//			if( (unsigned int)(frameCount_ * fpsWait_) - currentTime > 15 ){
				::Sleep((unsigned int)(frameCount_ * fpsWait_) - currentTime);
//			}
		}else{
			if( currentTime > 250 + lastDrawTime_ ){
				isSkip_ = false;
			}else{
				isSkip_ = true;
			}
		}
		if( !isSkip_ ){
			++drawCount_;
			lastDrawTime_ = timer_.get();
		}
		++frameCount_;
		if( frameCount_ % 32 == 0 ){
			int currentTime = timer_.get();
			if( currentTime - timeForRealFPS_  != 0 ){
				realFPS_ =  drawCount_ * 1000/ (currentTime - timeForRealFPS_);
			}else{
				realFPS_ = 0;
			}
			drawCount_ = 0;
			timeForRealFPS_ = currentTime;
		}
	}
	virtual bool isSkip()const{
		return isSkip_;
	}
	virtual void reset(){
		timer_.reset();
		lastDrawTime_ = 0;
		frameCount_ = 1;
		timeForRealFPS_ = 0;
		drawCount_ = 0;
		isSkip_ = false;
	}
	virtual unsigned int get() const{
		return timer_.get();
	}
	virtual void set(unsigned int time){
		timer_.set(time);
	}
	virtual void stop(){
		timer_.stop();
	}
	virtual void restart(){
		timer_.restart();
	}
// tolua_end
private:
	Timer timer_;
	double fpsWait_;
	unsigned int frameCount_;
	unsigned int drawCount_;
	unsigned int lastDrawTime_;
	unsigned int timeForRealFPS_;
	int fps_;
	int realFPS_;
	bool isSkip_;
// tolua_begin
};

}
}
// tolua_end
