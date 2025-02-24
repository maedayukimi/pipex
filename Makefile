NAME	= pipex

CC 	= cc
CFLAGS	= -Wall -Wextra -Werror

LIBFT_NAME	= libft.a
LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC		= -I ./includes/\
		  -I ./libft/

SRC_PATH	= srcs/
SRC		= \
		  pipex.c \
		  utils.c \
		  msg.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH	= obj/
OBJ		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

HEADERS		= $(includes/pipex.h)

all:	$(LIBFT) $(OBJ_PATH) $(OBJS) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean
