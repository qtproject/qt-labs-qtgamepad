// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtActionStore

Item {
    id: paddleController
    required property ActionMap actionMap
    required property Paddle paddle

    ActionDispatch {
        actionStore: paddleController.actionMap

        ActionHandler {
            actionTitle: "MoveUp"
            onTriggered: {
                if (source === ActionHandler.Key) {
                    paddleController.paddle.velocity = -1
                } else if (source === ActionHandler.JoyAxis) {
                    paddleController.paddle.velocity = -value > 0.2 ? value : 0
                }
            }
        }

        ActionHandler {
            actionTitle: "MoveDown"
            onTriggered: {
                if (source === ActionHandler.Key) {
                    paddleController.paddle.velocity = 1
                } else if (source === ActionHandler.JoyAxis) {
                    paddleController.paddle.velocity = value > 0.2 ? value : 0
                }
            }
        }

        ActionHandler {
            actionTitle: "MoveStop"
            onTriggered: {
                paddleController.paddle.velocity = 0
            }
        }
    }
}
