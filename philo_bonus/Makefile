NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main_bonus.c \
		utils_bonus.c \
		utils_bonus_1.c \
		init_bonus.c \
		philos_bonus.c \
		threads_bonus.c \
		free_all_bonus.c


LTHREAD = -pthread

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LTHREAD) -o $@ $(OBJS)
	@echo "Compiled $@"

clean:
	@rm -rf $(OBJS)
	@echo "Remove objects files."

fclean: clean
	@rm -rf $(NAME)
	@echo "Remove static libraries and executables."

re: fclean all
