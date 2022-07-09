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
const int N = 200010;

int n, k;
int a[N];

void solve() {
    set<int> st;
    for (int i = 1; i <= n; i++) st.insert(i);

    vector<int> stk;
    int need = 1;
    for (int i = 1; i <= k; i++) {
        stk.push_back(a[i]);
        while (!stk.empty() && need == stk.back()) {
            st.erase(stk.back());
            stk.pop_back();
            need++;
        }
    }

    if (!is_sorted(stk.rbegin(), stk.rend())) {
        cout << -1 << "\n";
        return;
    }
    for (int i = 1; i <= k; i++) cout << a[i] << " ";
    while (!st.empty()) {
        auto it = st.find(stk.back());

        if (it != st.begin()) {
            it = prev(it);
            while (1) {
                if (it == st.begin()) {
                    cout << *it << " ";
                    st.erase(it);
                    break;
                }

                auto pit = prev(it);
                cout << *it << " ";
                st.erase(it);

                it = pit;
            }
        }

        st.erase(stk.back());
        stk.pop_back();
    }
    cout << "\n";
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
        cin >> n >> k;
        for (int i = 1; i <= k; i++) cin >> a[i];
        solve();
    }

    return 0;
}