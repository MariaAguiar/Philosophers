/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:17:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/20 21:51:15 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

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

void	*actions(void *arg)
{
	t_table			*table;
	t_philo			*philo;

	table = (t_table *)arg;
	philo = get_philo(table);
	if (!philo)
		return (0);
	// if (philo->id % 2)
	// 	usleep(150);
	while (1)
	{
		if (get_time() - philo->lastmeal > table->die_t)
		{
			writes(table, philo->id, 'd');
			exit(1);
		}
		if (manage_forks(table, philo->id))
		{
			writes(table, philo->id, 'f');
			eating(table, philo->id);
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
		create_philos(table);
		create_forks(table);
		pthread_mutex_init(&table->ids, NULL);
		pthread_mutex_init(&table->writes, NULL);
		init_philos(table);
		destroy_table(table);
	}
	else
		printf("Invalid Arguments\n");
	return (0);
}
