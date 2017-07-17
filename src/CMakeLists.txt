
set(SOURCES snafoo.cpp)

add_executable(snafoo ${SOURCES})
add_dependencies(snafoo
  xtl
  SQLite
  CppSQLite3
  AngelScript
  ScriptArray
  ScriptBuilder
  ScriptStdString
  ScriptDebugger
  )