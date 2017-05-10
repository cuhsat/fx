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

#define SWAP(x, y) (_) = (x); (x) = (y); (y) = (_);

static unsigned char s[256], x, y, _;

/*
 * fumbled xor
 */
static void fumble(unsigned char byte) {
    y += x ^ byte;

    SWAP(s[x], s[y])
}

/*
 * key scheduling algorithm
 */
static void ksa(unsigned char *key, size_t length) {
    x = sizeof(s) - 1; y = 0;

    do {
        s[x] = x;
    } while (x-- > 0);

    do {
        fumble(key[x % length]);
    } while (x-- > 0);
}

/*
 * pseudorandom number generator
 */
static unsigned char prng() {
    fumble(s[x++]);

    return s[x ^ y];
}

/*
 * main
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: fx KEY\n");
        return 1;
    }

    ksa((unsigned char *)argv[1], strlen(argv[1]));

    while (!feof(stdin))
        fputc(fgetc(stdin) ^ prng(), stdout);

    return 0;
}