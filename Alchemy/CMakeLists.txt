# CMakeList.txt : CMake project for Alchemy, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Alchemy "main.cpp" "Alchemy1.h" "Alchemy1.cpp" "Alchemy2.h" "Alchemy2.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Alchemy PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
