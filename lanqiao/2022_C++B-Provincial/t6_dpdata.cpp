#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

void solve() {
    srand(time(0));
    int T = 100;
    cout << T << "\n";
    for (int i = 1; i <= T; i++) {
        int n = rand() % 100 + 1, m = rand() % 100 + 1;
        long long K = rand() * rand();
        cout << n << " " << m << " " << K << "\n";
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                cout << rand() << " ";
            }
            cout << "\n";
        }
    }
}

int main() {
    freopen("../dp.in", "w", stdout);

    solve();

    return 0;
}
