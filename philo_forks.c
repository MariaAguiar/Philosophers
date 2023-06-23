/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:07:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 11:58:32 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_nrzero(t_table *table, const unsigned long id)
{
	if (pthread_mutex_lock(table->mutex[0]) == 0 && table->forks[0] == 0)
	{
		table->forks[0] = id;
		pthread_mutex_unlock(table->mutex[0]);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(table->mutex[0]);
		return (0);
	}
}

int	get_left_fork(t_table *table, const unsigned long id)
{
	if (table->n_philos != id)
	{
		if (pthread_mutex_lock(table->mutex[id]) == 0 && table->forks[id] == 0)
		{
			table->forks[id] = (int)id;
			pthread_mutex_unlock(table->mutex[id]);
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
}

int	get_right_fork(t_table *table, const unsigned long id)
{
	if (pthread_mutex_lock(table->mutex[id - 1]) == 0
		&& table->forks[id - 1] == 0)
	{
		table->forks[id - 1] = id;
		pthread_mutex_unlock(table->mutex[id - 1]);
		return (1);
	}
	else
		pthread_mutex_unlock(table->mutex[id - 1]);
	return (0);
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
