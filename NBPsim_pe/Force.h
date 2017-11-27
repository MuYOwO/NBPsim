#pragma once

#include "NBPsim_pe.h"

#include "vector_t.h"

namespace pe {
    /**
     * unsigned N: Number of dimensions
     */
    template <unsigned _N>
    class Force
    {
    public:
        using vector_t_type = vector_t<_N, data_t>;
    public:
        Force() {}
        ~Force() = default;
    };
}
