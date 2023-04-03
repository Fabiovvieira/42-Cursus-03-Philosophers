/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:45:01 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:17:28 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_data *data)
{
	sem_wait(data->forks);
	print(data, "has taken a fork");
	sem_wait(data->forks);
	print(data, "has taken a fork");
	return (0);
}

int	eating(t_data *data)
{
	sem_wait(data->phi[data->i_philo].lock_death);
	print(data, "is eating");
	data->phi[data->i_philo].last_eat_time = get_time();
	sem_post(data->phi[data->i_philo].lock_death);
	usleep(data->t_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->phi[data->i_philo].eat_count++;
	if (data->phi[data->i_philo].eat_count == data->num_eat)
	{
		sem_post(data->all_ate);
	}
	return (0);
}

int	sleeping(t_data *data)
{
	print(data, "is sleeping");
	usleep(data->t_to_sleep * 1000);
	return (0);
}

int	thinking(t_data *data)
{
	print(data, "is thinking");
	return (0);
}

void	phi(t_data *data)
{
	if (data->phi[data->i_philo].id % 2)
		usleep(2000);
	while (1)
	{
		if (take_fork(data))
			break ;
		if (eating(data))
			break ;
		if (sleeping(data))
			break ;
		if (thinking(data))
			break ;
	}
	return ;
}
