#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <exception>
#include <boost/filesystem/path.hpp>
#include <pss/std/WAFInputFileStream.hpp>
#include <pss/std/Logger.hpp>
#include <boost/lexical_cast.hpp>


/**
 * @param propertyFilePathStr WAFアーカイブファイルを作成するプロパティファイル
 * @return 0 正常
 *         -1 失敗
 */
int doArchive(const ::std::string &propertyFilePathStr) {
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("doArchive");
	LOG4CXX_DEBUG(log, "begin.");
	::std::ifstream ifs(propertyFilePathStr.c_str());

	if (ifs.eof()) {
		::std::cout << "waf property file is syntax error." << ::std::endl;
		return -1;
	}

	::std::string wafFilePathStr = "";
	// 一行目から、WAFファイルの名前を取得
	::std::getline(ifs, wafFilePathStr);
	::std::ofstream ofs(wafFilePathStr.c_str() , ::std::ios_base::binary | ::std::ios_base::out);

	::std::cout << "load <" + propertyFilePathStr + ">" << ::std::endl;
	::std::cout << "waf file <" + wafFilePathStr + ">" << ::std::endl;
	int wafFileSize = 0;
	while (!ifs.eof()) {
		// アーカイブに登録するファイルをオープン
		::std::string sourceFilePathStr;
		::std::getline(ifs, sourceFilePathStr);
		::std::cout << "source file <" + sourceFilePathStr + ">" << ::std::endl;

		::std::ifstream sourcefs(sourceFilePathStr.c_str(), ::std::ios_base::binary | ::std::ios_base::in);

		::pss::std::basic_waf_filebuf<char>::Header header = {0};
		// ファイルサイズ
		// ファイルサイズ調査
		sourcefs.seekg(0, ::std::ios_base::end);
		header.size_ = sourcefs.tellg();
		LOG4CXX_DEBUG(log, "size = " + ::boost::lexical_cast<::std::string>(header.size_));
		// ファイルモード(非圧縮)
		header.mode_ = ::pss::std::basic_waf_filebuf<char>::WAF_NORMAL;
		LOG4CXX_DEBUG(log, "mode = " + ::boost::lexical_cast<::std::string>(header.mode_));
		// ファイル名(ディレクトリを除去、最後尾のファイル名のみ)
		::boost::filesystem::path sourceFilePath(sourceFilePathStr, ::boost::filesystem::no_check);
		::std::string sourceFilenameStr = *(--sourceFilePath.end()); 
		sourceFilenameStr.copy(header.filename_, sourceFilenameStr.length(), 0);
		LOG4CXX_DEBUG(log, "file = " + ::boost::lexical_cast<::std::string>(header.filename_));
		ofs.write((char*) &header, sizeof(header));
		LOG4CXX_DEBUG(log, "header size = " + ::boost::lexical_cast<::std::string>(sizeof(header)));
		wafFileSize += sizeof(header);
		sourcefs.seekg(0, ::std::ios_base::beg);
		int count = 0;
		for( int i = 0; i < header.size_ ; ++i, ++count ) {
			char buf = 0;
			sourcefs.read(&buf, 1);
			ofs.write(&buf, 1);
		}
		wafFileSize += header.size_;
		LOG4CXX_DEBUG(log, "write byte = " + ::boost::lexical_cast<::std::string>(count));		
	}
	// ファイル終端を書き込む( size = -1)
	::pss::std::basic_waf_filebuf<char>::Header header = {0};
	header.size_ = -1;
	ofs.write((char*) &header, sizeof(header));
	LOG4CXX_DEBUG(log, "waf file size = " + ::boost::lexical_cast<::std::string>(wafFileSize));		
	ifs.close();
	ofs.flush();
	ofs.close();
	LOG4CXX_DEBUG(log,"end");
	return 0;
}

/**
 * @param wafFilePathStr
 * @return -1 失敗
 *         0 成功
 */
int doExpand(const ::std::string &wafFilePathStr) {
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("doExpand");
	LOG4CXX_DEBUG(log, "begin.");
	::std::ifstream ifs(wafFilePathStr.c_str(), ::std::ios_base::binary | ::std::ios_base::in);
	
	// WAFファイル名に対応したディレクトリ作成
	::boost::filesystem::path wafFilePath(wafFilePathStr, ::boost::filesystem::no_check);
	::std::string wafFilenameStr = *(--wafFilePath.end());
	LOG4CXX_DEBUG(log, wafFilenameStr);
	::std::string directoryNameStr = ::boost::filesystem::basename(wafFilenameStr);
	LOG4CXX_DEBUG(log, directoryNameStr);
	if (!::boost::filesystem::exists(directoryNameStr)) {
		::boost::filesystem::create_directory(directoryNameStr);
	}
	while (!ifs.eof()) {
		// ヘッダ読み込み
		::pss::std::basic_waf_filebuf<char>::Header header = {0};
		ifs.read((char*) &header, sizeof(header));
		LOG4CXX_DEBUG(log, "header.size = " + ::boost::lexical_cast<::std::string>(header.size_));		
		LOG4CXX_DEBUG(log, "header.mode = " + ::boost::lexical_cast<::std::string>(header.mode_));		
		LOG4CXX_DEBUG(log, "header.mode = " + ::boost::lexical_cast<::std::string>(header.filename_));		
		::std::ofstream ofs((directoryNameStr + "/" + header.filename_).c_str(), ::std::ios_base::out | ::std::ios_base::binary);
		for (int i = 0; i < header.size_; ++i) {
			char buf;
			ifs.read(&buf, 1);
			ofs.write(&buf, 1);
		}
		ofs.close();
	}
	ifs.close();
	LOG4CXX_DEBUG(log, "end.");
	return 0;
}

/**
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char* argv[]) try {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");

	if (argc != 3) {
		::std::cout << "this program is Wajima Archive File Tool." << ::std::endl;
		::std::cout << "> waftool.exe create [waf property file]" << ::std::endl;
		::std::cout << "> waftool.exe expand [waf file]" << ::std::endl;
		return 0;
	}
	::std::string command(argv[1]);
	int result = 0;
	if (command.compare("create") == 0) {
		// WAFファイルぼ生成
		// 設定ファイルパス
		::std::string propertyFilePathStr(argv[2]);
		result = doArchive(propertyFilePathStr);
	} else if (command.compare("expand") == 0) {
		// WAFファイルの展開
		::std::string wafFilePathStr(argv[2]);
		result = doExpand(wafFilePathStr);
	} else {
		// エラー
		result = -1;
	}
	LOG4CXX_DEBUG(log, "end.");
	return result;
} catch (::std::exception &e ) {
	::std::cout << e.what() << ::std::endl;
}