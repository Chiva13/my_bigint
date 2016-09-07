include_directories ("${PROJECT_SOURCE_DIR}/libbigint")

add_executable(bigint_calc bigint_calc.cpp)
target_link_libraries (bigint_calc libbigint)