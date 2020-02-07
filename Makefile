APP_NAME = uls

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
inc/ \
libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
comparators/mx_name_comparators.c \
comparators/mx_size_comparators.c \
comparators/mx_time_asc_comparators.c \
comparators/mx_time_desc_comparators.c \
core/mx_proccess_output.c \
core/mx_process_l.c \
core/mx_read_data.c \
core/mx_settings.c \
core/mx_sort_data_list.c \
getters/mx_get_columns_info.c \
getters/mx_get_file_type.c \
getters/mx_get_full_filename.c \
getters/mx_get_group.c \
getters/mx_get_major.c \
getters/mx_get_max_len_struct.c \
getters/mx_get_minor.c \
getters/mx_get_owner.c \
getters/mx_get_permissions.c \
getters/mx_get_symlink.c \
getters/mx_get_terminal_width.c \
getters/mx_get_total.c \
getters/mx_get_xattr.c \
printing/mx_print_acl_xattr_or_nothing.c \
printing/mx_print_colored.c \
printing/mx_print_columns_colored_spaces.c \
printing/mx_print_columns.c \
printing/mx_print_date.c \
printing/mx_print_dir.c \
printing/mx_print_filename_and_total.c \
printing/mx_print_filename.c \
printing/mx_print_force.c \
printing/mx_print_inode.c \
printing/mx_print_long.c \
printing/mx_print_owner_group.c \
printing/mx_print_size.c \
printing/mx_print_spaces.c \
printing/mx_print_stream.c \
printing/mx_print_symlink.c \
printing/mx_print_tabs.c \
printing/mx_print_total.c \
printing/mx_print_x_columns.c \
printing/mx_print_xattrs_text.c \
sortings/mx_sort_by_creation_time.c \
sortings/mx_sort_by_last_access_time.c \
sortings/mx_sort_by_last_changed_time.c \
sortings/mx_sort_by_last_modification_time.c \
sortings/mx_sort_by_name.c \
sortings/mx_sort_by_size.c \
sortings/mx_sort_errors.c \
sortings/mx_sort.c \
utils/mx_check_chr_or_blk_device.c \
utils/mx_check_flags.c \
utils/mx_clear_errors_list.c \
utils/mx_convert_size.c \
utils/mx_create_errors.c \
utils/mx_errors_handler.c \
utils/mx_free_data.c \
utils/mx_has_acl.c \
utils/mx_has_output_format_flag.c \
utils/mx_round_number.c \
utils/mx_search_strarr.c \
utils/mx_store_files.c \
utils/mx_store_flags.c \
utils/mx_uls_h_get_pow.c \
main.c)

OBJ = \
mx_name_comparators.o \
mx_size_comparators.o \
mx_time_asc_comparators.o \
mx_time_desc_comparators.o \
mx_proccess_output.o \
mx_process_l.o \
mx_read_data.o \
mx_settings.o \
mx_sort_data_list.o \
mx_get_columns_info.o \
mx_get_file_type.o \
mx_get_full_filename.o \
mx_get_group.o \
mx_get_major.o \
mx_get_max_len_struct.o \
mx_get_minor.o \
mx_get_owner.o \
mx_get_permissions.o \
mx_get_symlink.o \
mx_get_terminal_width.o \
mx_get_total.o \
mx_get_xattr.o \
mx_print_acl_xattr_or_nothing.o \
mx_print_colored.o \
mx_print_columns_colored_spaces.o \
mx_print_columns.o \
mx_print_date.o \
mx_print_dir.o \
mx_print_filename_and_total.o \
mx_print_filename.o \
mx_print_force.o \
mx_print_inode.o \
mx_print_long.o \
mx_print_owner_group.o \
mx_print_size.o \
mx_print_spaces.o \
mx_print_stream.o \
mx_print_symlink.o \
mx_print_tabs.o \
mx_print_total.o \
mx_print_x_columns.o \
mx_print_xattrs_text.o \
mx_sort_by_creation_time.o \
mx_sort_by_last_access_time.o \
mx_sort_by_last_changed_time.o \
mx_sort_by_last_modification_time.o \
mx_sort_by_name.o \
mx_sort_by_size.o \
mx_sort_errors.o \
mx_sort.o \
mx_check_chr_or_blk_device.o \
mx_check_flags.o \
mx_clear_errors_list.o \
mx_convert_size.o \
mx_create_errors.o \
mx_errors_handler.o \
mx_free_data.o \
mx_has_acl.o \
mx_has_output_format_flag.o \
mx_round_number.o \
mx_search_strarr.o \
mx_store_files.o \
mx_store_flags.o \
mx_uls_h_get_pow.o \
main.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : libmx.a uls

libmx.a:
	@make -C $(LIBMXF)

uls : $(SRC) inc/uls.h libmx/libmx.a
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
