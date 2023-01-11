NAME		= minishell

VERSION		= 0.0.1

SRCS		= \
			  main.c \
			  srcs/exec/init.c \
			  srcs/exec/destroy.c \
			  srcs/exec/run_child.c \
			  srcs/exec/run_builtin.c \
			  srcs/exec/run_pipe_internal.c \
			  srcs/exec/run.c \
			  srcs/exec/redir.c \
			  srcs/exec/add_cmd.c \
			  srcs/exec/make_argv.c \
			  srcs/exec/get_ret_code.c \
			  srcs/builtin/echo.c \
			  srcs/builtin/unset.c \
			  srcs/builtin/cd.c \
			  srcs/builtin/get_builtin.c \
			  srcs/builtin/env.c \
			  srcs/builtin/pwd.c \
			  srcs/builtin/exit.c \
			  srcs/builtin/export.c \
			  srcs/input/input.c \
			  srcs/input/here_doc.c \
			  srcs/vars/vars.c \
			  srcs/vars/vars_print.c \
			  srcs/vars/vars_convert.c \
			  srcs/vars/add_vars.c \
			  srcs/parsing/check_cmd_line.c \
			  srcs/parsing/check_sp_char.c \
			  srcs/parsing/fill_cmd_tab.c \
			  srcs/parsing/get_cmd.c \
			  srcs/parsing/get_separator.c \
			  srcs/parsing/parsing_utils.c \
			  srcs/parsing/parsing.c \
			  srcs/parsing/replace_vars_utils.c \
			  srcs/parsing/replace_vars.c \
			  srcs/parsing/clean_quotes.c \
			  srcs/parsing/add_exec.c \
			  srcs/parsing/tokenize.c \

HEADERS		= \
			  includes \
			  
CCDEFS		= \
			  VERSION=\"$(VERSION)\" \
			  NAME=\"$(NAME)\" \
			  LCRIMET \

LIB_NAMES	= \
			  libft
			  
LIBS		= $(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

CCDEFSFLGS	= $(foreach def,$(CCDEFS),-D $(def))

BUILDDIR	= .build
OBJS		= $(SRCS:%.c=$(BUILDDIR)/%.o) 
DEPS		= $(SRCS:%.c=$(BUILDDIR)/%.d) 
CC			= cc
CCWFLGS		= -Wall -Wextra -Werror
CCDBGFLGS	= -DDEBUG -g -fsanitize=address
CCDEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir
UNAME		= $(shell uname)
ECHO		:= echo

ifeq ($(UNAME), Linux)
	ECHO += -e
endif

LIBS		+= -lreadline
LIB_LD		+= -L ~/.brew/opt/readline/lib
LIB_HEADERS	+= -I ~/.brew/opt/readline/include

all : banner libs $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCWFLGS) $(CCDBGFLGS) -o $(NAME) $(OBJS) $(LIB_LD) $(LIBS)

bonus : $(NAME)

libs :
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib); \
		)

clean : banner
		-$(RM) $(BUILDDIR)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

-include $(DEPS)

$(BUILDDIR)/%.o : %.c Makefile $(LIB_PATHS)
		@mkdir -p $(@D)
		$(CC) $(CCWFLGS) $(CCDEPSFLAGS) $(CCDBGFLGS) $(CCDEFSFLGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

banner :
		@$(ECHO) "\x1b[1m\x1b[38;5;27m___  ___ _       _ \x1b[31m     _          _ _ "
		@$(ECHO) "\x1b[1m\x1b[38;5;27m|  \/  |(_)     (_)\x1b[31m    | |        | | |"
		@$(ECHO) "\x1b[1m\x1b[38;5;27m|      | _ _ __  _ \x1b[31m ___| |__   ___| | |"
		@$(ECHO) "\x1b[1m\x1b[38;5;27m| |\/| || | '_ \| |\x1b[31m/ __| '_ \ / _ \ | |"
		@$(ECHO) "\x1b[1m\x1b[38;5;27m| |  | || | | | | |\x1b[31m\__ \ | | |  __/ | |"
		@$(ECHO) "\x1b[1m\x1b[38;5;27m\_|  |_/|_|_| |_|_|\x1b[31m|___/_| |_|\___|_|_|"
		@$(ECHO) "\x1b[0m\x1b[1mldurieux & lcrimet            \x1b[0mversion \x1b[1m$(VERSION)\x1b[0m"

.PHONY: all clean fclean re bonus libs banner
