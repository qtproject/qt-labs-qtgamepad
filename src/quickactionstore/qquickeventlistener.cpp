// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qquickeventlistener_p.h"

#include <QKeyEvent>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE

ActionStoreEventListener::ActionStoreEventListener(QQuickItem *parent)
    : QQuickItem(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setOpacity(0.0);
}

QQmlListProperty<QQuickActionStore> ActionStoreEventListener::actionStores()
{
    return QQmlListProperty<QQuickActionStore>(this, nullptr,
                                               &ActionStoreEventListener::appendActionHandler,
                                               &ActionStoreEventListener::countActionHandler,
                                               &ActionStoreEventListener::atActionHandler,
                                               &ActionStoreEventListener::clearActionHandler);
}

void ActionStoreEventListener::appendActionHandler(QQmlListProperty<QQuickActionStore> *list, QQuickActionStore *action)
{
    auto *Listener = static_cast<ActionStoreEventListener *>(list->object);
    Listener->m_actionStores.append(action);
}

qsizetype ActionStoreEventListener::countActionHandler(QQmlListProperty<QQuickActionStore> *list)
{
    auto *Listener = static_cast<ActionStoreEventListener *>(list->object);
    return Listener->m_actionStores.count();
}

QQuickActionStore *ActionStoreEventListener::atActionHandler(QQmlListProperty<QQuickActionStore> *list, qsizetype index)
{
    auto *Listener = static_cast<ActionStoreEventListener *>(list->object);
    return Listener->m_actionStores.at(index);
}

void ActionStoreEventListener::clearActionHandler(QQmlListProperty<QQuickActionStore> *list)
{
    auto *Listener = static_cast<ActionStoreEventListener *>(list->object);
    Listener->m_actionStores.clear();
}

void ActionStoreEventListener::sendKeyEvent(Qt::Key key, bool isPressed)
{
    for (auto *store : m_actionStores)
        store->sendKeyEvent(key, isPressed);
}

void ActionStoreEventListener::sendMouseButtonEvent(Qt::MouseButton button, bool isPressed)
{
    for (auto *store : m_actionStores)
        store->sendMouseButtonEvent(button, isPressed);
}

void ActionStoreEventListener::keyPressEvent(QKeyEvent *event)
{
    for (auto *store : m_actionStores)
        store->sendKeyEvent(Qt::Key(event->key()), true);

    QQuickItem::keyPressEvent(event);
}

void ActionStoreEventListener::keyReleaseEvent(QKeyEvent *event)
{
    for (auto *store : m_actionStores)
        store->sendKeyEvent(Qt::Key(event->key()), false);

    QQuickItem::keyReleaseEvent(event);
}

void ActionStoreEventListener::mousePressEvent(QMouseEvent *event)
{
    for (auto *store : m_actionStores)
        store->sendMouseButtonEvent(event->button(), true);

    QQuickItem::mousePressEvent(event);
}

void ActionStoreEventListener::mouseReleaseEvent(QMouseEvent *event)
{
    for (auto *store : m_actionStores)
        store->sendMouseButtonEvent(event->button(), false);

    QQuickItem::mouseReleaseEvent(event);
}

QT_END_NAMESPACE
