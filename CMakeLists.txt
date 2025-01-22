cmake_minimum_required(VERSION 3.20.0)
set(BOARD stm32_min_dev@blue)
find_package(Zephyr)
project(EchoCar)

include_directories(BEFORE src/)

target_sources(app PRIVATE
        src/main.c

        src/driver/display.c
        src/driver/motor.c

        src/infra/car_handler.c
)
