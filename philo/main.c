/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:16:53 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/05 16:38:34 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	free(data->forks);
	free(data->philos);
	free(data);
}

void	print(t_philo *philo, char *msg)
{
	long long		time_ms;

	time_ms = get_time() - philo->data->init_time;
	printf("%lld %d %s\n", time_ms, philo->id, msg);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(2000);
	while (1)
	{
		// Lock the left fork
		pthread_mutex_lock(&philo->l_fork->f_mutex);
		print(philo, "has taken a fork");

		// Lock the right fork
		pthread_mutex_lock(&philo->r_fork->f_mutex);
		print(philo, "has taken a fork");

		// Philosopher is eating
		print(philo, "is eating");
		philo->last_eat_time = get_time();
		philo->eat_count++;
		usleep(philo->data->t_to_eat * 1000);

		// Put down the forks
		pthread_mutex_unlock(&philo->r_fork->f_mutex);
		pthread_mutex_unlock(&philo->l_fork->f_mutex);

		// Philosopher is sleeping
		print(philo, "is sleeping");
		usleep(philo->data->t_to_sleep * 1000);

		// Philosopher is thinking
		print(philo, "is thinking");
	}
}

int	check_philos(t_data *data)
{
	int			i;
	long long	time_now;
	int			count;

	while (1)
	{
		i = 0;
		count = 0;
		time_now = get_time();
		while (i < data->num_philos)
		{
			if (time_now - data->philos[i].last_eat_time > data->t_to_die)
			{
				print(&data->philos[i], "died");
				return (1);
			}
			if (data->philos[i].eat_count >= data->num_eat)
				count++;
			i++;
		}
		if (count == data->num_philos)
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
		data->philos[i].last_eat_time = get_time();
		if(pthread_create(&data->philos[i].th_philo, NULL, &philosopher, &data->philos[i]) != 0)
		{
			printf("Error creating philosopher!\n");
			return (1);
		}
		pthread_detach(data->philos[i].th_philo);
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
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}
