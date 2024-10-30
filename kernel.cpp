#include <cstdio>
#include <cstdlib>
#include "src/MemoryManager.h"

int main() {
    MemoryManager::getInstance()->setUp();

    auto* str = static_cast<char *>(malloc(6));
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';

    auto* theNumber = static_cast<unsigned int *>(malloc(sizeof(unsigned int)));
    *theNumber = 1337;

    // throw it away
    free(str);

    auto* test = static_cast<char *>(malloc(4));
    test[0] = 'A';
    test[1] = 'B';
    test[2] = 'C';
    test[3] = 0;

    printf(
        "Mem: %u Bytes\n%s\n%u",
        static_cast<unsigned int>(MemoryManager::getMemoryLimit()),
        test,
        *theNumber
    );

    free(theNumber);
    free(test);
}
