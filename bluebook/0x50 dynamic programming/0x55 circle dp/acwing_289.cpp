#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;

const int N = 2e6 + 10;

int n;
int va[N];
deque<int> q;

void solve() {
    for (int i = 0; i < n; i++) {
        va[i + n] = va[i];
    }

    int ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        while (!q.empty() && i - q.front() > n / 2) q.pop_front();
        if (!q.empty()) ans = max(ans, i - q.front() + va[i] + va[q.front()]);
        while (!q.empty() && va[q.back()] - q.back() <= va[i] - i) q.pop_back();
        q.push_back(i);
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &va[i]);
    }
    solve();

    return 0;
}