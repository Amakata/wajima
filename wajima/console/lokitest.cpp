#include <iostream>
#include <fstream>
#include <pss/std/SmartPtr.hpp>
#include <pss/std/WAFInputFileStream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <pss/std/Logger.hpp>
#include <boost/lexical_cast.hpp>

/**
 * wafbuf、wafstraem、ifstreamの動作チェック
 */
int test(int argc, char *argv[]) {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");
	// ウィンドウズネームのみ許可
	::boost::filesystem::path test("test", ::boost::filesystem::windows_name);
	::boost::filesystem::path test2 = ::boost::filesystem::complete(test);
	// pathの各種メソッドテスト
	::std::cout << test2.root_path().string() << ::std::endl;
	::std::cout << test2.root_name() << ::std::endl;
	::std::cout << test2.root_directory() << ::std::endl;
	::std::cout << test2.leaf() << ::std::endl;
	::std::cout << test2.string() << ::std::endl;
	
	// waf用読み取りファイルバッファ
	::pss::std::basic_waf_filebuf<char> wafbuf;
	// waf入力ストリーム
	::pss::std::basic_waf_ifstream<char> wafstream;
	try {
		//
		// wafbufの動作を試す
		//
		// data.wafのtest2.txtをオープン
		wafbuf.open("data/test2.txt");
		// wafバッファを作成
		::std::basic_istream<char> is(&wafbuf);

		// 一行ずつ読み取り
		::std::string str = "";
		while (!is.eof()) {
			::std::getline(is, str);
			LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		}
		// クリア
		is.clear();
		// 先頭へシーク
		is.seekg(0, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// 先頭から１バイトシーク
		is.seekg(1, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// 先頭から８バイトシーク
		is.seekg(8, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// 先頭から９バイトシーク
		is.seekg(9, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// 先頭から１０バイトシーク
		is.seekg(10, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.clear();
		// 現在位置から-11バイトシーク
		is.seekg(-11, ::std::ios_base::cur);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		
		wafbuf.close();

		//
		// wafstreamの動作を試す
		//
		// data.wafのtest2.txtをオープン
		wafstream.open(::boost::filesystem::path("data/test2.txt"));
		wafstream >>  str;
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));		
		wafstream.close();

		//
		//　ifstreamでwafbufのストリームと同じ動作をするか検証する
		//
		// test.txtをオープン
		::std::basic_ifstream<char> ifs("test.txt");
		// 一行ずつ読み込み
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

int main(int argc, char* argv[]) {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");
	::pss::std::basic_waf_ifstream<char> ws1,ws2;
	ws1.open("data/hogehoge.txt");
	ws1.seekg(0, ::std::io_base::end);
	int size1 = ws1.tellg();
	LOG4CXX_DEBUG(log, "size1 = " + ::boost::lexical_cast<::std::string>(size1));
	::std::ofstream ofs("hogehoge.txt", ::std::ios_base::out | ::std::ios_base::binary);
	for (int i = 0; i < size1 ; ++i) {
		char buf;
		ws1.read(&buf, 1);
		ofs.write(&buf, 1);
	}
	ws1.close();


	LOG4CXX_DEBUG(log, "end.");
}