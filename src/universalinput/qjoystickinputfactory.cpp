// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qjoystickinputfactory_p.h"
#include "qjoystickinputplugin_p.h"
#include "qjoystickinput_p.h"

#include <QtCore/private/qfactoryloader_p.h>

QT_BEGIN_NAMESPACE

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader, (QJoystickInputFactoryInterface_iid, QLatin1String("/joystickinputs"), Qt::CaseInsensitive))

QStringList QJoystickInputFactory::keys()
{
    return loader->keyMap().values();
}

QJoystickInput *QJoystickInputFactory::create(const QString &key, const QStringList &paramList)
{
    return qLoadPlugin<QJoystickInput, QJoystickInputPlugin>(loader(), key, paramList);
}

QT_END_NAMESPACE
