// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QMOUSEINPUT_P_H
#define QMOUSEINPUT_P_H

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

#include <QtCore/qobject.h>
#include <QtUniversalInput/private/qtuniversalinputglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_UNIVERSALINPUT_EXPORT QMouseInput : public QObject
{
    Q_OBJECT
};

QT_END_NAMESPACE

#endif // QMOUSEINPUT_P_H
