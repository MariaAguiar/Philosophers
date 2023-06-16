/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:11:22 by mnascime          #+#    #+#             */
/*   Updated: 2023/06/16 17:12:34 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "philo.h"

void	free_threads(int all, pthread_t *threads)
{
	int	i;

	i = -1;
	if (!threads)
		return ;
	while (++i < all)
		pthread_join(threads[i], NULL);
	free(threads);
}

void	free_forks(int *forks)
{
	if (!forks)
		return ;
	free(forks);
}

void	free_mutexes(int all, pthread_mutex_t **mutex)
{
	int	i;

	i = -1;
	if (!mutex)
		return ;
	while (++i < all)
	{
		pthread_mutex_destroy(mutex[i]);
		free(mutex[i]);
	}
	free(mutex);
}

void	free_philos(int all, t_philo **philos)
{
	int	i;

	i = -1;
	if (!philos)
		return ;
	while (++i < all)
		free(philos[i]);
	free(philos);
}
