#pragma once

#include "NBPsim_pe.h"

#include "Acceleration.h"
#include "Displacement.h"
#include "Force.h"
#include "vector_t.h"
#include "Velocity.h"

namespace pe
{
    /**
    * unsigned _N: Number of dimensions
    */
    template <unsigned _N>
    class Physics
    {
    public:
        using vector_t_type = vector_t<_N, pe::component_t>;
        using Force_type = Force<_N>;
        using Acceleration_type = Acceleration<_N>;
        using Velocity_type = Velocity<_N>;
        using Displacement_type = Displacement<_N>;
    public:
        Physics() = delete;
        ~Physics() = delete;
    public:
        static Acceleration_type to_acceleration(const Force_type& n, pe::mass_t kg) {
            /**
             * a = F / m
             */
            return Acceleration_type(std::move(n.components() / kg));
        }

        static Velocity_type to_delta_velocity(const Acceleration_type& m_s2, pe::time_t delta_s) {
            /**
             * delta_v = a * delta_t
             */
            return Velocity_type(std::move(m_s2.components() * delta_s));
        }

        static Displacement_type to_displacement(const Velocity_type& m_s, pe::time_t delta_s) {
            /**
             * s = v * delta_t
             */
            return Displacement_type(std::move(m_s.components() * delta_s));
        }
    };
}
