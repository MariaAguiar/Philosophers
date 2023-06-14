/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:44:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/14 11:23:48 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{
    int             id;
    int             is_dead;
    int             l_fork;
    int             r_fork;
}   t_philo;

typedef struct s_table
{
    int             n_philos;
    int             die_t;
    int             eat_t;
    int             sleep_t;
    int             n_rounds;
    int             *forks;
    struct s_philo  **philos;
    pthread_mutex_t mutex;
}   t_table;

t_table *get_args(char **av);
int     ft_atoi(const char *str);

#endif