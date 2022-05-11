int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

pii e[M * 2];
int ne[M * 2], h[N], edm;

void add(int u, int v, int cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}