# Optional: IDE / compile_commands.json support. The daily loop uses scripts/run_drill.sh.
cmake_minimum_required(VERSION 3.20)
project(interview_prep CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)

option(DRILL_SANITIZE "Build drills with ASan + UBSan" ON)
if(DRILL_SANITIZE)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g)
  add_link_options(-fsanitize=address,undefined)
endif()

# Day dirs are days/<category>/<date>_<slug>. CONFIGURE_DEPENDS makes the glob re-run
# on build, so a day created by new_day.sh appears without a manual re-configure.
file(GLOB DAY_DIRS CONFIGURE_DEPENDS
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/days ${CMAKE_CURRENT_SOURCE_DIR}/days/*/*)
foreach(day ${DAY_DIRS})
  set(day_path ${CMAKE_CURRENT_SOURCE_DIR}/days/${day})
  if(IS_DIRECTORY ${day_path} AND EXISTS ${day_path}/solution.cpp)
    string(REPLACE "." "_" target "drill_${day}")
    string(REPLACE "/" "_" target "${target}")
    add_executable(${target} ${day_path}/solution.cpp ${day_path}/tests.cpp)
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common ${day_path})
  endif()
endforeach()
