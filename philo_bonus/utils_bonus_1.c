/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:26:08 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:26:31 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (time_ms);
}

void	print(t_data *data, char *msg)
{
	long long		time_ms;

	time_ms = get_time() - data->init_time;
	sem_wait(data->print_out);
	printf("%lld %d %s\n", time_ms, data->phi[data->i_philo].id, msg);
	sem_post(data->print_out);
}
