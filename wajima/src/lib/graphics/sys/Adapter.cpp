#include <sstream>

#include <graphics/sys/Adapter.h>

namespace zefiro_graphics {
	Adapter::Adapter( const int adapterNumber , const std::string name ):_adapterNumber(adapterNumber),_name(name){
	}
	Adapter::~Adapter(){
	}
	std::string Adapter::getName() const{
		return _name;
	}
	int Adapter::getAdapterNumber() const{
		return _adapterNumber;
	}
	void Adapter::addMode( Mode mode ){
		_modes.push_back( mode );
	}
	std::vector<Mode> Adapter::getModeVector() const{
		return _modes;
	}
	std::string Adapter::toString() const{
		std::ostringstream result;
		std::vector<Mode> modes = _modes;

		result << _name << std::endl;
		for( std::vector<Mode>::iterator mode = modes.begin() ; mode < modes.end() ; ++mode ){
			result << mode->toString() << std::endl;
		}
		return result.str();
	}
};