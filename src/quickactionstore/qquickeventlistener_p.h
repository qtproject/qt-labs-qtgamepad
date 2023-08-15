// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTQUICKEVENTLISTENER_H
#define QTQUICKEVENTLISTENER_H

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

#include <QObject>
#include <QQuickItem>
#include <QKeyEvent>
#include <QMouseEvent>

#include "qquickactionstore_p.h"

QT_BEGIN_NAMESPACE

class ActionStoreEventListener : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QQuickActionStore> actionStores READ actionStores)
    QML_ELEMENT

public:
    ActionStoreEventListener(QQuickItem *parent = nullptr);

    QQmlListProperty<QQuickActionStore> actionStores();
    static void appendActionHandler(QQmlListProperty<QQuickActionStore> *list, QQuickActionStore *action);
    static qsizetype countActionHandler(QQmlListProperty<QQuickActionStore> *list);
    static QQuickActionStore *atActionHandler(QQmlListProperty<QQuickActionStore> *list, qsizetype index);
    static void clearActionHandler(QQmlListProperty<QQuickActionStore> *list);

public Q_SLOTS:
    void sendKeyEvent(Qt::Key key, bool isPressed = true);
    void sendMouseButtonEvent(Qt::MouseButton button, bool isPressed = true);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QList<QQuickActionStore *> m_actionStores;
};

QT_END_NAMESPACE

#endif // QTQUICKEVENTLISTENER_H
