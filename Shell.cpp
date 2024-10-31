#include <cstdlib>
#include <cstdio>
#include <cstdint>

#define SHELL_MEM 2048

class Shell {
    char input[256]{};
    uint8_t inputLength = 0;

    void run() {
        char* instring = static_cast<char*>(malloc(256));
        uint8_t i = 0;
        for (; i < this->inputLength; i++) {
            instring[i] = this->input[i];
        }
        instring[i] = 0;
        putchar('\n');

        // TODO: actual parsing once i implement cstring :)
        bool test = false;
        if (instring[0] == 't') {
            if (instring[1] == 'e') {
                if (instring[2] == 's') {
                    if (instring[3] == 't') {
                        if (instring[4] == ' ' || instring[4] == '\0') {
                            printf("Hello World!\n\0");
                            test = true;
                        }
                    }
                }
            }
        }

        if (!test) {
            printf("What?\n\0");
        }

        free(instring);
        inputLength = 0;
    }
public:
    void handleKeyDown(KeyBoard* keyboard, uint8_t keyCode) {
        if (keyCode == 0x1C) {
            this->run();
            puts("$ \0");
        } else if (this->inputLength < 256) {
            char c = keyboard->getChar(keyCode);

            putchar(c);
            this->input[this->inputLength++] = c;
        }
    }

    void handleKeyUp(KeyBoard* keyboard, uint8_t keyCode) {
    }
};

Shell* shell() {
    auto* instance = static_cast<Shell*>(malloc(SHELL_MEM));
    puts("$ \0");

    return instance;
}
