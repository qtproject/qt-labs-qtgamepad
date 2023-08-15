// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Rectangle {
    property vector2d velocity: Qt.vector2d(0,0)
    property double velocityY: velocity.y
    property bool gravity: true

    function update() {
        goUpdate()
    }

    function goUpdate() {
        x += velocity.x
        y += velocity.y
    }

    function colliding(other: GameObject): bool {
        return x < other.x + other.width &&
               x + width > other.x &&
               y < other.y + other.height &&
               y + height > other.y
    }

    onVelocityChanged: {
        velocityY = velocity.y
    }

}
