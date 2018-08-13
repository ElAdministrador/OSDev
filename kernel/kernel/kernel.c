#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/gdt.h>
#include <string.h>

// Address where the GDT is located in Mem
const uint32_t GDT_BASE_ADDRESS = 0x0;

void kernel_main(void) {

	// Initialize terminal and perform some tests.
	terminal_initialize();
	printf("Hello, %s%d%d!\n", "deros v", 0,1);

	// Initialize GDT
	create_segment_descriptor((uint8_t*) 0x27 , 0x80000, 0x80001, 14);

	printf("GDT loaded %u\n", loadGdt((uint32_t)0,(uint16_t)0));
	
	printf ("\n");
	while(1) {
		char c = getChar();
		if (c != 0) {
			printf("%c", c);
		}
	}
}