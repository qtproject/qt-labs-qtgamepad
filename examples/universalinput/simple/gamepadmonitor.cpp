// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "gamepadmonitor.h"
#include <QtGamepad/QGamepad>

#include <QDebug>
#include <QLoggingCategory>
#include <QtUniversalInput/QUniversalInput>

GamepadMonitor::GamepadMonitor(QObject *parent)
    : QObject(parent)
{
    auto inputManager = QUniversalInput::instance();
    connect(inputManager, &QUniversalInput::joyConnectionChanged, this, [this](int index, bool isConnected) {
        if (index < 0)
            return;

        if (isConnected) {
            qDebug() << "Gamepad connected:" << index;
            connectGamepad(uint(index));
        } else {
            qDebug() << "Gamepad disconnected:" << index;
            disconnectGamepad(uint(index));
        }
    });
}

GamepadMonitor::~GamepadMonitor()
{
    const auto keys = m_gamepads.keys();
    for (const auto key : keys)
        disconnectGamepad(key);
}

void GamepadMonitor::connectGamepad(uint deviceId)
{
    GamepadConnections gamepadData;
    auto gamepad = new QGamepad(deviceId, this);
    gamepadData.gamepad = gamepad;
    gamepadData.connections.append(connect(gamepad, &QGamepad::axisLeftXChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Left X" << gamepad->axisLeftX();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::axisLeftYChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Left Y" << gamepad->axisLeftY();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::axisRightXChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Right X" << gamepad->axisRightX();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::axisRightYChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Right Y" << gamepad->axisRightY();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonAChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button A" << gamepad->buttonA();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonBChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button B" << gamepad->buttonB();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonXChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button X" << gamepad->buttonX();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonYChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Y" << gamepad->buttonY();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonL1Changed, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button L1" << gamepad->buttonL1();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonR1Changed, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button R1" << gamepad->buttonR1();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonL2Changed, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button L2: " << gamepad->buttonL2();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonR2Changed, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button R2: " << gamepad->buttonR2();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonSelectChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Select" << gamepad->buttonSelect();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonStartChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Start" << gamepad->buttonStart();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonGuideChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Guide" << gamepad->buttonGuide();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonRightChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Dpad Right" << gamepad->buttonRight();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonLeftChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Dpad Left" << gamepad->buttonLeft();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonUpChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Dpad Up" << gamepad->buttonUp();
    }));
    gamepadData.connections.append(connect(gamepad, &QGamepad::buttonDownChanged, this, [gamepad, deviceId](){
        qDebug() << "Device: " << deviceId << " Button Dpad Down" << gamepad->buttonDown();
    }));

    m_gamepads.insert(deviceId, gamepadData);
}

void GamepadMonitor::disconnectGamepad(uint deviceId)
{
    auto gamepadData = m_gamepads.find(deviceId);

    if (gamepadData != m_gamepads.end()) {
        for (auto connection : gamepadData->connections) {
            disconnect(connection);
        }
        delete gamepadData->gamepad;
        m_gamepads.erase(gamepadData);
    }
}
