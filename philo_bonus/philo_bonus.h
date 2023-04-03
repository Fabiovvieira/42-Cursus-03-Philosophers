/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:19:32 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/04/03 20:32:50 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo{
	int			id;
	long long	last_eat_time;
	int			eat_count;
	sem_t		*lock_death;
}	t_philo;

typedef struct s_data{
	int			num_philos;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	long long	init_time;
	int			num_eat;
	int			someone_died;
	int			everyone_ate;
	int			*pid;
	int			i_philo;
	sem_t		*print_out;
	sem_t		*forks;
	sem_t		*one_died;
	sem_t		*all_ate;
	sem_t		*finish;
	t_philo		*phi;
}	t_data;

/*utils_bonus.c*/

int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);

/*utils_bonus_1.c*/

long long	get_time(void);
void		print(t_data *data, char *msg);

/*free_all_bonus.c*/

void		free_all(t_data *data);

/*init_bonus.c*/

int			init(t_data *data, int argc, char **argv);
void		init_semaphore(t_data *data);
void		init_data(t_data *data, char **argv);

/*philos_bonus.c*/

int			take_fork(t_data *data);
int			eating(t_data *data);
int			sleeping(t_data *data);
int			thinking(t_data *data);
void		phi(t_data *data);

/*thread_bonus.c*/

void		*check_death(void *arg);
void		*check_all_ate(void *arg);
int			create_th_monitor(t_data *data);
void		*death_check_phi(void *arg);
int			create_th_death_check(t_data *data);

/*main_bonus.c*/

int			create_process(t_data *data);
int			check_parent(t_data *data);
int			simulation(t_data *data);

#endif
