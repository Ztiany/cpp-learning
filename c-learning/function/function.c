/*
 * =======================================
 *  C 语言函数
 * =======================================
 */

// 如果自建的函数写在 main 函数的后面，需要在 main 函数之前声明这个函数。
static int inner_function();

// 声明的时候可以不写参数名，所以 void function_with_parameter(char, int); 也是可以的
void function_with_parameter(char name, int x);

int main() {
    inner_function();
    function_with_parameter('a', 1);
}

//静态函数只能在内部调用
static int inner_function() {
    return 0;
}

void function_with_parameter(char name, int x) {}

// C99 支持的内联函数
inline int swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
