/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:48:11 by jdelattr          #+#    #+#             */
/*   Updated: 2026/01/06 21:41:56 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(const char *s)
{
	int	result;
	int	i;
	int	signe;

	result = 0;
	i = 0;
	signe = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
	{
		i++;
	}
	if (s[i] == '-' || s[i] == '+')
	{
		return (0);
	}
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * signe);
}

void	free_all(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (forks && i < data->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_print);
	free(forks);
	free(philo);
	free(data);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!is_dead_check(philo->data))
		printf("%ld %d %s\n", get_time_ms() - philo->data->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->data->mutex_print);
}
