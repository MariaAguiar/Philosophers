/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:17:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 19:55:43 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	eating(t_table *table, unsigned long id)
{
	writes(table, id, upd_meals(table, id), 'e');
	pthread_mutex_lock(&table->philos[id - 1]->last);
	table->philos[id - 1]->lastmeal = get_time();
	pthread_mutex_unlock(&table->philos[id - 1]->last);
	ft_sleep(table, table->eat_t, id, 'e');
	release_forks(table, id);
	writes(table, id, 0, 's');
	ft_sleep(table, table->sleep_t, id, 't');
}

void	*actions(void *arg)
{
	t_table			*table;
	t_philo			*philo;

	table = (t_table *)arg;
	philo = get_philo(table);
	if (!philo)
		return (0);
	while (check_stop(table))
	{
		if ((get_time() - philo->lastmeal) > table->die_t)
		{
			death_flag(table, philo->id);
			break ;
		}
		if (manage_forks(table, philo->id))
			eating(table, philo->id);
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
	table->ok_meals = 0;
	table->threads = NULL;
	return (table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		i;

	table = NULL;
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) < 0)
		{
			printf("Invalid Arguments\n");
			return(0);
		}
	}
	if ((ac == 5 || (ac == 6 && ft_atoi(av[5]) > 0)) && ft_atoi(av[1]) > 0)
	{
		table = get_args(av);
		if (!table)
			return (0);
		create_philos(table);
		create_forks(table);
		pthread_mutex_init(&table->ids, NULL);
		pthread_mutex_init(&table->writes, NULL);
		pthread_mutex_init(&table->death, NULL);
		pthread_mutex_init(&table->meals, NULL);
		init_philos(table);
		destroy_table(table);
	}
	else
		printf("Invalid Arguments\n");
	return (0);
}
