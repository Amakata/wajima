#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
//CUPPA:include=+
#include <SmartPtr.h>
#include <std/OwnershipPolicy.h>
#include <std/CheckingPolicy.h>
//CUPPA:include=-

class OwnerPolicyTest : public CppUnit::TestFixture {
//CUPPA:usercode=+
	class TestObject {
	public:
		TestObject(int &cnt):cnt_(cnt){
			++cnt_;
		}
		virtual ~TestObject(){
			--cnt_;
		}
	private:
		int& cnt_;
	};
	typedef Loki::SmartPtr<TestObject,Loki::WrapTemplate<zefiro_std::RefCounted>,Loki::DisallowConversion, Loki::WrapTemplate<zefiro_std::RejectNull> > SP;
	typedef Loki::SmartPtr<TestObject,Loki::WrapTemplate<zefiro_std::NoOwnerRefCounted>,Loki::DisallowConversion,Loki::WrapTemplate<zefiro_std::RejectNull> > NOSP;
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
		try{
			// �R���X�g���N�^�E�f�X�g���N�^�̃J�E���^
			int cnt = 0;
			//	SP�̃R���X�g���N�g�ƃf�X�g���N�g�ɂ��J�E���^�l�̃`�F�b�N
			{
				CPPUNIT_ASSERT_EQUAL( 0 , cnt );
				SP sp = SP( new TestObject( cnt ));
				CPPUNIT_ASSERT_EQUAL( 1 , cnt );
			}
			CPPUNIT_ASSERT_EQUAL( 0 , cnt );
			{
				SP sp = SP( new TestObject( cnt ));
				{
					CPPUNIT_ASSERT_EQUAL( 1 , cnt );
					NOSP nosp = sp;
					CPPUNIT_ASSERT_EQUAL( 1 , cnt );
				}
				CPPUNIT_ASSERT_EQUAL( 1 , cnt );
			}
			CPPUNIT_ASSERT_EQUAL( 0 , cnt );
		}catch( zefiro_std::NullPointerException &e ){
			CPPUNIT_FAIL("NullPointerException");
		}
	}
//CUPPA:decl=-

	CPPUNIT_TEST_SUITE(OwnerPolicyTest);
    CPPUNIT_TEST(test_copy);
	CPPUNIT_TEST_SUITE_END();

};
CPPUNIT_TEST_SUITE_REGISTRATION(OwnerPolicyTest);
  