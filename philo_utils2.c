/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:52:37 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 17:29:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000));
}

t_philo	*get_philo(t_table *table)
{
	t_philo		*philo;
	static int	i = -1;

	philo = NULL;
	pthread_mutex_lock(&table->ids);
	if (++i < (int)table->n_philos)
		philo = table->philos[i];
	pthread_mutex_unlock(&table->ids);
	return (philo);
}

int	upd_meals(t_table *table, unsigned long id)
{
	if (table->n_rounds == -1)
		return (0);
	pthread_mutex_lock(&table->meals);
	if (table->n_rounds != -1 && table->philos[id - 1]->n_meals > 0)
	{
		table->philos[id - 1]->n_meals--;
		if (table->philos[id - 1]->n_meals == 0)
			table->ok_meals++;
		if (table->ok_meals == (int)table->n_philos && table->n_rounds > -1)
		{
			pthread_mutex_unlock(&table->meals);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&table->meals);
			return (0);
		}
	}
	else
		pthread_mutex_unlock(&table->meals);
	return (0);
}

void	ft_sleep(t_table *table, const long long time, \
t_philo *philo, const char m)
{
	long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
		{
			if (m == 't')
				writes(table, philo->id, 0, 't');
			break ;
		}
	}
}
