#pragma once

#include "NBPsim_pe.h"

#include <cassert>
#include <cmath>
#include "vector_t.h"

namespace pe
{
    /**
     * unsigned _N: Number of dimensions
     */
    template <unsigned _N>
    class Velocity
    {
    public:
        using component_type = pe::component_t;
        using vector_t_type = vector_t<_N, component_type>;
        using Velocity_type = Velocity<_N>;
    public:
        Velocity() = default;
        template <class... _Ts> Velocity(_Ts... ts) :m_velocity_components{ ts... } {}
        Velocity(const vector_t_type& velocity_components) :m_velocity_components(velocity_components) {}
        Velocity(vector_t_type&& velocity_components) :m_velocity_components(std::move(velocity_components)) {}

        ~Velocity() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template<unsigned _I> component_type& get() { return m_velocity_components.get<_I>(); }
        template<unsigned _I> const component_type& get() const { return m_velocity_components.get<_I>(); }

        component_type& operator[](unsigned i) { assert(i < _N); return m_velocity_components[i]; }
        const component_type& operator[](unsigned i) const { assert(i < _N); return m_velocity_components[i]; }

        vector_t_type& components() { return m_velocity_components; }
        const vector_t_type& components()const { return m_velocity_components; }
    public:
        component_type norm_squared()const {
            return m_velocity_components.norm_squared();
        }
        component_type norm()const {
            return ::sqrt(m_velocity_components.norm_squared());
        }

        Velocity_type unit_vector()const {
            return *this / norm();
        }

        Velocity_type& operator+=(const Velocity_type& rhs) {
            m_velocity_components += rhs.m_velocity_components;
            return *this;
        }
        Velocity_type& operator-=(const Velocity_type& rhs) {
            m_velocity_components -= rhs.m_velocity_components;
            return *this;
        }

        Velocity_type& operator*=(const component_type& rhs) {
            m_velocity_components *= rhs;
            return *this;
        }
        Velocity_type& operator/=(const component_type& rhs) {
            m_velocity_components /= rhs;
            return *this;
        }

        Velocity_type opposite()const { Velocity_type v; return v -= *this; }
        Velocity_type operator-()const { return opposite(); }
    public:
        bool operator==(const Velocity_type& rhs)const { return m_velocity_components == rhs.m_velocity_components; }
        bool operator!=(const Velocity_type& rhs)const { return m_velocity_components != rhs.m_velocity_components; }

    protected:
        vector_t_type m_velocity_components;
    };

    template <unsigned _N>
    inline Velocity<_N> operator+(Velocity<_N> lhs, const Velocity<_N>& rhs) {
        return lhs += rhs;
    }

    template <unsigned _N>
    inline Velocity<_N> operator-(Velocity<_N> lhs, const Velocity<_N>& rhs) {
        return lhs -= rhs;
    }

    template <unsigned _N>
    inline Velocity<_N> operator*(Velocity<_N> lhs, const typename Velocity<_N>::component_type& rhs) {
        return lhs *= rhs;
    }
    template <unsigned _N>
    inline Velocity<_N> operator*(const typename Velocity<_N>::component_type& lhs, Velocity<_N> rhs) {
        return rhs *= lhs;
    }

    template <unsigned _N>
    inline Velocity<_N> operator/(Velocity<_N> lhs, const typename Velocity<_N>::component_type& rhs) {
        return lhs /= rhs;
    }
}
