// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GAMEPADMONITOR_H
#define GAMEPADMONITOR_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QHash>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE
class QGamepad;
QT_END_NAMESPACE

class GamepadMonitor : public QObject
{
    Q_OBJECT
public:
    explicit GamepadMonitor(QObject *parent = 0);
    ~GamepadMonitor();

private:
    struct GamepadConnections {
        QGamepad *gamepad = nullptr;
        QList<QMetaObject::Connection> connections;
    };

    void connectGamepad(uint deviceId);
    void disconnectGamepad(uint deviceId);

    QHash<uint, GamepadConnections> m_gamepads;
};

#endif // GAMEPADMONITOR_H
