// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/macos/joypad_macos.h" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

#ifndef MACOSMOUSEINPUT_H
#define MACOSMOUSEINPUT_H

#include <QtUniversalInput/private/qmouseinput_p.h>

#include <QTimer>
#include <QVector2D>

QT_BEGIN_NAMESPACE

class MacOsMouseInput : public QMouseInput
{
    Q_OBJECT
public:
    MacOsMouseInput();
    ~MacOsMouseInput();

    QVector2D getMouseDelta();
    void setCursorCenterOfWindow();


public Q_SLOTS:
    void onUpdate();

private:
    QTimer* m_timer = nullptr;
    bool m_wasDisabled = false;
};

QT_END_NAMESPACE

#endif // MACOSMOUSEINPUT_H
