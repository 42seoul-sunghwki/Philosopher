/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/10 10:32:37 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	_msg_philo(pthread_mutex_t *mutex, t_msg *msg)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret)
		return (ret);
	printf("%ld %ld ", msg->time, msg->ph);
	if (msg->msg == SLEEP)
		printf(SLEEP_MSG);
	else if (msg->msg == EAT)
		printf(EAT_MSG);
	else if (msg->msg == THINK)
		printf(THINK_MSG);
	else if (msg->msg == DIE)
	{
		printf(DIE_MSG);
		return (TRUE);
	}
	printf("\n");
	ret = pthread_mutex_unlock(mutex);
	return (ret);
}

void	*philo(void *input)
{
	t_thread	ph;
	t_info		info;
	t_msg		msg;
	//int		ret;
	long	start_time;
	long	microsec_now;
	long	start_eating; //millisecond
	//long	start_sleeping;
	//long	start_thinking;

	ph = *(t_thread *)input;
	info = ph.info;
	start_time = ft_now_microsec();
	msg.print = ph.print;
	msg.ph = ph.ph_name;
	//start_sleeping = 0;
	start_eating = 0;
	//start_thinking = 0;
	
	//eating
	while (1)
	{
	if (ph.ph_name % 2 == 0)
	{
		pthread_mutex_lock(ph.left_fork);
		*ph.left_f = TRUE;
		pthread_mutex_lock(ph.right_fork);
		*ph.right_f = TRUE;
		//while (1)
		//{

		//	if (*ph.left_f == FALSE)
		//	{
		//		pthread_mutex_lock(ph.left_fork);
		//		*ph.left_f = TRUE;
		//		if (*ph.right_f == FALSE)
		//		{
		//			pthread_mutex_lock(ph.right_fork);
		//			*ph.right_f = TRUE;
		//			break;
		//		}
		//		else
		//		{
		//			*ph.left_f = FALSE;
		//			pthread_mutex_unlock(ph.left_fork);
		//		}
		//	}
		//	usleep(50);
		//}
	}
	else
	{
		pthread_mutex_lock(ph.right_fork);
		*ph.right_f = TRUE;
		pthread_mutex_lock(ph.left_fork);
		*ph.left_f = TRUE;
		//while (1)
		//{
		//	if (*ph.right_f == FALSE)
		//	{
		//		pthread_mutex_lock(ph.right_fork);
		//		*ph.right_f = TRUE;
		//		if (*ph.left_f == FALSE)
		//		{
		//			pthread_mutex_lock(ph.left_fork);
		//			*ph.left_f = TRUE;
		//			break;
		//		}
		//		else
		//		{
		//			*ph.right_f = FALSE;
		//			pthread_mutex_unlock(ph.right_fork);
		//		}
		//	}
		//	usleep(50);
		//}
	}
	pthread_mutex_lock(ph.left_fork);
	*ph.left_f = TRUE;
	pthread_mutex_lock(ph.right_fork);
	*ph.right_f = TRUE;

	//eating printing
	start_eating = ft_now_microsec();
	microsec_now = ft_now_microsec();
	if (microsec_now - start_eating >= info.time_to_die)
	{
		*ph.count_eat = -1;
		msg.msg = DIE;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	else
	{
		msg.msg = EAT;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	//if (info.time_to_die <= info.time_to_eat) //이렇게 설계하지 말고, usleep을 짧고, 많이 하여 해결하자.
	//	usleep(info.time_to_die);
	//else
	//	usleep(info.time_to_eat);
	while (1)
	{
		microsec_now = ft_now_microsec();
		if (microsec_now - start_eating >= info.time_to_eat)
			break;
		usleep(50);
	}
	if (ph.ph_name % 2 == 0)
	{
		*ph.left_f = FALSE;
		*ph.right_f = FALSE;
		pthread_mutex_unlock(ph.left_fork);
		pthread_mutex_unlock(ph.right_fork);
	}
	else
	{	*ph.left_f = FALSE;
		*ph.right_f = FALSE;
		pthread_mutex_unlock(ph.right_fork);
		pthread_mutex_unlock(ph.left_fork);
	}
	//sleeping or dying printing
	microsec_now = ft_now_microsec();
	if (microsec_now - start_eating >= info.time_to_die)
	{
		*ph.count_eat = -1;
		msg.msg = DIE;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	else
	{
		msg.msg = SLEEP;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	//sleeping
	//start_sleeping = ft_now_microsec();
	//if (info.time_to_die - info.time_to_eat <= info.time_to_sleep)
	//	usleep(info.time_to_die - info.time_to_eat);
	//else
	//	usleep(info.time_to_sleep);

	while (1)
	{
		microsec_now = ft_now_microsec();
		if (microsec_now - start_eating >= info.time_to_sleep + info.time_to_eat)
			break;
		usleep(50);
	}
	//thinking printing
	//start_thinking = ft_now_microsec();
	microsec_now = ft_now_microsec();
	if (microsec_now - start_eating >= info.time_to_die)
	{
		
		*ph.count_eat = -1;
		msg.msg = DIE;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	else
	{
		msg.msg = THINK;
		msg.time = (microsec_now - start_time) / THOUSAND;
		if (_msg_philo(ph.print, &msg))
			return (NULL);
	}
	}
}
