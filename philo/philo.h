/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:32 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/03/29 08:49:10 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_fork{
	int				id;
	pthread_mutex_t	f_mutex;
}	t_fork;

typedef struct s_philo{
	int				id;
	long long		last_eat_time;
	int				eat_count;
	pthread_t		th_ph;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data{
	int				num_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	long long		init_time;
	int				num_eat;
	int				someone_died;
	int				everyone_ate;
	pthread_mutex_t	stdout;
	pthread_t		th_starve;
	t_philo			*phi;
	t_fork			*forks;
}	t_data;

/*utils.c*/

int			ft_atoi(const char *nptr);
int			init(t_data *data, int argc, char **argv);
long long	get_time(void);
void		free_all(t_data *data);
void		print(t_philo *philo, char *msg);

/*philos.c*/

int			take_fork(t_philo *philo);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);
void		*phi(void *data);

#endif
