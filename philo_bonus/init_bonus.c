/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:56:12 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:22:34 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	init_philo(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	data->phi = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	data->pid = (int *)malloc(sizeof(int) * data->num_philos);
	if (!data->phi || !data->pid)
		return (1);
	while (i < data->num_philos)
	{
		data->phi[i].id = i + 1;
		data->phi[i].last_eat_time = 0;
		data->phi[i].eat_count = 0;
		str = ft_itoa(i);
		sem_unlink(str);
		data->phi[i].lock_death = sem_open(str, O_CREAT, 0644, 1);
		free(str);
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
	data->i_philo = 0;
}

void	init_semaphore(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("all_ate");
	sem_unlink("one_died");
	sem_unlink("print_out");
	sem_unlink("finish");
	data->forks = sem_open("forks", O_CREAT, 0644, data->num_philos);
	data->all_ate = sem_open("all_ate", O_CREAT, 0644, 0);
	data->one_died = sem_open("one_died", O_CREAT, 0644, 0);
	data->print_out = sem_open("print_out", O_CREAT, 0644, 1);
	data->finish = sem_open("print_out", O_CREAT, 0644, 1);
}

int	init(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	init_data(data, argv);
	if (argc == 6)
		data->num_eat = ft_atoi(argv[5]);
	if (check_args_limits(data))
		return (1);
	if (init_philo(data))
	{
		free(data->phi);
		return (1);
	}
	init_semaphore(data);
	return (0);
}
