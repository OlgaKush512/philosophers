OS		= ${shell uname}

SRCS	=		srcs/main.c srcs/preliminary/check.c srcs/preliminary/fonctions_std.c srcs/preliminary/init.c srcs/errors/errors.c			\
				srcs/preliminary/time.c srcs/pthreads/actions.c srcs/pthreads/monitoring.c srcs/pthreads/take_fork_actions.c srcs/pthreads/put_print_fork.c\
				srcs/pthreads/mutex_actions.c\

SRCS_BONUS	=	

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME			= philo

NAME_BONUS		= pholo_bonus

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -pthread -g

RM	= rm -f

all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}
bonus : 	${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS}
				${CC} ${CFLAGS} -o ${NAME_BONUS} ${OBJS_BONUS} 

clean:		
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME} ${NAME}_bonus

re:			fclean all

.PHONY:		all mlx clean fclean re bonus
