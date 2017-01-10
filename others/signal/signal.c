#include <signal.h>
#include <stdio.h>

static void __sigint(int sig)
{
	printf("sig num = %d\n",sig);	
}

static void __signals_init(void)
{
/*
 * signal�����ã��ᵼ�½����Զ��˳�
 * ������SIGTTOU,SIGTTIN,SIGTSTP�󣬴����˽����Զ��˳���BUG
 */
	struct sigaction sa;


	sa.sa_flags = 0;
	sigaddset(&sa.sa_mask, SIGPIPE);
    sigaddset(&sa.sa_mask, SIGCHLD); 
   	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGHUP);
	sigaddset(&sa.sa_mask, SIGTERM); 
	sigaddset(&sa.sa_mask, SIGTTOU);
	sigaddset(&sa.sa_mask, SIGTTIN);
	sigaddset(&sa.sa_mask, SIGTSTP);
#if 0
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGCHLD, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGHUP, &sa, NULL);

	sa.sa_handler = __sigint;
	sigaction(SIGTERM, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGTTIN, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa, NULL);
#endif
	sa.sa_handler = __sigint;
	sigaction(SIGINT, &sa, NULL);
}

int main(void)
{
	__signals_init();

	while(1);
	
	return 0;
}

