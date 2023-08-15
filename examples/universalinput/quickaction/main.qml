// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtActionStore

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: "Platforms"

    Rectangle {
        id: gameArea
        width: parent.width
        height: parent.height
        color: "black"

        property int paddleWidth: 10
        property int paddleHeight: 80
        property double gravity: 0.5

        GameObjectList {
            id: gameObjectList
            gameObjects: [p1, p2, p3, p4, p5]
        }

        Player {
            id: player
            width: 20
            height: 20
            color: "red"
            controller: Controller {}
        }

        Platform {
            id: p1
            x: 0
            y: 575
            width: 800
            height: 50
        }

        Platform {
            id: p2
            x: 30
            y: 500
            width: 300
            height: 50
        }

        Platform {
            id: p3
            x: 100
            y: 400
            width: 300
            height: 50
        }

        Platform {
            id: p4
            x: 0
            y: 300
            width: 300
            height: 50
        }

        Platform {
            id: p5
            x: 300
            y: 200
            width: 300
            height: 50
        }

        function updateGame(delta : real) : void {
            // Gravity
            player.velocity.y += gravity

            // Updates position based on velocity
            player.update()

            // Handle collisions
            gameObjectList.gameObjects.forEach(gameObject => {
                if (player.colliding(gameObject))
                    player.handleCollision(gameObject)
            })

            // Player bounds check
            if (player.x < 0)
                player.x = 0
            else if (player.x > width - player.width)
                player.x = width - player.width

            if (player.y < 0)
                player.y = 0
            else if (player.y > height - player.height)
                player.y = height - player.height
        }

        FrameAnimation {
            running: true
            onTriggered: gameArea.updateGame(frameTime)
        }
    }

    ActionStoreEventListener {
        id: actionEventListener
        actionStores: [player.controller]
        focus: true
    }
}
