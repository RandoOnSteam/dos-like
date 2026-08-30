# Set the C compiler to TinyCC
set(CMAKE_C_COMPILER "${CMAKE_SOURCE_DIR}/tcc/tcc.exe")

# Set flags to empty since TinyCC may not support some default CMake flags
set(CMAKE_C_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "" FORCE)
