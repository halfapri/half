#include<bits/stdc++.h>
using namespace std;

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

const int M = 1000000+10;
typedef long long ll;

char s[M];
int ls;
int c[M];
int d[M];
int cost[M];
int n;

struct SAM {
	static const int kN = M<<1;
	static const int chN = 26;
	int fa[kN];
	int go[kN][chN];
	int l[kN];
	int o;
	int rt;
	int lst;

	inline int newNode(int _l) {
		for (int i=0; i<chN; ++i) {
			go[o][i] = -1;
		}
		l[o] = _l;
		return o ++;
	}
	void Init() {
		o = 0;
		rt = lst = newNode(0);
		fa[rt] = -1;
	}
	inline void InsKey() {
		int p = lst, np = newNode(l[lst]+1); lst = np;
		fa[np] = rt;
	}
	inline void Ins(int c) {
		int p = lst, np = newNode(l[lst]+1); lst = np;
		while (~p && go[p][c] == -1) go[p][c] = np, p = fa[p];
		if (p==-1) fa[np] = rt;
		else {
			int q = go[p][c];
			if (l[p]+1 == l[q]) fa[np] = q;
			else {
				int nq = newNode(l[p]+1);
				memcpy(go[nq], go[q], sizeof(go[q]));
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				while (~p && go[p][c] == q) go[p][c] = nq, p = fa[p];
			}
		}
	}

	//topo
	int ord[kN], cnt[kN];
	void topo() {
		int maxVal = 0;
		memset (cnt, 0, sizeof(cnt[0])*(o+1));
		for (int i=0; i<o; ++i) maxVal = max(maxVal, l[i]), ++ cnt[l[i]];
		for (int i=0; i<=maxVal; ++i) cnt[i] += cnt[i-1];
		for (int i=0; i<o; ++i) ord[-- cnt[l[i]]] = i;
	}
	int in[kN];
	ll dp[kN];
	ll Solve() {
		topo();
		memset (in, 0, sizeof(in[0])*(o+1));
		memset (dp, 0, sizeof(dp[0])*(o+1));
		for (int i=rt+1; i<o; ++i) {
			++ in[fa[i]];
		}
		ll ret = 0;
		for (int u=o-1; u>rt; --u) {
			int i = ord[u];
			int id = l[i]-1;
			if (d[id] == 0 && in[i] == 0) continue;
			if (in[i] == 0) {
				int w = cost[c[id]];
				if (d[id] >= l[fa[i]]+1) ret = max(ret, 1ll*w*d[id]);
				dp[fa[i]] += w;
			} else if (in[i] > 0){
				ret = max(ret, 1ll*dp[i]*l[i]);
				dp[fa[i]] += dp[i];
			}
		}
		return ret;
	}
} sam;

int main () {
	sam.Init();
	scanf ("%d", &n);
	ls = 0;
	for (int i=0; i<n; ++i) {
		d[ls++] = 0;
		sam.InsKey();
		scanf ("%s", s+ls);
		int f = ls;
		ls += strlen(s+f);
		for (int j=f; j<ls; ++j) {
			sam.Ins(s[j]-'a');
			c[j] = i+1;
			d[j] = j-f+1;
		}
	}
	for (int i=1; i<=n; ++i) {
		scanf ("%d", cost+i);
	}
	printf (LLD"\n", sam.Solve());
	return 0;
}
