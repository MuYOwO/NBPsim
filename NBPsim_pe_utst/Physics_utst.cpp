#include "stdafx.h"
#include "CppUnitTest.h"

#include "NBPsim_pe.h"

#include "Acceleration.h"
#include "Displacement.h"
#include "Force.h"
#include "Physics.h"
#include "Position.h"
#include "vector_t.h"
#include "Velocity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NBPsim_pe_utst
{
    TEST_CLASS(Physics_utst)
    {
    public:

        TEST_METHOD(force_to_acceleration)
        {
            pe::Force<3> n{ 4.,6.,8. };
            pe::mass_t kg = 2.;
            pe::Acceleration<3> m_s2_result = pe::Physics::to_acceleration(n, kg);

            pe::Acceleration<3> m_s2_expected{ 2.,3.,4. };
            Assert::IsTrue(m_s2_expected == m_s2_result);
        }

        TEST_METHOD(acceleration_to_delta_velocity)
        {
            pe::Acceleration<3> m_s2{ 4.,6.,8. };
            pe::time_t s = 2.;
            pe::Velocity<3> m_s_result = pe::Physics::to_delta_velocity(m_s2, s);

            pe::Velocity<3> m_s_expected{ 8.,12.,16. };
            Assert::IsTrue(m_s_expected == m_s_result);
        }

        TEST_METHOD(velocity_to_displacement)
        {
            pe::Velocity<3> m_s{ 4.,6.,8. };
            pe::time_t s = 2.;
            pe::Displacement<3> m_result = pe::Physics::to_displacement(m_s, s);

            pe::Displacement<3> m_expected{ 8.,12.,16. };
            Assert::IsTrue(m_expected == m_result);
        }

        TEST_METHOD(gravitational_force_magnitude)
        {
            pe::Position<3> p1{ 100.,200.,300. };
            pe::Position<3> p2{ 200.,400.,600. };

            pe::mass_t kg1 = 200.;
            pe::mass_t kg2 = 400.;

            pe::universal_t r2 = ::pow(200. - 100., 2.) + ::pow(400. - 200., 2.) + ::pow(600. - 300., 2.);
            pe::universal_t expected = pe::Physics::G * 200. * 400. / r2;

            Assert::AreEqual(expected, pe::Physics::gravitational_force_magnitude(p1, p2, kg1, kg2));
        }
    };
}
