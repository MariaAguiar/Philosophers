/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:44:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/20 21:40:17 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	unsigned long	id;
	long long		lastmeal;
	int				n_meals;
	// pthread_mutex_t	*l_fork;
	// pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_table
{
	unsigned long	n_philos;
	long long		start;
	long long		die_t;
	long long		eat_t;
	long long		sleep_t;
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

// Actions
void	eating(t_table *table, unsigned long id);
int		get_left_fork(t_table *table, const unsigned long id);
int		get_right_fork(t_table *table, const unsigned long id);
void	release_left(t_table *table, const unsigned long id);
void	release_right(t_table *table, const unsigned long id);

// Change
void	writes(t_table *table, const int id, int message);
t_philo	*get_philo_id(t_table *table, int i);
int		manage_forks(t_table *table, int id);

// Frees
void	free_philos(int all, t_philo **philos);
void	free_mutexes(int all, pthread_mutex_t **mutex);
void	free_forks(int *forks);
void	free_threads(int all, pthread_t *threads);

// Allocs
long	get_time(void);
void	init_philos(t_table *table);
void	create_philos(t_table *table);
// void	link_forks(t_table *table);
void	create_forks(t_table *table);

// Philos
t_table	*get_args(char **av);
void	*actions(void *arg);
void	destroy_table(t_table *table);

#endif