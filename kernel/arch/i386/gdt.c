#include <kernel/gdt.h>

/*
 * Create a segment descriptor in the GDT.
 *  \param descriptor A pointer to the 8-byte GDT entry
 *  \param base       Base address of the segment 
 *  \param limit      Limit address of the segment
 *  \param flag       Flags of the segment
 */
void create_segment_descriptor(uint8_t* descriptor,
    uint32_t base, uint32_t limit, uint16_t flag)
{

    // Set the base
    descriptor[2] = (uint8_t) base;
    descriptor[3] = (uint8_t) (base >> 8);
    descriptor[4] = (uint8_t) (base >> 16);
    descriptor[7] = (uint8_t) (base >> 24);

    // Set the limit
    descriptor[0] = (uint8_t) limit;
    descriptor[1] = (uint8_t) (limit >> 8);
    descriptor[6] = (uint8_t) (limit >> 16) & 0xF;

    // Set the flags
    descriptor[5] = (uint8_t) flag;
    descriptor[6] |= (uint8_t) ((flag >> 8) & 0xF0);
}