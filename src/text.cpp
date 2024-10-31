#ifndef TEXT
#define TEXT

#include <cstdlib>
#include <cstdint>
#include <cstring>

#define TEXT_OUT_WIDTH 80
#define TEXT_OUT_HEIGHT 25
#define TEXT_OUT_SIZE (TEXT_OUT_WIDTH * TEXT_OUT_HEIGHT)

#define VIDEO_MEMORY_PTR (char*)0xb8000

static auto* text_out_cursor = (uint16_t*)malloc(sizeof(uint16_t));
// TODO: buffer
// static auto* text_out_buffer = (char*)malloc(TEXT_OUT_SIZE * 2);

namespace text_out {
    void reset_cursor() {
        *text_out_cursor = 0;
    }

    void clear() {
        for (char* videoMem = VIDEO_MEMORY_PTR; videoMem < VIDEO_MEMORY_PTR + TEXT_OUT_SIZE; videoMem += 2) {
            *videoMem = ' ';
        }
        *text_out_cursor = 0;
    }

    void setc(char c, int pos) {
        if (pos < 0) {
            return;
        }

        if (pos >= TEXT_OUT_SIZE) {
            memmove(VIDEO_MEMORY_PTR, VIDEO_MEMORY_PTR + TEXT_OUT_WIDTH * 2, (TEXT_OUT_SIZE - TEXT_OUT_WIDTH) * 2);

            for (uint8_t i = 0; i < TEXT_OUT_WIDTH; i++) {
                *(VIDEO_MEMORY_PTR + (TEXT_OUT_SIZE - TEXT_OUT_WIDTH + i) * 2) = ' ';
            }

            *text_out_cursor -= TEXT_OUT_WIDTH;
            pos -= TEXT_OUT_WIDTH;
        }

        char* videoMem = VIDEO_MEMORY_PTR + pos * 2;
        *videoMem = c;
        *(videoMem + 1) = 0x0F;
    }

    void printc(char c) {
        switch (c) {
            case '\n':
                *text_out_cursor += TEXT_OUT_WIDTH - (*text_out_cursor % TEXT_OUT_WIDTH);

                break;
            case '\r':
            case '\a':
                break;
            default:
                setc(c, *text_out_cursor);
                *text_out_cursor += 1;
        }
    }

    void print(char* string) {
   	    while (*string) {
            printc(*string);
            string++;
        }
    }

    void print_hex(unsigned int integer, bool upperCase) {
        char remainingNibbles = 8;

        while (!(integer & 0xF0000000)) {
		    integer <<= 4;
            remainingNibbles--;
        }

        while (remainingNibbles--) {
            char i = integer >> 28;
            if (i <= 9) {
                printc(48 + i);
            } else if (upperCase) {
                printc(55 + i);
            } else {
                printc(87 + i);
            }

		    integer <<= 4;
        }
    }

    void print_oct(unsigned int integer) {
        if (integer >= 8) {
            print_oct(integer / 8);
        }

        printc((integer % 8) + '0');
    }

    void print_dec_unsigned(unsigned int integer) {
        if (integer >= 10) {
            print_dec_unsigned(integer / 10);
        }

        printc((integer % 10) + '0');
    }

    void print_dec_signed(int integer) {
        if (integer < 0) {
            printc('-');
            integer = -integer;
        }

        print_dec_unsigned((unsigned int)integer);
    }

    // void flush() {
    //     memcpy(VIDEO_MEMORY_PTR, text_out_buffer, TEXT_OUT_SIZE);
    // }

    void init() {
        clear();
        *text_out_cursor = 0;
    }
}

#endif //TEXT
