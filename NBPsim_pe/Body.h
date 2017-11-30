#pragma once

#include "NBPsim_pe.h"

#include <cassert>
#include "Force.h"
#include "Physics.h"
#include "Position.h"
#include "Velocity.h"

namespace pe
{
    /**
    * unsigned _N: Number of dimensions
    */
    template <unsigned _N>
    class Body
    {
    public:
        using component_type = pe::component_t;
        using Position_type = Position<_N>;
        using Velocity_type = Velocity<_N>;
        using Body_type = Body<_N>;
    public:
        Body() : Body(1.) {};
        Body(pe::mass_t kg, Position_type m = Position_type(), Velocity_type m_s = Velocity_type()) :
            m_kg(kg), m_m(m), m_m_s(m_s) {
            assert(kg != 0.);
        }
        Body(const Body_type& other) :m_kg(other.m_kg), m_m(other.m_m), m_m_s(other.m_m_s) {}
        Body(Body_type&& other) :m_kg(other.m_kg), m_m(std::move(other.m_m)), m_m_s(std::move(other.m_m_s)) {}

        Body_type& operator=(const Body_type& rhs) {
            if (&rhs != this) {
                m_kg = rhs.m_kg;
                m_m = rhs.m_m;
                m_m_s = rhs.m_m_s;
            }
            return *this;
        }
        Body_type& operator=(Body_type&& rhs) {
            assert(&rhs != this);
            m_kg = rhs.m_kg;
            m_m = std::move(rhs.m_m);
            m_m_s = std::move(rhs.m_m_s);
            return *this;
        }

        ~Body() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        pe::mass_t get_mass()const { return m_kg; }
        const Position_type& get_position()const { return m_m; }
        const Velocity_type& get_velocity()const { return m_m_s; }

        void set_mass(pe::mass_t kg) { assert(kg != 0.); m_kg = kg; }
        void set_position(Position_type m) { m_m = m; }
        void set_velocity(Velocity_type m_s) { m_m_s = m_s; }
    public:
        void apply_force(const Force<_N>& n, pe::time_t delta_s) {
            m_m_s += Physics::to_delta_velocity(Physics::to_acceleration(n, m_kg), delta_s);
            m_m += Physics::to_displacement(m_m_s, delta_s);
        }

        bool collides(const Body_type& other, component_type epsilon = component_type())const {
            return m_m.collides(other.m_m, epsilon);
        }

    protected:
        pe::mass_t m_kg;
        Position_type m_m;
        Velocity_type m_m_s;
    };
}
