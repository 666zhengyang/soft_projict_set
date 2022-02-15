/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-28 09:21:17
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-08-06 20:32:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// 
void create(int arr[], int size) {
    int num = 0;
    for (num = 0; num <= size - 1; num++) {
        arr[num] = rand() % 36 + 1;
    }
}

int val;  // 全局变量
void func(void) {
    int num = 10;
    int val = 100;
    printf("val是%d\n", val);
}

int fei(int num, int arr[], int size) {
    // static int arr[50] = {0};
    if (num <= 1) {
        return 1;
    }
    
    if (!arr[num - 2]) {


        arr[num - 2] = fei(num - 2, arr, size);
    }

    if (!arr[num - 1]) {
        arr[num - 1] = fei(num - 1, arr, size);
    }
    
    return arr[num - 2] + arr[num - 1];
}

void print(const void *p_v, int type) {
    if (!type) {
        printf("%c\n", *(const char *)p_v);
    }
    else if (type == 1) {
        printf("%d\n", *(const int *)p_v);
    }
    else if (type == 2) {
        printf("%g\n", *(const float *)p_v);
    }
}

void reverse(int *p_num, int size) {
    int *p_start = p_num, *p_end = p_num + size - 1;
    int tmp = 0;
    while (p_start < p_end) {
        tmp = *p_start;
        *p_start = *p_end;
        *p_end = tmp;
        p_start++;
        p_end--;
    }
}

int *max(const int *p_num, int size) {
    const int *p_tmp = NULL, *p_max = NULL;
    for (p_tmp = p_num;p_tmp <= p_num + size - 1;p_tmp++) {
        if (!p_max) {
            p_max = p_tmp;
        }
        else {
            if (*p_tmp > *p_max) {
                p_max = p_tmp;
            }
        }
    }
    return (int *)p_max;
}

typedef struct {
    int row;
    int col;
} pt;

typedef struct {
    pt pt1;
    pt pt2;
} rect;

rect *readdt(rect *p_r) 
{
    printf("请输入水平长方形的位置：");
    scanf("%d%d%d%d", &(p_r->pt1.row), &(p_r->pt1.col), &(p_r->pt2.row), &(p_r->pt2.col));
    return p_r;
}

int area(const rect *p_r) {
    int ret = (p_r->pt1.row - p_r->pt2.row) * (p_r->pt1.col - p_r->pt2.col);
    return ret >= 0 ? ret : 0 - ret;
}

pt *midpt(const rect *p_r, pt *p_mid) {
    p_mid->row = (p_r->pt1.row + p_r->pt2.row) / 2;
    p_mid->col = (p_r->pt1.col + p_r->pt2.col) / 2;
    return p_mid;
}

pt *read123(pt *p_pt) {
    printf("请输入点的位置：");
    scanf("%d%d", &(p_pt->row), &(p_pt->col));
    return p_pt;
}

rect *read(void) {
    rect *p_r = (rect *)malloc(sizeof(rect));
    if (p_r) {
        printf("请输入水平长方形的位置：");
        scanf("%d%d%d%d", &(p_r->pt1.row), &(p_r->pt1.col), &(p_r->pt2.row), &(p_r->pt2.col));
    }
    return p_r;
}
void print(const pt *p_pt) {
    printf("点的位置是(%d, %d)\n", p_pt->row, p_pt->col);
}

void larger(const rect *p_r1, const rect *p_r2, rect **pp_r) {
    *pp_r = (rect *)(area(p_r1) >= area(p_r2) ? p_r1 : p_r2);
}

typedef struct {
    pt center;
    int radius;
} circle;

void larger(const circle *p_cl1, const circle *p_cl2, circle **pp_cl) {
    *pp_cl = (circle *)(p_cl1->radius > p_cl2->radius ? p_cl1 : p_cl2);
}

/*void print(const int *p_num, int size) {
    int num = 0;
    for (num = 0;num <= size - 1;num++) {
        printf("%d ", *(p_num + num));
    }
    printf("\n");
}*/
void print_cb(int *p_num) {
    printf("%d ", *p_num);
}
void neg_cb(int *p_num) {
    *p_num = 0 - *p_num;
}
void for_each(int *p_num, int size, void (*p_func)(int *)) {
    int num = 0;
    for (num = 0;num <= size - 1;num++) {
        p_func(p_num + num);
    }
}

int add(int num, int num1) {
    return num + num1;
}

pt *midpt2(const rect *p_r) {
    pt *p_pt = (pt *)malloc(sizeof(pt));
    if (p_pt) {
        p_pt->row = (p_r->pt1.row + p_r->pt2.row) / 2;
        p_pt->col = (p_r->pt1.col + p_r->pt2.col) / 2;
    }
    return p_pt;
}

int *create2(int size) {
    int num = 0;
    int *p_num = (int *)malloc(size * sizeof(int));
    if (p_num) {
        for (num = 0;num <= size - 1;num++) {
            *(p_num + num) = rand() % 36 + 1;
        }
    }
    return p_num;
}

typedef struct {
    int id;
    float salary;
    char name[10];
} person;

int main(int argc, char *argv[])  {
#if 0
    {
        int num = 0, num1 = 0;    //变量声明语句
        num = 10;    //赋值语句
        num = 4 + 7;
        num + 5;
        printf("num是%d\n", num);
        num = num;
        printf("&num是%p\n", &num);
    }

    {
        printf("1\n");
        printf("%d\n", 1);
        printf("%d\n", 5 - 4);
        printf("a%db%dc\n", 1, 2);
    }

    {
        int price1 = 5000, price2 = 750;
        printf("5000 - 750 = 4250\n");
        printf("%d - %d = %d\n", 5000, 750, 5000 - 750);
        printf("%d - %d = %d\n", price1, price2, price1 - price2);
    }

    {
        int num = 1;
        printf("%d ", num);
        num = num + 1;
        printf("%d ", num);
        num = num + 1;
        printf("%d ", num);
        num = num + 1;
        printf("%d ", num);
        num = num + 1;
        printf("%d\n", num);
    }

    {
        int num = 1, ten = 10;
        printf("%d X %d = %d\n", num, ten - num, num * (ten - num));
        num = num + 1;
        printf("%d X %d = %d\n", num, ten - num, num * (ten - num));
        num = num + 1;
        printf("%d X %d = %d\n", num, ten - num, num * (ten - num));
        num = num + 1;
        printf("%d X %d = %d\n", num, ten - num, num * (ten - num));
        num = num + 1;
        printf("%d X %d = %d\n", num, ten - num, num * (ten - num));
    }

    {
        int num = 54321, ten = 10;
        printf("%d\n", num);
        num = num / ten;
        printf("%d\n", num);
        num = num / ten;
        printf("%d\n", num);
        num = num / ten;
        printf("%d\n", num);
        num = num / ten;
        printf("%d\n", num);
    }

    {
        int num = 3, num1 = 7, tmp = 0;
        tmp = num;
        num = num1;
        num1 = tmp;
        printf("num是%d,num1是%d\n", num, num1);
    }
#endif 

#if 0
    {
        printf("abc\nde\n");
        printf("abc\rde\n");  
    }

    {
         printf("%g   %f\n", 3.2f, 3.2f);
    }

    {
        int num = 0;
        printf("sizeof(num)是%d\n", (int)sizeof(num));
        printf("sizeof(int)是%d\n", (int)sizeof(int));
        printf("sizeof(3 + 6)是%d\n", (int)sizeof(3 + 6));
        sizeof(num = 10);
        printf("num是%d\n", num);
    }    


    {
        int num = 0, num1 = 0;
        printf("请输入两个数字：");
        scanf("%d%d", &num, &num1);
        printf("num是%d\n", num);
        printf("num1是%d\n", num1);
    }

    {
        float radius = 0.0f;
        printf("请输入半径：");
        scanf("%g", &radius);
        printf("周长是%g\n", 2 * 3.14f * radius);
    }

    {
        char ch = 300;
        int num = ch;
        printf("num是%d\n", num);
        ch = 128;
        num = ch;
        printf("num是%d\n", num);
    }

    {
        printf("%d  0%o\n", 0152, 0152);
        printf("%d  0X%X  0x%x\n", 0xcb, 0xcb, 0xcb);
    }

    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("        %d\r", num % 2);
        num = num / 2;
        printf("       %d\r", num % 2);
        num = num / 2;
        printf("      %d\r", num % 2);
        num = num / 2;
        printf("     %d\r", num % 2);
        num = num / 2;
        printf("   %d\r", num % 2);
        num = num / 2;
        printf("  %d\r", num % 2);
        num = num / 2;
        printf(" %d\r", num % 2);
        num = num / 2;
        printf("%d\n", num % 2);
    }
#endif
 #if 0
    {
        int num = 10, num1 = 0;
        num++;
        printf("num是%d\n", num);
        ++num;
        printf("num是%d\n", num);
        num1 = num++;
        printf("num是%d,num1是%d\n", num, num1);
        num1 = ++num;
        printf("num是%d,num1是%d\n", num, num1);
        num = 10;
        num1 = num++ + ++num;
        printf("num是%d,num1是%d\n", num, num1);
        int num2 = 10;
        num1 = num2++ + ++num2;
        printf("num2是%d,num1是%d\n", num2, num1);
    }

    {
        char ch = 0;
        int num = 0;
        printf("15 / 6是%d\n", 15 / 6);
        printf("15 %% 6是%d\n", 15 % 6);
        num = ch = 300;
        printf("num是%d\n", num);
        num += 6;
        printf("num是%d\n", num);
        num *= 2 + 3;
        printf("num是%d\n", num);
    }

    {
        int num = 0;
        unsigned char ch = 0x80;
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("转换结果是");
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d ", (num & ch) != 0);
        ch >>= 1;
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d", (num & ch) != 0);
        ch >>= 1;
        printf("%d\n", (num & ch) != 0);
    }

    {
        int num = 0, base = 64;
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("转换结果是0");
        printf("%d", num / base);
        num %= base;
        base >>= 1;
        printf("%d", num / base);
        num %= base;
        base >>= 1;
        printf("%d ", num / base);
        num %= base;
        base >>= 1;
        printf("%d", num / base);
        num %= base;
        base >>= 1;
        printf("%d", num / base);
        num %= base;
        base >>= 1;
        printf("%d", num / base);
        num %= base;
        base >>= 1;
        printf("%d\n", num / base);
    }

    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        num = num >= 0 ? num : 0 - num;
        //num >= 0 ? num = num : num = 0 - num;  错误
        printf("绝对值是%d\n", num); 
    }

    {
        int num = 0;
        printf("sizeof(1 ? 1 : 0.9)是%d\n", sizeof(1 ? 1 : 0.9));
        printf("-7 + 3 < 0是%d\n", -7 + 3 < 0);
        printf("-7 + 3u < 0是%d\n", -7 + 3u < 0);
        num = (char)300;
        printf("num是%d\n", num);
    }

    {
        int num = 0;
        printf("&num是%p\n", &num);
        *(&num) = 10;
        printf("num是%d\n", num);
    }

    {
        char ch = ~0xb3;
        int num = ch;
        unsigned int unum = 0;
        printf("num是0x%x\n", num);
        printf("3 & 5是%d\n", 3 & 5);
        printf("3 | 5是%d\n", 3 | 5);
        printf("3 ^ 5是%d\n", 3 ^ 5);
        printf("3 << 2是%d\n", 3 << 2);
        unum = 0x80000000;
        printf("unum >> 2是0x%x\n", unum >> 2);
        num = 0x80000000;
        printf("num >> 2是0x%x\n", num >> 2);
    }

    {
        int num = 0;
        printf("!8是%d\n", !8);
        printf("3 < 7 < 5是%d\n", 3 < 7 < 5);
        printf("3 < 7 && 7 < 5是%d\n", 3 < 7 && 7 < 5);
        1 || ++num;
        printf("num是%d\n", num);
        0 && ++num;
        printf("num是%d\n", num);
    }
#endif

#if 0 
    {
        int a = 3, b = 5;
        a = a ^ b;
        b = a ^ b;
        a = a ^ b; 
        printf("a is %d, b is %d\n", a , b);
    }
#endif 

#if 0
    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        if (num >= 0) {
            printf("非负数\n");
        }
        else if (num < 0) {
            printf("负数\n");
        }
    }

    {
        int num = 0;
        printf("请输入数字：");
        scanf("%d", &num);
        if (num > 0) {
            printf("正数\n");
        }
        else if (num < 0) {
            printf("负数\n");
        }
        else {
            printf("零\n");
        }
    }

    {
        int num = 0;
        printf("请输入数字：");
        scanf("%d", &num);
        if (num < 0) {
            printf("负数\n");
        }
        else if (num & 1) {
            printf("奇数\n");
        }
        else if (!(num & 1)) {
            printf("偶数\n");
        }
    }

    {
        int num = 0, num1 = 0, num2 = 0;
        printf("请输入三个数字：");
        scanf("%d%d%d", &num, &num1, &num2);
        /*if (num > num1 && num > num2) {
            printf("最大数字是%d\n", num);
        }
        else if (num1 > num && num1 > num2) {
            printf("最大数字是%d\n", num1);
        }
        else if (num2 > num && num2 > num1) {
            printf("最大数字是%d\n", num2);
        }*/
        if (num > num1) {
            if (num > num2) {
                printf("最大数字是%d\n", num);
            }
            else {
                printf("最大数字是%d\n", num2);
            }
        }
        else {
            if (num1 > num2) {
                printf("最大数字是%d\n", num1);
            }
            else {
                printf("最大数字是%d\n", num2);
            }
        }
    }

    {
        int season = 0;
        printf("请输入一个代表季节的数字：");
        scanf("%d", &season);
        switch (season) {
            case 0:
                printf("春天\n");
                break;
            case 1:
                printf("夏天\n");
                break;
            case 2:
                printf("秋天\n");
                break;
            case 3:
                printf("冬天\n");
                break;
            default:
                printf("不认识的数字\n");
                break;
        }
    }

    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        switch (num) {
            case 0:
                printf("假\n");git config --global core.editor "vim"

                break;
            default:
                printf("真\n");
                break;
        }       
    }

    {
        int num = 0;
        for (num = 1;num <= 5;num++) {
            printf("%d ", num);
        }
        printf("\n");
    }

    {
        int num = 0;
        for (num = 1;num <= 5;num++) {
            printf("%d X %d = %d\n", num, 10 - num, num * (10 - num));
        }
    }

    {
        int num = 0;
        for (num = 1;num <= 5;num++) {
            printf("%d\n", num);
            if (num == 3) {
                continue;
            }
            printf("%d\n", 10 + num);
        }
    }

    {
        int num = 0;
        for (num = 0;num <= 40;num++) {
            if (4 * num + 2 * (40 - num) == 100) {
                printf("兔子有%d只，鸡有%d只\n", num, 40 - num);
                break;
            }
        }
        printf("num是%d\n", num); 
    }

    {
        int num = 0, num1 = 0;
        /*for (num = 1;;num++) {
            printf("%d ", num);
        }
        printf("\n");*/
        /*for (num = 1, num1 = 9;num <= num1;num++, num1--) {
            printf("%d X %d = %d\n", num, num1, num * num1);
        }*/
        for (int num2 = 1;num2 <= 5;num2++) {
            printf("%d ", num2);
        }
        printf("\n");
        //printf("num2是%d\n", num2);    错误
    }
#endif 

#if 0
    {
        int min = 0, num = 0;
        printf("请输入一个数字：");
        scanf("%d", &min);
        for (num = min;num <= 100;num++) {
            if (num % 10 == 7) {
            continue; 
            }
            if (num / 10 == 7) {
                continue;
            }
            if (!(num % 7)) {
                continue;
            }
            printf("%d ", num);
        }
        printf("\n");
    }
    
    {
        int num = 0, num1 = 0;
        for (num = 1;num <= 5;num++) {
            for (num1 = 5;num1 >= num;num1--) {
                printf("%d", num1);
            }
            printf("\n");
        }
    }

    {
        int num = 1;
        while (num <= 5) {
            printf("%d ", num);
            num++;
        }
        printf("\n");
    }

    {
        srand(time(0));
        printf("%d\n", rand());
        printf("%d\n", rand());
        printf("%d\n", rand()); 
    }

    {
        int num = 0, num1 = 0;
        for (num = 0;num <= 2;num++) {
            for (num1 = 0;num1 <= 5;num1++) {
                if (5 * num + 2 * num1 <= 10) {
                    printf("5块钱有%d张，2块钱有%d张，1块钱有%d张\n", num, num1, 10 - 5 * num - 2 * num1);
                }
            }
        }
    }

    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        scanf("%*[^\n]");
        scanf("%*c");
        printf("num是%d\n", num);
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("num是%d\n", num);
    }

    {
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        scanf("%*[^\n]");
        scanf("%*c");
        printf("num是%d\n", num);
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("num是%d\n", num);
    }

    {
        int num = 0, guess = 0;
        srand(time(0));
        //num = rand() % 100;
        /*while (num != guess) {
            printf("请猜一个数字：");
            scanf("%d", &guess);
            if (num > guess) {
                printf("猜小了\n");
            }
            else if (num < guess) {
                printf("猜大了\n");
            }
            else {
                printf("猜对了\n");
            }
        }*/
        do {
            printf("请猜一个数字：");
            scanf("%d", &guess);
            if (num > guess) {
                printf("猜小了\n");
            }
            else if (num < guess) {
                printf("猜大了\n");
            }
            else {
                printf("猜对了\n");
            }
        } while (num != guess);
    }

    {
        printf("1");
        fflush(stdout);
        while (1) {
        }
    }

    {
        int num = 0, guess = 0;
        srand(time(0));
        num = rand() % 100;
        for (;;) {
            printf("请猜一个数字：");
            scanf("%d", &guess);
            if (guess > num) {
                printf("猜大了\n");
            }
            else if (guess < num) {
                printf("猜小了\n");
            }
            else {
                printf("猜对了\n");
                break;
            }
        }
    }

    {
        int arr[] = {0, 1, 2, 3, 4};    //数组声明语句
        int num = 0;
        //arr[2] = 10;
        /*for (num = 0;num <= 4;num++) {
            arr[num] = num;
        }*/
        for (num = 4;num >= 0;num--) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    {
        int arr[5] = {0};
        int num = 0, min = 0, sum = 0;
        for (num = 4;num >= 0;num--) {
        printf("请输入一个数字：");
        scanf("%d", &arr[num]);
            if (arr[num] < 0) {
                break;
            }
        }
        min = num + 1;
        for (num = min;num <= 4;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
        for (num = min;num <= 4;num++) {
            sum += arr[num];
        }
        printf("求和结果是%d\n", sum);
    }
#endif

#if 0
    {
        int arr[5][5] = {0};
        int row = 0, col = 0;
        for (row = 0;row <= 4;row++) {
            for (col = 0;col <= 4;col++) {
                if (col == 2) {
                    arr[row][col] = 1;
                }
                else if (row == 2) {
                    arr[row][col] = 2;
                }
                else if (row + col == 4) {
                    arr[row][col] = 3;
                }
                else if (row == col) {
                    arr[row][col] = 4;
                }
            }
        }
        arr[2][2] = 0;
        for (row = 0;row <= 4;row++) {
            for (col = 0;col <= 4;col++) {
                printf("%d", arr[row][col]);
            }
            printf("\n");
        }
    }

    {
        int arr[10][10] = {0};
        int delta[][2] = {-1, -1, -1, 0, -1, 1,
                    0, -1, 0, 1, 1, -1,
                    1, 0, 1, 1};
        int row = 0, col = 0, cnt = 0, num = 0;
        srand(time(0));
        do {
            row = rand() % 10;
            col = rand() % 10;
            if (!arr[row][col]) {
                arr[row][col] = -1;
                cnt++;
            }
        } while (cnt < 10);
        //在二维数组里加入数字
        /*for (row = 0;row <= 9;row++) {
            for (col = 0;col <= 9;col++) {
                if (arr[row][col] == -1) {
                    //排除所有的地雷
                    continue;
                }
                for (num = 0;num <= 7;num++) {
                    int tmp_row = row + delta[num][0];
                    int tmp_col = col + delta[num][1];
                    if (tmp_row < 0 || tmp_row > 9) {
                        continue;
                    }
                    if (tmp_col < 0 || tmp_col > 9) {
                        continue;
                    }
                    if (arr[tmp_row][tmp_col] == -1) {
                        arr[row][col]++;
                    }
                }
            }
        }*/
        for (row = 0;row <= 9;row++) {
            for (col = 0;col <= 9;col++) { 
                if (arr[row][col] != -1) {
                    continue;
                }
                for (num = 0;num <= 7;num++) {
                    int tmp_row = row + delta[num][0];
                    int tmp_col = col + delta[num][1];
                    if (tmp_row < 0 || tmp_row > 9) {
                        continue;
                    }
                    if (tmp_col < 0 || tmp_col > 9) {
                        continue;
                    }
                    if (arr[tmp_row][tmp_col] != -1) {
                        arr[tmp_row][tmp_col]++;
                    }
                }
            }
        }
        for (row = 0;row <= 9;row++) {
            for (col = 0;col <= 9;col++) {
                if (!arr[row][col]) {
                    printf("O");
                }
                else {
                    printf("%d", arr[row][col]);
                }
            }
            printf("\n");
        }
    }
#endif

#if 0
    {
        int arr[7] = {0}, num = 0;
        srand(time(0));
        create(arr, 7);
        for (num = 0;num <= 6;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    {
        func();
        //printf("num是%d\n", num);   错误
        printf("val是%d\n", val);
    }
#endif

#if 0
    {
        int arr[] = {1, 2, 3, 4, 5};
        printf("arr是%p\n", arr);
        printf("arr + 1是%p\n", arr + 1);
        printf("&arr[1]是%p\n", &arr[1]);
        printf("arr - 1是%p\n", arr - 1);
        printf("&arr[3] - arr是%d\n", &arr[3] - arr);
    }

    {
        int arr[] = {1, 2, 3, 4, 5}, num = 0;
        int *p_num = arr;
        for (num = 0;num <= 4;num++) {
            printf("%d ", arr[num]);
            printf("%d ", p_num[num]);
            printf("%d ", *(p_num + num));
        }
        printf("\n");
    }

    {
        int num = 0, num1 = 0, num2 = 0, tmp = 0;
        int *p_num = &num, *p_num1 = &num1, *p_num2 = &num2, *p_tmp = &tmp;
        printf("请输入三个数字：");
        scanf("%d%d%d", p_num, p_num1, p_num2);
        /*if (*p_num > *p_num1) {
            *p_tmp = *p_num;
            *p_num = *p_num1;
            *p_num1 = *p_tmp;
        }
        if (*p_num > *p_num2) {
            *p_tmp = *p_num;
            *p_num = *p_num2;
            *p_num2 = *p_tmp;
        }
        if (*p_num1 > *p_num2) {
            *p_tmp = *p_num1;
            *p_num1 = *p_num2;
            *p_num2 = *p_tmp;
        }*/
        if (*p_num > *p_num1) {
            p_tmp = p_num;
            p_num = p_num1;
            p_num1 = p_tmp;
        }
        if (*p_num > *p_num2) {
            p_tmp = p_num;
            p_num = p_num2;
            p_num2 = p_tmp;
        }
        if (*p_num1 > *p_num2) {
            p_tmp = p_num1;
            p_num1 = p_num2;
            p_num2 = p_tmp;
        }
        printf("%d %d %d\n", *p_num, *p_num1, *p_num2);
    }

    {
        int num = 0;
        int *p_num = &num, *p_num1 = NULL;    //指针声明
        p_num = &num;
        *p_num = 10;
        printf("num是%d\n", num);
    }

    {
        int arr[50] = {0};
        int num = 0;
        printf("请输入一个编号：");
        scanf("%d", &num);
        printf("结果是%d\n", fei(num, arr, 50));
    }

    {
        char ch = 't';
        int num = 23;
        float fnum = 7.5f;
        print(&ch, 0);
        print(&num, 1);
        print(&fnum, 2);
    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        int *p_num = NULL;
        for (p_num = arr;p_num <= arr + 4;p_num++) {
            printf("%d ", *p_num);
        }
        printf("\n");
    }

    {
        int num = 0;
        const int *p_num = &num;
        int * const p_num1 = &num;
        //*p_num = 10;     错误
        p_num = NULL;
        *p_num1 = 10;
        //p_num1 = NULL;     错误
    }

    {
        char ch = 't';
        int num = 10;
        float fnum = 5.4f;
        void *p_v = NULL;    //无类型指针
        p_v = &ch;
        printf("%c\n", *(char *)p_v);
        p_v = &num;
        printf("%d\n", *(int *)p_v);
        p_v = &fnum;
        printf("%g\n", *(float *)p_v);
    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        int num = 0;
        reverse(arr, 5);
        for (num = 0;num <= 4;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    {
        char str[10] = {0};
        printf("请输入一个字符串：");
        //scanf("%s", str);
        fgets(str, 10, stdin);
        if (strlen(str) == 9 && str[8] != '\n') {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        printf("%s\n", str);
        printf("请输入一个字符串：");
        //scanf("%s", str);
        fgets(str, 10, stdin);
        printf("%s\n", str);
    }

    {
    int grade = 0;
    char str[50] = {0},y tmp[10] = {0};
    while (1) {
        printf("请输入一个考试成绩：");
        scanf("%d", &grade);
        if (grade < 0) {
            break;
        }
        sprintf(tmp, "%d,", grade);
        strcat(str, tmp);
    }
    str[strlen(str) - 1] = 0;
    printf("结果是%s\n", str);
    }

    {
        double dnum = 0.0;
        int num = atoi("532da445sg");
        printf("num是%d\n", num);
        dnum = atof("43.65dsgd523dsfg");
        printf("dnum是%lg\n", dnum);
    }

    {
        char str[20] = {0};
        char ch = 0;
        int num = 0;
        float fnum = 0.0f;
        //printf("%d %c %g\n", 34, 't', 5.3f);
        sprintf(str, "%d %c %g\n", 34, 't', 5.3f);
        printf("%s", str);
        //scanf("%c%d%g", &ch, &num, &fnum);
        sscanf("r 23 6.5", "%c%d%g", &ch, &num, &fnum);
        printf("%g %d %c\n", fnum, num, ch);
    }

    {
        char str[10] = "abc";
        printf("有效字符个数是%d\n", strlen(str));
        printf("sizeof(str)是%d\n", sizeof(str));
        printf("%s\n", strcat(str, "xyz"));
        printf("%s\n", str);
        printf("%s\n", strncat(str, "defiop", 3));
        printf("%s\n", str);
        printf("比较结果是%d\n", strcmp("abc", "abd"));
        printf("比较结果是%d\n", strncmp("abc", "abd", 2));
        printf("%s\n", strcpy(str, "abc"));
        printf("%s\n", str);
        printf("%s\n", strncpy(str, "xyziop", 2));
        printf("%s\n", str);
        memset(str, 'h', 9);
        printf("str是%s\n", str);
        printf("%s\n", strstr("abcdefghijklmn", "def"));
    }

    {
        char str[] = "abc";
        printf("%p\n", "abc");
        printf("%p\n", "abc");
        printf("%p\n", "ab""c");
        printf("%c\n", *"abc");
        printf("%d\n", *("abc" + 3));
        //*"abc" = 'x';     错误
        printf("sizeof(str)是%d\n", sizeof(str));
        printf("%s\n", "abc");
    }

    {
        int arr[] = {40, 80, 30, 60, 10, 70, 20};
        int *p_max = max(arr, 7);
        printf("最大数字是%d\n", *p_max); 
    }
#endif

#if 0
    {
        char buf[10] = {0};
        int num = 0;
        for (num = 0;num <= 2;num++) {
            printf("请输入用户名：");
            fgets(buf, 10, stdin);
            if (strlen(buf) == 9 && buf[8] != '\n') {
                scanf("%*[^\n]");
                scanf("%*c");
            }
            if (strcmp(buf, "admin\n")) {
                continue;
            }
            printf("请输入密码：");
            fgets(buf, 10, stdin);
            if (strlen(buf) == 9 && buf[8] != '\n') {
                scanf("%*[^\n]");
                scanf("%*c");
            }
            if (strcmp(buf, "123456\n")) {
                continue;
            }
            break;
        }
        if (num <= 2) {
            printf("登陆成功\n");
        }
        else {
            printf("登陆失败\n");
        }
    }

    {
        char buf[50] = {0};
        char *p_tmp = buf;
        int sum = 0;
        printf("请输入字符串：");
        fgets(buf, 50, stdin);
        while (1) {
            sum += atoi(p_tmp);
            //找到下一个考试成绩的开始位置
            p_tmp = strstr(p_tmp, ",");
            if (!p_tmp) {
                break;
            }
            p_tmp++;
        }
        printf("总成绩是%d\n", sum);
    }

    {
        int order = 0;
        printf("请点菜：");
        scanf("%d", &order);
    #ifdef       ZHAOBENSHAN
        if (order == 2) {
            printf("真没有\n");
        }
        else {
            printf("没有\n");
        }
    #else
        if (order == 2) {
            printf("没有\n");
        }
        else {
            printf("有\n");
        }
    #endif
    }

    {
        //#ifdef    YI
        #ifndef   ER
            printf("1\n");
        #else
            printf("2\n");
        #endif
    }

    {
        #define   STR(n)       #n
        #define   PTR(n)       p_##n
        int num = 0;
        //int *p_num = &num;
        int *PTR(num) = &num;
        STR(2 + 3);
    }

    {
        #define   SQUARE(n)       ((n) * (n))
        int num = 5;
        printf("SQUARE(5)是%d\n", SQUARE(5));
        printf("SQUARE(++num)是%d\n", SQUARE(++num));
    }

    {
        #define   SUB(x, y)        ((x) - (y))    
        printf("SUB(10, 5)是%d\n", SUB(10, 5));
        printf("20 - SUB(10, 5)是%d\n", 20 - SUB(10, 5));
        printf("SUB(20, 10 - 5)是%d\n", SUB(20, 10 - 5));
    }

    {
        #define    ABS(n)       n >= 0 ? n : 0 - n
        #define    NEG(n)       n = 0 - n
        int num = 0;
        printf("请输入一个数字：");
        scanf("%d", &num);
        printf("绝对值是%d\n", abs(num));
        printf("绝对值是%d\n", ABS(num));
        NEG(num);
        printf("num是%d\n", num);
    }

    {
        #define        PI             3.14f
        #define        CIRCLE(r)      2 * PI * r
        int radius = 0;
        printf("请输入半径：");
        scanf("%d", &radius);
        printf("周长是%g\n", CIRCLE(radius));
    }

    {
        int heads = 0, legs = 0, num = 0;
        if (argc < 3) {
            printf("命令错误\n");
            return 0;
        }
        heads = atoi(argv[1]);
        legs = atoi(argv[2]);
        for (num = 0;num <= heads;num++) {
            if (4 * num + 2 * (heads - num) == legs) {
                printf("兔子有%d只,鸡有%d只\n", num, heads - num);
                return 0;
            }
        }
        printf("数字错误\n");
    }

    {
        int SIZE = 10;
        int MAX = 10;
        int arr[SIZE] = {0}, num = 0;
        srand(time(0));
        for (num = 0;num <= SIZE - 1;num++) {
            arr[num] = rand() % MAX + 1;
        }
        for (num = 0;num <= SIZE - 1;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    //#define    PI            3.14f
    {
        int radius = 0;
        float pi = 3.14f;
        printf("请输入半径：");
        scanf("%d", &radius);
        printf("周长是%g\n", 2 * PI * radius);
        printf("周长是%g\n", 2 * pi * radius);
    }

    {
        int num = 0;
        for (num = 0;num <= argc - 1;num++) {
            printf("%s\n", argv[num]);
        }
    }

    {
        char *strs[] = {"abc", "def", "iop",
            "xyz", "vbn"};    //指针数组
        int num = 0;
        for (num = 0;num <= 4;num++) {
            printf("%s\n", strs[num]);
        }
    }
#endif 

#if 0
    {
    /*struct person {
        int age;
        float height;
        char name[10];
    };
    typedef struct person sperson;*/
    typedef struct /*person*/ {
        int age;
        float height;
        char name[10];
    } sperson;

    // struct person prsn;   //结构体变量声明语句
    sperson prsn1 = {20, 1.74f, "abc"};
    sperson prsn2 = {0};
    sperson *p_person = &prsn1;
    printf("请输入年龄：");
    scanf("%d", &(prsn1.age));
    printf("请输入身高：");
    scanf("%g", &(prsn1.height));
    scanf("%*[^\n]");
    scanf("%*c");
    printf("请输入姓名：");
    fgets(prsn1.name, 10, stdin);
    printf("年龄是%d\n", prsn1.age);
    printf("身高是%g\n", prsn1.height);
    printf("姓名是%s\n", prsn1.name);
    prsn2 = prsn1;
    printf("年龄是%d\n", prsn2.age);
    printf("身高是%g\n", prsn2.height);
    printf("姓名是%s\n", prsn2.name);
    printf("年龄是%d\n", p_person->age);
    printf("身高是%g\n", p_person->height);
    printf("姓名是%s\n", p_person->name);
    }

    {
        typedef struct {
            int row;
            int col;
        } pt;
        typedef struct {
            pt pt1;
            pt pt2;
        } rect;
        int area = 0;
        rect r = {0}, *p_r = &r;
        pt mid = {0}, *p_mid = &mid;
        /*printf("请输入水平长方形的位置：");
        scanf("%d%d%d%d", &(r.pt1.row), &(r.pt1.col), &(r.pt2.row), &(r.pt2.col));
        area = (r.pt1.row - r.pt2.row) * (r.pt1.col - r.pt2.col);
        area = area >= 0 ? area : 0 - area;
        printf("面积是%d\n", area);
        mid.row = (r.pt1.row + r.pt2.row) / 2;
        mid.col = (r.pt1.col + r.pt2.col) / 2;
        printf("中间点位置是(%d, %d)\n", mid.row, mid.col);*/
        printf("请输入水平长方形的位置：");
        scanf("%d%d%d%d", &(p_r->pt1.row), &(p_r->pt1.col), &(p_r->pt2.row), &(p_r->pt2.col));
        area = (p_r->pt1.row - p_r->pt2.row) * (p_r->pt1.col - p_r->pt2.col);
        area = area >= 0 ? area : 0 - area;
        printf("面积是%d\n", area);
        p_mid->row = (p_r->pt1.row + p_r->pt2.row) / 2;
        p_mid->col = (p_r->pt1.col + p_r->pt2.col) / 2;
        printf("中心点位置是(%d, %d)\n", p_mid->row, p_mid->col);
    }
#endif 

#if 0
    {
        int num = 0;
        int *p_num = &num;
        int **pp_num = &p_num;   //二级指针
        **pp_num = 10;
        printf("num是%d\n", num);
        *pp_num = NULL;
        printf("p_num是%p\n", p_num);
    }

    {
        typedef union {
            int num;
            float fnum;
        } tmp;   //联合声明
        tmp tmp1 = {0};
        printf("&(tmp1.num)是%p\n", &(tmp1.num));
        printf("&(tmp1.fnum)是%p\n", &(tmp1.fnum));
        printf("sizeof(tmp)是%d\n", sizeof(tmp));
    }

    {
        enum {CHUN, XIA = 5, QIU, DONG};  //枚举声明
        printf("QIU是%d\n", QIU);
    }

    {
        typedef struct {
        char buf[2];
        int num;
        } tmp;
        typedef struct {
            char ch;
            int num;
            char ch1;
        } tmp1;
        printf("sizeof(tmp)是%d\n", sizeof(tmp));
        printf("sizeof(tmp1)是%d\n", sizeof(tmp1));
    }

    {

        rect r = {0}, *p_r = NULL;
        pt mid = {0}, *p_mid = NULL;
        p_r = readdt(&r);
        printf("面积是%d\n", area(p_r));
        p_mid = midpt(&r, &mid);
        printf("中心点位置是(%d, %d)\n", p_mid->row, p_mid->col);
    }

    {
        pt pt1 = {0}, *p_pt = NULL;
        p_pt = read123(&pt1);
        print(&pt1);
        print(p_pt);
    }

    {
        circle cl1 = {{3, 3}, 7}, cl2 = {{4, 5}, 6}, *p_cl = NULL;
        larger(&cl1, &cl2, &p_cl);
        printf("比较大的圆是((%d, %d), %d)\n", p_cl->center.row, p_cl->center.col, p_cl->radius);

    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        //print(arr, 5);
        for_each(arr, 5, print_cb);
        printf("\n");
        for_each(arr, 5, neg_cb);
        for_each(arr, 5, print_cb);
        printf("\n");
    }

    {
        rect r1 = {3, 6, 4, 8}, r2 = {2, 5, 7, 10}, *p_r = NULL;
        larger(&r1, &r2, &p_r);
        printf("面积比较大的长方形是((%d, %d), (%d, %d))\n", p_r->pt1.row, p_r->pt1.col, p_r->pt2.row, p_r->pt2.col);
    }

    {
        int (*p_func)(int, int) = add;   //函数指针声明
        printf("add是%p\n", add);
        printf("结果是%d\n", p_func(3, 8));   
    }

    {
        char ch = 'r';
        char *p_ch = &ch;
        void *p_v = &p_ch;
        printf("%c\n", **(char **)p_v);
    }

    {
        int num = 0;
        for (num = 0;num <= argc - 1;num++) {
            printf("%s\n", *(argv + num));
        }
    }

    {
        char *strs[] = {"abc", "def", "iop",
             "vbn", "xyz"};
        char **pp_str = strs;
        int num = 0;
        for (num = 0;num <= 4;num++) {
            printf("%s\n", strs[num]);
            printf("%s\n", *(pp_str + num));
        }
    }
#endif

#if 0
    {
        int *p_num = NULL, num = 0;
        srand(time(0));
        p_num = (int *)malloc(7 * sizeof(int));
        if (p_num) {
            for (num = 0;num <= 6;num++) {
                *(p_num + num) = rand() % 36 + 1;
            }
            for (num = 0;num <= 6;num++) {
                printf("%d ", *(p_num + num));
            }
            printf("\n");
            free(p_num);
            p_num = NULL;
        }
    }

    {
        int *p_num = (int *)malloc(5 * sizeof(int));
        /*if (p_num) {
            //
            free(p_num);
            p_num = NULL;
        }*/
        if (!p_num) {
            return 0;
        }
        //
        free(p_num);
        p_num = NULL; 
    }

    {
        int arr[][5] = {1, 1, 1, 1, 1,
                        2, 2, 2, 2, 2,
                        3, 3, 3, 3, 3,
                        4, 4, 4, 4, 4,
                        5, 5, 5, 5, 5};
        FILE *p_file = fopen("b.bin", "wb");
        if (p_file) {
            fwrite(arr, sizeof(int), 25, p_file);
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        int arr[5][5] = {0}, num = 0;
        int row = 0, col = 0;
        FILE *p_file = fopen("b.bin", "rb");
        if (p_file) {
            for (num = 4;num >= 0;num--) {
                fread(arr[num], sizeof(int), 5, p_file);
            }
            for (row = 0;row <= 4;row++) {
                for (col = 0;col <= 4;col++) {
                    printf("%d", arr[row][col]);
                }
                printf("\n");
            }
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        int arr[5][5] = {0}, num = 0;
        int row = 0, col = 0;
        FILE *p_file = fopen("b.bin", "rb");
        if (p_file) {
            for (num = 4;num >= 0;num--) {
                fread(arr[num], sizeof(int), 5, p_file);
            }
            for (row = 0;row <= 4;row++) {
                for (col = 0;col <= 4;col++) {
                    printf("%d", arr[row][col]);
                }
                printf("\n");
            }
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        int num = 0, val = 0;
        FILE *p_file = fopen("abc.txt", "r");
        if (p_file) {
            for (num = 0;num <= 4;num++) {
                fscanf(p_file, "%d", &val);
                printf("%d ", val);
            }
            printf("\n");
            fclose(p_file);
            p_file =  NULL;
        }
    }

    {
        char buf[10] = {0};
        int arr[] = {10, 20, 30, 40, 50}, num = 0;
        FILE  *p_file = fopen("abc.txt", "w");
        //FILE  *p_file = fopen("abc.txt", "wb");
        if (p_file) {
            for (num = 0;num <= 4;num++) {
                /*sprintf(buf, "%d ", arr[num]);
                fwrite(buf, sizeof(char), strlen(buf), p_file);*/
                fprintf(p_file, "%d ", arr[num]);
            }
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        int arr[] = {1, 2, 3, 4, 5}, size = 0;
        FILE *p_file = fopen("a.bin", "wb");
        if (p_file) {
            size = fwrite(arr, sizeof(int), 5, p_file);
            printf("size是%d\n", size);
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        FILE *p_file = fopen("a.txt", "w");
        /*if (p_file) {
            fclose(p_file);
            p_file = NULL;
        }*/
        if (!p_file) {
            return 0;
        }
        fclose(p_file);
        p_file = NULL;
    }

    {
        int arr[5] = {0}, num = 0, size = 0;
        FILE *p_file = fopen("a.bin", "rb");
        if (p_file) {
            size = fread(arr, sizeof(int), 5, p_file);
            printf("size是%d\n", size);
            for (num = 0;num <= 4;num++) {
                printf("%d ", arr[num]);
            }
            printf("\n");
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        rect *p_r = read();
        pt *p_pt = NULL;
        if (!p_r) {
            return 0;
        }
        p_pt = midpt2(p_r);
        if (!p_pt) {
            free(p_r);
            p_r = NULL;
            return 0;
        }
        printf("中心点位置是(%d, %d)\n", p_pt->row, p_pt->col);
        free(p_pt);
        p_pt = NULL;
        free(p_r);
        p_r = NULL;
    }

    {
        int *p_num = NULL, num = 0;
        srand(time(0));
        p_num = create2(7);
        if (p_num) {
            for (num = 0;num <= 6;num++) {
                printf("%d ", *(p_num + num));
            }
            printf("\n");
            free(p_num);
            p_num = NULL;
        }
    }

#endif 
    {
        int choice = 0;
        person prsn = {0};
        FILE *p_file = fopen("person.bin", "ab");
        if (p_file) {
            while (1) {
                printf("请输入id:");
                scanf("%d", &(prsn.id));
                printf("请输入工资：");
                scanf("%g", &(prsn.salary));
                scanf("%*[^\n]");
                scanf("%*c");
                printf("请输入姓名：");
                fgets(prsn.name, 10, stdin);
                fwrite(&prsn, sizeof(person), 1, p_file);
                printf("是否需要输入下一个人员信息？0表示不输入，1表示要输入");
                scanf("%d", &choice);
                if (!choice) {
                    break;
                }
            }
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
    int choice = 0, id = 0, size = 0, flag = 0;
    person prsn = {0};
    FILE *p_file = fopen("person.bin", "a+b");
    if (p_file) {
        while (1) {
            printf("请输入id:");
            scanf("%d", &(prsn.id));
            flag = 0;
            rewind(p_file);
            while (1) {
                size = fread(&id, sizeof(int), 1, p_file);
                if (!size) {
                    break;
                }
                if (id == prsn.id) {
                    flag = 1;
                    break;
                }
                fseek(p_file, sizeof(person) - sizeof(int), SEEK_CUR);
            }
            //fseek(p_file, 0, SEEK_END);
            if (flag) {
                continue;
            }
            printf("请输入工资：");
            scanf("%g", &(prsn.salary));
            scanf("%*[^\n]");
            scanf("%*c");
            printf("请输入姓名：");
            fgets(prsn.name, 10, stdin);
            fwrite(&prsn, sizeof(person), 1, p_file);
            printf("是否需要输入下一个人员信息？0表示不输入，1表示要输入");
            scanf("%d", &choice);
            if (!choice) {
                break;
            }
            }
            fclose(p_file);
            p_file = NULL;    
        }
    }

    {
        char ch = 0;
        FILE *p_file = fopen("abc.txt", "rb");
        if (p_file) {
            //rewind(p_file);
            fseek(p_file, 2, SEEK_SET);
            printf("位置指针数值是%ld\n", ftell(p_file));
            fread(&ch, sizeof(char), 1, p_file);
            printf("ch是%c\n", ch);
            //rewind(p_file);
            fseek(p_file, 4, SEEK_CUR);
            printf("位置指针数值是%ld\n", ftell(p_file));
            fread(&ch, sizeof(char), 1, p_file);
            printf("ch是%c\n", ch);
            //rewind(p_file);
            fseek(p_file, -3, SEEK_END);
            printf("位置指针数值是%ld\n", ftell(p_file));
            fread(&ch, sizeof(char), 1, p_file);
            printf("ch是%c\n", ch);
            fclose(p_file);
            p_file = NULL;
        }
    }

    {
        FILE *p_src = NULL, *p_dest = NULL;
        char buf[100] = {0};
        int size = 0;
        if (argc < 3) {
            printf("命令错误\n");
            return 0;
        }
        p_src = fopen(argv[1], "rb");
        if (!p_src) {
            printf("原始文件打开失败\n");
            return 0;
        }
        p_dest = fopen(argv[2], "wb");
        if (!p_dest) {
            printf("新文件打开失败\n");
            fclose(p_src);
            p_src = NULL;
            return 0;
        }
        while (1) {
            size = fread(buf, sizeof(char), 100, p_src);
            if (!size) {
                break;
            }
            fwrite(buf, sizeof(char), size, p_dest);
        }
        fclose(p_dest);
        p_dest = NULL;
        fclose(p_src);
        p_src = NULL;
    }

    return 0;
}
