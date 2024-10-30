#pragma once
#include <cstddef>
#include <cstdint>

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

class MemoryManager {
    public:
        static size_t getMemoryLimit()
        {
            return 1000 * 1000 + *reinterpret_cast<uint16_t *>(0x7c00 + 506) * 1000 + *reinterpret_cast<uint16_t *>(0x7c00 + 508) * 64 * 1000;
        }
};

#endif //MEMORYMANAGER_H
