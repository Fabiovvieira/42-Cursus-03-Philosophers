/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:56:12 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/29 08:50:16 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args_limits(t_data *data)
{
	if (data->num_philos <= 0
		|| data->t_to_die <= 0
		|| data->t_to_eat <= 0
		|| data->t_to_sleep <= 0
		|| data->num_eat <= 0)
		return (1);
	return (0);
}

static int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_philos)
	{
		data->forks[i].id = i + 1;
		if (pthread_mutex_init(&data->forks[i].f_mutex, NULL) != 0)
		{
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->phi = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_philos)
	{
		data->phi[i].id = i + 1;
		data->phi[i].last_eat_time = 0;
		data->phi[i].eat_count = 0;
		data->phi[i].data = data;
		data->phi[i].l_fork = &data->forks[(i + 1) % data->num_philos];
		data->phi[i].r_fork = &data->forks[i];
		if (data->num_philos == 1)
		{
			data->phi[i].l_fork = &data->forks[i];
			data->phi[i].r_fork = &data->forks[i];
		}
		i++;
	}
	return (0);
}

void	init_data(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->init_time = 0;
	data->everyone_ate = 0;
	data->someone_died = 0;
	data->num_eat = INT_MAX;
}

int	init(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	init_data(data, argv);
	pthread_mutex_init(&data->stdout, NULL);
	if (argc == 6)
		data->num_eat = ft_atoi(argv[5]);
	if (check_args_limits(data))
		return (1);
	if (init_fork(data))
	{
		free(data->forks);
		return (1);
	}
	if (init_philo(data))
	{
		free(data->phi);
		return (1);
	}
	return (0);
}
