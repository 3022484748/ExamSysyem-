#include"structure.h"

STUAnswer* s_head = NULL;
STUAnswer* s_tail = NULL;

void Start_exam() 
{
    Question* p = head;

    if (head == NULL) 
    {
        printf("���Ϊ�գ��޷���ʼ���ԣ�\n");
        return;
    }
    int a = TIME_LIMIT;

    time_t start_time, current_time,time_limit = TIME_LIMIT;//����ʱ������
    printf("��������ʱ�乲Ϊ %d ��\n",a);
    printf("�밴ʱ��ɿ���\n");
    Sleep(5000);
    printf("���Լ�����ʼ����\n");
    printf("��ע���ʱ��!\n");
    Sleep(8000);
    CLEAR_SCREEN();
    start_time = time(NULL);
    char timecpy_str[64];
    strcpy(timecpy_str , display_end_time());
    while (p != NULL) 
    {
        current_time = time(NULL);
        display_current_time();
        printf("\n");
        printf("����ʱ����: %s\n", timecpy_str);
            // ����Ƿ�ʱ
        if (difftime(current_time, start_time) > time_limit)
        {
            printf("\nʱ���ѵ������Խ�����\n");
            return;
        }


        printf("*******************************************\n");
        printf("����: %s", p->type);
        printf("��Ŀ %d:\n %s\n", p->id, p->question);
        if(strcmp(p->type , "�ж���" != 0))printf("A: %s\nB: %s\nC: %s\nD: %s\n", p->option[0], p->option[1], p->option[2], p->option[3]);
        else printf("%s\n", p->option[0]);
        printf("*******************************************\n");

        STUAnswer* ANew = (STUAnswer*)malloc(sizeof(STUAnswer));
        if (ANew == NULL)
        {
            printf("�ڴ����ʧ�ܣ�\n");
            return;
        }

        if (strcmp(p->type, "�ж���" )!= 0)printf("�������ѡ��(���� back ������һ��): ");
        else printf("�������ѡ�� Y/N (���� back ������һ��): ");
        scanf("%s", ANew->answer); 

        if (strcmp(ANew->answer, "back") == 0) 
        {
            free(ANew);
            // �ص���һ����߼�
            Question* prev = NULL;
            for (Question* t = head; t != p; t = t->next) 
            {
                prev = t;
            }
            if (prev != NULL) 
            {
                p = prev;  // �ص���һ��
                CLEAR_SCREEN();
            }
            else 
            {
                printf("�Ѿ��ǵ�һ��,�޷����أ�\n");
                Sleep(1000);
                CLEAR_SCREEN();
            }
            continue;  // ��������ѭ��
        }

        ANew->id = p->id;
        ANew->next = NULL;

        if (s_head == NULL)
        {
            s_head = ANew;
            s_tail = ANew;
        }
        else 
        {
            s_tail->next = ANew;
            s_tail = ANew;
        }

        CLEAR_SCREEN();
        p = p->next;
    }
    printf("��Ŀ��ȫ����ɣ�\n");
    Sleep(1000);
}
