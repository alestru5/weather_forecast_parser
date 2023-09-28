
cmake_minimum_required(VERSION 3.16)

project(oop_lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_PROFILE --coverage)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgumbo -std=c++20 -Wall -Wextra")

add_subdirectory(DailyForecast)
add_subdirectory(WeatherForecast)
add_subdirectory(Parsing)

find_package(CURL REQUIRED)

add_executable(main main.cpp)


include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(main DailyForecast WeatherForecast Parsing ${CURL_LIBRARIES} gumbo)


