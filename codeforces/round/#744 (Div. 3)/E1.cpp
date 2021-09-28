#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;

const int N = 2e5 + 10;

int n;
int va[N];

void solve() {
    deque<int> que;
    que.push_back(va[0]);
    for (int i = 1; i < n; i++) {
        if (va[i] < que.front()) que.push_front(va[i]);
        else que.push_back(va[i]);
    }

    for (auto x : que) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}