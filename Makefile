# Variables

NAME		= minitalk
INCLUDE		= includes
SRC_DIR		= sources/
OBJ_DIR		= objects/
FT_PRINTF	= ft_printf
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SMAKE		= make --no-print-directory

# Colors

END			=	\033[0m
BOLD		=	\033[1m
UNDER		=	\033[4m
REV			=	\033[7m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
LIGHT_RED	=	\033[0;31m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

SRC_FILES_C	=	client
SRC_FILES_S	=	server


SRC_C 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_C)))
OBJ_C 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_C)))

SRC_S 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_S)))
OBJ_S 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_S)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		all

$(NAME):
			@$(SMAKE) -C ${FT_PRINTF}
			@$(SMAKE) client
			@$(SMAKE) server
			@echo "$(GREEN)$(BOLD)$(NAME) compiled!$(DEF_COLOR)"

client:		$(OBJ_C)
			@$(CC) $(OBJ_C) -L $(FT_PRINTF) -lftprintf -o client
			@echo "$(GREEN)$(BOLD)Client compiled!$(DEF_COLOR)"

server:		$(OBJ_S)
			@$(CC) $(OBJ_S) -L $(FT_PRINTF) -lftprintf -o server
			@echo "$(GREEN)$(BOLD)Server compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -I $(FT_PRINTF)/includes -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(SMAKE) fclean -C ${FT_PRINTF}
			@$(RM) client
			@$(RM) server
			@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re:			fclean all

norm:
			@norminette $(SRC_DIR) $(INCLUDE) | grep -v Norme | awk '{\
			if ($$NF == "OK!") { \
				print "$(GREEN)"$$0"$(END)" \
			} else if ($$NF == "Error!") { \
				print "$(RED)$(BOLD)"$$0"$(END)" \
			} else if ($$1 == "Error:") { \
				print "$(LIGHT_RED)"$$0"$(END)" \
			} else { print }}'

.PHONY:		all clean fclean re norm