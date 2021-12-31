#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2510;

int n, m, K;
int xs[N], ys[N];
vector<int> lsh1, lsh2;

int get_id1(int x) { return lower_bound(lsh1.begin(), lsh1.end(), x) - lsh1.begin() + 1; }
int get_id2(int x) { return lower_bound(lsh2.begin(), lsh2.end(), x) - lsh2.begin() + 1; }

void init() {
    lsh1.push_back(0), lsh2.push_back(0);
    lsh1.push_back(n), lsh2.push_back(m);
    lsh1.push_back(n - 1), lsh2.push_back(m - 1);
    for (int i = 1; i <= K; i++) {
        lsh1.push_back(xs[i]), lsh1.push_back(xs[i] - 1);
        lsh2.push_back(ys[i]), lsh2.push_back(ys[i] - 1);
    }
    sort(lsh1.begin(), lsh1.end());
    sort(lsh2.begin(), lsh2.end());
    lsh1.resize(unique(lsh1.begin(), lsh1.end()) - lsh1.begin());
    lsh2.resize(unique(lsh2.begin(), lsh2.end()) - lsh2.begin());
}

void solve() {
    for (int i = 1; i <= K; i++) {
        if (xs[i] == 0 && ys[i] == 0) {
            cout << "No" << "\n";
            return;
        }
    }

    init();
    set<pii> st;
    for (int i = 1; i <= K; i++) {
        int id1 = get_id1(xs[i]), id2 = get_id2(ys[i]);
        st.insert({id1, id2});
    }
    int tn = lsh1.size(), tm = lsh2.size();
    int f[tn + 1][tm + 1];
    memset(f, 0, sizeof f);
    f[get_id1(0)][get_id2(0)] = 1;
    for (int i = 1; i <= tn; i++) {
        for (int j = 1; j <= tm; j++) {
            if (st.count({i, j})) continue;

            f[i][j] |= f[i - 1][j] || f[i][j - 1];
        }
    }

    cout << (f[get_id1(n)][get_id2(m)] ? "Yes" : "No") << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> K;
    for (int i = 1; i <= K; i++) cin >> xs[i] >> ys[i];
    solve();

    return 0;
}