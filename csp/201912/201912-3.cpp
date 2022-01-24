#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+10;
typedef vector<string> Vec;
typedef map<string,int> Map;
/*
11
H2+O2=H2O
2H2+O2=2H2O
H2+Cl2=2NaCl
H2+Cl2=2HCl
CH4+2O2=CO2+2H2O
CaCl2+2AgNO3=Ca(NO3)2+2AgCl
3Ba(OH)2+2H3PO4=6H2O+Ba3(PO4)2
3Ba(OH)2+2H3PO4=Ba3(PO4)2+6H2O
4Zn+10HNO3=4Zn(NO3)2+NH4NO3+3H2O
4Au+8NaCN+2H2O+O2=4Na(Au(CN)2)+4NaOH
Cu+As=Cs+Au
*/
Map operator*(Map a,int x) {
	Map::iterator it;
	for(it = a.begin(); it != a.end(); it++) it->second*=x;
	return a;
}
Map operator+(Map a,Map b) {
	Map::iterator it;
	for(it = b.begin(); it != b.end(); it++) a[it->first]+=it->second;
	return a;
}
bool operator==(Map a,Map b) {
	if(a.size()!=b.size())return 0;
	Map::iterator it;
	for(it = b.begin(); it != b.end(); it++)if(!a.count(it->first)||a[it->first]!=it->second)return 0;
	return 1;
}
Map F(string s) {
	Map a;
	a[s]=1;
	return a;
}
Vec split(string S,char C) {
	Vec vec;
	string s;
	
	for(int i = 0; i < S.size(); i++) {
		if(S[i]==C)vec.push_back(s),s.clear();
		else s.push_back(S[i]);
	}
	vec.push_back(s);
	return vec;
}
int n,tp,dep[N];
Map sta[N];
Map solve(string s) {
	tp=0;
	int i=0,x=0,d=0;
	for(; i<s.length()&&isdigit(s[i]); ++i)x=x*10+s[i]-'0';
	if(x==0)x=1;
	for(; i<s.length(); ++i) {
		if(isupper(s[i])) {
			string t;
			if(i+1<s.length()&&islower(s[i+1]))t=string(1,s[i])+string(1,s[i+1]),++i;
			else t=string(1,s[i]);
			sta[tp]=F(t),dep[tp++]=d;
		} else if(isdigit(s[i])) {
			int y=0;
			for(; i<s.length()&&isdigit(s[i]); ++i)y=y*10+s[i]-'0';
			sta[tp-1]=sta[tp-1]*y;
			--i;
		} else if(s[i]=='(') {
			++d;
		} else if(s[i]==')') {
			Map t;
			for(; tp&&dep[tp-1]==d; --tp)t=t+sta[tp-1];
			--d;
			sta[tp]=t,dep[tp++]=d;
		}
	}
	Map t;
	for(; tp&&dep[tp-1]==d; --tp)t=t+sta[tp-1];
	return t*x;
}
Map solve2(string s) {
	Vec vec=split(s,'+');
	Map t;
	for(int i = 0; i < vec.size(); i++)t=t+solve(vec[i]);
	return t;
}
int main() {
	cin>>n;
	while(n--) {
		string s;
		cin>>s;
		Vec vec=split(s,'=');
		Map mp1=solve2(vec[0]);
		Map mp2=solve2(vec[1]);
		puts(mp1==mp2?"Y":"N");
	}
	return 0;
}
