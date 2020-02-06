#include "uls.h"

static void uls_h_write_number(char *size, off_t st_size) {
    off_t number = st_size;
    int c = 0;

    for (c = 3; c > 0; --c) {
        if (number > 0) {
            size[c - 1] = number % 10 + 48;
            number /= 10;
        }
        else
            size[c - 1] = ' ';
    }
}

static void add_preffix(char *size, int pow) {
    switch (pow) {
        case 10:
            size[3] = 'K';
            break;
        case 20:
            size[3] = 'M';
            break;
        case 30:
            size[3] = 'G';
            break;
        case 40:
            size[3] = 'T';
            break;
        case 50:
            size[3] = 'P';
            break;
    }
}

static void size_more_thousand(off_t num, double g, int pow, char *size) {
    if (g >= 9.95) {
        num = mx_round_number(g);
        if (num < 999)
            uls_h_write_number(size, num);
        else {
            num = mx_round_number(g * 10);
            pow += 10;
            size[0] = num / 10 + 48;
            size[1] = '.';
            size[2] = num % 10 + 48;
        }
    }
    else {
        num = mx_round_number(g * 10);
        size[0] = num / 10 + 48;
        size[1] = '.';
        size[2] = num % 10 + 48;
    }
    add_preffix(size, pow);
}

static void size_less_thousand(off_t st_size, char *size) {
    off_t num = st_size;

    if (num == 0)
        size = mx_strcpy(size, "  0B");
    else if (st_size < 1000) {
        uls_h_write_number(size, num);
        size[3] = 'B';
    }
}

char *mx_convert_size(off_t st_size) {
    char *size = mx_strnew(4);
    double g = 0.0;
    int pow = 0;

    if (st_size < 1000)
        size_less_thousand(st_size, size);
    else if (st_size >= 1000) {
        pow = mx_uls_h_get_pow(st_size);
        g = st_size / mx_pow(2, pow);
        size_more_thousand(st_size, g, pow, size);
    }
    return size;
}
