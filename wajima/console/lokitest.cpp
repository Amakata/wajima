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
 * wafbuf�Awafstraem�Aifstream�̓���`�F�b�N
 */
int test(int argc, char *argv[]) {
	LOG4CXX_CONFIGUER("console.properties");
	LOG4CXX_LOGGER_PTR log = LOG4CXX_LOGGER("main");
	LOG4CXX_DEBUG(log, "begin.");
	// �E�B���h�E�Y�l�[���̂݋���
	::boost::filesystem::path test("test", ::boost::filesystem::windows_name);
	::boost::filesystem::path test2 = ::boost::filesystem::complete(test);
	// path�̊e�탁�\�b�h�e�X�g
	::std::cout << test2.root_path().string() << ::std::endl;
	::std::cout << test2.root_name() << ::std::endl;
	::std::cout << test2.root_directory() << ::std::endl;
	::std::cout << test2.leaf() << ::std::endl;
	::std::cout << test2.string() << ::std::endl;
	
	// waf�p�ǂݎ��t�@�C���o�b�t�@
	::pss::std::basic_waf_filebuf<char> wafbuf;
	// waf���̓X�g���[��
	::pss::std::basic_waf_ifstream<char> wafstream;
	try {
		//
		// wafbuf�̓��������
		//
		// data.waf��test2.txt���I�[�v��
		wafbuf.open("data/test2.txt");
		// waf�o�b�t�@���쐬
		::std::basic_istream<char> is(&wafbuf);

		// ��s���ǂݎ��
		::std::string str = "";
		while (!is.eof()) {
			::std::getline(is, str);
			LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		}
		// �N���A
		is.clear();
		// �擪�փV�[�N
		is.seekg(0, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// �擪����P�o�C�g�V�[�N
		is.seekg(1, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// �擪����W�o�C�g�V�[�N
		is.seekg(8, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// �擪����X�o�C�g�V�[�N
		is.seekg(9, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		// �擪����P�O�o�C�g�V�[�N
		is.seekg(10, ::std::ios_base::beg);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		is.clear();
		// ���݈ʒu����-11�o�C�g�V�[�N
		is.seekg(-11, ::std::ios_base::cur);
		::std::getline(is, str);
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));
		
		wafbuf.close();

		//
		// wafstream�̓��������
		//
		// data.waf��test2.txt���I�[�v��
		wafstream.open(::boost::filesystem::path("data/test2.txt"));
		wafstream >>  str;
		LOG4CXX_DEBUG(log, "str = " + str + " , length = " + ::boost::lexical_cast<::std::string>(str.length()));		
		wafstream.close();

		//
		//�@ifstream��wafbuf�̃X�g���[���Ɠ�����������邩���؂���
		//
		// test.txt���I�[�v��
		::std::basic_ifstream<char> ifs("test.txt");
		// ��s���ǂݍ���
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