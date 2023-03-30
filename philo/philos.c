/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:45:01 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/29 16:41:25 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->data->everyone_ate || philo->data->someone_died)
		return (1);
	pthread_mutex_lock(&philo->r_fork->f_mutex);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->l_fork->f_mutex);
	print(philo, "has taken a fork");
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->data->everyone_ate || philo->data->someone_died)
		return (1);
	print(philo, "is eating");
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->data->t_to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->r_fork->f_mutex);
	pthread_mutex_unlock(&philo->l_fork->f_mutex);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (philo->data->everyone_ate || philo->data->someone_died)
		return (1);
	print(philo, "is sleeping");
	usleep(philo->data->t_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (philo->data->everyone_ate || philo->data->someone_died)
		return (1);
	print(philo, "is thinking");
	return (0);
}

void	*phi(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(2000);
	while (1)
	{
		if (take_fork(philo))
			break ;
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
