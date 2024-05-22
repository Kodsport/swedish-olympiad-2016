// #undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
// #pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
// #pragma GCC optimize ("unroll-loops")

// #pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
// #pragma GCC target("movbe")                                      // byte swap
// #pragma GCC target("aes,pclmul,rdrnd")                           // encryption
// #pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>

using namespace std;

#define enablell 0

typedef long long ll;
#if enablell
#define int ll
#define inf LLONG_MAX
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

//#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
//#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if _MSC_VER > 0
#define gc() getchar()
#else
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
#define gc() getchar_unlocked()
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;
#endif

template<typename T>
inline T gcd(T a, T b)
{
    T c;
    while (b)
    {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}

struct fraction
{
    fraction(ll a, ll b) : a(a), b(b) { reduce(); }
    fraction(ll a) : a(a), b(1) { reduce(); }
    fraction() : a(0), b(1) { reduce(); }
    void reduce()
    {
        ll g = gcd(a, b);
        a /= g;
        b /= g;

        if (b < 0)
        {
            b *= -1;
            a *= -1;
        }
    }
    ll a, b;
};

inline bool operator>(const fraction& l, const fraction& r) { return l.a * r.b > l.b * r.a; }
inline fraction operator/(const fraction& l, const fraction& r) { return fraction(l.a*r.b, l.b*r.a); }
inline fraction operator*(const fraction& l, const fraction& r) { return fraction(l.a*r.a, l.b*r.b); }
inline void operator-=(fraction& l, const fraction& r) { l = fraction(l.a * r.b - l.b * r.a, l.b * r.b); }
inline fraction operator-(const fraction& l, const fraction& r) { return fraction(l.a * r.b - l.b * r.a, l.b * r.b); }
inline void operator+=(fraction& l, const fraction& r) { l = fraction(l.a * r.b + l.b * r.a, l.b * r.b); }
inline fraction abs(const fraction& a) { return fraction(abs(a.a), abs(a.b)); }

inline vi add(const vi& l, const vi& r) { vi ret(l.size()); rep(i, l.size()) ret[i] = l[i] + r[i]; return ret; }
inline vi dif(const vi& l, const vi& r) { vi ret(l.size()); rep(i, l.size()) ret[i] = l[i] - r[i]; return ret; }
inline vi mul(const vi& l, int m) { vi ret(l.size()); rep(i, l.size()) ret[i] = l[i] * m; return ret; }

inline vi calcpos(int i, int j)
{
    vi top = { 1,1,0,0 };
    vi diff = { 1,0,0,1 };
    diff = dif(diff, top);

    vi r = add(top, mul(diff, i));
    vi l = { 1, 0, i,0 };

    vi tempd = dif(r, l);
    vi p = add(l, mul(tempd, j));
    return p;
};

int32_t main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread2(int, n, m);
    //int n = 0; int m = 0;

    vvi rect(n, vi(m,inf));
    rep(i, n)
    {
        rep(j, m)
        {
            dread(string, r);
            if (r[0] != '.')
            {
                rect[i][j] = stoi(r);
            }
        }
    }

    /*n = 3;
    m = 2;*/
    vector<vector<fraction>> eq;


    /*vi d = calcpos(1, 0);
    vi a = calcpos(1, 1);
    vi b = calcpos(1, 2);
    vi c = calcpos(1, 3);
    vi f = calcpos(0, 0);*/

    rep(i, n) rep(j, m)
    {
        if (rect[i][j]!=inf)
        {
            vector<fraction> row(5);
            
            // a b c d
            
            vi vars = calcpos(i, j);
            rep(i, 4) row[i] = vars[i];
            row[4] = rect[i][j];
            eq.emplace_back(row);

        }

    }
    

    
   



    rep(c,4)
    {
        for (int i = c; i < eq.size(); ++i) if (eq[i][c].a != 0)
        {
            swap(eq[c], eq[i]);
            break;
        }

        
        // If we've run out of equations or need a new one
        if (c == eq.size() || eq[c][c].a == 0)
        {
            vector<fraction> neq(5);
            neq[c] = 1;
            eq.emplace_back(neq);
            swap(eq[c], eq[eq.size() - 1]);
        }


        

        repp(r, c + 1, eq.size())
        {
            fraction f = eq[r][c] / eq[c][c];
            eq[r][c] = 0;
            for (int j = c+1; j <= 4; ++j)
                eq[r][j] -= eq[c][j] * f;
        }
    }

    vector<fraction> ans(4);
    per(i, 4)
    {
        ans[i] = eq[i][4];
        for (size_t j = i + 1; j < 4; ++j)
            ans[i] -= eq[i][j] * ans[j];
        ans[i] = ans[i] / eq[i][i];
    }



    //for (int i = 0; i < m; ++i)
    //    if (where[i] != -1)
    //        ans[i] = eq[where[i]][m] / eq[where[i]][i];
    //for (int i = 0; i < n; ++i) {
    //    fraction sum = fraction(0,1);
    //    for (int j = 0; j < m; ++j)
    //        sum += ans[j] * eq[i][j];
    //    if (abs(sum - eq[i][m]) > fraction(1, int(1e9)))
    //    {
    //        cout << "ej magisk";
    //        quit;
    //    }
    //}

    //for (int i = 0; i < m; ++i)
    //    if (where[i] == -1)
    //        // infinite
    //        deb;


    rep(i, n)
    {
        rep(j, m)
        {
            fraction v = 0;
            vi coeffs = calcpos(i, j);

            rep(i, 4) v += coeffs[i] * ans[i];

            v.reduce();

            if (rect[i][j]!=inf&&(v.b!=1 || v.a!=rect[i][j]))
            {
                cout << "ej magisk";
                quit;
            }
        }
    }

    rep(i, n)
    {
        rep(j, m)
        {
            fraction v = 0;
            vi coeffs = calcpos(i, j);

            rep(i, 4) v += coeffs[i] * ans[i];

            v.reduce();

            cout << v.a;
            if (v.b != 1) cout << "/" << v.b;
            cout << " ";
        }
        cout << "\n";
    }
    


    quit;
}
