#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 6         //n个单位参加运动会
#define unit "学院" //参加运动会的单位(可以设定)
#define m 5         //男子比赛项目总数
#define w 5         //女子比赛项目总数
#define max_proj 3  //运动员最大的参加项目数
#define max_char 40 //字符串最大内存空间
#define max_long 10 //学号的最大位数
#define sco_file "D:\\sco_file.txt"    //成绩表的存储文件名

typedef struct Project
{
    char Jname_m[m][max_char];  // 男子比赛项目
    char Jname_w[w][max_char];  // 女生比赛项目
    int amout_proj_m[m];       // 各项男子比赛项目的报名人数
    int amout_proj_w[w];       // 各项女子比赛项目的报名人数
}Project;

typedef struct Unit
{

    char Cname[max_char];      // 单位名称
    int amout_m;               // 单位参加的男子比赛项目数
    int amout_w;               // 单位参加的女子比赛项目数
    char Jname_m[m][max_char];  // 单位参加的男子比赛项目
    char Jname_w[w][max_char];  // 单位参加的女子比赛项目
    int amout_M[m];            // 单位参加各项男子比赛项目的人数
    int amout_W[w];            // 单位参加各项女子比赛项目的人数
    float unit_score_m[m];     // 单位各项男子项目总成绩
    float unit_score_w[w];     // 单位各项女子项目总成绩
    struct Unit *next;         // 下一个单位结点
}Unit;

typedef struct Student
{
    int amout_S;             // 运动员参加项目的计数器，最大值为max_proj，初始值为0
    char Cname[max_char];    // 运动员所属单位名称
    long Sno;                // 运动员学号
    char Sname[max_char];    // 运动员姓名
    char Gender[max_char];   // 运动员性别
    char Jname[max_char];    // 参加的项目
    struct Student *next;    // 下一个运动员结点
}Student;

typedef struct Score
{
    long Sno;                 //学号
    char Gender[max_char];    //性别
    char Cname[max_char];     //运动员所属单位
    char Jname[max_char];     //参加的项目
    float score;              //该项项目的成绩
    struct Score *next;       //下一个成绩结点
}Score;

void initStudentList(Student *studentList);     //创建运动员链表
void initUnitList(Unit *unitList);              //创建单位链表
void initScoreLIst(Score *scoreList);           //创建成绩链表

int insertStudent(Student *studentList,Unit *unitList,Project *proj);       //录入运动员信息(增加运动员结点)
int insertUnit(Unit *unitList,Project *proj);                               //录入单位信息(增加单位结点)
int insertScore(Score *scoreList,Unit *unitList,Student *studentList);      //录入个人成绩信息(增加成绩结点)

int deleteStudent(Student *studentList,Project *proj);          //删除运动员信息(删除运动员结点)

int alterUnit(Unit *unitList);                                  //修改单位信息(修改单位结点数据)
int alterScore(Score *scoreList,Unit *unitList);                //修改个人成绩(修改成绩结点数据)

int searchUnitScore(Unit *unitList);                //查询单位成绩
int searchStudentScore(Score *scoreList);           //查询个人成绩

int setBackUp(Score *scoreList);    // 设置备份
int readBackUp(Score *scoreList);   // 读取备份
void importScore(Score *scoreList,long Sno,char* Gender,char* Cname,char* Jname,float score);   //读取备份创建成绩结点

void input_int(int* Amout);                     //输入单位参赛项目数,限制最大值
void input_Sno(long* Sno);                      //输入运动员学号，限制长度
void input_char(char* str);                     //输入字符串，限制长度

void menu();                                    //打印菜单

int main()
{
    // 设置比赛项目，项目名的顺序对应的项目的举办时间
    Project project = {
        {"跳高","跳远","篮球","足球","羽毛球"},
        {"跳高","跳远","篮球","足球","羽毛球"},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    //创建链表
    Student *studentList;
    Unit *unitList;
    Score *scoreList;

    //初始化链表
//    initStudentList(studentList);
//    initUnitList(unitList);
//    initScoreLIst(scoreList);

    studentList = (Student *)malloc(sizeof(Student));
    studentList->next = NULL;
//    printf("studentList->next:%p\n",studentList->next);
    unitList = (Unit *)malloc(sizeof(Unit));
    unitList->next = NULL;
//    printf("next_1:%p\n",unitList->next);
    scoreList = (Score *)malloc(sizeof(Score));
    scoreList->next = NULL;
//    printf("next_2:%p\n",scoreList->next);

    int operation = 1;      //操作选项
    while(operation)
    {
        menu();
        scanf("%d",&operation);
        switch(operation)
        {
        case 1:                 //运动员报名
            insertStudent(studentList,unitList,&project);
            break;
        case 2:                 //录入单位信息
            insertUnit(unitList,&project);
            break;
        case 3:                 //录入成绩信息
            insertScore(scoreList,unitList,studentList);
            break;
        case 4:                 //取消报名
            deleteStudent(studentList,&project);
            break;
        case 5:                 //修改单位信息
            alterUnit(unitList);
            break;
        case 6:                 //修改个人成绩
            alterScore(scoreList,unitList);
            break;
        case 7:                 //查询单位成绩
            searchUnitScore(unitList);
            break;
        case 8:                 //查询个人成绩
            searchStudentScore(scoreList);
            break;
        case 9:                 //系统退回到上次备份
            readBackUp(scoreList);
            break;
        case 0:                 //退出程序并备份
            setBackUp(scoreList);
            exit(0);
        default:
            printf("您输入的指令不正确，请重新输入");
        }
    }
}

void initStudentList(Student *studentList)
{
    studentList = (Student *)malloc(sizeof(Student));
    studentList->next = NULL;
//    printf("studentList->next:%p\n",studentList->next);
}

void initUnitList(Unit *unitList)
{
    unitList = (Unit *)malloc(sizeof(Unit));
    unitList->next = NULL;
//    printf("next_1:%p\n",unitList->next);
}

void initScoreLIst(Score *scoreList)
{
    scoreList = (Score *)malloc(sizeof(Score));
    scoreList->next = NULL;
//    printf("next_2:%p\n",scoreList->next);
}

//运动员参赛限制：
//1.不能参加异性的项目
//2.只能参加所属单位参与的项目
//3.最多只能参加max_proj个项目
//4.不能重复报名已报名的项目
//5.同步项目报名人数
int insertStudent(Student *studentList,Unit *unitList,Project *proj)
{
    char Cname[max_char];         // 运动员所属单位名称
    long Sno;                     // 运动员学号
    char Sname[max_char];         // 运动员姓名
    char Gender[max_char];        // 运动员性别
    char Jname[max_char];         // 参加的项目

    Student *p;
    p = (Student *)malloc(sizeof(Student));
    p->amout_S = 0;     // 参加的项目数初始化为0
    Student *q;
    q = studentList;
    Unit *r;
    r = unitList;

    if(!(r->next))
    {
        printf("单位表未创建！报名失败");
        return 0;
    }

    printf("\n请输入您所在的%s：",unit);
//    scanf("%s",p->Cname);
    input_char(p->Cname);
    printf("\n请输入您的学号：");
//    scanf("%ld",&Sno);
    input_Sno(&Sno);
    p->Sno = Sno;
    printf("\n请输入您的姓名：");
//    scanf("%s",p->Sname);
    input_char(p->Sname);
//    printf("Sname:%s",p->Sname);
    printf("\n请输入您的性别：");
//    scanf("%s",p->Gender);
    input_char(p->Gender);
//    printf("Gender:%s",p->Gender);
    printf("\n请输入您参加的项目：");
//    scanf("%s",p->Jname);
    input_char(p->Jname);

    while(r)
    {
        if(strcmp(p->Cname,r->Cname) == 0)
            break;

        r = r->next;
    }

    //只能参加所属单位参与的项目&&不能参加异性的项目
    if(strcmp(p->Gender,"男") == 0)
    {
//        printf("p->Gender == 男\n");

        for(int i=0;i<r->amout_m;i++)
        {
//            printf("r->amout[%d]:%s",i,r->Jname_m[i]);
            if(strcmp(p->Jname,r->Jname_m[i]) == 0)
            {
//                printf("p->Jname == r->Jname_m[i]\n");
//                printf("p->amout-S:%d\n",p->amout_S);

                while(q)
                {
                    if(q->Sno == p->Sno)
                    {
//                        printf("q->Sno == p->Sno\n");

                        //不能重复报名已报名的项目
                        if(q->amout_S == max_proj)
                        {
                            printf("\n您最多只能参加%d项比赛!",max_proj);
                            return 0;
                        }
                        // 最多只能参加max_proj个项目
                        if(strcmp(q->Jname,p->Jname)==0)
                        {
                            printf("\n您已经报名了%s比赛了",p->Jname);
                            return 0;
                        }
                        if((q->amout_S > p->amout_S)||(q->amout_S == p->amout_S))
                            p->amout_S = q->amout_S;
                    }
                    q = q->next;
                }

                if(p->amout_S < max_proj)
                {
//                    printf("p->amout_S < max_proj\n");   //测试

                    // 插入学生链表中（前插法）
                    p->next = studentList->next;
                    studentList->next = p;

                    for(int j=0;j<r->amout_m;j++)
                    {
                        // 同步项目参加人数
                        if(strcmp(proj->Jname_m[j],p->Jname) == 0)
                            proj->amout_proj_m[j]++;

                        //同步单位表中各项男生项目人数
                        if(strcmp(p->Jname,r->Jname_m[j]) == 0)
                            r->amout_M[j]++;
                    }

//                    for(int b=0;b<r->amout_m;b++) printf("\t%d",r->amout_M[b]);

                    printf("\n报名成功！");
                    return 1;
                }
            }
        }

        printf("\n您的单位没有参加该项目！");
        return 0;
    }

    //只能参加所属单位参与的项目&&不能参加异性的项目
    if(strcmp(p->Gender,"女") == 0)
    {
        for(int k=0;k<r->amout_w;k++)
        {
            if(strcmp(p->Jname,r->Jname_w[k]) == 0)
            {
                while(q)
                {
                    if(q->Sno == p->Sno)
                    {
                        //不能重复报名已报名的项目
                        if(q->amout_S == max_proj){
                            printf("\n您最多只能参加%d项比赛!",max_proj);
                            return 0;
                        }
                        // 最多只能参加max_proj个项目
                        if(strcmp(q->Jname,p->Jname) == 0)
                        {
                            printf("\n您已经报名了%s比赛了",p->Jname);
                            return 0;
                        }
                        if((q->amout_S > p->amout_S)||(q->amout_S == p->amout_S))
                            p->amout_S = q->amout_S;
                    }
                    q = q->next;
                }

                if(p->amout_S < max_proj)
                {
                    // 插入学生链表中（前插法）
                    p->next = studentList->next;
                    studentList->next = p;

                    for(int l=0;l<r->amout_w;l++)
                    {
                        // 同步项目参加人数
                        if(strcmp(proj->Jname_w[l],p->Jname) == 0)
                            proj->amout_proj_w[l]++;

                        // 同步单位表中各项女生项目人数
                        if(strcmp(p->Jname,r->Jname_w[l]) == 0)
                            r->amout_W[l]++;
                    }

                    printf("\n报名成功！");
                    return 1;
                }
            }

        }

        printf("\n您的单位没有参加该项目！");
        return 0;

    }
}

//单位录入信息限制：
// 1.不能录入相同的单位
// 2.单位选择参加的项目
// 3.初始化单位的各项成绩为0
int insertUnit(Unit *unitList,Project *proj)
{
    Unit *p,*q;
    p = (Unit *)malloc(sizeof(Unit));
    q = unitList;
    char jname_m[max_char];
    char jname_w[max_char];
    int amout_m,amout_w;
    int flag;

    printf("\n请输入%s的名称：",unit);
//    scanf("%s",p->Cname);
    input_char(p->Cname);

    while(q)
    {
        if(strcmp(p->Cname,q->Cname) == 0)
        {
            printf("单位表中已经有该单位的数据了！录入失败！");
            return 0;
        }
        q = q->next;
    }

    //单位选择参加的项目
    printf("\n请输入%s要报名的男子比赛项目总数：",p->Cname);
//    scanf("%d",&amout_m);
    input_int(&amout_m);
    p->amout_m = amout_m;
//    printf("p->amout_m:%d",p->amout_m);

    if(amout_m) printf("\n请输入%s要报名的男子比赛项目：\n",p->Cname);

    for(int i=0;i<amout_m;i++)
    {
        //初始化各个项目的参赛人数为0
        p->amout_M[i] = 0;
        // 初始化单位的各项成绩为0
        p->unit_score_m[i] = 0;

//        scanf("%s",&jname_m);5
        input_char(jname_m);

        flag = 0;
        for(int j=0;j<m;j++)
        {

            if(strcmp(jname_m,proj->Jname_m[j]) == 0)
            {

                flag = 1;
                strcpy(p->Jname_m[i],jname_m);            // 无法复制
//                printf("%s录入成功！\n",p->Jname_m[i]);
                break;
            }
        }

        if(!flag)
        {
            printf("没有该比赛项目！请重新输入！\n");
            i=-1;
        }
    }

    //单位选择参加的项目
    printf("\n请输入%s要报名的女子比赛项目总数：",p->Cname);
//    scanf("%d",&amout_w);
    input_int(&amout_w);
    p->amout_w = amout_w;

    if(amout_w) printf("\n请输入%s要报名的女子比赛项目：\n",p->Cname);

    for(int k=0;k<amout_w;k++)
    {
        //初始化各个项目的参赛人数为0
        p->amout_W[k] = 0;
        //初始化单位的各项成绩为0
        p->unit_score_w[k] = 0;

//        scanf("%s",&jname_w);
        input_char(jname_w);

        flag = 0;
        for(int l=0;l<w;l++)
        {
            if(strcmp(jname_w,proj->Jname_w[l]) == 0)
            {
                flag = 1;
                strcpy(p->Jname_w[k],jname_w);
                break;
            }
        }

        if(!flag)
        {
            printf("没有该比赛项目！请重新输入！\n");
            k=-1;
        }
    }

    // 插入单位结点（前插法）
    p->next = unitList->next;
    unitList->next = p;
    printf("\n录入成功！");

//    for(int a=0;a<amout_m;a++) printf("\n%s",p->Jname_m[a]);
//    for(int b=0;b<amout_m;b++) printf("\t%d",p->amout_M[b]);

    return 1;
}

//录入运动员成绩限制：
//不能有重复数据
//数据需要同步到Unit表中
int insertScore(Score *scoreList,Unit *unitList,Student *studentList)
{
    Score *p,*q;
    Unit *r;
    Student *s;
    p = (Score *)malloc(sizeof(Score));
    q = scoreList;
    r = unitList;
    s = studentList;
    long Sno;
    float score;
    int flag;

    if(!(r->next))
    {
        printf("单位表未创建！录入失败");
        return 0;
    }

    if(!(s->next))
    {
        printf("学生表未创建！录入失败");
        return 0;
    }

    printf("\n请输入运动员的学号：");
//    scanf("%l",p->Sno);
    input_Sno(&Sno);
    p->Sno = Sno;

    //判断运动员是否报名
    flag = 0;
    while(s)
    {
        if(s->Sno == Sno)
        {
            flag = 1;
            break;
        }
        s = s->next;
    }

    if(!flag)
    {
        printf("未找到该运动员的信息！");
        return 0;
    }

    printf("\n请输入运动员的性别：");
//    scanf("%s",p->Gender);
    input_char(p->Gender);
    printf("\n请输入运动员所属的%s：",unit);
//    scanf("%s",p->Cname);
    input_char(p->Cname);
    printf("\n请输入录入成绩的单个项目名称：");
//    scanf("%s",p->Jname);
    input_char(p->Jname);
    //不能录入重复数据

    while(q)
    {
        if((q->Sno == p->Sno)&&(strcmp(q->Jname,p->Jname)==0))
        {
            printf("\n您已经录入该项目的成绩了！");
            return 0;
        }
        q = q->next;
    }

    printf("\n请输入运动员该项的成绩：");
    scanf("%f",&score);
    p->score = score;

//    printf("score:%.2f",p->score);
    //同步UnitList表中的成绩

    while(r)
    {
        if(strcmp(p->Cname,r->Cname) == 0)
        {
            if(strcmp(p->Gender,"男") == 0)
            {
                for(int i=0;i<r->amout_m;i++)
                {
                    if(strcmp(p->Jname,r->Jname_m[i]) == 0)
                    {
                        r->unit_score_m[i] += p->score;
                        r->amout_M[i]++;
                        //插入成绩结点（前插法）
                        p->next = scoreList->next;
                        scoreList->next = p;
                        printf("\n录入成功！");
                        return 1;
                    }

                }
            }

            if(strcmp(p->Gender,"女") == 0)
            {
                for(int j=0;j<r->amout_w;j++)
                {
                    if(strcmp(p->Jname,r->Jname_w[j]) == 0)
                    {
                        r->unit_score_w[j] += p->score;
                        r->amout_W[j]++;
                        //插入成绩结点（前插法）
                        p->next = scoreList->next;
                        scoreList->next = p;
                        printf("\n录入成功！");
                        return 1;
                    }
                }
            }
        }

        r = r->next;
    }

    printf("\n未找到该运动员的信息！录入失败");
    return 0;
}

//取消报名限制：
//1.同步项目报名人数
int deleteStudent(Student *studentList,Project *proj)
{
    long Sno;
    char Jname[20];
    Student *p;
    p = studentList;

    if(!(p->next))
    {
        printf("学生表未创建！取消失败！");
        return 0;
    }

    printf("\n请输入您的学号：");
//    scanf("%ld",&Sno);
    input_Sno(&Sno);
    printf("\n请输入您想取消报名的项目：");
//    scanf("%s",&Jname);
    input_char(Jname);

    while(p)
    {
        if((Sno == p->next->Sno) && (strcmp(Jname,p->next->Jname))==0)
        {
            //同步项目报名人数
            if(strcmp(p->next->Gender,"男")==0)
            {
                for(int i=0;i<m;i++)
                {
                    if(strcmp(Jname,proj->Jname_m[i])==0)
                    {
                        proj->amout_proj_m[i]--;
                        printf("取消成功！");
                        //删除结点
                        p->next = p->next->next;
                        free(p->next);
                        return 1;
                    }

                }
            }
            if(strcmp(p->next->Gender,"女")==0)
            {
                for(int j=0;j<w;j++)
                {
                    if(strcmp(Jname,proj->Jname_w[j])==0)
                    {
                        proj->amout_proj_w[j]--;
                        printf("取消成功！");
                        //删除结点
                        p->next = p->next->next;
                        free(p->next);
                        return 1;
                    }

                }
            }
        }
        p = p->next;
    }
    printf("未找到您的报名信息！取消失败！");
}

//修改运动员成绩限制：
//同步unit成绩
int alterScore(Score *scoreList,Unit *unitList)
{
    long Sno;
    char Jname[max_char];
    float score;
    float diff;     //成绩差

    Score *p;
    p = scoreList;
    Unit *q;
    q = unitList;

    if(!(p->next))
    {
        printf("成绩表未创建！修改失败！");
        return 0;
    }

    if(!(q->next))
    {
        printf("单位表未创建！修改失败");
        return 0;
    }

    printf("\n请输入需要修改成绩的运动员的学号：");
//    scanf("%ld",&Sno);
    input_Sno(&Sno);
    printf("\n请输入需要成绩的项目：");
//    scanf("%s",&Jname);
    input_char(Jname);

    while(p)
    {
        if((p->Sno == Sno)&&(strcmp(p->Jname,Jname)==0))
        {
            diff = p->score;      //原始成绩
            printf("\n请输入修改后的成绩:");
            scanf("%f",&score);
            p->score = score;
            diff = p->score - diff;

            //同步unitList表中的数据

            while(q)
            {
                if(strcmp(p->Gender,"男")==0)
                {
                    for(int i=0;i<m;i++)
                    {
                        if(strcmp(Jname,q->Jname_m[i])==0)
                        {
                            q->unit_score_m[i] += diff;
                            printf("\n修改成功！");
                            return 1;
                        }

                    }
                }

                if(strcmp(p->Gender,"女")==0)
                {
                    for(int i=0;i<w;i++)
                    {
                        if(strcmp(Jname,q->Jname_w[i])==0)
                        {
                            q->unit_score_w[i] += diff;
                            printf("\n修改成功！");
                            return 1;
                        }

                    }
                }

                q = q->next;
            }
        }
        p = p->next;
    }
    printf("\n无法找到该项数据！");
    return 0;
}


//修改单位信息（单位名）
int alterUnit(Unit *unitList)
{
    char Cname[max_char];
    Unit *p;
    p = unitList;

    if(!(p->next))
    {
        printf("单位表未创建！修改失败！");
        return 0;
    }

    printf("\n请输入需要修改的%s：",unit);
//    scanf("%s",&Cname);
    input_char(Cname);
//    printf("Cname:%s",Cname);

    while(p)
    {
        if(strcmp(Cname,p->Cname)==0)
        {
            printf("\n请输入修改后的%s：",unit);
//            scanf("%s",p->Cname);
            input_char(p->Cname);
            printf("\n修改成功！");
            return 1;
        }
        p = p->next;
    }

    printf("\n数据库中没有这个%s！",unit);
    return 0;
}

//根据学号从scoreList中筛选出该运动员的各项成绩输出
int searchStudentScore(Score *scoreList)
{
    Score *p;
    long Sno;
    int flag;
    p = scoreList;
    flag = 0;

    if(!(p->next))
    {
        printf("成绩表未创建！查询失败！");
        return 0;
    }

    printf("\n请输入您的学号：");
//    scanf("%ld",&Sno);
    input_Sno(&Sno);

    while(p)
    {
        if(Sno == p->Sno)
        {
            flag++;
            printf("\n%s\t%.2f\n",p->Jname,p->score);
        }

        p = p->next;
    }

    if(!flag)
        printf("\n数据库中没有您的成绩");
    return 0;
}

//直接输出unitList中某个结点的平均成绩
int searchUnitScore(Unit *unitList)
{
    char Cname[max_char];
    Unit *p;
    p = unitList;

    if(!(p->next))
    {
        printf("单位表未创建！查询失败！");
        return 0;
    }

    printf("\n请输入需要查询成绩的%s：",unit);
    input_char(Cname);
//    printf("Cname:%s",Cname);
//    printf("\n%p",p);

    while(p)
    {
        if(strcmp(p->Cname,Cname)==0)
        {
            printf("\n%s的各项男子比赛项目成绩为：\n",Cname);
            if(p->amout_m)
            {
                for(int i=0;i<p->amout_m;i++)
                {
                    printf("\n%s\t%.2f",p->Jname_m[i],(p->unit_score_m[i])/(p->amout_M[i]));
                }
            }
            else
                printf("0");




            printf("\n\n%s的各项女子比赛项目成绩为：\n",Cname);
            if(p->amout_w)
            {
                for(int j=0;j<p->amout_w;j++)
                {
                    printf("\n%s\t%.2f",p->Jname_w[j],(p->unit_score_w[j])/(p->amout_W[j]));
                }
            }
            else
                printf("0");

            return 1;
        }
        p = p->next;
    }

    if(!p)
    {
        printf("数据库中没有该%s的成绩",unit);
        return 0;
    }
}

int setBackUp(Score *scoreList)
{
    if(!scoreList->next)
    {
        printf("成绩表为空表！备份失败！");
        return 0;
    }

    Score *p;
    FILE *fp;

    p = scoreList->next;
    fp = fopen(sco_file,"w");

    fprintf(fp,"学号\t性别\t单位\t项目\t成绩\n");     //文件的表头
    while(p)
    {
        fprintf(fp,"%ld\t%s\t%s\t%s\t%.2f\n",p->Sno,p->Gender,p->Cname,p->Jname,p->score);
        p = p->next;
    }

    fclose(fp);
    printf("备份成功！");
    return 1;
}

int readBackUp(Score *scoreList)
{


    FILE *fp;
    fp = fopen(sco_file,"r");
    if(!fp)
    {
        printf("文件不存在！");
        return 0;
    }

    long Sno;                 //学号
    char Gender[max_char];    //性别
    char Cname[max_char];     //运动员所属单位
    char Jname[max_char];     //参加的项目
    float score;              //该项项目的成绩

    Score *scoreList_1;       //备份的成绩链表
    scoreList_1 = (Score *)malloc(sizeof(Score)); //链表头指针
    scoreList_1->next = NULL;

    fseek(fp,sizeof("学号\t性别\t单位\t项目\t成绩\n"),SEEK_SET);       //跳过表头

//    printf("%d",fscanf(fp,"%ld\t%s\t%s\t%s\t%f\n",&Sno,Gender,Cname,Jname,&score));
//    printf("\n%s",Gender);
    printf("\n学号\t性别\t单位\t项目\t成绩\n");
    while(fscanf(fp,"%ld\t%s\t%s\t%s\t%f\n",&Sno,&Gender,&Cname,&Jname,&score)!=EOF)
        importScore(scoreList_1,Sno,Gender,Cname,Jname,score);

    if(fp != NULL) fclose(fp);
    scoreList = scoreList_1;
    printf("\n成绩表已还原为上次备份的状态！");
    return 1;
}

void importScore(Score *scoreList,long Sno,char* Gender,char* Cname,char* Jname,float score)
{
    Score *p;
    p = (Score *)malloc(sizeof(Score));

    p->Sno = Sno;
    strcpy(p->Cname,Cname);
    strcpy(p->Gender,Gender);
    strcpy(p->Jname,Jname);
    p->score = score;

    p->next = scoreList->next;
    scoreList->next = p;
    printf("%ld\t%s\t%s\t%s\t %.2f\n",p->Sno,p->Gender,p->Cname,p->Jname,p->score);
}


void input_int(int* Amout)
{
    int amout;
    scanf("%d",&amout);

    if((amout > 5)||(amout < 0))
    {
        printf("请重新输入0-%d的整数！\n",w);
        input_int(Amout);
    }

    *Amout = amout;
}

void input_Sno(long* Sno)
{
    char str[max_char];
    long sno;
    scanf("%ld",&sno);
    *Sno = sno;
    itoa(sno,str,10);
    if(strlen(str)>max_long)
    {
        printf("\n请重新输入10位以内的整数！");
        input_Sno(Sno);
    }
}

void input_char(char* str)
{
    scanf("%s",str);
    if(strlen(str)>max_char)
    {
        printf("请重新输入二十个以内的汉字！");
        input_char(str);
    }
}

void menu()
{
    printf("\n\n");
    printf("\t\t\t===================学校运动会项目管理系统================\n");
    printf("\t\t\t*                                                       *\n");
    printf("\t\t\t*                    1>. 运动员报名                     *\n");
    printf("\t\t\t*                    2>. 录入单位信息                   *\n");
    printf("\t\t\t*                    3>. 录入各项成绩                   *\n");
    printf("\t\t\t*                    4>. 取消报名                       *\n");
    printf("\t\t\t*                    5>. 修改单位信息                   *\n");
    printf("\t\t\t*                    6>. 修改个人成绩                   *\n");
    printf("\t\t\t*                    7>. 查询单位成绩                   *\n");
    printf("\t\t\t*                    8>. 查询个人成绩                   *\n");
    printf("\t\t\t*                    9>. 还原管理系统                   *\n");
    printf("\t\t\t*                    0>. 退出管理系统                   *\n");
    printf("\t\t\t*                                                       *\n");
    printf("\t\t\t=========================================================\n");
    printf("\t\t\t                 输入选项，按回车进入选项:               \n");
}
