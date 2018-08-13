#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <kernel/io_port.h>
#include <stdint.h>

static const uint16_t KB_CONTROL_PORT = 0x64;
static const uint16_t KB_DATA_PORT = 0x60;

// TODO build device driver
#include <kernel/tty.h>

/*
 PS/2 keyboard code
*/
char getChar();
uint8_t getScancode();
void processScancode(uint8_t c);

#endif