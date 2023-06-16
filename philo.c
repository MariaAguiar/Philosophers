/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:17:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/16 17:41:32 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	destroy_table(t_table *table)
{
	if (table)
	{
		if (table->philos)
		{
			usleep(10000);
			free_philos(table->n_philos, table->philos);
			free_forks(table->forks);
			free_mutexes(table->n_philos, table->mutex);
			free_threads(table->n_philos, table->threads);
			pthread_mutex_destroy(&table->ids);
		}
		free(table);
	}
}

void	*actions(void *arg)
{
	t_table		*table;
	t_philo		*philo;
	static int	i = -1;

	table = (t_table *)arg;
	pthread_mutex_lock(&table->ids);
	philo = table->philos[++i];
	pthread_mutex_unlock(&table->ids);
	while (philo->n_meals < table->n_rounds)
	{
		pthread_mutex_lock(&table->writes);
		printf("%lu here\n", philo->id);
		pthread_mutex_unlock(&table->writes);
		philo->n_meals++;
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
