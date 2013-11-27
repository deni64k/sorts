cmake_minimum_required (VERSION 2.8.7 FATAL_ERROR)
project (sorts)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set (CMAKE_CXX_FLAGS                "-std=c++11 -fpermissive -Wall -mtune=native")
set (CMAKE_CXX_FLAGS_DEBUG          "-O0 -g -ggdb")
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O4 -g -ggdb")
add_definitions (-D__STDC_CONSTANT_MACROS)

option (USE_JEMALLOC "Use jemalloc" OFF)

if (USE_JEMALLOC)
  find_package (jemalloc REQUIRED)
endif ()

set (sorts_SOURCES
  )

set (sorts_LIBRARIES
	# -lprofiler
  )

if (USE_JEMALLOC)
  list (APPEND sorts_LIBRARIES ${JEMALLOC_LIBRARIES})
endif ()

include_directories (
  ${CMAKE_SOURCE_DIR}/src
  )

add_executable (sorts src/main.cxx ${sorts_SOURCES})

target_link_libraries (sorts ${sorts_LIBRARIES})

include ("CMakeTests.txt")
