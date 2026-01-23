cmake_minimum_required(VERSION 3.15)
project(ThendralWorkspace)

# Add the subdirectories
# Thendral is added first so the DLL is available for the Frontend to link against
add_subdirectory(Thendral)
add_subdirectory(Frontend)