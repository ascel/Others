#include <bits/stdc++.h>
using namespace std;
#define n_l '\n'
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: "; cerr << to_string(__VA_ARGS__) << endl
template <typename T, size_t N> int SIZE(const T (&t)[N]){ return N; } template<typename T> int SIZE(const T &t){ return (int) t.size(); } string to_string(const string s, int x1=0, int x2=1e9){ return '"' + ((x1 < (int) s.size()) ? s.substr(x1, x2-x1+1) : "") + '"'; } string to_string(const char* s) { return to_string((string) s); } string to_string(const bool b) { return (b ? "true" : "false"); } string to_string(const char c){ return string({c}); } template<size_t N> string to_string(const bitset<N> &b, int x1=0, int x2=1e9){ string t = ""; for(int __iii__ = min(x1,SIZE(b)),  __jjj__ = min(x2, SIZE(b)-1); __iii__ <= __jjj__; ++__iii__){ t += b[__iii__] + '0'; } return '"' + t + '"'; } template <typename A, typename... C> string to_string(const A (&v), int x1=0, int x2=1e9, C... coords); int l_v_l_v_l = 0, t_a_b_s = 0; template <typename A, typename B> string to_string(const pair<A, B> &p) { l_v_l_v_l++; string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; l_v_l_v_l--; return res; } template <typename A, typename... C> string to_string(const A (&v), int x1, int x2, C... coords) { int rnk = rank<A>::value; string tab(t_a_b_s, ' '); string res = ""; bool first = true; if(l_v_l_v_l == 0) res += n_l; res += tab + "["; x1 = min(x1, SIZE(v)), x2 = min(x2, SIZE(v)); auto l = begin(v); advance(l, x1); auto r = l; advance(r, (x2-x1) + (x2 < SIZE(v))); for (auto e = l; e != r; e = next(e)) { if (!first) { res += ", "; } first = false; l_v_l_v_l++; if(e != l){ if(rnk > 1) { res += n_l; t_a_b_s = l_v_l_v_l; }; } else{ t_a_b_s = 0; } res += to_string(*e, coords...); l_v_l_v_l--; } res += "]"; if(l_v_l_v_l == 0) res += n_l; return res; } void dbgm(){;} template<typename Heads, typename... Tails> void dbgm(Heads H, Tails... T){ cerr << to_string(H) << " | "; dbgm(T...); } 
#define dbgm(...) cerr << "[" << #__VA_ARGS__ << "]: "; dbgm(__VA_ARGS__); cerr << endl
#define run(a, b) cerr << fixed << setprecision(6) << (double) (b - a) / (double) (CLOCKS_PER_SEC) << " s" << endl;
#define ll long long
#define INF (1e9 + 5)
#define MOD (int)(1e9 + 7) 

int MAXN;
vector<int> segtree;

int build(vector<int> &arr, int idx, int tl, int tr) {
    if(tl == tr) {
        return segtree[idx] = arr[tl-1];
    }

    int mid = (tl + tr) / 2;

    return segtree[idx] = build(arr, idx*2, tl, mid) + build(arr, idx*2+1, mid+1, tr);
}

void query(int idx, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        cout << segtree[idx] << '\n';
        segtree[idx] = new_val;
    } else {
        int mid = (tl + tr) / 2;
        if (pos <= mid)
            query(idx*2, tl, mid, pos, new_val);
        else
            query(idx*2+1, mid+1, tr, pos, new_val);
        segtree[idx] = segtree[idx*2] + segtree[idx*2+1];
    }
}

void update(int idx, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        segtree[idx] += new_val;
    } else {
        int mid = (tl + tr) / 2;
        if (pos <= mid)
            update(idx*2, tl, mid, pos, new_val);
        else
            update(idx*2+1, mid+1, tr, pos, new_val);
        segtree[idx] = segtree[idx*2] + segtree[idx*2+1];
    }
}

int querySum(int idx, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return segtree[idx];
    }
    int mid = (tl + tr) / 2;
    return querySum(idx*2, tl, mid, l, min(r, mid)) + querySum(idx*2+1, mid+1, tr, max(l, mid+1), r);
}

int main(){
    ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int t, tc = 1;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        MAXN = 4 * n;
        segtree.resize(MAXN);
        segtree.assign(MAXN, 0);
        vector<int> arr(n);
        for(int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        build(arr, 1, 1, n);
        cout << "Case " << tc++ << ":\n";
        for(int i = 0; i < q; ++i) {
            int p;
            cin >> p;
            if(p == 1) {
                int x;
                cin >> x;
                query(1, 1, n, x+1, 0);
            }
            else if(p == 2) {
                int x, v;
                cin >> x >> v;
                update(1, 1, n, x+1, v);
            }
            else if(p == 3) {
                int l, r;
                cin >> l >> r;
                cout << querySum(1, 1, n, l+1, r+1) << '\n';
            }
        }
    }
    return 0;
}
