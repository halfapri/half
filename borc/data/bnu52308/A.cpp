#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int M = 100000, nill=0;
const double eps = 1e-9;
struct Person {
    int v,tim;
    string s;
    bool operator < (const Person &rhs) const {
        if (v==rhs.v) return tim>rhs.tim;
        return v>rhs.v;
    }
}a[M];
int A;
/////////////////////////////////////////////////////
int ls[M], rs[M], rt;
struct Node
{
    int id,v,tim,sz;
    unsigned fix;
    Node (){}
    Node (int _v,int _tim) : v(_v), tim(_tim) {}
	inline bool operator == (const Node &rhs) const {
		return v==rhs.v && tim==rhs.tim;
	}
    inline bool operator < (const Node &rhs) const {
        if (v==rhs.v) return tim>rhs.tim;
        return v>rhs.v;
    }
}T[M];

struct Treap
{
    int MY;
    void init () {
        T[0].v=inf,T[0].tim=T[0].sz=0;
        ls[0]=rs[0]=0;MY=1;
    }
    inline int alloc (int id,int v,int tim) {
        T[MY].id=id,T[MY].v=v,T[MY].tim=tim,T[MY].sz=1,T[MY].fix=rand();
        ls[MY]=rs[MY]=nill; return MY++;
    }
    inline void down (int o) {
        T[o].sz=1;
    }
    inline void up (int o) {
        T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
    }
    void cut (int o,int &a,int &b,int k) {
        if (T[o].sz<=k) {a=o,b=nill;return;}
        if (k<=0) {b=o,a=nill;return;}
        down (o);
        if (T[ls[o]].sz<k) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
        else cut(ls[o],a,ls[b=o],k);
        up (o);
    }
    void Merge (int &o,int a,int b) {
        if (a==nill) o=b;
        else if (b==nill) o=a;
        else if (T[a].fix>T[b].fix) {
            down(o=a); Merge(rs[o],rs[a],b); up(o);
        } else {
            down(o=b); Merge(ls[o],a,ls[b]); up(o);
        }
    }
    void build (int &o,int l,int r) {
        if (l>r) return;
        int mid = l+r>>1;
        build (ls[o=alloc(mid,a[mid].v,a[mid].tim)], l, mid-1);
        build (rs[o], mid+1, r);
        up (o);
        T[o].fix = max(T[ls[o]].fix, T[rs[o]].fix);
    }
    int askrk (int o,Node x) {
		if (o==nill) return 0;
		if (x == T[o]) return T[ls[o]].sz;
		if (x<T[o]) return askrk (ls[o],x);
		return T[ls[o]].sz+1+askrk (rs[o],x);
    }
    int ins (int id,int v,int tim) {
        int a,b,c,k,o=alloc(id,v,tim);
        k = askrk (rt, T[o]);
        cut (rt, a, b, k);
        Merge (rt, a, o);
        Merge (rt, rt, b);
        return k+1;
    }
    int askid (int k) {
        int a,b,c,ans;
        cut (rt, a, b, k-1);
        cut (b, b, c, 1);
        ans = T[b].id;
        Merge (rt, a, b);
        Merge (rt, rt, c);
        return ans;
    }
    int del (Node now) {
        int a,b,c,k;
        k = askrk (rt, now);
        cut (rt, a, b, k);
        cut (b, b, c, 1);
        Merge (rt, a, c);
        return k+1;
    }
}my;

map<string,int> mp;

int main () {
	//freopen ("read.txt", "r", stdin);
    srand (time(0));
    scanf ("%d", &A);
    my.init();
    for (int i=1; i<=A; i++) {
        cin >> a[i].s;
        scanf ("%d", &a[i].v);
        a[i].tim=i;
    }
    sort (a+1, a+1+A);
    for (int i=1; i<=A; i++) mp[a[i].s] = i;
    my.build (rt, 1, A);
    int Q;
    scanf ("%d", &Q);
    int lst = (int) (0.2*A+eps), now, tot = A;
    string s;
    while (Q --) {char op[30]; int x, k;
        scanf ("%s", op);
        if (op[0]=='-') {
            cin >> s;
            x = mp[s];
            k = my.del (Node (a[x].v,a[x].tim));
            tot --;
            now = int (tot*0.2+eps);
            if (now == lst) {
                if (k<=now) {
                    int id = my.askid (now);
                    cout << a[id].s ;
                    printf (" is working hard now.\n");
                }
            } else {
                if (k>lst) {
                    int id = my.askid (lst);
                    cout << a[id].s;
                    printf (" is not working now.\n");
                }
            }
            mp.erase (s);
        } else {
            x = ++A;
            cin >> a[x].s;
            mp[a[x].s] = x;
            scanf ("%d", &a[x].v);
            a[x].tim = x;
            k = my.ins (x, a[x].v, a[x].tim);
            tot ++;
            now = (int) (0.2*tot + eps);
            if (k<=now) {cout << a[x].s; printf (" is working hard now.\n");}
            else {cout <<a[x].s; printf (" is not working now.\n");}
            if (now==lst) {
                if (k<=now) {
                    int id = my.askid (now+1);
                    cout << a[id].s;
                    printf (" is not working now.\n");
                }
            } else {
                if (k>now) {
                    int id = my.askid (now);
                    cout << a[id].s;
                    printf (" is working hard now.\n");
                }
            }
        }
		//printf ("There is %d people in ACM,%d are working hard.\n", mp.size(),now);
        lst = now;
    }
    return 0;
}
