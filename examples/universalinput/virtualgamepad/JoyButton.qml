// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: joyButton

    width: 50
    height: 50

    property string text: ""

    signal clicked()

    onTextChanged: {
        textLabel.text = text
    }

    Rectangle {
        anchors.fill: parent
        color: "gray"
        opacity: 0.9
        radius: width/2

        Text {
            id: textLabel
            anchors.centerIn: parent
            text: ""
            color: "#333333"
            font.pixelSize: 20
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                joyButton.clicked()
            }
        }
    }
}
