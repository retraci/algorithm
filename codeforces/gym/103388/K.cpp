#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int T, D, M;
vector<int> va;

void solve() {
    va.push_back(0), va.push_back(D);
    sort(va.begin(), va.end());

    int flag = 0;
    for (int i = 1; i < va.size(); i++) {
        flag |= (va[i] - va[i - 1]) >= T;
    }
    cout << (flag ? "Y" : "N") << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T >> D >> M;
    for (int i = 1; i <= M; i++) {
        int a;
        cin >> a;
        va.push_back(a);
    }
    solve();

    return 0;
}