#pragma once

/*
Copyright (c) 2016 - 2017, Roland Bock
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>

#include <sqlpp17/type_traits.h>

namespace sqlpp
{
  template <typename DbConnection, typename Object>
  [[nodiscard]] auto to_sql_name(const DbConnection& connection, const Object& object) -> std::string
  {
    if constexpr (std::is_base_of_v<::sqlpp::spec_base, Object>)
    {
      return std::string(Object::_sqlpp_name_tag::name);
    }
    else if constexpr (std::is_base_of_v<::sqlpp::name_tag_base, Object>)
    {
      return std::string(Object::name);
    }
    else if constexpr (not std::is_same_v<name_tag_of_t<Object>, none_t>)
    {
      return name_tag_of_t<Object>::name;
    }
    else
    {
      static_assert(
          wrong<Object>,
          "to_sql_name() is expecting a named expression (e.g. column, table), or a column/table spec, or a name tag");
    }
  }
}  // namespace sqlpp