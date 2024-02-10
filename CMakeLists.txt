###########################################################################

cmake_minimum_required (VERSION 3.17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_TOOLCHAIN_FILE ./cmake/arm-gcc-toolchain.cmake)
set(PROJECT blinky)

include(device)
include(utils)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT} LANGUAGES C CXX ASM)

option(ENABLE_FOTA "Enable firmware update over the air" OFF)
option(ENABLE_RTT "Enable SEGGER RTT for debugging" OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

#add_subdirectory(sdk EXCLUDE_FROM_ALL)

set(INCLUDE_DIRS
    3d_party/qpcpp/include
    3d_party/qpcpp/ports/arm-cm/qv/gnu
    board_specific
    3d_party/cmsis_device_stm_l4/Include
    3d_party/cmsis_5/CMSIS/Core/Include
    src
    board_specific
)


## Application source files
# C++ source files
set(APP_CPP_SRCS
    src/bsp.cpp
    src/main.cpp
    src/blinky.cpp
)

## STM32 source files
# Assembler source files
set(STM32_ASM_SRCS
    board_specific/startup_stm32l476xx.s
)

# C source files
set(STM32_C_SRCS
    board_specific/system_stm32l4xx.c
    board_specific/stm32l4xx_it.c
)

## QPCPP source files
# C++ source files
set(QP_CPP_SRCS
    3d_party/qpcpp/src/qf/qep_hsm.cpp
    3d_party/qpcpp/src/qf/qep_msm.cpp
    3d_party/qpcpp/src/qf/qf_act.cpp
    3d_party/qpcpp/src/qf/qf_actq.cpp
    3d_party/qpcpp/src/qf/qf_defer.cpp
    3d_party/qpcpp/src/qf/qf_dyn.cpp
    3d_party/qpcpp/src/qf/qf_mem.cpp
    3d_party/qpcpp/src/qf/qf_ps.cpp
    3d_party/qpcpp/src/qf/qf_qact.cpp
    3d_party/qpcpp/src/qf/qf_qeq.cpp
    3d_party/qpcpp/src/qf/qf_qmact.cpp
    3d_party/qpcpp/src/qf/qf_time.cpp
    3d_party/qpcpp/src/qv/qv.cpp
    3d_party/qpcpp/ports/arm-cm/qv/gnu/qv_port.cpp)

include_directories(${INCLUDE_DIRS})

add_executable( ${PROJECT} 
                ${APP_CPP_SRCS}
                ${STM32_ASM_SRCS} 
                ${STM32_C_SRCS} 
                ${QP_CPP_SRCS})


target_include_directories(${PROJECT} PRIVATE include)


#target_link_libraries(${PROJECT} PRIVATE rsl10_system)
#target_link_libraries(${PROJECT} PRIVATE ble_abstraction_layer)
#target_link_libraries(${PROJECT} PRIVATE qpcpp_system)

if (ENABLE_FOTA)
    target_make_fota(${PROJECT})
else ()
    target_linker_script(${PROJECT} "${CMAKE_CURRENT_LIST_DIR}/board_specific/blinky.ld")
endif ()

#if (ENABLE_RTT)
#    target_link_libraries(${PROJECT} PRIVATE SeggerRTT)
#    target_compile_definitions(${PROJECT} PRIVATE ENABLE_RTT)
#endif ()

#target_compile_definitions(${PROJECT} PRIVATE Q_SPY)

set(WARNINGS
    all
	extra
	maybe-uninitialized
	strict-overflow=2
	switch
	write-strings
)

list(TRANSFORM WARNINGS PREPEND "-W")
list(TRANSFORM DISABLE_WARNINGS PREPEND "-Wno-")
target_compile_options(${PROJECT} PRIVATE "${WARNINGS}" "${DISABLE_WARNINGS}")
if (FATAL_ERRORS)
    target_compile_options(${PROJECT} PRIVATE "-Wfatal-errors")
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")

#set(LAUNCH_FILE_INTERMEDIATE "${CMAKE_CURRENT_BINARY_DIR}/launch.json.in")
#configure_file("${CMAKE_CURRENT_LIST_DIR}/cmake/launch.json.in" ${LAUNCH_FILE_INTERMEDIATE} @ONLY)

#file(GENERATE
#    OUTPUT "${CMAKE_CURRENT_LIST_DIR}/.vscode/launch.json"
#    INPUT ${LAUNCH_FILE_INTERMEDIATE}
#)
