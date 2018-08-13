#ifndef _IO_PORT_H
#define _IO_PORT_H

#include <stdint.h>

void outb(uint16_t adr, uint8_t value);
uint8_t inb(uint16_t adr);

#endif