// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*
  Originally based on code from "platform/macos/joypad_macos.h" from Godot Engine v4.0
  Copyright (c) 2014-present Godot Engine contributors
  Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.
*/

#ifndef MACOSJOYSTICKINPUT_H
#define MACOSJOYSTICKINPUT_H

#include <QtUniversalInput/private/qjoystickinput_p.h>
#include <QtCore/QVector>

#import <ForceFeedback/ForceFeedback.h>
#import <ForceFeedback/ForceFeedbackConstants.h>
#import <IOKit/hid/IOHIDLib.h>
#import <Kernel/IOKit/hidsystem/IOHIDUsageTables.h>

QT_BEGIN_NAMESPACE

struct RecElement {
    IOHIDElementRef ref;
    IOHIDElementCookie cookie;

    uint32_t usage = 0;

    int min = 0;
    int max = 0;

    struct Comparator {
        bool operator()(const RecElement p_a, const RecElement p_b) const { return p_a.usage < p_b.usage; }
    };
};

struct Joypad {
    IOHIDDeviceRef deviceRef = nullptr;

    QVector<RecElement> axisElements;
    QVector<RecElement> buttonElements;
    QVector<RecElement> hatElements;

    int id = 0;
    bool offsetHat = false;

    io_service_t forceFeedbackService = 0;
    FFCONSTANTFORCE forceFeedbackConstantForce;
    FFDeviceObjectReference forceFeedbackDevice = nullptr;
    FFEffectObjectReference forcefeedbackObject = nullptr;
    quint64 forceFeedbackTimestamp = 0;
    LONG *forceFeedbackDirections = nullptr;
    FFEFFECT forceFeedbackEffect;
    DWORD *forceFeedbackAxes = nullptr;

    void add_hid_elements(CFArrayRef p_array);
    void add_hid_element(IOHIDElementRef p_element);

    bool has_element(IOHIDElementCookie p_cookie, QVector<RecElement> *p_list) const;
    bool config_force_feedback(io_service_t p_service);
    bool check_ff_features();

    int get_hid_element_state(RecElement *p_element) const;

    void free();
    Joypad();
};

class MacOsJoystickInput : public QJoystickInput
{
    Q_OBJECT
public:
    MacOsJoystickInput();
    ~MacOsJoystickInput();

    void processJoypads();

    void deviceAdded(IOReturn p_res, IOHIDDeviceRef p_devic);
    void deviceRemoved(IOReturn p_res, IOHIDDeviceRef p_device);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    bool have_device(IOHIDDeviceRef p_device) const;
    bool configure_joypad(IOHIDDeviceRef p_device_ref, Joypad *p_joy);

    int get_joy_index(int p_id) const;
    int get_joy_ref(IOHIDDeviceRef p_device) const;

    void poll_joypads() const;
    void config_hid_manager(CFArrayRef p_matching_array) const;

    void joypad_vibration_start(int p_id, float p_magnitude, float p_duration, uint64_t p_timestamp);
    void joypad_vibration_stop(int p_id, uint64_t p_timestamp);


    IOHIDManagerRef m_hidManager;
    QVector<Joypad> m_deviceList;
};

QT_END_NAMESPACE

#endif // MACOSJOYSTICKINPUT_H
