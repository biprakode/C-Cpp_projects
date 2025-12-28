#ifndef PADDING_H
#define PADDING_H

#include <cstddef>

class Padder {
public:
    static const size_t calculate_padding(const size_t base_adr , const size_t alignment) {
        const size_t multiplier = base_adr / alignment + 1;
        const size_t aligned_adr = multiplier * alignment;
        const size_t padding = aligned_adr - base_adr;
        return padding;
    }

    static const size_t calculate_padding_header(const size_t base_adr , const size_t alignment , const size_t header_size) {
        size_t padding = calculate_padding(base_adr , alignment);
        size_t need = header_size;

        if(padding < need) { // header no fit
            need -= padding;
            if(need % alignment > 0) {
                padding += alignment * (1 + (need / alignment));
            }else {
                padding += alignment * ((need / alignment));
            }
        }
        return padding;
    }
};

#endif