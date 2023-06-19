/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:44:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/19 16:55:18 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	id;
	int			to_die;
	int			n_meals;
	int			*l_fork;
	int			*r_fork;
}	t_philo;

typedef struct s_table
{
	unsigned long	n_philos;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				n_rounds;
	int				is_dead;
	int				*forks;
	struct s_philo	**philos;
	pthread_mutex_t	**mutex;
	pthread_mutex_t	ids;
	pthread_mutex_t	writes;
	pthread_t		*threads;
}	t_table;

// libft
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

// Frees
void	free_philos(int all, t_philo	**philos);
void	free_mutexes(int all, pthread_mutex_t **mutex);
void	free_forks(int *forks);
void	free_threads(int all, pthread_t *threads);

// Allocs
void	init_philos(t_table *table);
void	create_philos(t_table *table);
void	create_forks(t_table *table);

// Philos
t_table	*get_args(char **av);
void	*actions(void *arg);
void	destroy_table(t_table *table);

#endif