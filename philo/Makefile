NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		utils.c \
		init.c \
		philos.c

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
