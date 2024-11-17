#pragma once

#ifndef _keymap_de_
#define _keymap_de_

#include "../Keyboard.cpp"

void setupKeymapDE()
{
    auto* keymap = KeyBoard::getInstance()->keymap;

    // + 0x80 => UP

    // 0xE  -> backspace
    // 0x1C -> return
    // 0x1  -> escape
    // 0x5  -> tab

    // 1 - 9
    uint8_t i = 0;
    for (; i < 9; i++) {
        keymap->map[i + 0x2] = '1' + i;
    }
    keymap->map[0xB] = '0';

    keymap->mapShifted[0x2] = '!';
    keymap->mapShifted[0x3] = '"';
    // keymap->mapShifted[0x4] = '!';
    keymap->mapShifted[0x5] = '$';
    keymap->mapShifted[0x6] = '%';
    keymap->mapShifted[0x7] = '&';
    keymap->mapShifted[0x8] = '/';
    keymap->mapShifted[0x9] = '(';
    keymap->mapShifted[0xA] = ')';
    keymap->mapShifted[0xB] = '=';
    keymap->mapShifted[0xC] = '?';

    keymap->map[0x10] = 'q';
    keymap->map[0x11] = 'w';
    keymap->map[0x12] = 'e';
    keymap->map[0x13] = 'r';
    keymap->map[0x14] = 't';
    keymap->map[0x15] = 'z';
    keymap->map[0x16] = 'u';
    keymap->map[0x17] = 'i';
    keymap->map[0x18] = 'o';
    keymap->map[0x19] = 'p';

    keymap->map[0x1E] = 'a';
    keymap->map[0x1F] = 's';
    keymap->map[0x20] = 'd';
    keymap->map[0x21] = 'f';
    keymap->map[0x22] = 'g';
    keymap->map[0x23] = 'h';
    keymap->map[0x24] = 'j';
    keymap->map[0x25] = 'k';
    keymap->map[0x26] = 'l';

    keymap->map[0x2C] = 'y';
    keymap->map[0x2D] = 'x';
    keymap->map[0x2E] = 'c';
    keymap->map[0x2F] = 'v';
    keymap->map[0x30] = 'b';
    keymap->map[0x31] = 'n';
    keymap->map[0x32] = 'm';

    keymap->mapShifted[0x10] = 'Q';
    keymap->mapShifted[0x11] = 'W';
    keymap->mapShifted[0x12] = 'E';
    keymap->mapShifted[0x13] = 'R';
    keymap->mapShifted[0x14] = 'T';
    keymap->mapShifted[0x15] = 'Z';
    keymap->mapShifted[0x16] = 'U';
    keymap->mapShifted[0x17] = 'I';
    keymap->mapShifted[0x18] = 'O';
    keymap->mapShifted[0x19] = 'P';

    keymap->mapShifted[0x1E] = 'A';
    keymap->mapShifted[0x1F] = 'S';
    keymap->mapShifted[0x20] = 'D';
    keymap->mapShifted[0x21] = 'F';
    keymap->mapShifted[0x22] = 'G';
    keymap->mapShifted[0x23] = 'H';
    keymap->mapShifted[0x24] = 'J';
    keymap->mapShifted[0x25] = 'K';
    keymap->mapShifted[0x26] = 'L';

    keymap->mapShifted[0x2C] = 'Y';
    keymap->mapShifted[0x2D] = 'X';
    keymap->mapShifted[0x2E] = 'C';
    keymap->mapShifted[0x2F] = 'V';
    keymap->mapShifted[0x30] = 'B';
    keymap->mapShifted[0x31] = 'N';
    keymap->mapShifted[0x32] = 'M';

    keymap->map[0x1B] = '+';
    keymap->map[0x2B] = '#';
    keymap->mapShifted[0x1B] = '*';
    keymap->mapShifted[0x2B] = '\'';

    keymap->map[0x56] = '<';
    keymap->mapShifted[0x56] = '>';

    keymap->map[0x33] = ',';
    keymap->map[0x34] = '.';
    keymap->map[0x35] = '-';
    keymap->mapShifted[0x33] = ';';
    keymap->mapShifted[0x34] = ':';
    keymap->mapShifted[0x35] = '_';

    keymap->map[0x39] = ' ';
}

#endif
