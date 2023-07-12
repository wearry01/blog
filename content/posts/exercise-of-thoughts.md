---
title: 趣味数学题
date: 2020-02-10 22:04:22
description: 收集一些有意思的题目
categories:
    - 趣题
---

Basel Series
---

Calculate 

$$
\sum_{n=1}^{\infty} \frac{1}{n^2} = 1 + \frac{1}{2^2} + \frac{1}{3^2} + \dots
$$

### Analytical Perspective

First notice that：

$$
\begin{aligned}
    I=&\int_0^1 \mathrm{d} x \int_0^1 \frac{1}{1-xy} \mathrm{d} y \\\\
    =&\iint_D \sum_{i=0}^{\infty} (xy)^i \mathrm{d}x\mathrm{d}y \\\\
    =&\sum_{i=0}^{\infty} \iint_D (xy)^i \mathrm{d}x\mathrm{d}y \\\\
    =&\sum_{i=0}^{\infty} \left(\int_0^1 x^i \mathrm{d} x\right)^2 \\\\
    =&\sum_{i=1}^{\infty} \frac{1}{i^2}
\end{aligned}
$$

Now just need to calculate \\(I\\)，replace variables：

$$
\begin{cases}
    x = u + v \\\\
    y = u - v
\end{cases},
\frac{\partial(x, y)}{\partial(u, v)} = \left|\begin{matrix} 1 & 1 \\\\ 1 & -1 \end{matrix} \right| = -2
$$

then：

$$
\begin{aligned}
I &= 2 \iint_{D_{uv}} \frac{1}{1 - u^2 + v^2} \mathrm{d} u \mathrm{d} v \\\\
&= 4 \left(\int_0^{\frac{1}{2}} \mathrm{d} u \int_0^{u} \frac{1}{1-u^2+v^2} \mathrm{d} v + \int_{\frac{1}{2}}^{1} \mathrm{d}u \int_0^{1-u} \frac{1}{1-u^2+v^2} \mathrm{d} v\right) \\\\
&= 4 \left(\int_0^{\frac{1}{2}} \frac{1}{\sqrt{1-u^2}} \arctan \frac{u}{\sqrt{1-u^2}} \mathrm{d} u + \int_{\frac{1}{2}}^{1} \frac{1}{\sqrt{1-u^2}} \arctan \frac{1-u}{\sqrt{1-u^2}} \mathrm{d} u\right) \\\\
&= 4 \left(\int_0^{\frac{1}{2}} \arctan \frac{u}{\sqrt{1-u^2}} \mathrm{d} \arctan \frac{u}{\sqrt{1-u^2}} 
  -2       \int_{\frac{1}{2}}^1 \arctan \frac{1-u}{\sqrt{1-u^2}} \mathrm{d} \arctan \frac{1-u}{\sqrt{1-u^2}} \right) \\\\
&= 4 \times \frac{1}{2} \times \left(\frac{\pi}{6}\right)^2 + 4 \times \left(\frac{\pi}{6}\right)^2 = \frac{\pi^2}{6} \\\\
&& \square
\end{aligned}
$$

### Algebraic Perspective

From Taylor's series, we know that:

$$
\sin(x) = x - \frac{x^3}{3!} + \frac{x^5}{5!} - \dots
$$

Let:

$$
f(x) = \frac{\sin(x)}{x} = 1 - \frac{x^2}{3!} + \frac{x^4}{5!} - \dots
$$

Obviously the roots of \\(f(x)\\) are \\(n\pi, n \in \mathbb{Z} \backslash \{0\}\\), hence:

$$
f(x) = (1 - \frac{x}{\pi})(1 + \frac{x}{\pi})(1 - \frac{x}{2\pi})(1 + \frac{x}{2\pi})\dots
$$

Consider the coeficient of \\(x^2\\), we have:

$$
-\left(\frac{1}{\pi^2} + \frac{1}{(2\pi)^2} + \frac{1}{(3\pi)^2} + \dots\right) = -\frac{1}{3!}
$$

Which also shows that:

$$
\sum_{n=1}^{\infty} \frac{1}{n^2} = \frac{\pi^2}{6}
$$

### Application

> What's the probability that any two arbitrary positive integers are **relatively prime**?

For any prime \\(p\\)，those integers won't be **relatively prime** if they are both multiples of \\(p\\), thus the probability is:

$$
\begin{aligned}
P &= \prod_{p\, \mathrm{is\ prime}} \left(1 - \frac{1}{p^2}\right) \\
&= \prod_{p\, \mathrm{is\ prime}} \cfrac{1}{\displaystyle \sum_{i=0}^{\infty} \left(\cfrac{1}{p^2}\right)^i} \\
&= \frac{1}{\displaystyle \sum_{i=1}^{\infty} \frac{1}{i^2}} \\
&= \frac{6}{\pi^2}
\end{aligned}
$$

Birthday Paradox
---

> There are \\(k\\) people whose birthdays are among set \\(B\\) with size \\(n\\), 
> the probability that there are **at least** a pair of people have the same birthday is greater than \\(\frac{1}{2}\\) when \\(k \ge 1.2 \sqrt{n} + 1\\)

### Proof

Suppose each person's birthday is **independent uniform** in \\(B\\), 
then the probability that don't exist such a pair is:

$$
P = \prod_{i=0}^{k-1} \left(1 - \frac{i}{n}\right)
$$

to prove \\(P \le \frac{1}{2}\\), we use the result in analysis that:

> \\(\forall x \in \mathbb{R}, 1 + x \le \mathrm{e}^x\\)
> ![](/images/exp.png) 

then:

$$
\begin{aligned}
P &\le \exp \left(\sum_{i=0}^{k-1} -\cfrac{i}{n}\right) \\\\
&\le \exp \left(-\frac{(k-1)^2}{2n}\right) \\\\
&\le \exp \left(-\frac{(1.2 \sqrt{n})^2}{2n}\right) \\\\
&= \exp(-0.72) < \frac{1}{2} \\
\end{aligned}
$$
