#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/gdt.h>
#include <string.h>

// Address where the GDT is located in Mem
const uint32_t GDT_BASE_ADDRESS = 0x7A120;
// space for 10 segment descriptors
const uint32_t GDT_LIMIT_ADDRESS = GDT_BASE_ADDRESS + 8 * 10;

void kernel_main(void) {

	// Initialize terminal and perform some tests.
	terminal_initialize();
	printf("Hello, %s%d%d!\n", "deros v", 0,1);

	// Initialize GDT
	loadGdt((uint32_t) GDT_BASE_ADDRESS,(uint16_t) GDT_LIMIT_ADDRESS);
	printf("GDT loaded at %x\n", GDT_BASE_ADDRESS);
	// null descriptor
	create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS , 0x0, 0x0, 0x0);
	printf("Null descriptor loaded\n");
	for (int i = 0; i < 8; i++) {
		printf("0x%x ", *(((uint8_t*) GDT_BASE_ADDRESS)+i));
	}
	// kernel code segment descriptor
	//create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+16, 0x0, 0x0, 0x0);
	
	printf ("\n");
	while(1) {
		char c = getChar();
		if (c != 0) {
			printf("%c", c);
		}
	}
}