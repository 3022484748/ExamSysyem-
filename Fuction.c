#include "structure.h"

// 函数定义

void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // 清空缓冲区直到遇到换行符或文件结束符
}



User users[3] = {
    {"root", "root123", 0}, // 至高无上的管理员
    {"admin", "admin123", 1 }, // 管理员
    {"student", "student123", 2} // 学生
};


int Login(const char* name, const char* password)
{
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(users[i].name, name) == 0 && strcmp(users[i].password, password) == 0) 
        {
            return users[i].charactor;  // 找到匹配的用户，返回角色
        }
    }
    return -1;
}





void show_menu_xiaoju() 
{
    printf("========== 考试系统菜单 ==========\n");
    printf("=== 1. 创建题目 ===\n");
    printf("=== 2. 查看题目 ===\n");
    printf("=== 3. 添加题目 ===\n");
    printf("=== 4. 删除题目 ===\n");
    printf("=== 5. 开始考试 ===\n");
    printf("=== 6. 查询成绩 ===\n");
    printf("=== 9. 注销账号 ===\n");
    printf("=== 0. 退出 ===\n");
    printf("主人您的选择是~ ");
}

void show_menu_admin() 
{
    printf("========== 考试系统菜单 ==========\n");
    printf("=== 1. 创建题目 ===\n");
    printf("=== 2. 查看题目 ===\n");
    printf("=== 3. 添加题目 ===\n");
    printf("=== 4. 删除题目 ===\n");
    printf("=== 9. 注销账号 ===\n");
    printf("=== 0. 退出 ===\n");
    printf("请输入你的选择: ");
}

void show_menu_student_start() 
{
    printf("========== 考试系统菜单 ==========\n");
    printf("=== 1. 开始考试 ===\n");
    printf("=== 9. 注销账号 ===\n");
    printf("=== 0. 退出 ===\n");
    printf("请输入你的选择: ");
}
void show_menu_student_end()
{
    printf("========== 考试系统菜单 ==========\n");
    printf("=== 1. 查询成绩 ===\n");
    printf("=== 9. 注销账号 ===\n");
    printf("=== 0. 退出 ===\n");
    printf("请输入你的选择: ");
}


void save_question(const char* filename) 
{
    FILE* file = fopen(filename, "w");  // 打开文件，如果文件不存在则创建
    if (file == NULL) 
    {
        printf("无法打开文件进行写入！\n");
        return;
    }

    Question* p = head;  // 从链表的头开始遍历
    while (p != NULL) 
    {
        // 按照特定格式写入文件，使用"|"分隔各个字段
        fprintf(file, "%s|%d|%s|%s|%s|%s|%s|%s|%d\n", p->type,p->id, p->question,
            p->option[0], p->option[1], p->option[2], p->option[3],
            p->answer, p->score);
        p = p->next;  // 移动到下一个节点
    }

    fclose(file);  // 关闭文件
    printf("题目已成功保存到文件中！\n");
}

void load_question(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s！\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Question* new_question = (Question*)malloc(sizeof(Question));
        if (new_question == NULL) {
            printf("内存分配失败！\n");
            fclose(file);
            return;
        }

        // 初始化节点
        new_question->next = NULL;

        // 先解析题目类型
        int result = sscanf(line, "%255[^|]|%d|%255[^|]|", new_question->type, &new_question->id, new_question->question);
        if (result < 3) {
            printf("文件格式错误，跳过行：%s\n", line);
            free(new_question);
            continue;
        }

        // 如果是“判断题”，只解析一部分
        if (strcmp(new_question->type, "判断题") == 0) {
            // 只解析判断题的答案和分数
            result = sscanf(line, "%255[^|]|%d|%255[^|]|%9[^|]|%d", new_question->type, &new_question->id, new_question->question, new_question->answer, &new_question->score);
            if (result != 5) {
                printf("文件格式错误，跳过行：%s\n", line);
                free(new_question);
                continue;
            }
            // 对于判断题，清空选项内容
            for (int i = 0; i < 4; i++) {
                strcpy(new_question->option[i], "无");
            }
        }
        else {
            // 如果不是“判断题”，解析选项、答案和分数
            result = sscanf(line, "%255[^|]|%d|%255[^|]|%255[^|]|%255[^|]|%255[^|]|%255[^|]|%d", new_question->type, &new_question->id, new_question->question,
                new_question->option[0], new_question->option[1], new_question->option[2], new_question->option[3],
                new_question->answer, &new_question->score);
            if (result != 9) {
                printf("文件格式错误，跳过行：%s\n", line);
                free(new_question);
                continue;
            }
        }

        // 打印调试信息，检查解析结果
        printf("解析成功：ID=%d 类型=%s 题目=%s\n", new_question->id, new_question->type, new_question->question);

        // 添加到链表
        if (head == NULL) {
            head = new_question;
            tail = new_question;
        }
        else {
            tail->next = new_question;
            tail = new_question;
        }
    }

    fclose(file);
    printf("题目已成功加载！\n");
}
