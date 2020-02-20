cmake_minimum_required(VERSION 3.15)
project(db_to_voltage)

set(sdk_folder
    ../../se_sdk3
    )

include_directories(
    ${sdk_folder}
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

include (GenerateExportHeader)

add_library(${PROJECT_NAME} SHARED ${sdk_srcs} ${srcs})

