#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <angelscript.h>
#include <CppSQLite3.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <experimental/filesystem>
#include <as_jit.h>

namespace std{
  using namespace std::experimental;
}


struct script_exception : std::runtime_error{
  script_exception(int errcode, const char * sWhat) : runtime_error(sWhat), _error_code(errcode){}
  int error_code() const { return _error_code; }
private:
  int _error_code;
};

#define _AS(...) { auto iRet = (__VA_ARGS__); assert(iRet >= 0); if (iRet<0) throw script_exception(iRet, #__VA_ARGS__); }

void script_message_callback(const asSMessageInfo *, void *);
void script_print_handler(const std::string&);

int main(int argc, char * argv[]){
  try{
    auto oEngine = asCreateScriptEngine();
    _AS(oEngine->SetMessageCallback(asFUNCTION(script_message_callback), 0, asCALL_CDECL));
    RegisterStdString(oEngine);
    _AS(oEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(script_print_handler), asCALL_CDECL));
    _AS(oEngine->SetEngineProperty(asEP_INCLUDE_JIT_INSTRUCTIONS, 1))
    auto oJIT = std::make_unique<asCJITCompiler>(0);
    _AS(oEngine->SetJITCompiler(oJIT.get()));
    _AS(oEngine->RegisterObjectType("Database", 0, asOBJ_REF));

    std::filesystem::path oPath(std::string(argv[0]));
    oPath = oPath.remove_filename();
    oPath.append(".db");
    const auto bCreateDB = !std::filesystem::exists(oPath);
    CppSQLite3DB oDB;
    oDB.open(oPath.string().c_str());
    if (bCreateDB){
      oDB.execDML("Begin Transaction;");
      oDB.execDML("Create Table Scripts(Module String Not Null, Name String Not Null, Code String Not Null);");
      oDB.execDML("Create Unique Index PK_Scripts On Scripts (Module, Name);");
      oDB.execDML("Commit Transaction;");
    }

    auto oCoreScriptsQuery = oDB.execQuery("Select Name, Code From Scripts Where Module='core';");
    while (!oCoreScriptsQuery.eof()){

    }

    auto oCoreModule = oEngine->GetModule("core");

    oEngine->ShutDownAndRelease();
    return 0;
  }
  catch(const script_exception& ex){
    std::cout << "An unhandled script exception " << ex.error_code() << " " << ex.what() << '\0';
  }
  catch(const CppSQLite3Exception& ex){
    std::cout << "An unhandled database exception occurred: " << ex.errorMessage() << '\0';
  }
  catch(const std::exception& ex){
    std::cout << "An unhandled exception occurred: " << ex.what() << '\0';
  }
  catch(...){
    std::cout << "\nA critical exception occurred.\n\0";
  }
  return -1;
}


void script_message_callback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void script_print_handler(const std::string &sMsg){
  std::cout << sMsg;
}