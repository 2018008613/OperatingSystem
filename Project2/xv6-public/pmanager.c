#include "types.h"
#include "user.h"
#include "fcntl.h"

int run_pmanager()
{
	printf(2, ">> ");
	static char buf[100];
	char p[15];
	gets(buf, 100);
	int i;
	for (i = 0;i < 100;i++)
	{
		if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
		{
			p[i] = '\0';
			break;
		}
		p[i] = buf[i];
	}
	int n = i + 1;
	i++;
	if (!strcmp(p, "list"))
	{
		getlist();
	}
	else if (!strcmp(p, "kill"))
	{
		int pid;
		char ch_pid[15];
		for (;i < 100;i++)
		{
			if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
			{
				ch_pid[i - n] = '\0';
				break;
			}
			ch_pid[i - n] = buf[i];
		}
		pid = atoi(ch_pid);
		if (kill(pid))
			printf(2, "kill %d failed\n", pid);
		else
			printf(2, "kill %d success\n", pid);
	}
	else if (!strcmp(p, "execute"))
	{
		char path[60];
		char* argv[10];
		int stacksize;
		char ch_stacksize[15];
		for (;i < 100;i++)
		{
			if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
			{
				path[i - n] = '\0';
				break;
			}
			path[i - n] = buf[i];
		}
		n = i + 1;
		i++;
		for (;i < 100;i++)
		{
			if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
			{
				ch_stacksize[i - n] = '\0';
				break;
			}
			ch_stacksize[i - n] = buf[i];
		}
		stacksize = atoi(ch_stacksize);
		strcpy(argv[0], path);
		argv[1] = 0;
		int chk_pid = fork();
		if (chk_pid == 0)
		{
			if (exec2(path, argv, stacksize) == -1)
				printf(2, "exec failed\n");
			return 1;
		}

	}
	else if (!strcmp(p, "memlim"))
	{
		int pid, limit;
		char ch_pid[15], ch_limit[15];
		for (;i < 100;i++)
		{
			if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
			{
				ch_pid[i - n] = '\0';
				break;
			}
			ch_pid[i - n] = buf[i];
		}
		n = i + 1;
		i++;
		for (;i < 100;i++)
		{
			if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
			{
				ch_limit[i - n] = '\0';
				break;
			}
			ch_limit[i - n] = buf[i];
		}
		pid = atoi(ch_pid);
		limit = atoi(ch_limit);
		if (setmemorylimit(pid, limit))
			printf(2, "memlim failed\n");
		else
			printf(2, "memlim success\n");
	}
	else if (!strcmp(p, "exit"))
	{
		printf(2, "exit the program...\n");
		return 1;
	}
	else
	{
		printf(2, "invalid input!\n");
	}
	return 0;
}

int main()
{

	char ch[15];
	printf(2, "학번을 입력하세요 : ");
	gets(ch, 15);
	for (int i = 0;i < 15;i++)
	{
		if (ch[i] == '\n')
		{
			ch[i] = '\0';
			break;
		}
	}
	if (getadmin(ch) == -1)
	{
		printf(2, "잘못된 학번입니다.\n");
		return -1;
	}
	printf(2, "올바른 학번입니다. 관리자 권한을 획득했습니다.\n");
	while (1)
	{
		if (run_pmanager())
			break;

	}
	return 0;
}




