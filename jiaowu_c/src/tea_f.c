#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "hand.h"

//老师注册
void teacher_sign_in()
{
    int x=1;
    struct teacher*hand = NULL;
    hand = create_node();       //创造节点
    hand = teacher_read(hand);      //读取老师信息，防止重复
    while(x)
    {
        printf("-------------------------------------\n");
        printf("欢迎来到老师注册界面\n");
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
        printf("请输入教师编号：");
        char id[20];
        scanf("%s",id);
        while(getchar()!='\n');
        printf("年龄：");
        int age;
        scanf("%d",&age);
        while(getchar()!='\n');
        x=ver_code(x);                                 //验证码
        printf("----------------------------------------");
        struct teacher *s = search_teacher(hand,id);
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
            struct teacher new_teacher;    //写入老师信息
            strcpy(new_teacher.name,name);
            strcpy(new_teacher.password,name);
            strcpy(new_teacher.id,id);
            new_teacher.age = age;
            add_teacher(new_teacher,hand);
            printf("注册成功\n");
            x=0;
        }
    }
    free_list(hand);       //释放内存
}


//创建节点
struct teacher*create_node()
{
    struct teacher*node = (struct teacher*)malloc(sizeof(struct teacher));
    assert(node!=NULL);
    node->next = NULL;
    return node;
}

//读取老师信息
struct teacher*teacher_read(struct teacher*hand)
{
    FILE*fp = NULL;
    fp=fopen("./teacher_data.txt","r");
    assert(fp!=NULL);
    //开始读
    struct teacher *pnew=NULL,*newhand=NULL;
    int ret;
    while(1)
    {
        pnew = create_node();
        ret = fscanf(fp,"%s%s%s%d",pnew->name,pnew->password,pnew->id,&pnew->age);
        if(ret == EOF)
        {
            break;
        }
        pnew->next = newhand;
        newhand = pnew;
    }
    free(pnew);
    fclose(fp);
    printf("读取老师信息成功\n");
    hand->next = newhand;
    return hand;
};

//验证码
int ver_code(int x)
{
    int flag_one=1;
    int flag_two=1;
    int times=0;
    srand((unsigned int)time(NULL));
    //一级验证
    while(flag_one){
        char alphabet[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char integer[]="0123456789";
        char symbol[]="~!@#$^&*()_-=+{}[]|<>:;?";
        char store[5];
        int num=0;
        printf("验证码：");
        for(int i=0;i<2;i++)
        {
            int x=rand()%52;
            printf("%c",alphabet[x]);
            store[num]=alphabet[x];
            ++num;
        }
        for(int i=0;i<4;i++)
        {
            int y=rand()%24;
            printf("%c",symbol[y]);
        }
        for(int i=0;i<2;i++)
        {
            int z=rand()%10;
            printf("%c",integer[z]);
            store[num]=integer[z];
            ++num;
        }
        for(int i=0;i<2;i++)
        {
            int y=rand()%24;
            printf("%c",symbol[y]);
        }   
        printf("\n");
        printf("请输入有效验证码(数字和字母):");
        char yanz[5];
        scanf("%s",yanz);
        if(strcmp(store,yanz)==0)
        {
            ++times;
            break;
        }
        else
        {
            printf("验证码错误\n");
            if(times==2)
            {
                printf("三次输入错误，退出\n");
                return 0;
            }
            printf("退出请按0,任意键继续\n");
            int set;
            scanf("%d",&set);
            while(getchar()!='\n');
            if(set==0)
            {
                return 0;
            }
        }
        ++times;
    }
    //二级验证
    if(times==1)
    {
        printf("验证成功\n");
        return 1;
    }
    else
    {
        times=0;
        while(flag_two)
        {
            printf("请输入计算后的结果(整数)：");
            char ari_sign[5]={'+','-','*','/'};
            int a=rand()%20;
            int b=rand()%20+1;
            int x=rand()%4;
            int c;
            int result;
            printf("%d %c %d =",a,ari_sign[x],b);
            if(ari_sign[x]=='+')
            {
                result = a + b;
            }
            if(ari_sign[x]=='-')
            {
                result = a - b;
            }
            if(ari_sign[x]=='*')
            {
                result = a * b;
            }
            if(ari_sign[x]=='/')
            {
                result = a / b;
            }
            scanf("%d",&c);
            if(result==c)
            {
                printf("验证成功\n");
                return 1;
            }
            else
            {
                printf("计算错误\n");
                if(times==2)
                {
                    printf("三次输入错误，退出\n");
                    return 0;
                }
                printf("退出请按0,任意键继续\n");
                int set;
                scanf("%d",&set);
                while(getchar()!='\n');
                if(set==0)
                {
                    return 0;
                }
                ++times;
            }
        }
    }
}

//寻找老师信息
struct teacher*search_teacher(struct teacher *hand,char *id)
{
    struct teacher *p = NULL,*ps = NULL;
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
        printf("无该老师信息\n");
    }
    return ps;
}

//写入老师信息
void add_teacher(struct teacher new_teacher,strcut teacher*hand)
{
    struct teacher*new_node = create_node();
    memcpy(new_node,&new_teacher,sizeof(struct teacher));
    new_node->next = hand->next;
    hand->next = new_node;
    //写入
    FILE*fp = NULL;
    fp=fopen("./teacher_data.txt","a");
    assert(fp!=NULL);
    if(fprintf(fp,"%s %s %s %d\n",new_node->name,new_node->password,new_node->id,new_node->age)<0)
    {
        perror("fprintf error");
        fclose(fp);
        return;
    }
    fclose(fp);
}

//释放内存
void free_list(struct teacher*hand)
{
    struct teacher*current = hand;
    struct teacher*next;
    while(current!=NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}



//老师登入和功能
void teacher_info()
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
    s = create_node();
    while(x)
    {
        printf("-----------------------------------\n");
        printf("欢迎来到老师登录界面\n");
        printf("请输入教师编号：");
        char id[20];
        scanf("%s",id);
        while(getchar()!='\n');
        printf("请输入密码:\n");
        char password[20];
        scanf("%s",password);
        while(getchar()!='\n');
        x=ver_code(int x);
        printf("正在确认中...\n");
        s = search_teacher(tea_hand,id);    
        if(NULL = s)
        {
            printf("登录失败\n");
            return;
        }
        else if(strcmp(s->id,id)==0 && strcmp(s->password,password)==0)
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
        printf("欢迎来到老师功能界面\n");
        printf("请选择功能:\n");
        printf("1,查阅信息\n");
        printf("2,修改密码\n");
        printf("3,学生成绩\n");
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
            case 2:change_password(s);break;
            case 3:stu_grade();break;
            case 4:email();break;
            case 5:tea_question();break;
            case 6:sma_umb();break;
            case 7:flag = delete_tea_data(tea_hand,s);break;
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

//查阅信息
void search_data(struct teacher*tea_hand,struct student*stu_hand)
{
    int x=1;
    while(x)
    {
        struct teacher *new_s = NULL;
        new_s = tea_hand;
        struct student *new_ps = NULL;
        new_ps = stu_hand;
        printf("-------------------------------------\n");
        printf("1,老师         2,学生          0,退出\n");
        printf("你要查找的是:");
        int choose;
        scanf("%d",&choose);
        while(getchar()!='\n');
        switch(choose)
        {
            case 0:x = 0;break;
            case 1:search_teacher_all(new_s);break;
            case 2:search_student_all(new_ps);break;
            default:printf("无此功能\n");
            break;
        }
    }
}

//搜索老师信息
void search_teacher_all(struct teacher*hand)
{
    int flag;
    while(flag)
    {
       printf("1,教师编号查找       2,姓名查找     0,退出\n");
       printf(选择:);
       int choose;
       scanf("%d",&choose);
       while(getchar()!='\n');
       switch(choose)
       {
        case 0;flag = 0;break;
        case 1:search_teacher_id(hand);break;
        case 2:search_teacher_name(hand);break;
        default:printf("无此功能\n");
        break;
       } 
    }
}

//用id搜索老师
void search_teacher_id(struct teacher*hand)
{
    printf("输入教师编号:");
    char id[20];
    fgets(id,sizeof(id),stdin);
    size_t len = strlen(id);
    if(len > 0 && id[len-1]=='\n')
    {
        id[len-1] = '\0';
    }
    struct teacher*n = search_teacher(hand,id);
    if(n = NULL)
    {
        printf("没有这个人哦，亲\n再核对一下信息吧！\n");
        return;
    }
    else
    {
        printf("name:%s\n",n->name);
        printf("id:%s\n",n->id);
        printf("age:%d\n",n->age);
        return;
    } 
}

//用name搜索老师
void search_teacher_name(struct teacher*hand)
{
    printf("输入老师姓名:");
    char name[20];
    fgets(name,sizeof(name),stdin);
    size_t len = strlen(name);
    if(len > 0 && name[len-1]=='\n')
    {
        name[len-1] = '\0';
    }
    struct teacher *p = NULL,*ps = NULL;
    p = hand->next;
    while(p!=NULL)
    {
        if(strcmp(p->name,name)==0)
        {
            ps = p;
            break;
        }
        p = p->next;
    }
    if(ps == NULL)
    {
        printf("无该老师信息\n");
        return;
    }
    printf("name:%s\n",ps->name);
    printf("id:%s\n",ps->id);
    printf("age:%d\n",ps->age);
    return;
}

//搜索学生信息
void search_student_all(struct student*hand)
{
    int flag;
    while(flag)
    {
       printf("1,学号查找       2,姓名查找      0,退出\n");
       printf(选择:);
       int choose;
       scanf("%d",&choose);
       while(getchar()!='\n');
       switch(choose)
       {
        case 0;flag = 0;break;
        case 1:search_student_id(hand);break;
        case 2:search_student_name(hand);break;
        default:printf("无此功能\n");
        break;
       } 
    }
}

//用id搜索学生信息
void search_student_id(struct student*hand)
{
    printf("输入学号:");
    char id[20];
    fgets(id,sizeof(id),stdin);
    size_t len = strlen(id);
    if(len > 0 && id[len-1]=='\n')
    {
        id[len-1] = '\0';
    }
    struct student*n = search_student(hand,id);
    if(n = NULL)
    {
        printf("没有这个人哦，亲\n再核对一下信息吧！\n");
        return;
    }
    else
    {
        printf("name:%s\n",n->name);
        printf("id:%s\n",n->id);
        printf("age:%d\n",n->age);
        printf("class:%s\n",n->class);
        return;
    } 
}

//用name搜索学生信息
void search_student_name(struct student*hand)
{
    printf("输入学生姓名:");
    char name[20];
    fgets(name,sizeof(name),stdin);
    size_t len = strlen(name);
    if(len > 0 && name[len-1]=='\n')
    {
        name[len-1] = '\0';
    }
    struct student *p = NULL,*ps = NULL;
    p = hand->next;
    while(p!=NULL)
    {
        if(strcmp(p->name,name)==0)
        {
            ps = p;
            break;
        }
        p = p->next;
    }
    if(ps == NULL)
    {
        printf("无该学生信息\n");
        return;
    }
    printf("name:%s\n",ps->name);
    printf("id:%s\n",ps->id);
    printf("age:%d\n",ps->age);
    printf("class:%s\n",ps->class);
    return;
}

//修改密码
void change_password(struct teacher*current)
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

//注销账户
int delete_tea_data(struct teacher*hand,struct teacher*current)
{
    FILE*fp = fopen("./teacher_data.txt","r");
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
    char line[100];
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
    remove("./teacher_data.txt");
    rename("temp_fp.txt","./teacher_data.txt");
    if(current = hand)
    {
        hand->next = current->next;
    }
    else
    {
        struct teacher*pre = hand;
        while(pre->next!=current)
        {
            pre = pre->next;
        }
        pre->next = current->next;
    }
    free_list(hand);
    return 0;
}

//学生成绩
void stu_grade()
{

}