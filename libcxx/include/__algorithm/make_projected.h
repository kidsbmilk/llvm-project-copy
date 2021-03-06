//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___ALGORITHM_MAKE_PROJECTED_H
#define _LIBCPP___ALGORITHM_MAKE_PROJECTED_H

#include <__concepts/same_as.h>
#include <__config>
#include <__functional/identity.h>
#include <__functional/invoke.h>
#include <__utility/forward.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

#if _LIBCPP_STD_VER > 17 && !defined(_LIBCPP_HAS_NO_INCOMPLETE_RANGES)

_LIBCPP_BEGIN_NAMESPACE_STD

namespace ranges {

template <class _Comp, class _Proj>
_LIBCPP_HIDE_FROM_ABI constexpr static
decltype(auto) __make_projected_comp(_Comp& __comp, _Proj& __proj) {
  if constexpr (same_as<_Proj, identity>) {
    // Avoid creating the lambda and just use the pristine comparator -- for certain algorithms, this would enable
    // optimizations that rely on the type of the comparator.
    return __comp;

  } else {
    return [&](auto&& __lhs, auto&& __rhs) {
      return std::invoke(__comp,
                        std::invoke(__proj, std::forward<decltype(__lhs)>(__lhs)),
                        std::invoke(__proj, std::forward<decltype(__rhs)>(__rhs)));
    };
  }
}

} // namespace ranges

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP_STD_VER > 17 && !defined(_LIBCPP_HAS_NO_INCOMPLETE_RANGES)

#endif // _LIBCPP___ALGORITHM_MAKE_PROJECTED_H
