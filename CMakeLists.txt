cmake_minimum_required(VERSION 3.10)
project(CmbApplicationFAW VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 1)

set(QNX_HOST $ENV{QNX_HOST})
set(QNX_TARGET $ENV{QNX_TARGET})
set(QNX_ARCH gcc_ntoaarch64le)

set(CMAKE_C_COMPILER qcc)
set(CMAKE_CXX_COMPILER q++)



set(CMAKE_C_FLAGS "-V8.3.0,gcc_ntoaarch64le -fpermissive")
set(CMAKE_CXX_FLAGS "-V8.3.0,gcc_ntoaarch64le -fpermissive")

# CMB Configuration, refer to CMB-2.0.2/src/SConstruct.py
# Macro definitions
add_definitions(-DENABLE_BAF_ADAPTOR=0)
add_definitions(-DENABLE_BRF_ADAPTOR=1)
add_definitions(-DENABLE_BTF_ADAPTOR=1)
add_definitions(-DENABLE_BCF_ADAPTOR=1)
add_definitions(-DENABLE_IOAUDIO_ADAPTOR=1)
add_definitions(-DENABLE_ASDS_ADAPTOR=0)
add_definitions(-DENABLE_SOCKET_THREADS=1)
add_definitions(-DMD5_CHECKSUM)

# CMB Variables
set(BOSE_ENTERTAINMENT_AUDIO 1)
set(BOSE_RNC  0)
set(BOSE_ASDS 0)

if(BOSE_ENTERTAINMENT_AUDIO)
    set(BOSE_EA_BTF  1)
    set(BOSE_EA_BRF  1)
    set(BOSE_EA_BCF  1)
    set(BOSE_EA_BAF  0)
    set(IOAUDIO_PROXY_CNT 1)
    set(BOSE_RNC_BTF 0)
    set(BOSE_RNC_BRF  0)
    set(BOSE_RNC_BCF 0)
    set(BOSE_RNC_BAF 0)
    set(BOSE_ASDS_BTF  0)
    set(BOSE_ASDS_BRF  0)
    set(BOSE_ASDS_BCF  0)
    set(BOSE_ASDS_BAF  0)
else()
    set(BOSE_EA_BTF  1)
    set(BOSE_EA_BRF  1)
    set(BOSE_EA_BCF  1)
    set(BOSE_EA_BAF  0)
    set(IOAUDIO_PROXY_CNT 1)
endif()

math(EXPR BTF_PROXY_CNT "${BOSE_EA_BTF} + ${BOSE_RNC_BTF} + ${BOSE_ASDS_BTF}")
math(EXPR BRF_PROXY_CNT "${BOSE_EA_BRF} + ${BOSE_RNC_BRF} + ${BOSE_ASDS_BRF}")
math(EXPR BCF_PROXY_CNT "${BOSE_EA_BCF} + ${BOSE_RNC_BCF} + ${BOSE_ASDS_BCF}")
math(EXPR BAF_PROXY_CNT "${BOSE_EA_BAF} + ${BOSE_RNC_BAF} + ${BOSE_ASDS_BAF}")
add_definitions(-DBTF_PROXY_CNT=${BTF_PROXY_CNT})
add_definitions(-DBRF_PROXY_CNT=${BRF_PROXY_CNT})
add_definitions(-DBCF_PROXY_CNT=${BCF_PROXY_CNT})


# Configure the application code for the feature selectd.
add_definitions(-DBOSE_ENTERTAINMENT_AUDIO=${BOSE_ENTERTAINMENT_AUDIO})
add_definitions(-DBOSE_RNC=${BOSE_RNC})
add_definitions(-DBOSE_ASDS=${BOSE_ASDS})

# print out the variables for debugging
message(STATUS "Using QNX_HOST = ${QNX_HOST}")
message(STATUS "Using QNX_TARGET = ${QNX_TARGET}")
message(STATUS "Using QNX_ARCH = ${QNX_ARCH}")
message(STATUS "C Compiler = ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler = ${CMAKE_CXX_COMPILER}")

message(STATUS "BTF_PROXY_CNT =${BTF_PROXY_CNT}")
message(STATUS "BRF_PROXY_CNT=${BRF_PROXY_CNT}")
message(STATUS "BCF_PROXY_CNT=${BCF_PROXY_CNT}")

# include directories
include_directories(CMB-2.0.2/include)
include_directories(include/BCF)
include_directories(include/BAF)
include_directories(include/BRF)
include_directories(include/BTF)
include_directories(include/CART/include)
include_directories(include/CART/Runtime/CMB)


link_directories(CMB-2.0.2/dll)
link_directories(lib)
link_directories(${QNX_TARGET}/aarch64le/lib)

add_executable(${PROJECT_NAME} src/main.c
                               src/CMB_Framework_config.cpp
                               src/CMB_Framework.c
                               )
target_link_libraries(${PROJECT_NAME} csd2IpcClient slog2 audio_log_util OSAbstraction libstd asound
ams2 pmem_client ssr tzbsplib diag_lsm dalconfig
Cmb_dll
Adaptor_Common
IOA_Adaptor
BTF_Adaptor 
BCF_Adaptor 
BRF_Adaptor 
Tuning_Adaptor 
Control_Adaptor 
CSD2_Adaptor 
ACS_Adaptor
AMS_Adaptor)