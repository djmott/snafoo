
ExternalProject_Add(xtl
  GIT_REPOSITORY https://github.com/djmott/xtl.git
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/xtl
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xtl
  CMAKE_GENERATOR ${CMAKE_GENERATOR}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_GENERATOR_TOOLSET ${CMAKE_GENERATOR_TOOLSET}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/angelscript
  BUILD_IN_SOURCE 0
  INSTALL_COMMAND ""
)

#[[
ExternalProject_ADD(SQLite
  URL https://www.sqlite.org/src/tarball/sqlite.tar.gz?r=release
  DOWNLOAD_NAME sqlite.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/sqlite
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sqlite
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/sqlite --disable-tcl --enable-static --disable-shared
  BUILD_COMMAND make
  BUILD_IN_SOURCE 0
  INSTALL_COMMAND make install
  )
]]

ExternalProject_ADD(SQLite
  URL https://www.sqlite.org/src/tarball/sqlite.tar.gz?r=release
  DOWNLOAD_NAME sqlite.tar.gz
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/sqlite
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sqlite
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/configure --disable-tcl --enable-static --disable-shared
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND ""
  )


ExternalProject_Add(CppSQLite3
  DEPENDS SQLite
  GIT_REPOSITORY https://github.com/neosmart/CppSQLite.git
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cppsqlite3
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cppsqlite3
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${CMAKE_CXX_COMPILER} -c ${CMAKE_CURRENT_SOURCE_DIR}/cppsqlite3/CppSQLite3.cpp
  INSTALL_COMMAND ""
  )

ExternalProject_ADD(AngelScript
  SVN_REPOSITORY http://svn.code.sf.net/p/angelscript/code/trunk
  SVN_TRUST_CERT 1
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/angelscript
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/angelscript
  SOURCE_SUBDIR sdk/angelscript/projects/cmake
  CMAKE_GENERATOR ${CMAKE_GENERATOR}
  CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
  CMAKE_GENERATOR_TOOLSET ${CMAKE_GENERATOR_TOOLSET}
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/angelscript
  BUILD_IN_SOURCE 0
  INSTALL_COMMAND ""
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/angelscript/sdk/angelscript/include)

set(ADDON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/angelscript/sdk/add_on)

add_library(ContextMgr STATIC ${ADDON_DIR}/contextmgr/contextmgr.cpp ${ADDON_DIR}/contextmgr/contextmgr.h)

add_library(ScriptDateTime STATIC ${ADDON_DIR}/datetime/datetime.cpp ${ADDON_DIR}/datetime/datetime.h)

add_library(ScriptDebugger STATIC ${ADDON_DIR}/debugger/debugger.cpp ${ADDON_DIR}/debugger/debugger.h)

add_library(ScriptArray STATIC ${ADDON_DIR}/scriptarray/scriptarray.cpp ${ADDON_DIR}/scriptarray/scriptarray.h)

add_library(ScriptBuilder STATIC ${ADDON_DIR}/scriptbuilder/scriptbuilder.cpp ${ADDON_DIR}/scriptbuilder/scriptbuilder.h)

add_library(ScriptDictionary STATIC ${ADDON_DIR}/scriptdictionary/scriptdictionary.cpp ${ADDON_DIR}/scriptdictionary/scriptdictionary.h)

add_library(ScriptFile STATIC
  ${ADDON_DIR}/scriptfile/scriptfile.cpp ${ADDON_DIR}/scriptfile/scriptfile.h
  ${ADDON_DIR}/scriptfile/scriptfilesystem.cpp ${ADDON_DIR}/scriptfile/scriptfilesystem.h
)

add_library(ScriptHelper STATIC ${ADDON_DIR}/scripthelper/scripthelper.cpp ${ADDON_DIR}/scripthelper/scripthelper.h)

add_library(ScriptMath STATIC
  ${ADDON_DIR}/scriptmath/scriptmath.cpp ${ADDON_DIR}/scriptmath/scriptmath.h
  ${ADDON_DIR}/scriptmath/scriptmathcomplex.cpp ${ADDON_DIR}/scriptmath/scriptmathcomplex.h
)
add_library(ScriptStdString STATIC
  ${ADDON_DIR}/scriptstdstring/scriptstdstring.cpp
  ${ADDON_DIR}/scriptstdstring/scriptstdstring.h
  ${ADDON_DIR}/scriptstdstring/scriptstdstring_utils.cpp
)

add_library(ScriptSerializer STATIC ${ADDON_DIR}/serializer/serializer.cpp ${ADDON_DIR}/serializer/serializer.h)
add_library(ScriptWeakRef STATIC ${ADDON_DIR}/weakref/weakref.cpp ${ADDON_DIR}/weakref/weakref.h)
