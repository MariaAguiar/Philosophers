/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:48:55 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 17:05:18 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	death_flag(t_table *table, unsigned int id)
{
	pthread_mutex_lock(&table->death);
	if (table->is_dead == 0)
	{
		writes(table, id, 0, 'd');
		table->is_dead = 1;
	}
	pthread_mutex_unlock(&table->death);
}

int	check_death(t_table *table)
{
	unsigned int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i]->last);
		if ((get_time() - table->philos[i]->lastmeal) > table->die_t)
		{
			death_flag(table, table->philos[i]->id);
			pthread_mutex_unlock(&table->philos[i]->last);
			return (1);
		}
		pthread_mutex_unlock(&table->philos[i]->last);
	}
	return (0);
}

int	check_stop(t_table *table)
{
	pthread_mutex_lock(&table->death);
	if (table->is_dead == 1)
	{
		pthread_mutex_unlock(&table->death);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&table->death);
		if (table->n_rounds == -1)
			return (1);
		pthread_mutex_lock(&table->meals);
		if (table->ok_meals == (int)table->n_philos && table->n_rounds > -1)
		{
			pthread_mutex_unlock(&table->meals);
			return (0);
		}
		pthread_mutex_unlock(&table->meals);
	}
	return (1);
}
