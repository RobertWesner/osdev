#pragma once

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <cstddef>
#include <cstdint>

#define MEMORY_RESERVED_ADDRESS 0x100000
#define MEMORY_BEGIN_ADDRESS 0x101000

class MemorySection {
    public:
        mutable size_t size;
        mutable const MemorySection* previous = nullptr;
        mutable const MemorySection* next = nullptr;

        explicit MemorySection(const size_t size) : size(size) {}
};

class MemoryManager {
        const size_t overhead = sizeof(size_t) + sizeof(MemorySection*) * 2;
        const MemorySection* availableMemory = nullptr;
    public:
        static size_t getMemoryLimit() {
            return 1000 * 1000 + *reinterpret_cast<uint16_t *>(0x7c00 + 506) * 1000 + *reinterpret_cast<uint16_t *>(0x7c00 + 508) * 64 * 1000;
        }

        static MemoryManager* getInstance() {
            return reinterpret_cast<MemoryManager *>(MEMORY_RESERVED_ADDRESS);
        }

        /**
         * You NEED to call this once before doing anything.
         *
         * I intentionally didn't just magically set this up since getInstance() can be based on random memory -> invalid pointers.
         */
        void setUp() {
            this->availableMemory = reinterpret_cast<MemorySection*>(MEMORY_BEGIN_ADDRESS);
            this->availableMemory->size = getMemoryLimit() - MEMORY_BEGIN_ADDRESS;
        }

        void* allocate(size_t size) {
            /*
             .-------------------------------------------------->
             |    |              |                       |      >
             '-------------------------------------------------->
            */
            const MemorySection* section = this->availableMemory;
            while (section->size < size) {
                section = section->next;
            }

            if (section->size == size) {
                // exact match, use existing sector

                // patch up the hole
                section->previous->next = section->next;
                section->previous->previous = section->previous;
            } else {
                // split sector into smaller parts

                /*
                 .-------------------------------------------------->
                 |    | free         |                      |      >
                 '-------------------------------------------------->
                */
                const MemorySection* newMemory = section + this->overhead + size;
                newMemory->size = section->size - this->overhead - size;
                /*
                 .-------------------------------------------------->
                 |    |         | new |                       |      >
                 '-------------------------------------------------->
                */
                section->size = size;
                /*
                 .-------------------------------------------------->
                 |    | size    | new |                      |      >
                 '-------------------------------------------------->
                */

                if (section->previous == nullptr) {
                    this->availableMemory = newMemory;
                } else {
                    section->previous->next = newMemory;
                }
            }

            return (void*)(section + this->overhead);
        }

        void free(void* pointer) {
            const auto section = reinterpret_cast<MemorySection*>(reinterpret_cast<size_t>(pointer) - this->overhead);
            this->availableMemory->next->previous = section;
            this->availableMemory->next = section;
            section->previous = this->availableMemory;
        }

        void* reallocate(void* ptr, size_t size) {
            void* reallocated = this->allocate(size);
            this->free(ptr);

            return reallocated;
        }
};

#endif //MEMORYMANAGER_H
