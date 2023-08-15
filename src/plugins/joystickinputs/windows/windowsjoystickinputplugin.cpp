// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "windowsjoystickinputplugin.h"
#include "windowsjoystickinput.h"

QT_BEGIN_NAMESPACE

QJoystickInput *WindowsJoystickInputPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    if (key == QLatin1String("windows"))
        return new WindowsJoystickInput();
    return nullptr;
}

QT_END_NAMESPACE
