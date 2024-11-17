#pragma once

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#define MEMORY_RESERVED_ADDRESS 0x100000
#define MEMORY_BEGIN_ADDRESS 0x101000

class MemoryPool {
public:
    size_t itemCount;
    size_t itemSize;
    bool* freeFlags;
    void* items;

    void* allocate() {
        size_t i = 0;
        for (; this->freeFlags[i] == false; i++) {
            if (i > this->itemCount) {
                // TODO: some kind of error handling would be awesome
                return nullptr;
            }
        }

        this->freeFlags[i] = false;

        return reinterpret_cast<void*>(reinterpret_cast<size_t>(this->items) + this->itemSize * i);
    }

    void free(void* p) {
        const size_t n = reinterpret_cast<size_t>(p) - reinterpret_cast<size_t>(this->items);
        if (n > this->itemCount) {
            // massive fail, trying to free item from another pool
            return;
        }

        this->freeFlags[n] = true;
    }

    void* getLocation() {
        return this->freeFlags;
    }
};

class MemoryManager {
    size_t remainingMemory = 0;
    void* freeAddress = nullptr;

    MemoryPool* pool1 = nullptr;
    MemoryPool* pool2 = nullptr;
    MemoryPool* pool4 = nullptr;
    MemoryPool* pool8 = nullptr;
    MemoryPool* pool16 = nullptr;
    MemoryPool* pool32 = nullptr;
    MemoryPool* pool64 = nullptr;
    MemoryPool* pool128 = nullptr;
    MemoryPool* pool256 = nullptr;
    MemoryPool* pool1024 = nullptr;
    MemoryPool* pool4096 = nullptr;
    MemoryPool* pool65536 = nullptr;

    void* poolEndIndicator = nullptr;

    MemoryPool* createPool(const size_t itemCount, const size_t itemSize) {
        const size_t poolMetadataSize = itemCount + itemSize + sizeof(void*) * 2;

        const auto pool = static_cast<MemoryPool*>(this->getMemorySlice((sizeof(bool) + itemSize) * itemCount));
        pool->itemCount = itemCount;
        pool->itemSize = itemSize;
        pool->freeFlags = reinterpret_cast<bool*>(reinterpret_cast<size_t>(pool) + poolMetadataSize);
        pool->items = static_cast<void*>(pool->freeFlags + sizeof(bool) * itemCount);

        // Initialize everything as free
        for (size_t i = 0; i < itemCount; i++) {
            pool->freeFlags[i] = true;
        }

        return pool;
    }
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
        this->remainingMemory = getMemoryLimit() - MEMORY_BEGIN_ADDRESS;
        this->freeAddress = reinterpret_cast<void*>(MEMORY_BEGIN_ADDRESS);
        size_t poolItemLimit = this->remainingMemory / 2 / (1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 1024 + 4096 + 65536);

        this->pool1 = this->createPool(poolItemLimit, 1);
        this->pool2 = this->createPool(poolItemLimit, 2);
        this->pool4 = this->createPool(poolItemLimit, 4);
        this->pool8 = this->createPool(poolItemLimit, 8);
        this->pool16 = this->createPool(poolItemLimit, 16);
        this->pool32 = this->createPool(poolItemLimit, 32);
        this->pool64 = this->createPool(poolItemLimit, 64);
        this->pool128 = this->createPool(poolItemLimit, 128);
        this->pool256 = this->createPool(poolItemLimit, 256);
        this->pool1024 = this->createPool(poolItemLimit, 1024);
        this->pool4096 = this->createPool(poolItemLimit, 4096);
        this->pool65536 = this->createPool(poolItemLimit, 65536);

        this->poolEndIndicator = this->getMemorySlice(1);
    }

    /**
     * This gets a raw slice of memory, should not be used directly
     */
    void* getMemorySlice(size_t size) {
        // TODO: handle out of memory, not relevant yet
        const auto slice = this->freeAddress;
        this->freeAddress = reinterpret_cast<void*>(reinterpret_cast<size_t>(this->freeAddress) + size);

        return slice;
    }

    void* allocate(size_t size) {
        if (size == 1) {
            return this->pool1->allocate();
        }

        if (size == 2) {
            return this->pool2->allocate();
        }

        if (size <= 4) {
            return this->pool4->allocate();
        }

        if (size <= 8) {
            return this->pool8->allocate();
        }

        if (size <= 16) {
            return this->pool16->allocate();
        }

        if (size <= 32) {
            return this->pool32->allocate();
        }

        if (size <= 64) {
            return this->pool64->allocate();
        }

        if (size <= 128) {
            return this->pool128->allocate();
        }

        if (size <= 256) {
            return this->pool256->allocate();
        }

        if (size <= 1024) {
            return this->pool1024->allocate();
        }

        if (size <= 4096) {
            return this->pool4096->allocate();
        }

        if (size <= 65536) {
            return this->pool65536->allocate();
        }

        // cant be freed (yet)
        return this->getMemorySlice(size);
    }

    void free(void* pointer) {
        if (pointer > this->poolEndIndicator) {
            return;
        }

        if (pointer > this->pool65536->getLocation()) {
            pool65536->free(pointer);
        }

        if (pointer > this->pool4096->getLocation()) {
            pool4096->free(pointer);
        }

        if (pointer > this->pool1024->getLocation()) {
            pool1024->free(pointer);
        }

        if (pointer > this->pool256->getLocation()) {
            pool256->free(pointer);
        }

        if (pointer > this->pool128->getLocation()) {
            pool128->free(pointer);
        }

        if (pointer > this->pool64->getLocation()) {
            pool64->free(pointer);
        }

        if (pointer > this->pool32->getLocation()) {
            pool32->free(pointer);
        }

        if (pointer > this->pool16->getLocation()) {
            pool16->free(pointer);
        }

        if (pointer > this->pool8->getLocation()) {
            pool8->free(pointer);
        }

        if (pointer > this->pool4->getLocation()) {
            pool4->free(pointer);
        }

        if (pointer > this->pool2->getLocation()) {
            pool2->free(pointer);
        }

        if (pointer > this->pool1->getLocation()) {
            pool1->free(pointer);
        }
    }

    void* reallocate(void* ptr, size_t size) {
        void* reallocated = this->allocate(size);
        this->free(ptr);

        return reallocated;
    }
};

#endif //MEMORYMANAGER_H
