cmake_minimum_required(VERSION 3.11)
project (MalwareVaccine CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(MalwareTechniques
    src/ntdll.cpp
    src/ntdll.h

    src/edr_stress.cpp
    src/edr_stress.h

    src/domain.h
    src/domain.cpp
)

add_executable(MalwareVaccine
    src/main.cpp
)	

target_link_libraries(MalwareVaccine PUBLIC
    MalwareTechniques
)