#include <stdio.h>
#include <stdlib.h>

typedef struct Joseph
{
    int secrete;         // 每个人的密码
    int no;              // 每个人的编号
    struct Joseph *next; // 下一个结点
} Joseph;

int joseph(Joseph *first, int n, int m);    // 具体算法
void input(int *n);                         // 限制输入
int insertList(Joseph *rare, int i, int n); // 将结点插入链表，构造单向循环链表

int main(void)
{
    int n, m;     // 总人数、报数上限值
    Joseph *rare; // 链表尾指针

    // 初始化循环链表
    rare = (Joseph *)malloc(sizeof(Joseph));
    rare->next = NULL;

    printf("\n请输入初始报数上限值m：");
    input(&m);
    printf("\n请输入总人数n：");
    input(&n);

    for (int i = 1; i < (n + 1); i++)
        insertList(rare, i, n);

    // printf("\n密码出列顺序为：");
    printf("\n编号出列顺序为：");
    joseph(rare->next, n, m);

    return 1;
}

int joseph(Joseph *first, int n, int m)
{
    if (n == 1)
    {
        // printf("%d--", first->secrete);
        printf("%d", first->no);
        return 0;
    }

    else
    {
        Joseph *p;
        p = first;

        // 查找报数为最大值m的结点的前一个结点
        if (m == 1)
        {
            for (int i = 1; i < n; i++)
            {
                p = p->next;
            }
        }

        if (m > 2)
        {
            for (int i = 1; i < m - 1; i++)
            {
                p = p->next;
            }
        }

        // printf("--%d--", p->next->secrete);
        printf("%d，", p->next->no);

        int m1 = p->next->secrete; //更新最大报数m

        //删除出列节点
        p->next = p->next->next;
        // free(p->next);

        joseph(p->next, n - 1, m1); //递归调用
    }

    return 1;
}

void input(int *n)
{
    scanf("%d", n);
    if (*n < 1)
    {
        printf("请输入正整数：");
        input(n);
    }
}

int insertList(Joseph *rare, int i, int n)
{
    if (!rare)
    {
        printf("未创建链表！");
        return 0;
    }

    int secret;
    Joseph *p, *q;
    p = (Joseph *)malloc(sizeof(Joseph));
    q = rare;

    printf("\n请输入第%d个人的密码：", i);
    input(&secret);

    if (i == n)
    {
        rare->secrete = secret;
        rare->no = i;
    }
    else
    {
        p->secrete = secret;
        p->no = i;

        for (int j = 1; j < i; j++)
            q = q->next;

        if (i == 1) // 如果是第一个结点，则先构造循环链表
        {
            p->next = rare;
            rare->next = p;
        }
        else // 如果是其他结点，则用头插法存入链表中
        {
            p->next = rare;
            q->next = p;
        }
    }

    return 1;
}
