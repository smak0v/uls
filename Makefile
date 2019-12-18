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
mx_format_time.c \
mx_print_spaces.c \
mx_get_permissions.c \
mx_print_permissions.c \
mx_read_data.c \
utils.c

SRCF = \
src/main.c \
src/mx_errors_handler.c \
src/mx_store_flags.c \
src/mx_store_files.c \
src/mx_check_flags.c \
src/mx_format_time.c \
src/mx_print_spaces.c \
src/mx_get_permissions.c \
src/mx_print_permissions.c \
src/mx_read_data.c \
src/utils.c

OBJ = \
main.o \
mx_errors_handler.o \
mx_store_flags.o \
mx_store_files.o \
mx_check_flags.o \
mx_format_time.o \
mx_print_spaces.o \
mx_get_permissions.o \
mx_print_permissions.o \
mx_read_data.o \
utils.o

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install:
	@make -C $(LIBMXF)
	@cp $(SRCF) .
	@cp $(INCF) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@mkdir ./obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(INC)
	@rm -rf $(SRC)
	@rm -rf ./obj
	@rm -rf uls.h.gch

reinstall: uninstall install
