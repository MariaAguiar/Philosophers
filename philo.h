/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:44:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/23 11:58:29 by mnascime         ###   ########.fr       */
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
	pthread_mutex_t	last;
}	t_philo;

typedef struct s_table
{
	unsigned long	n_philos;
	long long		start;
	long long		die_t;
	long long		eat_t;
	long long		sleep_t;
	int				n_rounds;
	int				ok_meals;
	int				is_dead;
	int				*forks;
	struct s_philo	**philos;
	pthread_mutex_t	**mutex;
	pthread_mutex_t	ids;
	pthread_mutex_t	writes;
	pthread_mutex_t	meals;
	pthread_mutex_t	death;
	pthread_t		*threads;
}	t_table;

// Allocs
void	init_philos(t_table *table);
void	create_philos(t_table *table);
void	create_forks(t_table *table);

// End
int		check_stop(t_table *table);
void	death_flag(t_table *table, unsigned int id);
int		check_death(t_table *table);

// Forks
int		get_nrzero(t_table *table, const unsigned long id);
int		get_left_fork(t_table *table, const unsigned long id);
int		get_right_fork(t_table *table, const unsigned long id);
void	release_left(t_table *table, const unsigned long id);
void	release_right(t_table *table, const unsigned long id);

// Frees
void	free_philos(int all, t_philo **philos);
void	free_mutexes(t_table *table, int all, pthread_mutex_t **mutex);
void	free_forks(int *forks);
void	free_threads(int all, pthread_t *threads);
void	destroy_table(t_table *table);

// libft
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

// Utils
int		to_write(long long time, char *i, char message);
void	writes(t_table *table, const int id, const int m, char message);
t_philo	*get_philo_id(t_table *table, int i);
int		manage_forks(t_table *table, int id);

// Utils2
long	get_time(void);
t_philo	*get_philo(t_table *table);
int	upd_meals(t_table *table, unsigned long id);
void	ft_sleep(t_table *table, const long long time, \
t_philo *philo, const char m);

// Philo
void	eating(t_table *table, unsigned long id);
t_table	*get_args(char **av);
void	*actions(void *arg);

#endif