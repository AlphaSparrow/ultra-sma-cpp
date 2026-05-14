cmake_minimum_required(VERSION 3.10)
project(UltraSMACPP)

# Im guiding the Compiler here to use the latest boi C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Now we got some speed flags here and there son
# -O3 my hostel hehe, this is for aggressive optimisation siuuuu
# -march=native ??? optimise for this CPU exclusively which in my caase is OMEN
# -ffast-math - this is not cringe free fire, this is for FAST FLOATING POITY MATH
# -flto is ? idk gotta see

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-O3 -march=native -ffast-math -flto)
    add_link_options(-flto)
endif()

include_directories(include)

# Classic way of telling every .cpp boy in src folder, GLOBAL SOURCES opening technique
file(GLOB SOURCES "src/*.cpp")

# This adds executable ? aye ?
add_executable(ultra_sma ${SOURCES})