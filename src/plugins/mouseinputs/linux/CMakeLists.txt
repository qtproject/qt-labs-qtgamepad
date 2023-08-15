# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_plugin(LinuxMouseInputPlugin
    OUTPUT_NAME linuxmouseinput
    PLUGIN_TYPE mouseinputs
    SOURCES
        linuxmouseinput.cpp linuxmouseinput.h
        linuxmouseinputplugin.cpp linuxmouseinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
)
