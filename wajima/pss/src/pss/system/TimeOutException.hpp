#pragma once

#include "pss/std/Exception.hpp"


namespace pss {
	namespace system {
		class TimeOutException  : public ::pss::std::Exception{
		public:
#if 0
			TimeOutException ();
#endif
// tolua_end
			TimeOutException ()throw() :Exception(){
			}
// tolua_begin
			virtual ~TimeOutException (){
			}
		};
	}
}

