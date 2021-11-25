#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
int va[N];

void solve() {
    deque<int> qi, qo;
    for (int i = 1; i <= n; i++) qi.push_back(va[i]);

    int id = max_element(va + 1, va + 1 + n) - va;

    if (id != 1 && id != n) {
        cout << -1 << endl;
        return;
    }

    for (int k = 1; k <= n; k++) {
        if (qi.front() > qi.back()) {
            qo.push_front(qi.front());
            qi.pop_front();
        } else {
            qo.push_back(qi.back());
            qi.pop_back();
        }
    }

    while (!qo.empty()) {
        cout << qo.front() << " ";
        qo.pop_front();
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}