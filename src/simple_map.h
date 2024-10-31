#ifndef SIMPLE_MAP_H
#define SIMPLE_MAP_H

#include <cstddef>
#include <cstdlib>
#include <cstring>

// this could probably benefit from using templates

class simple_map_entry {
public:
    const char* key;
    void* value;

    void* operator new(size_t size) {
        void* ptr = malloc(size);

        return ptr;
    }
};

// simple string key -> any value map of fixed size
class simple_map {
public:
    simple_map_entry* entries{};
    size_t maxSize;
    size_t size;

    void* operator new(size_t size) {
        void* ptr = malloc(size);

        return ptr;
    }

    void operator delete(void* ptr) {
        free(ptr);
    }

    void set(const char* key, void* value) {
        size_t i = 0;
        while (i < this->size) {
            if (strcmp(this->entries[i].key, key) == 0) {
                this->entries[i].value = value;

                return;
            }

            i++;
        }

        // TODO: check max size

        this->entries[i].key = key;
        this->entries[i].value = value;
        this->size++;
    }

    void* get(const char* k) const {
        for (size_t i = 0; i < this->size; i++) {
            if (strcmp(this->entries[i].key, k) == 0) {
                return this->entries[i].value;
            }
        }

        return nullptr;
    }

    simple_map() = default;
    explicit simple_map(const size_t size) : maxSize(size), size(0) {
        this->entries = reinterpret_cast<simple_map_entry*>(sizeof(size_t) * 2 * size);
        for (size_t i = 0; i < size; i++) {
            this->entries[i].key = nullptr;
            this->entries[i].value = nullptr;
        }
    }

    ~simple_map() {
        free(this->entries);
    }
};

#endif //SIMPLE_MAP_H
