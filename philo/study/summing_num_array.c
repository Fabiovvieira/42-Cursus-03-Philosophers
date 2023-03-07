/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summing_num_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:36:25 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/25 10:23:29 by fvalli-v         ###   ########.fr       */
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
	int	sum = 0;
	int	i = 0;
	while (i < 5)
	{
		sum += primes[index + i];
		i++;
	}
	printf("Local sum = %d\n", sum);
	*(int *)arg = sum;
	return (arg);
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	th[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		int	*a = malloc(sizeof(int));
		*a = i * 5;
		if(pthread_create(&th[i] , NULL, &routine, a) != 0)
		{
			printf("Error creating thread!\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	int	globalSum = 0;
	while (i < 2)
	{
		void *r;
		if(pthread_join(th[i], &r) != 0)
		{
			printf("Error!\n");
			return (1);
		}
		globalSum += *(int *)r;
		free(r);
		printf("Thread %d has fineshed\n", i);
		i++;
	}
	printf("Global sum = %d\n", globalSum);
	return (0);
}
