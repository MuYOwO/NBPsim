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

        TEST_METHOD(copy_assignment)
        {
            pe::vector_t<3, int> a{ 1,3,5 };
            pe::vector_t<3, int> b;
            b = a;
            Assert::AreEqual(1, b.get<0>());
            Assert::AreEqual(3, b.get<1>());
            Assert::AreEqual(5, b.get<2>());
            Assert::AreEqual(1, a.get<0>());
            Assert::AreEqual(3, a.get<1>());
            Assert::AreEqual(5, a.get<2>());
        }

        TEST_METHOD(move_assignment)
        {
            pe::vector_t<3, int> a{ 1,3,5 };
            pe::vector_t<3, int> b;
            b = std::move(a);
            Assert::AreEqual(1, b.get<0>());
            Assert::AreEqual(3, b.get<1>());
            Assert::AreEqual(5, b.get<2>());
        }

        TEST_METHOD(dimension)
        {
            pe::vector_t<3, int> a;
            pe::vector_t<5, double> b;
            pe::vector_t<7, float> c;
            pe::vector_t<8, unsigned> d;
            Assert::AreEqual(3U, a.dimension());
            Assert::AreEqual(5U, b.dimension());
            Assert::AreEqual(7U, c.dimension());
            Assert::AreEqual(8U, d.dimension());
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

        TEST_METHOD(norm_squared)
        {
            pe::vector_t<3, int> a{ 3,4,5 };
            int norm_sq = a.norm_squared();
            Assert::AreEqual(50, norm_sq);
            pe::vector_t<2, int> b{ 3,4 };
            norm_sq = b.norm_squared();
            Assert::AreEqual(25, norm_sq);
        }

        TEST_METHOD(plus_equal)
        {
            pe::vector_t<3, int> a{ 10,10,10 };
            pe::vector_t<3, int> b{ 1,2,3 };
            a += b;
            Assert::AreEqual(11, a.get<0>());
            Assert::AreEqual(12, a.get<1>());
            Assert::AreEqual(13, a.get<2>());
        }

        TEST_METHOD(minus_equal)
        {
            pe::vector_t<3, int> a{ 10,10,10 };
            pe::vector_t<3, int> b{ 1,2,3 };
            a -= b;
            Assert::AreEqual(9, a.get<0>());
            Assert::AreEqual(8, a.get<1>());
            Assert::AreEqual(7, a.get<2>());
        }

        TEST_METHOD(scalar_multiplies_equal)
        {
            pe::vector_t<3, int> a{ 2,6,8 };
            int c = 3;
            a *= c;
            Assert::AreEqual(6, a.get<0>());
            Assert::AreEqual(18, a.get<1>());
            Assert::AreEqual(24, a.get<2>());
        }

        TEST_METHOD(scalar_divides_equal)
        {
            pe::vector_t<3, int> a{ 3,6,9 };
            int c = 3;
            a /= c;
            Assert::AreEqual(1, a.get<0>());
            Assert::AreEqual(2, a.get<1>());
            Assert::AreEqual(3, a.get<2>());
        }

        TEST_METHOD(opposite_and_negate)
        {
            pe::vector_t<3, int> a{ 3,6,9 };

            pe::vector_t<3, int> b(-a);
            Assert::AreEqual(-3, b.get<0>());
            Assert::AreEqual(-6, b.get<1>());
            Assert::AreEqual(-9, b.get<2>());

            pe::vector_t<3, int> c(a.opposite());
            Assert::AreEqual(-3, c.get<0>());
            Assert::AreEqual(-6, c.get<1>());
            Assert::AreEqual(-9, c.get<2>());
        }

        TEST_METHOD(addition)
        {
            pe::vector_t<3, int> a{ 10,10,10 };
            pe::vector_t<3, int> b{ 1,2,3 };
            pe::vector_t<3, int> c = a + b;
            Assert::AreEqual(11, c.get<0>());
            Assert::AreEqual(12, c.get<1>());
            Assert::AreEqual(13, c.get<2>());
        }

        TEST_METHOD(subtraction)
        {
            pe::vector_t<3, int> a{ 10,10,10 };
            pe::vector_t<3, int> b{ 1,2,3 };
            pe::vector_t<3, int> c = a - b;
            Assert::AreEqual(9, c.get<0>());
            Assert::AreEqual(8, c.get<1>());
            Assert::AreEqual(7, c.get<2>());
        }

        TEST_METHOD(scalar_multiplication)
        {
            pe::vector_t<3, int> a{ 2,6,8 };
            int c = 3;
            pe::vector_t<3, int> b = a * c;
            Assert::AreEqual(6, b.get<0>());
            Assert::AreEqual(18, b.get<1>());
            Assert::AreEqual(24, b.get<2>());
        }

        TEST_METHOD(scalar_division)
        {
            pe::vector_t<3, int> a{ 3,6,9 };
            int c = 3;
            pe::vector_t<3, int> b = a / c;
            Assert::AreEqual(1, b.get<0>());
            Assert::AreEqual(2, b.get<1>());
            Assert::AreEqual(3, b.get<2>());
        }

        TEST_METHOD(equality_and_inequality)
        {
            pe::vector_t<3, int> a{ 10,11,22 };
            pe::vector_t<3, int> b = a;
            pe::vector_t<3, int> c = { 1,2,3 };
            Assert::IsTrue(a == b);
            Assert::IsTrue(a != c);
        }
    };
}