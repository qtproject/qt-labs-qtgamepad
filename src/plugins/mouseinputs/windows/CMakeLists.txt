# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_plugin(WindowsMouseInputPlugin
    OUTPUT_NAME windowsmouseinput
    PLUGIN_TYPE mouseinputs
    SOURCES
        windowsmouseinput.cpp windowsmouseinput.h
        windowsmouseinputplugin.cpp windowsmouseinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate
)
