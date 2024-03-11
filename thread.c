	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/11 19:10:17 by sunghwki         ###   ########.fr       */
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

int	_msg_philo(t_thread *ph, t_msg *msg)
{
	int	ret;
	int	die;

	ret = pthread_mutex_lock(ph->print);
	die = DIE;
	if (ph->info.num_must_eat && *(ph->count_eat) > ph->info.num_must_eat)
	{
		pthread_mutex_unlock(ph->print);
		return (FUN_FAIL);
	}
	if (ret || *(ph->flag) == DIE)
	{
		printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
		pthread_mutex_unlock(ph->print);
		return (FUN_FAIL);
	}
	if (msg->flag == EAT)
	{
		*(ph->count_eat) = *(ph->count_eat) + 1;
		if (ph->info.num_must_eat && *(ph->count_eat) > ph->info.num_must_eat)
		{
			*(ph->flag) = die;
			printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
			pthread_mutex_unlock(ph->print);
			return (FUN_FAIL);
		}
	}
	printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
	ret = pthread_mutex_unlock(ph->print);
	return (ret);
}

int		check_status(t_thread *ph, long base_time, long cmp_time, int flag)
{
	int		die;
	t_msg	msg;

	msg.flag = flag;
	msg.ph = ph->ph_name;
	msg.print = ph->print;
	msg.time = (ft_now_microsec() - *(ph->start_time)) / THOUSAND;
	die = DIE;
	if (flag == SLEEP)
		msg.msg = SLEEP_MSG;
	else if (flag == EAT)
		msg.msg = EAT_MSG;
	else if (flag == THINK)
		msg.msg = THINK_MSG;
	if (base_time <= cmp_time)
	{
		if (flag != NOT_CHECK)
			return (_msg_philo(ph, &msg));
	}
	else
	{
		msg.msg = DIE_MSG;
		*(ph->flag) = DIE;
		return (_msg_philo(ph, &msg));
	}
	return (FUN_SUC);
}

void	*philo(void *input)
{
	t_thread	ph;
	t_info		info;
	t_msg		msg;
	int			die;
	long	microsec_now;
	long	start_eating; //millisecond

	ph = *(t_thread *)input;
	info = ph.info;
	die = DIE;
	msg.print = ph.print;
	msg.ph = ph.ph_name;
	if (ph.ph_name % 2 == 0)
		usleep(200);
	start_eating = ft_now_microsec();

	//start
	while (1)
	{
		if (ph.ph_name % 2 == 0)
		{
		while (1)
		{
			if (*ph.left_f == FALSE)
			{
				pthread_mutex_lock(ph.left_fork);
				*ph.left_f = TRUE;
				
				if (*ph.right_f == FALSE)
				{
					pthread_mutex_lock(ph.right_fork);
					*ph.right_f = TRUE;
					pthread_mutex_unlock(ph.right_fork);
					pthread_mutex_unlock(ph.left_fork);
					break;
				}
				else
				{
					*ph.left_f = FALSE;
					pthread_mutex_unlock(ph.left_fork);
				}
			}
			microsec_now = ft_now_microsec();
			if (check_status(&ph, microsec_now - start_eating, ph.info.time_to_die, NOT_CHECK) == FUN_FAIL)
				return (NULL);
			usleep(100);
		}
		}
		else
		{
			while (1)
			{
				if (*ph.right_f == FALSE)
				{
					pthread_mutex_lock(ph.right_fork);
					*ph.right_f = TRUE;
					
					if (*ph.left_f == FALSE)
					{
						pthread_mutex_lock(ph.left_fork);
						*ph.left_f = TRUE;
						pthread_mutex_unlock(ph.left_fork);
						pthread_mutex_unlock(ph.right_fork);
						break;
					}
					else
					{
						*ph.right_f = FALSE;
						pthread_mutex_unlock(ph.right_fork);
					}
				}
				if (check_status(&ph, microsec_now - start_eating, info.time_to_die, NOT_CHECK) == FUN_FAIL)
					return (NULL);
				usleep(100);
			}
		}

	start_eating = ft_now_microsec();
	microsec_now = ft_now_microsec();
	if (check_status(&ph, microsec_now - start_eating, info.time_to_die, EAT) == FUN_FAIL)
		return (NULL);
	while (1)
	{
		microsec_now = ft_now_microsec();
		if (microsec_now - start_eating >= info.time_to_eat || microsec_now - start_eating >= info.time_to_die)
			break;
		if (info.time_to_eat - (microsec_now - start_eating) >= THOUSAND)
		{
			usleep((info.time_to_eat - (microsec_now - start_eating)) / 2);
		}
		else
			usleep(50);
	}
	pthread_mutex_lock(ph.left_fork);
	pthread_mutex_lock(ph.right_fork);
	*ph.left_f = FALSE;
	*ph.right_f = FALSE;
	pthread_mutex_unlock(ph.left_fork);
	pthread_mutex_unlock(ph.right_fork);
	if (check_status(&ph, microsec_now - start_eating, info.time_to_die, SLEEP) == FUN_FAIL)
		return (NULL);
	while (1)
	{
		microsec_now = ft_now_microsec();
		if (microsec_now - start_eating >= info.time_to_sleep + info.time_to_eat || microsec_now - start_eating >= info.time_to_die)
			break;
		if (info.time_to_sleep + info.time_to_eat - (microsec_now - start_eating) >= THOUSAND)
		{
			usleep((info.time_to_sleep + info.time_to_eat - (microsec_now - start_eating)) / 2);
		}
		else
			usleep(10);
	}
	microsec_now = ft_now_microsec();
	if (check_status(&ph, microsec_now - start_eating, info.time_to_die, THINK) == FUN_FAIL)
		return (NULL);
	}
}
