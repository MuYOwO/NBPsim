#pragma once

#include "NBPsim_pe.h"

#include <cassert>
#include <cmath>
#include "vector_t.h"

namespace pe
{
    /**
     * unsigned N: Number of dimensions
     */
    template <unsigned _N>
    class Force
    {
    public:
        using vector_t_type = vector_t<_N, value_t>;
        using Force_type = Force<_N>;
    public:
        Force() = default;
        template <class... _Ts> Force(_Ts... ts) : m_force_components{ ts... } {}
        Force(const vector_t_type& force_components) :m_force_components(force_components) {}
        Force(vector_t_type&& force_components) :m_force_components(std::move(force_components)) {}

        ~Force() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template <unsigned _I> value_t& get() { return m_force_components.get<_I>(); }
        template <unsigned _I> const value_t& get() const { return m_force_componentsget<_I>(); }

        value_t& operator[](unsigned i) { assert(i < _N); return m_force_components[i]; }
        const value_t& operator[](unsigned i) const { assert(i < _N); return m_force_components[i]; }
    public:
        value_t norm_squared()const {
            return m_force_components.norm_squared();
        }
        value_t norm()const {
            return ::sqrt(m_force_components.norm_squared());
        }

        Force_type& operator+=(const Force_type& rhs) {
            m_force_components += rhs.m_force_components;
            return *this;
        }
        Force_type& operator-=(const Force_type& rhs) {
            m_force_components -= rhs.m_force_components;
            return *this;
        }

        Force_type opposite()const { Force_type v; return v -= *this; }
        Force_type operator-()const { return opposite(); }

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
}