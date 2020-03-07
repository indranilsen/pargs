# Find bash to run tests from shell script
find_program(BASH_PROGRAM bash)

enable_testing()

set(TEST_BINARY PargsTest)
add_executable(${TEST_BINARY} test.cpp)

add_test(BASIC_TEST PargsTest COMMAND PargsTest --someVal=override_default_val --testInteger=100 --testString=hello --test --testFunctor=true)
add_test(SCRIPTED_TESTS ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/runtest.sh)

target_link_libraries(${TEST_BINARY} pargs)