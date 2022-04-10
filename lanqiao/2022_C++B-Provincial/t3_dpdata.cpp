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
    int T = 1000;
    cout << T << "\n";
    for (int i = 1; i <= T; i++) {
        cout << rand() + 1 << " " << rand() + 1 << " " << rand() + 1 << "\n";
    }
}

int main() {
    freopen("../dp.in", "w", stdout);

    solve();

    return 0;
}
