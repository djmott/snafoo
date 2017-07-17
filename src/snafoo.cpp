
#include <angelscript.h>
#include <sqlite3.h>
#include <CppSQLite3.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <xtd/parse.hpp>
#include <xtd/string.hpp>
#include <bits/exception.h>
#include <iostream>


namespace cli{
  using namespace xtd::parse;
  STRING(sExit, "exit");
  STRING(sQuit, "quit");

  struct grammar : rule<grammar, or_<sExit,sQuit>>{
    template <typename ... _ChildRuleTs>
    explicit grammar(_ChildRuleTs&& ... oChildRules) : rule(std::forward<_ChildRuleTs>(oChildRules)...){}

  };

  using whitespace_type = whitespace<'\n', '\r', '\t'>;


  using parser = xtd::parser<grammar, true, whitespace_type>;

}



int main(){
  try{
    CppSQLite3DB oDB;
    oDB.open("default.db");
    for(;;){
      xtd::string sInput;
      std::cout << "> ";
      std::getline(std::cin, sInput);
      try {
        auto oAST = cli::parser::parse(sInput.cbegin(), sInput.cend());
        if (!oAST){
          std::cout << "Invalid command.\n"; continue;
        }
        if (oAST->items()[0]->isa(typeid(cli::sExit)) || oAST->items()[0]->isa(typeid(cli::sQuit))) break;
      }
      catch(const std::exception&){
        std::cout << "\nInvalid command.\n\0";
      }

    }
    return 0;
  }
  catch(const std::exception& ex){
    std::cout << "An unhandled exception occurred: " << ex.what() << '\0';
  }
  catch(...){
    std::cout << "\nA critical exception occurred.\n\0";
  }
  return -1;
}