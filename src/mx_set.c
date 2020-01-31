// #include "uls.h"

// // Takes a strarr, returns number of unique entries, which are also included 
// // in the str.
// // E.G. flags = ["l", "m", "l", "R", "t", "A", "R", "m"] & DATA_FLAGS = "ARalf"
// // mx_count_unique(flags, DATA_FLAGS) returns 3 (unique data flags: l, R, A)
// int mx_count_unique(char **arr, char *str) {
//     int unequal_count = 0;
//     int count = 0;

//     for (int i = 0; i < mx_get_arr_length(arr); i++) {
//         unequal_count++;
//         if (mx_get_char_index(str, arr[i][0]) < 0) {
//             count++;
//             continue;
//         }
//         for (int j = i + 1; j < mx_get_arr_length(arr); j++)
//             if (mx_strcmp(arr[j], arr[i]) == 0) {
//                 count++;
//                 break;
//             }
//     }
//     return unequal_count - count;
// }

// static bool check_set(char **set, char *element) {
//     int i = 0;

//     while (set[i]) {
//         if (mx_strcmp(set[i], element) == 0)
//             return true;
//         i++;
//     }
//     return false;
// }

// char **mx_create_custom_set(char **arr, char *str) {
//     int count = mx_count_unique(arr, str) + 1;
//     char **set = (char **)malloc(sizeof(char *) * count);
//     int j = 0;

//     for (int i = 0; i < count; i++)
//         set[i] = NULL;
//     for (int i = 0; i < mx_get_arr_length(arr); i++) {
//         if (!check_set(set, arr[i])
//             && mx_get_char_index(DATA_FLAGS, *arr[i]) != -1) {
//             set[j++] = mx_strdup(arr[i]);
//         }
//     }       
//     set[j] = NULL;
//     return set;
// }
