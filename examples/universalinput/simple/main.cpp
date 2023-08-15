// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtCore/QCoreApplication>
#include "gamepadmonitor.h"

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    GamepadMonitor monitor;

    return application.exec();
}
