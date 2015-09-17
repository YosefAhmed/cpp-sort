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
#include <algorithm>
#include <ctime>
#include <iterator>
#include <list>
#include <random>
#include <catch.hpp>
#include <cpp-sort/adapters/self_sort_adapter.h>
#include <cpp-sort/sorters/pdq_sorter.h>
#include <cpp-sort/sorters/quick_sorter.h>
#include <cpp-sort/sort.h>

// This class can sort itself but its sort method
// does not accept a comparator
struct non_comparison_self_sortable
{
    std::list<int> elements;

    template<typename... Args>
    non_comparison_self_sortable(Args... args):
        elements(args...)
    {}

    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }
    auto begin() const { return elements.begin(); }
    auto end() const { return elements.end(); }

    // No comparison function
    auto sort() { elements.sort(); }
};

TEST_CASE( "self-sortable object without comparison",
           "[self_sort_adapter][no_compare]" )
{
    // Pseudo-random number engine
    std::mt19937_64 engine(std::time(nullptr));

    // Collection to sort
    non_comparison_self_sortable collection(80);

    SECTION( "without a comparator" )
    {
        // Make sure the sort method is used when no
        // comparator is given

        using sorter = cppsort::self_sort_adapter<
            cppsort::pdq_sorter
        >;

        // Fill the collection
        std::vector<int> tmp(std::distance(std::begin(collection), std::end(collection)));
        std::iota(std::begin(tmp), std::end(tmp), 0);
        std::shuffle(std::begin(tmp), std::end(tmp), engine);
        std::copy(std::begin(tmp), std::end(tmp), std::begin(collection));

        // Sort and check it's sorted
        cppsort::sort(collection, sorter{});
        CHECK( std::is_sorted(std::begin(collection), std::end(collection)) );
    }

    SECTION( "with a comparator" )
    {
        // Make sure the fallback sorter is used when a
        // comparator is given

        using sorter = cppsort::self_sort_adapter<
            cppsort::quick_sorter
        >;

        // Fill the collection
        std::vector<int> tmp(std::distance(std::begin(collection), std::end(collection)));
        std::iota(std::begin(tmp), std::end(tmp), 0);
        std::shuffle(std::begin(tmp), std::end(tmp), engine);
        std::copy(std::begin(tmp), std::end(tmp), std::begin(collection));

        // Sort and check it's sorted
        cppsort::sort(collection, sorter{}, std::less<>{});
        CHECK( std::is_sorted(std::begin(collection), std::end(collection)) );
    }
}
