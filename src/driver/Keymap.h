#pragma once

#ifndef KEYMAP_H
#define KEYMAP_H

static void* keyboardPtr;

class KeyMap {
public:
    char map[128] = {};
    char mapShifted[128] = {};
};

#endif //KEYMAP_H
