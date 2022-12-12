NAME		= minishell

VERSION		= 0.0.1

SRCS		= \
			  main.c \
			  srcs/exec/init.c \
			  srcs/exec/run.c \
			  srcs/exec/add_cmd.c \
			  srcs/input/input.c \
			  srcs/input/here_doc.c \


HEADERS		= \
			  includes \
			  
CCDEFS		= \
			  VERSION=\"$(VERSION)\" \
			  NAME=\"$(NAME)\" \

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
CCDBGFLGS	= -DDEBUG -g #-fsanitize=address
CCDEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir
ADDFLAGS	= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
ADDFLAGS2	= -I ~/.brew/opt/readline/include

all : banner libs $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCWFLGS) $(CCDBGFLGS) $(ADDFLAGS) -o $(NAME) $(OBJS) $(LIB_LD) $(LIBS)

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
		$(CC) $(CCWFLGS) $(CCDEPSFLAGS) $(CCDBGFLGS) $(ADDFLAGS2) $(CCDEFSFLGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

banner :
		@echo "\x1b[1m\x1b[38;5;27m    _____  .__ \x1b[38;5;33m      .__ \x1b[31m   _______.__           .__  .__   "
		@echo "\x1b[1m\x1b[38;5;27m   /     \ |__|\x1b[38;5;33m ____ |__|\x1b[31m  /   ____/  |__   ____ |  | |  |  "
		@echo "\x1b[1m\x1b[38;5;27m  /  \ /  \|  |\x1b[38;5;33m/    \|  |\x1b[31m  \____  \|  |  \_/ __ \|  | |  |  "
		@echo "\x1b[1m\x1b[38;5;27m /    Y    \  |\x1b[38;5;33m   |  \  |\x1b[31m  /       \   Y  \  ___/|  |_|  |__"
		@echo "\x1b[1m\x1b[38;5;27m \____|__  /__|\x1b[38;5;33m___|  /__|\x1b[31m /______  /___|  /\___  >____/____/"
		@echo "\x1b[1m\x1b[38;5;27m         \/    \x1b[38;5;33m    \/    \x1b[31m        \/     \/     \/    \x1b[0mversion \x1b[1m$(VERSION)\x1b[0m"

.PHONY: all clean fclean re bonus libs banner

