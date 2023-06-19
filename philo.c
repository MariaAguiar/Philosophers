/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:17:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/19 19:47:17 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	writes(pthread_mutex_t *writes, int id, int message)
{
	char *i;

	i = ft_itoa(id);
	pthread_mutex_lock(writes);
	write(1, i, ft_strlen(i));
	if (message == 'e')
		write(1, " is eating\n", 11);
	else if (message == 's')
		write(1, " is sleeping\n", 13);
	else if (message == 'f')
		write(1, " has taken a fork\n", 18);
	else if (message == 't')
		write(1, " is thinking\n", 13);
	else if (message == 'a')
		write(1, " is about to die\n", 17);
	else if (message == 'd')
		write(1, " died\n", 6);
	pthread_mutex_unlock(writes);
	free(i);
}

void	release_right(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(table->mutex[philo->id - 1]);
	table->forks[philo->id] = 0;
	philo->l_fork = NULL;
	pthread_mutex_unlock(table->mutex[philo->id - 1]);
}
void	release_left(t_table *table, t_philo *philo)
{
	if (table->n_philos != philo->id)
	{
		pthread_mutex_lock(table->mutex[philo->id - 1]);
		table->forks[philo->id + 1] = 0;
		philo->r_fork = NULL;
		pthread_mutex_unlock(table->mutex[philo->id - 1]);
	}
	if (table->n_philos == philo->id)
	{
		pthread_mutex_lock(table->mutex[0]);
		table->forks[0] = 0;
		philo->r_fork = NULL;
		pthread_mutex_unlock(table->mutex[0]);
	}
}

void	*actions(void *arg)
{
	t_table		*table;
	t_philo		*philo;
	static int	i = -1;

	table = (t_table *)arg;
	philo = NULL;
	pthread_mutex_lock(&table->ids);
	if (table->philos[++i])
		philo = table->philos[i];
	pthread_mutex_unlock(&table->ids);
	if (!philo)
		return (0);
	int e = 20;
	while (--e > 0)
	{
		if (philo->to_die < table->eat_t && \
		philo->to_die > 0)
			writes(&table->writes, philo->id, 'a');
		if (philo->to_die == 0)
			writes(&table->writes, philo->id, 'd');
		if (philo->l_fork && philo->r_fork)
			{
				writes(&table->writes, philo->id, 'e');
				philo->to_die = table->die_t;
				release_left(table, philo);
				release_right(table, philo);
				writes(&table->writes, philo->id, 's');
				if (usleep(table->sleep_t * 1000) == -1)
					write(1, "Error\n", 6);
				writes(&table->writes, philo->id, 't');
				continue ;
			}
		else
		{
			if (!philo->l_fork)
			{
				if (table->n_philos != philo->id && table->forks[philo->id + 1] == 0)
				{
					pthread_mutex_lock(table->mutex[philo->id - 1]);
					table->forks[philo->id + 1] = (int)philo->id;
					philo->l_fork = &table->forks[philo->id + 1];
					writes(&table->writes, philo->id, 'f');
					pthread_mutex_unlock(table->mutex[philo->id - 1]);
				}
				if (table->n_philos == philo->id && table->forks[0] == 0)
				{
					pthread_mutex_lock(table->mutex[0]);
					table->forks[0] = philo->id;
					philo->l_fork = &table->forks[0];
					writes(&table->writes, philo->id, 'f');
					pthread_mutex_unlock(table->mutex[0]);
				}
			}
			if (!philo->r_fork)
			{
				pthread_mutex_lock(table->mutex[philo->id - 1]);
				if (table->forks[philo->id] == 0)
				{
					table->forks[philo->id] = philo->id;
					philo->r_fork = &table->forks[philo->id];
					writes(&table->writes, philo->id, 'f');
				}
				pthread_mutex_unlock(table->mutex[philo->id - 1]);
			}
			if (philo->r_fork && !philo->l_fork)
				release_right(table, philo);
			if (philo->l_fork && !philo->r_fork)
				release_left(table, philo);
		}
	}
	return (0);
}

t_table	*get_args(char **av)
{
	t_table	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->n_philos = ft_atoi(av[1]);
	table->die_t = ft_atoi(av[2]);
	table->eat_t = ft_atoi(av[3]);
	table->sleep_t = ft_atoi(av[4]);
	table->is_dead = 0;
	if (av[5])
		table->n_rounds = ft_atoi(av[5]);
	else
		table->n_rounds = -1;
	table->threads = NULL;
	return (table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if ((ac == 5 || (ac == 6 && ft_atoi(av[5]) > 0)) && ft_atoi(av[1]) > 0)
	{
		table = get_args(av);
		if (!table)
			return (0);
		create_forks(table);
		create_philos(table);
		pthread_mutex_init(&table->ids, NULL);
		pthread_mutex_init(&table->writes, NULL);
		init_philos(table);
		destroy_table(table);
	}
	else
		printf("Invalid Arguments\n");
	return (0);
}
