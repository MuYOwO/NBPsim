#include "stdafx.h"
#include "CppUnitTest.h"

#include "Body.h"
#include "Force.h"
#include "Position.h"
#include "Velocity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(Body_utst)
    {
    public:

        TEST_METHOD(default_constructor)
        {
            pe::Body<3> a;
            Assert::AreEqual(1.0, a.get_mass());
            Assert::AreEqual(0.0, a.get_position().get<0>());
            Assert::AreEqual(0.0, a.get_position().get<1>());
            Assert::AreEqual(0.0, a.get_position().get<2>());
            Assert::AreEqual(0.0, a.get_velocity().get<0>());
            Assert::AreEqual(0.0, a.get_velocity().get<1>());
            Assert::AreEqual(0.0, a.get_velocity().get<2>());
        }

        TEST_METHOD(full_constructor)
        {
            pe::Body<3> a(3., pe::Position<3>(2., 2., 2.), pe::Velocity<3>(1., 1., 1.));
            Assert::AreEqual(3.0, a.get_mass());
            Assert::AreEqual(2.0, a.get_position().get<0>());
            Assert::AreEqual(2.0, a.get_position().get<1>());
            Assert::AreEqual(2.0, a.get_position().get<2>());
            Assert::AreEqual(1.0, a.get_velocity().get<0>());
            Assert::AreEqual(1.0, a.get_velocity().get<1>());
            Assert::AreEqual(1.0, a.get_velocity().get<2>());
        }

        TEST_METHOD(copy_constructor)
        {
            pe::Body<3> a(3., pe::Position<3>(2., 2., 2.), pe::Velocity<3>(1., 1., 1.));
            pe::Body<3> b(a);
            Assert::AreEqual(3.0, a.get_mass());
            Assert::AreEqual(2.0, a.get_position().get<0>());
            Assert::AreEqual(2.0, a.get_position().get<1>());
            Assert::AreEqual(2.0, a.get_position().get<2>());
            Assert::AreEqual(1.0, a.get_velocity().get<0>());
            Assert::AreEqual(1.0, a.get_velocity().get<1>());
            Assert::AreEqual(1.0, a.get_velocity().get<2>());
            Assert::AreEqual(3.0, b.get_mass());
            Assert::AreEqual(2.0, b.get_position().get<0>());
            Assert::AreEqual(2.0, b.get_position().get<1>());
            Assert::AreEqual(2.0, b.get_position().get<2>());
            Assert::AreEqual(1.0, b.get_velocity().get<0>());
            Assert::AreEqual(1.0, b.get_velocity().get<1>());
            Assert::AreEqual(1.0, b.get_velocity().get<2>());
        }

        TEST_METHOD(move_constructor)
        {
            pe::Body<3> a(3., pe::Position<3>(2., 2., 2.), pe::Velocity<3>(1., 1., 1.));
            pe::Body<3> b(std::move(a));
            Assert::AreEqual(3.0, b.get_mass());
            Assert::AreEqual(2.0, b.get_position().get<0>());
            Assert::AreEqual(2.0, b.get_position().get<1>());
            Assert::AreEqual(2.0, b.get_position().get<2>());
            Assert::AreEqual(1.0, b.get_velocity().get<0>());
            Assert::AreEqual(1.0, b.get_velocity().get<1>());
            Assert::AreEqual(1.0, b.get_velocity().get<2>());
        }

        TEST_METHOD(copy_assignment)
        {
            pe::Body<3> a(3., pe::Position<3>(2., 2., 2.), pe::Velocity<3>(1., 1., 1.));
            pe::Body<3> b;
            b = a;
            Assert::AreEqual(3.0, a.get_mass());
            Assert::AreEqual(2.0, a.get_position().get<0>());
            Assert::AreEqual(2.0, a.get_position().get<1>());
            Assert::AreEqual(2.0, a.get_position().get<2>());
            Assert::AreEqual(1.0, a.get_velocity().get<0>());
            Assert::AreEqual(1.0, a.get_velocity().get<1>());
            Assert::AreEqual(1.0, a.get_velocity().get<2>());
            Assert::AreEqual(3.0, b.get_mass());
            Assert::AreEqual(2.0, b.get_position().get<0>());
            Assert::AreEqual(2.0, b.get_position().get<1>());
            Assert::AreEqual(2.0, b.get_position().get<2>());
            Assert::AreEqual(1.0, b.get_velocity().get<0>());
            Assert::AreEqual(1.0, b.get_velocity().get<1>());
            Assert::AreEqual(1.0, b.get_velocity().get<2>());
        }

        TEST_METHOD(move_assignment)
        {
            pe::Body<3> a(3., pe::Position<3>(2., 2., 2.), pe::Velocity<3>(1., 1., 1.));
            pe::Body<3> b;
            b = std::move(a);
            Assert::AreEqual(3.0, b.get_mass());
            Assert::AreEqual(2.0, b.get_position().get<0>());
            Assert::AreEqual(2.0, b.get_position().get<1>());
            Assert::AreEqual(2.0, b.get_position().get<2>());
            Assert::AreEqual(1.0, b.get_velocity().get<0>());
            Assert::AreEqual(1.0, b.get_velocity().get<1>());
            Assert::AreEqual(1.0, b.get_velocity().get<2>());
        }

        TEST_METHOD(dimension)
        {
            pe::Body<2> a;
            pe::Body<4> b;
            pe::Body<10> c;
            Assert::AreEqual(2U, a.dimension());
            Assert::AreEqual(4U, b.dimension());
            Assert::AreEqual(10U, c.dimension());
        }

        TEST_METHOD(get_set_mass)
        {
            pe::Body<3>a;
            a.set_mass(2.);
            Assert::AreEqual(2., a.get_mass());
        }

        TEST_METHOD(get_set_position)
        {
            pe::Body<3>a;
            a.set_position(pe::Position<3>(2., 1., 3.));
            Assert::AreEqual(2., a.get_position().get<0>());
            Assert::AreEqual(1., a.get_position().get<1>());
            Assert::AreEqual(3., a.get_position().get<2>());
        }

        TEST_METHOD(get_set_velocity)
        {
            pe::Body<3>a;
            a.set_velocity(pe::Velocity<3>(2., 1., 3.));
            Assert::AreEqual(2., a.get_velocity().get<0>());
            Assert::AreEqual(1., a.get_velocity().get<1>());
            Assert::AreEqual(3., a.get_velocity().get<2>());
        }

        TEST_METHOD(apply_force)
        {
            pe::Body<3>a(2., pe::Position<3>(1., 2., 3.), pe::Velocity<3>(10., 20., 30.));
            a.apply_force(pe::Force<3>(1., 2., 3.), 1.);

            pe::Body<3>::component_type v_x = (1. / 2.*1. + 10.);
            pe::Body<3>::component_type x = v_x*1. + 1.;

            pe::Body<3>::component_type v_y = (2. / 2.*1. + 20.);
            pe::Body<3>::component_type y = v_y*1. + 2.;

            pe::Body<3>::component_type v_z = (3. / 2.*1. + 30.);
            pe::Body<3>::component_type z = v_z*1. + 3.;

            Assert::AreEqual(v_x, a.get_velocity().get<0>());
            Assert::AreEqual(v_y, a.get_velocity().get<1>());
            Assert::AreEqual(v_z, a.get_velocity().get<2>());
            Assert::AreEqual(x, a.get_position().get<0>());
            Assert::AreEqual(y, a.get_position().get<1>());
            Assert::AreEqual(z, a.get_position().get<2>());
        }

        TEST_METHOD(collides)
        {
            pe::Position<3> apos{ 0.,10.,0. };
            pe::Position<3> bpos{ 0.,11.,0. };
            pe::Body<3> a(1., apos);
            pe::Body<3> b(1., bpos);

            Assert::IsTrue(a.collides(b, 1.1));
            Assert::IsFalse(a.collides(b));
        }

    };
}
