// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef IOSJOYSTICKINPUT_H
#define IOSJOYSTICKINPUT_H

#include <QtCore/QObject>
#include <QtUniversalInput/private/qjoystickinput_p.h>

Q_FORWARD_DECLARE_OBJC_CLASS(JoypadIOSObserver);

QT_BEGIN_NAMESPACE

class IosJoystickInput : public QJoystickInput{
public:
    IosJoystickInput();
    ~IosJoystickInput();

    void startProcessing();

private:
    JoypadIOSObserver *m_observer;
};

QT_END_NAMESPACE

#endif // IOSJOYSTICKINPUT_H
