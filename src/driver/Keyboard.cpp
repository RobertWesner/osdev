#pragma once

#ifndef KEYBOARD
#define KEYBOARD

#include <cstdint>
#include <cstdlib>
#include "Keymap.h"

void keyboard_init() {
    keyboardPtr = malloc(512);
}

void onKeyDown(void* keymap, uint8_t keyCode);
void onKeyUp(void* keymap, uint8_t keyCode);

class KeyBoard {
    uint8_t last = 0;
public:
    bool keys[128]{};

    bool shift = false;
    bool capsLock = false;
    bool ctrl = false;
    bool alt = false;
    bool super = false;

    KeyMap* keymap{};

    static KeyBoard* getInstance() {
        return static_cast<KeyBoard*>(keyboardPtr);
    }

    char getChar(const uint8_t code) const {
        if (this->shift) {
            return this->keymap->mapShifted[code];
        }

        return this->keymap->map[code];
    }

    void handle() {
        uint8_t key = inb(0x60);

        if (key == this->last) {
            return;
        }
        this->last = key;

        bool down;
        if (key >= 0x80) {
            key -= 0x80;
            down = false;
        } else {
            down = true;
        }

        switch (key) {
            case 0x2A:
            case 0x36:
                this->shift = down;
                break;
            case 0x1D:
                this->ctrl = down;
                break;
            case 0x38:
                this->alt = down;
                break;
            case 0x5B:
            case 0x5C:
                this->super = down;
                break;
            default:
                if (down) {
                    this->keys[key] = true;
                    onKeyDown(this, key);
                } else {
                    this->keys[key] = false;
                    onKeyUp(this, key);
                }
        }
    }
};

#endif
