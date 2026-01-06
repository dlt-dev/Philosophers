/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:28:11 by jdelattr          #+#    #+#             */
/*   Updated: 2026/01/06 21:43:04 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*pars_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (ac > 6 || ac < 5)
		return (NULL);
	data->start_time = get_time_ms();
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->how_many_meals = -1;
	if (ac == 6)
		data->how_many_meals = atoi(av[5]);
	if (pthread_mutex_init(&data->mutex_death, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (NULL);
	data->someone_died = 0;
	return (data);
}

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine,
				&philo[i]) != 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	create_fork(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	philo_init(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].id = i + 1;
		philo[i].last_meal = data->start_time;
		philo[i].meals_eaten = 0;
		philo[i].left_fork = &forks[i];
		if (i == data->nb_philo - 1)
			philo[i].right_fork = &forks[0];
		else
			philo[i].right_fork = &forks[i + 1];
		philo[i].data = data;
		i++;
	}
	return (0);
}

int	join_threads(t_data *data, t_philo *philo, pthread_t supervisor)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(supervisor, NULL);
	return (0);
}
