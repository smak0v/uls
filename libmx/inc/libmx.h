#ifndef LIBMX_H
#define LIBMX_H

#include <fcntl.h>
#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

// Structures
typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

// Utils pack
void mx_printchar(char c);
void mx_printchar_endl(char c);
void mx_print_unicode(wchar_t c);
void mx_printstr(const char *s);
void mx_printstr_endl(const char *s);
void mx_print_error(const char *error);
void mx_print_error_endl(const char *error);
void mx_print_strarr(char **arr, const char *delim);
int mx_strarr_len(char **strarr);
void mx_printint(int n);
void mx_printint_endl(int n);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
char *mx_nbr_to_hex(unsigned long nbr);
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_itoa(int number);
char *mx_lltoa(long long value);
char *mx_ulltoa(unsigned long long value);
int mx_atoi(const char *str);
int mx_ctoi(char c);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);
int mx_get_arr_length(char **arr);
void mx_del_intarr(int ***array, int length);
void mx_intdel(int **arr);
int mx_get_file_length(const char *file);
int mx_count_unequal(char **arr);
int mx_strarr_len(char **strarr);
int mx_numlen(long long value);
int mx_unumlen(unsigned long long value);

// String pack
int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
char **mx_pop_string_array(char **arr, char *value);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
int mx_strncmp(const char *s1, const char *s2, size_t n);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *file);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
bool mx_isspace(char c);
bool mx_isalpha(char c);
bool mx_isdigit(char c);
bool mx_islower(char c);
bool mx_isupper(char c);
int mx_toupper(int c);
int mx_tolower(int c);

// Memory pack
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c,
                 size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);
void *mx_memalloc(size_t size);

// List pack
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_push_second(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
void mx_clear_list(t_list **list);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));
void mx_list_merge_sort(t_list **head_ptr, bool (*cmp)(void *a, void *b));
void mx_revers_list(t_list **list);
bool mx_is_equal_lists(t_list *a, t_list *b);

// Set pack
bool mx_check_set(char **set, char *element, int set_size);
char **mx_create_set(char **arr);

#endif
