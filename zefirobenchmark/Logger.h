#pragma once

#include <dinput.h>

#define DXERROR_LOG( hr )	Logger::d3dlogging( hr , __FILE__ , __LINE__ )
#define DXIERROR_LOG( hr )	Logger::dilogging( hr , __FILE__ , __LINE__ )

class Logger {
public:
	static void d3dlogging( HRESULT hr , std::string file , int line ){
		if( hr != D3D_OK ){
			std::ofstream ofs;
			ofs.open("zefirobenchmarkoutput.txt",std::ios_base::out | std::ios_base::app );
			ofs << file <<":"<< line <<":"<< hr << std::endl;
			ofs.close();
		}
	}
	static void dilogging( HRESULT hr , std::string file , int line ){
		if( hr != DI_OK ){
			std::ofstream ofs;
			ofs.open("zefirobenchmarkoutput.txt",std::ios_base::out | std::ios_base::app );
			ofs << file <<":"<< line <<":"<< hr << std::endl;
			ofs.close();
		}
	}
};
