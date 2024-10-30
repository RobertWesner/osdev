#include <cstdio>
#include <cstdlib>
#include "src/MemoryManager.h"

int main() {
    MemoryManager::getInstance()->setUp();

    printf("Mem: %u Bytes", static_cast<unsigned int>(MemoryManager::getMemoryLimit()));

    char* str = static_cast<char *>(malloc(6));
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';

    char* egg = static_cast<char *>(malloc(4));
    egg[0] = 'E';
    egg[1] = 'G';
    egg[2] = 'G';

    free(egg);

    char* test = static_cast<char *>(malloc(4));
    test[0] = 'A';
    test[1] = 'B';
    test[2] = 'C';
    test[3] = 0;

    printf(test);

    free(str);
    free(test);
}
