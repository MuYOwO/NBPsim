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
    class Force
    {
    public:
        using component_type = pe::component_t;
        using vector_t_type = vector_t<_N, component_type>;
        using Force_type = Force<_N>;
    public:
        Force() = default;
        template <class... _Ts> Force(_Ts... ts) : m_force_components{ ts... } {}
        Force(const vector_t_type& force_components) :m_force_components(force_components) {}
        Force(vector_t_type&& force_components) :m_force_components(std::move(force_components)) {}

        ~Force() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template<unsigned _I> component_type& get() { return m_force_components.get<_I>(); }
        template<unsigned _I> const component_type& get() const { return m_force_components.get<_I>(); }

        component_type& operator[](unsigned i) { assert(i < _N); return m_force_components[i]; }
        const component_type& operator[](unsigned i) const { assert(i < _N); return m_force_components[i]; }

        vector_t_type& components() { return m_force_components; }
        const vector_t_type& components()const { return m_force_components; }
    public:
        component_type norm_squared()const {
            return m_force_components.norm_squared();
        }
        component_type norm()const {
            return ::sqrt(m_force_components.norm_squared());
        }

        Force_type unit_vector()const {
            return *this / norm();
        }

        Force_type& operator+=(const Force_type& rhs) {
            m_force_components += rhs.m_force_components;
            return *this;
        }
        Force_type& operator-=(const Force_type& rhs) {
            m_force_components -= rhs.m_force_components;
            return *this;
        }

        Force_type& operator*=(const component_type& rhs) {
            m_force_components *= rhs;
            return *this;
        }
        Force_type& operator/=(const component_type& rhs) {
            m_force_components /= rhs;
            return *this;
        }

        Force_type opposite()const { Force_type v; return v -= *this; }
        Force_type operator-()const { return opposite(); }
    public:
        bool operator==(const Force_type& rhs)const { return m_force_components == rhs.m_force_components; }
        bool operator!=(const Force_type& rhs)const { return m_force_components != rhs.m_force_components; }

    protected:
        vector_t_type m_force_components;
    };

    template <unsigned _N>
    inline Force<_N> operator+(Force<_N> lhs, const Force<_N>& rhs) {
        return lhs += rhs;
    }

    template <unsigned _N>
    inline Force<_N> operator-(Force<_N> lhs, const Force<_N>& rhs) {
        return lhs -= rhs;
    }

    template <unsigned _N>
    inline Force<_N> operator*(Force<_N> lhs, const typename Force<_N>::component_type& rhs) {
        return lhs *= rhs;
    }
    template <unsigned _N>
    inline Force<_N> operator*(const typename Force<_N>::component_type& lhs, Force<_N> rhs) {
        return rhs *= lhs;
    }

    template <unsigned _N>
    inline Force<_N> operator/(Force<_N> lhs, const typename Force<_N>::component_type& rhs) {
        return lhs /= rhs;
    }
}
