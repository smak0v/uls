#include "uls.h"

int mx_search_arr(t_settings *setup, t_data_enum value) {
    t_data_enum *arr = setup->data;

    for (int i = 0; i < setup->data_len; i++) {
        if (arr[i] == value)
            return 1;
    }

    return 0;
}
