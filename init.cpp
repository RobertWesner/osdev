#include "src/MemoryManager.h"
#include "src/driver/Interrupt.cpp"
#include "src/driver/keymap/de.cpp"
#include "src/text.cpp"

void init() {
    MemoryManager::getInstance()->setUp();
    idt_init();
    text_out::init();
    keyboard_init();
    setupKeymapDE();
}