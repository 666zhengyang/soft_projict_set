/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-28 11:40:31
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-28 12:31:10
 */
#include <stdio.h>
#include <stdlib.h>

void insert(int *p_num, int size, int val) {
    int num = 0, val1 = val, tmp = 0;
    for (num = 0;num <= size - 1;num++) {
        if (*(p_num + num) > val1) {
            tmp = *(p_num + num);
            *(p_num + num) = val1;
            val1 = tmp;
        }
        else if (!*(p_num + num)) {
            *(p_num + num) = val1;
            break;
        }
    }
}

#define SIZE 10
typedef struct {
    int buf[SIZE];
    int qty;    //栈里的数字个数
} stack;

void stack_init(stack *p_stack) {
    p_stack->qty = 0;
}
//栈的清理函数
void stack_deinit(stack *p_stack) {
    p_stack->qty = 0;
}
//获得有效数字个数的函数
int stack_size(const stack *p_stack) {
    return p_stack->qty;
}
//判断栈是不是满了
int stack_full(const stack *p_stack) {
    return p_stack->qty >= SIZE;
}
//判断栈是不是空的
int stack_empty(const stack *p_stack) {
    return !(p_stack->qty);
}
//向栈里加入数字的函数
int stack_push(stack *p_stack, int num) {
    if (p_stack->qty >= SIZE) {
        return 0;
    }
    p_stack->buf[p_stack->qty] = num;
    p_stack->qty++;
    return 1;
}
//从栈里获得数字的函数(同时删除数字)
int stack_pop(stack *p_stack, int *p_num) {
    if (!(p_stack->qty)) {
        return 0;
    }
    *p_num = p_stack->buf[p_stack->qty - 1];
    p_stack->qty--;
    return 1;
}
//从栈里获得数字的函数(不会删除数字)
int stack_top(const stack *p_stack, int *p_num) {
    if (!(p_stack->qty)) {
        return 0;
    }
    *p_num = p_stack->buf[p_stack->qty - 1];
    return 1;
}

typedef struct {
    int buf[SIZE];
    int head;    //最前一个数字所在存储区的下标
    int tail;    //最后一个数字的后一个存储区的下标
    //如果队列里没有数字的时候head应该等于tail
} queue;

void queue_init(queue *p_queue) {
    p_queue->head = 0;
    p_queue->tail = 0;
}
//队列的清理函数
void queue_deinit(queue *p_queue) {
    p_queue->head = 0;
    p_queue->tail = 0;
}
//判断队列是否空的函数
int queue_empty(const queue *p_queue) {
    return p_queue->head == p_queue->tail;
}
//判断队列是否满的函数
int queue_full(const queue *p_queue) {
    return p_queue->tail >= SIZE;
}
//获得有效数字个数的函数
int queue_size(const queue *p_queue) {
    return p_queue->tail - p_queue->head;
}
//向队列里加入数字的函数
int queue_push(queue *p_queue, int val) {
    if (p_queue->tail >= SIZE) {
        return 0;
    }
    p_queue->buf[p_queue->tail] = val;
    p_queue->tail++;
    return 1;
}

//从队列里获得数字的函数(会把数字从队列里删除)
int queue_pop(queue *p_queue, int *p_num) {
    if (p_queue->head == p_queue->tail) {
        return 0;
    }
    *p_num = p_queue->buf[p_queue->head];
    p_queue->head++;
    return 1;
}
//从队列里获得数字的函数(不会把数字从队列里删除)
int queue_front(const queue *p_queue, int *p_num) {
    if (p_queue->head == p_queue->tail) {
        return 0;
    }
    *p_num = p_queue->buf[p_queue->head];
    return 1;
}

typedef struct node {
    int num;
    struct node *p_next;
} node;
typedef struct {
    node head, tail;
} link;

//链表的初始化函数
void link_init(link *p_link) {
    p_link->head.p_next = &(p_link->tail);
    p_link->tail.p_next = NULL;
}
//链表的清理函数
void link_deinit(link *p_link) {
    while (p_link->head.p_next != &(p_link->tail)) {
        node *p_first = &(p_link->head);
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        p_first->p_next = p_last;
        free(p_mid);
        p_mid = NULL;
    }
}
//判断链表是否空的函数
int link_empty(const link *p_link) {
    return p_link->head.p_next == &(p_link->tail);
}
//判断链表是否满的函数
int link_full(const link *p_link) {
    return 0;
}
//统计有效数字个数的函数
int link_size(const link *p_link) {
    int cnt = 0;
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail)) {
            cnt++;
        }
    }
    return cnt;
}
//在最前面插入新数字的函数
int link_add_head(link *p_link, int num) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    node *p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    //新结点插入到p_first和p_mid中间
    p_first->p_next = p_tmp;
    p_tmp->p_next = p_mid;
    return 1;
}
//在最后插入新数字的函数
int link_append(link *p_link, int num) {
    node *p_node = NULL;
    node *p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid == &(p_link->tail)) {
            p_first->p_next = p_tmp;
            p_tmp->p_next = p_mid;
            break;
        }
    }
    return 1;
}
//把数字按照顺序插入到链表的函数
int link_insert(link *p_link, int num) {
    node *p_node = NULL;
    node *p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid == &(p_link->tail) || p_mid->num > p_tmp->num) {
            p_first->p_next = p_tmp;
            p_tmp->p_next = p_mid;
            break;
        }
    }
    return 1;
}
//删除最前面数字的函数
int link_remove_head(link *p_link) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    p_first->p_next = p_last;
    free(p_mid);
    p_mid = NULL;
    return 1;
}
//删除最后一个有效数字
int link_remove_tail(link *p_link) {
    node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_last == &(p_link->tail)) {
            p_first->p_next = p_last;
            free(p_mid);
            p_mid = NULL;
            return 1;
        }
    }
    return 0;
}
//删除某个给定数字的函数
int link_remove(link *p_link, int num) {
    node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail) && p_mid->num == num) {
            p_first->p_next = p_last;
            free(p_mid);
            p_mid = NULL;
            return 1;
        }
    }
    return 0;
}

//获得第一个有效数字的函数
int link_get_head(const link *p_link, int *p_num) {
    const node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    *p_num = p_mid->num;
    return 1;
}
//获得最后一个有效数字的函数
int link_get_tail(const link *p_link, int *p_num) {
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_last == &(p_link->tail)) {
            *p_num = p_mid->num;
            return 1;
        }
    }
    return 0;
}
//获得指定编号数字的函数
int link_get(const link *p_link, int *p_num, int num) {
    int cnt = 0;
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail) && cnt == num) {
            *p_num = p_mid->num;
            return 1;
        }
        cnt++;
    }
    return 0;
}

struct tree_node;
typedef struct {
    struct tree_node *p_node;
} tree;
typedef struct tree_node {
    int num;
    tree left;
    tree right;
} tree_node;

//树的初始化函数
void tree_init(tree *p_tree) {
    p_tree->p_node = NULL;
}
//树的清理函数
void tree_deinit(tree *p_tree) {
    if (!(p_tree->p_node)) {
        return ;
    }
    tree_deinit(&(p_tree->p_node->left));
    tree_deinit(&(p_tree->p_node->right));
    free(p_tree->p_node);
    p_tree->p_node = NULL;
}
//在有序二叉树里查找某个数字的位置
tree *tree_search(const tree *p_tree, int num) {
    if (!(p_tree->p_node)) {
        return (tree *)p_tree;
    }
    if (p_tree->p_node->num == num) {
        return (tree *)p_tree;
    }
    else if (p_tree->p_node->num > num) {
        return tree_search(&(p_tree->p_node->left), num);
    }
    else {
        return tree_search(&(p_tree->p_node->right), num);
    }
}
//向有序二叉树里加入数字的函数
int tree_insert(tree *p_tree, int num) {
    tree *p_tmp = NULL;
    tree_node *p_node = (tree_node *)malloc(sizeof(tree_node));
    if (!p_node) {
        return 0;
    }
    p_node->num = num;
    p_node->left.p_node = NULL;
    p_node->right.p_node = NULL;
    p_tmp = tree_search(p_tree, num);
    if (p_tmp->p_node) {
        free(p_node);
        p_node = NULL;
    }
    else {
        p_tmp->p_node = p_node;
    }
}
//从小到大显示有序二叉树里所有数字
/*void tree_print(const tree *p_tree) {
    if (!(p_tree->p_node)) {
        return ;
    }
    tree_print(&(p_tree->p_node->left));
    printf("%d ", p_tree->p_node->num);
    tree_print(&(p_tree->p_node->right));
}*/
//中序遍历函数
void tree_miter(const tree *p_tree, void (*p_func)(int)) {
    if (!(p_tree->p_node)) {
        return ;
    }
    tree_miter(&(p_tree->p_node->left), p_func);
    p_func(p_tree->p_node->num);
    tree_miter(&(p_tree->p_node->right), p_func);
}

//计算高度的函数
int tree_height(const tree *p_tree) {
    int left_height = 0, right_height = 0;
    if (!(p_tree->p_node)) {
        return 0;
    }
    left_height = tree_height(&(p_tree->p_node->left));
    right_height = tree_height(&(p_tree->p_node->right));
    return (left_height > right_height ? left_height : right_height) + 1;
}
//删除数字的函数
int tree_remove(tree *p_tree, int num) {
    tree_node *p_node = NULL;
    tree *p_tmp = tree_search(p_tree, num);
    if (!(p_tmp->p_node)) {
        return 0;
    }
    p_node = p_tmp->p_node;
    //把要删除的结点从树里摘出来
    if (!(p_node->left.p_node) && !(p_node->right.p_node)) {
        //左右子树都不存在
        p_tmp->p_node = NULL;
    }
    else if (!(p_node->left.p_node)) {
        //左子树不存在
        p_tmp->p_node = p_node->right.p_node;
    }
    else if (!(p_node->right.p_node)) {
        //右子树不存在
        p_tmp->p_node = p_node->left.p_node;
    }
    else {
        //左右子树都存在
        //把左右子树合并成一个有序二叉树
        tree *p_tmp1 = tree_search(&(p_node->right), p_node->left.p_node->num);   //在右子树里查找左子树根结点所应该插入的位置
        p_tmp1->p_node = p_node->left.p_node; //把左子树的根结点插入到右子树里
        p_tmp->p_node = p_node->right.p_node;  //用右子树的根结点替换要删除的结点
    }
    free(p_node);   //释放要删除的结点
    p_node = NULL;
    return 1;
}

void print_cb(int num) {
    printf("%d ", num);
}

//快速排序函数
void quick_sort(int *p_num, int size) {
    int base = *p_num, tmp = 0;
    int *p_start = p_num, *p_end = p_num + size - 1;
    if (size <= 1) {
        return ;
    }
    while (p_start < p_end) {
        //交换p_start指针和p_end指针
        //所捆绑的存储区内容
        if (*p_start > *p_end) {
            tmp = *p_start;
            *p_start = *p_end;
            *p_end = tmp;
        }
        if (*p_start != base) {
            //如果p_start指针捆绑的存储区
            //内容不是选定数字就把p_start
            //指针向后移动一步
            p_start++;
        }
        else {
            //如果p_end指针捆绑的存储区
            //内容不是选定数字就把p_end
            //指针向前移动一步
            p_end--;
        }
    }
    //递归调用quick_sort函数对左半边数字
    //进行排序
    quick_sort(p_num, p_start - p_num);
    //递归调用quick_sort函数对右半边数字
    //进行排序
    quick_sort(p_start + 1, size - (p_start - p_num) - 1);
}
//插入排序函数
void insert_sort(int *p_num, int size) {
    int num = 0, num1 = 0, tmp = 0;
    for (num = 1;num <= size - 1;num++) {
        //把下标为num的存储区里的数字插入
        //到前面的数字里合适的位置上
        for (num1 = num - 1;num1 >= 0;num1--) {
            //调整下标为num1和num1 + 1
            //两个存储区里数字的顺序
            if (*(p_num + num1) > *(p_num + num1 + 1)) {
                tmp = *(p_num + num1);
                *(p_num + num1) = *(p_num + num1 + 1);
                *(p_num + num1 + 1) = tmp;
            }
            else {
                break;
            }
        }
    }
}
//选择排序函数
void choice_sort(int *p_num, int size) {
    int num = 0, num1 = 0, tmp = 0;
    for (num = size - 1;num >= 1;num--) {
        //把合适的数字放在下标为num
        //的存储区里
        for (num1 = 0;num1 <= num - 1;num1++) {
            //调整下标为num1和num两个
            //存储区里的数字的顺序
            if (*(p_num + num1) > *(p_num + num)) {
                tmp = *(p_num + num1);
                *(p_num + num1) = *(p_num + num);
                *(p_num + num) = tmp;
            }
        }
    }
}
//冒泡排序函数
void bubble_sort(int *p_num, int size) {
    int num = 0, num1 = 0, tmp = 0;
    for (num = size - 1;num >= 1;num--) {
        //每次循环要把合适的数字放在下标
        //为num的存储区里
        for (num1 = 0;num1 <= num - 1;num1++) {
            //把下标为num1和num1 + 1的两个
            //数字进行顺序调整
            if (*(p_num + num1) > *(p_num + num1 + 1)) {
                tmp = *(p_num + num1);
                *(p_num + num1) = *(p_num + num1 + 1);
                *(p_num + num1 + 1) = tmp;
            }
        }
    }
}

int *half_search(const int *p_num, int size, int num) {
    const int *p_start = p_num, *p_end = p_num + size - 1;
    while (p_start <= p_end) {
        //计算中间点存储区的位置
        const int *p_mid = p_start + (p_end - p_start + 1) / 2;
        if (*p_mid == num) {
            //中间点位置的数字就是要查找
            //的数字
            return (int *)p_mid;
        }
        else if (*p_mid > num) {
            //中间点的数字比要查找的
            //数字大，这个时候应该
            //排除右半边数字
            p_end = p_mid - 1;
        }
        else {
            //中间点的数字比要查找的
            //数字小，这个时候应该排除
            //左半边数字
            p_start = p_mid + 1;
        }
    }
    return NULL;
}

#if 0
typedef struct node {
    int num;
    struct node *p_pre;
    struct node *p_next;
} node;

typedef struct {
    node head, tail;
    node *p_cur;
} link;
//链表的初始化函数
void link_init(link *p_link) {
    p_link->head.p_next = &(p_link->tail);
    p_link->tail.p_next = NULL;
    p_link->tail.p_pre = &(p_link->head);
    p_link->head.p_pre = NULL;
    p_link->p_cur = NULL;
}
//链表的清理函数
void link_deinit(link *p_link) {
    p_link->p_cur = NULL;
    while (p_link->head.p_next != &(p_link->tail)) {
        node *p_first = &(p_link->head);
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        p_first->p_next = p_last;
        p_last->p_pre = p_first;
        free(p_mid);
        p_mid = NULL;
    }
}
//判断链表是否空的函数
int link_empty(const link *p_link) {
    return p_link->head.p_next == &(p_link->tail);
}
//判断链表是否满的函数
int link_full(const link *p_link) {
    return 0;
}
//统计有效数字个数的函数
int link_size(const link *p_link) {
    int cnt = 0;
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail)) {
            cnt++;
        }
    }
    return cnt;
}
//在最前面插入新数字的函数
int link_add_head(link *p_link, int num) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    node *p_tmp = NULL;
    p_link->p_cur = NULL;
    p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    p_tmp->p_pre = NULL;
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    //新结点插入到p_first和p_mid中间
    p_first->p_next = p_tmp;
    p_tmp->p_next = p_mid;
    p_mid->p_pre = p_tmp;
    p_tmp->p_pre = p_first;
    return 1;
}
//在最后插入新数字的函数
int link_append(link *p_link, int num) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    node *p_tmp = NULL;
    p_link->p_cur = NULL;
    p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    p_tmp->p_pre = NULL;
    p_first = p_link->tail.p_pre;
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    //加入新结点
    p_first->p_next = p_tmp;
    p_tmp->p_next = p_mid;
    p_mid->p_pre = p_tmp;
    p_tmp->p_pre = p_first;
    return 1;
}
/*int link_append(link *p_link, int num) {
    node *p_node = NULL;
    node *p_tmp = NULL;
    p_link->p_cur = NULL;
    p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    p_tmp->p_pre = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid == &(p_link->tail)) {
            p_first->p_next = p_tmp;
            p_tmp->p_next = p_mid;
            p_mid->p_pre = p_tmp;
            p_tmp->p_pre = p_first;
            break;
        }
    }
    return 1;
}*/
//把数字按照顺序插入到链表的函数
int link_insert(link *p_link, int num) {
    node *p_node = NULL;
    node *p_tmp = NULL;
    p_link->p_cur = NULL;
    p_tmp = (node *)malloc(sizeof(node));
    if (!p_tmp) {
        return 0;
    }
    p_tmp->num = num;
    p_tmp->p_next = NULL;
    p_tmp->p_pre = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid == &(p_link->tail) || p_mid->num > p_tmp->num) {
            p_first->p_next = p_tmp;
            p_tmp->p_next = p_mid;
            p_mid->p_pre = p_tmp;
            p_tmp->p_pre = p_first;
            break;
        }
    }
    return 1;
}
//删除最前面数字的函数
int link_remove_head(link *p_link) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    p_link->p_cur = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    p_first->p_next = p_last;
    p_last->p_pre = p_first;
    free(p_mid);
    p_mid = NULL;
    return 1;
}
//删除最后一个有效数字
int link_remove_tail(link *p_link) {
    node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    p_link->p_cur = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = p_link->tail.p_pre->p_pre;
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    //让p_mid指针捆绑结点脱离链表
    p_first->p_next = p_last;
    p_last->p_pre = p_first;
    free(p_mid);
    p_mid = NULL;
    return 1;
}
/*int link_remove_tail(link *p_link) {
    node *p_node = NULL;
    p_link->p_cur = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_last == &(p_link->tail)) {
            p_first->p_next = p_last;
            p_last->p_pre = p_first;
            free(p_mid);
            p_mid = NULL;
            return 1;
        }
    }
    return 0;
}*/
//删除某个给定数字的函数
int link_remove(link *p_link, int num) {
    node *p_node = NULL;
    p_link->p_cur = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        node *p_first = p_node;
        node *p_mid = p_first->p_next;
        node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail) && p_mid->num == num) {
            p_first->p_next = p_last;
            p_last->p_pre = p_first;
            free(p_mid);
            p_mid = NULL;
            return 1;
        }
    }
    return 0;
}
//获得第一个有效数字的函数
int link_get_head(const link *p_link, int *p_num) {
    const node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = &(p_link->head);
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    *p_num = p_mid->num;
    return 1;
}
//获得最后一个有效数字的函数
int link_get_tail(const link *p_link, int *p_num) {
    const node *p_first = NULL, *p_mid = NULL, *p_last = NULL;
    if (p_link->head.p_next == &(p_link->tail)) {
        return 0;
    }
    p_first = p_link->tail.p_pre->p_pre;
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    *p_num = p_mid->num;
    return 1;
}
/*int link_get_tail(const link *p_link, int *p_num) {
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_last == &(p_link->tail)) {
            *p_num = p_mid->num;
            return 1;
        }
    }
    return 0;
}*/
//获得指定编号数字的函数
int link_get(const link *p_link, int *p_num, int num) {
    int cnt = 0;
    const node *p_node = NULL;
    for (p_node = &(p_link->head);p_node != &(p_link->tail);p_node = p_node->p_next) {
        const node *p_first = p_node;
        const node *p_mid = p_first->p_next;
        const node *p_last = p_mid->p_next;
        if (p_mid != &(p_link->tail) && cnt == num) {
            *p_num = p_mid->num;
            return 1;
        }
        cnt++;
    }
    return 0;
}
//开始从前向后遍历链表的函数
void link_begin(link *p_link) {
    p_link->p_cur = &(p_link->head);
}
//在遍历过程中获得下一个数字的函数
int link_next(link *p_link, int *p_num) {
    if (!(p_link->p_cur)) {
        return 0;
    }
    p_link->p_cur = p_link->p_cur->p_next;
    if (p_link->p_cur == &(p_link->tail)) {
        p_link->p_cur = NULL;
        return 0;
    }
    else {
        *p_num = p_link->p_cur->num;
        return 1;
    }
}
#endif

int main()
{
    {
        int arr[10] = {10, 20, 30, 40, 50, 60, 70}, num = 0;
        insert(arr, 10, 35);
        for (num = 0;num <= 9;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    {
        node node1 = {1}, node2 = {5}, node3 = {10}, head = {0}, tail = {0}, *p_node = NULL;
        head.p_next = &node1;
        node1.p_next = &node2;
        node2.p_next = &node3;
        node3.p_next = &tail;
        for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
            //p_node指针循环变量从头结点开始
            //一直捆绑到最后一个有效结点
            node *p_first = p_node;
            node *p_mid = p_first->p_next;
            node *p_last = p_mid->p_next;
            //以上三个指针和三个相邻结点
            //捆绑，p_first指针捆绑的结点
            //在最前面，p_last指针捆绑的结点
            //在最后面
            //p_mid指针从第一个有效结点捆绑
            //到尾结点
            if (p_mid != &tail) {
                printf("%d ", p_mid->num);
            }
        }
        printf("\n");
    }

    {
        int cnt = 0;
        node head = {0}, tail = {0}, node1 = {1}, node2 = {5}, node3 = {10};
        node node4 = {7}, *p_node = NULL;
        head.p_next = &node1;
        node1.p_next = &node2;
        node2.p_next = &node3;
        node3.p_next = &tail;
        for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
            node *p_first = p_node;
            node *p_mid = p_first->p_next;
            node *p_last = p_mid->p_next;
            if (p_mid == &tail || p_mid->num > node4.num) {
                p_first->p_next = &node4;
                node4.p_next = p_mid;
                break;
            }
        }
        for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
            node *p_first = p_node;
            node *p_mid = p_first->p_next;
            node *p_last = p_mid->p_next;
            if (p_mid != &tail && p_mid->num == 5) {
                p_first->p_next = p_last;
                break;
            }
        }
        for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
            node *p_first = p_node;
            node *p_mid = p_first->p_next;
            node *p_last = p_mid->p_next;
            if (p_mid != &tail) {
                printf("%d ", p_mid->num);
            }
        }
        printf("\n");
        for (p_node = &head;p_node != &tail;p_node = p_node->p_next) {
            node *p_first = p_node;
            node *p_mid = p_first->p_next;
            node *p_last = p_mid->p_next;
            if (p_mid != &tail && cnt == 2) {
                printf("编号为2的数字是%d\n", p_mid->num);
                break;
            }
            cnt++;
        }
    }

    {
        int val = 0;
        stack stk = {0};
        stack_init(&stk);
        printf("判断空的结果是%d\n", stack_empty(&stk));
        printf("判断满的结果是%d\n", stack_full(&stk));
        printf("数字个数是%d\n", stack_size(&stk));
        stack_push(&stk, 10);
        stack_push(&stk, 30);
        stack_push(&stk, 50);
        printf("判断空的结果是%d\n", stack_empty(&stk));
        printf("判断满的结果是%d\n", stack_full(&stk));
        printf("数字个数是%d\n", stack_size(&stk));
        stack_push(&stk, 70);
        stack_push(&stk, 90);
        printf("判断空的结果是%d\n", stack_empty(&stk));
        printf("判断满的结果是%d\n", stack_full(&stk));
        printf("数字个数是%d\n", stack_size(&stk));
        stack_top(&stk, &val);
        printf("最后一个数字是%d\n", val);
        stack_pop(&stk, &val);
        printf("%d ", val);
        stack_pop(&stk, &val);
        printf("%d ", val);
        stack_pop(&stk, &val);
        printf("%d\n", val);
        printf("判断空的结果是%d\n", stack_empty(&stk));
        printf("判断满的结果是%d\n", stack_full(&stk));
        printf("数字个数是%d\n", stack_size(&stk));
        stack_push(&stk, 100);
        stack_push(&stk, 120);
        stack_pop(&stk, &val);
        printf("%d ", val);
        stack_pop(&stk, &val);
        printf("%d ", val);
        stack_pop(&stk, &val);
        printf("%d ", val);
        stack_pop(&stk, &val);
        printf("%d\n", val);
        stack_deinit(&stk);
        printf("判断空的结果是%d\n", stack_empty(&stk));
        printf("判断满的结果是%d\n", stack_full(&stk));
        printf("数字个数是%d\n", stack_size(&stk));
    }

    {
        int val = 0;
        queue que = {0};
        queue_init(&que);
        printf("判断空的结果是%d\n", queue_empty(&que));
        printf("判断满的结果是%d\n", queue_full(&que));
        printf("数字个数是%d\n", queue_size(&que));
        queue_push(&que, 10);
        queue_push(&que, 20);
        queue_push(&que, 30);
        queue_push(&que, 40);
        printf("判断空的结果是%d\n", queue_empty(&que));
        printf("判断满的结果是%d\n", queue_full(&que));
        printf("数字个数是%d\n", queue_size(&que));
        queue_front(&que, &val);
        printf("最前面的数字是%d\n", val);
        queue_pop(&que, &val);
        printf("%d ", val);
        queue_pop(&que, &val);
        printf("%d ", val);
        queue_pop(&que, &val);
        printf("%d\n", val);
        printf("判断空的结果是%d\n", queue_empty(&que));
        printf("判断满的结果是%d\n", queue_full(&que));
        printf("数字个数是%d\n", queue_size(&que));
        queue_push(&que, 50);
        queue_push(&que, 60);
        printf("判断空的结果是%d\n", queue_empty(&que));
        printf("判断满的结果是%d\n", queue_full(&que));
        printf("数字个数是%d\n", queue_size(&que));
        queue_pop(&que, &val);
        printf("%d ", val);
        queue_pop(&que, &val);
        printf("%d ", val);
        queue_pop(&que, &val);
        printf("%d\n", val);
        printf("判断空的结果是%d\n", queue_empty(&que));
        printf("判断满的结果是%d\n", queue_full(&que));
        printf("数字个数是%d\n", queue_size(&que));
        queue_deinit(&que);
    }


    {
        int size = 0, num = 0, val = 0;
        link lnk = {0};
        link_init(&lnk);
        link_add_head(&lnk, 30);
        link_add_head(&lnk, 20);
        link_append(&lnk, 90);
        link_append(&lnk, 100);
        link_insert(&lnk, 50);
        link_insert(&lnk, 60);
        link_insert(&lnk, 40);
        link_insert(&lnk, 80);
        link_insert(&lnk, 70);
        link_remove_head(&lnk);
        link_remove_tail(&lnk);
        link_remove(&lnk, 70);
        size = link_size(&lnk);
        for (num = 0;num <= size - 1;num++) {
            link_get(&lnk, &val, num);
            printf("%d ", val);
        }
        printf("\n");
        link_get_head(&lnk, &val);
        printf("最前面的数字是%d\n", val);
        link_get_tail(&lnk, &val);
        printf("最后面的数字是%d\n", val);
        link_deinit(&lnk);
    }
    
#if 0
    {
        int size = 0, num = 0, val = 0;
        link lnk = {0};
        link_init(&lnk);
        link_add_head(&lnk, 30);
        link_add_head(&lnk, 20);
        link_append(&lnk, 90);
        link_append(&lnk, 100);
        link_insert(&lnk, 50);
        link_insert(&lnk, 60);
        link_insert(&lnk, 40);
        link_insert(&lnk, 80);
        link_insert(&lnk, 70);
        link_remove_head(&lnk);
        link_remove_tail(&lnk);
        link_remove(&lnk, 70);
        size = link_size(&lnk);
        /*for (num = 0;num <= size - 1;num++) {
            link_get(&lnk, &val, num);
            printf("%d ", val);
        }*/
        link_begin(&lnk);
        while (1) {
            if (link_next(&lnk, &val)) {
                printf("%d ", val);
            }
            else {
                break;
            }
        }
        printf("\n");
        link_get_head(&lnk, &val);
        printf("最前面的数字是%d\n", val);
        link_get_tail(&lnk, &val);
        printf("最后面的数字是%d\n", val);
        link_deinit(&lnk);
    }
#endif

    {
        tree tr = {0};
        tree_init(&tr);
        tree_insert(&tr, 50);
        tree_insert(&tr, 30);
        tree_insert(&tr, 80);
        tree_insert(&tr, 15);
        tree_insert(&tr, 40);
        tree_insert(&tr, 65);
        tree_insert(&tr, 91);
        tree_insert(&tr, 57);
        tree_insert(&tr, 85);
        tree_miter(&tr, print_cb);
        printf("\n");
        printf("高度是%d\n", tree_height(&tr));
        tree_remove(&tr, 80);
        printf("高度是%d\n", tree_height(&tr));
        tree_deinit(&tr);
    }

    {
        int arr[] = {50, 30, 80, 60, 20, 40, 10};
        int num = 0;
        //bubble_sort(arr, 7);
        //choice_sort(arr, 7);
        //insert_sort(arr, 7);
        quick_sort(arr, 7);
        for (num = 0;num <= 6;num++) {
            printf("%d ", arr[num]);
        }
        printf("\n");
    }

    {
        int arr[] = {10, 20, 30, 40, 50, 60,
          70, 80, 90};
        int *p_num = half_search(arr, 9, 80);
        if (p_num) {
            printf("数字是%d\n", *p_num);
        }
    }
    return 0;
}