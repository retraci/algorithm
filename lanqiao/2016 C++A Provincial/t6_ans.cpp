/*
dfs搜索
*/
#include<bits/stdc++.h>
using namespace std;

bool book[15];
int a[15];
int ans = 0;

void dfs(int dep)
{
    if (dep == 13) {
        //必须整除，变成乘法判断
        if (a[10] == a[11] * a[12]) ans++;
        return;
    }
    if (dep == 10) {
        if (a[7] * a[8] != a[9]) return;
    }
    if (dep == 7) {
        if (a[4] - a[5] != a[6]) return;
    }
    if (dep == 4) {
        if (a[1] + a[2] != a[3]) return;
    }
    for (int i = 1; i <= 13; i++) {
        if (!book[i]) {
            book[i] = true;
            a[dep] = i;
            dfs(dep + 1);
            a[dep] = -1;
            book[i] = false;
        }
    }
}

int main() {
    dfs(1);
    cout << ans << endl;

    return 0;
}