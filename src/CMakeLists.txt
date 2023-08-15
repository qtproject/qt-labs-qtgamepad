# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(universalinput)
add_subdirectory(gamepad)
if(TARGET Qt::Quick)
    add_subdirectory(quickgamepad)
    add_subdirectory(quickactionstore)
    add_subdirectory(quickuniversalinput)
endif()
add_subdirectory(plugins)
