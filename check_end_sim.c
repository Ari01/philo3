/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:33:29 by dchheang          #+#    #+#             */
/*   Updated: 2022/01/25 12:40:03 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (get_timediff(philo->time_last_meal) >= (unsigned long)info->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		print_status(philo, philo->info, "died");
		pthread_mutex_lock(&info->death_mutex);
		info->end_sim = 1;
		pthread_mutex_unlock(&info->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (0);
}

int	check_eat(t_philo *philo, t_info *info)
{
	int	ret;

	ret = 0;
	if (info->n_eat > 0)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		pthread_mutex_lock(&info->death_mutex);
		if (philo->n_eat >= info->n_eat)
		{
			info->all_ate++;
			philo->n_eat = -1;
		}
		if (info->all_ate >= info->n_philo)
		{
			info->end_sim = 1;
			ret = 1;
		}
		pthread_mutex_unlock(&info->death_mutex);
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	return (ret);
}

void	check_end_sim(t_philo *philo, t_info *info)
{
	int	i;
	int	end_sim;

	end_sim = 0;
	while (!end_sim)
	{
		i = 0;
		while (!end_sim && i < info->n_philo)
		{
			end_sim = check_death(&philo[i], info);
			i++;
		}
		i = 0;
		while (!end_sim && i < info->n_philo)
		{
			end_sim = check_eat(&philo[i], info);
			i++;
		}
	}
}
