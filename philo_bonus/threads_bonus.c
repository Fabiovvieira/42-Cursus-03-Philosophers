/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:20:22 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:23:15 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	sem_wait(data->one_died);
	while (++i < data->num_philos)
		sem_post(data->all_ate);
	return (NULL);
}

void	*check_all_ate(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->all_ate);
		data->everyone_ate++;
		if (data->everyone_ate == data->num_philos)
		{
			while (++i < data->num_philos)
				kill(data->pid[i], SIGKILL);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_th_monitor(t_data *data)
{
	pthread_t	monitor_death;
	pthread_t	monitor_all_ate;

	if (pthread_create(&monitor_death, NULL, &check_death, data) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	pthread_detach(monitor_death);
	if (pthread_create(&monitor_all_ate, NULL, &check_all_ate, data) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	pthread_detach(monitor_all_ate);
	return (0);
}

void	*death_check_phi(void *arg)
{
	t_data		*data;
	long long	time_now;

	data = (t_data *)arg;
	while (1)
	{
		time_now = get_time();
		if (time_now - data->phi[data->i_philo].last_eat_time > data->t_to_die)
		{
			sem_wait(data->phi[data->i_philo].lock_death);
			print(data, "died");
			sem_post(data->one_died);
			exit (0);
		}
	}
}

int	create_th_death_check(t_data *data)
{
	pthread_t	death_check;

	if (pthread_create(&death_check, NULL, &death_check_phi, data) != 0)
	{
		printf("Error creating thread!\n");
		return (1);
	}
	pthread_detach(death_check);
	return (0);
}
