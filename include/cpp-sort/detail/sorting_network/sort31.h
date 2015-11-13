/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Morwenn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CPPSORT_DETAIL_SORTING_NETWORK_SORT31_H_
#define CPPSORT_DETAIL_SORTING_NETWORK_SORT31_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <functional>
#include "../swap_if.h"

namespace cppsort
{
namespace detail
{
    template<>
    struct sorting_network_sorter_impl<31u>
    {
        template<
            typename RandomAccessIterator,
            typename Compare = std::less<>
        >
        auto operator()(RandomAccessIterator first, RandomAccessIterator, Compare compare={}) const
            -> void
        {
            sorting_network_sorter<16u>{}(first, first+16u, compare);
            sorting_network_sorter<15u>{}(first+16u, first+31u, compare);

            swap_if(first[0u], first[16u], compare);
            swap_if(first[8u], first[24u], compare);
            swap_if(first[8u], first[16u], compare);
            swap_if(first[4u], first[20u], compare);
            swap_if(first[12u], first[28u], compare);
            swap_if(first[12u], first[20u], compare);
            swap_if(first[4u], first[8u], compare);
            swap_if(first[12u], first[16u], compare);
            swap_if(first[20u], first[24u], compare);
            swap_if(first[2u], first[18u], compare);
            swap_if(first[10u], first[26u], compare);
            swap_if(first[10u], first[18u], compare);
            swap_if(first[6u], first[22u], compare);
            swap_if(first[14u], first[30u], compare);
            swap_if(first[14u], first[22u], compare);
            swap_if(first[6u], first[10u], compare);
            swap_if(first[14u], first[18u], compare);
            swap_if(first[22u], first[26u], compare);
            swap_if(first[2u], first[4u], compare);
            swap_if(first[6u], first[8u], compare);
            swap_if(first[10u], first[12u], compare);
            swap_if(first[14u], first[16u], compare);
            swap_if(first[18u], first[20u], compare);
            swap_if(first[22u], first[24u], compare);
            swap_if(first[26u], first[28u], compare);
            swap_if(first[1u], first[17u], compare);
            swap_if(first[9u], first[25u], compare);
            swap_if(first[9u], first[17u], compare);
            swap_if(first[5u], first[21u], compare);
            swap_if(first[13u], first[29u], compare);
            swap_if(first[13u], first[21u], compare);
            swap_if(first[5u], first[9u], compare);
            swap_if(first[13u], first[17u], compare);
            swap_if(first[21u], first[25u], compare);
            swap_if(first[3u], first[19u], compare);
            swap_if(first[11u], first[27u], compare);
            swap_if(first[11u], first[19u], compare);
            swap_if(first[7u], first[23u], compare);
            swap_if(first[15u], first[23u], compare);
            swap_if(first[7u], first[11u], compare);
            swap_if(first[15u], first[19u], compare);
            swap_if(first[23u], first[27u], compare);
            swap_if(first[3u], first[5u], compare);
            swap_if(first[7u], first[9u], compare);
            swap_if(first[11u], first[13u], compare);
            swap_if(first[15u], first[17u], compare);
            swap_if(first[19u], first[21u], compare);
            swap_if(first[23u], first[25u], compare);
            swap_if(first[27u], first[29u], compare);
            swap_if(first[1u], first[2u], compare);
            swap_if(first[3u], first[4u], compare);
            swap_if(first[5u], first[6u], compare);
            swap_if(first[7u], first[8u], compare);
            swap_if(first[9u], first[10u], compare);
            swap_if(first[11u], first[12u], compare);
            swap_if(first[13u], first[14u], compare);
            swap_if(first[15u], first[16u], compare);
            swap_if(first[17u], first[18u], compare);
            swap_if(first[19u], first[20u], compare);
            swap_if(first[21u], first[22u], compare);
            swap_if(first[23u], first[24u], compare);
            swap_if(first[25u], first[26u], compare);
            swap_if(first[27u], first[28u], compare);
            swap_if(first[29u], first[30u], compare);
        }
    };
}}

#endif // CPPSORT_DETAIL_SORTING_NETWORK_SORT31_H_
