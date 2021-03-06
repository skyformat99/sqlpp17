/*
Copyright (c) 2016, Roland Bock
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

#include <iostream>
#include <sqlpp17_test/tables/TabDepartment.h>
#include <sqlpp17_test/tables/TabEmpty.h>
#include <sqlpp17_test/tables/TabPerson.h>

#include <sqlpp17/clause/select.h>
#include <sqlpp17/clause/union.h>
#include <sqlpp17/operator.h>

#warning : Not implemented

struct connection
{
  template <typename Statement, typename Row>
  auto select(const Statement& s, const Row& row)
  {
    return row;
  }
};
int main()
{
  auto context = 0;
  /*
  #warning : s should be a constexpr
    auto s = sqlpp::union_all(sqlpp::select() << select_columns(test::tabPerson.id),
                              sqlpp::select() << select_columns(test::tabPerson.id));
  sqlpp::select() << sqlpp::selected_fields(test::tabPerson.id, test::tabPerson.isManager,
                                                     test::tabPerson.address, test::tabPerson.name)
                           << sqlpp::from(test::tabPerson)
                           << sqlpp::where(test::tabPerson.isManager and test::tabPerson.name == '\0')
                           << sqlpp::having(test::tabPerson.id == test::tabPerson.id or test::tabPerson.id == 1);
  #warning : need to test results
    std::cout << to_sql_string_c(context, s);
    auto conn = connection{};
    auto row = s.execute(conn);
    */
  /*

  // using data_members_of_meta = std::meta::get_public_data_members_m<reflexpr(reflexpr(row))>;
  // std::cout << std::meta::get_size_v<data_members_of_meta> << std::endl;
  // data_members::hansi;
  // std::cout << data_members{} << std::endl;
  row.hansi;
  */
}
