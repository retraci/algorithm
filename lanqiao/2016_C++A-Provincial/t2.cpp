// 生日蜡烛

#include <bits/stdc++.h>

using namespace std;

int n;

void solve() {
    n = 236;
    for (int s = 0; s < 100; s++) {
        int sum = 0;
        for (int j = s; ; j++) {
            sum += j;
            if (sum > n) break;
            if (sum == n) {
                cout << s << endl;
                return;
            }
        }
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();
//  正解
//    for (int i = 0; i < 100; ++i) {
//        int sum = 0;
//        for (int j = i; j < 100; ++j) {
//            sum += j;
//            if (sum > 236)break;
//            if (sum == 236)cout << i << "->" << j << endl;
//        }
//    }

    return 0;
}