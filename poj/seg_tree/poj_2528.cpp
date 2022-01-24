// POJ 2528 Mayor's posters
/*
	思路：
	线段树 + 离散化 
	染色问题 
	
	node:
	离散化数组 lsh.size = maxn * 3 
	步骤：
	排序，unique去重，计算个数
	如果间隔 >1 添加新点 n++
	排序，造映射表  
	
	染色问题， -1 表示多种颜色， 0 表示没颜色 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define mid (left+(right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

struct Node {
	int left, right, sum, lz;
	Node(int l_, int r_, int s_, int lz_) {
		left = l_, right = r_, sum = s_, lz = lz_;
	}
};

const int maxn = 10010;

int n, tot, ans;
int ls[maxn], rs[maxn], lsh[maxn*3];
int vis[maxn*3];
vector<Node> tree;

void print_tree() {
	cout << endl;
	for(int i = 0; i < tree.size(); i++) {
		printf("%d %d %d\n", tree[i].left, tree[i].right, tree[i].sum);
	}
	cout << endl;
}

void push_up(int node) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(tree[lson].sum == tree[rson].sum) {
		tree[node].sum = tree[lson].sum;
	} else {
		tree[node].sum = -1;
	}
}

void push_down(int node) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(tree[node].lz) {
		tree[lson].sum = tree[lson].lz = tree[node].lz;
		tree[rson].sum = tree[rson].lz = tree[node].lz;
		tree[node].lz = 0;
	}
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;

	if(left == right) return;

	build(lson, left, mid);
	build(rson, mid+1, right);
	push_up(node);
}

void update(int node, int L, int R, int val) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right < L || left > R) return;
	if(L<=left && right<=R) {
		tree[node].sum = val;
		tree[node].lz = val;
		return;
	}

	push_down(node);
	update(lson, L, R, val);
	update(rson, L, R, val);
	push_up(node);
}

void query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right < L || left > R) return;
	if(L<=left && right<=R) {
		int color = tree[node].sum;
		if(color != -1) {
			if(color!=0 && !vis[color]) {
				ans++;
				vis[color] = 1;
			}
		} else {
			push_down(node);
			query(lson, L, R);
			query(rson, L, R);
		}
		return;
	}

	push_down(node);
	query(lson, L, R);
	query(rson, L, R);
}

void solve() {
	sort(lsh, lsh+tot);
	// 去重
	int m = unique(lsh, lsh+tot) - lsh;
	int t = m;
	for(int i = 1; i < t; i++) {
		if(lsh[i]-lsh[i-1] > 1) {
			lsh[m++] = lsh[i-1] + 1;
		}
	}
	
	tree = vector<Node>(m*4, Node(0,0,0,0));
	build(0, 0, m-1);
	// 排序拿映射表 
	sort(lsh, lsh+m);
	for(int i = 0; i < n; i++) {
		// 找 ls[i] rs[i] 的下标当作映射 
		int left = lower_bound(lsh, lsh+m, ls[i]) - lsh;
		int right = lower_bound(lsh, lsh+m, rs[i]) - lsh;
		// 涂色    从 1 开始 
		update(0, left, right, i+1);
	}
	
	ans = 0;
	memset(vis, 0, sizeof(vis));
	query(0, 0, m-1);
	cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		tot = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &ls[i], &rs[i]);
			lsh[tot++] = ls[i];
			lsh[tot++] = rs[i];
		}
		solve();
	}

	return 0;
}
