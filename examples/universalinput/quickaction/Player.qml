// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtActionStore

GameObject {
    id: player

    property Controller controller
    property double playerSpeed: 3

    function update() {
        goUpdate() // does GameObject update functionality
    }

    ActionDispatch {
        actionStore: controller

        ActionHandler {
            actionTitle: "Left"
            onTriggered: {
                velocity.x = value * -playerSpeed
            }
        }

        ActionHandler {
            actionTitle: "Right"
            onTriggered: {
                velocity.x = value * playerSpeed
            }
        }

        ActionHandler {
            actionTitle: "Jump"
            onTriggered: {
                let force = -15
                velocity.y += force
            }
        }
    }

    function handleCollision(other: GameObject) {
        if (x + width > other.x && x < other.x) {
            // Left
            x = other.x - width
        } else if (x < other.x + other.width && x + width > other.x + other.width) {
            // Right
            x = other.x + other.width
        }

        if (y + height > other.y && y < other.y) {
            // Top
            y = other.y - height
            velocity.y = 0
        } else if (y < other.y + other.height && y + height > other.y + other.height) {
            // Bottom
            y = other.y + other.height
            velocity.y = 0
        }
    }
}
