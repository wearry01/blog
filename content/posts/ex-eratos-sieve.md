---
title: 拓展埃氏筛法小结
date: 2018-08-21 19:42:41
description: 学完洲阁筛之后忘得差不多了, 不过现在已经可以将洲阁筛扔进垃圾桶了
tags:
    - 趣题
---

## Description

求:

$$h(n) = \sum_{i=1}^{n} f(i)$$ 

其中 \\(f\\) 是定义在正整数集下的积性函数, 满足 \\(f(p^c)\\) 能够快速计算.

## Conversion

首先可以将所有要求的数按照是否只含大于 \\(\sqrt{n}\\) 的质因子分为两类, 对于第一类数一定是一个质数, 而第二类数一定可以在某个较小的质因子处考虑到, 于是我们只关注不超过 \\(\sqrt{n}\\) 的那些质因子.

定义 \\(S_k(n, i)\\) 表示小于等于 \\(n\\) 的数中与前 \\(i\\) 个质数互质的所有数与**所有质数**的 \\(k\\) 次方和, 容易得到转移:

$$
S_k(n, i) = 
\begin{cases}
S_k(n, i-1) & n < p_i^2 \\\\
S_k(n, i-1) - p_i^k \times \left(S_k(\left \lfloor \frac{n}{p_i} \right \rfloor, i - 1) - S_k(p_{i-1}, i - 1)\right) & \mathrm{otherwise} 
\end{cases}
$$

在考虑完 \\(\sqrt{n}\\) 以内的所有质因数后, \\(S_k(n)\\) 中留下了所有质数的 \\(k\\) 次方, 这样所有第一类数的函数值都可以快速计算.

类似地, 定义 \\(G(n, i)\\) 表示小于等于 \\(n\\) 的数中仅由第 \\(i\\) 个以后的质数构成的数与**所有质数** \\(x\\) 的 \\(f(x)\\) 之和, 转移的方式类似:

$$
G(n, i) = G(n, i+1) + \sum_{c=0}^{\substack{p_i^{c+1} \le n}} f(p_i^{c+1}) + f(p_i^c) \times \left(G(\left \lfloor \frac{n}{p_i^c} \right \rfloor, i+1) - G(p_i, i+1)\right)
$$

复杂度约为 \\(O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)\\)

## Code

```cpp
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
```
