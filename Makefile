APP_NAME = uls

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
libmx.h \
uls.h

INCF = \
libmx/inc/libmx.h \
inc/uls.h

SRC = \
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
mx_print_l.c \
mx_get_total.c \
mx_print_total.c \
mx_get_acl.c \
mx_get_xattr.c \
mx_get_group.c \
mx_get_symlink.c \
mx_print_acl_xattr_or_nothing.c \
mx_r_align.c \
mx_l_align.c \
mx_right_align_links.c \
mx_right_align_size.c \
mx_left_align_owner.c \
mx_left_align_group.c \
mx_print_date.c \
mx_sort_by_name.c \
mx_settings.c \
mx_output.c

SRCF = \
src/main.c \
src/mx_errors_handler.c \
src/mx_store_flags.c \
src/mx_store_files.c \
src/mx_check_flags.c \
src/mx_print_spaces.c \
src/mx_get_file_type.c \
src/mx_get_permissions.c \
src/mx_read_data.c \
src/mx_search_strarr.c \
src/mx_print_l.c \
src/mx_get_total.c \
src/mx_print_total.c \
src/mx_get_acl.c \
src/mx_get_xattr.c \
src/mx_get_group.c \
src/mx_get_symlink.c \
src/mx_print_acl_xattr_or_nothing.c \
src/mx_r_align.c \
src/mx_l_align.c \
src/mx_right_align_links.c \
src/mx_right_align_size.c \
src/mx_left_align_owner.c \
src/mx_left_align_group.c \
src/mx_print_date.c \
src/mx_sort_by_name.c \
src/mx_settings.c \
src/mx_output.c

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
mx_print_l.o \
mx_get_total.o \
mx_print_total.o \
mx_get_acl.o \
mx_get_xattr.o \
mx_get_group.o \
mx_get_symlink.o \
mx_print_acl_xattr_or_nothing.o \
mx_r_align.o \
mx_l_align.o \
mx_right_align_links.o \
mx_right_align_size.o \
mx_left_align_owner.o \
mx_left_align_group.o \
mx_print_date.o \
mx_sort_by_name.o \
mx_settings.o \
mx_output.o

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make -C $(LIBMXF)
	@cp $(SRCF) .
	@cp $(INCF) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@mkdir ./obj
	@mv $(OBJ) ./obj

uninstall:
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(INC)
	@rm -rf $(SRC)
	@rm -rf ./obj
	@rm -rf uls.h.gch

reinstall: uninstall all
