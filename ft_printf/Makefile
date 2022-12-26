# Variables

NAME		= libftprintf.a
INCLUDE		= includes
SRC_DIR		= sources/
OBJ_DIR		= objects/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs
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

SRC_FILES	=	ft_printf flags_utils handlers putui putnbr putptr putstr putul_hex


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		all

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(GREEN)$(BOLD)ft_printf compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(CYAN)ft_printf executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for ft_printf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme | awk '{\
			if ($$NF == "OK!") { \
				print "$(GREEN)"$$0"$(END)" \
			} else if ($$NF == "Error!") { \
				print "$(RED)$(BOLD)"$$0"$(END)" \
			} else if ($$1 == "Error:") { \
				print "$(LIGHT_RED)"$$0"$(END)" \
			} else { print }}'

.PHONY:		all clean fclean re norm