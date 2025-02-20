

#ifndef STRUCTURE_H
#define STRUCTURE_H


#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include<windows.h>
#include<time.h>



#define TIME_LIMIT 60; //定义考试时间为60秒

// 题目结构体
typedef struct question{
	int id;
	char type[256];//1是单选题,2是多选题,0是判断题
	char question[256];
	char option[4][100];
	char answer[10];
	int score;
	struct question *next;
}Question;


// 答卷结构体
typedef struct stuuser{
	int studentid;
	char name[256];
	struct stuuser* next;
}STUuser;

typedef struct stuanswer {
	int id;
	char answer[30];
	struct stuanswer* next;
}STUAnswer;


typedef struct user {
	char name[50];
	char password[50];
	int charactor;
	int grade;
}User;


extern Question* head;
extern Question* tail;
extern STUAnswer* s_head;
extern STUAnswer* s_tail;
extern int ID;
extern int StuANSFLAG;




void initquestion();
void add_question();
void read_question();
void clear_input_buffer();
void show_menu_student_start();
void show_menu_student_end();
int Login(const char* name, const char* password);
void delete_question(int number);
void show_menu_xiaoju();
void show_menu_admin();
void save_question(const char* filename);
void load_question(const char* filename);
void Start_exam();
int Get_grade();
void display_current_time();
char* display_end_time();
void show_analysis();






#endif // STRUCTURE_H
