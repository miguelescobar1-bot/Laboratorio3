cmake_minimum_required(VERSION 3.16)

project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3 main.cpp
    Modulo_RLE.cpp
    Modulo_LZ78.cpp
    Encriptacion.cpp
    Modulo_RLE.h
    Modulo_LZ78.h
    Encriptacion.h
)

include(GNUInstallDirs)
install(TARGETS Lab3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
