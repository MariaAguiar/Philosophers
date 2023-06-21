/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:07:06 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/21 15:00:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_table *table, unsigned long id, const long long last)
{
	long start;

	start = get_time();
	while(1)
	{
		if (get_time() - start >= table->sleep_t)
		{
			writes(table, id, 't');
			break;
		}
		if ((get_time() - last) > table->die_t)
		{
			death_flag(table, id);
			break ;
		}
	}
}

void	eating(t_table *table, unsigned long id)
{
	writes(table, id, 'e');
	table->philos[id - 1]->lastmeal = get_time();
	ft_sleep(table, id, table->philos[id - 1]->lastmeal);
	release_left(table, id);
	release_right(table, id);
	writes(table, id, 's');
	ft_sleep(table, id, table->philos[id - 1]->lastmeal);
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
