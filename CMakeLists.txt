cmake_minimum_required(VERSION 3.16)

project(OperatingSystems LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OperatingSystems main.cpp
    bttf.h
    bttf.cpp
    bttf.cpp
    sort.h
    container.h

)

include(GNUInstallDirs)
install(TARGETS OperatingSystems
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
