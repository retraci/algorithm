#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 110;

int n;
vector<pii> va, vb;
int ans[N];

void solve() {
    va.clear(), vb.clear();
    for (int i = 2; i <= n; i++) {
        cout << "? ";
        for (int j = 1; j <= n - 1; j++) cout << i << " ";
        cout << 1 << endl;
        cout.flush();

        int id;
        cin >> id;
        if (id == 0) continue;
        va.push_back({id, i - 1});
    }

    for (int i = 2; i <= n; i++) {
        cout << "? ";
        for (int j = 1; j <= n - 1; j++) cout << 1 << " ";
        cout << i << endl;
        cout.flush();

        int id;
        cin >> id;
        if (id == 0) continue;
        vb.push_back({id, -(i - 1)});
    }

    ans[n] = va.size() + 1;
    for (auto &[k, v] : va) {
        ans[k] = ans[n] - v;
    }
    for (auto &[k, v] : vb) {
        ans[k] = ans[n] - v;
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
    cout.flush();
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n;
    solve();

    return 0;
}