/*
 * =======================================
 *  C 语言数组
 * =======================================
 */

#include <stdio.h>

static void define_array(void) {
    // 定义数组
    int array1[4] = {1, 2, 4, 5};
    int array2[] = {1, 2, 4, 5};

    // 推荐：数组的所有元素都被初始化为 0。
    int array3[5] = {0};

    // C99 可以指定初始化某个元素
    int days[7] = {[6] = 6};

    // 定义多维数组
    int multiArr1[][4] = {{4}, {4}}; //直接初始化
    int multiArr2[3][4]; // 同时指定行列数

    // 在 C99 之前的标准（如 C89/C90）中，数组的长度必须是常量表达式，不能在运行时动态确定。
    // C99 标准之后这种数组是变长数组，需要注意的是，虽然 C99 标准引入了变长数组，但并不是所有的编译器都完全支持这一特性。
    int n = 3;
    char crumbs[n];
}

// 使用数组作为参数，可以指定长度也可以不指定长度，使用 const 修饰参数，可以防止 array 所指向的内容被修改。
static void const_array(const int array[]) {
    // 不合法
    // array[0] = 3;
}

static void variable_array1(const int length) {
    int n; // 数组的大小
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n]; // 声明一个大小为 n 的数组

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("You entered the following elements:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 变长数组，C99 之前，二维数组传参，必须指定数组的维度，C99 开始可以使用变长数组，变长数组必须使用自动变量。
static void variable_array2(int rows, int cols, int arr[rows][cols]) {
    for (int i = 0; i < cols; ++i) {}
}

int main() {
    define_array();
    variable_array1(4);
}
