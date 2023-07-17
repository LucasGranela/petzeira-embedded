#ifdef EMBEDDED

#ifndef STATIC_CONFIG_H
#define STATIC_CONFIG_H

/* INDIVIDUAL MODULE ENABLED */
#define SERVO_ENABLED
#define BALANCA_ENABLED
#define WATER_ENABLED
#define SERIAL_ENABLED

/* INDIVIDUAL MODULE VERBOSE MODE ENABLERS */
#ifdef SERIAL_ENABLED

#endif


/* PIN ALLOCATION */

#ifdef SERVO_ENABLED
    #define SERVO_PIN 2
#endif

#ifdef BALANCA_ENABLED
    #define HX711_DOUT_FOOD 15//mcu > HX711 dout pin, must be external interrupt capable!
    #define HX711_SCK_FOOD 14 //mcu > HX711 sck pin
#endif

#ifdef WATER_ENABLED
    #define TRANSISTOR_PIN 12
#endif

#endif

#endif