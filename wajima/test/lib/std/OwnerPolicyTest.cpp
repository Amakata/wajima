#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
//CUPPA:include=+
#include <SmartPtr.h>
#include <std/OwnershipPolicy.h>
//CUPPA:include=-

class OwnerPolicyTest : public CppUnit::TestFixture {
//CUPPA:usercode=+
	class TestObject {
	public:
		TestObject():cnt_(0){
			++cnt_;
		}
		virtual ~TestObject(){
			--cnt_;
		}
		int getCount() const{
			return cnt_;
		}
	private:
		int cnt_;
	};
	typedef Loki::SmartPtr<TestObject,Loki::WrapTemplate<zefiro_std::RefCounted>,Loki::DisallowConversion, Loki::WrapTemplate<Loki::NoCheck> > SP;
	typedef Loki::SmartPtr<TestObject,Loki::WrapTemplate<zefiro_std::NoOwnerRefCounted>,Loki::DisallowConversion,Loki::WrapTemplate<Loki::RejectNull> > NOSP;
private:
	// your staff
public:
	virtual void setUp() {
		// initialize
	}
	virtual void tearDown() {
		// terminate
	}
//CUPPA:usercode=-

//CUPPA:decl=+
    void test_copy() {
	}
//CUPPA:decl=-

	CPPUNIT_TEST_SUITE(OwnerPolicyTest);
    CPPUNIT_TEST(test_copy);
	CPPUNIT_TEST_SUITE_END();

};
CPPUNIT_TEST_SUITE_REGISTRATION(OwnerPolicyTest);
  