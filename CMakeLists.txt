cmake_minimum_required(VERSION 2.8)

project(rokkit_hash)

execute_process(COMMAND python3 -c "import sysconfig; print(sysconfig.get_paths()['include'])" OUTPUT_VARIABLE PYTHON_INCLUDE_PATH ERROR_VARIABLE ERROR_VAR RESULT_VARIABLE RESULT_VAR)
message("PYTHON_INCLUDE_FLAGS = " ${PYTHON_INCLUDE_FLAGS} ", ERROR_VAR = " ${ERROR_VAR} ", RESULT_VAR = " ${RESULT_VAR} "\n")

include_directories(${PYTHON_INCLUDE_PATH})

add_library(${PROJECT_NAME} SHARED "rokkit_hash_module.c")

#string(CONCAT EXE_NAME ${PROJECT_NAME} "_test")
#add_executable(${PROJECT_NAME}_test "rokkit_hash_module.c")
