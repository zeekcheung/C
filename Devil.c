#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlength 20 //原始魔王语言字符串最大长度
#define B "tsaedsae" //规则B
#define A "sae"      //规则A

// 链栈结点
typedef struct StackNode
{
    char data;
    struct StackNode *next;
} StackNode, LinkStack;

// 链队列结点
typedef struct QueueNode
{
    char data;
    struct QueueNode *next;
} QueueNode, *QueuePtr;

// 链队列
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

LinkStack *input(LinkStack *S); //输入原始魔王语言并存入S栈中

int StackEmpty(LinkStack *S);          //判断栈空
LinkStack *push(LinkStack *S, char c); //入栈
LinkStack *pop(LinkStack *S, char *c); //出栈

LinkQueue *initQueue(LinkQueue *Q); //初始化队列
int QueueEmpty(LinkQueue *Q);       //判断队空
int EnQueue(LinkQueue *Q, char c);  //进队
int DeQueue(LinkQueue *Q, char *c); //出队

void explain(LinkStack *S, LinkQueue *Q); //解释S栈中存储的原始魔王语言，并将结果存入队列Q中
void echo(LinkQueue *Q);                  //输出队列Q中存储的解释后的魔王语言

int main(void)
{
    LinkStack *S = NULL; // 用链栈S存储原始魔王语言
    LinkQueue *Q = NULL; // 用链队列Q存储解释后的魔王语言

    Q = initQueue(Q);
    S = input(S);

    explain(S, Q);
    echo(Q);
    fflush(stdin);
    getchar();
    return 0;
}

//输入原始魔王语言并存入S栈中
LinkStack *input(LinkStack *S)
{
    char original[maxlength];
    scanf("%s", original);

    for (int i = strlen(original) - 1; i > -1; i--)
        S = push(S, original[i]);

    return S;
}

//判断栈空
int StackEmpty(LinkStack *S)
{
    return S == NULL;
}

//进栈
LinkStack *push(LinkStack *S, char c)
{
    StackNode *p;
    p = (StackNode *)malloc(sizeof(StackNode));
    if (!p)
        return 0;

    p->data = c;
    p->next = S;
    S = p;
    return S;
}

//出栈
LinkStack *pop(LinkStack *S, char *c)
{
    if (StackEmpty(S))
        return NULL;

    StackNode *p;
    p = S;
    *c = S->data;
    S = S->next;
    free(p);
    return S;
}

//初始化队列
LinkQueue *initQueue(LinkQueue *Q)
{
    Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QueueNode));
    if (!Q->front)
        return NULL;

    Q->rear->next = NULL;
    return Q;
}

//判断队空
int QueueEmpty(LinkQueue *Q)
{
    return Q->front == Q->rear;
}

//入队
int EnQueue(LinkQueue *Q, char c)
{
    QueuePtr q = (QueuePtr)malloc(sizeof(QueueNode));
    if (!q)
        return 0;

    q->data = c;
    q->next = NULL;
    Q->rear->next = q;
    Q->rear = q;
    return 1;
}

//出队
int DeQueue(LinkQueue *Q, char *c)
{
    if (QueueEmpty(Q))
        return 0;

    QueueNode *q;
    q = Q->front->next;
    *c = q->data;
    Q->front->next = q->next;
    if (q == Q->rear)
        Q->rear = Q->front;
    free(q);
    return 1;
}

//解释S栈中存储的原始魔王语言，并将结果存入队列Q中
void explain(LinkStack *S, LinkQueue *Q)
{
    LinkStack *S1 = NULL; //S1栈存储括号中转换后的英文字符串

    while (!StackEmpty(S))
    {
        char c;
        S = pop(S, &c);

        if (c != '(')
        {
            if (c == 'B') //字母B根据规则B解析后存入队列Q
            {
                for (int i = 0; i < strlen(B); i++)
                    EnQueue(Q, B[i]);
            }
            else if (c == 'A') //字母A根据规则A解析后存入队列Q
            {
                for (int j = 0; j < strlen(A); j++)
                    EnQueue(Q, A[j]);
            }
            else //小写字母直接存入队列Q
                EnQueue(Q, S->data);
        }
        else
        {
            //将括号内字符串根据规则转换后存入S1栈
            char n = S->data;
            S = S->next;
            c = S->data;
            while (c != ')')
            {
                S1 = push(S1, n);
                S1 = push(S1, c);
                S = S->next;
                c = S->data;
            }
            S1 = push(S1, n);
            S = S->next;

            //将转换后的字符串进一步转换后存入队列Q
            char c1;
            while (!StackEmpty(S1))
            {
                c1 = S1->data;
                if (c1 == 'B') //字母B根据规则B解析后存入队列Q
                {
                    for (int i = 0; i < strlen(B); i++)
                        EnQueue(Q, B[i]);
                }
                else if (c1 == 'A') //字母A根据规则A解析后存入队列Q
                {
                    for (int j = 0; j < strlen(A); j++)
                        EnQueue(Q, A[j]);
                }
                else //小写字母直接存入队列Q
                    EnQueue(Q, S1->data);

                S1 = S1->next;
            }
        }
    }
}

//输出队列Q中存储的解释后的魔王语言
void echo(LinkQueue *Q)
{
    char *c[1];
    char c1;
    while (!QueueEmpty(Q))
    {
        DeQueue(Q, &c1);
        switch (c1)
        {
        case 't':
            *c = "天";
            break;
        case 'd':
            *c = "地";
            break;
        case 's':
            *c = "上";
            break;
        case 'a':
            *c = "一只";
            break;
        case 'e':
            *c = "鹅";
            break;
        case 'z':
            *c = "追";
            break;
        case 'g':
            *c = "赶";
            break;
        case 'x':
            *c = "下";
            break;
        case 'n':
            *c = "蛋";
            break;
        case 'h':
            *c = "恨";
            break;
        default:
            break;
        }

        printf("%s", *c);
    }
}