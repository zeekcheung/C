#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 文件
FILE *fp = NULL;
// 文件名
char *fileName = NULL;
//单词最大长度
const int MAX_LENGTH = 15;

// 存储单词的链节点
typedef struct QueueNode
{
    char *word;  // 词汇名
    int nums;    // 词汇出现次数
    char *lines; // 词汇所在行号
    struct QueueNode *next;
} QueueNode, *QueuePtr;

// 存储词汇表的链队列
typedef struct LinkQueue
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

void openFile();                        // 打开英文小说所在的文本文件
LinkQueue *initQueue(LinkQueue *Q);     // 初始化队列
int QueueEmpty(LinkQueue *Q);           // 判断队空
void EnQueue(LinkQueue *Q, char *word); // 入队
void DeQueue(LinkQueue *Q);             // 出队
void inputWords(LinkQueue *Q);          // 输入单词
void find(LinkQueue *Q);                // 统计词汇的出现次数和所在行号
void echoWords(LinkQueue *Q);

int main(void)
{
    // 打开文本文件
    openFile();
    // 构建词汇表
    LinkQueue *Q = NULL;
    Q = initQueue(Q);
    inputWords(Q);
    // 统计词汇的出现次数及位置
    find(Q);
    // 格式化输出
    echoWords(Q);
    getchar();
    return 0;
}

// 打开英文小说所在的文本文件
void openFile()
{
    int i = 0, length = MAX_LENGTH;
    char ch;

    if ((fileName = (char *)malloc(MAX_LENGTH * sizeof(char))) == NULL)
        return;

    printf("Please input the file name:\n");

    while ((ch = fgetc(stdin)) != '\n')
    {
        if (i >= MAX_LENGTH)
        {
            // 单词长度超过最大长度，重新申请内存
            if ((fileName = (char *)realloc(fileName, (++length) * sizeof(char))) == NULL)
                return;
        }

        fileName[i++] = ch;
    }
    fileName[i] = '\0';

    // 打开文件
    fp = fopen(fileName, "r");
    if (fp)
    {
        // printf("Success!");
        return;
    }
    else
    {
        printf("Fail to open the file!");
        openFile(fp);
    }
}

// 输入单词
void inputWords(LinkQueue *Q)
{
    int i = 0, length = MAX_LENGTH;
    char *word = NULL, ch;
    if ((word = (char *)malloc(MAX_LENGTH * sizeof(char))) == NULL)
        return;

    printf("Enter the words you want to retrieve, press enter to complete the input of a single word, "
           "and enter the # symbol to complete the input of all words:\n");

    while ((ch = fgetc(stdin)) != '#')
    {
        if (ch != '\n')
        {
            if (i >= MAX_LENGTH)
            {
                // 单词长度超过最大长度，重新申请内存
                if ((word = (char *)realloc(word, (++length) * sizeof(char))) == NULL)
                    return;
            }

            word[i++] = ch;
        }
        else
        {
            // 如果输入了回车符，则将该单词存入队列中
            word[i] = '\0';
            EnQueue(Q, word);
            // 清空word字符串
            // memset(word, 0, i * sizeof(char));
            word[0] = '\0';
            i = 0;
        }
    }
}

// 初始化词汇链表
LinkQueue *initQueue(LinkQueue *Q)
{
    Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QueueNode));

    if (!Q->front)
        return NULL;

    Q->rear->next = NULL;
    return Q;
}

// 判断队空
int QueueEmpty(LinkQueue *Q)
{
    return Q->front == Q->rear;
}

// 词汇节点入队
void EnQueue(LinkQueue *Q, char *word)
{
    QueuePtr q = (QueuePtr)malloc(sizeof(QueueNode));
    q->word = (char *)malloc(strlen(word) * sizeof(char));
    q->lines = (char *)malloc(50 * sizeof(char));
    if (q == NULL || q->word == NULL || q->lines == NULL)
        return;

    strcpy(q->word, word);
    q->nums = 0; // 出现次数初始化为0
    strcpy(q->lines, " ");
    q->next = NULL;
    Q->rear->next = q;
    Q->rear = q;
}

// 单词出队
void DeQueue(LinkQueue *Q)
{
    if (QueueEmpty(Q))
        return;

    QueueNode *q;
    q = Q->front->next;

    printf("\n-----------------------\n");
    printf("word:%s\n", q->word);
    printf("nums:%d\n", q->nums);
    printf("lines:%s", q->lines);
    printf("\n-----------------------\n");

    Q->front->next = q->next;
    if (q == Q->rear)
        Q->rear = Q->front;
    free(q);
}

// 统计词汇的出现次数和所在行号
void find(LinkQueue *Q)
{
    if (Q == NULL)
        return;

    char ch;           // 文本中每个字母
    char *word = NULL; // 文本中每个单词
    int row = 1;       // 行号
    int j = 0;         // 每个单词中字母下标
    int length = MAX_LENGTH;
    QueueNode *q = Q->front->next;
    if ((word = (char *)malloc(MAX_LENGTH * sizeof(char))) == NULL)
        return;

    // 一直读取文件直到结束
    while (!feof(fp))
    {
        ch = fgetc(fp);
        j = 0;
        // 截取文件中的每个单词
        while (ch != ' ' && ch != ')' && ch != '\n' && !feof(fp))
        {
            if (ch == '#' || ch == '(')
            {
                ch = fgetc(fp);
                continue;
            }
            else if (ch == '/')
            {
                while (fgetc(fp) != '\n')
                    continue;

                ch = fgetc(fp);
                row++;
            }
            else
            {
                if (j >= MAX_LENGTH)
                {
                    // 单词长度超过最大长度，重新申请内存
                    if ((word = (char *)realloc(word, (++length) * sizeof(char))) == NULL)
                        return;
                }
                word[j++] = ch;
                ch = fgetc(fp);
            }
        }
        word[j] = '\0';

        // 和词汇表中每个单词比对
        while (q)
        {
            if (strcmp(word, q->word) == 0)
            {
                q->nums++;

                char row_str[5];
                itoa(row, row_str, 10);
                strcat(strcat(q->lines, row_str), " ");
            }

            q = q->next;
        }

        // 如果换行
        if (ch == '\n')
        {
            row++;
        }

        // 清空word字符串
        // memset(word, 0, sizeof(char) * 256);
        word[0] = '\0';
        // 重置q
        q = Q->front->next;
    }
}

// 格式化输出词汇表
void echoWords(LinkQueue *Q)
{
    while (!QueueEmpty(Q))
        DeQueue(Q);
}
