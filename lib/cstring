#include <cstddef>
#include <cstdlib>
#include <cstdint>

#ifndef _cstring_
#define _cstring_

// TODO: refactor all the counter variable based methods to increment the pointers (see: strcat)

void memcpy(void* destination, const void* source, size_t num) {
    for (size_t i = 0; i < num; i++) {
        ((uint8_t*)destination)[i] = ((uint8_t*)source)[i];
    }
}

void memmove(void* destination, const void* source, size_t num) {
    void* buffer = malloc(num);
    memcpy(buffer, source, num);
    memcpy(destination, buffer, num);
    free(buffer);
}

char* strcpy(char* destination, const char* source) {
    for (size_t i = 0; source[i]; i++) {
        ((uint8_t*)destination)[i] = ((uint8_t*)source)[i];
    }

    return destination;
}

char* strncpy(char* destination, const char* source, size_t num) {
    for (size_t i = 0; source[i] && i < num; i++) {
        ((uint8_t*)destination)[i] = ((uint8_t*)source)[i];
    }

    for (size_t i = 0; i < num; i++) {
        ((uint8_t*)destination)[i] = 0;
    }

    return destination;
}

char* strcat(char* destination, const char* source) {
    // Skip to end of destination
    while (*destination) {
        destination++;
    }

    while (*source) {
        *destination = *source;
        source++;
        destination++;
    }

    *destination = 0;

    return destination;
}

// TODO: strncat

// TODO: memcmp

int strcmp(const char* str1, const char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

// TODO: strcoll

// TODO: strncmp

// TODO: strxfrm

// TODO: memchr

// TODO: strchr

// TODO: strcspn

// TODO: strpbrk

// TODO: strrchr

// TODO: strspn

// TODO: strstr

// TODO: strtok

// TODO: memset

// TODO: strerror

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }

    return len;
}

#endif
