cmake_minimum_required(VERSION 3.10)
project(ShopSimulation VERSION 0.1.0)

file(GLOB ShopSimulation_src
    "src/*.cpp"
    "src/*.h"
    "src/interfaces/*.cpp"
    "src/interfaces/*.h"
    "src/exceptions/*.cpp"
    "src/exceptions/*.h"
)

add_executable(ShopSimulation ${ShopSimulation_src})

set_target_properties(ShopSimulation
    PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
