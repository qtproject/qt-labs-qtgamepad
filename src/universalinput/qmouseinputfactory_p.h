// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QMOUSEINPUTFACTORY_P_H
#define QMOUSEINPUTFACTORY_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtUniversalInput/private/qtuniversalinputglobal_p.h>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE

class QMouseInput;

class Q_UNIVERSALINPUT_EXPORT QMouseInputFactory
{
public:
    static QStringList keys();
    static QMouseInput *create(const QString &key, const QStringList &paramList);
};

QT_END_NAMESPACE

#endif // QMOUSEINPUTFACTORY_P_H
