# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_plugin(WindowsJoystickInputPlugin
    OUTPUT_NAME windowsjoystickinput
    PLUGIN_TYPE joystickinputs
    SOURCES
        windowsjoystickinput.cpp windowsjoystickinput.h
        windowsjoystickinputplugin.cpp windowsjoystickinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
        dinput8
)
