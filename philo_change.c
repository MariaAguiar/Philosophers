/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:11:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/21 21:37:06 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_write(long long time, char * i, char message)
{
	if (message == 's')
		printf("is sleeping\n");
	else if (message == 'f')
	{
		printf("has taken a fork\n");
		printf("%lld %s ", time, i);
		printf("has taken a fork\n");
	}
	else if (message == 't')
		printf("is thinking\n");
	else if (message == 'd')
	{
		printf("died\n");
		return(1);
	}
	return (0);
}

void	writes(t_table *table, int id, const int m, char message)
{
	char		*i;
	long long	time;
	static int	d = 0;

	i = ft_itoa(id);
	pthread_mutex_lock(&table->writes);
	time = get_time() - table->start;
	if (d == 0)
	{
		printf("%lld %s ", time, i);
		if (message == 'e')
		{
			printf("is eating\n");
			if (d == 0)
				d = m;
		}
		else
			d = to_write(time, i, message);
	}
	pthread_mutex_unlock(&table->writes);
	free(i);
}

t_philo	*get_philo_id(t_table *table, int i)
{
	t_philo	*philo;

	philo = NULL;
	if (i < (int)table->n_philos)
		philo = table->philos[i];
	return (philo);
}

int	manage_forks(t_table *table, int id)
{
	if (id % 2 == 1)
	{
		if (get_left_fork(table, id))
		{
			if (get_right_fork(table, id))
				return (1);
			else
				release_left(table, id);
		}
	}
	else
	{
		if (get_right_fork(table, id))
		{
			if (get_left_fork(table, id))
				return (1);
			else
				release_right(table, id);
		}
	}
	// if (philo->r_fork && !philo->l_fork)
	// 	release_right(table, id);
	// if (philo->l_fork && !philo->r_fork)
	// 	release_left(table, id);
	return (0);
}
