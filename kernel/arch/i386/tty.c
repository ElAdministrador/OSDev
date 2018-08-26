#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"

#define TAB_WIDTH 4

// VGA Screen attributes
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
// Terminal indices
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

// IO port adresses and commands
static uint16_t const VGA_INDEX_REGISTER = 0x3d4;
static uint16_t const VGA_DATA_REGISTER = 0x3d5;
static uint8_t const VGA_CMD_HIGH = 14;
static uint8_t const VGA_CMD_LOW = 15;

// Set the HW cursor on position (x,y)
static void setHWCursor(int x, int y) {
	uint16_t offset = y * VGA_WIDTH + x;
	outb((uint16_t) VGA_INDEX_REGISTER, (uint8_t) VGA_CMD_HIGH);
	outb((uint16_t) VGA_DATA_REGISTER, (uint8_t) (offset >> 8));
	outb((uint16_t) VGA_INDEX_REGISTER, (uint8_t) VGA_CMD_LOW);
	outb((uint16_t) VGA_DATA_REGISTER, (uint8_t) (offset & 0xFF));
}

// Initialize empty Terminal 
void terminal_initialize(void)
{
	setHWCursor(0,0);
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

// Set color of the terminal text/bg
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

// Place character at position (x,y)
static void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

// Get character & color at position (x,y)
static uint16_t terminal_getentryat(size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	return terminal_buffer[index];
}

// Shift all rows up by one line
static void terminal_shift_up()
{
	for (unsigned int i = 0; i < VGA_HEIGHT-1; i++) {
		for (unsigned int r = 0; r < VGA_WIDTH; r++)
			terminal_buffer[r+i*VGA_WIDTH] = terminal_buffer[r+VGA_WIDTH+i*VGA_WIDTH];
	}

	terminal_row = VGA_HEIGHT-1;
}

// Output character to 
void terminal_putchar(char c)
{
	unsigned char uc = c;

	if (c == '\n') {
		// newline feed
		terminal_column = VGA_WIDTH-1;
	} else if(c == '\t') {
		// tabulator feed
		for (unsigned int i = 0; i < TAB_WIDTH; i++) {
			terminal_write(" ", 1);
		}
	}
	else {
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	}

	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		// End of screen reached?
		if (++terminal_row == VGA_HEIGHT) {
			// Shift rows up and clear last line
			terminal_shift_up();
			for (unsigned int i = 0; i < VGA_WIDTH; i++)
				terminal_putentryat(' ', terminal_color, i, terminal_row);
		}
	}

	// Set the HW cursor next position.
	setHWCursor(terminal_column,terminal_row);
}
 
// Write a string to terminal
void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

// Write a string to terminal 
void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

// Delete last character and move cursor back by one
void terminal_backspace()
{
	if (terminal_column == 0) {
		if (terminal_row != 0) {
			terminal_column = VGA_WIDTH-1;
			terminal_row--;
			// Move cursor to linebreak
			uint16_t entry;
			do {
				terminal_column--;
				entry = terminal_getentryat(terminal_column-1, terminal_row);
			} while ((uint8_t) entry == ' ' && terminal_column != 0);
		}
	} else {
		terminal_column--;
	}

	terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
	// Also move the HW cursor back
	setHWCursor(terminal_column,terminal_row);
}