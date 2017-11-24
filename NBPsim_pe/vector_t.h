#pragma once

#include <array>

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

        ~vector_t() = default;
    public:
        template <unsigned I> reference get() { return std::get<I>(m_components); }
        template <unsigned I> const_reference get() const { return std::get<I>(m_components); }

        // reference operator[](unsigned i);
        // const_reference operator[](unsigned i) const;

    protected:
        std::array<component_type, N> m_components;
    };
}
