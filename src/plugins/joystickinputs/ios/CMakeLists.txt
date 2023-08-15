# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_plugin(IosJoystickInputPlugin
    OUTPUT_NAME iosjoystickinput
    PLUGIN_TYPE joystickinputs
    SOURCES
        iosjoystickinput.mm iosjoystickinput.h
        iosjoystickinputplugin.cpp iosjoystickinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
        ${FWFoundation}
        ${FWGameController}
)
