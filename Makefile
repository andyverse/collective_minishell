# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slaree <slaree@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 14:24:38 by mcherrie          #+#    #+#              #
#    Updated: 2022/08/25 19:29:35 by slaree           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_MS		=	minishell
HEADER_MS	=	minishell.h


FILES_MS	=	builtin_utils.c cd.c check.c cmd_args.c count.c echo.c env.c exec_utils.c execute.c exit.c \
				export.c free.c heredoc.c init.c lst_utils.c parse_utils.c pipe_utils.c pipex.c pwd.c redirect.c \
				signal.c special_simbols.c split_words.c struct_utils.c struct.c unset.c main.c utils1.c utils2.c \
				utils3.c utils4.c ft_atoi.c ft_split.c

OBJ_MS		=	$(FILES_MS:%.c=%.o)
FLAGS_MS	=	-Wall -Wextra -Werror


.PHONY	: all clean fclean re libft

all		: $(NAME_MS)

%.o	:	%.c  $(HEADER_MS) Makefile
	cc $(FLAGS_MS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I $(HEADER_MS)

$(NAME_MS):	$(OBJ_MS)
	cc $(FLAGS_MS)  -L$(shell brew --prefix readline)/lib -lreadline $(OBJ_MS) -o $@

clean	:
	rm -rf $(OBJ_MS)

fclean	:	clean
	rm -rf $(NAME_MS)

re		: fclean all
