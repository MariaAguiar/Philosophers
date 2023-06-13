/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:54:37 by margarida         #+#    #+#             */
/*   Updated: 2023/06/12 20:19:55 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_timer
{
    int n_philos;
    int to_die;
    int to_eat;
    int to_sleep;
    int n_rounds;
}   t_timer;

typedef struct s_philo
{
    int n_philos;
    int to_die;
    int to_eat;
    int to_sleep;
    int n_rounds;
}   t_philo;

#endif