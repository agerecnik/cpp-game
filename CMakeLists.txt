cmake_minimum_required(VERSION 3.14)
project(game)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_main test/game_manager_test.cpp test/game_test.cpp test/board_test.cpp src/game_manager.h src/game_manager.cpp src/game.h src/game.cpp src/board.h src/board.cpp)
add_executable(game src/main.cpp src/game_manager.h src/game_manager.cpp src/game.h src/game.cpp src/board.h src/board.cpp)
target_link_libraries(test_main gtest_main gmock_main)
include(GoogleTest)
gtest_discover_tests(test_main)