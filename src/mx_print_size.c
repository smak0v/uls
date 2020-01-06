#include "uls.h"

static void print_size(long long file_size, int spaces_count);

void mx_print_size(t_data *data, t_max_len *max_len, bool is_device_met) {
    if (is_device_met)
        if (MX_IS_CHR(data->mode) || MX_IS_BLK(data->mode)) {
            mx_print_spaces(3 - mx_strlen(data->major));
            mx_printstr(data->major);
            mx_printstr(", ");
            mx_print_spaces(3 - mx_strlen(data->minor));
            mx_printstr(data->minor);
            return;
        }
        else
            print_size(data->file_size, 8);
    else
        print_size(data->file_size, max_len->sizes_max_len);
}

static void print_size(long long file_size, int spaces_count) {
    char *size = mx_lltoa(file_size);

    mx_print_spaces(spaces_count - mx_strlen(size));
    mx_printstr(size);
    mx_strdel(&size);
}
