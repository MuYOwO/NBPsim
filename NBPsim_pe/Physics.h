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
            return Acceleration<_N>(std::move(n.components() / kg));
        }

        template <unsigned _N>
        static Velocity<_N> to_delta_velocity(const Acceleration<_N>& m_s2, pe::time_t delta_s) {
            /**
             * delta_v = a * delta_t
             */
            return Velocity<_N>(std::move(m_s2.components() * delta_s));
        }

        template <unsigned _N>
        static Displacement<_N> to_displacement(const Velocity<_N>& m_s, pe::time_t delta_s) {
            /**
             * s = v * delta_t
             */
            return Displacement<_N>(std::move(m_s.components() * delta_s));
        }

        template <unsigned _N>
        static Force<_N> gravitational_force_magnitude(const Position<_N>& p1, const Position<_N>& p2, pe::mass_t m1, pe::mass_t m2) {
            /// TODO: Implement scalar multiplication and division for each physics Class.
            /// TODO: Implement this function
            return Force<_N>();
        }
    };
}
