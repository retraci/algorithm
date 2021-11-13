#include <bits/stdc++.h>
using namespace std;

int va[6][6], cor[13][2], q[6];
int ans = 0;

int getsum(int x, int y)
{
    //值为0的不用计算
    if (va[x][y] == 0) return 0;
    //算过一次就要清零，避免重复
    va[x][y] = 0;
    //超出范围也没事，因为va数组的周围都是0
    return 1 + getsum(x - 1, y) + getsum(x + 1, y) + getsum(x, y - 1) + getsum(x, y + 1);
}

void dfs(int dep, int last) {
    if (dep == 5) {
        memset(va, 0, sizeof(va));
        for (int i = 0; i < 5; i++) {
            va[cor[q[i]][0]][cor[q[i]][1]] = 1;
        }
        if (getsum(cor[last][0], cor[last][1]) == 5) ans++;
        return;
    }
    for (int i = last + 1; i <= 12; i++) {
        //q数组保存我们选中的格子
        q[dep] = i;
        dfs(dep + 1, i);
        q[dep] = -1;
    }
}

int main()
{
    //算出第n个格子的横纵坐标
    for (int i = 1, n = 1; i <= 3; i++) {
        for (int j = 1; j <= 4; j++, n++) {
            cor[n][0] = i; cor[n][1] = j;
        }
    }
    dfs(0, 0);
    printf("%d\n", ans);
    return 0;
}