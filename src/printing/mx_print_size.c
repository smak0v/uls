#include "uls.h"

static void print_size(off_t size, int spaces, int format, int is_device) {
    char *tmp = NULL;

    if (format && !is_device) {
        tmp = mx_convert_size(size);
        mx_print_spaces(4 - mx_strlen(tmp));
    }
    else if (format && is_device) {
        tmp = mx_convert_size(size);
        mx_print_spaces(spaces - mx_strlen(tmp));
    }
    else {
        tmp = mx_lltoa(size);
        mx_print_spaces(spaces - mx_strlen(tmp));
    }
    mx_printstr(tmp);
    mx_strdel(&tmp);
}

void mx_print_size(t_data *data, t_max_len *max_len, bool is_device_met,
t_settings *settings) {
    int format = settings->format_size;

    if (is_device_met)
        if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode)) {
            mx_print_spaces(3 - mx_strlen(data->major));
            mx_printstr(data->major);
            mx_printstr(", ");
            mx_print_spaces(3 - mx_strlen(data->minor));
            mx_printstr(data->minor);
        }
        else
            print_size(data->file_size, 8, format, is_device_met);
    else
        print_size(data->file_size, max_len->sizes, format, is_device_met);
}

