#include <iostream>
#include <fstream>
#include <pss/std/SmartPtr.hpp>
#include <pss/std/WAFInputFileStream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <pss/std/Logger.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char *argv[]) {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");
	// ウィンドウズネームのみ許可
	::boost::filesystem::path test("test", ::boost::filesystem::windows_name);
	::boost::filesystem::path test2 = ::boost::filesystem::complete(test);
	::std::cout << test2.root_path().string() << ::std::endl;
	::std::cout << test2.root_name() << ::std::endl;
	::std::cout << test2.root_directory() << ::std::endl;
	::std::cout << test2.leaf() << ::std::endl;
	::std::cout << test2.string() << ::std::endl;

	::pss::std::basic_waf_filebuf<char> wafbuf;
	::pss::std::basic_waf_ifstream<char> wafstream;
	try {
		wafbuf.open("data/test2.txt");
		::std::basic_istream<char> is(&wafbuf);
		::std::string str = "";
		while (!is.eof()) {
			::std::getline(is, str);
			LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		}
		is.clear();
		is.seekg(0, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.seekg(1, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.seekg(8, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.seekg(9, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.seekg(10, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.clear();
		is.seekg(-11, ::std::ios_base::cur);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		
		wafbuf.close();
		wafstream.open(::boost::filesystem::path("data/test2.txt"));
		wafstream >>  str;
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));		
		wafstream.close();


		::std::basic_ifstream<char> ifs("test.txt");
		while (!ifs.eof()) {
			::std::getline(ifs, str);
			LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		}
		ifs.clear();
		ifs.seekg(0, ::std::ios_base::beg);
		::std::getline(ifs, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		ifs.seekg(8, ::std::ios_base::beg);
		::std::getline(ifs, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		ifs.seekg(9, ::std::ios_base::beg);
		::std::getline(ifs, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		ifs.seekg(10, ::std::ios_base::beg);
		::std::getline(ifs, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
	} catch ( ::boost::filesystem::filesystem_error &e ){
		LOG4CXX_DEBUG(log, e.what());
	}
	LOG4CXX_DEBUG(log, "end.");
	return 0;
}