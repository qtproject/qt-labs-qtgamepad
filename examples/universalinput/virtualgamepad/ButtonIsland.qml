// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    property alias buttonA: buttonA
    property alias buttonB: buttonB
    property alias buttonX: buttonX
    property alias buttonY: buttonY

    width: 100
    height: 100

    onScaleChanged: {
        resize()
    }

    onXChanged: {
        resize()
    }

    onYChanged: {
        resize()
    }

    onWidthChanged: {
        resize()
    }

    onHeightChanged: {
        resize()
    }

    function resize() {
        let scale = Math.min(width, height) / 3

        buttonA.width = scale
        buttonA.height = scale

        buttonB.width = scale
        buttonB.height = scale

        buttonX.width = scale
        buttonX.height = scale

        buttonY.width = scale
        buttonY.height = scale

        let middleX = (width - scale) / 2
        let middleY = (height - scale) / 2

        buttonB.x = width - scale
        buttonB.y = middleY

        buttonY.x = middleX
        buttonY.y = 0

        buttonX.x = 0
        buttonX.y = middleY

        buttonA.x = middleX
        buttonA.y = height - scale
    }

    JoyButton {
        id: buttonA
        text: "A"
    }

    JoyButton {
        id: buttonB
        text: "B"
    }

    JoyButton {
        id: buttonX
        text: "X"
    }

    JoyButton {
        id: buttonY
        text: "Y"
    }
}
