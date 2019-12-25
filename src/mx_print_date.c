#include "uls.h"

static void print_date_with_year(char *str_date);
static void print_date_with_time(char *str_date);

void mx_print_date(time_t date) {
    time_t now = time(NULL);
    time_t diff = now - date;
    time_t half_year = (365.24 / 2) * 86400;
    char *str_date = NULL;

    if (diff < 0)
        diff *= -1;
    str_date = ctime(&date);
    if (diff >= half_year)
        print_date_with_year(str_date);
    else
        print_date_with_time(str_date);
}

static void print_date_with_time(char *str_date) {
    char *date = NULL;

    str_date += 4;
    date = mx_strndup(str_date, 12);
    mx_printstr(date);
    mx_strdel(&date);
}

static void print_date_with_year(char *str_date) {
    char *date = mx_strnew(12);

    str_date += 4;
    date = mx_strncpy(date, str_date, 6);
    str_date += 15;
    date[6] = ' ';
    date[7] = str_date[0];
    date[8] = str_date[1];
    date[9] = str_date[2];
    date[10] = str_date[3];
    date[11] = str_date[4];
    mx_printstr(date);
    mx_strdel(&date);
}
