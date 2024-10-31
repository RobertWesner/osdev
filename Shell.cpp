#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include "src/simple_map.h"

#include "shell/test.cpp"
#include "shell/help.cpp"

#define SHELL_MEM 2048

class Shell {
    uint8_t inputLength = 0;

    void run() {
        auto command = static_cast<char*>(malloc(256));
        auto arguments = static_cast<char*>(malloc(256));
        uint8_t i = 0;

        for (; i < this->inputLength && this->input[i] != ' '; i++) {
            command[i] = this->input[i];
        }
        command[i] = 0;

        // skip empty space
        i++;

        for (uint8_t x = 0; i < this->inputLength;) {
            arguments[x++] = this->input[i++];
        }
        arguments[i] = 0;

        putchar('\n');

        void* call = this->commands->get(command);
        if (call == nullptr) {
            printf("unknown command \"%s\"\n", command);
        } else {
            reinterpret_cast<void(*)(const char*)>(call)(static_cast<const char*>(arguments));
        }

        free(command);
        free(arguments);
        inputLength = 0;
    }
public:
    char* input;
    simple_map* commands;

    void handleKeyDown(KeyBoard* keyboard, uint8_t keyCode) {
        if (keyCode == 0x1C) {
            this->run();
            puts("$ \0");
        } else if (keyCode == 0xE) {
            text_out::back();
            this->input[--this->inputLength] = 0;
        }else if (this->inputLength < 256) {
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
    instance->input = static_cast<char*>(malloc(255));
    puts("$ \0");

    instance->commands = new simple_map(static_cast<size_t>(256));
    instance->commands->set("test", reinterpret_cast<void*>(&shell_test));
    instance->commands->set("help", reinterpret_cast<void*>(&shell_help));

    return instance;
}
