#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <map>
#include <string>

class Config {
public:
	Config( std::string configFilePath ){
		std::ifstream ifs;
		std::string name;
		std::string value;

		ifs.open( configFilePath.c_str() );
		while( !ifs.eof() ){
			ifs >> name >> value;
			config_.insert( std::pair<std::string,std::string>( name , value ) );
		}
		ifs.close();
	}
	std::string getString( std::string key ){
		return config_[key];
	}
	const char *getCStr( std::string key ){
		return config_[key].c_str();
	}
protected:
	std::map< std::string , std::string > config_;
};

#endif //__CONFIG_H__