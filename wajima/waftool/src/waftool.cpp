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
 * data/test/
 * 
 */
int main(int argc, char* argv[]) try {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");

	if (argc == 1) {
		::std::cout << "this program is Wajima Archive File Tool." << ::std::endl;
		::std::cout << "> waftool.exe [waf property file]" << ::std::endl;
		return 0;
	}
	// �ݒ�t�@�C���p�X
	::std::string propertyFilePath(argv[1]);

	::std::ifstream ifs(propertyFilePath.c_str());

	if (ifs.eof()) {
		::std::cout << "waf property file is syntax error." << ::std::endl;
		return -1;
	}

	::std::string wafFilePath = "";
	// ��s�ڂ���AWAF�t�@�C���̖��O���擾
	::std::getline(ifs, wafFilePath);
	::std::ofstream ofs(wafFilePath.c_str() , ::std::ios_base::binary | ::std::ios_base::out);

	::std::cout << "load <" + propertyFilePath + ">" << ::std::endl;
	::std::cout << "waf file <" + wafFilePath + ">" << ::std::endl;

	while (!ifs.eof()) {
		// �A�[�J�C�u�ɓo�^����t�@�C�����I�[�v��
		::std::string sourceFilePath;
		::std::getline(ifs, sourceFilePath);
		::std::cout << "source file <" + sourceFilePath + ">" << ::std::endl;

		::std::ifstream sourcefs(sourceFilePath.c_str(), ::std::ios_base::binary | ::std::ios_base::in);

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
		::std::string sourceFileName = ::boost::filesystem::basename(::boost::filesystem::path(sourceFilePath, ::boost::filesystem::no_check));
		LOG4CXX_DEBUG(log, "leaf ok");
		sourceFileName.copy(header.filename_, sourceFileName.length(), 0);
		LOG4CXX_DEBUG(log, "file = " + ::boost::lexical_cast<::std::string>(header.filename_));
		ofs.write((char*) &header, sizeof(header));
		::std::copy(::std::istream_iterator<char>(sourcefs), ::std::istream_iterator<char>(), ::std::ostream_iterator<char>(ofs));
	}

	ifs.close();
	LOG4CXX_DEBUG(log, "end.");
	return 0;
} catch (::std::exception &e ) {
	::std::cout << e.what() << ::std::endl;
}