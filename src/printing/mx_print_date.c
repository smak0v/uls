#include "uls.h"

static void print_full_date(char *str_date) {
    char *date = NULL;

    str_date += 4;
    date = mx_strndup(str_date, mx_strlen(str_date) - 1);
    mx_printstr(date);
    mx_strdel(&date);
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

static void print(time_t date, int print_full_time) {
    time_t now = 0;
    time_t diff = 0;
    time_t half_year = 0;
    char *str_date = NULL;

    str_date = ctime(&date);
    if (print_full_time) {
        print_full_date(str_date);
        return;
    }
    now = time(NULL);
    diff = now - date;
    half_year = (365 / 2) * 86400;
    if (diff < 0)
        diff *= -1;
    if (diff >= half_year)
        print_date_with_year(str_date);
    else
        print_date_with_time(str_date);
}

void mx_print_date(t_data *data, t_settings *settings) {
    if (settings->time == crt)
        print(data->creation_time, settings->full_time);
    else if (settings->time == chg)
        print(data->last_changed, settings->full_time);
    else if (settings->time == acc)
        print(data->last_access, settings->full_time);
    else
        print(data->last_modified, settings->full_time);
}
