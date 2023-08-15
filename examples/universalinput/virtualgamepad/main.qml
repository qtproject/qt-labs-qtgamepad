// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtUniversalInput

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 400
    title: "Virtual Gamepad"

    Rectangle {
        id: gameArea
        anchors.fill: parent
        color: "white"

        Rectangle {
            id: player
            width: 50
            height: 50
            color: "red"

            property double speed : 5
            property double velocityX : 0
            property double velocityY : 0
        }

        VirtualGamepad {
            anchors.fill: parent
        }

        FrameAnimation {
            running: true
            onTriggered: {
                player.x += player.velocityX * player.speed
                player.y += player.velocityY * player.speed
            }
        }
    }

    UniversalInput {
        onJoyButtonEvent: (device, button, isPressed) => {
            if (button === 0) {
                player.color = isPressed ? "blue" : "red";
            } else if (button === 1) {
                player.color = isPressed ? "green" : "red";
            }
        }
        onJoyAxisEvent: (device, axis, value) => {
                            let leftX =0;
                            let leftY =1;
                            let rightX = 2;
                            let rightY = 3;

                            //console.log(value)

                            if (axis === leftX) {
                                player.velocityX = value;
                            } else if (axis === leftY) {
                                player.velocityY = value;
                            }

                            if (axis === leftX && Math.abs(value) < 0.2) {
                                player.velocityX = 0;
                            }
                            if (axis === leftY && Math.abs(value) < 0.2) {
                                player.velocityY = 0;
                            }
                        }
    }
}
