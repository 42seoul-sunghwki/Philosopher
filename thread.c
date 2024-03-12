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
	if (ret || *(ph->flag) == DIE)
	{
		printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
		pthread_mutex_unlock(ph->print);
		return (FUN_FAIL);
	}
	if (msg->flag == EAT)
	{
		*(ph->count_eat) = *(ph->count_eat) + 1; //refactoring required
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
	t_msg	msg;

	msg.flag = flag;
	msg.ph = ph->ph_name;
	msg.print = ph->print;
	msg.time = (ft_now_microsec() - *(ph->start_time)) / THOUSAND;
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

int		lock_fork(pthread_mutex_t *fork, long *flag, int fork_flag)
{
	int	ret;

	ret = FUN_SUC;
	ret = pthread_mutex_lock(fork);
	*flag = fork_flag;
	ret = pthread_mutex_unlock(fork);
	return (ret);
}

int		odd_philo(t_thread *ph, long start_eating)
{
	long	microsec_now;

	while (1)
	{
		if (*ph->left_f == FALSE)
		{
			lock_fork(ph->left_fork, ph->left_f, TRUE);
			if (*ph->right_f == FALSE)
			{
				lock_fork(ph->right_fork, ph->right_f, TRUE);
				break ;
			}
			else
				lock_fork(ph->left_fork, ph->left_f, FALSE);
		}
		microsec_now = ft_now_microsec();
		if (check_status(ph, microsec_now - start_eating, ph->info.time_to_die, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

int	even_philo(t_thread *ph, long start_eating)
{
	long	microsec_now;

	while (1)
	{
		if (*ph->right_f == FALSE)
		{
			lock_fork(ph->right_fork, ph->right_f, TRUE);
			if (*ph->left_f == FALSE)
			{
				lock_fork(ph->left_fork, ph->left_f, TRUE);
				break ;
			}
			else
				lock_fork(ph->right_fork, ph->right_f, FALSE);
		}
		microsec_now = ft_now_microsec();
		if (check_status(ph, microsec_now - start_eating, ph->info.time_to_die, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

void	*philo(void *input)
{
	t_thread	ph;
	long	microsec_now;
	long	start_eating; //millisecond

	ph = *(t_thread *)input;
	if (ph.ph_name % 2 == 0)
		usleep(200);
	start_eating = ft_now_microsec();

	//start
	while (1)
	{
		if (ph.ph_name % 2 == 0)
		{
			if (even_philo(&ph, start_eating) == FUN_FAIL)
				return (NULL);
		}
		else
		{
			if (odd_philo(&ph, start_eating) == FUN_FAIL)
				return (NULL);
		}
		start_eating = ft_now_microsec();
		microsec_now = ft_now_microsec();
		if (check_status(&ph, microsec_now - start_eating, ph.info.time_to_die, EAT) == FUN_FAIL)
			return (NULL);
		while (1) //중복
		{
			microsec_now = ft_now_microsec();
			if (microsec_now - start_eating >= ph.info.time_to_eat || microsec_now - start_eating >= ph.info.time_to_die || *(ph.flag) == DIE)
				break;
			if (ph.info.time_to_eat - (microsec_now - start_eating) >= THOUSAND)
			{
				usleep(THOUSAND);
			}
			else
				usleep(100);
		}
		lock_fork(ph.left_fork, ph.left_f, FALSE);
		lock_fork(ph.right_fork, ph.right_f, FALSE);
		if (check_status(&ph, microsec_now - start_eating, ph.info.time_to_die, SLEEP) == FUN_FAIL)
			return (NULL);
		while (1)
		{
			microsec_now = ft_now_microsec();
			if (microsec_now - start_eating >= ph.info.time_to_sleep + ph.info.time_to_eat || microsec_now - start_eating >= ph.info.time_to_die || *(ph.flag) == DIE)
				break;
			if (ph.info.time_to_sleep + ph.info.time_to_eat - (microsec_now - start_eating) >= THOUSAND)
			{
				//usleep((ph.info.time_to_sleep + ph.info.time_to_eat - (microsec_now - start_eating)) / 2);
				usleep(THOUSAND);
			}
			else
				usleep(100);
		}
		microsec_now = ft_now_microsec();
		if (check_status(&ph, microsec_now - start_eating, ph.info.time_to_die, THINK) == FUN_FAIL)
			return (NULL);
	}
}
