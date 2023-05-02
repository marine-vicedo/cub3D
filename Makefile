# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 13:19:56 by pmaimait          #+#    #+#              #
#    Updated: 2023/05/02 11:07:48 by pmaimait         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#									GENERAL               				       #
#------------------------------------------------------------------------------#

NAME	= cub3D
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

#------------------------------------------------------------------------------#
#								HEADER FILES            				       #
#------------------------------------------------------------------------------#

HEADER_FILES	= cub3D
HEADERS_PATH 	= includes/
HEADERS			= $(addsuffix .h, $(addprefix $(HEADERS_PATH), $(HEADER_FILES)))
HEADERS_INC		= $(addprefix -I, $(HEADERS_PATH) $(LIB_HEADER_PATH) $(MLIB_HEADER_PATH))

#------------------------------------------------------------------------------#
#									LIBFT           				   	   	   #
#------------------------------------------------------------------------------#

LIB_NAME 	= ft
LIB_PATH	= libft/
LIB			= -L$(LIB_PATH) -l$(LIB_NAME) -lreadline
LIB_HEADER_PATH = $(LIB_PATH)includes/


#------------------------------------------------------------------------------#
#									minilibx           				   	   	   #
#------------------------------------------------------------------------------#

MLIB_NAME 	= mlx
MLIB_PATH	= minilibx-linux/
MLIB			= -L$(MLIB_PATH) -l$(MLIB_NAME) -lreadline
MLIB_HEADER_PATH = $(MLIB_PATH)minilibx-linux/
MLX_FLAGS	= -L./mlx -lmlx -lm -lX11 -lXext

#------------------------------------------------------------------------------#
#								cub3D FILES           				   	   #
#------------------------------------------------------------------------------#

# List of all .c source files
ROOT_FILE = main
INIT_FOLDER = init/
MOVE_FOLDER = mobe/
PARSING_FOLDER = parsing/
UTILS_FOLDER = utils/


SRCS_PATH = srcs/
SRCS_NAMES 	= $(addsuffix .c,$(ROOT_FILE)) 

# All .o files go to objs directory
OBJS_NAMES	= $(SRCS_NAMES:.c=.o)
OBJS_FOLDERS = $(addprefix $(OBJS_PATH), $(PARSING_FOLDER) $(INIT_FOLDER) $(MOVE_FOLDER) $(PARSING_FOLDER) $(UTILS_FOLDER)) 
OBJS_PATH 	= objs/
OBJS		= $(addprefix $(OBJS_PATH), $(OBJS_NAMES))

# Gcc/Clang will create these .d files containing dependencies
DEPS		= $(addprefix $(OBJS_PATH), $(SRCS_NAMES:.c=.d))

#------------------------------------------------------------------------------#
#								BASCIC RULES	        				       #
#------------------------------------------------------------------------------#

all:	header $(NAME)
	@echo "\n$(GREEN)[ ✔ ] cub3D$(WHITE)"
	@echo "\n▶ TO LAUNCH:\t./cub3D\n"

# Actual target of the binary - depends on all .o files
$(NAME): lib mlib $(HEADERS) $(OBJS)
# Link all the object files
	@$(CC) $(FLAGS) $(MLX_FLAGS) $(HEADERS_INC) $(OBJS) $(LIB) $(MLIB) -lm -o $(NAME) -lmlx -lm -lX11 -lXext
# Build target for every single object file
# The potential dependency on header files is covered
# by calling `-include $(DEPS)`
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
# Create objs directory
	@mkdir -p $(OBJS_FOLDERS)
  # The -MMD flags additionaly creates a .d file with
  # the same name as the .o file.
	@$(CC) $(FLAGS) $(HEADERS_INC) -MMD -MP -o $@ -c $<
	@printf "$(YELLOW). . . COMPILING CUB3D OBJECTS . . . $(GREY)%-33.33s\r$(DEF_COLOR)" $@

lib:
	@$(MAKE) --no-print-directory -C $(LIB_PATH)
	@echo "\n$(GREEN)[ ✔ ] LIBFT$(DEF_COLOR)"

mlib:
	@$(MAKE) --no-print-directory -C $(MLIB_PATH)
	@echo "\n$(GREEN)[ ✔ ] MLIB$(DEF_COLOR)"
	
clean:
	@echo "$(YELLOW)\n. . . CLEANING OBJECTS . . .\n$(DEF_COLOR)"
	@$(MAKE) clean --no-print-directory -C $(LIB_PATH)
	@$(MAKE) clean --no-print-directory -C $(MLIB_PATH)
	@$(RM) -rd $(OBJS_PATH)
	@echo "$(GREEN)[ ✔ ] OBJECTS CLEANED$(DEF_COLOR)"

fclean:	clean
	@echo "$(YELLOW)\n. . . CLEANING REST . . .\n$(DEF_COLOR)"
	@$(MAKE) --no-print-directory fclean -C $(LIB_PATH)
	@$(MAKE) --no-print-directory clean -C $(MLIB_PATH)
	@$(RM) $(NAME)
	@echo "$(GREEN)[ ✔ ] ALL CLEANED$(DEF_COLOR)"

re:	fclean all

# Include all .d files
-include $(DEPS)

.PHONY:	all clean fclean re header norme check lib

#------------------------------------------------------------------------------#
#								CUSTOM RULES    					           #
#------------------------------------------------------------------------------#

define HEADER_PROJECT


     ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
    ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
    ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
    ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
    ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
     ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 
                                             
                                                         
endef
export HEADER_PROJECT

header:
		clear
		@echo "$$HEADER_PROJECT"

check:
	@grep -qe ${USER} -e ${MAIL} srcs/* includes/* && \
	echo "$(GREEN)[ ✔ ]$(WHITE)	Username and email" \
	|| echo "$(RED)[ ✗ ]$(BLUE)	Username and email"
	@ls | grep -q -U $(NAME) && \
	echo "$(GREEN)[ ✔ ]$(WHITE)	Executable name" || \
	echo "$(RED)[ ✗ ]$(BLUE)	Executable name"
	@$(MAKE) norme | grep -B 1 Error && \
	echo "$(RED)[ ✗ ]$(BLUE)	Norme" || \
	echo "$(GREEN)[ ✔ ]$(WHITE)	Norme"

norme:
	norminette $(HEADERS) $(SRCS_PATH) $(LIB_PATH)

#Colors
DEF_COLOR = \033[0;39m
GREY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[1;95m
CYAN = \033[0;96m
WHITE = \033[0;97m



