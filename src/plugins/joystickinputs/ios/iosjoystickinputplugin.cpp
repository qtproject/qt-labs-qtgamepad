// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "iosjoystickinputplugin.h"
#include "iosjoystickinput.h"

QT_BEGIN_NAMESPACE

QJoystickInput *IosJoystickInputPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    if (key == QLatin1String("ios"))
        return new IosJoystickInput();
    return nullptr;
}

QT_END_NAMESPACE
