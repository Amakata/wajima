#include <limits>
#include <stdexcept>
#include <algorithm>
#include <std/unique_number_bad_alloc.h>
#include <std/UniqueNumberFactory.h>

namespace zefiro_std{
	// public 
	UniqueNumberFactory::UniqueNumberFactory( int beginNumber ):_maxUniqueNumber(beginNumber){
	}
	UniqueNumberFactory::~UniqueNumberFactory(){
	}
	int UniqueNumberFactory::createNumber(){
		if( _deletedUniqueNumbers.empty() ){
			if( _maxUniqueNumber == std::numeric_limits<int>::max() ){
				throw zefiro_std::unique_number_bad_alloc();
			}
			return ++_maxUniqueNumber;
		}else{
			int result = _deletedUniqueNumbers.back();
			_deletedUniqueNumbers.pop_back();
			return result;
		}
	}
	void UniqueNumberFactory::deleteNumber( int number ){
		if( isContainedInUsedUniqueNumbers( number ) ){
			throw std::invalid_argument("");
		}
		_deletedUniqueNumbers.push_back( number );
	}
	// protected
	bool UniqueNumberFactory::isContainedInUsedUniqueNumbers( int number ){
		return number > _maxUniqueNumber || isContainedInDeletedUniqueNumbers( number );
	}
	bool UniqueNumberFactory::isContainedInDeletedUniqueNumbers( int number ){
		return _deletedUniqueNumbers.end() != std::find( _deletedUniqueNumbers.begin() , _deletedUniqueNumbers.end() , number );
	}
}