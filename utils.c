/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:24:31 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 14:06:10 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_limit(int n, int sign, int x)
{
	if (n > INT_MAX / 10)
		return (0);
	n = n * 10;
	if (sign == 1 && n > INT_MAX - x)
		return (0);
	if (sign == -1 && n * sign < INT_MIN - x)
		return (0);
	return (1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (!check_limit(n, sign, s[i] - '0'))
			return (0);
		n = n * 10 + (s[i++] - '0');
	}
	if (s[i])
		return (0);
	return (n * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	get_timediff(long long start)
{
	long long	end;

	end = get_time();
	return (end - start);
}

void	print_status(t_philo *philo, t_info *info, char *msg)
{
	pthread_mutex_lock(&info->death_mutex);
	if (!info->end_sim)
		printf("%lld %d %s\n", get_timediff(info->time_start), philo->id, msg);
	pthread_mutex_unlock(&info->death_mutex);
}
