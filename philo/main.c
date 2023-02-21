/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:16:53 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/21 18:16:51 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	x = 2;

void	*routine()
{
	x++;
	sleep(2);
	printf("value of x : %d\n", x);
	printf("Process id : %d\n", getpid());
	return ((void *)1);
}

void	*routine2()
{
	sleep(2);
	printf("value of x : %d\n", x);
	printf("Process id : %d\n", getpid());
	return ((void *)1);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	t1, t2;
	if(pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	if(pthread_create(&t2, NULL, &routine2, NULL) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	if(pthread_join(t1, NULL) != 0)
	{
		printf("Error!\n");
		return (1);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		printf("Error!\n");
		return (1);
	}
	return (0);
}
