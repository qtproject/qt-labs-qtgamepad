// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtActionStore

ActionStore {
    id: actionStore
    property int device: JoyAxisEvent.Device0

    InputAction {
        title: "Left"

        JoyAxisEvent {
            axis: JoyAxisEvent.LeftX
            direction: JoyAxisEvent.Left
            deadzone: 0
        }

        KeyboardEvent {
            key: Qt.Key_A
            isPressed: true
        }

        KeyboardEvent {
            key: Qt.Key_Left
            isPressed: true
        }
    }

    InputAction {
        title: "Right"

        JoyAxisEvent {
            axis: JoyAxisEvent.LeftX
            direction: JoyAxisEvent.Right
            deadzone: 0
        }

        KeyboardEvent {
            key: Qt.Key_D
            isPressed: true
        }

        KeyboardEvent {
            key: Qt.Key_Right
            isPressed: true
        }
    }

    InputAction {
        title: "Up"

        JoyAxisEvent {
            axis: JoyAxisEvent.LeftY
            direction: JoyAxisEvent.Up
            deadzone: 0
        }
    }

    InputAction {
        title: "Down"

        JoyAxisEvent {
            axis: JoyAxisEvent.LeftY
            direction: JoyAxisEvent.Down
            deadzone: 0
        }
    }

    InputAction {
        title: "Shoot"

        JoyButtonEvent {
            button: JoyButtonEvent.RightShoulder
            isPressed: true
        }
    }

    InputAction {
        title: "Jump"

        JoyButtonEvent {
            button: JoyButtonEvent.A
            isPressed: true
        }

        KeyboardEvent {
            key: Qt.Key_Space
            isPressed: true
        }
    }
}
