APP_NAME = uls

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
inc/ \
libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
main.c \
mx_errors_handler.c \
mx_store_flags.c \
mx_store_files.c \
mx_check_flags.c \
mx_print_spaces.c \
mx_get_file_type.c \
mx_get_permissions.c \
mx_read_data.c \
mx_search_strarr.c \
mx_print_long.c \
mx_get_total.c \
mx_print_total.c \
mx_get_acl.c \
mx_get_xattr.c \
mx_get_group.c \
mx_get_owner.c \
mx_get_symlink.c \
mx_print_acl_xattr_or_nothing.c \
mx_print_date.c \
comparators/mx_name_comparators.c \
comparators/mx_size_comparators.c \
comparators/mx_time_asc_comparators.c \
comparators/mx_time_desc_comparators.c \
sortings/mx_sort_by_name.c \
sortings/mx_sort_by_creation_time.c \
sortings/mx_sort_by_last_access_time.c \
sortings/mx_sort_by_last_modification_time.c \
sortings/mx_sort_by_last_changed_time.c \
sortings/mx_sort_by_size.c \
sortings/mx_sort_errors.c \
mx_settings.c \
mx_process_output.c \
mx_get_max_len_struct.c \
mx_print_filename_and_total.c \
mx_process_l.c \
mx_get_major.c \
mx_get_minor.c \
mx_check_chr_or_blk_device.c \
mx_print_columns.c \
mx_print_x_columns.c \
mx_get_terminal_width.c \
mx_print_force.c \
mx_print_stream.c \
mx_get_max_filename_length.c \
mx_print_size.c \
mx_convert_size.c \
mx_print_symlink.c \
mx_print_xattrs_text.c \
mx_get_formatted_size.c \
utils/mx_get_max_len_by_strings.c \
utils/mx_get_max_len_by_numbers.c \
mx_has_output_format_flag.c \
mx_get_columns_info.c \
mx_print_filename.c \
mx_print_colored.c \
mx_print_errors.c \
mx_create_error.c \
mx_print_inode.c \
mx_set.c \
mx_get_full_filename.c \
mx_search_arr.c \
mx_append_slash.c \
mx_append_type_sign.c \
mx_print_dir.c \
mx_print_owner_group.c)

OBJ = \
main.o \
mx_errors_handler.o \
mx_store_flags.o \
mx_store_files.o \
mx_check_flags.o \
mx_print_spaces.o \
mx_get_file_type.o \
mx_get_permissions.o \
mx_read_data.o \
mx_search_strarr.o \
mx_print_long.o \
mx_get_total.o \
mx_print_total.o \
mx_get_acl.o \
mx_get_xattr.o \
mx_get_group.o \
mx_get_owner.o \
mx_get_symlink.o \
mx_print_acl_xattr_or_nothing.o \
mx_print_date.o \
mx_name_comparators.o \
mx_size_comparators.o \
mx_time_asc_comparators.o \
mx_time_desc_comparators.o \
mx_sort_by_name.o \
mx_sort_by_creation_time.o \
mx_sort_by_last_access_time.o \
mx_sort_by_last_modification_time.o \
mx_sort_by_last_changed_time.o \
mx_sort_by_size.o \
mx_sort_errors.o \
mx_settings.o \
mx_process_output.o \
mx_get_max_len_struct.o \
mx_print_filename_and_total.o \
mx_process_l.o \
mx_get_major.o \
mx_get_minor.o \
mx_check_chr_or_blk_device.o \
mx_print_columns.o \
mx_print_x_columns.o \
mx_get_terminal_width.o \
mx_print_force.o \
mx_print_stream.o \
mx_get_max_filename_length.o \
mx_print_size.o \
mx_convert_size.o \
mx_print_symlink.o \
mx_print_xattrs_text.o \
mx_get_formatted_size.o \
mx_get_max_len_by_strings.o \
mx_get_max_len_by_numbers.o \
mx_has_output_format_flag.o \
mx_get_columns_info.o \
mx_print_filename.o \
mx_print_colored.o \
mx_print_errors.o \
mx_create_error.o \
mx_print_inode.o \
mx_set.o \
mx_get_full_filename.o \
mx_search_arr.o \
mx_append_slash.o \
mx_append_type_sign.o \
mx_print_dir.o \
mx_print_owner_group.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : uls

uls : $(SRC) inc/uls.h
	@make -C $(LIBMXF)
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@mkdir $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install
