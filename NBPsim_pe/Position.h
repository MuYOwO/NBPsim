#pragma once

#include "NBPsim_pe.h"

#include <cassert>
#include "Displacement.h"
#include "vector_t.h"

namespace pe
{
    /**
     * unsigned _N: Number of dimensions
     */
    template <unsigned _N>
    class Position
    {
    public:
        using component_type = pe::component_t;
        using vector_t_type = vector_t<_N, component_type>;
        using Position_type = Position<_N>;
    public:
        Position() = default;
        template <class... _Ts> Position(_Ts... ts) :m_position_components{ ts... } {}
        Position(const vector_t_type& position_components) :m_position_components(position_components) {}
        Position(vector_t_type&& position_components) :m_position_components(std::move(position_components)) {}

        ~Position() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template<unsigned _I> component_type& get() { return m_position_components.get<_I>(); }
        template<unsigned _I> const component_type& get() const { return m_position_components.get<_I>(); }

        component_type& operator[](unsigned i) { assert(i < _N); return m_position_components[i]; }
        const component_type& operator[](unsigned i) const { assert(i < _N); return m_position_components[i]; }

        vector_t_type& components() { return m_position_components; }
        const vector_t_type& components()const { return m_position_components; }
    public:
        Position_type& operator+=(const Displacement<_N>& rhs) {
            m_position_components += rhs.components();
            return *this;
        }
        Position_type& operator-=(const Displacement<_N>& rhs) {
            m_position_components -= rhs.components();
            return *this;
        }
    public:
        bool collides(const Position_type& other, component_type epsilon = component_type())const {
            return (m_position_components - other.m_position_components).norm_squared() < epsilon;
        }
        bool operator==(const Position_type& rhs)const { return m_position_components == rhs.m_position_components; }
        bool operator!=(const Position_type& rhs)const { return m_position_components != rhs.m_position_components; }

    protected:
        vector_t_type m_position_components;
    };

    template <unsigned _N>
    inline Position<_N> operator+(Position<_N> lhs, const Displacement<_N>& rhs) {
        return lhs += rhs;
    }

    template <unsigned _N>
    inline Position<_N> operator+(const Displacement<_N>& lhs, Position<_N> rhs) {
        return rhs += lhs;
    }

    /**
     * Only supports Position - Displacement.
     */
    template <unsigned _N>
    inline Position<_N> operator-(Position<_N> lhs, const Displacement<_N>& rhs) {
        return lhs -= rhs;
    }

    template <unsigned _N>
    inline Displacement<_N> operator-(const Position<_N>& lhs, const Position<_N>& rhs) {
        return Displacement<_N>(lhs.components() - rhs.components());
    }
}
