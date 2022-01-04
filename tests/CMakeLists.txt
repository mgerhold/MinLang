add_executable(Tests Main.test.cpp Lexer.test.cpp)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(Tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(Tests PRIVATE MinLang)
target_include_directories(Tests PUBLIC ${PROJECT_SOURCE_DIR}/src)

# static runtime library
set_property(TARGET Tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")