/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/25 09:14:37 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 100000; i++)
	{
		if(pthread_mutex_lock(&mutex) != 0)
		{
			printf("Error on mutex lock!\n");
			return (void *)0;
		}
		mails++;
		if(pthread_mutex_unlock(&mutex) != 0)
		{
			printf("Error on mutex lock!\n");
			return (void *)0;
		}
	}
	return ((void *)1);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	th[2];
	struct timeval tv1, tv2;
	int	i;

	i = 0;
	gettimeofday(&tv1, NULL);
	pthread_mutex_init(&mutex, NULL);

	while (i < 2)
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
	while (i < 2)
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
	gettimeofday(&tv2, NULL);
	printf("time to process = %d\n", (int)(tv2.tv_usec - tv1.tv_usec));
	printf("Number of mails %d\n", mails);
	return (0);
}
