# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ADC)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/tests.c)
target_sources(app PRIVATE src/adc_reader/adc_reader.c)
target_sources(app PRIVATE src/user_interface/user_interface.c)
target_sources(app PRIVATE src/pwm_controller/pwm_controller.c)
target_sources(app PRIVATE src/power_path_controller/power_path_controller.c)
target_sources(app PRIVATE src/battery_monitor/battery_monitor.c)

