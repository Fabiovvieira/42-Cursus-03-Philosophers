/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_args_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/05 16:38:37 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>

int	primes[10] = {2,3,5,7,11,13,17,19,23,29};

void	*routine(void* arg)
{
	int index = *(int*)arg;
	printf("%d\n", primes[index]);
	free(arg);
	return ((void *)1);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	th[10];
	int	i;

	i = 0;
	while (i < 10)
	{
		int	*a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i] , NULL, &routine, a) != 0)
		{
			printf("Error creating thread!\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			printf("Error!\n");
			return (1);
		}
		printf("Thread %d has fineshed\n", i);
		i++;
	}
	return (0);
}
