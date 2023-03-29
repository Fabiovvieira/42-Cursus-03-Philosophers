/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:16:53 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/29 13:23:54 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_ate(int count, t_data *data)
{
	if (count == data->num_philos)
	{
		data->everyone_ate = 1;
		return (1);
	}
	return (0);
}

int	check_philos(t_data *data)
{
	int			i;
	long long	time_now;
	int			count;

	while (1)
	{
		i = -1;
		count = 0;
		time_now = get_time();
		while (++i < data->num_philos)
		{
			if (time_now - data->phi[i].last_eat_time > data->t_to_die)
			{
				print(&data->phi[i], "died");
				data->someone_died = 1;
				return (1);
			}
			if (data->phi[i].eat_count >= data->num_eat)
				count++;
		}
		if (philos_ate(count, data))
			return (1);
	}
}

int	simulation(t_data *data)
{
	int	i;

	i = 0;
	data->init_time = get_time();
	while (i < data->num_philos)
	{
		data->phi[i].last_eat_time = get_time();
		if (pthread_create(&data->phi[i].th_ph, NULL, &phi, &data->phi[i]) != 0)
		{
			printf("Error creating philosopher!\n");
			return (1);
		}
		pthread_detach(data->phi[i].th_ph);
		i++;
	}
	if (check_philos(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || init(data, argc, argv))
	{
		printf("Invalid arguments! Try again.\n");
		free (data);
		return (1);
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
