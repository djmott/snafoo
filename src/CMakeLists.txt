
set(SOURCES
  ASAddins.cpp
  snafoo.cpp
  )


link_directories(${XTL_BIN_DIR})
link_directories(${ANGELSCRIPT_BIN_DIR})
link_directories(${SQLITE_BIN_DIR})

link_libraries(XTL)
link_libraries(sqlite3)
link_libraries(angelscript)
link_libraries(pthread)

add_executable(snafoo ${SOURCES})

add_dependencies(snafoo
  XTL
  SQLite
  CppSQLite3
  AngelScript
  )


