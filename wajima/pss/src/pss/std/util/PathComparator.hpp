#pragma once

#include <boost/filesystem/path.hpp>

namespace pss{
	namespace std{
		namespace util{
			struct PathComparator{
				bool operator()( const ::boost::filesystem::path& l, const ::boost::filesystem::path& r ) const{
					return l.string().compare( r.string() ) < 0;
				}
			};
		}
	}
}