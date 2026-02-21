cmake_minimum_required(VERSION 3.11)
project (MalwareVaccine CXX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
find_package(spdlog REQUIRED)

add_library(Logger 
    src/Logger/logger.h
    src/Logger/logger.cpp
)

target_link_libraries(Logger PUBLIC 
    spdlog::spdlog
)

add_library(ThreadPool 
    src/ThreadPool/thread_pool.h
    src/ThreadPool/thread_pool.cpp 
)

add_library(MalwareTechniques
    src/MalwareTechniques/ntdll.cpp
    src/MalwareTechniques/ntdll.h

    src/MalwareTechniques/privilege_escalator.h
    src/MalwareTechniques/privilege_escalator.cpp
    
    src/MalwareTechniques/domain.h
    src/MalwareTechniques/domain.cpp
)
target_link_libraries(MalwareTechniques PUBLIC 
    Logger
)

add_library(BSODThrower 
    src/BSODThrower/bsod_thrower.cpp
    src/BSODThrower/bsod_thrower.h
)
target_link_libraries(BSODThrower PRIVATE 
    MalwareTechniques
)

add_library(Ransomware 
    src/Ransomware/ransomware.h
    src/Ransomware/ransomware.cpp
)
target_link_libraries(Ransomware PRIVATE 
    MalwareTechniques
)

add_library(MalwareVaccine
    src/MalwareVaccine/malware_vaccine.h
    src/MalwareVaccine/malware_vaccine.cpp 
)	
target_link_libraries(MalwareVaccine PUBLIC
    MalwareTechniques
    Ransomware
    BSODThrower
    ThreadPool
)

add_library(Application SHARED
    src/MalwareVaccine/application.h
    src/MalwareVaccine/application.cpp
)
target_link_libraries(Application PRIVATE 
    MalwareVaccine
)

target_compile_definitions(Application PRIVATE APPLICATION_EXPORT)

add_executable(TestMalwareVaccine 
    src/main.cpp 
)
target_link_libraries(TestMalwareVaccine PRIVATE 
    MalwareVaccine 
    Application
)
