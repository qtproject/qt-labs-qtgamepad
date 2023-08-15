// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Rectangle {
    id: paddle
    color: "white"
    height: 80 * scale
    width: 10 * scale

    readonly property real topY: y - height * 0.5
    readonly property real bottomY: y + height * 0.5
    readonly property real leftX: x - width * 0.5
    readonly property real rightX: x + width * 0.5

    transform: [
        Translate { x: -paddle.width * 0.5; y: -paddle.height * 0.5 }
    ]

    property real scale: 1
    property real velocity: 0
    property real speed: 5 * 60

    function move(delta : real) : void {
        paddle.y += paddle.speed * scale * delta * paddle.velocity
    }
}
