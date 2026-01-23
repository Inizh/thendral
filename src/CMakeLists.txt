cmake_minimum_required(VERSION 3.15...3.25)

# 1. Project metadata
project(Thendral
    VERSION 0.0.0 
    DESCRIPTION "A modern game engine made for fun"
)

# 2. Set C++ Standard (17 or 20 is standard in 2026)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 3. Define the executable target
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/utils.cpp
)

# 4. Include directories (PUBLIC for things headers need, PRIVATE for internal logic)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 5. Compiler options (Enable warnings to keep code clean)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

