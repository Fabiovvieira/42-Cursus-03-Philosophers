/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:16:53 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/04 09:13:36 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_data *data)
{
	data->init_time = get_time();
	while (data->i_philo < data->num_philos)
	{
		data->pid[data->i_philo] = fork();
		if (data->pid[data->i_philo] == -1)
			return (1);
		if (data->pid[data->i_philo] == 0)
		{
			data->phi[data->i_philo].last_eat_time = get_time();
			break ;
		}
		data->i_philo++;
	}
	return (0);
}

int	check_parent(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (!data->pid[i])
			return (0);
		i++;
	}
	return (1);
}

int	simulation(t_data *data)
{
	int	i;

	i = -1;
	if (check_parent(data))
	{
		if (create_th_monitor(data))
			return (1);
		while (++i < data->num_philos)
			waitpid(-1, NULL, 0);
	}
	else
	{
		if (create_th_death_check(data))
			return (1);
		phi(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || init(data, argc, argv))
	{
		printf("Invalid arguments! Try again.\n");
		free_all(data);
		return (1);
	}
	if (create_process(data))
	{
		free_all(data);
		return (0);
	}
	if (simulation(data))
	{
		usleep(20000);
		free_all(data);
		return (0);
	}
	free_all(data);
	return (0);
}
