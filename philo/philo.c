/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 19:05:00 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_thread *ph)
{
	int	i;

	i = ph[0].info.num_philo;
	pthread_mutex_destroy(ph[0].print);
	pthread_mutex_destroy(ph[0].count_mutex);
	pthread_mutex_destroy(ph[0].flag_mutex);
	free(ph[0].print);
	free(ph[0].count_mutex);
	free(ph[0].flag_mutex);
	free(ph[0].count_eat);
	free((void *)ph[0].flag);
	while (--i >= 0)
	{
		pthread_mutex_destroy(ph[i].left_fork);
		free(ph[i].left_fork);
		free(ph[i].left_f);
	}
}

t_thread	*init_thread(int argc, char **argv)
{
	t_thread		*ph;
	t_info			info;
	long			start_time;
	long			i;

	if (init_value(argc, argv, &info))
		return (NULL);
	i = 0;
	ph = (t_thread *)malloc((sizeof(t_thread) * info.num_philo));
	init_static_value(ph, info.num_philo);
	init_mutex_thread(ph, info.num_philo);
	start_time = ft_usec_now() + 10 * info.num_philo;
	while (i < info.num_philo)
	{
		ph[i].info = info;
		ph[i].start_time = start_time;
		ph[i].right_f = (long *)malloc(sizeof(long));
		ph[(i + 1) % info.num_philo].left_f = ph[i].right_f;
		if (i % 2 == 0)
			*(ph[i].right_f) = 0;
		else
			*(ph[i].right_f) = -1;
		i += 1;
	}
	return (ph);
}

void	thread_create(t_thread *ph, pthread_t **th_name)
{
	long	i;

	i = 0;
	while (i < ph[0].info.num_philo)
	{
		th_name[i] = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(th_name[i], NULL, philo, (void *)(&ph[i]));
		i++;
	}
	i = 0;
	while (i < ph[0].info.num_philo)
	{
		pthread_join(*th_name[i], NULL);
		free((void *)(*th_name[i]));
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t		**th_name;
	t_thread		*ph;

	ph = init_thread(argc, argv);
	if (ph == NULL)
		return (1);
	th_name = (pthread_t **)malloc(sizeof(pthread_t *) * ph[0].info.num_philo);
	thread_create(ph, th_name);
	free_thread(ph);
	free(ph);
	free(th_name);
	return (0);
}
