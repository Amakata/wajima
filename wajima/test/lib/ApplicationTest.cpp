

#include "ApplicationTest.h"

#include "system/Process.h"
#include "std/Logger.h"
#include "Config.h"
#include "ThreadTest.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <stdlib.h>
#include <mmsystem.h>
HWND hWnd__ = 0;

ApplicationTest::ApplicationTest( HWND hWnd ):hWnd_(hWnd){
	hWnd__ = hWnd;
	Config::config__ = new Config("zefirolibtest.ini");
	ostr_.open(Config::config__->getCStr("logfile") );
	zefiro_std::Logger::setOutputter( &ostr_ );
}
ApplicationTest::~ApplicationTest(){
	delete Config::config__;
	ostr_.close();
	zefiro_std::Logger::resetOutputter();
}
void ApplicationTest::testUnit(){
	std::ofstream ofs;
	ofs.open( Config::config__->getCStr("unittestfile") );
	// Create the event manager and test controller
	CppUnit::TestResult controller;
	// Add a listener that colllects test result
	CppUnit::TestResultCollector result;
	controller.addListener( &result );        
	// Add a listener that print dots as test run.
	CppUnit::TextTestProgressListener progress;
	controller.addListener( &progress );      
	// Add the top suite to the test runner
	CppUnit::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );   
	try
	{
		std::cout << "Running ";
		runner.run( controller, "" );
		std::cerr << std::endl;
		// Print test in a compiler compatible format.
		CppUnit::CompilerOutputter outputter( &result, ofs );
		outputter.write();                      
	}
	catch ( std::invalid_argument &e )  // Test path not resolved
	{
		std::cerr	<<  std::endl  
					<<  "ERROR: "  <<  e.what()
					<< std::endl;
		return;
	}
    ofs.close();
	exec( Config::config__->getString("editor") + " " + Config::config__->getString("unittestfile") );
}
void ApplicationTest::testThread(){
	ThreadTest::create( hWnd_ );
	ThreadTest::start();
	exec(Config::config__->getString("editor") + " " + Config::config__->getString("logfile") );
}
void ApplicationTest::testThreadNotify(){
	ThreadTest::notify();
}

void ApplicationTest::exec( std::string cmdLine ){
	zefiro_system::Process *process = new zefiro_system::Process( cmdLine );
	try{
		process->start();
	}catch( zefiro_std::Win32Exception &e ){
		std::string message = std::string(e.what()) + "\n" + cmdLine;
		MessageBox( hWnd_ , message.c_str() , "Error" , MB_OK );
	}
	delete process;
}

