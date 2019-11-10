#include<bits/stdc++.h>
using namespace std;
#define n_l '\n'
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: "; cerr << to_string(__VA_ARGS__) << endl
template <typename T, size_t N> int SIZE(const T (&t)[N]){ return N; } template<typename T> int SIZE(const T &t){ return t.size(); } string to_string(const string s, int x1=0, int x2=1e9){ return '"' + ((x1 < s.size()) ? s.substr(x1, x2-x1+1) : "") + '"'; } string to_string(const char* s) { return to_string((string) s); } string to_string(const bool b) { return (b ? "true" : "false"); } string to_string(const char c){ return string({c}); } template<size_t N> string to_string(const bitset<N> &b, int x1=0, int x2=1e9){ string t = ""; for(int __iii__ = min(x1,SIZE(b)),  __jjj__ = min(x2, SIZE(b)-1); __iii__ <= __jjj__; ++__iii__){ t += b[__iii__] + '0'; } return '"' + t + '"'; } template <typename A, typename... C> string to_string(const A (&v), int x1=0, int x2=1e9, C... coords); int l_v_l_v_l = 0, t_a_b_s = 0; template <typename A, typename B> string to_string(const pair<A, B> &p) { l_v_l_v_l++; string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; l_v_l_v_l--; return res; } template <typename A, typename... C> string to_string(const A (&v), int x1, int x2, C... coords) { int rnk = rank<A>::value; string tab(t_a_b_s, ' '); string res = ""; bool first = true; if(l_v_l_v_l == 0) res += n_l; res += tab + "["; x1 = min(x1, SIZE(v)), x2 = min(x2, SIZE(v)); auto l = begin(v); advance(l, x1); auto r = l; advance(r, (x2-x1) + (x2 < SIZE(v))); for (auto e = l; e != r; e = next(e)) { if (!first) { res += ", "; } first = false; l_v_l_v_l++; if(e != l){ if(rnk > 1) { res += n_l; t_a_b_s = l_v_l_v_l; }; } else{ t_a_b_s = 0; } res += to_string(*e, coords...); l_v_l_v_l--; } res += "]"; if(l_v_l_v_l == 0) res += n_l; return res; } void dbgm(){;} template<typename Heads, typename... Tails> void dbgm(Heads H, Tails... T){ cerr << to_string(H) << " | "; dbgm(T...); } 
#define dbgm(...) cerr << "[" << #__VA_ARGS__ << "]: "; dbgm(__VA_ARGS__); cerr << endl
#define run(a, b) cerr << fixed << setprecision(6) << (double) (b - a) / (double) (CLOCKS_PER_SEC) << " s" << endl;
#define ll long long
#define ld long double
#define INF (1e18L + 5)
#define MOD (int)(1e9 + 7) 

int m, w;
vector<ll> costM, dp, col;
vector<vector<ll>> wireMatrix, wire;

ll solve(int a) {
    if(a == m) {
        return INF;
    }
    if(dp[a] != INF) {
        return dp[a];
    }
    ll res = 0;
    for(auto &i : wire[a]) {
        if(col[i] >= col[a]) {
            // dbgm(a, i);
            res += min(wireMatrix[i][a], solve(i));
        }
    }
    return dp[a] = min(res, costM[a]);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin >> m >> w, m and w) {
        costM.assign(m+1, INF);
        for(int i = 0; i < m - 2; i++) {
            int x, y;
            cin >> x >> y;
            costM[x] = y;
        }
        wireMatrix.assign(m+1, vector<ll>(m+1, INF));
        wire.assign(m+1, vector<ll>());
        for(int i = 0; i < w; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            wire[x].push_back(y);
            wire[y].push_back(x);
            wireMatrix[x][y] = z;
            wireMatrix[y][x] = z;
        }
        // dbg(wire);
        col.assign(m+1, -1);
        queue<int> bfs;
        bfs.push(1);
        col[1] = 0;
        while(!bfs.empty()) {
            int top = bfs.front(); bfs.pop();
            for(auto &i : wire[top]) {
                if(col[i] == -1) {
                    col[i] = col[top]+1;
                    bfs.push(i);
                }
            }
        }
        // dbg(col);
        dp.assign(m+1, INF);
        cout << solve(1) << endl;
        dbg(dp);
    }
    return 0;
}
