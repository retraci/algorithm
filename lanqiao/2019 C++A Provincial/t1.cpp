// 平方和

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

bool check(int x) {
    while (x) {
        int cur = x % 10;
        if (cur == 2 || cur == 0 || cur == 1 || cur == 9) return true;
        x /= 10;
    }

    return false;
}

void solve() {
    long long sum = 0;
    for (int i = 1; i <= 2019; i++) {
        if (check(i)) sum += i * i;
    }

    cout << sum << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}