#ifndef __Config__H__
#define __Config__H__

#include <fstream>
#include <sstream>
#include <map>
#include <ios>
#include <string>

class Config {
public:
	static Config *Config::config__;
	Config( std::string configFilePath );
	virtual ~Config();
	std::string getString( std::string key );
	const char *getCStr( std::string key );
	int getInteger( std::string key );
	double getDouble( std::string key );
	bool getBool( std::string key );

protected:
	std::map< std::string , std::string > param_;
	std::ofstream	logfile_;
};

#endif //__Config__H__