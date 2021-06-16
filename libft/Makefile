.PHONY: all clean fclean re bonus

NAME	= libft.a

SRCS		= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_putstr.c ft_count_base.c ft_putnbr_base.c ft_putchar.c ft_uitoa.c ft_putnbr_base.c ft_count_digit.c ft_ltoa.c ft_absolute.c \
ft_atol.c ft_argstoints.c 

OBJS		= ${SRCS:.c=.o}

CC			= cc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

$(NAME):	${OBJS}
		ar rcs ${NAME} $?

%.o: 	%.c	libft.h
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

bonus: 	${OBJS}
		ar rs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all