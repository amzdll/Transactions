cmake_minimum_required(VERSION 3.25)
project(Transactions)
set(CMAKE_CXX_STANDARD 17)

include_directories(storages/include)
include_directories(libs/unordered_map)
include_directories(libs/map)
include_directories(utils/student_data)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(INCLUDE_DIR ${SRC_DIR}/include)

add_library(unordered_map
        libs/unordered_map/unordered_map.cc
        libs/unordered_map/unordered_map.h
)

add_library(map
        libs/map/map.cc
        libs/map/map.h
        libs/map/test.cc
)

add_library(hash_table
        storages/include/abstract_storage.h
        storages/source/hash_table.cc
        storages/include/hash_table.h
)

add_library(self_balancing_binary_search_tree
        storages/include/abstract_storage.h
        storages/source/self_balancing_binary_search_tree.cc
        storages/include/self_balancing_binary_search_tree.h
)

add_library(student_data
        utils/student_data/student_data.cc
        utils/student_data/student_data.h
)

add_executable(Transactions
        main.cc
        console_interface/interface.cc
        console_interface/interface.h
)

target_include_directories(student_data PUBLIC ${INCLUDE_DIR})

target_include_directories(unordered_map PUBLIC ${INCLUDE_DIR})
target_include_directories(hash_table PUBLIC ${INCLUDE_DIR})

target_include_directories(map PUBLIC ${INCLUDE_DIR})
target_include_directories(self_balancing_binary_search_tree PUBLIC ${INCLUDE_DIR})


target_link_libraries(Transactions PRIVATE
        unordered_map unordered_map student_data
        hash_table self_balancing_binary_search_tree)