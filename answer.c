#include"structure.h"

STUAnswer* s_head = NULL;
STUAnswer* s_tail = NULL;

void Start_exam() 
{
    Question* p = head;

    if (head == NULL) 
    {
        printf("题库为空，无法开始考试！\n");
        return;
    }
    int a = TIME_LIMIT;

    time_t start_time, current_time,time_limit = TIME_LIMIT;//设置时间限制
    printf("本次作答时间共为 %d 秒\n",a);
    printf("请按时完成考试\n");
    Sleep(5000);
    printf("考试即将开始……\n");
    printf("请注意好时间!\n");
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
        printf("结束时间是: %s\n", timecpy_str);
            // 检查是否超时
        if (difftime(current_time, start_time) > time_limit)
        {
            printf("\n时间已到！考试结束。\n");
            return;
        }


        printf("*******************************************\n");
        printf("类型: %s", p->type);
        printf("题目 %d:\n %s\n", p->id, p->question);
        if(strcmp(p->type , "判断题" != 0))printf("A: %s\nB: %s\nC: %s\nD: %s\n", p->option[0], p->option[1], p->option[2], p->option[3]);
        else printf("%s\n", p->option[0]);
        printf("*******************************************\n");

        STUAnswer* ANew = (STUAnswer*)malloc(sizeof(STUAnswer));
        if (ANew == NULL)
        {
            printf("内存分配失败！\n");
            return;
        }

        if (strcmp(p->type, "判断题" )!= 0)printf("请输入答案选项(输入 back 返回上一题): ");
        else printf("请输入答案选项 Y/N (输入 back 返回上一题): ");
        scanf("%s", ANew->answer); 

        if (strcmp(ANew->answer, "back") == 0) 
        {
            free(ANew);
            // 回到上一题的逻辑
            Question* prev = NULL;
            for (Question* t = head; t != p; t = t->next) 
            {
                prev = t;
            }
            if (prev != NULL) 
            {
                p = prev;  // 回到上一题
                CLEAR_SCREEN();
            }
            else 
            {
                printf("已经是第一题,无法返回！\n");
                Sleep(1000);
                CLEAR_SCREEN();
            }
            continue;  // 跳过本次循环
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
    printf("题目已全部完成！\n");
    Sleep(1000);
}
