/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylock_vs_lock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/25 10:37:04 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>
#include <error.h>

int	mails = 0;
pthread_mutex_t	mutex;

// void	*routine()
// {
// 	if(pthread_mutex_lock(&mutex) != 0)
// 	{
// 		printf("Error on mutex lock!\n");
// 		return (void *)0;
// 	}
// 	printf("Got Lock\n");
// 	sleep(1);
// 	if(pthread_mutex_unlock(&mutex) != 0)
// 	{
// 		printf("Error on mutex lock!\n");
// 		return (void *)0;
// 	}
// 	return ((void *)1);
// }

void	*routine()
{
	if(pthread_mutex_trylock(&mutex) == 0)
	{
		printf("Got Lock\n");
		sleep(1);
		if(pthread_mutex_unlock(&mutex) != 0)
		{
			printf("Error on mutex lock!\n");
			return (void *)0;
		}
	}
	else
	{
		printf("Didn't get lock\n");
	}
	return ((void *)1);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	th[4];
	int	i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);

	while (i < 4)
	{
		if(pthread_create(&th[i] , NULL, &routine, NULL) != 0)
		{
			printf("Error creating thread!\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			printf("Error!\n");
			return (1);
		}
		printf("Thread %d has fineshed\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails %d\n", mails);
	return (0);
}
