#include <cstdio>
#include <cstdint>

#include "init.cpp"
#include "Shell.cpp"
#include "src/driver/Keyboard.cpp"

static Shell* shellInstance;

void onKeyDown(void* ptr, uint8_t keyCode) {
    shellInstance->handleKeyDown(static_cast<KeyBoard*>(ptr), keyCode);
}

void onKeyUp(void* ptr, uint8_t keyCode) {
    shellInstance->handleKeyUp(static_cast<KeyBoard*>(ptr), keyCode);
}

[[noreturn]] int main() {
    init();

    shellInstance = shell();

    auto* keyboard = KeyBoard::getInstance();
    while (true) {
        keyboard->handle();
    }
}
