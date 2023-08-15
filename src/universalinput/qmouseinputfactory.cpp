// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qmouseinputfactory_p.h"
#include "qmouseinputplugin_p.h"
#include "qmouseinput_p.h"

#include <QtCore/private/qfactoryloader_p.h>

QT_BEGIN_NAMESPACE

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader, (QMouseInputFactoryInterface_iid, QLatin1String("/mouseinputs"), Qt::CaseInsensitive))

QStringList QMouseInputFactory::keys()
{
    return loader->keyMap().values();
}

QMouseInput *QMouseInputFactory::create(const QString &key, const QStringList &paramList)
{
    return qLoadPlugin<QMouseInput, QMouseInputPlugin>(loader(), key, paramList);
}

QT_END_NAMESPACE
