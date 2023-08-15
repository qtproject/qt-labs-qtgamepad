// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTQUICKGAMEPAD_H
#define QTQUICKGAMEPAD_H

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


#include <QtGamepad/QGamepad>
#include <QtQml/QQmlEngine>

QT_BEGIN_NAMESPACE

class QQuickGamepad : public QGamepad {
    Q_OBJECT
    QML_NAMED_ELEMENT(Gamepad)
public:
    QQuickGamepad(QObject *parent = nullptr);
    ~QQuickGamepad();

};


QT_END_NAMESPACE

#endif // QTQUICKGAMEPAD_H
