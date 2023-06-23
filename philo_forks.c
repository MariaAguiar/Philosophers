/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:07:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 15:57:10 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_nrzero(t_table *table, const unsigned long id)
{
	if (pthread_mutex_lock(table->mutex[0]) == 0)
	{
		if (table->forks[0] == 0)
		{
			table->forks[0] = (int)id;
			writes(table, id, 0, 'f');
			return (1);
		}
		else if (table->forks[0] == id)
			return (1);
		else
			pthread_mutex_unlock(table->mutex[0]);
	}
	else
		pthread_mutex_unlock(table->mutex[0]);
	return (0);
}

int	get_left_fork(t_table *table, const unsigned long id)
{
	if (table->n_philos != id)
	{
		if (pthread_mutex_lock(table->mutex[id]) == 0)
		{
			if (table->forks[id] == 0)
			{
				table->forks[id] = (int)id;
				writes(table, id, 0, 'f');
				return (1);
			}
			else if (table->forks[id] == id)
				return (1);
		}
		else
		{
			pthread_mutex_unlock(table->mutex[id]);
			return (0);
		}
	}
	else
		return (get_nrzero(table, id));
	return (0);
}

int	get_right_fork(t_table *table, const unsigned long id)
{
	if (pthread_mutex_lock(table->mutex[id - 1]) == 0 && table->n_philos > 1)
	{
		if (table->forks[id - 1] == 0)
		{
			table->forks[id - 1] = (int)id;
			writes(table, id, 0, 'f');
			return (1);
		}
		else if (table->forks[id - 1] == id)
		{
			if (table->n_philos > 1)
				return (1);
			return (0);
		}
	}
	else
		pthread_mutex_unlock(table->mutex[id - 1]);
	return (0);
}

static void	release_even(t_table *table, const unsigned long id)
{
	if (table->n_philos != id)
	{
		table->forks[id] = 0;
		pthread_mutex_unlock(table->mutex[id]);
	}
	else
	{
		table->forks[0] = 0;
		pthread_mutex_unlock(table->mutex[0]);
	}
	table->forks[id - 1] = 0;
	pthread_mutex_unlock(table->mutex[id - 1]);
}

void	release_forks(t_table *table, const unsigned long id)
{
	if (id % 2 != 0)
	{
		table->forks[id - 1] = 0;
		pthread_mutex_unlock(table->mutex[id - 1]);
		if (table->n_philos != id)
		{
			table->forks[id] = 0;
			pthread_mutex_unlock(table->mutex[id]);
		}
		else
		{
			table->forks[0] = 0;
			pthread_mutex_unlock(table->mutex[0]);
		}
	}
	else
		release_even(table, id);
}
