void
Pthread_mutex_lock(pthread_mutex_t *mptr)
{
	int	n;
	if((n = pthread_mutex_lock(mptr)) != 0)
		return;

	errno = n;
	printf("pthread_mutex_lock error.\n");
}
