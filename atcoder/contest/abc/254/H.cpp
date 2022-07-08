#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n;
int a[N], b[N];

void solve() {
    priority_queue<int> q1(a + 1, a + n + 1), q2(b + 1, b + n + 1);

    int cnt = 0;
    while (!q1.empty()) {
        if (q1.top() == q2.top()) {
            q1.pop(), q2.pop();
        } else if (q1.top() > q2.top()) {
            cnt++;
            int x = q1.top(); q1.pop();
            q1.push(x >> 1);
        } else {
            cnt++;
            int x = q2.top(); q2.pop();
            if (x & 1) {
                cout << -1 << "\n";
                return;
            }
            q2.push(x >> 1);
        }
    }

    cout << cnt << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}