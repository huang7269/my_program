#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hand.h"

int main()
{
    int x = 1;
    while(x)
    {
        printf("---------------------------------\n");
        printf("欢迎来到教务管理系统\n");
        printf("1,老师注册\n");
        printf("2,老师登录\n");
        printf("3,学生注册\n");
        printf("4,学生登录\n");
        printf("0,退出\n");
        printf("请选择（输入数字）：");
        int choose;
        scanf("%d",&choose);
        while(getchar()!='\n');
        switch (choose)
        {
        case 1:teacher_sign_in();break;
        case 2:teacher_info();break;
        case 3:student_sign_in();break;
        case 4:student_info();break;
        case 0:x=0;printf("成功退出\n");break;
        default:printf("无此功能\n");
            break;
        }
    }
    return 0;
}

