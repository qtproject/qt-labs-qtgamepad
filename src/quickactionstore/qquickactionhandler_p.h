// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTQUICKACTIONHANDLER_H
#define QTQUICKACTIONHANDLER_H


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

#include "qquickactionstore_p.h"

QT_BEGIN_NAMESPACE

class QQuickActionHandler : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ActionHandler)
    Q_PROPERTY(QString actionTitle READ actionTitle WRITE setActionTitle NOTIFY actionTitleChanged)
    Q_PROPERTY(QQuickActionStore* actionStore READ actionStore WRITE setActionStore NOTIFY actionStoreChanged)
    Q_PROPERTY(Source source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_ENUMS(Source)

public:
    enum class Source {
        Key,
        MouseButton,
        Touch,
        JoyButton,
        JoyAxis,
        Other
    };
    QQuickActionHandler(QObject *parent = nullptr);
    ~QQuickActionHandler() override = default;

    void setActionStore(QQuickActionStore *actionStore);
    QQuickActionStore* actionStore() const;

    void setActionTitle(const QString &actionName);
    QString actionTitle() const;

    void setSource(Source source);
    Source source() const;

    void setValue(float value);
    float value() const;

Q_SIGNALS:
    void actionStoreChanged();
    void actionTitleChanged();
    void sourceChanged();
    void valueChanged();
    void triggered();


private:
    QQuickActionStore *m_actionStore;
    QString m_actionTitle;
    Source m_source;
    float m_value;
};

class QQuickActionDispatch : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ActionDispatch)
    Q_PROPERTY(QQuickActionStore* actionStore READ actionStore WRITE setActionStore NOTIFY actionStoreChanged)
    Q_PROPERTY(QQmlListProperty<QQuickActionHandler> handlers READ handlers NOTIFY handlersChanged)
    Q_CLASSINFO("DefaultProperty", "handlers")

public:
    QQuickActionDispatch(QObject *parent = nullptr);
    ~QQuickActionDispatch() override = default;

    void setActionStore(QQuickActionStore *actionStore);
    QQuickActionStore* actionStore() const;

    QQmlListProperty<QQuickActionHandler> handlers();
    static void appendActionHandler(QQmlListProperty<QQuickActionHandler> *list, QQuickActionHandler *action);
    static qsizetype countActionHandler(QQmlListProperty<QQuickActionHandler> *list);
    static QQuickActionHandler *atActionHandler(QQmlListProperty<QQuickActionHandler> *list, qsizetype index);
    static void clearActionHandler(QQmlListProperty<QQuickActionHandler> *list);

Q_SIGNALS:
    void actionStoreChanged();
    void handlersChanged();

private:
    QQuickActionStore *m_actionStore;
    QList<QQuickActionHandler*> m_handlers;
};

QT_END_NAMESPACE

#endif // QTQUICKACTIONHANDLER_H
