/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:37:03 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/20 15:50:46 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define ERROR 1

# define YELL "\033[33;1;3m"
# define CYAN "\033[36;1;3m"
# define RESET "\001\033[0m\002"
# define YELL_PS "\001\033[33;1m\002"
# define BLUE_PS "\001\033[34;1m\002"
# define GREEN "\001\033[32;1m\002"
# define RED "\001\033[31;1m\002"

/*     5 — The number of philosophers
    800 — The time a philosopher will die if he doesn’t eat
    200 — The time it takes a philosopher to eat
    200 — The time it takes a philosopher to sleep
    7 — Number of times all the philosophers need to eat before terminating the program ** */

	//une fourchette de chaque coteee, , booleen su chaques forchettes

//	av 1[nb de philo] 2[time to die ] 3[time to eat] 4[time tio sleep] 5[number of time each philo eat]
// init des mutex globeaux 

void *philo_routine(void *data) //routine des philos 
{
	//1 prends fourchettes
	//2 think
	//3 eat
	//4 sleep

/* 	routine(philo):
		si philo.id est impair
			attendre un peu (éviter deadlock)

		tant que personne n’est morte
			penser

			prendre la fourchette gauche
			afficher "has taken a fork"

			prendre la fourchette droite
			afficher "has taken a fork"

			manger
				mettre à jour last_meal
				incrémenter meals_eaten
				attendre time_to_eat

			reposer les fourchettes

			dormir
				attendre time_to_sleep */

	pthread_t tid;
	t_counter *count;
	unsigned int i;

	tid = pthread_self();
	count = (t_counter *)data;
	printf("tread [%1lu] = count at start = [%u]\n", tid, count->count);

	i =0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&count->count_mutex);
		count->count++;
		pthread_mutex_unlock(&count->count_mutex);
		i++;
	}

	pthread_mutex_lock(&count->count_mutex);
	printf("tread [%1lu] = count at end = [%u]\n", tid, count->count);
	pthread_mutex_unlock(&count->count_mutex);
	return (NULL);
}

t_data *pars_data(t_data *data, int ac, char **av)
{

	if (ac > 6 || ac < 5)
	{
		//free_all(); //detruire les mutex et free allocs
		return (NULL);
	}

	data->start_time = data->start_time = get_time_ms();

	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->how_many_meals = atoi(av[5]);
	data->how_many_meals = -1;

	data->someone_died = 0;
	//data.start_time = get_time_ms()
	return (data);
}

int	create_thread_philo(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]); // routine des threads
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);//attendre
		i++;
	}
}

int	create_fork(t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int link_fork_philo(t_philo philo, pthread_mutex_t *forks)
{
	// relier fork left / right aux philos
}

/* pour i de 0 à nb_philo - 1
{
    philos[i].id = i + 1
    philos[i].data = &data
    philos[i].last_meal = start_time
    philos[i].meals_eaten = 0

    philos[i].left_fork  = &forks[i]
    philos[i].right_fork = &forks[(i + 1) % nb_philo]
} */

int philo_init(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	// init la strycr des philos a 0 (utile ?)
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;//ca sdu dernier philo
		// apppeler la fct init thread ici ?
		//philo[i].last_meal = start_time
		philo[i].meals_eaten = 0;


		//assigne les fork a chaques philos
		philo[i].left_fork = &forks[i];
		if (i == data->nb_philo)
			philo[i].right_fork = &forks[0];
		else
			philo[i].right_fork = &forks[i + 1];

		philo[i].data = &data;

		philo[i].status = DEFAULT;
	}
}

void free_all(t_data *data, t_philo **philo, pthread_mutex_t **forks)
{
	int i;

	i = 0;

/* 	destroy_mutex(data)
	free(philos)
	free(forks)
	free(data)
 */

	while (i < data->nb_philo)
	{
		free(philo[i]);
		i++;
	}

	i = 0;

	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(forks[i]);
		i++;
	}
	
	free(data);
}

// gettimeofday() prendre le temps du debut
// int gettimeofday(struct timeval *restrict tv, struct timezone *_Nullable restrict tz);
//


int main(int ac, char **av)
{
	// tab de philos t_philo dans une boucle
	//cas speciale 1 philo
	//si last meal > time_to_die == mort du philo

	t_data *data;
	pthread_mutex_t *forks;
	t_philo *philo;

	data = pars_data(data, ac, av);
	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	//CHECK MALLOC
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	//CHECK MALLOC
	if (forks == NULL)
		return (NULL); // free_all ............

/* 	if (pars_data(data, ac, av) == ERROR)
		return 0;//BAD ARGS */

	//init fork

	if (create_fork(data, &forks) == ERROR)
		return (free_all(data, philo, fork), 0);//erreur fork init

	//init philo
	if (philo_init(data, philo, forks) == ERROR)
		return (free_all(&data, &philo, fork), 0);//erreur philo creation

	//creer les threads
	if (create_thread_philo(data, philo) == ERROR)
		return (free_all(data, philo, fork), 0);//erreur philo creation

/* 	if (data->nb_philo == 1)
	{
		routine_one();//routine philo seul
	} */

	//destroy et free - return 
	//


}

/* pthread_mutex_lock(philo->left_fork);
pthread_mutex_lock(philo->right_fork);

manger

pthread_mutex_unlock(philo->right_fork);
pthread_mutex_unlock(philo->left_fork); */