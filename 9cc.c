#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // 初めの引数が何かを確認した
    char *a = argv[0];
    fprintf(stdout, "argv[0]='%s'\n", a);

    //引数の個数が正しいかの確認
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    char *p = argv[1];

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("  mov rax, %ld\n", strtol(p, &p, 10));

    // ０個以上の項があるため、順に読みだしている。
    // strtolは一文字読み出すことに第２引数をインクリメントしている。
    while(*p) {
        if(*p == '+') {
            p++;
            printf("    add rax, %ld\n", strtol(p, &p, 10));
            continue;
        }

        if (*p == '-')
        {
            p++;
            printf("    sub rax, %ld\n", strtol(p, &p, 10));
            continue;
        }

        // 最後まで進んでしまうことはないため、エラーとする。
        fprintf(stderr, "予期しない文字です：　'%c'\n", *p);
        return 1;
    }

    printf("  ret\n");
    return 0;
}
