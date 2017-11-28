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
    class Displacement
    {
    public:
        using component_type = pe::component_t;
        using vector_t_type = vector_t<_N, component_type>;
        using Displacement_type = Displacement<_N>;
    public:
        Displacement() = default;
        template <class... _Ts> Displacement(_Ts... ts) :m_displacement_components{ ts... } {}
        Displacement(const vector_t_type& displacement_components) :m_displacement_components(displacement_components) {}
        Displacement(vector_t_type&& displacement_components) :m_displacement_components(std::move(displacement_components)) {}

        ~Displacement() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template<unsigned _I> component_type& get() { return m_displacement_components.get<_I>(); }
        template<unsigned _I> const component_type& get() const { return m_displacement_components.get<_I>(); }

        component_type& operator[](unsigned i) { assert(i < _N); return m_displacement_components[i]; }
        const component_type& operator[](unsigned i) const { assert(i < _N); return m_displacement_components[i]; }
    public:
        component_type norm_squared()const {
            return m_displacement_components.norm_squared();
        }
        component_type norm()const {
            return ::sqrt(m_displacement_components.norm_squared());
        }

        Displacement_type& operator+=(const Displacement_type& rhs) {
            m_displacement_components += rhs.m_displacement_components;
            return *this;
        }
        Displacement_type& operator-=(const Displacement_type& rhs) {
            m_displacement_components -= rhs.m_displacement_components;
            return *this;
        }

        Displacement_type opposite()const { Displacement_type v; return v -= *this; }
        Displacement_type operator-()const { return opposite(); }
    public:
        bool operator==(const Displacement_type& rhs)const { return m_displacement_components == rhs.m_displacement_components; }
        bool operator!=(const Displacement_type& rhs)const { return m_displacement_components != rhs.m_displacement_components; }

    protected:
        vector_t_type m_displacement_components;
    };

    template <unsigned _N>
    inline Displacement<_N> operator+(Displacement<_N> lhs, const Displacement<_N>& rhs) {
        return lhs += rhs;
    }

    template <unsigned _N>
    inline Displacement<_N> operator-(Displacement<_N> lhs, const Displacement<_N>& rhs) {
        return lhs -= rhs;
    }
}
