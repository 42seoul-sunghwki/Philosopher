/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/02 23:48:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_msg_philo(pthread_mutex_t *mutex, long time, long ph, char *msg)
{
	int	ret;
	
	ret = pthread_mutex_lock(mutex);
	if (ret)
		return (ret);
	printf("%ld %ld %s\n", time / THOUSAND, ph, msg);
	ret = pthread_mutex_unlock(mutex);
	return (ret);
}

void	*philo(void *input)
{
	t_thread	ph;
	t_info		info;
	int		ret;
	long	microsec_period;
	long	start_eating; //millisecond
	long	start_sleeping;
	long	start_thinking;

	ph = *(t_thread *)input;
	info = ph.info;
	start_sleeping = 0;
	start_eating = 0;
	start_thinking = 0;
	
	//eating
	while (1)
	{
	if (ph.ph_name % 2 == 0)
	{
		while (1)
		{
			if (*ph.left_f == FALSE)
			{
				*ph.left_f = TRUE;
				ret = pthread_mutex_lock(ph.left_fork);
				if (*ph.right_f == FALSE)
				{
					*ph.right_f = TRUE;
					ret = pthread_mutex_lock(ph.right_fork);
					break;
				}
				else
				{
					*ph.left_f = FALSE;
					pthread_mutex_unlock(ph.left_fork);
				}
			}
			usleep(100);
		}
	}
	else
	{
		while (1)
		{
			if (*ph.right_f == FALSE)
			{
				*ph.right_f = TRUE;
				ret = pthread_mutex_lock(ph.right_fork);
				if (*ph.left_f == FALSE)
				{
					*ph.left_f = TRUE;
					ret = pthread_mutex_lock(ph.left_fork);
					break;
				}
				else
				{
					*ph.right_f = FALSE;
					ret = pthread_mutex_unlock(ph.right_fork);
				}
			}
			usleep(50);
		}
	}
	//thinking printing
	if (start_thinking)
	{
		microsec_period = ft_now_microsec() - start_eating;
		if (microsec_period >= ph.info.time_to_die)
		{
			
			*ph.count_eat = -1;
			if (_msg_philo(ph.print, microsec_period, ph.ph_name, "died"))
				return (NULL);
		}
		else
		{
			if (_msg_philo(ph.print, microsec_period - start_eating - start_sleeping, ph.ph_name, "is thinking"))
				return (NULL);
		}
	}
	start_eating = ft_now_microsec();
	if (ph.info.time_to_die <= ph.info.time_to_eat)
		usleep(ph.info.time_to_die);
	else
		usleep(ph.info.time_to_eat);
	if (ph.ph_name % 2 == 0)
	{
		*ph.left_f = FALSE;
		*ph.right_f = FALSE;
		ret = pthread_mutex_unlock(ph.left_fork);
		ret = pthread_mutex_unlock(ph.right_fork);
	}
	else
	
	{	*ph.left_f = FALSE;
		*ph.right_f = FALSE;
		ret = pthread_mutex_unlock(ph.right_fork);
		ret = pthread_mutex_unlock(ph.left_fork);
	}
	//eating or dying printing
	microsec_period = ft_now_microsec() - start_eating;
	if (microsec_period >= ph.info.time_to_die)
	{
		*ph.count_eat = -1;
		if (_msg_philo(ph.print, microsec_period, ph.ph_name, "died"))
			return (NULL);
	}
	else
	{
		if (_msg_philo(ph.print, microsec_period, ph.ph_name, "is eating"))
			return (NULL);
	}
	//sleeping
	start_sleeping = ft_now_microsec();
	if (ph.info.time_to_die - ph.info.time_to_eat <= ph.info.time_to_sleep)
		usleep(ph.info.time_to_die - ph.info.time_to_eat);
	else
		usleep(ph.info.time_to_sleep);
	//sleeping or dying printing
	microsec_period = ft_now_microsec() - start_eating;
	if (microsec_period >= ph.info.time_to_die)
	{
		*ph.count_eat = -1;
		if (_msg_philo(ph.print, microsec_period, ph.ph_name, "died"))
			return (NULL);
	}
	else
	{
		printf("after : %ld, start_sleeping : %ld\n", microsec_period, start_sleeping);
		if (_msg_philo(ph.print, microsec_period - start_sleeping, ph.ph_name, "is sleeping"))
			return (NULL);
	}
	start_thinking = ft_now_microsec();
	}
}
