# clang-format targets (Google style via .clang-format).
#
#   cmake --build --preset debug --target format
#   cmake --build --preset debug --target format-check

find_program(BK_CLANG_FORMAT_EXE
  NAMES clang-format clang-format-18 clang-format-17 clang-format-16
)

set(_bk_clang_format_globs
  "${CMAKE_SOURCE_DIR}/blackhart/*.c"
  "${CMAKE_SOURCE_DIR}/blackhart/*.h"
  "${CMAKE_SOURCE_DIR}/blackhart/*.cpp"
  "${CMAKE_SOURCE_DIR}/blackhart/*.hpp"
  "${CMAKE_SOURCE_DIR}/blackhart.studio/*.c"
  "${CMAKE_SOURCE_DIR}/blackhart.studio/*.h"
  "${CMAKE_SOURCE_DIR}/blackhart.studio/*.cpp"
  "${CMAKE_SOURCE_DIR}/blackhart.studio/*.hpp"
  "${CMAKE_SOURCE_DIR}/blackhart.data/*.c"
  "${CMAKE_SOURCE_DIR}/blackhart.data/*.h"
  "${CMAKE_SOURCE_DIR}/blackhart.data/*.cpp"
  "${CMAKE_SOURCE_DIR}/blackhart.data/*.hpp"
)

file(GLOB_RECURSE BK_CLANG_FORMAT_FILES CONFIGURE_DEPENDS ${_bk_clang_format_globs})

if (BK_CLANG_FORMAT_EXE)
  add_custom_target(format
    COMMAND ${BK_CLANG_FORMAT_EXE} -i ${BK_CLANG_FORMAT_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting sources with clang-format (Google)"
    VERBATIM
  )

  add_custom_target(format-check
    COMMAND ${BK_CLANG_FORMAT_EXE} --dry-run --Werror ${BK_CLANG_FORMAT_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Checking clang-format (Google)"
    VERBATIM
  )
else ()
  message(WARNING "clang-format not found: targets 'format' and 'format-check' are unavailable")
endif ()
