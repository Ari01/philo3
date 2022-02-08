/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 13:24:32 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, unsigned long t)
{
	unsigned long	start;
	int				death;

	start = get_time();
	death = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_mutex);
		if (philo->info->end_sim)
			death = 1;
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (death || get_timediff(start) > t)
			break ;
		usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
		if (philo->info->n_philo != 1)
		{
			pthread_mutex_lock(philo->lf);
			print_status(philo, philo->info, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
}

int	eat(t_philo *philo)
{
	if (philo->info->n_philo == 1)
	{
		ft_sleep(philo, philo->info->time_to_die);
		return (0);
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->info->death_mutex);
	print_status(philo, philo->info, "is eating");
	if (philo->info->n_eat >= 0 && philo->n_eat >= 0)
		philo->n_eat++;
	ft_sleep(philo, philo->info->time_to_eat);
	drop_forks(philo);
/*	pthread_mutex_lock(&philo->info->room_mutex);
	philo->info->room--;
	pthread_mutex_unlock(&philo->info->room_mutex);*/
	return (1);
}
