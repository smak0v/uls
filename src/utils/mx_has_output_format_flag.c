#include "uls.h"

bool mx_has_output_format_flag(char **flags) {
    int arr_len = mx_get_arr_length(flags);

    for (; arr_len >= 0; --arr_len)
        for (int i = 0; i < mx_strlen(MODE_FLAGS); ++i)
            if (mx_get_char_index(flags[arr_len], MODE_FLAGS[i]) == 0)
                return true;
    return false;
}
