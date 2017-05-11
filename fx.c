/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 */
#include <stdio.h>
#include <string.h>

#define SWAP3(x, y, z) (_) = (x); (x) = (y); (y) = (z); (z) = (_);

static unsigned char s[256], x, y, z, _;

/*
 * Fumbled XOR
 */
static void fx(unsigned char byte) {
    y = x ^ byte;
    z = x ^ (y + z);

    SWAP3(s[x], s[y], s[z])
}

/*
 * Key Scheduling Algorithm
 */
static void ksa(unsigned char *key, size_t length) {
    x = sizeof(s) - 1; y = z = 0;

    do {
        s[x] = x;
    } while (x-- > 0);

    do {
        fx(key[x % length]);
    } while (x-- > 0);
}

/*
 * Pseudo-Random Number Generator
 */
static unsigned char prng() {
    fx(s[x++]);

    return s[x ^ y ^ z];
}

/*
 * Main
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: fx key\n");
        return 1;
    }

    ksa((unsigned char *)argv[1], strlen(argv[1]));

    while (!feof(stdin)) {
        fputc(fgetc(stdin) ^ prng(), stdout);
    }

    return 0;
}
