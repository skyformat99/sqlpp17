#pragma once

/*
Copyright (c) 2017 - 2018, Roland Bock
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

#include <sqlpp17/clause/from.h>
#include <sqlpp17/clause/where.h>
#include <sqlpp17/clause_fwd.h>
#include <sqlpp17/to_sql_name.h>
#include <sqlpp17/type_traits.h>
#include <sqlpp17/wrong.h>

namespace sqlpp
{
  namespace clause
  {
    struct command
    {
    };
  }  // namespace clause

  struct command_t
  {
    std::string _command;
  };

  template<>
  struct nodes_of<command_t>
  {
    using type = type_vector<>;
  };

  template<>
  constexpr auto clause_tag<command_t> = clause::command{};

  template <typename Statement>
  class clause_base<command_t, Statement>
  {
  public:
    template <typename OtherStatement>
    clause_base(const clause_base<command_t, OtherStatement>& t) : _command(t._comand)
    {
    }

    clause_base(std::string command) : _command(command)
    {
    }

    std::string _command;
  };

  template<>
  constexpr auto is_result_clause_v<command_t> = true;

  template<>
  struct clause_result_type<command_t>
  {
    using type = execute_result;
  };

  template <typename Context, typename Statement>
  [[nodiscard]] auto to_sql_string(Context& context, const clause_base<command_t, Statement>& t)
  {
    return t._command;
  }

  [[nodiscard]] auto command(std::string command)
  {
    return statement<command_t>{command};
  }
}  // namespace sqlpp
