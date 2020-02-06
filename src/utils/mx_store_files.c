#include "uls.h"

static char **store_files(int files_count, int argc, int flags, char **argv) {
    char **files = NULL;
    int j = -1;

    if (files_count) {
        files = (char **)malloc(sizeof(char *) * (++files_count));
        for (int i = flags + 1; i < argc; ++i)
            files[++j] = mx_strdup(argv[i]);
        files[++j] = NULL;
    }
    else {
        files = (char **)malloc(sizeof(char *) * (2));
        files[0] = mx_strdup(".");
        files[1] = NULL;
    }
    return files;
}

static int count_files(int argc, int flags_count) {
    int count = 0;

    for (int i = flags_count + 1; i < argc; ++i)
        ++count;
    return count;
}

static int count_flags_with_stop_flag(int argc, char **argv) {
    int count = 0;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if ((argv[i][1] == '-') && (mx_strlen(argv[i]) == 2)) {
                ++count;
                break;
            }
            ++count;
            continue;
        }
        break;
    }
    return count;
}

char **mx_store_files(int argc, char **argv) {
    int flags_count = count_flags_with_stop_flag(argc, argv);
    int files_count = count_files(argc, flags_count);

    return store_files(files_count, argc, flags_count, argv);
}
