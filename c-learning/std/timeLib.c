/*
 * =======================================
 *  time.h
 * =======================================
 */

# include <stdio.h>
# include <time.h>
# include <stdlib.h>

/**
 * time.h 是 C 标准函数库中获取时间与日期、对时间与日期数据操作及格式化的头文件。
 */
int main(void) {
    const time_t timer = time(NULL);
    printf("ctime is %s\n", ctime(&timer));
    return EXIT_SUCCESS;
}
