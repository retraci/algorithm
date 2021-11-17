// HDU 2243 考研路茫茫――单词情结
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int n,l;
int ch[30][26],fail[30],flag[30],tn;

void insert(char *s) {
	int now = 0;
	for(int i=0;s[i];i++) {
		int x = s[i]-'a';
		if(ch[now][x] == 0) ch[now][x] = ++tn;
		now = ch[now][x];
	}
	flag[now] = 1;	
}

void init() {
	queue<int> q;
	for(int i=0;i<26;i++) {
		if(ch[0][i]) q.push(ch[0][i]);
	}
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i=0;i<26;i++) {
			if(ch[now][i]) {
				fail[ch[now][i]] = ch[fail[now]][i];
				q.push(ch[now][i]);
			} else {
				ch[now][i] = ch[fail[now]][i];
			}
			flag[ch[now][i]] |= flag[ch[fail[now]][i]];
		}
	}
}

struct Mat {
	unsigned long long m[30][30];
	int n;
	Mat() {
		memset(m,0,sizeof(m));
	}
};

Mat operator * (const Mat &m1,const Mat &m2) {
	Mat m;
	m.n = max(m1.n,m2.n);
	for(int i=0;i<m.n;i++) {
		for(int j=0;j<m.n;j++) {
			for(int k=0;k<m.n;k++) {
				m.m[i][j] += m1.m[i][k]*m2.m[k][j];
			}
		}
	}
	return m;
}

void pow(Mat m,Mat &e,int c) {
	while(c) {
		if(c&1) e = m*e;
		m = m*m;
		c >>= 1;
	}
}

int main() {
	char s[10];
	while(~scanf("%d%d",&n,&l)) {
		tn = 0;
		memset(ch,0,sizeof(ch));
		memset(fail,0,sizeof(fail));
		memset(flag,0,sizeof(flag));
		
		for(int i=0;i<n;i++) {
			scanf("%s",s);
			insert(s);
		}
		init();
		
		Mat sm,se;
		sm.n = se.n = 2;
		se.m[0][0]=0 ;se.m[0][1]=0;
		se.m[1][0]=26;se.m[1][1]=0;
		sm.m[0][0]=26;sm.m[0][1]=1;
		sm.m[1][0]=0 ;sm.m[1][1]=1;
		pow(sm,se,l);
		unsigned long long tot = se.m[0][0];
//		cout << se.m[0][0] << " " << se.m[0][1] << endl;
//		cout << se.m[1][0] << " " << se.m[1][1] << endl;
//		cout << tot;
		
		Mat tm,te;
		tm.n = te.n = tn+1;
		for(int i=0;i<te.n;i++) te.m[i][i] = 1;
		for(int i=0;i<tn;i++) {
			if(flag[i]) continue;
			for(int j=0;j<26;j++) {
				if(flag[ch[i][j]]) continue;
				tm.m[i][ch[i][j]]++;
			}
		}
		for(int i=0;i<tn+1;i++) tm.m[i][tn] = 1;
		pow(tm,te,l);
		unsigned long long res = 0;
		for(int i=0;i<te.n;i++) res += te.m[0][i];
		
//		cout << tot << endl << res << endl;
		cout << tot-res+1 << endl;
	}
	
	return 0;
}

