#include <iostream>
#include <pss/std/SmartPtr.hpp>
#include <pss/std/WAFInputFileStream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

int main(int argc, char *argv[]) {

	// ウィンドウズネームのみ許可
	::boost::filesystem::path test("test", ::boost::filesystem::windows_name);
	::boost::filesystem::path test2 = ::boost::filesystem::complete(test);
	::std::cout << test2.root_path().string() << ::std::endl;
	::std::cout << test2.root_name() << ::std::endl;
	::std::cout << test2.root_directory() << ::std::endl;
	::std::cout << test2.leaf() << ::std::endl;
	::std::cout << test2.string() << ::std::endl;
	::pss::std::basic_waf_filebuf<char> WAFStreamBuf;

	return 0;
}