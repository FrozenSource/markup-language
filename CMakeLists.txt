cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(HUNTER_PACKAGES GTest)
include(FetchContent)
FetchContent_Declare(SetupHunter GIT_REPOSITORY https://github.com/cpp-pm/gate)
FetchContent_MakeAvailable(SetupHunter)

set(This MarkupLanguage)
project(${This} LANGUAGES C CXX)

find_package(GTest CONFIG REQUIRED)

set(Headers
        ${PROJECT_SOURCE_DIR}/include/StringBuilder.h
        ${PROJECT_SOURCE_DIR}/include/MarkupLanguage.h
        ${PROJECT_SOURCE_DIR}/include/HtmlLanguage.h
        ${PROJECT_SOURCE_DIR}/include/XmlLanguage.h
        ${PROJECT_SOURCE_DIR}/include/INIConfig.h)

set(Sources
        ${PROJECT_SOURCE_DIR}/src/StringBuilder.cpp
        ${PROJECT_SOURCE_DIR}/src/MarkupLanguage.cpp
        ${PROJECT_SOURCE_DIR}/src/HtmlLanguage.cpp
        ${PROJECT_SOURCE_DIR}/src/XmlLanguage.cpp
        ${PROJECT_SOURCE_DIR}/src/INIConfig.cpp)

set(Test-Sources
        ${PROJECT_SOURCE_DIR}/test/HtmlLanguage.cpp
        ${PROJECT_SOURCE_DIR}/test/XmlLanguage.cpp
        ${PROJECT_SOURCE_DIR}/test/INIConfig.cpp)

add_library(${This} ${Headers} ${Sources})
add_executable(${This}-test ${Test-Sources} ${PROJECT_SOURCE_DIR}/test/main-test.cpp)
target_include_directories(${This} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${This}-test PUBLIC GTest::gtest ${This})

if(WIN32)
        target_compile_definitions(${This} PUBLIC BUILD _CRT_SECURE_NO_WARNINGS)
endif()

enable_testing()

add_test(
        NAME ${This}-test
        COMMAND ${This}-test
)
