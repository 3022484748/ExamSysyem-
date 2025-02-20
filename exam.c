#include"structure.h"


Question* head = NULL;
Question* tail = NULL;
int ID = 0;

// ����ԭʼ��Ŀ
void initquestion()
{
	while (1)
	{
		Question* ONew = (Question*)malloc(sizeof(Question));
		if (ONew == NULL) {
			printf("�ڴ����ʧ�ܣ�\n");
			return;
		}

		printf("��������Ŀ����:\n");
		printf("1.��ѡ��\n");
		printf("2.��ѡ��\n");
		printf("0.�ж���\n");

		int a;
		while (1)
		{
			scanf("%d", &a);
			if (a == 1) {
				strcpy(ONew->type, "��ѡ��");
				break;
			}
			else if (a == 2) {
				strcpy(ONew->type, "��ѡ��");
				break;
			}
			else if (a == 0) {
				strcpy(ONew->type, "�ж���");
				break;
			}
			else {
				printf("���ʹ���! ������������ȷ����Ŀ����: ");
			}
		}

		printf("��������Ŀ(����Ѿ���������� exit ):");
		clear_input_buffer();

		char input_buffer[256];
		fgets(input_buffer, sizeof(input_buffer), stdin);
		size_t len = strlen(input_buffer);
		if (len > 0 && input_buffer[len - 1] == '\n')
		{
			input_buffer[--len] = '\0'; // ȥ�����з�
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
			printf("������ѡ��A������:");
			scanf("%s", ONew->option[0]);
			printf("������ѡ��B������:");
			scanf("%s", ONew->option[1]);
			printf("������ѡ��C������:");
			scanf("%s", ONew->option[2]);
			printf("������ѡ��D������:");
			scanf("%s", ONew->option[3]);
		}
		
		if (a == 1 || a == 2)
		{
			printf("��������ȷ�Ĵ�ѡ��:");
			scanf("%s", ONew->answer);
		}
		else
		{
			printf("��������ȷ�Ĵ�ѡ��(Y/N):");
			scanf("%s", ONew->answer);
		}

		printf("���������Ŀ�ķ�ֵ:");
		scanf("%d", &ONew->score);
		while (ONew->score < -999 || ONew->score > 1001) 
		{
			printf("��ֵ��Ч����������Ч�ķ�ֵ��");
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





// �������Ŀ
void add_question()
{
	Question* New = (Question*)malloc(sizeof(Question));
	if (New == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		return;
	}
	New->id = ++ID;
	printf("��������Ŀ����:\n");
	printf("1.��ѡ��\n");
	printf("2.��ѡ��\n");
	printf("0.�ж���\n");

	int a;
	while (1) 
	{
		scanf("%d", &a);
		if (a == 1) {
			strcpy(New->type, "��ѡ��");
			break;
		}
		else if (a == 2) {
			strcpy(New->type, "��ѡ��");
			break;
		}
		else if (a == 0) {
			strcpy(New->type, "�ж���");
			break;
		}
		else {
			printf("���ʹ���! ������������ȷ����Ŀ����: ");
		}
	}

	printf("��������Ŀ:");
	clear_input_buffer();

	char input_buffer[256];
	fgets(input_buffer, sizeof(input_buffer), stdin);
	size_t len = strlen(input_buffer);

	if (len > 0 && input_buffer[len - 1] == '\n') 
	{
		input_buffer[--len] = '\0'; // ȥ�����з�
	}

	strcpy(New->question, input_buffer);

	if (a != 0)
	{
		printf("������ѡ��A������:");
		scanf("%s", New->option[0]);
		printf("������ѡ��B������:");
		scanf("%s", New->option[1]);
		printf("������ѡ��C������:");
		scanf("%s", New->option[2]);
		printf("������ѡ��D������:");
		scanf("%s", New->option[3]);
	}

	if (a == 1 || a == 2)
	{
		printf("��������ȷ�Ĵ�ѡ��:");
		scanf("%s", New->answer);
	}
	else
	{
		printf("��������ȷ�Ĵ�ѡ��(Y/N):");
		scanf("%s", New->answer);
	}

	printf("���������Ŀ�ķ�ֵ:");
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


//ɾ����Ŀ
void delete_question(int number)
{
	Question* temp = head;
	Question* q = NULL;

	// ���ͷ�ڵ����Ҫɾ���Ľڵ�
	if (temp != NULL && temp->id == number) {
		head = temp->next;
		free(temp);
		save_question("Questions.txt");  // �����ļ�
		CLEAR_SCREEN();
		printf("��Ŀ %d ��ɾ��\n", number);
		return;
	}

	// ����Ҫɾ���Ľڵ�
	while (temp != NULL && temp->id != number) {
		q = temp;
		temp = temp->next;
	}

	// ���������û�и�Ԫ��
	if (temp == NULL) {
		CLEAR_SCREEN();
		printf("��Ŀ %d ������\n", number);
		return;
	}

	// ɾ��Ŀ��ڵ�
	q->next = temp->next;
	free(temp);

	// �����ļ�����
	save_question("Questions.txt");

	CLEAR_SCREEN();
	printf("��Ŀ %d ��ɾ��\n", number);
}



void read_question()
{

	for (Question *p = head; p != NULL; p = p->next)
	{
		if (strcmp(p->type, "�ж���" )!= 0)
		{
			printf("*******************************************\n");
			printf("����:%s\n��Ŀ%d:\n%s\nA:%s\nB:%s\nC:%s\nD:%s\n��ȷѡ��:%s\n��ֵ:%d\n", p->type, p->id, p->question, p->option[0], p->option[1], p->option[2], p->option[3], p->answer, p->score);
			printf("*******************************************\n");
		}
		else
		{
			printf("*******************************************\n");
			printf("����:%s\n��Ŀ%d:\n%s\n��ȷѡ��:%s\n��ֵ:%d\n", p->type, p->id, p->question, p->answer,p->score);
			printf("*******************************************\n");
		}
	}
}
