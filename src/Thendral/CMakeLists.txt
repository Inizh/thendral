cmake_minimum_required(VERSION 3.15)
project(ThendralLib)

# Create the DLL target
add_library(thendral_dll SHARED 
    thendral.cpp 
    thendral.h
)

# Define where the headers are so Frontend can find them automatically
target_include_directories(thendral_dll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Handle Windows DLL symbol exporting
set_target_properties(thendral_dll PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)