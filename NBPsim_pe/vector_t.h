#pragma once

#include <array>
#include <cassert>

namespace pe {
    template <unsigned N, typename T>
    class vector_t
    {
    public:
        using component_type = T;
        using reference = component_type&;
        using const_reference = const component_type&;
    public:
        vector_t() :m_components{ 0 } { }
        template <typename... Ts> vector_t(Ts... ts) : m_components{ ts... } { }
        vector_t(const vector_t<N, T>& other) :m_components(other.m_components) {}
        vector_t(vector_t<N, T>&& other) :m_components(std::move(other.m_components)) {}

        ~vector_t() = default;
    public:
        template <unsigned I> reference get() { return std::get<I>(m_components); }
        template <unsigned I> const_reference get() const { return std::get<I>(m_components); }

        reference operator[](unsigned i) { assert(i < N); return m_components[i]; }
        const_reference operator[](unsigned i) const { assert(i < N); return m_components[i]; }

    protected:
        std::array<component_type, N> m_components;
    };
}
