// region trie
template<int SZ>
struct Trie {
    int ne[SZ + 10][26], cnt[SZ + 10], mem;

    Trie() {}

    void init(int _n) {
        fill(&ne[0][0], &ne[_n][25] + 1, 0);
        fill(cnt, cnt + _n + 1, 0);
        mem = 0;
    }

    void ins(string &s) {
        int u = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) v = ++mem;
            u = v;
        }

        cnt[u]++;
    }

    int qr(string &s) {
        int u = 0, res = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) break;
            u = v;
            res += cnt[u];
        }

        return res;
    }
};
// endregion

// region 01trie
template<int SZ>
struct Trie {
    int ne[SZ + 10][2], cnt[SZ + 10], mem;

    Trie() {}

    void init(int _n) {
        fill(&ne[0][0], &ne[_n][1] + 1, 0);
        fill(cnt, cnt + _n + 1, 0);
        mem = 0;
    }

    void ins(int x) {
        int u = 0;
        for (int i = __lg(x); i >= 0; i--) {
            int bi = x >> i & 1;
            int &v = ne[u][bi];
            if (!v) v = ++mem;
            u = v;
        }

        cnt[u]++;
    }

    int qr(int x) {
        int u = 0, res = 0;
        for (int i = __lg(x); i >= 0; i--) {
            int bi = x >> i & 1;
            if (ne[u][!bi]) {
                res += 1 << i;
                u = ne[u][!bi];
            } else {
                u = ne[u][bi];
            }
        }

        return res;
    }
};
// endregion
