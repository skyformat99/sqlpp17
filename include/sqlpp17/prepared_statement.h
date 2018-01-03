#pragma once

/*
Copyright (c) 2017, Roland Bock
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

#include <sqlpp17/algorithm.h>
#include <sqlpp17/bad_statement.h>
#include <sqlpp17/clause_fwd.h>
#include <sqlpp17/detail/statement_constructor_arg.h>
#include <sqlpp17/result.h>
#include <sqlpp17/succeeded.h>
#include <sqlpp17/type_traits.h>
#include <sqlpp17/wrapped_static_assert.h>

namespace sqlpp::detail
{
  struct runner
  {
    template <typename T>
    decltype(auto) operator()(T& t) const
    {
      return t.run();
    }
  };
  constexpr auto run = runner{};
}  // namespace sqlpp::detail
namespace sqlpp
{
  template <typename ResultBase, typename Handle, typename = void>
  class prepared_statement_t
  {
    Handle _handle;

    friend detail::runner;

    auto run()
    {
      return _handle.run();
    }

  public:
    prepared_statement_t([[maybe_unused]] const ResultBase& result_base, Handle handle) : _handle(std::move(handle))
    {
    }
  };

  template <typename ResultBase, typename Handle>
  class prepared_statement_t<ResultBase, Handle, std::enable_if_t<has_result_row_v<ResultBase>>>
  {
    Handle _handle;
    using result_type = ::sqlpp::result_t<result_row_of_t<ResultBase>, decltype(_handle.run())>;

    result_type _result;

    friend detail::runner;

    decltype(auto) run()
    {
      _result = result_type{_handle.run()};
      return *this;
    }

  public:
    prepared_statement_t([[maybe_unused]] const ResultBase& result_base, Handle handle)
        : _handle(std::move(handle)){}

              [[nodiscard]] decltype(auto) begin()
    {
      return _result.begin();
    }

    [[nodiscard]] constexpr decltype(auto) end() const
    {
      return _result.end();
    }

    [[nodiscard]] decltype(auto) empty() const { return _result.empty(); }

        [[nodiscard]] decltype(auto) front() const
    {
      return _result.front();
    }

    auto pop_front() -> void
    {
      _result.pop_front();
    }
  };

  template <typename ResultBase, typename Handle>
  struct result_row_of<prepared_statement_t<ResultBase, Handle>>
  {
    using type = result_row_of_t<ResultBase>;
  };

  template <typename ResultBase, typename Handle>
  decltype(auto) execute(prepared_statement_t<ResultBase, Handle>& prepared_statement)
  {
    return detail::run(prepared_statement);
  }

}  // namespace sqlpp
