cmake_minimum_required(VERSION 3.25)
project(Transactions)

set(CMAKE_CXX_STANDARD 17)

include_directories(storages/include)
include_directories(libs/unordered_map)
include_directories(libs)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(INCLUDE_DIR ${SRC_DIR}/include)

add_library(unordered_map
        libs/unordered_map/unordered_map.cc
        libs/unordered_map/unordered_map.h
)

add_library(hash_table
        storages/source/hash_table.cc
        storages/include/hash_table.h
)

add_executable(Transactions
        main.cc
        storages/include/abstract_storage.h
        storages/source/hash_table.cc
        storages/include/hash_table.h
        storages/source/info_school.cc
        storages/include/info_school.h
        libs/unordered_map/unordered_map.cc
        libs/unordered_map/unordered_map.h

        #        src/include/self_balancing_binary_search_tree.h
        #        src/source/self_balancing_binary_search_tree.cc

        interface/interface.cc interface/interface.h interface/interface.cc
        utils/student_data/student_data.cc
        utils/student_data/student_data.h)

target_include_directories(unordered_map PUBLIC ${INCLUDE_DIR})
target_include_directories(hash_table PUBLIC ${INCLUDE_DIR})


target_link_libraries(Transactions PRIVATE unordered_map hash_table)
