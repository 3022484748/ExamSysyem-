#include"structure.h"


int Get_grade()
{
	Question* G_head = head;
	Question* G_tail = NULL;
	int grade = 0;
	for (STUAnswer* p = s_head; p != NULL; p = p->next)
	{
		if (strcmp(p->answer, G_head->answer) == 0)
		{
			grade += G_head->score;
		}
		G_head = G_head->next;
	}

	return grade;
}

void show_analysis()
{
	STUAnswer* ss_head = s_head;
	STUAnswer* ss_tail = s_tail;
	STUAnswer* q = ss_head;
	for (Question* p = head; p != NULL; p = p->next)
	{
		if (strcmp(p->type, "�ж���" != 0))
		{
			printf("*******************************************\n");
			printf("����:%s\n��Ŀ%d:\n%s\nA:%s\nB:%s\nC:%s\nD:%s\n��ȷѡ��:%s    ��Ĵ�:%s\n��ֵ:%d\n", p->type, p->id, p->question, p->option[0], p->option[1], p->option[2], p->option[3], p->answer, q->answer, p->score);
			printf("*******************************************\n");
		}
		else
		{
			printf("*******************************************\n");
			printf("����:%s\n��Ŀ%d:\n%s\n��ȷѡ��:%s    ��Ĵ�:%s\n��ֵ:%d\n", p->type, p->id, p->question, p->answer, q->answer, p->score);
			printf("*******************************************\n");
		}
		q = q->next;
	}
}