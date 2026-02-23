#include "hashtable.h"
#include <math.h>
#include <string.h>

#define PHI ((sqrt(5.0) - 1.0) / 2.0)  // GOLDEN RATIO FOR MULT METHOD

size_t hash_int_modulo(int key, size_t capacity) {
    return key % capacity;
}

size_t hash_int_multiplication_mod(int key, size_t capacity) {
    return ((size_t) floor(key*PHI)) % capacity;
}

size_t hash_float_multiplication(double s, double t,float key, size_t capacity) {
    return ((key-s)/(t-s))*capacity;
}

size_t hash_short_str(const char* key, size_t capacity) {
    const size_t b = 31;
    size_t hash = 0;
    size_t n = strlen(key);

    for (size_t i = 0; i < n; i++) {
        size_t power = 1;
        for (size_t j = 0; j < (n - 1 - i); j++) {
            power *= b;
        }
        hash += (unsigned char)key[i] * power;
    }
    return hash % capacity;
}


size_t hash_long_str_horner(const char* key, size_t capacity) {
    size_t hash = 0;
    size_t b = 127;
    for (size_t i = 0; key[i] != '\0'; i++) {
        hash = (hash * b + (unsigned char)key[i]) % capacity;
    }
    return hash;
}
