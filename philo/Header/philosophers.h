/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:40:07 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/22 17:36:42 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

enum status
{
	DEFAULT,
	FORK, //
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	IS_DEAD,
	DO_NOTHING,
};

/* struct timeval
{
	time_t tv_sec;   // secondes
	suseconds_t tv_usec; // microsecondes
};
 */

typedef struct s_philo
{
	int id;//ID des philos
	pthread_t thread;//THREAD DU PHILO
	long		last_meal;//temps depuis le dernir repas
	int 	meals_eaten;// dans le cas ou il y a un limite ++ 

	pthread_mutex_t *left_fork;//creer tab de fork puis relier aux philos
	pthread_mutex_t *right_fork;

	t_data *data;//contient les rags(parametres du programme)


	int status;
}		t_philo;


typedef struct s_data
{

	long			start_time;

	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				how_many_meals; // -1 si je n'ai rien

	int				someone_died; //etat global, si un philo meurt le programme s'arrete
	

}	t_data;

//main.c

//utils.c

int	ft_atoi(const char *s);

#endif

//data->start_time = get_time_ms();
