#include"structure.h"

void display_current_time() 
{
    // ��ȡ��ǰʱ���
    time_t raw_time = time(NULL);
    if (raw_time == -1) 
    {
        printf("��ȡʱ��ʧ�ܣ�\n");
        return;
    }

    // ת��Ϊ����ʱ��
    struct tm* time_info = localtime(&raw_time);
    if (time_info == NULL) {
        printf("ת������ʱ��ʧ�ܣ�\n");
        return;
    }

    // ��ʽ��ʱ���ַ���
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    // ��ʾʱ��
    printf("��ǰʱ����: %s\n", time_str);
}
char* display_end_time()
{
    // ��ȡ��ǰʱ���
    time_t raw_time = time(NULL) + TIME_LIMIT;
    if (raw_time == -1)
    {
        printf("��ȡʱ��ʧ�ܣ�\n");
        return;
    }

    // ת��Ϊ����ʱ��
    struct tm* time_info = localtime(&raw_time);
    if (time_info == NULL) {
        printf("ת������ʱ��ʧ�ܣ�\n");
        return;
    }

    // ��ʽ��ʱ���ַ���
    static char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    // ��ʾʱ��
    //printf("����ʱ����: %s\n", time_str);
    return time_str;
}