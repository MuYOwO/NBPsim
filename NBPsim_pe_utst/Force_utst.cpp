#include "stdafx.h"
#include "CppUnitTest.h"

#include "Force.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(Force_utst)
    {
    public:

        TEST_METHOD(default_constructor)
        {
            pe::Force<3> a;
            Assert::AreEqual(0.0, a.get<0>());
            Assert::AreEqual(0.0, a.get<1>());
            Assert::AreEqual(0.0, a.get<2>());
        }
    };
}