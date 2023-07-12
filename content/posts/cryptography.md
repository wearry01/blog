---
title: Cryptography Notes
date: 2020-07-07 21:37:14
tags:
    - Probability
    - Number Theory
    - Induction
draft: true
---

Some notes of 🔒 cryptography lessons 

**TODO**: 

- [x] Reconstruct the architecture of this post
- Complete other contents
    - [x] I: Pseudorandomness
    - [x] II: Cipher
    - [ ] III: MAC
    - [ ] IV: Attack & Security
    - [ ] V: Public-key Cryptography

<!--more-->

# *Preliminary: Fundamental Discrete Probability*

Suppose $U$ is a finite set.

## *Probability Distribution*

> a `probability distribution` $P$ over $U$ is a function
> $$P: U \rightarrow [0,1]$$
> s.t.
> $$\sum_{x \in U} P(x) = 1$$

Some examples:

- Uniform distribution: $\forall x \in U, P(x) = \dfrac{1}{|U|}$
- Pointed distribution: $\exists x \in U, P(x) = 1$

## *Event*

> an `event` is a subset $E$ of $U$, define the probability of $E$ under `probability distribution` $P$ as below:
> $$Pr[E] = \sum_{x \in E} P(x)$$

### *The Union Bound*

By definition, we can obviously get:

$$Pr[A_1 \cap A_2] + Pr[A_1 \cup A_2] = Pr[A_1] + Pr[A_2]$$

Which also implies that:

$$Pr[A_1 \cup A_2] \le Pr[A_1] + Pr[A_2]$$

## *Random Variable*

> a `random variable` $X$ is a function 
> $$X:U \rightarrow V$$
> where $V$ is **range** of $X$

Example [^1]:

$$
\begin{aligned}
X:\{0, 1\}^n \rightarrow \{0, 1\} \\
X(b) = LSB(b) \in \{0, 1\}
\end{aligned}
$$ 

As you can see, `random variable` $X$ can also induce `probability distribution` from $U$ to $V$ (Suppose $P$ is a distribution on $U$):

$$
\forall v \in V, Q(v) = Pr[X = v] = Pr[X^{-1}(v)]
$$


### *Uniform Random Variable*

Specially, when $P$ is uniform distribution and $X(r) = r$ for all $r \in U$, then:

$$
\forall r \in U, Pr[X = r] = \frac{1}{|U|}
$$

this is called `uniform random variable`, denoted by $X \xleftarrow{R} U$

## *Independence*

- Two `events` $A, B$ are independent **iff**: $Pr[A \cap B] = Pr[A] \times Pr[B]$
- Two `random variables` $A, B$ are independent **iff** $\forall a \in V_A, b \in V_B$:

$$
Pr[A = a \,\,\mathrm{and}\,\, B = b] = Pr[A = a] \times Pr[B = b]
$$

> For better understanding of independence, consider the example below:
> Suppose a dice numbered by $D = \{1, 2, \dots, 6\}$ and 2 `random variables` $A, B$:
> $$ \begin{aligned}
> &A:D \rightarrow \{0, 1\} &A(x) = [x \equiv 0 \pmod 2] \\
> &B:D \rightarrow \{0, 1\} &B(x) = [x \equiv 0 \pmod 3] 
> \end{aligned} $$
> For uniform distribution of $D$, $A, B$ are obviously independent. Think about conditions below:
>
> 1. $B(x) = [x \equiv 0 \pmod 4]$
> 2. $D = \{1, 2, \dots, 5\}$

## *More about Probability*

[See also](https://crypto.stanford.edu/~blynn/pr/)

# *I: Pseudorandomness*

`Pseudorandomness` measures the extent to which a sequence of numbers, though produced by a completely deterministic and repeatable process, appear to be patternless.

## *Pseudo-random Generator*

A `Pseudo-random Generator`, or `PRG` for short, is an efficient, deterministic algorithm $G$ that given as input a `seed` $s$, computes an output $r$. 
Both $s$ and $r$ come from a finite space, called $\mathcal{S}$ and $\mathcal{R}$ respectively.

Typically $\mathcal{S}$ and $\mathcal{R}$ are sets of bit strings of some prescribed length. We can also regard $G$ as an abstract function defined over $\mathcal{(S, R)}$:

$$
G: \mathcal{S} = \{0, 1\}^l \rightarrow \mathcal{R} = \{0, 1\}^L
$$

### *Security*

We say a PRG $G$ is secure if $G(s)$ and $r$ are **computational indistinguishable**, among which $s$ is chosen uniform randomly from $\mathcal{S}$ and $r$ is chosen at random from $\mathcal{R}$.

To illustrate **computational indistinguishability**, the definition is formulated as an attack game:

> #### *Attack Game (PRG) and Advantage*
>
> For a given PRG $G$ defined over $\mathcal{(S, R)}$, 
> and for a given adversary $\mathcal{A}$, 
> we define two experiments, Experiment $0$ and Experiment $1$:
>
> **Experiment** $b$:
>
> - The Challenger computes $r \in \mathcal{R}$ as follows:
>     ![PRG-ADV](/img/PRG-ADV.png)
> 
>     - if $b = 0$, $s \xleftarrow{R} \mathcal{S}, r \leftarrow G(s)$
>     - if $b = 1$, $r \xleftarrow{R} \mathcal{R}$
> 
> - Given $r$, the adversary computes and outputs a bit $\hat{b} \in \{0, 1\}$
> 
> For $b \in \{0, 1\}$, let $W_b$ be the event that $\mathcal{A}$ outputs $\hat{b} = 1$ in Experiment $b$. We define $\mathcal{A}$'s `advantage` with respect to $G$ as
> 
> $$
> PRG_{adv} [\mathcal{A}, G] = \left|Pr[W_0] - Pr[W_1]\right|
> $$

Now we can define a PRG $G$ is **secure** if the value $PRG_{adv} [\mathcal{A}, G]$ is negligible [^3] for all efficient adversaries $\mathcal{A}$.

## *Pseudo-random Function*

A `Pseudo-random Function(PRF)` $F$ is a deterministic algorithm that has two inputs: a `key` $k$ and an `input data block` $x$; its output $y := F(k, x)$ is called an
`output data block`. We denote the finite space of $k, x, y$ with $(\mathcal{K, X, Y})$, over which is $F$ defined.

Intuitively, our notion of security says that for a randomly chosen key $k$, $F(k, \cdot )$ is indistinguishable from a random function from $\mathcal{X}$ to $\mathcal{Y}$

> ### **Notation**
> $$
> Funs[\mathcal{X, Y}] = \{f: \mathcal{X} \rightarrow \mathcal{Y}\}
> $$
> clearly we know that
> $$
> |Funs[\mathcal{X, Y}]| = |\mathcal{Y}|^{|\mathcal{X}|}
> $$

### *Attack Game (PRF)*

Similarly we can define two experiments, Experiment $0$ and $1$, for a PRF $F$ defined over $(\mathcal{K, X, Y})$:

**Experiment** $b$:

- The challenger selects $f$ as follows:
    - if $b = 0$, $k \xleftarrow{R} \mathcal{K}, f \leftarrow F(k, \cdot)$
    - if $b = 1$, $f \xleftarrow{R} Funs[\mathcal{X, Y}]$
- The adversary $\mathcal{A}$ submits a sequence of queries $x_1, \dots, x_q$, and receives $y_i = f(x_i)$ for each $i$ from the challenger
- The adversary computes $\hat{b} \in \{0, 1\}$

Let $W_b$ be the event $\mathcal{A}$ outputs $1$ in Experiment $b$, the `advantage` is also defined by:

$$
PRF_{adv} [\mathcal{A}, F] = |Pr[W_0] - Pr[W_1]|
$$

We say a PRF $F$ is **secure** if all efficient adversary $A$ have a negligible advantage.

## *Pseudo-random Permutation*

Also called [Block Cipher](#bc), is a special PRF which is also invertible.

# *II: Cipher*

Throughout history, there were many ways of encryption, however, some of them have been proved unsafe. The question now is whether a particular `cipher` is **secure** and how to construct a **secure** one.

> A `cipher` defined over a triple $(\mathcal{K, M, C})$ is a pair of **efficient**[^2] algos $(E, D)$ where:
>
> $$
> \begin{aligned}
> E: \mathcal{K \times M} \rightarrow \mathcal{C} \\
> D: \mathcal{K \times C} \rightarrow \mathcal{M}
> \end{aligned}
> $$
> s.t. $\forall m \in \mathcal{M}, k \in \mathcal{K}$
> $$
> m = D(k, E(k, m))
> $$
> and $\mathcal{K, M, C}$ denote the space of keys, messages and cipher texts.

## *Stream Cipher*

The example below shows the basic idea of stream cipher.

### *One Time Pad* {#otp}

An example cipher over $\mathcal{K, M, C} = \{0, 1\}^n$ and:

$$
\begin{aligned}
E(k, m) &= k \oplus m \\
D(k, c) &= k \oplus c \\
\end{aligned}
$$

## *Perfect Secrecy*

The basic idea behind perfect secrecy is: cipher text should reveal no "info" about plain text.

> A `cipher` $(E, D)$ over $\{\mathcal{K, M, C}\}$ has `perfect secrecy` **iff**:
>
> $\forall m_0, m_1 \in \mathcal{M} \,\,\mathrm{that}\,\, |m_0| = |m_1|, c \in \mathcal{C}$:
> $$Pr[E(k, m_0) = c] = Pr[E(k, m_1) = c]$$
> where $k \xleftarrow{R} \mathcal{K}$

It's not hard to see that when attacker gets a cipher text, he will have no idea what the plain text is. By definition, we can also prove [One Time Pad](#otp) has `perfect secrecy`.

However, `perfect secrecy` is too hard to satisfy because we have theorem says:

> If a `cipher` has `perfect secrecy`, then:
> $$|\mathcal{K}| \ge |\mathcal{M}|$$
> which means the length of keys mustn't less than length of messages. 

That somehow makes no sense for if we have some way sending and receiving such long keys secretly, then it's absolutely unnecessary to use `cipher`.

### *Stream Cipher in Practice*

However, `One Time Pad` is not mainly used in practice because:

1. The key space $\mathcal{K}$ is as large as message space $\mathcal{M}$, which makes no sense in communication.
2. For two same message segments in different positions, they would also be same in the cipher text.

In practice, we have to change some details to solve these problems:

1. We can implement a `PRF` $G$ with seed space $\mathcal{S}$ much less than the message space $\mathcal{M}$, and rewrite the process of encryption and decryption as:
$$
\begin{aligned}
E(k, m) &= G(k) \oplus m \\
D(k, c) &= G(k) \oplus c
\end{aligned}
$$
By the properties of `PRF` we could argue the security.

2. To solve this problem, we can change the key after a fixed length of message or using a nonce, the later one will appear in remain chapters.

## *Block Cipher* {#bc}

A `block cipher` defined over $(\mathcal{K, X})$ is a deterministic $(E, D)$ whose message space and cipher space is same (finite) set $\mathcal{X}$.
Additionally, for each $k \in \mathcal{K}$, it's necessary that $E(k, \cdot)$ is invertible, 
which also means $f_k := E(k, \cdot)$ is an one-to-one map on finite set $\mathcal{X}$ and $D(k, \cdot) = f_k^{-1}$.

It's not hard to see that $D(k, E(k, m)) = m$, so the point now is to argue the security of `block cipher` (also called `Pseudo-random Permutation`, `PRP`).
Before that, let's focus on the properties of invertible function on a finite set $\mathcal{X}$:

1. Some notation:
$$
Perm[\mathcal{X}] = \{F \in Funs[\mathcal{X, X}] : F \text{ is invertible}\}
$$

2. Obviously:
$$
|Perm[\mathcal{X}]| = |\mathcal{X}|!
$$

### *Attack Game (PRP) & Security*

Similarly with the idea used in attacking `PRF`, 
we design an attack game for a certain `block cipher` (or `PRP`) $\mathcal{E} = (E, D)$ over $(\mathcal{K, X})$ against an attacker $\mathcal{A}$:

Experiment $b$:

1. Challenger selects $f$ as follow

    - if $b = 0$, $k \xleftarrow{R} \mathcal{K}, f = E(k, \cdot)$
    - if $b = 1$, $f \xleftarrow{R} Perm[\mathcal{X}]$
2. Attacker choose a sequence of input $x_1, x_2, \dots, x_q$, and get $y_i = f(x_i)$ from the challenger.
3. Attacker output a $\hat{b} \in \{0, 1\}$.

The advantage is defined as:

$$
BC_{ADV}[\mathcal{A, E}] = |Pr[W_0] - Pr[W_1]|
$$

where $W_b$ describe the event that $\mathcal{A}$ outputs $\hat{b} = 1$ in Experiment $b$, 
$\mathcal{E}$ is **secure** if the advantage is negligible for all efficient algorithm $\mathcal{A}$.

### Practice

In practice, we often divide messages into "blocks", then implement `block cipher` to them and concate to get the cipher text.

# *III: Message Integrity*

In previous chapters, we mainly focused on security against an eavesdropping adversary, which could not change messages en-route.
In this chapter we turn out attention to active adversaries by startting with the basic question of *message integrity*: Bob receives a message $m$ from Alice,
and he wants to convince himself that the message was not modified en-route. 

Alice could send a extra tag $t$ of message $m$ to Bob, when Bob receives the pair $(m, t)$, 
he can determine that by recalculating the tag of $m$ and then checking whether it is $t$.

## *Message Authentication Code (MAC)*

A `MAC` system $\mathcal{I} = (S,V)$ is a pair of efficient algorithms, $S$ and $V$, where $S$ is called a `signing algorithm` and $V$ is called a `verification algorithm`.
$S$ is used to generate tags and $V$ is to verify tags.

- $S$ is a probabilistic algorithm that is invoked as $t \xleftarrow{R} S(k, m)$, where $k$ is a key, $m$ is a message.
- $V$ is a deterministic algorithm that is invoked as $r = V(k, m, t)$, where $k$ is a key, $m$ is a message, $t$ is a tag, and $r \in \{0, 1\}$
- For all keys and all messages:

$$
V(k, m, S(k, m)) = 1
$$

As usual, we say that keys, messages and tags lie in some finite key space $\mathcal{K, M, T}$. We say that $\mathcal{I} = (S, V)$ is defined over $\mathcal{K, M, T}$.

## *Security of MACs*

Suppose an adversary is attacking a MAC system $\mathcal{I} = (S, V)$. Let $k$ be some randomly chosen MAC key, which is unknown to the attacker. We allow the attacker to request tags $t := S(k, m)$ for arbitrary messages $m$ of its choice. And the attacker need to come up with a *new* pair $(m, t)$ satisfies $V(k, m, t) = 1$.

# *IV: Attack & Security*

# *V: Public-key Cryptography*

[^1]: LSB is a function which gets the last significant bit of a bit-string.
[^2]: Theoretically, efficient means runs in polynomial time; Practically it means runs within a certain time period.
[^3]: Negligible means small enough so that cannot be detected even by enormous samples.
