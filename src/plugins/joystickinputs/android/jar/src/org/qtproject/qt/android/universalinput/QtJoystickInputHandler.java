// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/android/java/lib/src/org/godotengine/godot/input/GodotInputHandler.java" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

package org.qtproject.qt.android.universalinput;

import android.app.Activity;
import android.content.Context;
import android.hardware.input.InputManager;
import android.os.Build;
import android.util.Log;
import android.util.SparseArray;
import android.util.SparseIntArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class QtJoystickInputHandler implements InputManager.InputDeviceListener {

    private final SparseIntArray m_joystickIds = new SparseIntArray(4);
    private final SparseArray<Joystick> m_joystickDevices = new SparseArray<>(4);
    private final InputManager m_inputManager;
    Activity m_activity;
    private long m_nativePtr = 0;

    public QtJoystickInputHandler(Activity activity) {
        m_activity = activity;
        m_inputManager = (InputManager)activity.getSystemService(Context.INPUT_SERVICE);
    }

    public void register(long nativePtr)
    {
        synchronized (this) {
            if (m_inputManager != null) {
                m_nativePtr = nativePtr;
                m_activity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            m_inputManager.registerInputDeviceListener(QtJoystickInputHandler.this, null);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
                initInputDevices();
            }
        }
    }

    public void unregister()
    {
        synchronized (this) {
            if (m_inputManager != null) {
                m_nativePtr = 0;
                m_inputManager.unregisterInputDeviceListener(this);
            }
        }
    }

    private boolean isKeyEventGameDevice(int source) {
        if (source == (InputDevice.SOURCE_KEYBOARD | InputDevice.SOURCE_DPAD))
            return false;
        return (source & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK || (source & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD || (source & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD;
    }

    public boolean onKeyUp(final int keyCode, KeyEvent event) {
        int source = event.getSource();
        if (isKeyEventGameDevice(source)) {
            // Check if the device exists
            final int deviceId = event.getDeviceId();
            if (m_joystickIds.indexOfKey(deviceId) >= 0) {
                final int button = getButtonValue(keyCode);
                final int joyId = m_joystickIds.get(deviceId);
                joyButton(joyId, button, false);
                return true;
            }
        }

        return false;
    }

    public boolean onKeyDown(final int keyCode, KeyEvent event) {
        int source = event.getSource();
        final int deviceId = event.getDeviceId();
        // Check if source is a game device and that the device is a registered gamepad
        if (isKeyEventGameDevice(source)) {
            if (event.getRepeatCount() > 0) // ignore key echo
                return true;

            if (m_joystickIds.indexOfKey(deviceId) >= 0) {
                final int button = getButtonValue(keyCode);
                final int joyId = m_joystickIds.get(deviceId);
                joyButton(joyId, button, true);
                return true;
            }
        }

        return false;
    }

    public boolean onGenericMotionEvent(MotionEvent event) {
        if (event.isFromSource(InputDevice.SOURCE_JOYSTICK) && event.getActionMasked() == MotionEvent.ACTION_MOVE) {
            // Check if the device exists
            final int deviceId = event.getDeviceId();
            if (m_joystickIds.indexOfKey(deviceId) >= 0) {
                final int joyId = m_joystickIds.get(deviceId);
                Joystick joystick = m_joystickDevices.get(deviceId);
                if (joystick == null) {
                    return true;
                }

                for (int i = 0; i < joystick.axes.size(); i++) {
                    final int axis = joystick.axes.get(i);
                    final float value = event.getAxisValue(axis);
                    /*
                      As all axes are polled for each event, only fire an axis event if the value has actually changed.
                      Prevents flooding Godot with repeated events.
                     */
                    if (joystick.axesValues.indexOfKey(axis) < 0 || (float)joystick.axesValues.get(axis) != value) {
                        // save value to prevent repeats
                        joystick.axesValues.put(axis, value);
                        joyAxis(joyId, i, value);
                    }
                }

                if (joystick.hasAxisHat) {
                    final int hatX = Math.round(event.getAxisValue(MotionEvent.AXIS_HAT_X));
                    final int hatY = Math.round(event.getAxisValue(MotionEvent.AXIS_HAT_Y));
                    if (joystick.hatX != hatX || joystick.hatY != hatY) {
                        joystick.hatX = hatX;
                        joystick.hatY = hatY;
                        joyHat(joyId, hatX, hatY);
                    }
                }
                return true;
            }
        }

        return false;
    }

    public void initInputDevices() {
        int[] deviceIds = m_inputManager.getInputDeviceIds();
        for (int deviceId : deviceIds) {
            InputDevice device = m_inputManager.getInputDevice(deviceId);
            onInputDeviceAdded(deviceId);
        }
    }

    private int assignJoystickIdNumber(int deviceId) {
        int joyId = 0;
        while (m_joystickIds.indexOfValue(joyId) >= 0) {
            joyId++;
        }
        m_joystickIds.put(deviceId, joyId);
        return joyId;
    }

    @Override
    public void onInputDeviceAdded(int deviceId) {
        // Check if the device has not been already added

        if (m_joystickIds.indexOfKey(deviceId) >= 0) {
            return;
        }

        InputDevice device = m_inputManager.getInputDevice(deviceId);
        //device can be null if deviceId is not found
        if (device == null) {
            return;
        }

        int sources = device.getSources();

        // Device may not be a joystick or gamepad
        if ((sources & InputDevice.SOURCE_GAMEPAD) != InputDevice.SOURCE_GAMEPAD &&
                (sources & InputDevice.SOURCE_JOYSTICK) != InputDevice.SOURCE_JOYSTICK) {
            return;
        }

        // Assign first available number. Re-use numbers where possible.
        final int id = assignJoystickIdNumber(deviceId);

        final Joystick joystick = new Joystick();
        joystick.device_id = deviceId;
        joystick.name = device.getName();

        Set<Integer> already = new HashSet<>();
        for (InputDevice.MotionRange range : device.getMotionRanges()) {
            boolean isJoystick = range.isFromSource(InputDevice.SOURCE_JOYSTICK);
            boolean isGamepad = range.isFromSource(InputDevice.SOURCE_GAMEPAD);
            if (!isJoystick && !isGamepad) {
                continue;
            }
            final int axis = range.getAxis();
            if (axis == MotionEvent.AXIS_HAT_X || axis == MotionEvent.AXIS_HAT_Y) {
                joystick.hasAxisHat = true;
            } else {
                if (!already.contains(axis)) {
                    already.add(axis);
                    joystick.axes.add(axis);
                }
            }
        }
        Collections.sort(joystick.axes);
        m_joystickDevices.put(deviceId, joystick);

        joyConnectionChanged(id, true, joystick.name);
    }

    @Override
    public void onInputDeviceRemoved(int deviceId) {
        // Check if the device has not been already removed
        if (m_joystickIds.indexOfKey(deviceId) < 0) {
            return;
        }
        final int joyId = m_joystickIds.get(deviceId);
        m_joystickIds.delete(deviceId);
        m_joystickDevices.delete(deviceId);
        joyConnectionChanged(joyId, false, "");
    }

    @Override
    public void onInputDeviceChanged(int deviceId) {
        onInputDeviceRemoved(deviceId);
        onInputDeviceAdded(deviceId);
    }

    public static int getButtonValue(int keyCode) {
        int button;
        switch (keyCode) {
            case KeyEvent.KEYCODE_BUTTON_A:
                button = 0;
                break;
            case KeyEvent.KEYCODE_BUTTON_B:
                button = 1;
                break;
            case KeyEvent.KEYCODE_BUTTON_X:
                button = 2;
                break;
            case KeyEvent.KEYCODE_BUTTON_Y:
                button = 3;
                break;
            case KeyEvent.KEYCODE_BUTTON_L1:
                button = 9;
                break;
            case KeyEvent.KEYCODE_BUTTON_L2:
                button = 15;
                break;
            case KeyEvent.KEYCODE_BUTTON_R1:
                button = 10;
                break;
            case KeyEvent.KEYCODE_BUTTON_R2:
                button = 16;
                break;
            case KeyEvent.KEYCODE_BUTTON_SELECT:
                button = 4;
                break;
            case KeyEvent.KEYCODE_BUTTON_START:
                button = 6;
                break;
            case KeyEvent.KEYCODE_BUTTON_THUMBL:
                button = 7;
                break;
            case KeyEvent.KEYCODE_BUTTON_THUMBR:
                button = 8;
                break;
            case KeyEvent.KEYCODE_DPAD_UP:
                button = 11;
                break;
            case KeyEvent.KEYCODE_DPAD_DOWN:
                button = 12;
                break;
            case KeyEvent.KEYCODE_DPAD_LEFT:
                button = 13;
                break;
            case KeyEvent.KEYCODE_DPAD_RIGHT:
                button = 14;
                break;
            case KeyEvent.KEYCODE_BUTTON_C:
                button = 17;
                break;
            case KeyEvent.KEYCODE_BUTTON_Z:
                button = 18;
                break;

            default:
                button = keyCode - KeyEvent.KEYCODE_BUTTON_1 + 20;
                break;
        }
        return button;
    }

    private static native void joyConnectionChanged(int id, boolean connected, String name);
    private static native void joyButton(int id, int button, boolean pressed);
    private static native void joyAxis(int id, int axis, float value);
    private static native void joyHat(int id, int hatX, int hatY);
}
