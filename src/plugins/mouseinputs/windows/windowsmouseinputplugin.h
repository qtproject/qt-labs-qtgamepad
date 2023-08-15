// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef WINDOWSMOUSEINPUTPLUGIN_H
#define WINDOWSMOUSEINPUTPLUGIN_H

#include <QtUniversalInput/private/qmouseinputplugin_p.h>
#include <QtUniversalInput/private/qmouseinput_p.h>

QT_BEGIN_NAMESPACE

class WindowsMouseInputPlugin : public QMouseInputPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMouseInputFactoryInterface_iid FILE "windows.json")

public:
    QMouseInput *create(const QString &key, const QStringList &paramList) override;
};

QT_END_NAMESPACE

#endif // WINDOWSMOUSEINPUTPLUGIN_H
