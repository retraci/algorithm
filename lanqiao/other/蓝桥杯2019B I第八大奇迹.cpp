// 蓝桥杯2019B I第八大奇迹
/*
	思路：
	线段树
	树套 vector + merge
*/

#include <bits/stdc++.h>

using namespace std;

#define mid (left + (right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

const int maxn = 100010;

struct Node {
	int left, right;
	vector<int> v;
	Node(int l_, int r_) {
		left = l_, right = r_;
		v.resize(8);
	}
};

int n, m;
vector<Node> tree;

void push_up(vector<int> &v, const vector<int> &v1, const vector<int> &v2) {
	int k = 0, i = 0, j = 0;

	while(i < 8 && j < 8 && k < 8) {
		if(v1[i] > v2[j]) {
			v[k++] = v1[i++];
		} else {
			v[k++] = v2[j++];
		}
	}
	while(k < 8 && i < 8) v[k++] = v1[i++];
	while(k < 8 && j < 8) v[k++] = v2[j++];
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;

	if(left == right) return;
	build(lson, left, mid);
	build(rson, mid+1, right);
}

void update(int node, int idx, int val) {
	int left = tree[node].left;
	int right = tree[node].right;
	
	if(idx < left || idx > right) return;

	if(left == right && left == idx) {
		tree[node].v[0] = val;
		return;
	}
	update(lson, idx, val);
	update(rson, idx, val);

	push_up(tree[node].v, tree[lson].v, tree[rson].v);
}

vector<int> query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(L <= left && right <= R) {
		return tree[node].v;
	}
	if(R <= mid) return query(lson, L, R);
	if(mid+1 <= L) return query(rson, L, R);
	
	vector<int> v = vector<int>(8, 0);
	push_up(v, query(lson, L, R), query(rson, L, R));

	return v;
}

void solve() {
	tree = vector<Node>(4*n, Node(0, 0));
	build(0, 0, n-1);

	char op;
	int a, b;
	while(m--) {
		cin >> op >> a >> b;
		if(op == 'C') {
			update(0, a-1, b);
		} else if(op == 'Q') {
			cout << query(0, a-1, b-1)[7] << endl;
		}
	}
//	cout << endl;
//	if(m == -1) {
//		for(int i = 0; i < 4*n; i++) {
//			printf("%d %d %d\n", tree[i].left, tree[i].right, tree[i].v[7]);
//		}
//	}
}

int main() {
	cin >> n >> m;
	solve();

	return 0;
}
