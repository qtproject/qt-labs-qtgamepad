# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

set(java_sources
    jar/src/org/qtproject/qt/android/universalinput/QtJoystickInputHandler.java
    jar/src/org/qtproject/qt/android/universalinput/QtJoystick.java
)

qt_internal_add_jar(Qt${QtUniversalInput_VERSION_MAJOR}AndroidJoystickInput
    INCLUDE_JARS ${QT_ANDROID_JAR}
    SOURCES ${java_sources}
    OUTPUT_DIR "${QT_BUILD_DIR}/jar"
)

qt_path_join(destination ${INSTALL_DATADIR} "jar")

install_jar(Qt${QtUniversalInput_VERSION_MAJOR}AndroidJoystickInput
    DESTINATION ${destination}
    COMPONENT Devel
)


qt_internal_add_plugin(AndroidJoystickInputPlugin
    OUTPUT_NAME androidjoystickinput
    PLUGIN_TYPE joystickinputs
    DEFAULT_IF ANDROID
    SOURCES
        androidjoystickinput.cpp androidjoystickinput.h
        androidjoystickinputplugin.cpp androidjoystickinputplugin.h
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::UniversalInput
        Qt::UniversalInputPrivate

)

set_property(
    TARGET
        AndroidJoystickInputPlugin
    APPEND PROPERTY QT_ANDROID_BUNDLED_JAR_DEPENDENCIES
        jar/Qt${QtUniversalInput_VERSION_MAJOR}AndroidJoystickInput.jar
)
