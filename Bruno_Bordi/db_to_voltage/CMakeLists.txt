cmake_minimum_required(VERSION 3.15)
project(db_to_voltage)

set(sdk_folder
    ../../se_sdk3
    )

set(sdk_srcs
     ${sdk_folder}/mp_sdk_common.cpp
     ${sdk_folder}/mp_sdk_audio.cpp
    )

set(srcs
    db_to_voltage.cpp
    module.rc
    )

set(srcs
    db_to_voltage.cpp
    module.rc
    )

include_directories(
    ${sdk_folder}
    )

include (GenerateExportHeader)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_library(${PROJECT_NAME} SHARED ${sdk_srcs} ${srcs})

