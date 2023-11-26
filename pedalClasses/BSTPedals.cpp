#include "BSTPedals.h"

void BSTPedals_::joySetup()
{
    Joystick->setThrottleRange(0, 255);
    Joystick->setAcceleratorRange(0, 255);
    Joystick->setBrakeRange(0, 255);
    Joystick->setXAxisRange(0, 255);
    Joystick->setYAxisRange(0, 255);
    Joystick->setZAxisRange(0, 255);
    Joystick->setRxAxisRange(0, 255);
    Joystick->setRyAxisRange(0, 255);
    Joystick->setRzAxisRange(0, 255);
    Joystick->setRudderRange(0, 255);
    Joystick->setSteeringRange(0, 255);

    Joystick->begin(false);

    Joystick->setThrottle(127);
    Joystick->setAccelerator(127);
    Joystick->setBrake(127);
    Joystick->setXAxis(127);
    Joystick->setYAxis(127);
    Joystick->setZAxis(127);
    Joystick->setRxAxis(127);
    Joystick->setRyAxis(127);
    Joystick->setRzAxis(127);
    Joystick->setRudder(127);
    Joystick->setSteering(127);

    Joystick->sendState();
}

void BSTPedals_::Worker()
{
    serialHandler.Worker();
    clutch.Worker();
    gas.Worker();
    brake.Worker();

    Joystick->setYAxis(clutch.getmappedValue());
    Joystick->setZAxis(brake.getmappedValue());
    Joystick->setXAxis(gas.getmappedValue());

    Joystick->sendState();
}