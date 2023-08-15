// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtActionStore

ActionStore {
    id: actionStore
    property int device: JoyAxisEvent.Device0

    InputAction {
        title: "MoveUp"
        JoyAxisEvent {
            device: actionStore.device
            axis: JoyAxisEvent.LeftY
            direction: JoyAxisEvent.Up
            deadzone: 0
        }
        JoyButtonEvent {
            device: actionStore.device
            button: JoyButtonEvent.DpadUp
            isPressed: true
        }
        KeyboardEvent {
            id: upKey
            key:  actionStore.device === 0 ? "Key_W" : "Key_Up"
            isPressed: true
        }
    }

    InputAction {
        title: "MoveDown"
        JoyAxisEvent {
            device: actionStore.device
            axis: JoyAxisEvent.LeftY
            direction: JoyAxisEvent.Down
            deadzone: 0
        }
        JoyButtonEvent {
            device: actionStore.device
            button: JoyButtonEvent.DpadDown
            isPressed: true
        }
        KeyboardEvent {
            key: actionStore.device === 0 ? "Key_S" : "Key_Down"
            isPressed: true
        }
    }

    InputAction {
        title: "MoveStop"
        KeyboardEvent {
            id: stopUp
            key:  actionStore.device === 0 ? "Key_W" : "Key_Up"
            isPressed: false
        }
        KeyboardEvent {
            key: actionStore.device === 0 ? "Key_S" : "Key_Down"
            isPressed: false
        }
    }

    InputAction {
        title: "ReleaseMouse"
        KeyboardEvent {
            key: "Key_Escape"
            isPressed: true
        }
    }
}
