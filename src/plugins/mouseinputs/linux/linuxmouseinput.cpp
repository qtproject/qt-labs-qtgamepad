// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/macos/joypad_macos.cpp" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

#include "linuxmouseinput.h"
#include <QtUniversalInput/QUniversalInput>
#include <QtEndian>

#include <QCursor>
#include <QGuiApplication>
#include <QWindow>
#include <QDateTime>

#include <QCursor>

QT_BEGIN_NAMESPACE

static LinuxMouseInput *self = nullptr;

LinuxMouseInput::LinuxMouseInput()
{
    self = this;

    m_timer = new QTimer(this);
    m_timer->setInterval(1);
    connect(m_timer, &QTimer::timeout, this, &LinuxMouseInput::onUpdate);
    m_timer->start();
}

LinuxMouseInput::~LinuxMouseInput()
{
    self = nullptr;
    m_timer->stop();
    delete m_timer;
}

QVector2D LinuxMouseInput::getMouseDelta()
{
    static QPoint lastPos = QCursor::pos();
    QPoint newPos = QCursor::pos();
    QVector2D delta = QVector2D(newPos.toPointF() - lastPos.toPointF());
    lastPos = newPos;
    return delta;
}

void LinuxMouseInput::setCursorCenterOfWindow()
{
    QWindow* window = QGuiApplication::focusWindow();
    if (!window)
        return;
    QPoint center = window->geometry().center();
    QCursor::setPos(center);
}

void LinuxMouseInput::onUpdate()
{
    if (!self)
        return;

    auto input = QUniversalInput::instance();

    QVector2D delta = getMouseDelta();
    if (delta.x() == 0 && delta.y() == 0)
        return;

    input->mouseMove(delta);

    if (input->isMouseDisabled()) {
        setCursorCenterOfWindow();
        // set cursor to blank
        QGuiApplication::setOverrideCursor(Qt::BlankCursor);
        m_wasDisabled = true;
    } else if (m_wasDisabled) {
        QGuiApplication::setOverrideCursor(Qt::ArrowCursor);
        m_wasDisabled = false;
    }
}

QT_END_NAMESPACE
