#include <cstdio>
#include "src/MemoryManager.h"

int main()
{
    printf("Mem: %u Bytes", static_cast<unsigned int>(MemoryManager::getMemoryLimit()));
}
