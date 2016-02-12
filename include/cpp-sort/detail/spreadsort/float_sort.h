//Templated Spreadsort-based implementation of float_sort and float_mem_cast

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
float_mem_cast fix provided by:
Scott McMurray
*/

// Modified in 2015-2016 by Morwenn for inclusion into cpp-sort

#ifndef CPPSORT_DETAIL_SPREADSORT_FLOAT_SORT_H_
#define CPPSORT_DETAIL_SPREADSORT_FLOAT_SORT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstring>
#include <functional>
#include <limits>
#include <cpp-sort/utility/functional.h>
#include "detail/constants.h"
#include "detail/float_sort.h"
#include "../pdqsort.h"

namespace cppsort
{
namespace detail
{
namespace spreadsort
{
  /*!
  \brief Casts a float to the specified integer type.

  \tparam Data_type Floating-point IEEE 754/IEC559 type.
  \tparam Cast_type Integer type (same size) to which to cast.

  \par Example:
  \code
  struct rightshift {
    int operator()(const DATA_TYPE &x, const unsigned offset) const {
      return float_mem_cast<KEY_TYPE, CAST_TYPE>(x.key) >> offset;
    }
  };
  \endcode
  */
  template<class Data_type, class Cast_type>
  auto float_mem_cast(const Data_type & data)
      -> Cast_type
  {
    // Only cast IEEE floating-point numbers, and only to a same-sized integer.
    static_assert(sizeof(Cast_type) == sizeof(Data_type), "");
    static_assert(std::numeric_limits<Data_type>::is_iec559, "");
    static_assert(std::numeric_limits<Cast_type>::is_integer, "");
    Cast_type result;
    std::memcpy(&result, &data, sizeof(Cast_type));
    return result;
  }


  /*!
    \brief @c float_sort with casting to the appropriate size.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_float_sort.htm"> windows_float_sort</a>
   \n
   <a href="../../doc/graph/osx_float_sort.htm"> osx_float_sort</a>



   \par A simple example of sorting some floating-point is:
   \code
     vector<float> vec;
     vec.push_back(1.0);
     vec.push_back(2.3);
     vec.push_back(1.3);
     spreadsort(vec.begin(), vec.end());
   \endcode
   \par The sorted vector contains ascending values "1.0 1.3 2.3".

  */
  template<class RandomAccessIter>
  auto float_sort(RandomAccessIter first, RandomAccessIter last)
      -> void
  {
    if (last - first < detail::min_sort_size)
      pdqsort(first, last, std::less<>{}, utility::identity{});
    else
      detail::float_sort(first, last);
  }

  /*!
    \brief Floating-point sort algorithm using random access iterators with just right-shift functor.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.
    \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.

  */
  template<class RandomAccessIter, class Right_shift>
  auto float_sort(RandomAccessIter first, RandomAccessIter last,
                  Right_shift rshift)
      -> void
  {
    if (last - first < detail::min_sort_size)
      pdqsort(first, last, std::less<>{}, utility::identity{});
    else
      detail::float_sort(first, last, rshift(*first, 0), rshift);
  }


  /*!
   \brief Float sort algorithm using random access iterators with both right-shift and user-defined comparison operator.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
  */

  template<class RandomAccessIter, class Right_shift, class Compare>
  auto float_sort(RandomAccessIter first, RandomAccessIter last,
                  Right_shift rshift, Compare comp)
      -> void
  {
    if (last - first < detail::min_sort_size)
      pdqsort(first, last, comp, utility::identity{});
    else
      detail::float_sort(first, last, rshift(*first, 0), rshift, comp);
  }
}}}

#endif // CPPSORT_DETAIL_SPREADSORT_FLOAT_SORT_H_
