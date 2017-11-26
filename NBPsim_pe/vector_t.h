#pragma once

#include <array>
#include <algorithm>
#include <cassert>

#include <unordered_map>
namespace pe {
    /**
     * unsigned N: Number of dimensions
     * class T: Component type
     * class T_Equal: Binary predicate that takes two arguments of type T and returns a bool.
     *       Returns true if they are equivalent (same as operator==()).
     */
    template <unsigned N, class T, class T_Equal = std::equal_to<T>>
    class vector_t
    {
    public:
        using component_type = T;
        using component_equal = T_Equal;
        using component_reference = component_type&;
        using const_component_reference = const component_type&;
        using vector_t_type = vector_t<N, T, T_Equal>;

    public:
        vector_t() :m_components{ 0 } { }
        template <class... Ts> vector_t(Ts... ts) : m_components{ ts... } { }
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
        constexpr unsigned dimension()const { return N; }

        template <unsigned I> component_reference get() { return std::get<I>(m_components); }
        template <unsigned I> const_component_reference get() const { return std::get<I>(m_components); }

        component_reference operator[](unsigned i) { assert(i < N); return m_components[i]; }
        const_component_reference operator[](unsigned i) const { assert(i < N); return m_components[i]; }
    public:
        vector_t_type& operator+=(const vector_t_type& rhs) {
            std::transform(m_components.begin(), m_components.end(), rhs.m_components.begin(), m_components.begin(),
                [](T t1, T t2)-> T { return t1 + t2; });
            return *this;
        }
        vector_t_type& operator-=(const vector_t_type& rhs) {
            std::transform(m_components.begin(), m_components.end(), rhs.m_components.begin(), m_components.begin(),
                [](T t1, T t2)-> T { return t1 - t2; });
            return *this;
        }
    public:
        bool operator==(const vector_t_type& rhs)const {
            return std::equal(m_components.begin(), m_components.end(), rhs.m_components.begin(), component_equal());
        }
        bool operator!=(const vector_t_type& rhs)const {
            return !operator==(rhs);
        }

    protected:
        std::array<component_type, N> m_components;
    };

    template <unsigned N, class T, class T_Equal>
    inline vector_t<N, T, T_Equal> operator+(vector_t<N, T, T_Equal> lhs, const vector_t<N, T, T_Equal>& rhs) {
        return lhs += rhs;
    }

    template <unsigned N, class T, class T_Equal>
    inline vector_t<N, T, T_Equal> operator-(vector_t<N, T, T_Equal> lhs, const vector_t<N, T, T_Equal>& rhs) {
        return lhs -= rhs;
    }
}
