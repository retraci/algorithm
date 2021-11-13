// 跳蚱蜢

#include <bits/stdc++.h>

using namespace std;

map<string, int> vis;

void solve() {
    string s = "012345678";
    string t = "087654321";

    queue<string> que;
    que.push(s);
    int step = 0;
    while (que.size()) {
        int sz = que.size();
        step++;

        for (int i = 0; i < sz; i++) {
            string cur = que.front(); que.pop();

            if (vis[cur]) continue;
            vis[cur] = 1;

            if (cur == t) {
                cout << step - 1 << endl;
                return;
            }

            int idx = -1;
            for (int i = 0; i < cur.size(); i++) if (cur[i] == '0') idx = i;

            int a = (idx + 1) % 9;
            int b = (idx + 2) % 9;
            int c = (idx - 1 + 9) % 9;
            int d = (idx - 2 + 9) % 9;

            string ns = cur;
            swap(ns[idx], ns[a]);
            que.push(ns);
            swap(ns[idx], ns[a]);

            swap(ns[idx], ns[b]);
            que.push(ns);
            swap(ns[idx], ns[b]);

            swap(ns[idx], ns[c]);
            que.push(ns);
            swap(ns[idx], ns[c]);

            swap(ns[idx], ns[d]);
            que.push(ns);
            swap(ns[idx], ns[d]);
        }
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}