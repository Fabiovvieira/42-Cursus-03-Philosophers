/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:38:39 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/29 13:22:37 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	i = 0;
	sign = ft_isspace(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * res);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (time_ms);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].f_mutex);
		i++;
	}
	free(data->forks);
	free(data->phi);
	free(data);
}

void	print(t_philo *philo, char *msg)
{
	long long		time_ms;

	if (philo->data->everyone_ate || philo->data->someone_died)
		return ;
	time_ms = get_time() - philo->data->init_time;
	pthread_mutex_lock(&philo->data->stdout);
	printf("%lld %d %s\n", time_ms, philo->id, msg);
	pthread_mutex_unlock(&philo->data->stdout);
}
