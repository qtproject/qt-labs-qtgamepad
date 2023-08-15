// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Rectangle {
    id: ball
    color: "white"
    width: 20 * scale
    height: 20 * scale

    readonly property real topY: y - height * 0.5
    readonly property real bottomY: y + height * 0.5
    readonly property real leftX: x - width * 0.5
    readonly property real rightX: x + width * 0.5

    property real lastDX: 0

    transform: [
        Translate { x: -ball.width * 0.5; y: -ball.height * 0.5 }
    ]

    property real scale: 1
    property real dx: 3 * 60
    property real dy: 3 * 60

    function move(delta : real) : void {
        const dx = ball.dx * scale * delta;
        ball.x += dx
        ball.lastDX = dx
        ball.y += ball.dy * scale * delta
    }

    function reset() : void {
        ball.x = parent.width / 2 - ball.width / 2
        ball.y = parent.height / 2 - ball.height / 2
    }
}
