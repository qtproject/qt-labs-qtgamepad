// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/android/java/lib/src/org/godotengine/godot/input/Joystick.java" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

package org.qtproject.qt.android.universalinput;

import android.util.SparseArray;

import java.util.ArrayList;
import java.util.List;

class Joystick {
    int device_id;
    String name;
    List<Integer> axes = new ArrayList<>();
    protected boolean hasAxisHat = false;
    /*
     * Keep track of values so we can prevent flooding the engine with useless events.
     */
    protected final SparseArray<Float> axesValues = new SparseArray<>(4);
    protected int hatX;
    protected int hatY;
}
