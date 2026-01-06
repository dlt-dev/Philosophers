/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:29 by jdelattr          #+#    #+#             */
/*   Updated: 2026/01/06 21:42:58 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine_one(t_philo *lonely_philo)
{
	print_action(lonely_philo, "has taken a fork");
	usleep(lonely_philo->data->time_to_die * 1000);
	print_action(lonely_philo, "died");
	set_dead(lonely_philo->data);
}

int	all_sated(t_philo *philo)
{
	int	i;

	if (philo[0].data->how_many_meals == -1)
		return (0);
	i = 0;
	while (i < philo[0].data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meals_eaten < philo[i].data->how_many_meals)
		{
			pthread_mutex_unlock(&philo[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (1);
}

void	*supervisor_routine(void *philos)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philos;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo[0].data->nb_philo)
		{
			if (get_time_ms() - philo[i].last_meal > philo[i].data->time_to_die)
			{
				printf("%ld %d died\n", get_time_ms()
					- philo[i].data->start_time, philo[i].id);
				set_dead(philo[i].data);
				return (NULL);
			}
			if (all_sated(philo))
				return (set_dead(philo[0].data), NULL);
			i++;
		}
		usleep(1111);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (routine_one(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1111);
	while (is_dead_check(philo->data) != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		philo->last_meal = get_time_ms();
		philo->last_meal = get_time_ms();
		print_action(philo, "is eating");
		philo_eat(philo->data->time_to_eat);
		philo->meals_eaten = philo->meals_eaten + 1;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_action(philo, "is sleeping");
		philo_sleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
