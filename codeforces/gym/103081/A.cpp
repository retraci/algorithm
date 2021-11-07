#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

const int N = 100010;

int n, K;
string ss[N];
unordered_map<string, int> cnt;
unordered_map<string, int> last;
vector<pii> va;

void solve() {
    for (int i = 1; i <= n; i++) cnt[ss[i]]++;
    for (int i = 1; i <= n; i++) last[ss[i]] = i;

    for (auto &[s, _]: cnt) {
        int c = cnt[s], id = last[s];
        va.push_back({c, id});
    }

    sort(va.begin(), va.end(), [&](pii &a, pii &b) {
        auto &[c1, id1] = a;
        auto &[c2, id2] = b;

        if (c1 == c2) return id1 > id2;
        else return c1 > c2;
    });

    for (int i = 0; i < K && i < va.size(); i++) {
        auto &[_, id] = va[i];
        cout << ss[id] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    n *= 3;
    getline(cin, ss[0]);
    for (int i = 1; i <= n; i++) getline(cin, ss[i]);
//    for (int i = 1; i <= n; i++) cout << ss[i] << endl;
    solve();

    return 0;
}