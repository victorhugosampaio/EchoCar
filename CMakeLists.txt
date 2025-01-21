cmake_minimum_required(VERSION 3.20.0)
set(BOARD stm32_min_dev@blue)
find_package(Zephyr)
project(EchoCar)

target_sources(app PRIVATE
        src/main.c

        src/drivers/display.c
        src/drivers/motor.c
)
