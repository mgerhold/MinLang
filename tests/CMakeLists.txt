add_executable(Tests Lexer.test.cpp)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(Tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_include_directories(Tests PUBLIC ${PROJECT_SOURCE_DIR})

# static runtime library
set_property(TARGET Tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_test(NAME unit COMMAND Tests)