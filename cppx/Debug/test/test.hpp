#include <iostream>


namespace zefiro {
	namespace filesystem {
		class test {
// CPPX_BEGIN ::zefiro::filesystem::test
			virtual void test() {
// CPPX_FUNC_BEGIN void $0$::test()
				::std::cout << "test" << ::std::endl;
// CPPX_FUNC_END
			}
// CPPX_STATIC int $0$::a = 0;
			static int a;
// CPPX_END
		};
	}
}
