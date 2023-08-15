# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_find_apple_system_framework(FWForceFeedback ForceFeedback)

qt_internal_add_plugin(MacOSJoystickInputPlugin
    OUTPUT_NAME macosjoystickinput
    PLUGIN_TYPE joystickinputs
    SOURCES
        macosjoystickinput.mm macosjoystickinput.h
        macosjoystickinputplugin.cpp macosjoystickinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
        ${FWIOKit}
        ${FWForceFeedback}
)
