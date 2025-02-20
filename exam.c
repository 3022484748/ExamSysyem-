#include"structure.h"


Question* head = NULL;
Question* tail = NULL;
int ID = 0;

// 创建原始题目
void initquestion()
{
	while (1)
	{
		Question* ONew = (Question*)malloc(sizeof(Question));
		if (ONew == NULL) {
			printf("内存分配失败！\n");
			return;
		}

		printf("请输入题目类型:\n");
		printf("1.单选题\n");
		printf("2.多选题\n");
		printf("0.判断题\n");

		int a;
		while (1)
		{
			scanf("%d", &a);
			if (a == 1) {
				strcpy(ONew->type, "单选题");
				break;
			}
			else if (a == 2) {
				strcpy(ONew->type, "多选题");
				break;
			}
			else if (a == 0) {
				strcpy(ONew->type, "判断题");
				break;
			}
			else {
				printf("类型错误! 请重新输入正确的题目类型: ");
			}
		}

		printf("请输入题目(如果已经完成请输入 exit ):");
		clear_input_buffer();

		char input_buffer[256];
		fgets(input_buffer, sizeof(input_buffer), stdin);
		size_t len = strlen(input_buffer);
		if (len > 0 && input_buffer[len - 1] == '\n')
		{
			input_buffer[--len] = '\0'; // 去除换行符
		}

		strcpy(ONew->question, input_buffer);

		if (strcmp(ONew->question, "exit") == 0)
		{
			free(ONew);
			break;
		}

		ONew->id = ++ID;
		if (a != 0)
		{
			printf("请输入选项A的内容:");
			scanf("%s", ONew->option[0]);
			printf("请输入选项B的内容:");
			scanf("%s", ONew->option[1]);
			printf("请输入选项C的内容:");
			scanf("%s", ONew->option[2]);
			printf("请输入选项D的内容:");
			scanf("%s", ONew->option[3]);
		}
		
		if (a == 1 || a == 2)
		{
			printf("请输入正确的答案选项:");
			scanf("%s", ONew->answer);
		}
		else
		{
			printf("请输入正确的答案选项(Y/N):");
			scanf("%s", ONew->answer);
		}

		printf("请输入该题目的分值:");
		scanf("%d", &ONew->score);
		while (ONew->score < -999 || ONew->score > 1001) 
		{
			printf("分值无效！请输入有效的分值：");
			scanf("%d", &ONew->score);
		}
		

		if (head == NULL)
		{
			head = ONew;
			tail = ONew;
		}
		else
		{
			tail->next = ONew;
			tail = tail->next;
		}
		tail->next = NULL;
	}
}





// 添加新题目
void add_question()
{
	Question* New = (Question*)malloc(sizeof(Question));
	if (New == NULL) {
		printf("内存分配失败！\n");
		return;
	}
	New->id = ++ID;
	printf("请输入题目类型:\n");
	printf("1.单选题\n");
	printf("2.多选题\n");
	printf("0.判断题\n");

	int a;
	while (1) 
	{
		scanf("%d", &a);
		if (a == 1) {
			strcpy(New->type, "单选题");
			break;
		}
		else if (a == 2) {
			strcpy(New->type, "多选题");
			break;
		}
		else if (a == 0) {
			strcpy(New->type, "判断题");
			break;
		}
		else {
			printf("类型错误! 请重新输入正确的题目类型: ");
		}
	}

	printf("请输入题目:");
	clear_input_buffer();

	char input_buffer[256];
	fgets(input_buffer, sizeof(input_buffer), stdin);
	size_t len = strlen(input_buffer);

	if (len > 0 && input_buffer[len - 1] == '\n') 
	{
		input_buffer[--len] = '\0'; // 去除换行符
	}

	strcpy(New->question, input_buffer);

	if (a != 0)
	{
		printf("请输入选项A的内容:");
		scanf("%s", New->option[0]);
		printf("请输入选项B的内容:");
		scanf("%s", New->option[1]);
		printf("请输入选项C的内容:");
		scanf("%s", New->option[2]);
		printf("请输入选项D的内容:");
		scanf("%s", New->option[3]);
	}

	if (a == 1 || a == 2)
	{
		printf("请输入正确的答案选项:");
		scanf("%s", New->answer);
	}
	else
	{
		printf("请输入正确的答案选项(Y/N):");
		scanf("%s", New->answer);
	}

	printf("请输入该题目的分值:");
	scanf("%d", &New->score);

	New->next = NULL;

	if (head == NULL) 
	{
		head = New;
		tail = New;
	}
	else 
	{
		tail->next = New;
		tail = tail->next;
	}
	tail->next = NULL;
}


//删除题目
void delete_question(int number)
{
	Question* temp = head;
	Question* q = NULL;

	// 如果头节点就是要删除的节点
	if (temp != NULL && temp->id == number) {
		head = temp->next;
		free(temp);
		save_question("Questions.txt");  // 更新文件
		CLEAR_SCREEN();
		printf("题目 %d 已删除\n", number);
		return;
	}

	// 查找要删除的节点
	while (temp != NULL && temp->id != number) {
		q = temp;
		temp = temp->next;
	}

	// 如果链表中没有该元素
	if (temp == NULL) {
		CLEAR_SCREEN();
		printf("题目 %d 不存在\n", number);
		return;
	}

	// 删除目标节点
	q->next = temp->next;
	free(temp);

	// 更新文件内容
	save_question("Questions.txt");

	CLEAR_SCREEN();
	printf("题目 %d 已删除\n", number);
}



void read_question()
{

	for (Question *p = head; p != NULL; p = p->next)
	{
		if (strcmp(p->type, "判断题" )!= 0)
		{
			printf("*******************************************\n");
			printf("类型:%s\n题目%d:\n%s\nA:%s\nB:%s\nC:%s\nD:%s\n正确选项:%s\n分值:%d\n", p->type, p->id, p->question, p->option[0], p->option[1], p->option[2], p->option[3], p->answer, p->score);
			printf("*******************************************\n");
		}
		else
		{
			printf("*******************************************\n");
			printf("类型:%s\n题目%d:\n%s\n正确选项:%s\n分值:%d\n", p->type, p->id, p->question, p->answer,p->score);
			printf("*******************************************\n");
		}
	}
}
