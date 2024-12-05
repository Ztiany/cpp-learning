/*
 * =======================================
 *  指针学习
 * =======================================
 */

#include <stdio.h>

/**
 * @param pointer 指向 float[4]的指针。
 * @param i 查询的位置。
 * @return 该函数返回一个 float 类型的指针。
 */
static float* search(const float (*pointer)[4], const int i) {
    // pointer + i 移动的是 i*sizeof(float[4]) 个字节
    // 取出第 i 个 float[4] 的首地址返回
    return *(pointer + i);
}

static void demo() {
    const float score[][4] = {
        {66, 77, 88, 99},
        {666, 727, 868, 994},
        {666, 757, 848, 939},
        {166, 277, 188, 199}
    };

    // 有一个指针 ps，指向一个一维数组
    const float (*ps)[4] = score;

    int i, k;
    scanf("%d %d", &i, &k);
    const float* p = search(score, k);
    printf("%f", *(p + i));
}

static void const_pointer() {
    /*
     * 声明常量指针：
     *
     *  - 常量指针指向的对象不能通过这个指针来修改。
     *  - 指针还可以指向别处，因为指针本身只是个变量，可以指向任意地址，所以叫常量指针，是限制了通过这个指针修改变量的值。
     */
    int const* p1 = NULL;
    const int* p2 = NULL;

    // *p1 = 3; // 错误
    p1 = p2; // 允许

    /*
     * 声明指针常量：
     *
     *  - 指针常量是一个指针，还有常量的特性。指针常量的值是指针，这个值因为是常量，所以不能被赋值。
     *  - 指针本身是常量，指向的地址不可以变化，但是指向的地址所对应的内容可以变化。
     */
    int i1 = 3;
    int* const p3 = &i1;
    *p3 = 1; // 允许
    // p3 = p2; // 错误
}

/**
 * 两个指针变量做比较运算（`>、>=、<、<=、==、!=`）表示什么意义？指针之间的比较运算比的是地址，C 语言正是这样规定的，只有
 * 指向同一个数组中元素的指针之间相互比较才有意义，否则没有意义。
 */
static void pointer_compare(void) {

}

int main(void) {
    demo();
}
