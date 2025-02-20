#include"structure.h"

void display_current_time() 
{
    // 获取当前时间戳
    time_t raw_time = time(NULL);
    if (raw_time == -1) 
    {
        printf("获取时间失败！\n");
        return;
    }

    // 转换为本地时间
    struct tm* time_info = localtime(&raw_time);
    if (time_info == NULL) {
        printf("转换本地时间失败！\n");
        return;
    }

    // 格式化时间字符串
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    // 显示时间
    printf("当前时间是: %s\n", time_str);
}
char* display_end_time()
{
    // 获取当前时间戳
    time_t raw_time = time(NULL) + TIME_LIMIT;
    if (raw_time == -1)
    {
        printf("获取时间失败！\n");
        return;
    }

    // 转换为本地时间
    struct tm* time_info = localtime(&raw_time);
    if (time_info == NULL) {
        printf("转换本地时间失败！\n");
        return;
    }

    // 格式化时间字符串
    static char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    // 显示时间
    //printf("结束时间是: %s\n", time_str);
    return time_str;
}