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
 * @param propertyFilePathStr WAF�A�[�J�C�u�t�@�C�����쐬����v���p�e�B�t�@�C��
 * @return 0 ����
 *         -1 ���s
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
	// ��s�ڂ���AWAF�t�@�C���̖��O���擾
	::std::getline(ifs, wafFilePathStr);
	::std::ofstream ofs(wafFilePathStr.c_str() , ::std::ios_base::binary | ::std::ios_base::out);

	::std::cout << "load <" + propertyFilePathStr + ">" << ::std::endl;
	::std::cout << "waf file <" + wafFilePathStr + ">" << ::std::endl;
	int wafFileSize = 0;
	while (!ifs.eof()) {
		// �A�[�J�C�u�ɓo�^����t�@�C�����I�[�v��
		::std::string sourceFilePathStr;
		::std::getline(ifs, sourceFilePathStr);
		::std::cout << "source file <" + sourceFilePathStr + ">" << ::std::endl;

		::std::ifstream sourcefs(sourceFilePathStr.c_str(), ::std::ios_base::binary | ::std::ios_base::in);

		::pss::std::basic_waf_filebuf<char>::Header header = {0};
		// �t�@�C���T�C�Y
		// �t�@�C���T�C�Y����
		sourcefs.seekg(0, ::std::ios_base::end);
		header.size_ = sourcefs.tellg();
		LOG4CXX_DEBUG(log, "size = " + ::boost::lexical_cast<::std::string>(header.size_));
		// �t�@�C�����[�h(�񈳏k)
		header.mode_ = ::pss::std::basic_waf_filebuf<char>::WAF_NORMAL;
		LOG4CXX_DEBUG(log, "mode = " + ::boost::lexical_cast<::std::string>(header.mode_));
		// �t�@�C����(�f�B���N�g���������A�Ō���̃t�@�C�����̂�)
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
	// �t�@�C���I�[����������( size = -1)
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
 * @return -1 ���s
 *         0 ����
 */
int doExpand(const ::std::string &wafFilePathStr) {
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("doExpand");
	LOG4CXX_DEBUG(log, "begin.");
	::std::ifstream ifs(wafFilePathStr.c_str(), ::std::ios_base::binary | ::std::ios_base::in);
	
	// WAF�t�@�C�����ɑΉ������f�B���N�g���쐬
	::boost::filesystem::path wafFilePath(wafFilePathStr, ::boost::filesystem::no_check);
	::std::string wafFilenameStr = *(--wafFilePath.end());
	LOG4CXX_DEBUG(log, wafFilenameStr);
	::std::string directoryNameStr = ::boost::filesystem::basename(wafFilenameStr);
	LOG4CXX_DEBUG(log, directoryNameStr);
	if (!::boost::filesystem::exists(directoryNameStr)) {
		::boost::filesystem::create_directory(directoryNameStr);
	}
	while (!ifs.eof()) {
		// �w�b�_�ǂݍ���
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
		// WAF�t�@�C���ڐ���
		// �ݒ�t�@�C���p�X
		::std::string propertyFilePathStr(argv[2]);
		result = doArchive(propertyFilePathStr);
	} else if (command.compare("expand") == 0) {
		// WAF�t�@�C���̓W�J
		::std::string wafFilePathStr(argv[2]);
		result = doExpand(wafFilePathStr);
	} else {
		// �G���[
		result = -1;
	}
	LOG4CXX_DEBUG(log, "end.");
	return result;
} catch (::std::exception &e ) {
	::std::cout << e.what() << ::std::endl;
}