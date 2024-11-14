#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "hand.h"


//学生注册
void student_sign_in()
{
    int x=1;
    struct student*hand = NULL;
    hand = stu_create_node();       //创造节点
    hand = student_read();      //读取学生信息，防止重复
    while(x)
    {
        printf("-------------------------------------\n");
        printf("欢迎来到学生注册界面\n");
        printf("请输入姓名：");
        char name[20];
        fgets(name,sizeof(name),stdin);
        size_t len = strlen(name);
        if(len > 0 && name[len-1]=='\n')
        {
            name[len-1] = '\0';
        }
        printf("请输入密码：");
        char password[20];
        scanf("%s",password);
        while(getchar()!='\n');
        printf("请输入学号：");
        char id[20];
        scanf("%s",id);
        while(getchar()!='\n');
        printf("年龄：");
        int age;
        scanf("%d",&age);
        while(getchar()!='\n');
        char class[30];
        printf("请输入班级:");
        scanf("%s",class);
        x=ver_code(x);                                 //验证码
        printf("----------------------------------------");
        struct student *s = search_student(hand,id);
        if(s != NULL && (s->id,id) == 0)
        {    
            printf("用户已存在\n");
            printf("退出请按0,继续注册请按1\n");
            int n;
            scanf("%d",&n);
            if(n == 0)
            {
                x=0;
            }
        }
        else
        {
            struct student new_student;    //写入学生信息
            strcpy(new_student.name,name);
            strcpy(new_student.password,name);
            strcpy(new_student.id,id);
            strcpy(new_student->class,class);
            new_student.age = age;
            add_student(new_student,hand);
            printf("注册成功\n");
            x=0;
        }
    }
    free_list(hand);       //释放内存
    return;
}

//创建节点
struct student*stu_create_node()
{
    struct student*node = (struct student*)malloc(sizeof(struct student));
    assert(node!=NULL);
    node->next = NULL;
    return node;
}

//读取学生信息
struct student*student_read(struct student*hand)
{
    FILE*fp = NULL;
    fp=fopen("./student_data.txt","r");
    assert(fp!=NULL);
    //开始读
    struct student *pnew=NULL,*newhand=NULL;
    int ret;
    while(1)
    {
        pnew = create_node();
        ret = fscanf(fp,"%s%s%s%d%s",pnew->name,pnew->password,pnew->id,&pnew->age,pnew->class);
        if(ret == EOF)
        {
            break;
        }
        pnew->next = newhand;
        newhand = pnew;
    }
    free(pnew);
    fclose(fp);
    printf("读取学生信息成功\n");
    hand->next = newhand;
    return hand;
};

//寻找学生信息
struct student*search_student(struct student *hand,char *id)
{
    struct student *p = NULL,*ps = NULL;
    p = hand->next;
    while(p!=NULL)
    {
        if(strcmp(p->id,id)==0)
        {
            ps = p;
            break;
        }
        p = p->next;
    }
    if(ps == NULL)
    {
        printf("无该学生信息\n");
    }
    return ps;
}

//写入学生信息
void add_student(struct student new_student,strcut student*hand)
{
    struct student*new_node = stu_create_node();
    memcpy(new_node,&new_student,sizeof(struct student));
    new_node->next = hand->next;
    hand->next = new_node;
    //写入
    FILE*fp = NULL;
    fp=fopen("./student_data.txt","a");
    assert(fp!=NULL);
    if(fprintf(fp,"%s %s %s %d %s\n",new_node->name,new_node->password,new_node->id,new_node->age,new_node->class)<0)
    {
        perror("fprintf error");
        fclose(fp);
        return;
    }
    fclose(fp);
}

//释放内存
void stu_free_list(struct student*hand)
{
    struct student*current = hand;
    struct student*next;
    while(current!=NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

//学生登录与功能
void student_info()
{
    int x=1;
    struct teacher*tea_hand = NULL;
    struct student*stu_hand() = NULL;
    tea_hand = create_node();
    tea_hand = teacher_read();
    stu_hand = stu_create_node();
    stu_hand = student_read();     //读学生信息
    struct student*ps = NULL;
    struct teacher*s = NULL;
    ps = stu_create_node();
    while(x)
    {
        printf("-----------------------------------\n");
        printf("欢迎来到学生登录界面\n");
        printf("请输入学号：");
        char id[20];
        scanf("%s",id);
        while(getchar()!='\n');
        printf("请输入密码:\n");
        char password[20];
        scanf("%s",password);
        while(getchar()!='\n');
        x=ver_code(int x);
        printf("正在确认中...\n");
        ps = search_student(stu_hand,id);    
        if(NULL = s)
        {
            printf("登录失败\n");
            return;
        }
        else if(strcmp(ps->id,id)==0 && strcmp(ps->password,password)==0)
        {
            printf("登录成功！\n");
            break;
        }
        else
        {
            printf("信息有误，请核实信息\n");
            return;
        }
    }
    int flag = 1;
    while(flag)
    {
        printf("-----------------------------------\n");
        printf("欢迎来到学生功能界面\n");
        printf("请选择功能:\n");
        printf("1,查阅信息\n");
        printf("2,修改密码\n");
        printf("3,成绩查询\n");
        printf("4,邮件\n");
        printf("5,问卷\n");
        printf("6,智能雨伞\n");
        printf("7,注销账户\n");
        printf("0,退出\n");
        printf("请选择:\n");
        int choose;
        scanf("%d",&choose);
        while(getchar()!='\n');
        switch(choose)
        {
            case 1:search_data(tea_hand,stu_hand);break;
            case 2:stu_change_password(ps);break;
            case 3:stu_grade_find();break;
            case 4:stu_email();break;
            case 5:stu_question();break;
            case 6:sma_umb();break;
            case 7:flag = delete_tea_data(stu_hand,ps);break;
            case 0:flag = 0; 
            break;
            default:printf("无此功能\n");
            break;
        }
    }
    teacher_write(s);
    stu_write(ps);
    return;
}

//注销账户
int delete_stu_data(struct student*hand,struct student*current)
{
    FILE*fp = fopen("./student_data.txt","r");
    if(NULL == fp)
    {
        perror("fopen error");
        return 1;
    }
    FILE*temp_fp = fopen("temp.txt","w");
    if(NULL == temp_fp)
    {
        perror("fopen temp error");
        fclose(fp);
        return 1;
    }
    char line[150];
    while(fgets(line,sizeof(line),fp))
    {
        char id[20];
        sscanf(line,"%*s %*s %s",id);
        if(strcmp(id,current->id)==0)
        {
            fputs(line,temp_fp);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("./student_data.txt");
    rename("temp_fp.txt","./student_data.txt");
    if(current = hand)
    {
        hand->next = current->next;
    }
    else
    {
        struct student*pre = hand;
        while(pre->next!=current)
        {
            pre = pre->next;
        }
        pre->next = current->next;
    }
    stu_free_list(hand);
    return 0;
}

//修改密码
void stu_change_password(struct student*current)
{
    char password_first[20];
    char password_second[20];
    printf("请输入你要更换的密码:");
    fgets(password_first,sizeof(password_first),stdin);
    size_t len = strlen(password_first);
    if(len > 0 && password_first[len-1]=='\n')
    {
        password_first[len-1] == '\0';
    }
    if (strlen(password_first) > 16)
    {
        printf("密码长度过长，请重新输入\n");
        return;
    }
    printf("再输一次:");
    fgets(password_second,sizeof(password_second),stdin);
    len = strlen(password_second);
    if(len > 0 && password_second[len-1]=='\n')
    {
        password_second[len-1] == '\0';
    }
    if (strlen(password_second) > 16)
    {
        printf("密码长度过长，请重新输入\n");
        return;
    }
    if(strcmp(password_first,password_second)==0)
    {
        strcpy(current->password,password_first);
        printf("修改成功\n");
        return;
    }
    else
    {
        printf("两次输入不同,修改错误\n");
        return;
    }
}