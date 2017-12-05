#include "stdafx.h"
#include "CppUnitTest.h"

#include "Velocity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(Velocity_utst)
    {
    public:

        TEST_METHOD(default_constructor)
        {
            pe::Velocity<3> a;
            Assert::AreEqual(0.0, a.get<0>());
            Assert::AreEqual(0.0, a.get<1>());
            Assert::AreEqual(0.0, a.get<2>());
        }

        TEST_METHOD(list_initializer_constructor)
        {
            pe::Velocity<3> a{ 1.,2.,3. };
            Assert::AreEqual(1., a.get<0>());
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(3., a.get<2>());
        }

        TEST_METHOD(vector_t_arg_constructor)
        {
            pe::vector_t <3, double> v{ 1.,2.,3. };
            pe::Velocity<3> a(v);
            Assert::AreEqual(1., a.get<0>());
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(3., a.get<2>());
            Assert::AreEqual(1., v.get<0>());
            Assert::AreEqual(2., v.get<1>());
            Assert::AreEqual(3., v.get<2>());

            pe::vector_t <3, double> u{ 2.,4.,6. };
            pe::Velocity<3> b(std::move(u));
            Assert::AreEqual(2., b.get<0>());
            Assert::AreEqual(4., b.get<1>());
            Assert::AreEqual(6., b.get<2>());
        }

        TEST_METHOD(dimension)
        {
            pe::Velocity<2> a;
            pe::Velocity<4> b;
            pe::Velocity<10> c;
            Assert::AreEqual(2U, a.dimension());
            Assert::AreEqual(4U, b.dimension());
            Assert::AreEqual(10U, c.dimension());
        }

        TEST_METHOD(retrieve_nonconst_component_reference)
        {
            pe::Velocity<3> a;

            a[0] = 1.;
            Assert::AreEqual(1., a[0]);
            Assert::AreEqual(a[0], a.get<0>());

            a.get<1>() = 2.;
            Assert::AreEqual(2., a.get<1>());
            Assert::AreEqual(a.get<1>(), a[1]);

            pe::Velocity<3>::component_type& a_2_ref_0 = a[2];
            pe::Velocity<3>::component_type& a_2_ref_1 = a.get<2>();
            Assert::AreSame(a_2_ref_0, a_2_ref_1);
            a_2_ref_0 = 88.;
            Assert::AreEqual(88., a_2_ref_1);
            Assert::AreEqual(88., a[2]);
            Assert::AreEqual(a[2], a.get<2>());
        }

        TEST_METHOD(components)
        {
            pe::Velocity<3> a{ 1.,2.,3. };
            Assert::AreEqual(1., a.components().get<0>());
            Assert::AreEqual(2., a.components().get<1>());
            Assert::AreEqual(3., a.components().get<2>());
        }

        TEST_METHOD(norm_squared_and_norm)
        {
            pe::Velocity<3> a{ 2.,3.,4. };
            pe::Velocity<3>::component_type actual_norm_squared = 2.*2. + 3.*3. + 4.*4.;
            pe::Velocity<3>::component_type actual_norm = ::sqrt(actual_norm_squared);
            Assert::AreEqual(actual_norm_squared, a.norm_squared());
            Assert::AreEqual(actual_norm, a.norm());
        }

        TEST_METHOD(unit_vector)
        {
            pe::Velocity<3> a{ 2.,3.,4. };
            pe::Velocity<3> u = a.unit_vector();
            pe::Velocity<3>::component_type actual_norm_squared = 2.*2. + 3.*3. + 4.*4.;
            pe::Velocity<3>::component_type actual_norm = ::sqrt(actual_norm_squared);
            Assert::AreEqual(2. / actual_norm, u.get<0>());
            Assert::AreEqual(3. / actual_norm, u.get<1>());
            Assert::AreEqual(4. / actual_norm, u.get<2>());
        }

        TEST_METHOD(plus_equal)
        {
            pe::Velocity<3> a{ 10.,10.,10. };
            pe::Velocity<3> b{ 1.,2.,3. };
            a += b;
            Assert::AreEqual(11., a.get<0>());
            Assert::AreEqual(12., a.get<1>());
            Assert::AreEqual(13., a.get<2>());
        }

        TEST_METHOD(minus_equal)
        {
            pe::Velocity<3> a{ 10.,10.,10. };
            pe::Velocity<3> b{ 1.,2.,3. };
            a -= b;
            Assert::AreEqual(9., a.get<0>());
            Assert::AreEqual(8., a.get<1>());
            Assert::AreEqual(7., a.get<2>());
        }

        TEST_METHOD(multiplies_equal)
        {
            pe::Velocity<3> a{ 12.,16.,18. };
            a *= 2.;
            Assert::AreEqual(24., a.get<0>());
            Assert::AreEqual(32., a.get<1>());
            Assert::AreEqual(36., a.get<2>());
        }

        TEST_METHOD(divides_equal)
        {
            pe::Velocity<3> a{ 12.,16.,18. };
            a /= 2.;
            Assert::AreEqual(6., a.get<0>());
            Assert::AreEqual(8., a.get<1>());
            Assert::AreEqual(9., a.get<2>());
        }

        TEST_METHOD(opposite_and_negate)
        {
            pe::Velocity<3> a{ 3.,6.,9. };

            pe::Velocity<3> b(-a);
            Assert::AreEqual(-3., b.get<0>());
            Assert::AreEqual(-6., b.get<1>());
            Assert::AreEqual(-9., b.get<2>());

            pe::Velocity<3> c(a.opposite());
            Assert::AreEqual(-3., c.get<0>());
            Assert::AreEqual(-6., c.get<1>());
            Assert::AreEqual(-9., c.get<2>());
        }

        TEST_METHOD(addition)
        {
            pe::Velocity<3> a{ 10.,10.,10. };
            pe::Velocity<3> b{ 1.,2.,3. };
            pe::Velocity<3> c = a + b;
            Assert::AreEqual(11., c.get<0>());
            Assert::AreEqual(12., c.get<1>());
            Assert::AreEqual(13., c.get<2>());
        }

        TEST_METHOD(subtraction)
        {
            pe::Velocity<3> a{ 10.,10.,10. };
            pe::Velocity<3> b{ 1.,2.,3. };
            pe::Velocity<3> c = a - b;
            Assert::AreEqual(9., c.get<0>());
            Assert::AreEqual(8., c.get<1>());
            Assert::AreEqual(7., c.get<2>());
        }

        TEST_METHOD(multiplication)
        {
            pe::Velocity<3> a{ 12.,16.,18. };
            pe::Velocity<3> b = a * 2.;
            pe::Velocity<3> c = 3. * a;
            Assert::AreEqual(24., b.get<0>());
            Assert::AreEqual(32., b.get<1>());
            Assert::AreEqual(36., b.get<2>());
            Assert::AreEqual(36., c.get<0>());
            Assert::AreEqual(48., c.get<1>());
            Assert::AreEqual(54., c.get<2>());
        }

        TEST_METHOD(division)
        {
            pe::Velocity<3> a{ 12.,16.,18. };
            pe::Velocity<3> b = a / 2.;
            Assert::AreEqual(6., b.get<0>());
            Assert::AreEqual(8., b.get<1>());
            Assert::AreEqual(9., b.get<2>());
        }

        TEST_METHOD(equality_and_inequality)
        {
            pe::Velocity<3> a{ 10.,11.,22. };
            pe::Velocity<3> b = a;
            pe::Velocity<3> c = { 1.,2.,3. };
            Assert::IsTrue(a == b);
            Assert::IsTrue(a != c);
        }
    };
}
