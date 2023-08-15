// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtActionStore
import QtUniversalInput

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 400
    title: "Paddles"

    property double scale: 1

    function updateScale() : void {
        scale = Math.min(mainWindow.width / 800, mainWindow.height / 400)
    }

    onWidthChanged: updateScale()
    onHeightChanged: updateScale()

    Rectangle {
        id: gameArea
        anchors.fill: parent
        color: "black"

        property int player1Score: 0
        property int player2Score: 0

        Paddle {
            id: paddle1
            scale: mainWindow.scale
            x: 10 + width * 0.5
            y: gameArea.height * 0.5
        }

        Paddle {
            id: paddle2
            scale: mainWindow.scale
            x: gameArea.width - 10 - width * 0.5
            y: gameArea.height * 0.5
        }

        Ball {
            id: ball
            scale: mainWindow.scale
            x: gameArea.width * 0.5
            y: gameArea.height * 0.5
        }

        function handleCollisions(deltaTime : real) : void {
            if (ball.topY <= 0 || ball.bottomY >= gameArea.height)
                ball.dy = -ball.dy

            let ff_duration = 0.1
            let ff_strength = 0.5

            let hit = false
            let device = null
            if (ball.leftX <= paddle1.rightX && ball.bottomY >= paddle1.topY && ball.topY <= paddle1.bottomY) {
                hit = true
                device = actionMapPlayer1.device
            }

            if (ball.rightX >= paddle2.leftX && ball.bottomY >= paddle2.topY && ball.topY <= paddle2.bottomY) {
                hit = true
                device = actionMapPlayer2.device
            }

            if (hit) {
                ball.x -= ball.lastDX
                ball.dx = -ball.dx
                universalInput.addForce(device, Qt.vector2d(ff_strength, ff_strength), ff_duration)
            }

            if (ball.leftX <= 0 || ball.rightX >= gameArea.width) {
                if (ball.x <= 0)
                    gameArea.player2Score += 1
                else
                    gameArea.player1Score += 1

                ball.reset()
            }

            handlePaddleInBounds(paddle1)
            handlePaddleInBounds(paddle2)
        }

        function handlePaddleInBounds(paddle : Paddle) : void {
            if (paddle.topY < 0)
                paddle.y = paddle1.height * 0.5

            if (paddle.bottomY >= gameArea.height)
                paddle.y = gameArea.height - paddle.height * 0.5
        }

        FrameAnimation {
            id: frameTimer
            running: true
            onTriggered: {
                paddle1.move(frameTime)
                paddle2.move(frameTime)
                ball.move(frameTime)
                gameArea.handleCollisions(frameTime)
            }
        }

        Label {
            id: scoreLabel
            anchors.horizontalCenter: parent.horizontalCenter
            y: 20
            text: gameArea.player1Score + " - " + gameArea.player2Score
            color: "white"
            font.pixelSize: 40
            font.weight: Font.ExtraBold
        }

        // Mouse solution. Have to propagate mouse events to actionStores
        MouseArea {
            anchors.fill: parent
            onPressed: event => actionEventListener.sendMouseButtonEvent(event, true)
            onReleased: event => actionEventListener.sendMouseButtonEvent(event, false)
        }
    }

    Label {
        x: 10
        y: 10
        text: "Press ESC to release mouse"
        color: "white"
    }

    // Player 1 actions
    ActionMap {
        id: actionMapPlayer1
        device: ActionMap.Device0
    }

    PaddleController {
        paddle: paddle1
        actionMap: actionMapPlayer1
    }


    // Player 2 actions
    ActionMap {
        id: actionMapPlayer2
        device: ActionMap.Device1
    }

    PaddleController {
        paddle: paddle2
        actionMap: actionMapPlayer2
    }

    // Distributes key and mouse events for actionStores
    ActionStoreEventListener {
        id: actionEventListener
        actionStores: [actionMapPlayer1, actionMapPlayer2]
        focus: true
    }

    // Using actionMap to listen for mouse events such that we can release the mouse.
    // Also an example of standalone ActionHandler.
    ActionHandler {
        actionStore: actionMapPlayer1
        actionTitle: "ReleaseMouse"
        onTriggered: {
            universalInput.mouseDisabled = false
        }
    }

    UniversalInput {
        id: universalInput
        mouseDisabled: true
    }
}
