#include "stdafx.h"
#include "CppUnitTest.h"
#include "mystring.h"
#include <cstring>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Length) {
			Assert::IsTrue(String().length() == 0);
			Assert::IsTrue(String("").length() == 0);
			Assert::IsTrue(String("abc").length() == 3);
		}

		TEST_METHOD(ToCString) {
			Assert::AreEqual("12345", String("12345").toCString().get());
			Assert::AreEqual("", String("").toCString().get());
			Assert::AreEqual("", String().toCString().get());
		}

		TEST_METHOD(Construction) {
			String s0;
			String s1("");
			String s2("abc");
			String s00(s0);
			String s11(s1);
			String s22(s2);
			Assert::AreEqual("", s11.toCString().get());
			Assert::AreEqual("abc", s22.toCString().get());
		}

		TEST_METHOD(Concat) {
			Assert::AreEqual("Amigo", String("Amig").concat('o').toCString().get());
			Assert::AreEqual("How are you my friend", String("How ").concat(String("are ").concat(String("you ")).concat(String("my friend"))).toCString().get());
		}

		TEST_METHOD(SubString) {
			//Not performant.. doesn't have to be
			String abc;	for (char c = 'A'; c <= 'Z'; ++c){ abc = abc.concat(c); }
			Assert::AreEqual("C", abc.substring(2, 3).toCString().get());
			Assert::AreEqual("CDEFGH", abc.substring(2, 8).toCString().get());
			Assert::AreEqual("DEF", abc.substring(2, 8).substring(1, 4).toCString().get());
			Assert::AreEqual("", abc.substring(2, 8).substring(1, 4).substring(4, 5).toCString().get());
			Assert::AreEqual("", abc.substring(2, 1).toCString().get());
			Assert::AreEqual("", abc.substring(5, 3).toCString().get());
		}

		TEST_METHOD(CharAt) {
			Assert::IsTrue('0' == String("0123456").charAt(0));
			Assert::IsTrue('6' == String("0123456").charAt(6));
			Assert::IsTrue('2' == String("0123456").charAt(2));
			Assert::IsTrue('1' == String("0123456").substring(1, 5).charAt(0));
			Assert::IsTrue('4' == String("0123456").substring(1, 5).charAt(3));
			Assert::IsTrue('3' == String("0123456").substring(1, 5).charAt(2));
		}

		TEST_METHOD(Equal) {
			Assert::IsTrue(String() == String());
			Assert::IsTrue(String("") == String());
			Assert::IsTrue(String() == String(""));
			Assert::IsTrue(String("") == String(""));
			Assert::IsTrue(String("12345") == String("12345"));
			Assert::IsTrue(String("12345") == String(String("12345")));
			Assert::IsFalse(String("hallo") == String("123456789"));
			Assert::IsFalse(String("12345a") == String("123456789"));
			Assert::IsFalse(String("12345") == String("123456789"));
			Assert::IsTrue(String("12345") == String("0123456789").substring(1, 6));
		}

		TEST_METHOD(ValueOf) {
			Assert::IsTrue(String("0") == String::valueOf(0));
			Assert::IsTrue(String("5") == String::valueOf(5));
			Assert::IsTrue(String("6546") == String::valueOf(6546));
			Assert::IsTrue(String("1345") == String::valueOf(1345));
			Assert::IsTrue(String("-5") == String::valueOf(-5));
			Assert::IsTrue(String("-1534") == String::valueOf(-1534));
			Assert::IsTrue(String("123456789") == String::valueOf(123456789));
			Assert::IsTrue(String("-123456789") == String::valueOf(-123456789));
		}

		TEST_METHOD(CompareTo) {
			Assert::IsTrue(String("a").compareTo("b") == -1);
			Assert::IsTrue(String("b").compareTo("a") == 1);
			Assert::IsTrue(String("aaa").compareTo("bbb") == -1);
			Assert::IsTrue(String("bbb").compareTo("aaa") == 1);
			Assert::IsTrue(String("aaa").compareTo("aac") == -1);
			Assert::IsTrue(String("aac").compareTo("aaa") == 1);
			Assert::IsTrue(String("aaa").compareTo("aaaaa") == -1);
			Assert::IsTrue(String("aaaaa").compareTo("aaa") == 1);
			Assert::IsTrue(String("a").compareTo("a") == 0);
			Assert::IsTrue(String("aaa").compareTo("aaa") == 0);
		}
	};
}