// region e-dcc
int e[M * 4], ne[M * 4], h1[N], h2[N], edm;

void add(int h[], int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfn[N], low[N], ti;
vector<int> stk;
int co[N], sz[N], dcc;
int br[M * 2];

void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u);

    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = e[i];
        if ((i ^ 1) == pe) continue;

        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u]) br[i] = br[i ^ 1] = 1;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        dcc++;
        int t;
        do {
            t = stk.back(); stk.pop_back();
            co[t] = dcc;
            sz[dcc]++;
        } while (t != u);
    }
}
// endregion

// region v-dcc
int e[M * 4], ne[M * 4], h1[N], h2[N], edm;

void add(int h[], int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfn[N], low[N], ti, rt;
vector<int> stk;
vector<int> cc[N];
int cut[N], dcc;

void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u);

    if (u == rt && h1[u] == -1) {
        dcc++;
        cc[dcc].push_back(u);
        return;
    }

    int cnt = 0;
    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = e[i];
        if ((i ^ 1) == pe) continue;

        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                if (++cnt >= 2 || u != rt) cut[u] = 1;

                dcc++;
                int t;
                do {
                    t = stk.back(); stk.pop_back();
                    cc[dcc].push_back(t);
                } while (t != v);
                cc[dcc].push_back(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
// endregion
