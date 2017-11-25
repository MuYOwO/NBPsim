#include "stdafx.h"
#include "CppUnitTest.h"

#include "vector_t.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(vector_t_utst)
    {
    public:

        TEST_METHOD(default_constructor)
        {
            pe::vector_t<3, int> a;
            Assert::AreEqual(0, a.get<0>());
            Assert::AreEqual(0, a.get<1>());
            Assert::AreEqual(0, a.get<2>());

            pe::vector_t<2, double> b;
            Assert::AreEqual(0.0, b.get<0>());
            Assert::AreEqual(0.0, b.get<1>());
        }

        TEST_METHOD(list_initializer_constructor)
        {
            pe::vector_t<3, int> a{ 1, 2, 3 };
            Assert::AreEqual(1, a.get<0>());
            Assert::AreEqual(2, a.get<1>());
            Assert::AreEqual(3, a.get<2>());

            pe::vector_t<2, double> b{ 1.0,3.0 };
            Assert::AreEqual(1.0, b.get<0>());
            Assert::AreEqual(3.0, b.get<1>());

            pe::vector_t<3, int> c{ 1 };
            Assert::AreEqual(1, c.get<0>());
            Assert::AreEqual(0, c.get<1>());
            Assert::AreEqual(0, c.get<2>());

            pe::vector_t<3, int> d{  };
            Assert::AreEqual(0, d.get<0>());
            Assert::AreEqual(0, d.get<1>());
            Assert::AreEqual(0, d.get<2>());
        }

        TEST_METHOD(copy_constructor)
        {
            pe::vector_t<3, int> a{ 1,3,5 };
            pe::vector_t<3, int> b(a);
            Assert::AreEqual(a.get<0>(), b.get<0>());
            Assert::AreEqual(a.get<1>(), b.get<1>());
            Assert::AreEqual(a.get<2>(), b.get<2>());
        }

        TEST_METHOD(move_constructor)
        {
            pe::vector_t<3, int> a{ 1,3,5 };
            pe::vector_t<3, int> b(std::move(a));
            Assert::AreEqual(1, b.get<0>());
            Assert::AreEqual(3, b.get<1>());
            Assert::AreEqual(5, b.get<2>());
        }

        TEST_METHOD(retrieve_nonconst_component_reference)
        {
            pe::vector_t<3, int> a;

            a[0] = 1;
            Assert::AreEqual(1, a[0]);
            Assert::AreEqual(a[0], a.get<0>());

            a.get<1>() = 2;
            Assert::AreEqual(2, a.get<1>());
            Assert::AreEqual(a.get<1>(), a[1]);

            int& a_2_ref_0 = a[2];
            int& a_2_ref_1 = a.get<2>();
            Assert::AreEqual(&a_2_ref_0, &a_2_ref_1);
            a_2_ref_0 = 88;
            Assert::AreEqual(88, a_2_ref_1);
            Assert::AreEqual(88, a[2]);
            Assert::AreEqual(a[2], a.get<2>());
        }
    };
}