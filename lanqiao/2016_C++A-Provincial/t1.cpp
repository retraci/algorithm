// 网友年龄

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int ans = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            int fa = i * 10 + j;
            int son = fa - 27;
            if (son < 0) continue;
            if (son == j * 10 + i) ans++;
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

//    正解
//    int count = 0;
//    for (int Dad = 27; Dad < 100; ++Dad) {
//        int Son = Dad - 27;
//        int t = Dad % 10 * 10 + Dad / 10;
//        if (t == Son)count++;
//    }
//    cout << count << endl;

    return 0;
}