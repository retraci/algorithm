#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 30010;

int n, m;
int va[N], vu[N];

priority_queue<int> que1;
priority_queue<int, vector<int>, greater<>> que2;

int work(int x) {
    while (que1.size() < x) que1.push(que2.top()), que2.pop();
    while (!que1.empty() && !que2.empty() && que1.top() > que2.top()) {
        int tp1 = que1.top(); que1.pop();
        int tp2 = que2.top(); que2.pop();
        que1.push(tp2), que2.push(tp1);
    }

    return que1.top();
}

void solve() {
    int j = 1, idx = 0;
    for (int i = 1; i <= n; i++) {
        que2.push(va[i]);
        while (j <= m && i == vu[j]) cout << work(++idx) << "\n", j++;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= m; i++) cin >> vu[i];
    solve();

    return 0;
}