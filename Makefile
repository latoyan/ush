NAME = ush

CFLG = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP = clang

SRCD = src
INCD = inc
OBJD = obj

LMXD = libmx
LMXA := $(LMXD)/libmx.a
LMXI := $(LMXD)/inc

INC = ush.h
INCS = $(addprefix $(INCD)/, $(INC))

SRC = main.c mx_check_args.c\

SRCS = $(addprefix $(SRCD)/, $(SRC))
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install clean

install: $(LMXA) $(NAME)

$(NAME): $(OBJS)
	@$(COMP) $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXA):
	@make -sC $(LMXD)

clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)

uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)

reinstall: uninstall install
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
