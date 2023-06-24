/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:11:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/24 11:34:18 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_write(char message)
{
	if (message == 's')
		printf("is sleeping\n");
	else if (message == 'f')
		printf("has taken a fork\n");
	else if (message == 't')
		printf("is thinking\n");
	else if (message == 'd')
	{
		printf("died\n");
		return (1);
	}
	return (0);
}

void	writes(t_table *table, int id, const int m, char message)
{
	long long	time;
	static int	d = 0;

	pthread_mutex_lock(&table->writes);
	time = get_time() - table->start;
	if (d == 0)
	{
		printf("%lld %d ", time, id);
		if (message == 'e')
		{
			printf("is eating\n");
			if (d == 0)
				d = m;
		}
		else
			d = to_write(message);
	}
	pthread_mutex_unlock(&table->writes);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	value;

	sign = 1;
	value = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		value = value * 10 + (*str++ - '0');
	if ((value * sign) > 2147483647 || (value * sign) < -2147483648)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (value * sign);
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
	if (id % 2 != 0)
	{
		if (get_left_fork(table, id))
		{
			if (table->n_philos > 1)
			{
				if (get_right_fork(table, id))
					return (1);
			}
			else
				pthread_mutex_unlock(table->mutex[id - 1]);
		}
	}
	else
	{
		if (get_right_fork(table, id))
		{
			if (get_left_fork(table, id))
				return (1);
		}
	}
	return (0);
}
