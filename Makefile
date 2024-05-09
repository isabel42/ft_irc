SRCS	= main.cpp \
			Server.cpp \
			Client.cpp \
			CreateClientCon.cpp \
			Hadlein.cpp \
			handleout.cpp \
			handleerr.cpp \
			parsing.cpp \
			utils.cpp \
			commands/nick.cpp \
			commands/user.cpp \
			commands/pass.cpp

OBJS		= ${SRCS:%.cpp=${DIR_OBJS}%.o}

NAME 	= ircserv

CPP			= c++

DIR_SRCS	= srcs/

DIR_OBJS	= objs/

# DEP			= ${OBJS:%.o=%.d}

CPPFLAGS	= -Wall -Wextra -Werror -std=c++98 -c -I. -I./includes

RM 			= rm -f

all:	${NAME}

${NAME} : ${OBJS}
	${CPP} $^ -o $@

${OBJS} : ${DIR_OBJS}%.o: ${DIR_SRCS}%.cpp
	mkdir -p ${@D}
	${CPP} ${CPPFLAGS} $< -o $@
# -include ${DEP}

clean:
	${RM} -r ${DIR_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re