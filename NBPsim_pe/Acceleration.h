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
    class Acceleration
    {
    public:
        using component_type = pe::component_t;
        using vector_t_type = vector_t<_N, component_type>;
        using Acceleration_type = Acceleration<_N>;
    public:
        Acceleration() = default;
        template <class... _Ts> Acceleration(_Ts... ts) :m_acceleration_components{ ts... } {}
        Acceleration(const vector_t_type& acceleration_components) :m_acceleration_components(acceleration_components) {}
        Acceleration(vector_t_type&& acceleration_components) :m_acceleration_components(std::move(acceleration_components)) {}

        ~Acceleration() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template<unsigned _I> component_type& get() { return m_acceleration_components.get<_I>(); }
        template<unsigned _I> const component_type& get() const { return m_acceleration_components.get<_I>(); }

        component_type& operator[](unsigned i) { assert(i < _N); return m_acceleration_components[i]; }
        const component_type& operator[](unsigned i) const { assert(i < _N); return m_acceleration_components[i]; }

        vector_t_type& components() { return m_acceleration_components; }
        const vector_t_type& components()const { return m_acceleration_components; }
    public:
        component_type norm_squared()const {
            return m_acceleration_components.norm_squared();
        }
        component_type norm()const {
            return ::sqrt(m_acceleration_components.norm_squared());
        }

        Acceleration_type unit_vector()const {
            return *this / norm();
        }

        Acceleration_type& operator+=(const Acceleration_type& rhs) {
            m_acceleration_components += rhs.m_acceleration_components;
            return *this;
        }
        Acceleration_type& operator-=(const Acceleration_type& rhs) {
            m_acceleration_components -= rhs.m_acceleration_components;
            return *this;
        }

        Acceleration_type& operator*=(const component_type& rhs) {
            m_acceleration_components *= rhs;
            return *this;
        }
        Acceleration_type& operator/=(const component_type& rhs) {
            m_acceleration_components /= rhs;
            return *this;
        }

        Acceleration_type opposite()const { Acceleration_type v; return v -= *this; }
        Acceleration_type operator-()const { return opposite(); }
    public:
        bool operator==(const Acceleration_type& rhs)const { return m_acceleration_components == rhs.m_acceleration_components; }
        bool operator!=(const Acceleration_type& rhs)const { return m_acceleration_components != rhs.m_acceleration_components; }

    protected:
        vector_t_type m_acceleration_components;
    };

    template <unsigned _N>
    inline Acceleration<_N> operator+(Acceleration<_N> lhs, const Acceleration<_N>& rhs) {
        return lhs += rhs;
    }

    template <unsigned _N>
    inline Acceleration<_N> operator-(Acceleration<_N> lhs, const Acceleration<_N>& rhs) {
        return lhs -= rhs;
    }

    template <unsigned _N>
    inline Acceleration<_N> operator*(Acceleration<_N> lhs, const typename Acceleration<_N>::component_type& rhs) {
        return lhs *= rhs;
    }
    template <unsigned _N>
    inline Acceleration<_N> operator*(const typename Acceleration<_N>::component_type& lhs, Acceleration<_N> rhs) {
        return rhs *= lhs;
    }

    template <unsigned _N>
    inline Acceleration<_N> operator/(Acceleration<_N> lhs, const typename Acceleration<_N>::component_type& rhs) {
        return lhs /= rhs;
    }
}
