// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3

#include <cstring>
#include <string>
#include <vector>
#include <range/v3/core.hpp>
#include <range/v3/view/move.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/utility/iterator.hpp>
#include "../simple_test.hpp"
#include "../test_utils.hpp"

int main()
{
    using namespace ranges;
    std::vector<std::string> vs{"'allo", "'allo", "???"};

    auto x = vs | view::move;
    CONCEPT_ASSERT(Same<bounded_range_concept_t<decltype(x)>, concepts::BoundedRange>());
    CONCEPT_ASSERT(Same<sized_range_concept_t<decltype(x)>, concepts::SizedRange>());
    ::models<concepts::BoundedRange>(x);
    ::models<concepts::SizedRange>(x);
    ::models<concepts::InputIterator>(x.begin());
    ::models_not<concepts::ForwardIterator>(x.begin());
    using I = decltype(x.begin());
    CONCEPT_ASSERT(Same<iterator_concept_t<I>, concepts::InputIterator>());
    CONCEPT_ASSERT(Same<iterator_category_t<I>, ranges::input_iterator_tag>());

    CHECK(std::strcmp(x.begin()->c_str(), "'allo") == 0);

    std::vector<std::string> vs2(x.begin(), x.end());
    static_assert(std::is_same<std::string&&, decltype(*x.begin())>::value, "");
    ::check_equal(vs2, {"'allo", "'allo", "???"});
    ::check_equal(vs, {"", "", ""});

    return test_result();
}
