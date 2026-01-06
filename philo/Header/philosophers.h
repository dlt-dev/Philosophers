/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:40:07 by jdelattr          #+#    #+#             */
/*   Updated: 2026/01/06 21:41:18 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR 1

typedef struct s_data
{
	long			start_time;

	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				how_many_meals;
	int				someone_died;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}					t_philo;

// utils.c
long				get_time_ms(void);
int					ft_atoi(const char *s);
void				free_all(t_data *data, t_philo *philo,
						pthread_mutex_t *forks);
void				print_action(t_philo *philo, char *action);

// routine.c
void				routine_one(t_philo *lonely_philo);
int					all_sated(t_philo *philo);
void				*supervisor_routine(void *philos);
void				*philo_routine(void *arg);

// init.c
t_data				*pars_data(int ac, char **av);
int					create_threads(t_data *data, t_philo *philo);
int					create_fork(t_data *data, pthread_mutex_t *forks);
int					philo_init(t_data *data, t_philo *philo,
						pthread_mutex_t *forks);
int					join_threads(t_data *data, t_philo *philo,
						pthread_t supervisor);

// main.c
void				philo_sleep(long time_to_sleep);
void				philo_eat(long time_to_eat);
int					is_dead_check(t_data *data);
void				set_dead(t_data *data);
int					main(int ac, char **av);

#endif
