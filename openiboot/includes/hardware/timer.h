#ifndef HW_TIMER_H
#define HW_TIMER_H

#include "hardware/s5l8900.h"

// Constants
#define EventTimer 4
#ifdef CONFIG_IPOD
#define PiezoTimer 1
#endif
#ifdef CONFIG_IPHONE_3G
#define VibratorTimer 5
#endif

// Devices

#if !defined(CONFIG_IPHONE_4) && !defined(CONFIG_IPAD)
#define TIMER 0x3E200000
#else
#define TIMER 0xBF100000
#endif

// Registers

#define TIMER_0 0x0
#define TIMER_1 0x20
#define TIMER_2 0x40
#define TIMER_3 0x60
#define TIMER_4 0xA0
#define TIMER_5 0xC0
#define TIMER_6 0xE0
#define TIMER_CONFIG 0
#define TIMER_STATE 0x4
#define TIMER_COUNT_BUFFER 0x8
#define TIMER_COUNT_BUFFER2 0xC
#define TIMER_PRESCALER 0x10
#define TIMER_UNKNOWN3 0x14
#if !defined(CONFIG_IPHONE_4) && !defined(CONFIG_IPAD)
#define TIMER_TICKSHIGH 0x80
#define TIMER_TICKSLOW 0x84
#else
#define TIMER_TICKSHIGH 0x2004
#define TIMER_TICKSLOW 0x2000
#endif
#define TIMER_UNKREG0 0x88
#define TIMER_UNKREG1 0x8C
#define TIMER_UNKREG2 0x90
#define TIMER_UNKREG3 0x94
#define TIMER_UNKREG4 0x98
#define TIMER_IRQSTAT 0x10000
#define TIMER_IRQLATCH 0xF8

// Timer
#define NUM_TIMERS 7
#define TIMER_CLOCKGATE 0x25
#if !defined(CONFIG_IPHONE_4) && !defined(CONFIG_IPAD)
#define TIMER_IRQ 0x7
#else
#define TIMER_IRQ 0x6
#define TIMER_REGISTER 0xBF102008
#define TIMER_REGISTER_TICK 0xBF102010
/* Argument == 1
#define TIMER_IRQ 0x5
#define TIMER_REGISTER 0xBF10200C
#define TIMER_REGISTER_TICK 0xBF102014
*/
#endif
#define TIMER_STATE_START 1
#define TIMER_STATE_STOP 0
#define TIMER_STATE_MANUALUPDATE 2
#define TIMER_UNKREG0_RESET1 0xA
#define TIMER_UNKREG0_RESET2 0x18010
#define TIMER_UNKREG1_RESET 0xFFFFFFFF
#define TIMER_UNKREG2_RESET 0xFFFFFFFF
#define TIMER_UNKREG3_RESET 0xFFFFFFFF
#define TIMER_UNKREG4_RESET 0xFFFFFFFF
#define TIMER_DIVIDER1 4
#define TIMER_DIVIDER2 0
#define TIMER_DIVIDER4 1
#define TIMER_DIVIDER16 2
#define TIMER_DIVIDER64 3
#define TIMER_SPECIALTIMER_BIT0 0x1000000
#define TIMER_SPECIALTIMER_BIT1 0x2000000

#define TIMER_Separator 4

#endif
