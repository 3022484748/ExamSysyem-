#include "structure.h"

// ��������

void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // ��ջ�����ֱ���������з����ļ�������
}



User users[3] = {
    {"root", "root123", 0}, // �������ϵĹ���Ա
    {"admin", "admin123", 1 }, // ����Ա
    {"student", "student123", 2} // ѧ��
};


int Login(const char* name, const char* password)
{
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(users[i].name, name) == 0 && strcmp(users[i].password, password) == 0) 
        {
            return users[i].charactor;  // �ҵ�ƥ����û������ؽ�ɫ
        }
    }
    return -1;
}





void show_menu_xiaoju() 
{
    printf("========== ����ϵͳ�˵� ==========\n");
    printf("=== 1. ������Ŀ ===\n");
    printf("=== 2. �鿴��Ŀ ===\n");
    printf("=== 3. �����Ŀ ===\n");
    printf("=== 4. ɾ����Ŀ ===\n");
    printf("=== 5. ��ʼ���� ===\n");
    printf("=== 6. ��ѯ�ɼ� ===\n");
    printf("=== 9. ע���˺� ===\n");
    printf("=== 0. �˳� ===\n");
    printf("��������ѡ����~ ");
}

void show_menu_admin() 
{
    printf("========== ����ϵͳ�˵� ==========\n");
    printf("=== 1. ������Ŀ ===\n");
    printf("=== 2. �鿴��Ŀ ===\n");
    printf("=== 3. �����Ŀ ===\n");
    printf("=== 4. ɾ����Ŀ ===\n");
    printf("=== 9. ע���˺� ===\n");
    printf("=== 0. �˳� ===\n");
    printf("���������ѡ��: ");
}

void show_menu_student_start() 
{
    printf("========== ����ϵͳ�˵� ==========\n");
    printf("=== 1. ��ʼ���� ===\n");
    printf("=== 9. ע���˺� ===\n");
    printf("=== 0. �˳� ===\n");
    printf("���������ѡ��: ");
}
void show_menu_student_end()
{
    printf("========== ����ϵͳ�˵� ==========\n");
    printf("=== 1. ��ѯ�ɼ� ===\n");
    printf("=== 9. ע���˺� ===\n");
    printf("=== 0. �˳� ===\n");
    printf("���������ѡ��: ");
}


void save_question(const char* filename) 
{
    FILE* file = fopen(filename, "w");  // ���ļ�������ļ��������򴴽�
    if (file == NULL) 
    {
        printf("�޷����ļ�����д�룡\n");
        return;
    }

    Question* p = head;  // �������ͷ��ʼ����
    while (p != NULL) 
    {
        // �����ض���ʽд���ļ���ʹ��"|"�ָ������ֶ�
        fprintf(file, "%s|%d|%s|%s|%s|%s|%s|%s|%d\n", p->type,p->id, p->question,
            p->option[0], p->option[1], p->option[2], p->option[3],
            p->answer, p->score);
        p = p->next;  // �ƶ�����һ���ڵ�
    }

    fclose(file);  // �ر��ļ�
    printf("��Ŀ�ѳɹ����浽�ļ��У�\n");
}

void load_question(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s��\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Question* new_question = (Question*)malloc(sizeof(Question));
        if (new_question == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            fclose(file);
            return;
        }

        // ��ʼ���ڵ�
        new_question->next = NULL;

        // �Ƚ�����Ŀ����
        int result = sscanf(line, "%255[^|]|%d|%255[^|]|", new_question->type, &new_question->id, new_question->question);
        if (result < 3) {
            printf("�ļ���ʽ���������У�%s\n", line);
            free(new_question);
            continue;
        }

        // ����ǡ��ж��⡱��ֻ����һ����
        if (strcmp(new_question->type, "�ж���") == 0) {
            // ֻ�����ж���Ĵ𰸺ͷ���
            result = sscanf(line, "%255[^|]|%d|%255[^|]|%9[^|]|%d", new_question->type, &new_question->id, new_question->question, new_question->answer, &new_question->score);
            if (result != 5) {
                printf("�ļ���ʽ���������У�%s\n", line);
                free(new_question);
                continue;
            }
            // �����ж��⣬���ѡ������
            for (int i = 0; i < 4; i++) {
                strcpy(new_question->option[i], "��");
            }
        }
        else {
            // ������ǡ��ж��⡱������ѡ��𰸺ͷ���
            result = sscanf(line, "%255[^|]|%d|%255[^|]|%255[^|]|%255[^|]|%255[^|]|%255[^|]|%d", new_question->type, &new_question->id, new_question->question,
                new_question->option[0], new_question->option[1], new_question->option[2], new_question->option[3],
                new_question->answer, &new_question->score);
            if (result != 9) {
                printf("�ļ���ʽ���������У�%s\n", line);
                free(new_question);
                continue;
            }
        }

        // ��ӡ������Ϣ�����������
        printf("�����ɹ���ID=%d ����=%s ��Ŀ=%s\n", new_question->id, new_question->type, new_question->question);

        // ��ӵ�����
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
    printf("��Ŀ�ѳɹ����أ�\n");
}
