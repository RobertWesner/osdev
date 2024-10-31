#include <cstdio>
#include <cstdint>

#include "src/MemoryManager.h"
#include "src/driver/Interrupt.cpp"
#include "src/driver/Keyboard.cpp"
#include "src/driver/keymap/de.cpp"

void onKeyDown(void* ptr, uint8_t keyCode) {
    auto keyboard = static_cast<KeyBoard *>(ptr);

    printf(
        "DOWN: %X\nCHAR: %c",
        keyCode,
        keyboard->getChar(keyCode)
    );
}

void onKeyUp(void* ptr, uint8_t keyCode) {
    auto keyboard = static_cast<KeyBoard *>(ptr);

    printf(
        "UP:   %X\nCHAR: %c",
        keyCode,
        keyboard->getChar(keyCode)
    );
}

[[noreturn]] int main() {
    MemoryManager::getInstance()->setUp();
    idt_init();
    keyboard_init();
    setupKeymapDE();

    auto* keyboard = KeyBoard::getInstance();

    while (true) {
        keyboard->handle();
    }
}
