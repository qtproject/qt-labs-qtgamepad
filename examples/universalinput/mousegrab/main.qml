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
    title: "Mousegrab"

    Rectangle {
        id: gameArea
        width: parent.width
        height: parent.height
        color: "gray"

        Rectangle {
            id: player
            width: 10
            height: 10
            color: "red"

            Component.onCompleted: {
                resetPosition()
            }

            function resetPosition() {
                x = parent.width / 2 - width / 2
                y = parent.height / 2 - height / 2
            }

            function move(amount) {
                x += amount.x
                y += amount.y
            }
        }

        Keys.onPressed: event => {
                            if (event.key === Qt.Key_Escape) {
                                gameArea.focus = false
                            }
                        }

        onFocusChanged: {
            universalInput.mouseDisabled = focus
            if (focus) {
                player.resetPosition()
                universalInput.firstFramesAfterFocus = true
            }

        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                gameArea.focus = true
            }
        }

        Label {
            x: 10
            y: 10
            text: "Press ESC to release mouse"
        }

        Label {
            x: 10
            y: 30
            text: "Click to grab mouse"
        }

        Label {
            id: deltaLabel
            x: 10
            y: 50
            text: "Mouse deltas: (0,0)"
        }
    }

    UniversalInput {
        id: universalInput
        mouseDisabled: gameArea.focus

        property bool firstFramesAfterFocus: false
        property int frameCount: 0

        onMouseDeltaChanged: delta => {
                                 deltaLabel.text = "Mouse deltas: (" + delta.x + "," + delta.y + ")"

                                if (mouseDisabled) {
                                     // Big delta after focus is received, so delay the action
                                     if (firstFramesAfterFocus) {
                                         if (frameCount < 1) {
                                             ++frameCount
                                             return
                                         }
                                         frameCount = 0
                                         firstFramesAfterFocus = false
                                         return
                                     }
                                     player.move(delta)
                                 }
                             }
    }
}
