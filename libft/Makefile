# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tosinga <tosinga@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/02 18:40:40 by tosinga       #+#    #+#                  #
#    Updated: 2022/02/02 18:40:40 by tosinga       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=		libft.a

SRC		=		ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_free.c \
				ft_split.c \
				ft_intlen.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

BONUS_SRC = 	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c 


HEADER		=	libft.h
OBJECTS		=	$(SRC:.c=.o)
BONUS_OBJS	=	$(BONUS_SRC:.c=.o) 
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc

ifdef BONUS
	COMPILATION=$(OBJECTS) $(BONUS_OBJS)
else
	COMPILATION=$(OBJECTS)
endif

all: $(NAME)

$(NAME): $(COMPILATION) $(HEADER)
	$(AR) rcs $(NAME) $(COMPILATION)


%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	@ $(MAKE) all BONUS=1

.PHONY: all clean fclean re bonus
