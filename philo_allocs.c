/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_allocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:37:05 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/21 14:21:07 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000));
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->threads = malloc(sizeof(pthread_t) * table->n_philos);
	table->start = get_time();
	while (++i < (int)table->n_philos)
	{
		table->philos[i]->lastmeal = get_time();
		if (pthread_create(&table->threads[i], NULL, &actions, table) != 0)
			write(1, "nope!", 5);
	}
}

void	create_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = malloc(table->n_philos * sizeof(*philos));
	if (!philos)
		return ;
	while (++i < (int)table->n_philos)
	{
		philos[i] = malloc(sizeof(*philos[i]));
		if (!philos[i])
		{
			free_philos(i, philos);
			return ;
		}
		philos[i]->id = i + 1;
		philos[i]->lastmeal = 0;
		if (table->n_rounds == -1)
			philos[i]->n_meals = -1;
		else
			philos[i]->n_meals = 0;
		// philos[i]->l_fork = NULL;
		// philos[i]->r_fork = NULL;
	}
	table->philos = philos;
}

// void	link_forks(t_table *table)
// {
// 	unsigned long	i;

// 	i = -1;
// 	while (++i < table->n_philos)
// 	{
// 		table->philos[i]->r_fork = table->mutex[i];
// 		if (table->n_philos != table->philos[i]->id)
// 			table->philos[i]->l_fork = table->mutex[i + 1];
// 		else
// 			table->philos[i]->l_fork = table->mutex[0];
// 	}
// }

void	create_forks(t_table *table)
{
	pthread_mutex_t	**mutex;
	int				*forks;
	unsigned long	i;

	i = -1;
	mutex = malloc(table->n_philos * sizeof(*mutex));
	if (!mutex)
		return ;
	forks = malloc(table->n_philos * sizeof(forks));
	if (!forks)
		return ;
	while (++i < table->n_philos)
	{
		mutex[i] = malloc(sizeof(*mutex[i]));
		if (!mutex[i])
		{
			free_mutexes(i, mutex);
			return ;
		}
		forks[i] = 0;
		pthread_mutex_init(mutex[i], NULL);
	}
	table->forks = forks;
	table->mutex = mutex;
	// link_forks(table);
}
