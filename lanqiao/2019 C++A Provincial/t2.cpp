// 数列求值

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1e4;

int n = 20190324;

void solve() {
    int a1 = 1, a2 = 1, a3 = 1;

    for (int i = 4; i <= n; i++) {
        int n3 = (a1 + a2 + a3) % MOD;
        int n2 = a3, n1 = a2;

        a1 = n1, a2 = n2, a3 = n3;
    }

    cout << a3 << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}