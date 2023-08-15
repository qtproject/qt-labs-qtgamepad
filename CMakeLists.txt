# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

include(.cmake.conf)
project(QtUniversalInput
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt Universal Input Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core)
find_package(Qt6 ${PROJECT_VERSION} QUIET CONFIG OPTIONAL_COMPONENTS Concurrent Network Quick Widgets PacketProtocolPrivate)

if(VXWORKS OR WATCHOS)
    message(NOTICE "Skipping the build as the condition \"NOT VXWORKS AND NOT WATCHOS\" is not met.")
    return()
endif()

qt_build_repo()
