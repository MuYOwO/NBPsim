#pragma once

#include <array>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <xstddef>

namespace pe
{

    /**
     * <xstddef> does not have std::divides.
     *
     * TEMPLATE STRUCT divides
     */
    template<class _Ty = void>
    struct divides
    {	// functor for operator/
        typedef _Ty first_argument_type;
        typedef _Ty second_argument_type;
        typedef _Ty result_type;

        constexpr _Ty operator()(const _Ty& _Left, const _Ty& _Right) const
        {	// apply operator/ to operands
            return (_Left / _Right);
        }
    };

    /**
     * unsigned N: Number of dimensions
     * class T: Component type
     * class T_Equal: Binary predicate that takes two arguments of type T and returns a bool.
     *       Returns true if they are equivalent (same as operator==()).
     * class T_Plus: Binary predicate that takes two arguments of tyep T and returns a T.
     *       Returns the sum of these two arguments (same as operator+()).
     * class T_Minus: Binary predicate that takes two arguments of tyep T and returns a T.
     *       Returns the difference of these two arguments (same as operator-()).
     * class T_Multiplies: Binary predicate that takes two arguments of tyep T and returns a T.
     *       Returns the product of these two arguments (same as operator*()).
     * class T_Divides: Binary predicate that takes two arguments of tyep T and returns a T.
     *       Returns the quotient of these two arguments (same as operator/()).
     */
    template <
        unsigned _N,
        class _T,
        class _T_Equal = std::equal_to<_T>,
        class _T_Plus = std::plus<_T>,
        class _T_Minus = std::minus<_T>,
        class _T_Multiplies = std::multiplies<_T>,
        class _T_Divides = divides<_T>
    >
        class vector_t
    {
    public:
        using component_type = _T;
        using component_equal = _T_Equal;
        using component_plus = _T_Plus;
        using component_minus = _T_Minus;
        using component_multiplies = _T_Multiplies;
        using component_divides = _T_Divides;
        using component_reference = component_type&;
        using const_component_reference = const component_type&;
        using vector_t_type = vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>;

    public:
        vector_t() :m_components{ component_type() } { }
        template <class... _Ts> vector_t(_Ts... ts) : m_components{ ts... } { }
        vector_t(const vector_t_type& other) :m_components(other.m_components) {}
        vector_t(vector_t_type&& other) :m_components(std::move(other.m_components)) {}

        vector_t_type& operator=(const vector_t_type& rhs) {
            if (&rhs != this) {
                std::copy(rhs.m_components.begin(), rhs.m_components.end(), m_components.begin());
            }
            return *this;
        }
        vector_t_type& operator=(vector_t_type&& rhs) {
            assert(&rhs != this);
            std::copy(rhs.m_components.begin(), rhs.m_components.end(), m_components.begin());
            return *this;
        }

        ~vector_t() = default;
    public:
        constexpr unsigned dimension()const { return _N; }

        template <unsigned _I> component_reference get() { return std::get<_I>(m_components); }
        template <unsigned _I> const_component_reference get() const { return std::get<_I>(m_components); }

        component_reference operator[](unsigned i) { assert(i < _N); return m_components[i]; }
        const_component_reference operator[](unsigned i) const { assert(i < _N); return m_components[i]; }
    public:
        component_type norm_squared()const {
            component_type sum = component_type();
            for (const component_type& v : m_components) {
                sum = component_plus()(sum, component_multiplies()(v, v));
            }
            return sum;
        }

        vector_t_type& operator+=(const vector_t_type& rhs) {
            std::transform(m_components.begin(), m_components.end(), rhs.m_components.begin(), m_components.begin(),
                [](const component_type& t1, const component_type& t2)->component_type { return component_plus()(t1, t2); });
            return *this;
        }
        vector_t_type& operator-=(const vector_t_type& rhs) {
            std::transform(m_components.begin(), m_components.end(), rhs.m_components.begin(), m_components.begin(),
                [](const component_type& t1, const component_type& t2)->component_type { return component_minus()(t1, t2); });
            return *this;
        }
        vector_t_type& operator*=(const component_type& c) {
            std::transform(m_components.begin(), m_components.end(), m_components.begin(),
                [&c](const component_type& t)->component_type { return component_multiplies()(t, c); });
            return *this;
        }
        vector_t_type& operator/=(const component_type& c) {
            std::transform(m_components.begin(), m_components.end(), m_components.begin(),
                [&c](const component_type& t)->component_type {return component_divides()(t, c); });
            return *this;
        }

        vector_t_type opposite()const { vector_t_type v; return v -= *this; }
        vector_t_type operator-()const { return opposite(); }
    public:
        bool operator==(const vector_t_type& rhs)const {
            return std::equal(m_components.begin(), m_components.end(), rhs.m_components.begin(), component_equal());
        }
        bool operator!=(const vector_t_type& rhs)const {
            return !operator==(rhs);
        }

    protected:
        std::array<component_type, _N> m_components;
    };

    template <
        unsigned _N,
        class _T,
        class _T_Equal,
        class _T_Plus,
        class _T_Minus,
        class _T_Multiplies,
        class _T_Divides
    >
        inline vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>
        operator+(vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides> lhs, const vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>& rhs) {
        return lhs += rhs;
    }

    template <
        unsigned _N,
        class _T,
        class _T_Equal,
        class _T_Plus,
        class _T_Minus,
        class _T_Multiplies,
        class _T_Divides
    >
        inline vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>
        operator-(vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides> lhs, const vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>& rhs) {
        return lhs -= rhs;
    }

    template <
        unsigned _N,
        class _T,
        class _T_Equal,
        class _T_Plus,
        class _T_Minus,
        class _T_Multiplies,
        class _T_Divides
    >
        inline vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>
        operator*(vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides> lhs, const _T& rhs) {
        return lhs *= rhs;
    }

    template <
        unsigned _N,
        class _T,
        class _T_Equal,
        class _T_Plus,
        class _T_Minus,
        class _T_Multiplies,
        class _T_Divides
    >
        inline vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides>
        operator/(vector_t<_N, _T, _T_Equal, _T_Plus, _T_Minus, _T_Multiplies, _T_Divides> lhs, const _T& rhs) {
        return lhs /= rhs;
    }
}
