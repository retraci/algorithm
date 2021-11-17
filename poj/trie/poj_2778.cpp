// POJ 2778 DNA Sequence
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MOD = 100000;

int m,n;
int trie[110][4],fail[110],flag[110],tn;

int get_idx(char c) {
	if(c=='A') return 0;
	else if(c=='T') return 1;
	else if(c=='C') return 2;
	else return 3;
}

void insert(char *s) {
	int now = 0;
	for(int i=0; s[i]; i++) {
		int ch = get_idx(s[i]);
		if(trie[now][ch] == 0) trie[now][ch] = ++tn;
		now = trie[now][ch];
	}
	flag[now] = 1;
}

void get_fail() {
	memset(fail,0,sizeof(fail));
	fail[0] = -1;
	queue<int> q;
	for(int i=0; i<4; ++i) {
		if(trie[0][i]) q.push(trie[0][i]);
	}
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		if(flag[fail[now]])					//如果当前结点的指向是不允许的，那么这个点也是不允许的
			flag[now] = 1;
		for(int i=0; i<4; ++i) {
			if(trie[now][i]) {
				fail[trie[now][i]] = trie[fail[now]][i];
				q.push(trie[now][i]);
			} else {
				trie[now][i] = trie[fail[now]][i];
			}
		}
	}
}

struct Mat {
	long long mat[110][110];
	Mat() {
		memset(mat,0,sizeof(mat));
	}
};

Mat operator * (const Mat &m1,const Mat &m2) {
	Mat ret;
	for(int i=0; i<=tn; i++) {
		for(int j=0; j<=tn; j++) {
			for(int k=0; k<=tn; k++) {
				ret.mat[i][j] += m1.mat[i][k]*m2.mat[k][j];
				ret.mat[i][j] %= MOD;
			}
		}
	}
	return ret;
}

Mat Mat_pow(Mat m) {
	Mat e;
	for(int i=0; i<=tn; i++) e.mat[i][i] = 1;
	while(n) {
		if(n&1) e = e*m;
		m = m*m;
		n >>= 1;
	}
	return e;
}

int main() {
	char str[11];
	while(~scanf("%d%d",&m,&n)) {
		tn=0;
		memset(flag,0,sizeof(flag));
		memset(trie,0,sizeof(trie));
		for(int i=0; i<m; i++) {
			scanf("%s",str);
			insert(str);
		}
		get_fail();

		Mat x,e;
		for(int i=0; i<=tn; ++i) {
			if(flag[i]) continue;
			for(int j=0; j<4; ++j) {
				if(flag[trie[i][j]]) continue;
				x.mat[i][trie[i][j]]++;
			}
		}
		e = Mat_pow(x);

		long long res=0;
		for(int i=0; i<=tn; ++i) {
			res += e.mat[0][i];
			res %= MOD;
		}
		cout << res << endl;
	}
	return 0;
}
