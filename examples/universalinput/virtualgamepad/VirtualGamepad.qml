// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Layouts
import QtUniversalInput

Item {
    onWidthChanged: {
        resize()
    }

    onHeightChanged: {
        resize()
    }

    function resize() {
        let min = Math.min(width, height) * 0.35

        // Sticks

        leftStick.width = min
        leftStick.height = min

        rightStick.width = min
        rightStick.height = min

        leftStick.x = 4 * min / 3
        rightStick.x = width - 7 * min / 3

        leftStick.y = height - min - 10
        rightStick.y = height - min - 10

        // Buttons
        rightIsland.width = min
        rightIsland.height = min
        rightIsland.x = width - rightIsland.width - 20
        rightIsland.y = height - 5 * min / 3

        leftIsland.width = min
        leftIsland.height = min
        leftIsland.x = 20
        leftIsland.y = height - 5 * min / 3
    }

    Joystick {
        id: leftStick

        onUpdateReady: {
            console.log("left:" + value.x + ", " + value.y )
            let device = 0
            let leftX = 0;
            let leftY = 1;
            input.joyAxis(device, leftX, value.x)
            input.joyAxis(device, leftY, -value.y)
        }
    }

    Joystick {
        id: rightStick

        onUpdateReady: {
            let device = 0
            let rightX = 2;
            let rightY = 3;
            input.joyAxis(device, rightX, value.x)
            input.joyAxis(device, rightY, -value.y)
        }
    }

    ButtonIsland {
        id: rightIsland

        buttonA.onClicked: {
            input.joyButton(0, 0, 1)
        }

        buttonB.onClicked: {
            input.joyButton(0, 1, 1)
        }

        buttonX.onClicked: {
            input.joyButton(0, 2, 1)
        }

        buttonY.onClicked: {
            input.joyButton(0, 3, 1)
        }
    }

    ButtonIsland {
        id: leftIsland

        buttonB.text: "→"
        buttonA.text: "↓"
        buttonX.text: "←"
        buttonY.text: "↑"

        buttonA.onClicked: {
            input.joyHat(0, 4)
        }

        buttonB.onClicked: {
            input.joyHat(0, 2)
        }

        buttonX.onClicked: {
            input.joyHat(0, 8)
        }

        buttonY.onClicked: {
            input.joyHat(0, 1)
        }
    }

    UniversalInput {
        id: input
    }

    Component.onCompleted: {
        resize()
    }
}
