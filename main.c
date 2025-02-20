/*考试系统
│
├── main.c           // 程序入口，菜单界面
├── answer.c           // 考试管理模块
├── exam.c          // 试卷管理模块
├── grade.c          // 成绩管理模块
├── time.c           // 时间管理模块
├── structure.h      // 数据结构定义
└── fuction.c          // 工具函数
*/

#include "structure.h"


int main()
{
/*******************************************************************************************************************
                                                         登录模块
*******************************************************************************************************************/

    char name[50], password[50];
LOGIN:    printf("请输入用户名: ");
    scanf("%s", name);
    printf("请输入密码: ");
    scanf("%s", password);

    int charactor = Login(name, password);
    if (charactor == -1)//用户名或密码错误
    {
        while (charactor == -1)
        {
            printf("用户名或密码错误!\n");
            printf("请输入用户名: ");
            scanf("%s", name);
            printf("请输入密码: ");
            scanf("%s", password);
            charactor = Login(name, password);
        }
    }


    if (charactor == 0)//至高无上的管理员
    {
        CLEAR_SCREEN();
        printf("欢迎root大人 mua mua mua!!!\n");
    }
    else if (charactor == 1)//普通管理员
    {
        CLEAR_SCREEN();
        printf("管理员 %s 登录成功!\n",name);
    }
    else//学生
    {
        CLEAR_SCREEN();
        printf("学生 %s 登录成功!\n",name);
    }


/*******************************************************************************************************************
                                                         界面模块
*******************************************************************************************************************/

    if (charactor == 0) //至高无上的管理员
    {
        load_question("Questions.txt");
        while (1)
        {
            show_menu_xiaoju();
            int choice;
            scanf("%d", &choice);
            while (choice < 0 || choice >= 10)
            {
                clear_input_buffer();
                printf("再输就要坏掉了哇\n");
                printf(" > < \n");
                show_menu_admin();
                scanf("%d", &choice);
                if (choice >= 0 && choice <= 10) break;
            }
            switch (choice)
            {
                case 1:
                {
                    if (!head)
                    {
                        CLEAR_SCREEN();
                        clear_input_buffer();
                        initquestion();
                        CLEAR_SCREEN();
                        printf("初始化成功!\n");
                        break;
                    }
                    else
                    {
                        CLEAR_SCREEN();
                        printf("题目已经存在,请查看题目或选择添加题目\n");
                        break;
                    }
                }

                case 2:
                {
                    CLEAR_SCREEN();
                    if (head) read_question();
                    else printf("你还没有输入题目\n");
                    break;
                }

                case 3:
                {
                    printf("是否需要添加问题?(Y/N)\n");
                    clear_input_buffer();

                    char s = getchar();
                    if (s == 'Y')
                    {
                        add_question();
                        printf("题目添加成功!\n");
                    }
                    break;
                }

                case 4:
                {
                    CLEAR_SCREEN();
                    read_question(head);
                    clear_input_buffer();
                    printf("请输入需要删除的题目:");
                    int s;
                    scanf("%d", &s);
                    if (s >= 0 && s <= 1000)
                    {
                        CLEAR_SCREEN();
                        delete_question(s);
                    }
                    break;
                }

                case 5:
                {
                    CLEAR_SCREEN();
                    Start_exam();
                    show_analysis();
                    break;
                }

                case 6:
                {
                    int grade;
                    CLEAR_SCREEN();
                    grade = Get_grade();
                    printf("你的成绩是:%d\n", grade);
                    break;
                }

                case 9:
                {
                    CLEAR_SCREEN();
                    goto LOGIN;
                }

                case 0:
                {
                    CLEAR_SCREEN();
                    save_question("Questions.txt");
                    printf("感谢使用本系统\n");
                    return 0;
                }
            }
        }
    }
    else if(charactor == 1) //管理员界面
    {
        load_question("Questions.txt");
        while (1)
        {
            show_menu_admin();
            int choice;
            scanf("%d", &choice);
            while(choice < 0 || choice >= 10)
            {
                clear_input_buffer();
                printf("你在输什么?\n");
                show_menu_admin();
                scanf("%d", &choice);
                if (choice >= 0 && choice <= 10) break;
            }
            switch (choice)
            {
                case 1:
                {
                    if (!head)
                    {
                        CLEAR_SCREEN();
                        clear_input_buffer();
                        initquestion();
                        CLEAR_SCREEN();
                        printf("初始化成功!\n");
                        break;
                    }
                    else
                    {
                        CLEAR_SCREEN();
                        printf("题目已经存在,请查看题目或选择添加题目\n");
                        break;
                    }
                }

                case 2:
                {
                    CLEAR_SCREEN();
                    if (head) read_question();
                    else printf("你还没有输入题目\n");
                    break;
                }

                case 3:
                {
                    printf("是否需要添加问题?(Y/N)\n");
                    clear_input_buffer();

                    char s = getchar();
                    if (s == 'Y')
                    {
                        add_question();
                        printf("题目添加成功!\n");
                    }
                    break;
                }

                case 4:
                {
                    CLEAR_SCREEN();
                    read_question(head);
                    clear_input_buffer();
                    printf("请输入需要删除的题目:");
                    int s;
                    scanf("%d", &s);
                    if (s >= 0 && s <= 1000)
                    {
                        CLEAR_SCREEN();
                        delete_question(s);
                    }
                    break;
                }

                case 9:
                {
                    CLEAR_SCREEN();
                    goto LOGIN;
                }

                case 0:
                {
                    CLEAR_SCREEN();
                    save_question("Questions.txt");
                    printf("感谢使用本系统\n");
                    return 0;
                }




            }
        }
    }
    else//学生界面
    {
        int StuANSFLAG = 0;
        load_question("Questions.txt");
        while (1)
        {
            if (StuANSFLAG == 0)//没答题前
            {
                StuANSFLAG = 1;
                show_menu_student_start();
                int choice;
                scanf("%d", &choice);
                while (choice < 0 || choice >= 10)
                {
                    clear_input_buffer();
                    printf("你在输什么?\n");
                    show_menu_student_start();
                    scanf("%d", &choice);
                    if (choice == 1 || choice == 0) break;
                }
                switch (choice)
                {
                    case 1:
                    {
                        CLEAR_SCREEN();
                        Start_exam();
                        show_analysis();
                        break;
                    }

                    case 9:
                    {
                        CLEAR_SCREEN();
                        goto LOGIN;
                    }

                    case 0:
                    {
                        CLEAR_SCREEN();
                        printf("感谢使用本系统！\n");
                        return 0;
                    }
                }
            }
            else//已经结束考试
            {
                show_menu_student_end();
                int choice;
                scanf("%d", &choice);
                while (choice < 0 || choice >= 10)
                {
                    clear_input_buffer();
                    printf("你在输什么?\n");
                    show_menu_student_end();
                    scanf("%d", &choice);
                    if (choice == 1 || choice == 0 || choice == 9) break;
                }
                switch (choice)
                {
                    case 1:
                    {
                        int grade;
                        CLEAR_SCREEN();
                        grade = Get_grade();
                        printf("你的成绩是:%d\n", grade);
                        break;
                    }

                    case 9:
                    {
                        goto LOGIN;
                    }

                    case 0:
                    {
                        CLEAR_SCREEN();
                        printf("感谢使用本系统！\n");
                        return 0;
                    }
                }
            }
        }
    }

    


    return 0;
}
