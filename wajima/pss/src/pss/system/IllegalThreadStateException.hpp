#pragma once

#include "pss/std/Exception.hpp"

namespace pss {
	namespace system {
		class IllegalThreadStateException  : public ::pss::std::Exception{
		public:
#if 0
			IllegalThreadStateException ();
#endif
// tolua_end
			IllegalThreadStateException () throw() :Exception(){
			}
// tolua_begin
			virtual ~IllegalThreadStateException (){
			}
		};
	}
}
