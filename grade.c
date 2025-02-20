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
		if (strcmp(p->type, "判断题" != 0))
		{
			printf("*******************************************\n");
			printf("类型:%s\n题目%d:\n%s\nA:%s\nB:%s\nC:%s\nD:%s\n正确选项:%s    你的答案:%s\n分值:%d\n", p->type, p->id, p->question, p->option[0], p->option[1], p->option[2], p->option[3], p->answer, q->answer, p->score);
			printf("*******************************************\n");
		}
		else
		{
			printf("*******************************************\n");
			printf("类型:%s\n题目%d:\n%s\n正确选项:%s    你的答案:%s\n分值:%d\n", p->type, p->id, p->question, p->answer, q->answer, p->score);
			printf("*******************************************\n");
		}
		q = q->next;
	}
}