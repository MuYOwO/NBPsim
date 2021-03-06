#include "stdafx.h"
#include "CppUnitTest.h"

#include "Displacement.h"
#include "Position.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(Position_utst)
    {
    public:

        TEST_METHOD(default_constructor)
        {
            pe::Position<3> a;
            Assert::AreEqual(0.0, a.get<0>());
            Assert::AreEqual(0.0, a.get<1>());
            Assert::AreEqual(0.0, a.get<2>());
        }

        TEST_METHOD(list_initializer_constructor)
        {
            pe::Position<3> a{ 1.,2.,3. };
            Assert::AreEqual(1., a.get<0>());
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(3., a.get<2>());
        }

        TEST_METHOD(vector_t_arg_constructor)
        {
            pe::vector_t <3, double> v{ 1.,2.,3. };
            pe::Position<3> a(v);
            Assert::AreEqual(1., a.get<0>());
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(3., a.get<2>());
            Assert::AreEqual(1., v.get<0>());
            Assert::AreEqual(2., v.get<1>());
            Assert::AreEqual(3., v.get<2>());

            pe::vector_t <3, double> u{ 2.,4.,6. };
            pe::Position<3> b(std::move(u));
            Assert::AreEqual(2., b.get<0>());
            Assert::AreEqual(4., b.get<1>());
            Assert::AreEqual(6., b.get<2>());
        }

        TEST_METHOD(dimension)
        {
            pe::Position<2> a;
            pe::Position<4> b;
            pe::Position<10> c;
            Assert::AreEqual(2U, a.dimension());
            Assert::AreEqual(4U, b.dimension());
            Assert::AreEqual(10U, c.dimension());
        }

        TEST_METHOD(retrieve_nonconst_component_reference)
        {
            pe::Position<3> a;

            a[0] = 1.;
            Assert::AreEqual(1., a[0]);
            Assert::AreEqual(a[0], a.get<0>());

            a.get<1>() = 2.;
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(a.get<1>(), a[1]);

            pe::Position<3>::component_type& a_2_ref_0 = a[2];
            pe::Position<3>::component_type& a_2_ref_1 = a.get<2>();
            Assert::AreSame(a_2_ref_0, a_2_ref_1);
            a_2_ref_0 = 88.;
            Assert::AreEqual(88., a_2_ref_1);
            Assert::AreEqual(88., a[2]);
            Assert::AreEqual(a[2], a.get<2>());
        }

        TEST_METHOD(components)
        {
            pe::Position<3> a{ 1.,2.,3. };
            Assert::AreEqual(1., a.components().get<0>());
            Assert::AreEqual(2., a.components().get<1>());
            Assert::AreEqual(3., a.components().get<2>());
        }

        TEST_METHOD(plus_equal)
        {
            pe::Position<3> a{ 10.,10.,10. };
            pe::Displacement<3> b{ 1.,2.,3. };
            a += b;
            Assert::AreEqual(11., a.get<0>());
            Assert::AreEqual(12., a.get<1>());
            Assert::AreEqual(13., a.get<2>());
        }

        TEST_METHOD(minus_equal)
        {
            pe::Position<3> a{ 10.,10.,10. };
            pe::Displacement<3> b{ 1.,2.,3. };
            a -= b;
            Assert::AreEqual(9., a.get<0>());
            Assert::AreEqual(8., a.get<1>());
            Assert::AreEqual(7., a.get<2>());
        }

        TEST_METHOD(addition)
        {
            pe::Position<3> a{ 10.,10.,10. };
            pe::Displacement<3> b{ 1.,2.,3. };
            pe::Position<3> c = a + b;
            Assert::AreEqual(11., c.get<0>());
            Assert::AreEqual(12., c.get<1>());
            Assert::AreEqual(13., c.get<2>());

            pe::Position<3> d{ 10.,10.,10. };
            pe::Displacement<3> e{ 1.,2.,3. };
            pe::Position<3> f = e + d;
            Assert::AreEqual(11., f.get<0>());
            Assert::AreEqual(12., f.get<1>());
            Assert::AreEqual(13., f.get<2>());
        }

        TEST_METHOD(subtraction)
        {
            pe::Position<3> a{ 10.,10.,10. };
            pe::Displacement<3> b{ 1.,2.,3. };
            pe::Position<3> c = a - b;
            Assert::AreEqual(9., c.get<0>());
            Assert::AreEqual(8., c.get<1>());
            Assert::AreEqual(7., c.get<2>());

            pe::Position<3> d{ 10.,10.,10. };
            pe::Position<3> e{ 1.,2.,3. };
            pe::Displacement<3> f = d - e;
            Assert::AreEqual(9., f.get<0>());
            Assert::AreEqual(8., f.get<1>());
            Assert::AreEqual(7., f.get<2>());
        }

        TEST_METHOD(collides)
        {
            pe::Position<3> a{ 0.,10.,0. };
            pe::Position<3> b{ 0.,11.,0. };
            Assert::IsTrue(a.collides(b, 1.1));
            Assert::IsFalse(a.collides(b));
        }

        TEST_METHOD(equality_and_inequality)
        {
            pe::Position<3> a{ 10.,11.,22. };
            pe::Position<3> b = a;
            pe::Position<3> c = { 1.,2.,3. };
            Assert::IsTrue(a == b);
            Assert::IsTrue(a != c);
        }
    };
}
