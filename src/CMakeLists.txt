set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.23)
project(Transactions LANGUAGES CXX)

enable_testing()
find_package(GTest REQUIRED)

include_directories(libs/map)
include_directories(libs/unordered_map)
include_directories(storages/include)
include_directories(utils/student_data)
include_directories(${GTEST_INCLUDE_DIRS})

set(SRC_DIR ../)
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

add_executable(
        Transactions
        #        libs/unordered_map/unordered_map.cc
        #        libs/unordered_map/test.cc
        #        libs/unordered_map/unordered_map.h
        #        storages/include/hash_table.h
        main.cc
        console_interface/console_interface.cc
        console_interface/console_interface.h
)

add_executable(test_map
        libs/map/map.cc
        libs/map/test.cc
)

target_include_directories(student_data PUBLIC ${INCLUDE_DIR})
target_include_directories(map PUBLIC ${INCLUDE_DIR})
target_include_directories(unordered_map PUBLIC ${INCLUDE_DIR})
target_include_directories(hash_table PUBLIC ${INCLUDE_DIR})
target_include_directories(self_balancing_binary_search_tree PUBLIC ${INCLUDE_DIR})

target_link_libraries(Transactions PRIVATE
        student_data
        map
        unordered_map
        hash_table
        self_balancing_binary_search_tree
)

target_link_libraries(test_map gtest pthread)
#
#
#add_library(
#        hash_table.a STATIC
#        storages/source/hash_table.cc
#        storages/include/hash_table.h
#)
#set_target_properties(hash_table.a PROPERTIES PREFIX "")
