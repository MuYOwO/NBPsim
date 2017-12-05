#pragma once

#include "NBPsim_pe.h"

#include "Acceleration.h"
#include "Displacement.h"
#include "Force.h"
#include "Position.h"
#include "vector_t.h"
#include "Velocity.h"

namespace pe
{
    /**
     * unsigned _N: Number of dimensions
     */
    class Physics
    {
    public:
        Physics() = delete;
        ~Physics() = delete;
    public:
        static constexpr pe::universal_t G = 6.674E-11; /* m3 kg-1 s-2 */
    public:
        template <unsigned _N>
        static Acceleration<_N> to_acceleration(const Force<_N>& n, pe::mass_t kg) {
            /**
             * a = F / m
             */
            return Acceleration<_N>(std::move((n / kg).components()));
        }

        template <unsigned _N>
        static Velocity<_N> to_delta_velocity(const Acceleration<_N>& m_s2, pe::time_t delta_s) {
            /**
             * delta_v = a * delta_t
             */
            return Velocity<_N>(std::move((m_s2 * delta_s).components()));
        }

        template <unsigned _N>
        static Displacement<_N> to_displacement(const Velocity<_N>& m_s, pe::time_t delta_s) {
            /**
             * s = v * delta_t
             */
            return Displacement<_N>(std::move((m_s * delta_s).components()));
        }

        template <unsigned _N>
        static pe::universal_t gravitational_force_magnitude(const Position<_N>& m1, const Position<_N>& m2, pe::mass_t kg1, pe::mass_t kg2) {
            /**
             * F = G * m1*m2 / r^2
             */
            Displacement<_N> delta_m = m1 - m2;
            return G * kg1*kg2 / delta_m.norm_squared();
        }
    };
}
