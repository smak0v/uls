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
main.c

SRCF = \
src/main.c

OBJ = \
main.o

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
