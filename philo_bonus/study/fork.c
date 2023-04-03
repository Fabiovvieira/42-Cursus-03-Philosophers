/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:58:12 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/01 16:14:30 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int	check_pid(int *pid, int num_philo)
{
	int i;

	i = 0;
	while (i < num_philo)
	{
		if (!pid[i])
			return (0);
		i++;
	}
	return(1);
}

int	main(void)
{
	int num_philo = 5;
	int pid[num_philo];
	for (int i = 0; i < num_philo; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			break ;
	}
	if (check_pid(pid, num_philo))
	{
		for (int i = 0; i < num_philo; i++)
		{
			waitpid(-1, NULL, 0);
		}
		for(int i = 0; i < num_philo; i++)
		{
			printf("pid %d is %d\n",i, pid[i]);
			fflush(stdout);
		}
	}else
	{
		usleep(1000);
		for(int i = 0; i < num_philo; i++)
		{
			printf("pid %d is %d\n",i, pid[i]);
			fflush(stdout);
		}
	}
	// printf("Hello world in pid: %d\n", pid);
	// if (pid == 0)
	// 	printf("this is child process\n");
	// else
	// 	printf("this is parent process\n");
	return (0);
}
