/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:24:58 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:26:34 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_data *data)
{
	int		i;
	char	*str;

	i = -1;
	sem_unlink("forks");
	sem_unlink("all_ate");
	sem_unlink("one_died");
	sem_unlink("print_out");
	sem_unlink("finish");
	sem_close(data->forks);
	sem_close(data->all_ate);
	sem_close(data->one_died);
	sem_close(data->print_out);
	sem_close(data->finish);
	while (++i < data->num_philos)
	{
		str = ft_itoa(i);
		sem_unlink(str);
		free(str);
		sem_close(data->phi[i].lock_death);
	}
	free(data->phi);
	free(data->pid);
	free(data);
}
