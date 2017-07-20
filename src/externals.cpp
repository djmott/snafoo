#include <datetime/datetime.cpp>
#include <debugger/debugger.cpp>
#include <scriptany/scriptany.cpp>
#include <scriptarray/scriptarray.cpp>
#include <scriptbuilder/scriptbuilder.cpp>
#include <scriptdictionary/scriptdictionary.cpp>
#include <scriptfile/scriptfile.cpp>
#include <scriptfile/scriptfilesystem.cpp>
//#include <scriptgrid/scriptgrid.cpp>
#include <scripthandle/scripthandle.cpp>
#include <scripthelper/scripthelper.cpp>
#include <scriptmath/scriptmath.cpp>
#include <scriptmath/scriptmathcomplex.cpp>
#include <scriptstdstring/scriptstdstring.cpp>
#include <serializer/serializer.cpp>
#include <weakref/weakref.cpp>
#include <CppSQLite3.cpp>

#include <as_jit.cpp>

#if defined(WIN32)
  #include <virtual_asm_windows.cpp>
  #include <virtual_asm_x86.cpp>
#elif defined(WIN64)
  #include <virtual_asm_windows.cpp>
  #include <virtual_asm_x64.cpp>
#elif defined(__x86_64__)
  #include <virtual_asm_linux.cpp>
  #include <virtual_asm_x64.cpp>
#else()
  #include <virtual_asm_linux.cpp>
  #include <virtual_asm_x86.cpp>
#endif()

