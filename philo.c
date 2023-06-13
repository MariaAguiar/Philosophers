/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margarida <margarida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:54:42 by margarida         #+#    #+#             */
/*   Updated: 2023/06/12 20:26:58 by margarida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_timer *get_times(char **av)
{
    t_timer *times;

    times = malloc(sizeof(*times));
    times->n_philos = atoi(av[1]);
    times->to_die = atoi(av[2]);
    times->to_eat = atoi(av[3]);
    times->to_sleep = atoi(av[4]);
    if (av[5])
        times->n_rounds = atoi(av[5]);
    return (times);
}

int main(int ac, char **av)
{
    t_timer *timer;

    if (ac == 5 || ac == 6)
    {
        timer = get_times(av);
        printf("%d\n", timer->n_philos);
    }
    free(timer);
    return (0);
}