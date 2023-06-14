/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:17:08 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/14 11:23:49 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	free_philos(int all, t_philo	**philos)
{
	int	i;

	i = -1;
	if (!philos)
		return ;
	while (++i < all)
		free(philos[i]);
	free(philos);
}

void	create_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = malloc(table->n_philos * sizeof(*philos));
	if (!philos)
		return ;
	while (++i < table->n_philos)
	{
		philos[i] = malloc(sizeof(*philos[i]));
		if (!philos[i])
		{
			free_philos(i, philos);
			return ;
		}
		philos[i]->id = i;
	}
	table->philos = philos;
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

t_table *get_args(char **av)
{
	t_table *table;

	table = malloc(sizeof(*table));
	if (!table)
		return NULL;
	table->n_philos = ft_atoi(av[1]);
	table->die_t = ft_atoi(av[2]);
	table->eat_t = ft_atoi(av[3]);
	table->sleep_t = ft_atoi(av[4]);
	if (av[5])
		table->n_rounds = ft_atoi(av[5]);
	else
		table->n_rounds = -1;
	return (table);
}

int main(int ac, char **av)
{
	t_table *table;

	table = NULL;
	if ((ac == 5 || (ac == 6 && ft_atoi(av[5]) > 0)) && ft_atoi(av[1]) > 0)
	{
		table = get_args(av);
		if (!table)
			return (0);
		create_philos(table);
		printf("%d\n", table->philos[0]->id);
	}
	else
		printf("Invalid Arguments\n");
	if (table)
	{
		if (table->philos)
			free_philos(table->n_philos, table->philos);
		free(table);
	}
	return (0);
}

// pthread_mutex_t mutex;

// void* thread_function(void)
// {
//     pthread_mutex_lock(&mutex);
//     printf("Thread executing\n");
//     pthread_mutex_unlock(&mutex);
//     pthread_exit(NULL);
// }

// int main(void)
// {
//     pthread_t thread1;
//     pthread_t thread2;

//     pthread_mutex_init(&mutex, NULL);
//     pthread_create(&thread1, NULL, thread_function, NULL);
//     pthread_create(&thread2, NULL, thread_function, NULL);
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);
//     pthread_mutex_destroy(&mutex);
//     return 0;
// }