#include <cstdio>
#include <cstdint>

#include "src/MemoryManager.h"
#include "src/driver/Interrupt.cpp"
#include "src/driver/Keyboard.cpp"
#include "src/driver/keymap/de.cpp"
#include "src/text.cpp"

void onKeyDown(void* ptr, uint8_t keyCode) {
    auto keyboard = static_cast<KeyBoard *>(ptr);

    if (keyCode == 0x1C) {
        putchar('\n');
    } else {
        putchar(keyboard->getChar(keyCode));
    }
}

void onKeyUp(void* ptr, uint8_t keyCode) {
    auto keyboard = static_cast<KeyBoard *>(ptr);

}

[[noreturn]] int main() {
    MemoryManager::getInstance()->setUp();
    idt_init();
    text_out::init();
    keyboard_init();
    setupKeymapDE();

    auto* keyboard = KeyBoard::getInstance();

    while (true) {
        keyboard->handle();
    }
}
