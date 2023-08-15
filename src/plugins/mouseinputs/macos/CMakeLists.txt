# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_find_apple_system_framework(FWAppKit AppKit)

qt_internal_add_plugin(MacOSMouseInputPlugin
    OUTPUT_NAME macosmouseinput
    PLUGIN_TYPE mouseinputs
    SOURCES
        macosmouseinput.mm macosmouseinput.h
        macosmouseinputplugin.cpp macosmouseinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
        ${FWAppKit}
)
