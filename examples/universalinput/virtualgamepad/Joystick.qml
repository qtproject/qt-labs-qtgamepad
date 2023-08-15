// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: joystick
    property real joystickRadius: width > height ? height * 0.5 : width * 0.5
    property real stickRadius: joystickRadius * 0.2
    property alias value: stick.position

    signal updateReady()

    width: 100
    height: 100

    FrameAnimation {
        running: true

        property vector2d previousPosition: Qt.vector2d(0, 0)

        onTriggered: {
            // If the stick is not in the deadzone, update the value
            const isInDeadzone = stick.position.length() < 0.05
            if (!isInDeadzone)
                joystick.updateReady()
        }
    }


    function normalizePosition(position) {
        return Qt.vector2d(position.x / joystickRadius, -position.y / joystickRadius);
    }

    Rectangle {
        id: joystickBg
        anchors.fill: parent
        color: "transparent"
        border.color: "black"
        border.width: 3
        radius: joystick.joystickRadius

        Item {
            id: stick
            property real xPos: 0
            property real yPos: 0
            property vector2d position: Qt.vector2d(0, 0)

            function resetPosition() {
                setPosition(Qt.point(0, 0));
                joystick.updateReady()
            }

            function setPosition(point) {
                xPos = point.x;
                yPos = point.y;
                position = normalizePosition(Qt.point(xPos, yPos));
                stickBg.x = xPos;
                stickBg.y = yPos;
            }

            width: 2 * joystick.stickRadius
            height: 2 * joystick.stickRadius
            anchors.centerIn: parent

            Rectangle {
                id: stickBg
                x: parent.width / 2 - width / 2
                y: parent.height / 2 - height / 2
                width: 2 * joystick.stickRadius
                height: 2 * joystick.stickRadius
                color: "gray"
                border.color: "black"
                border.width: 2
                radius: joystick.stickRadius

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    preventStealing: true
                    property real startX: 0
                    property real startY: 0

                    onPressed: {
                        startX = mouseX;
                        startY = mouseY;
                    }
                    onPositionChanged: {
                        var deltaX = stick.xPos + (mouseX - startX);
                        var deltaY = stick.yPos + (mouseY - startY);
                        var distance = Math.sqrt(deltaX * deltaX + deltaY * deltaY);

                        if (distance <= joystick.joystickRadius - joystick.stickRadius) {
                            stick.setPosition(Qt.point(deltaX, deltaY));
                        } else {
                            var maxDeltaX = (joystick.joystickRadius - joystick.stickRadius) * deltaX / distance;
                            var maxDeltaY = (joystick.joystickRadius - joystick.stickRadius) * deltaY / distance;
                            stick.setPosition(Qt.point(maxDeltaX, maxDeltaY));
                        }
                    }
                    onReleased: {
                        stick.resetPosition();
                    }
                }
            }
        }
    }
}
