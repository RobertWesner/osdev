#pragma once

#ifndef INTERRUPT
#define INTERRUPT

#include <cstdint>
#include <cstdlib>

#include "PIC.cpp"

#define IDT_MAX_DESCRIPTORS 256
#define PIC_1_CTRL 0x20
#define PIC_2_CTRL 0xA0
#define PIC_1_DATA 0x21
#define PIC_2_DATA 0xA1

extern "C" {
    typedef struct {
        uint16_t    isr_low;      // The lower 16 bits of the ISR's address
        uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
        uint8_t     reserved;     // Set to zero
        uint8_t     attributes;   // Type and attributes; see the IDT page
        uint16_t    isr_high;     // The higher 16 bits of the ISR's address
    } __attribute__((packed)) idt_entry_t;

    __attribute__((aligned(0x10)))
    static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance

    typedef struct {
        uint16_t	limit;
        uint32_t	base;
    } __attribute__((packed)) idtr_t;

    static idtr_t idtr;

    [[noreturn]] void exception_handler() {
        std::exit(1);
    }

    static bool vectors[IDT_MAX_DESCRIPTORS];

    extern void* isr_stub_table[];

    void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
        idt_entry_t* descriptor = &idt[vector];

        descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
        descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
        descriptor->attributes     = flags;
        descriptor->isr_high       = (uint32_t)isr >> 16;
        descriptor->reserved       = 0;
    }

    static void initialize_pic()
    {
        /* ICW1 - begin initialization */
        outb(PIC_1_CTRL, 0x11);
        outb(PIC_2_CTRL, 0x11);

        /* ICW2 - remap offset address of idt_table */
        /*
        * In x86 protected mode, we have to remap the PICs beyond 0x20 because
        * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
        */
        outb(PIC_1_DATA, 0x20);
        outb(PIC_2_DATA, 0x28);

        /* ICW3 - setup cascading */
        outb(PIC_1_DATA, 0x00);
        outb(PIC_2_DATA, 0x00);

        /* ICW4 - environment info */
        outb(PIC_1_DATA, 0x01);
        outb(PIC_2_DATA, 0x01);
        /* Initialization finished */

        /* mask interrupts */
        outb(0x21 , 0xFF);
        outb(0xA1 , 0xFF);
    }

    void idt_init() {
        initialize_pic();

        idtr.base = (uintptr_t)&idt[0];
        idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

        for (uint8_t vector = 0; vector < 32; vector++) {
            idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
            vectors[vector] = true;
        }

        __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
        __asm__ volatile ("sti"); // set the interrupt flag
    }
}

#endif //INTERRUPT
