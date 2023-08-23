# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouabba <ebouabba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 12:15:34 by ebouabba          #+#    #+#              #
#    Updated: 2022/10/26 18:02:45 by ebouabba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILE = ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c \
			    ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c \
				 	ft_calloc.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				 		 ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
						  	ft_memmove.c ft_memset.c ft_strchr.c ft_strrchr.c \
							  	ft_strlcat.c ft_strlen.c ft_strncmp.c \
							        ft_tolower.c ft_toupper.c ft_strnstr.c \
                                                ft_strlcpy.c 

NAME = libft.a
OBJ_FILE = $(SRC_FILE:.c=.o)
CFLAGS = -Wall -Werror -Wextra
HEADER = libft.h

all : $(NAME)

$(NAME) : $(OBJ_FILE)
	ar rc $(NAME) $(OBJ_FILE)

%.o:%.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ_FILE)

fclean : clean
	rm -f $(NAME)

re : fclean all
