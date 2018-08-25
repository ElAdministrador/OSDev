
#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/mem_init.h>
#include <kernel/cpu.h>

// Std Lib includes
#include <string.h>
#include <stdio.h>

// GCC includes
#include <cpuid.h>

// Debugging
#include <kernel/paging.h>

void kernel_main(void) {

	// Initialize memory management
	init_gdt();
	init_paging();

	// Initialize terminal and perform some tests.
	terminal_initialize();
	printf("Hello, %s%d%d!\n", "deros v", 0,1);

	printf("\n");
	printf("virt %x phys %p\n", 0x100000, get_physaddr((void*) 0x100000));
	printf("virt %x phys %p\n", 0x100001, get_physaddr((void*) 0x100001));
	printf("virt %x phys %p\n", 0x100010, get_physaddr((void*) 0x100010));
	printf("virt %x phys %p\n", 0x100100, get_physaddr((void*) 0x100100));
	printf("virt %x phys %p\n", 0x101000, get_physaddr((void*) 0x101000));
	printf("virt %x phys %p\n", 0x101001, get_physaddr((void*) 0x101001));
	printf("virt %x phys %p\n", 0x110000, get_physaddr((void*) 0x110000));
	printf("virt %x phys %p\n", 0x111111, get_physaddr((void*) 0x111111));
	printf("virt kernel_main:%x phys %p\n", (uint32_t) &kernel_main,
		get_physaddr((void*) &kernel_main));
	printf("virt pd:%x phys %p\n", (uint32_t) &page_directory,
		get_physaddr((void*) &page_directory));
	printf("virt pt:%x phys %p\n", (uint32_t) &master_page_table,
		get_physaddr((void*) &master_page_table));

	/*if (checkCPUID()) {
		memset(&cpuInfo_global, 0, sizeof(cpuInfo_t));

		unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
		__get_cpuid(0, &eax, &ebx, &ecx, &edx);
		cpuInfo_global.intelSignature = ebx == signature_INTEL_ebx &&
										ecx == signature_INTEL_ecx &&
										edx == signature_INTEL_edx;

		__get_cpuid_max(0x0, &(cpuInfo_global.cpuInfo_maxBasic));
		__get_cpuid_max(0x80000000, &(cpuInfo_global.cpuInfo_maxExt));

		if (1 <= cpuInfo_global.cpuInfo_maxBasic) {
			ecx = 0, edx = 0;
			__get_cpuid(1, &eax, &ebx, &ecx, &edx);
			cpuInfo_global.HTT = ((edx & (1 << 27)) >> 27);
			cpuInfo_global.TM = ((edx & (1 << 28)) >> 28);
		}

		if (4 <= cpuInfo_global.cpuInfo_maxBasic) {
			eax = 0xB;
			__get_cpuid(4, &eax, &ebx, &ecx, &edx);
		}

		if (cpuInfo_global.intelSignature) {
			printf ("Signature Intel\n");
			printf ("HTT %d\n", cpuInfo_global.HTT);
			printf ("TM %d\n", cpuInfo_global.TM);
		}
	}*/

	printf ("\n");
	while(1) {
		char c = getChar();
		if (c != 0) {
			printf("%c", c);
		}
	}
}