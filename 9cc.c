#include <stdio.h>
#include <stdlib.h>

//main関数の引数の　argc: コマンドライン引数の数, **argvはコマンドライン引数　が格納される
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    printf("    mov rax, %d\n", atoi(argv[1])); //atoi: 文字列をintに変換
    printf("    ret\n");
    return 0;
}