/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:38:44 by vmoreau           #+#    #+#             */
/*   Updated: 2021/06/11 17:44:04 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	find_id_fork(t_philo *philo, int *id_left)
{
	if (philo->id == 1)
		*id_left = philo->data->philos[philo->data->nb_philo - 1].id;
	else
		*id_left = philo->id - 1;
}

void		t_fork(pthread_mutex_t *f_l, pthread_mutex_t *f_r, t_philo *philo)
{
	pthread_mutex_lock(f_r);
	display_status(philo, "FORK");
	pthread_mutex_lock(f_l);
	display_status(philo, "FORK");
}

void		r_fork(pthread_mutex_t *f_l, pthread_mutex_t *f_r)
{
	pthread_mutex_unlock(f_l);
	pthread_mutex_unlock(f_r);
}

void		action_eat(t_philo *philo, unsigned int *reset)
{
	int id_left;

	find_id_fork(philo, &id_left);
	t_fork(&philo->data->philos[id_left - 1].fork, &philo->fork, philo);
	philo->time_without_eat = get_time(false, *reset);
	display_status(philo, "EAT");
	philo->ntpe++;
	*reset = get_time(true, *reset);
	usleep(philo->arg.time_eat * 1000);
	r_fork(&philo->data->philos[id_left - 1].fork, &philo->fork);
}

void		action_sleep(t_philo *philo)
{
	display_status(philo, "SLEEP");
	usleep(philo->arg.time_sleep * 1000);
}