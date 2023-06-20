/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:07:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/20 19:37:13 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_table *table, unsigned long id)
{
	writes(table, id, 'e');
	usleep(table->eat_t * 1000);
	table->philos[id - 1]->lastmeal = get_time();
	release_right(table, id);
	release_left(table, id);
	writes(table, id, 's');
	usleep(table->sleep_t * 1000);
	writes(table, id, 't');
}

int	get_left_fork(t_table *table,const unsigned long id)
{
	int	i;

	i = 0;
	if (table->n_philos != id)
	{
		if (pthread_mutex_lock(table->mutex[id]) == 0 && table->forks[id] == 0)
		{
			table->forks[id] = (int)id;
			i = 1;
			pthread_mutex_unlock(table->mutex[id]);
		}
	}
	if (table->n_philos == id)
	{
		if (pthread_mutex_lock(table->mutex[0]) == 0)
		{
			if(table->forks[0] == 0)
			{
				table->forks[0] = id;
				i = 1;
			}
			pthread_mutex_unlock(table->mutex[0]);
		}
	}
	return (i);
}

int	get_right_fork(t_table *table, const unsigned long id)
{
	int i;

	i = 0;
	if (pthread_mutex_lock(table->mutex[id - 1]) == 0 && table->forks[id - 1] == 0)
	{
		table->forks[id - 1] = id;
		i = 1;
		pthread_mutex_unlock(table->mutex[id - 1]);
	}
	return (i);
}

void	release_left(t_table *table, const unsigned long id)
{
	if (table->n_philos != id)
	{
		pthread_mutex_lock(table->mutex[id]);
		table->forks[id] = 0;
		pthread_mutex_unlock(table->mutex[id]);
	}
	if (table->n_philos == id)
	{
		pthread_mutex_lock(table->mutex[0]);
		table->forks[0] = 0;
		pthread_mutex_unlock(table->mutex[0]);
	}
}

void	release_right(t_table *table, const unsigned long id)
{
	if (pthread_mutex_lock(table->mutex[id - 1]) == 0)
	{
		table->forks[id - 1] = 0;
		pthread_mutex_unlock(table->mutex[id - 1]);
	}
}
