#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

namespace fs = ::boost::filesystem;
bool zefiro_name( const std::string & name )
{
    return
    name.size() == 0
    || name == "."
    || name == ".."
	|| (::fs::windows_name( name )
	&& ::fs::portable_posix_name( name )
    && name[0] != '-');
}

class cppx_operation {
public:
	enum op_code {prefix, function};
	cppx_operation(op_code op, ::std::string value) : op_code_(op), value_(value) {
	}
	::std::string get_value() const {
		return value_;
	}
	op_code get_op_code() const {
		return op_code_;
	}
	::std::string str() const {
		if (op_code_ == function) {
			return ::std::string("FUNCTION :") + value_;
		} else {
			return ::std::string("PREFIX   :") + value_;
		}
	}
private:
	::std::string value_;
	op_code op_code_;
};

::std::string get_func_prefix( ::std::list< cppx_operation >& op_stack ) {
	::std::list< cppx_operation >::iterator it = op_stack.begin();
	::std::list< cppx_operation >::iterator end = op_stack.end();
	::std::string result = "";
	if (it == end) {
		return result;
	}
	--end;
	while (it != end) {
		result = result + it->get_value(); 
		++it;
	}
	return result;
}

::std::string get_static_prefix( ::std::list< cppx_operation >& op_stack ) {
	::std::list< cppx_operation >::iterator it = op_stack.begin();
	::std::list< cppx_operation >::iterator end = op_stack.end();
	::std::string result = "";
	if (it == end) {
		return result;
	}
	while (it != end) {
		result = result + it->get_value(); 
		++it;
	}
	return result;
}


void generate_cppx(::fs::path source_path, ::fs::path dest_path, bool modify) {
	if (modify) {
		::fs::remove(dest_path);
	}
	::std::list< cppx_operation > op_stack;
	::fs::ifstream source_fs(source_path);
	::fs::ofstream dest_fs(dest_path);
	::fs::ofstream dest_fs_cpp(::fs::change_extension(dest_path,".cpp"));
	dest_fs_cpp << "#include \"" << dest_path.leaf() << "\"" << ::std::endl; 

	::boost::regex cppx_re("^//[\\s]*CPPX");
	::boost::regex cppx_begin_re("^_BEGIN[\\s]*([\\w\\s:]*)");
	::boost::regex cppx_func_begin_re("^_FUNC_BEGIN[\\s]*");
	::boost::regex cppx_func_end_re("^_FUNC_END");
	::boost::regex cppx_end_re("^_END");
	::boost::regex cppx_static_re("^_STATIC[\\s]*");
	::boost::regex cppx_func_tail("\\{[\\s]*$");
	::boost::smatch smresult;
	while (!source_fs.eof()) {
		::std::string line;
		::std::getline(source_fs, line);
//		::std::cout << "line " << line << ::std::endl;
		if (::boost::regex_search(line, smresult, cppx_re)) {
			::std::string suffix = smresult.suffix();
			::boost::smatch smresult;
			if (::boost::regex_search(suffix, smresult, cppx_begin_re)) {
				// スタックを積むだけ
				op_stack.push_back(cppx_operation(cppx_operation::prefix, smresult.str(1)));
//				::std::cout << "push() [" << op_stack.back().str() << "]" << ::std::endl;
			} else if(::boost::regex_search(suffix, smresult, cppx_func_begin_re)) {
				op_stack.push_back(cppx_operation(cppx_operation::function, smresult.suffix()));
//				::std::cout << "push() [" << op_stack.back().str() << "]" << ::std::endl;
				// 解析してcpp側に出力
				dest_fs_cpp << smresult.suffix().str().replace(smresult.suffix().str().find("$0$"), 3, get_func_prefix(op_stack)) + " {"<< ::std::endl;
				::std::getline(source_fs, line);
				if (::boost::regex_search(line, smresult, cppx_func_tail)) {
					dest_fs << smresult.prefix() << ";" << ::std::endl;
				} else {
					dest_fs << line << ";" << ::std::endl;
				}
			} else if(::boost::regex_search(suffix, smresult, cppx_func_end_re)) {
				// スタックを戻すだけ。
//				::std::cout << "pop()  [" << op_stack.back().str() << "]" << ::std::endl;
				op_stack.pop_back();
			} else if(::boost::regex_search(suffix, smresult, cppx_end_re)) {
				// スタックを戻すだけ。
//				::std::cout << "pop()  [" << op_stack.back().str() << "]" << ::std::endl;
				op_stack.pop_back();
			} else if(::boost::regex_search(suffix, smresult, cppx_static_re)) {
				// CPPX_STATICはcpp側に出力
//				::std::cout << "       [STATIC   :" << smresult.suffix() << "]" << ::std::endl;
//				::std::cout << smresult.suffix().str().find("$0$") << ::std::endl;
				dest_fs_cpp << smresult.suffix().str().replace(smresult.suffix().str().find("$0$"), 3, get_static_prefix(op_stack)) << ::std::endl;
			}
		} else {
			if (op_stack.size() > 0 && op_stack.back().get_op_code() == cppx_operation::function ) {
				// CPPX_FUNCなのでcpp側に出力
				dest_fs_cpp << line << ::std::endl;
			} else {
				// CPPX_FUNCではないのでhpp側に出力
				dest_fs << line << ::std::endl;
			}
		}
	}
	source_fs.close();
	dest_fs.close();
	dest_fs_cpp.close();
}

void generate_cppx_tree(::fs::path source_path, ::fs::path dest_path) {
	if ( ::fs::is_directory(source_path)) {
		// 目的側にディレクトリが存在していない場合は、コピー
		if (!::fs::exists(dest_path)) {
			::fs::create_directory(dest_path);
		}
		// ディレクトリ配下について同様に実行
		::fs::directory_iterator it = ::fs::directory_iterator(source_path);
		::fs::directory_iterator end = ::fs::directory_iterator();
		while (it != end) {
			if (it->leaf() != ::std::string(".svn")) {
				generate_cppx_tree(*it, dest_path / it->leaf());
			}
			++it;
		}
	} else {
		// 拡張子がhppかhの以外は終了
		if (::fs::extension(source_path) == ::std::string(".hpp") || ::fs::extension(source_path) == ::std::string(".h")) {
			// 目的側にファイルが存在しているか？
			if (::fs::exists(dest_path)) {
				::boost::posix_time::ptime source_ptime = ::boost::posix_time::from_time_t(::fs::last_write_time(source_path));
				::boost::posix_time::ptime dest_ptime = ::boost::posix_time::from_time_t(::fs::last_write_time(dest_path));
				if (source_ptime > dest_ptime) {
					// ソースの方が新しければ処理
					generate_cppx(source_path, dest_path , true);
					::std::cout << "M " << source_path.native_file_string() << ::std::endl;
				} else {
					::std::cout << "  " << source_path.native_file_string() << ::std::endl;
				}
			} else {
				// 目的側にソースが存在しなければ処理
				generate_cppx(source_path, dest_path , false);
				::std::cout << "C " << source_path.native_file_string() << ::std::endl;
			}
		}
	}
}

int main(int argc, char* argv[]) try {
	if (argc < 2) {
		::std::cout << "cppx [source_path] [dest_path]" << ::std::endl;
		return 0;
	}
	::fs::path::default_name_check(zefiro_name);
	::fs::path source_path(argv[1], ::fs::native);
	::fs::path dest_path(argv[2], ::fs::native);
	::std::cout << "source = " << ::fs::complete(source_path).native_file_string() << ::std::endl;
	::std::cout << "dest   = " << ::fs::complete(dest_path).native_file_string() << ::std::endl;
	generate_cppx_tree(::fs::complete(source_path), ::fs::complete(dest_path));
	return 0;
} catch (::fs::filesystem_error &e) {
	::std::cerr << e.what() << ::std::endl;
}

