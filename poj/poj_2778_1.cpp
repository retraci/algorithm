// POJ 2778 DNA Sequence
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int MOD = 100000;

int m,n;
int ch[110][4],fail[110],flag[110],tn;

int get_index(char c) {
	if(c == 'A') return 0;
	if(c == 'C') return 1;
	if(c == 'T') return 2;
	else return 3;
}

void insert(char *s) {
	int now = 0;
	int idx;
	for(int i=0;s[i];i++) {
		idx = get_index(s[i]);
		if(ch[now][idx] == 0) ch[now][idx] = ++tn;
		now = ch[now][idx];
	}
	flag[now] = 1;
}

void get_fail() {
	fail[0] = -1;
	queue<int> q;
	for(int i=0;i<4;i++) 
		if(ch[0][i]) q.push(ch[0][i]);
		
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		if(flag[fail[now]]) flag[now] = 1;
		for(int i=0;i<4;i++) {
			if(ch[now][i]) {
				fail[ch[now][i]] = ch[fail[now]][i];
				q.push(ch[now][i]);
			} else {
				ch[now][i] = ch[fail[now]][i];
			}
		}
	}
}

struct Mat {
	int mat[110][110];
	Mat() {
		memset(mat,0,sizeof(mat));
	}
};

Mat operator * (const Mat &m1,const Mat &m2) {
	Mat m;
	for(int i=0;i<=tn;i++) {
		for(int j=0;j<=tn;j++) {
			for(int k=0;k<=tn;k++) {
				m.mat[i][j] += m1.mat[i][k]*m2.mat[k][j];
				m.mat[i][j] %= MOD;
			}
		}
	}
	
	return m;
}

void pow(Mat m,Mat &e) {
	for(int i=0;i<=tn;i++) e.mat[i][i] = 1;
	while(n) {
		if(n&1) e = e*m;
		m = m*m;
		n >>= 1;
	}
}

int main() {
	char s[11];
	while(~scanf("%d%d",&m,&n)) {
		tn = 0;
		memset(ch,0,sizeof(ch));
		memset(flag,0,sizeof(flag));
		memset(fail,0,sizeof(fail));
		for(int i=0;i<m;i++) {
			scanf("%s",s);
			insert(s);
		}
		get_fail();
		
		Mat x,e;
		for(int i=0;i<=tn;i++) {
			if(flag[i]) continue;
			for(int j=0;j<4;j++) {
				if(flag[ch[i][j]]) continue;
				x.mat[i][ch[i][j]]++;
			}
		}
		pow(x,e);
		
		long long ans = 0;
		for(int i=0;i<=tn;i++) {
			ans += e.mat[0][i];
			ans %= MOD;
		}
		cout << ans << endl;
	}
	
	return 0;
}

