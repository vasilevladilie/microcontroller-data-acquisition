/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>


// Blinking rate in milliseconds
#define BLINKING_RATE       500ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);
    DigitalIn userButton(BUTTON1);
    PwmOut ledModulated1(PE_6);
    ledModulated1.period(0.001f);
    ledModulated1.write(0.0f);
    PwmOut ledModulated2(PB_8);
    ledModulated2.period(0.001f);
    ledModulated2.write(0.0f);

    PwmOut voltageModulation(PB_6);
    voltageModulation.period(0.001f);
    voltageModulation.write(0.0f);
    AnalogIn voltageAnalogValues(PF_4);
    voltageAnalogValues.set_reference_voltage(3.3f);
    // Queue<message_t, 32> queue;

    while (true) {

        if(userButton.read() !=0 ) {

            led1.write(1);
            ThisThread::sleep_for(BLINKING_RATE);
            led1 = 0;
            ThisThread::sleep_for(BLINKING_RATE);

            printf("Start modulating second led to high:\n");
            for (float modulation = 0.0f; modulation <= 1.0f; modulation += 0.05f) {
                ledModulated2.write(modulation);
                voltageModulation.write(modulation);
                //printf("BW$%2.6ff\n", voltageAnalogValues.read_voltage());
                ThisThread::sleep_for(100ms);
                printf("AW$%2.6ff\n", voltageAnalogValues.read_voltage());
            }
            ThisThread::sleep_for(BLINKING_RATE);
            printf("Start modulating second led to low:\n");
            for (float modulation = 1.0f; modulation >= 0.0f; modulation -= 0.05f) {
                ledModulated2.write(modulation);
                voltageModulation.write(modulation);
                //printf("BW$%2.6ff\n", voltageAnalogValues.read_voltage());
                ThisThread::sleep_for(100ms);
                printf("AW$%2.6ff\n", voltageAnalogValues.read_voltage());
            }
            ThisThread::sleep_for(BLINKING_RATE);
            ledModulated2.write(0.0f);

            printf("Start modulating first led to high:\n");
            for (float modulation = 0.0f; modulation <= 1.0f; modulation += 0.05f) {
                ledModulated1.write(modulation);
                voltageModulation.write(modulation);
                //printf("AW$%2.6ff\n", voltageAnalogValues.read_voltage());
                ThisThread::sleep_for(100ms);
                printf("BW$%2.6ff\n", voltageAnalogValues.read_voltage());
            }
            ThisThread::sleep_for(BLINKING_RATE);
            printf("Start modulating first led to low:\n");
            for (float modulation = 1.0f; modulation >= 0.0f; modulation -= 0.05f) {
                ledModulated1.write(modulation);
                voltageModulation.write(modulation);
                //printf("BW$%2.6ff\n", voltageAnalogValues.read_voltage());
                ThisThread::sleep_for(100ms);
                printf("AW$%2.6ff\n", voltageAnalogValues.read_voltage());
            }
            ThisThread::sleep_for(BLINKING_RATE);
            ledModulated1.write(0.0f);
            printf("Both done.\n");

            led2.write(1);
            ThisThread::sleep_for(BLINKING_RATE);
            led2 = 0;
            ThisThread::sleep_for(BLINKING_RATE);
        }
    }
}
