// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/macos/joypad_macos.cpp" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

#include "macosmouseinput.h"
#include <QtUniversalInput/QUniversalInput>
#include <QtEndian>

#include <AppKit/AppKit.h>
#include <CoreGraphics/CoreGraphics.h>

#include <QCursor>
#include <QGuiApplication>

QT_BEGIN_NAMESPACE

static MacOsMouseInput *self = nullptr;

MacOsMouseInput::MacOsMouseInput()
{
    self = this;

    m_timer = new QTimer(this);
    m_timer->setInterval(1);
    connect(m_timer, &QTimer::timeout, this, &MacOsMouseInput::onUpdate);
    m_timer->start();
}

MacOsMouseInput::~MacOsMouseInput()
{
    self = nullptr;
    m_timer->stop();
    delete m_timer;
}

QVector2D MacOsMouseInput::getMouseDelta()
{
    // kind of a hack, but it works for now
    static NSPoint previousLocation;
    NSPoint currentLocation = [NSEvent mouseLocation];
    CGPoint delta = CGPointMake(currentLocation.x - previousLocation.x, currentLocation.y - previousLocation.y);
    previousLocation = currentLocation;
    return QVector2D(float(delta.x), float(delta.y));
}

void MacOsMouseInput::setCursorCenterOfWindow()
{
    NSRect windowRect = [[NSApp mainWindow] frame];
    NSPoint windowCenter = NSMakePoint(NSMidX(windowRect), NSMidY(windowRect));
    CGWarpMouseCursorPosition(windowCenter);
}

void MacOsMouseInput::onUpdate()
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
