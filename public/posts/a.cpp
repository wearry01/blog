const int M = 100000;

ll n;
int m;
uint val[M + 5];
int prime[M + 5], pcnt;
uint s[M + 5], S[M + 5];
uint f[M + 5], F[M + 5];

inline uint gets(ll x) { return x <= m ? s[x] : S[n / x]; }
inline uint getf(ll x) { return x <= m ? f[x] : F[n / x]; }

int my_sqrt(ll x) {
int r = 1;
while(1ll * (r + 1) * (r + 1) <= x) ++ r;
return r;
}

void init(ll _n) {
m = my_sqrt(n = _n);

for(int i = 1; i <= m; ++i) {
val[i] = 81 * i * i - 27 * i + 9;
s[i] = i - 1;
S[i] = (n / i) - 1;
}

for(int p = 2; p <= m; ++p) {
if(s[p] == s[p-1]) continue;
prime[pcnt ++] = p;

const uint _s = s[p - 1];
const ll q = 1ll * p * p, lim = min((ll) m, n / q), x = m / p, y = n / p;

for(int i = 1; i <= x; ++i) S[i] -= S[i * p] - _s;
for(int i = x + 1; i <= lim; ++i) S[i] -= s[y / i] - _s;
for(int i = m; i >= q; --i) s[i] -= s[i / p] - _s;
}

for(int i = 1; i <= m; ++i) {
f[i] = s[i] * 63;
F[i] = S[i] * 63;
}

for(int e = pcnt; e >= 1; --e) {
int p = prime[e-1];
const ll q = 1ll * p * p, lim = min((ll) m, n / q);

for(int i = 1; i <= lim; ++i) {
ll cur = n / i;
for(ll t = p, c = 1; t * p <= cur; t *= p, ++ c) {
F[i] += (getf(cur / t) - e * 63) * val[c] + val[c + 1];
}
}

for(int i = m; i >= q; --i) {
int cur = i;
for(int t = p, c = 1; t <= cur / p; t *= p, ++ c) {
f[i] += (getf(cur / t) - e * 63) * val[c] + val[c + 1];
}
}
}
}
}
