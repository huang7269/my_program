#pragma once

struct teacher
{
    char name[20];
    char password[20];
    char id[20];
    int age;
    struct teacher*next;
    
};
struct student
{
    char name[20];
    char password[20];
    char id[20];
    int age;
    char cla[30];
    int chi_gra;
    int math_gra;
    int eng_gra;
    int sum_gra;
    struct student*next;
};

void teacher_sign_in();
struct teacher*create_node();
struct teacher*teacher_read();
int ver_code(int x);
struct teacher*search_teacher(struct teacher *hand,char *id);
void add_teacher(struct teacher new_teacher,strcut teacher*hand);
void free_list(struct teacher*hand);

void teacher_info();
void search_data(struct teacher*tea_hand,struct student*stu_hand);
void search_teacher_all(struct teacher*hand);
void search_teacher_id(struct teacher*hand);
void search_teacher_name(struct teacher*hand);
void search_student_all(struct student*hand);
void search_student_id(struct student*hand);
void search_student_name(struct student*hand);