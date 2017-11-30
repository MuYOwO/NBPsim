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

        TEST_METHOD(dimension)
        {
            pe::Body<2> a;
            pe::Body<4> b;
            pe::Body<10> c;
            Assert::AreEqual(2U, a.dimension());
            Assert::AreEqual(4U, b.dimension());
            Assert::AreEqual(10U, c.dimension());
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
