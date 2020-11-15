# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

# Depended on your own environment variable
set(GNUARMEMB_TOOLCHAIN_PATH "$ENV{GCC_ARM_HOME}")
set(ZEPHYR_TOOLCHAIN_VARIANT gnuarmemb)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(cfb_custom_font_demo)

include(${ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)


FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_cfb_font_for_target(app fonts/fsex302.ttf ${gen_dir}/cfb_font_fixedsys32.h 8 16 -s 16 --first 32 --last 126)
generate_cfb_font_for_target(app fonts/JetBrainsMono-Bold.ttf ${gen_dir}/cfb_font_jetbrains_mono_bold.h 26 48 -s 40 --first 32 --last 126)