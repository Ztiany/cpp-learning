/*
 ============================================================================
 
 Author      : Ztiany
 Description : 内联函数

 ============================================================================
 */

/*声明内联函数*/
inline int add(int a, int b) {
    return a + b;
}

int main(){
    add(1, 2);
    return 0;
}