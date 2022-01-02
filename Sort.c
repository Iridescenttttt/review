#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAXSIZE 50000

clock_t start, stop;
int delta[15] = {10000, 7000, 6000, 4000, 3333, 2200, 1111, 999, 888, 777, 666, 555, 444, 333};

typedef struct QueueNode{
    int num;
    struct QueueNode *next;
}QueueNode;

typedef struct Time{
    char *name;                                      //排序方法名称
    double t;                                              //所用时间
}Time;

void QuickSort(int *a, int low, int high)
{
    if(low >= high)return;
    int i = low, j = high;
    int temp = a[i];
    a[i] = a[(i + j) / 2];
    a[(i + j) / 2] = temp;
    int pivot = a[i];
    while(i < j){
        while(a[j] >= pivot && j > i)j--;
        a[i] = a[j];
        while(a[i] <= pivot && i < j)i++;
        a[j] = a[i];
    }
    a[i] = pivot;
    QuickSort(a, low, i - 1);
    QuickSort(a, i + 1, high);
}

void Init()
{
    int a[MAXSIZE + 1];
    srand(time(NULL));
    // 第一个样本（顺序）：
    for(int i = 1; i <= MAXSIZE; i++){
        a[i] = rand();
    }
    QuickSort(a, 1, MAXSIZE);
    freopen("Sample1.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", a[i]);
    }
    freopen("CON", "w", stdout);
    // 第二个样本（逆序）：
    for(int i = 1; i <= MAXSIZE; i++){
        a[i] = rand();
    }
    QuickSort(a, 1, MAXSIZE);
    freopen("Sample2.txt", "w", stdout);
    for(int i = MAXSIZE; i > 0; i--){
        printf("%d ", a[i]);
    }
    freopen("CON", "w", stdout);
    // 第三个样本（随机）：
    freopen("Sample3.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第四个样本（随机）：
    freopen("Sample4.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第五个样本（随机）：
    freopen("Sample5.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第六个样本（随机）：
    freopen("Sample6.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第七个样本（随机）：
    freopen("Sample7.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第八个样本（随机）：
    freopen("Sample8.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第九个样本（随机）：
    freopen("Sample9.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    // 第十个样本（随机）：
    freopen("SampleX.txt", "w", stdout);
    for(int i = 1; i <= MAXSIZE; i++){
        printf("%d ", rand());
    }
    freopen("CON", "w", stdout);
    printf("初始化完成\n");
}

void InsertSort(int *a)
{
    for(int i = 2; i <= MAXSIZE; i++){
        int temp = a[i];
        int j;
        for(j = i; j > 1; j--){
            if(temp < a[j - 1])a[j] = a[j - 1];
            else break;
        }
        a[j] = temp;
    }
}

void ShellSort(int *a)
{
    for(int i = 0; i < 15; i++){
        int d = delta[i];
        for(int j = 1; j <= d; j++){
            for(int k = j + d; j <= MAXSIZE; j += d){
                int temp = a[k];
                int l;
                for(l = k; l >= d; l -= d){
                    if(temp < a[l - d])a[l] = a[l - d];
                    else break;
                }
                a[l] = temp;
            }
        }
    }
    InsertSort(a);
}

void BubbleSort(int *a)
{
    for(int i = 1; i <= MAXSIZE; i++){
        for(int j = 1; j < MAXSIZE - i + 1; j++){
            if(a[j] > a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void SelectSort(int *a)
{
    for(int i = 1; i < MAXSIZE; i++){
        for(int j = i + 1; j <= MAXSIZE; j++){
            if(a[j] < a[i]){
                int temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}

void HeapAdjust(int *a, int low, int high)
{
    int temp = a[low];
    int i = low, j = 2 * i;
    while(j <= high){
        if(j + 1 <= high && a[j + 1] > a[j])j++;
        if(temp > a[j])break;
        a[i] = a[j];
        i = j;
        j = 2 * i;
    }
    a[i] = temp;
}

void HeapSort(int *a)
{
    for(int i = MAXSIZE / 2; i >= 1; i--){
        HeapAdjust(a, i, MAXSIZE);
    }
    for(int i = MAXSIZE; i > 1; i--){
        int temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        HeapAdjust(a, 1, i - 1);
    }
}

void Merge(int *a, int low, int mid, int high)
{
    int *b = (int*)malloc((high - low + 1) * sizeof(int));
    int i = low, j = mid + 1, k = 0;
    while(i <= mid && j <= high){
        if(a[i] < a[j]){
            b[k] = a[i];
            i++;
        }
        else{
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while(i <= mid){
        b[k] = a[i];
        i++;
        k++;
    }
    while(j <= high){
        b[k] = a[j];
        j++;
        k++;
    }
    for(k = 0, i = low; i <= high; i++, k++){
        a[i] = b[k];
    }
}

void MergeSort(int *a)
{
    for(int len = 1; len <= MAXSIZE; len = 2 * len){
        int i = 1;
        while(i + 2 * len <= MAXSIZE){
            Merge(a, i, i + len - 1, i + 2 * len - 1);
            i = i + 2 * len;
        }
        if(i + len <= MAXSIZE){
            Merge(a, i, i + len - 1, MAXSIZE);
        }
    }
}

void RadixSort(int *a)
{
    QueueNode q[10];
    for(int i = 0; i < 10; i++){
        q[i].next = NULL;
    }
    int radix = 1;
    for(int k = 1; k <= 5; k++){
        QueueNode *rear[10];
        for(int i = 0; i < 10; i++){
            rear[i] = &q[i];
        }
        radix *= 10;
        for(int i = 1; i <= MAXSIZE; i++){
            int m = (a[i] % radix) / (radix / 10);
            QueueNode *p = (QueueNode*)malloc(sizeof(QueueNode));
            p->num = a[i];
            p->next = NULL;
            rear[m]->next = p;
            rear[m] = rear[m]->next;
        }
        for(int i = 1, m = 0; m < 10; m++){
            while(q[m].next){
                a[i] = q[m].next->num;
                q[m].next = q[m].next->next;
                i++;
            }
        }
    }
}

int cmp(const void *x, const void *y)
{
    return (*(Time*)x).t - (*(Time*)y).t;
}

void test()
{
    int a[MAXSIZE + 1];
    Time s[8];
    for(int i = 0; i < 8; i++){
        s[i].name = (char*)malloc(15 * sizeof(char));
    }
    for(int i = 1; i <= 10; i++){
        char file[15] = "Sample";
        char num[6] = "\0";
        if(i >= 1 && i <= 9)num[0] = i + '0';
        else num[0] = 'X';
        strcat(num, ".txt");
        strcat(file, num);
        freopen(file, "r", stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        InsertSort(a);
        stop = clock();
        s[0].name = "直接插入排序";
        s[0].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        ShellSort(a);
        stop = clock();
        s[1].name = "希尔排序";
        s[1].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        BubbleSort(a);
        stop = clock();
        s[2].name = "冒泡排序";
        s[2].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        QuickSort(a, 1, MAXSIZE);
        stop = clock();
        s[3].name = "快速排序";
        s[3].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        SelectSort(a);
        stop = clock();
        s[4].name = "选择排序";
        s[4].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        HeapSort(a);
        stop = clock();
        s[5].name = "堆排序";
        s[5].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        MergeSort(a);
        stop = clock();
        s[6].name = "归并排序";
        s[6].t = stop - start;
        rewind(stdin);
        for(int j = 1; j <= MAXSIZE; j++){
            scanf("%d", &a[j]);
        }
        start = clock();
        RadixSort(a);
        stop = clock();
        s[7].name = "基数排序";
        s[7].t = stop - start;
        qsort(s, 8, sizeof(Time), cmp);
        printf("              ");
        for(int j = 0; j < 8; j++){
            printf("%s      ", s[j].name);
        }
        printf("\n");
        if(i == 1)printf("1.正序样本    ");
        else if(i == 2)printf("2.逆序样本   ");
        else printf("%d.随机样本    ", i);
        for(int j = 0; j < 8; j++){
            if(j != 7)printf("%f      ", s[j].t / 1000);
            else printf("%f\n", s[j].t / 1000);
        }
        // printf("%f\n", s[3].t / 1000);
    }
}

int main()
{
    Init();
    test(); 
    return 0;
}