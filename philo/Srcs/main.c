/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:37:03 by jdelattr          #+#    #+#             */
/*   Updated: 2026/01/06 21:40:20 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(long time_to_sleep)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time_to_sleep)
		usleep(100);
}

void	philo_eat(long time_to_eat)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time_to_eat)
		usleep(100);
}

int	is_dead_check(t_data *data)
{
	int	check_dead;

	pthread_mutex_lock(&data->mutex_death);
	check_dead = data->someone_died;
	pthread_mutex_unlock(&data->mutex_death);
	return (check_dead);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex_death);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->mutex_death);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		supervisor;

	data = pars_data(ac, av);
	if (!data)
		return (ERROR);
	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!forks || !philo)
		return (free_all(data, philo, forks), ERROR);
	if (create_fork(data, forks) == ERROR)
		return (free_all(data, philo, forks), ERROR);
	if (philo_init(data, philo, forks) == ERROR)
		return (free_all(data, philo, forks), ERROR);
	if (create_threads(data, philo) == ERROR)
		return (free_all(data, philo, forks), ERROR);
	if (pthread_create(&supervisor, NULL, supervisor_routine, philo) != 0)
		return (free_all(data, philo, forks), ERROR);
	if (join_threads(data, philo, supervisor))
		return (free_all(data, philo, forks), ERROR);
	free_all(data, philo, forks);
	return (0);
}
