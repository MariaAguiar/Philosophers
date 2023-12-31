/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_allocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:37:05 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/25 17:59:15 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->threads = malloc(sizeof(pthread_t) * table->n_philos);
	if (!table->threads)
		return ;
	table->start = get_time();
	while (++i < (int)table->n_philos)
	{
		pthread_mutex_init(&table->philos[i]->last, NULL);
		table->philos[i]->lastmeal = get_time();
		if (pthread_create(&table->threads[i], NULL, &actions, table) != 0)
			write(1, "nope!", 5);
	}
	if (table->n_philos > 1)
	{
		while (1)
		{
			if (check_death(table))
				break ;
		}
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
			philos[i]->n_meals = table->n_rounds;
	}
	table->philos = philos;
}

void	create_forks(t_table *table)
{
	pthread_mutex_t	**mutex;
	unsigned long	*forks;
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
			free_mutexes(table, i, mutex);
			return ;
		}
		forks[i] = 0;
		pthread_mutex_init(mutex[i], NULL);
	}
	table->forks = forks;
	table->mutex = mutex;
}
