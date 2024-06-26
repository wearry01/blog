---
title: Atcoder 选做
date: 2017-06-30 21:33:45
tags:
    - 趣题
description:
    "总结一下比赛中遇到的好题, 然后瞎做了几场 AGC 的题目练习, 感觉比较有意思"

---

# AGC

## AGC002 F Leftmost Ball

> 给你\\(N\\)种不同颜色的球, 每种有\\(K\\)个, 现在你可以将球任意排列, 但最终的序列中每种颜色的第一个出现位置要被染成\\(0\\)颜色, 求能够得到的本质不同的序列数, 对\\(10^9 + 7\\)取模.
>
> \\(N, K \leq 2000\\)

这题正着处理没有什么思路, 但是如果从右往左来会比较好考虑. 
我们可以记\\(f(i, j)\\)表示当前从右往左填剩下\\(i\\)个\\(0\\)颜色的球, 还剩下\\(j\\)种颜色没有放的方案数. 
那么每一次的决策就包括放入一个\\(0\\)颜色的球以及添加一种颜色的\\(k-1\\)个球:

\begin{aligned}
    f(i-1, j) & \leftarrow f(i, j) \mid [i > j] \\\\
    f(i, j-1) & \leftarrow f(i, j) \times {n-i + (n-j) \times (k-1) + k-2 \choose k-2}
\end{aligned}

> 后面那个公式是可重集, 还有最后的答案要乘以 \\(n!\\).

## AGC005 D ~K Perm Counting

> 求长度为\\(N\\)的排列中, 满足对任意的\\(i\\), 都有\\(|a_i - i| \neq K\\)的排列数量. 
>
> \\(1 \leq K \lt N \leq 2000\\)

考虑容斥, 计算至少有\\(i\\)个位置不合法的方案数. 由于\\(K\\)是确定的, 那么所有不合法的方案可以看成是完全二分图匹配中出现了一条\\((i, i+k)\\)的边或者一条\\((i, i-k)\\)的边.

将这样的边在画出来就是若干条交叉路径. 观察到这样的交叉路径不相交, 所以可以拆开拼成一个序列, 然后在序列上DP即可.

## AGC015 D A or...or B Problem

> 求在\\([A, B]\\)中任意选出一个非空整数集合的元素位或和有多少种不同的答案.
>
> \\(1 \le A \le B \le 2^{60}\\)

先考虑一些比较特殊的情况(以下默认\\(A, B\\)的位数相同):

- 当\\(B\\)可以表示为\\(2^k - 1\\)时, 这个位或和恰好取遍\\([A, B]\\)之间的所有整数.
- 当\\(A\\)可以表示为\\(2^k\\)时, 这个位或和在区间\\([A, A + 2^{t+1}) \mid t \lt \log_2 A\\)中, 其中\\(t\\)是最大的满足\\(B\\)的第\\(t\\)位为\\(1\\)的数.

 那么一般情况下这些条件有什么用呢?

我们考虑找到最大的一个\\(T\\),使得\\(B\\)的第\\(T\\)位为\\(1\\)且\\(A\\)的第\\(T\\)位不为\\(1\\), 记\\(K = 2 ^ T\\). 当选择的数的集合在\\([A, K)\\)以及在\\([K, B]\\)中的情况可以直接用上述结论.

接下来考虑同时选取两个集合中的数可能会产生的答案. 因为这时小于\\(K\\)的部分是没有贡献的, 所以直接将\\([A, K)\\)中的所有答案取出. 不难发现\\([K, B]\\)中取任意个都与只使用\\(K\\)没有区别, 那么这时候的范围是\\([K+A, 2\times K-1]\\), 注意减去重复贡献.

## AGC015 F Kenus the Ancient Greek

> \\(Q\\) 组询问, 每组询问的形式为A, B, 表示求\\(x \in [1, A], y \in [1, B]\\)的\\(g(x, y)\\)的最大值, 及最大值的方案数, 其中: 
>
> \\[ g(x, y) = \begin{cases} 1, & \text{y = 0} \\\\ g(y, x), & \text{x > y} \\\\ g(y \bmod x, x) + 1, & \text{otherwise} \\\\ \end{cases} \\]
>
> \\(1 \le Q \le 3 \times 10 ^ 5,  1 \le A, B \le 10 ^ {18}\\)

**以下无特殊说明, 均默认所有\\(x < y, A < B\\)**

先考虑第一问, 如果我们由一个特定的\\((x, y)\\), 从小到大地构造使得\\(g(x, y)\\)的值不断地变大, 那么如何构造使得这个值最大呢?
 对于所有\\((x', y')\\)满足\\(g(x', y') = g(x, y) + 1\\), 显然有:
$$
(x', y') \in \\{ (y, x + ky) \mid k \in Z^+ \\} 
$$
同时, 为了使得这个过程尽可能的多次进行,我们从\\((0, 1)\\)出发, 每次取\\(k = 1\\). 
发现这样生成了一组`Fibonacci`数列, 这里`Fibonacci`数列从0开始标号. 
 那么第一问的答案就是求满足\\(F_k \le A, F_{k+1} \le B\\)的最大的\\(k\\). 同时, 这样的数对是满足\\(g(x, y) = k\\)的最小的数对.
接下来考虑统计方案数. 首先, 对于一组询问我们只需考虑其中**与最优解相关**的\\((x, y)\\).
考虑所有最优的\\((x, y)\\)会具有的性质:

- \\(x \ge F_k, y \ge F_{k+1}\\)
- 不存在一组\\((x' \lt x, y' \lt y)\\), 使得\\(g(x', y') > g(x, y)\\)

然而这样的\\((x, y)\\)并不一定是最优的.
 我们接着分析所有在最优解的\\(g\\)的计算路径上的数对\\((x, y)\\)的性质: 不难发现, 经过一次变化后得到的\\((x', y')\\), 一定满足:

- \\(g(x', y') = k-1\\)
- \\(x' \ge F_{k-1}, y' \ge F_{k}\\)
- \\(y' \le F_{k+1} + F_{k-2}\\)

后面条件的解释: 若\\(y' > F_{k+1} + F_{k-2}\\), 则:
$$
(x, y) = (y' > F_{k+1} + F_{k-2} > F_{k+1}, x' + py' \ge x' + y' > F_{k+2})
$$
\\((x, y)\\)不再满足上述最优性质2, 矛盾.
 同时每次向下一步进行构造的时候只有\\((Fib_k, Fib_{k+1})\\)可能取到\\(p = 2\\)所以这样的数对个数是\\(O(k)\\)的. 所以我们预处理所有的这样的数对, 然后用除法算下答案就好了.
 复杂度\\(O(\log^2{\text{MAX}} + Q\log \text{MAX})\\).

# ARC

ARC 的题目主要来源是打过的几场比赛, 暂时不多.

## ARC074 E RGB Sequence

> 给你一个长度为\\(N\\)的序列和\\(M\\)组约束条件, 每组条件形如\\(L_i, R_i, X_i\\), 表示序列上的\\([L_i, R_i]\\)中恰好有\\(X_i\\)种颜色, 现在要你用三种颜色给这个序列染色, 求满足所有约束的方案数.
>
> \\(1 \le N, M \le 300\\)

DP思路应该比较显然, 然而普通的状态表示不太好处理. 我们记\\(dp_{r, g, b}\\)表示三种颜色的球最后一次出现的位置分别是\\(r, g, b\\)时的方案数. 

然后考虑状态的合法性, 可以把条件存在\\(R_i\\)的位置. 当选择一个状态时, 考虑这个状态的最末位的所有约束即可. 

## ARC077 F SS

> 定义一个字符串为偶的, 当且仅当这个字符串能够被分成两个完全相同的字符串.
>
> 定义函数\\(f(s)\\), 其中\\(s, f(s)\\)均是字符串,\\(f(s)\\)为在字符串\\(s\\)后添加非空的字符满足新串为偶且长度最小的串. 现在给你串\\(s\\)(初始为偶的), 求\\(f^{10^{100}}(s)[L, R]\\)中各个字母的出现次数.
>
> \\(1 \le |S| \le 2\times 10^5\\)
>
> \\(1 \le L \le R \le 10^{18}\\)

首先对于一个给定的\\(s\\), 其\\(f(s)\\)必定唯一. 考虑每次最少加一个字符,\\(f^{10^{100}}(s)\\)就等价于一个长度无穷的字符串. 这个答案的形式显然可以前缀和, 又因为\\(s\\)在变化过程中始终是偶的, 实际上我们只需要关注左半部分的字符.

我们从最简单的一次操作来考虑. 记初始的字符串\\(s\\)为\\(SS\\), 记一次变化之后左边的部分为\\(ST\\), 那么得到的新串就是\\(STST\\). 要使得加的字符长度最小, 就要在\\(S\\)中找到最长前后缀匹配长度, 这时\\(T\\)就是\\(S\\)去掉最长匹配后缀所得.

我们发现, 每次操作都等价于找到前后缀匹配最大长度(当然要小于\\(|S|\\)), 然后将剩下部分的前缀\\(T\\)添加到\\(S\\)的末尾.

- 当\\(|T| \mid |S|\\)时,\\(|S|\\)有长为\\(|T|\\)的最小周期, 每次加入的\\(|T|\\)相同.
- 当\\(|T| \nmid|S|\\)时, 我们~~通过打表~~发现, 这样的\\(T\\)是在有规律地变化的, 因为每次加入\\(T\\)之后的串前后缀最长匹配一定是\\(|T|\\), 否则的话, 上一步中最长匹配的性质就不一定会满足.

然后我们得到了一个`Fibonacci`数列? 直接暴力算就好了... 实际上第一种情况也可以直接算, 因为整个序列都是\\(T\\)的若干次重复得到的.
