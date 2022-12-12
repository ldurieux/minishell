NAME		= minishell

VERSION		= 0.0.1

SRCS		= \
			  main.c \
			  srcs/exec/init.c \
			  srcs/exec/run.c \
			  srcs/exec/add_cmd.c \

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
		@echo -e "\e[1m\e[38;5;27m    _____  .__ \e[38;5;33m      .__ \e[31m   _______.__           .__  .__   "
		@echo -e "\e[1m\e[38;5;27m   /     \ |__|\e[38;5;33m ____ |__|\e[31m  /   ____/  |__   ____ |  | |  |  "
		@echo -e "\e[1m\e[38;5;27m  /  \ /  \|  |\e[38;5;33m/    \|  |\e[31m  \____  \|  |  \_/ __ \|  | |  |  "
		@echo -e "\e[1m\e[38;5;27m /    Y    \  |\e[38;5;33m   |  \  |\e[31m  /       \   Y  \  ___/|  |_|  |__"
		@echo -e "\e[1m\e[38;5;27m \____|__  /__|\e[38;5;33m___|  /__|\e[31m /______  /___|  /\___  >____/____/"
		@echo -e "\e[1m\e[38;5;27m         \/    \e[38;5;33m    \/    \e[31m        \/     \/     \/    \e[0mversion \e[1m$(VERSION)\e[0m"

.PHONY: all clean fclean re bonus libs banner

