SRCS	= main.cpp \
			Server.cpp \
			Client.cpp \
			CreateClientCon.cpp \
			Hadlein.cpp \
			handleout.cpp \
			handleerr.cpp \
			parsing.cpp \

OBJS 	= ${SRCS:.cpp=.o}

NAME 	= ircserv

CC		= c++

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror -std=c++98 -g -fsanitize=address

.cpp.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

${NAME}: 	${OBJS}
			${CC} $(CFLAGS) ${OBJS} -o ${NAME} 

all:		${NAME}

clean:		
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


