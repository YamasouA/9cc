#include "9cc.h"

//main関数の引数の　argc: コマンドライン引数の数, **argvはコマンドライン引数　が格納される
int main(int argc, char **argv) {
    if (argc != 2) 
        error("引数の個数が正しくありません");


    //トークナイズしてパースする
    user_input = argv[1];
    token = tokenize();
    Node *node = expr();

    //アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");

    //抽象構文木を下りながらコードを生成
    gen(node);

    //スタックトップに式全体の値が残っているはずなので
    //それをRAXにロードして関数からの返り値とする
    printf("  pop rax\n");
    printf("  ret\n");
    return 0;
}