/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:11:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/20 21:39:46 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	writes(t_table *table, int id, int message)
{
	char	*i;
	char	*time;

	i = ft_itoa(id);
	time = ft_itoa(get_time() - table->start);
	pthread_mutex_lock(&table->writes);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, i, ft_strlen(i));
	if (message == 'e')
		write(1, " is eating\n", 11);
	else if (message == 's')
		write(1, " is sleeping\n", 13);
	else if (message == 'f')
	{
		write(1, " has taken a fork\n", 18);
		write(1, time, ft_strlen(time));
		write(1, " ", 1);
		write(1, i, ft_strlen(i));
		write(1, " has taken a fork\n", 18);
	}
	else if (message == 't')
		write(1, " is thinking\n", 13);
	else if (message == 'd')
		write(1, " died\n", 6);
	pthread_mutex_unlock(&table->writes);
	free(i);
	free(time);
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
	if (get_left_fork(table, id))
	{
		if (get_right_fork(table, id))
			return (1);
		else
			release_right(table, id);
	}
	// if (philo->r_fork && !philo->l_fork)
	// 	release_right(table, id);
	// if (philo->l_fork && !philo->r_fork)
	// 	release_left(table, id);
	return (0);
}
