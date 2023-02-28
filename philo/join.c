/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/25 09:29:40 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>

pthread_mutex_t	mutex;

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*res = malloc(sizeof(int));
	printf("Routine: Number of dice = %d\n", value);
	*res = value;
	return ((void *)res);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	*res;
	pthread_t	th;
	struct timeval tv1, tv2;
	srand(time(NULL));
	int	i;

	i = 0;
	gettimeofday(&tv1, NULL);
	pthread_mutex_init(&mutex, NULL);

	if(pthread_create(&th , NULL, &roll_dice, NULL) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	printf("Thread 1 has started\n");
	if(pthread_join(th, (void **)&res) != 0)
	{
		printf("Error!\n");
		return (1);
	}
	printf("Thread 1 has fineshed\n");
	printf("Main: Number of dice = %d\n", *res);
	pthread_mutex_destroy(&mutex);
	gettimeofday(&tv2, NULL);
	printf("time to process = %d\n", (int)(tv2.tv_usec - tv1.tv_usec));
	return (0);
}
