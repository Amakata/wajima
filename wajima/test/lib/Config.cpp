/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/lib/Config.cpp,v 1.2 2002/11/13 18:24:01 ama Exp $
 */
#include "Config.h"

Config * Config::config__;

Config::Config( std::string configFilePath ){
	std::ifstream ifs;
	std::string name;
	std::string value;

	ifs.open( configFilePath.c_str() );
	while( !ifs.eof() ){
		ifs >> name >> value;
		Config::param_.insert( std::pair<std::string,std::string>( name , value ) );
	}
	ifs.close();
	logfile_.open( "Config.log");
	logfile_.setf( std::ios_base::boolalpha );
}
Config::~Config(){
	logfile_.close();
}
std::string Config::getString( std::string key ){
	logfile_ << "key = " << key << " , value = " << param_[key]<< std::endl;
	return param_[key];
}
const char *Config::getCStr( std::string key ){
	logfile_ << "key = " << key << " , value = " << param_[key].c_str()<< std::endl;
	return param_[key].c_str();
}
int Config::getInteger( std::string key ){
	std::istringstream istr(param_[key]) ;
	int result;
	istr >> result;
	logfile_ << "key = " << key << " , value = " << result<< std::endl;
	return result;
}
double Config::getDouble( std::string key ){
	std::istringstream istr(param_[key]) ;
	double result;
	istr >> result;
	logfile_ << "key = " << key << " , value = " << result<< std::endl;
	return result;
}
bool Config::getBool( std::string key ){
	std::istringstream istr(param_[key]) ;
	bool result;
	istr.setf(std::ios_base::boolalpha);
	istr >> result;
	logfile_ << "key = " << key << " , value = " << result << std::endl;
	return result;
}
HWND Config::hwnd__ = 0;