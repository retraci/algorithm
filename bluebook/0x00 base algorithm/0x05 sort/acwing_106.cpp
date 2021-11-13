#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 1e4 + 10;

int n, m;
int va[maxn];
priority_queue<int> que1;
priority_queue<int, vector<int>, greater<int>> que2;

void solve() {
    cout << m << " " << (n+1) / 2 << endl;

    while (!que1.empty()) que1.pop();
    while (!que2.empty()) que2.pop();

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (que2.empty() || va[i] > que2.top()) {
            que2.push(va[i]);
        } else {
            que1.push(va[i]);
        }
        while (que1.size() > que2.size()) {
            int tmp = que1.top(); que1.pop();
            que2.push(tmp);
        }
        while (que2.size() - que1.size() > 1) {
            int tmp = que2.top(); que2.pop();
            que1.push(tmp);
        }

        if ((i+1) & 1) {
            printf("%d ", que2.top());
            cnt++;
        }
        if (cnt == 10) {
            cnt = 0;
            puts("");
        }
    }

    if (cnt != 0) puts("");
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d", &m, &n);
        for (int i = 0; i < n; i++) scanf("%d", &va[i]);
        solve();
    }

    return 0;
}

