#ifndef __Config__H__
#define __Config__H__

#include <windows.h>
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
	static HWND getHWND(){
		return hwnd__;
	}
	static void setHWND( HWND hwnd ){
		hwnd__ = hwnd;
	}
protected:
	static HWND hwnd__;
	std::map< std::string , std::string > param_;
	std::ofstream	logfile_;
};

#endif //__Config__H__