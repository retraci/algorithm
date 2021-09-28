#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int location;
    int v;
    int is;
    int live;

} Czr;

Czr *creat(int n);

void move(Czr *czrs, int n, int *num);

void check(Czr *czrs, int n);

int cnt(Czr *czrs, int n);

int main() {
    int n, sum, num;
    printf("n=");
    scanf("%d", &n);
    Czr *czrs;
    czrs = creat(n);
    num = n;

    while (num != 0) {
        move(czrs, n, &num);
        //printf("num=%d",num);
    }

    sum = cnt(czrs, n);

    printf("共有%d只陈梓锐感染猪瘟\n", sum);

    system("pause");
    return 0;
}

Czr *creat(int n) {
    Czr *czrs;
    czrs = (Czr *) malloc(sizeof(Czr) * n);
    int xyer;

    for (int i = 0; i < n; i++) {
        czrs[i].v = 1;
        czrs[i].is = 0;
        czrs[i].live = 1;
        printf("%d:", i + 1);
        scanf("%d", &czrs[i].location);

    }

    printf("xyer:");
    scanf("%d", &xyer);
    czrs[xyer - 1].is = 1;

    return czrs;
}

void move(Czr *czrs, int n, int *num) {
    for (int i = 0; i < n; i++) {
        if (czrs[i].location == 0 || czrs[i].location == 100) {
            czrs[i].location = 200;
            czrs[i].live = 0;
            *num = *num - 1;

        }
    }

    check(czrs, n);
    for (int i = 0; i < n; i++) {
        if (czrs[i].live == 1) {
            czrs[i].location++;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("czrs[%d]=%d ", i, czrs[i].location);

    }
    printf("\n");
}

void check(Czr *czrs, int n) {
    for (int i = 0; i < n - 1; i++) {
        // 遍历检查是否有相碰
        for (int j = i + 1; j < n; j++) {
            // 如果相碰
            if (czrs[i].location + czrs[j].location == -1 || czrs[i].location + czrs[j].location == -2) {
                czrs[i].location *= -1;
                czrs[j].location *= -1;
                if (czrs[i].is == 1 || czrs[j].is == 1) {
                    czrs[i].is = czrs[j].is = 1;

                }
                check(czrs, n);
            }
        }

    }
}

int cnt(Czr *czrs, int n) {
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (czrs[i].is == 1) {
            cnt++;
        }

    }

    return cnt;
}