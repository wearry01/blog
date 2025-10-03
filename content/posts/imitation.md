+++
title = "与不可区分的随机共舞"
author = ["Wearry"]
date = 2024-06-11T22:52:00+08:00
lastmod = 2025-10-03T14:07:05+08:00
tags = ["TCS"]
draft = false
+++

## 模仿游戏 {#模仿游戏}

1950 年，英国曼彻斯特。

Alan Turing 在其影响深远的论文 _Computing Machinery and Intelligence_
中探讨了「机器能否思考」这一问题，并给出了他的判断方法——即著名的图灵测试 (The Turing Test):

{{< figure src="/images/turing test.jpg" >}}

> 如果人类无法区分屏幕后与其对话的是另一个人类个体还是某种计算机器，则称这台它具有机器智能。

大半个世纪后的今天，GPT 的横空出世和快速发展已经让越来越多的人相信，机器智能将在可预见的未来中实现，一些观点甚至认为 GPT 已经通过了 “图灵测试”&nbsp;[^fn:1]。尽管自提出以来，类似的争议以及对图灵测试本身的质疑从未停息，其中 **不可区分** 的哲学也影响了计算机科学的基础。在图灵测试提出 6年后，以色列海法一个护士和电气工程师组成的家庭中诞生的一个孩子，将在其中做出突出贡献，并以此让自己的名字和图灵紧密联系在一起。


## Avi Wigderson 简介 {#avi-wigderson-简介}

1956 年，Avi Wigderson 出生在以色列海法。

1977 年，Wigderson 进入以色列理工学院学习并于 1980 年毕业，之后进入普林斯顿大学攻读研究生，1983 年在导师 Richard Lipton 指导下完成题为
_Studies in Combinatorial Complexity_ 的博士论文，并获得了计算机科学博士学位。1999 年，Wigderson 加入了普林斯顿高等研究院 (IAS)，并在那里工作至今。2016 年，在一场庆祝 Wigderson 60 岁生日的活动中，IAS 院长
Robbert Dijkgraaf 说，他开创了该研究院在理论计算机科学领域的黄金时代。

因 **理论计算机科学与离散数学方面的奠基性贡献** ，Wigderson 于 2021 年与布达佩斯罗兰大学的数学家 László Lovász 共享了阿贝尔奖。并于 2024 年4
月 10 日，被 ACM 授予 2023 年图灵奖，以表彰他对 **计算理论的基础性贡献，包括塑造对计算中随机性作用的理解** 。由此，他也成为了唯一一个同时摘得数学领域阿贝尔奖和计算机科学领域图灵奖的学者。


## 不可区分的随机性 {#不可区分的随机性}

Wigderson 具有重大影响力的一系列工作——也是获授图灵奖的代表性工作——关于计算中随机性的理解。

20 世纪 70 年代末，计算机科学家逐渐意识到，对于许多难题，允许计算机通过抛掷硬币来使用随机性可以得到更好的算法。例如，在 1977 年，Robert
Solovay 和 Volker Strassen 引入了一种随机算法，可以比当时最好的确定性算法更快地确定一个数字是否为素数&nbsp;[^fn:2] 。

另一方面，对于某些问题，概率算法也反过来指导了确定性算法的设计。20 世纪 80 年代初，Wigderson 与加州大学伯克利分校的 Richard Karp 合作，他和
Karp 发现了一种针对某个难题的随机算法，后来他们能够将其去随机化并得到确定性算法。大约在同一时间，其他研究人员展示了密码学问题中的计算难度假设如何能够实现一般的去随机化。

上述两个事实似乎为 **随机性在计算中有效** 与 **随机性在计算中无关紧要** 两个相对的方向分别提供了证据，也促使 Wigderson 开始思考随机性在计算中是否真正必要。在与 Noam Nisan 合作的文章 _Hardness
vs. Randomness_&nbsp;[^fn:3]中，他们注意到可以基于 _计算困难_ 的问题——即对某类计算机器来说不存在确定性高效算法的问题，构造针对这类计算机器的伪随机数生成器 (Pseudo Random Generator, PRG)，并利用这样的 PRG 消除计算过程中对随机性的依赖。

> 伪随机数生成器是实际计算机器中常用的引入 “随机” 的方式，能从长度较短的随机种子生成更长的伪随机串。在理论计算的语境下，通常要求其输出与相同长度的真随机串无法在某些计算限制下有效区分。

Wigderson 敏锐地观察到，计算困难问题某种意义上来说天然地提供了这样的不可区分的条件——无法高效地区分不同计算结果对应的输入，而不可区分性恰恰是设计 PRG 的关键！进一步地，通过高效遍历 PRG 在所有短随机种子上生成的伪随机串，Wigderson 与 Nisan 能够从一类计算机器中的随机算法得到效率相近的确定性算法。后续的工作中，Wigderson 与其他合作者进一步基于另一些与线路复杂性有关的假设得到有关概率多项式算法的去随机化结果&nbsp;[^fn:4],&nbsp;[^fn:5]。

从信息论的观点来看，不可区分和随机，实际上都在描述信息量不足这同一件事情。而 Wigderson 的研究则为我们在计算理论的视角揭示了这两者之间的紧密关联，计算困难性最终也将我们引向了计算意义下的随机性。


## 结语 {#结语}

“不可区分” 哲学的身影，也时常出现在计算机科学的其它分支中。不管是训练 AI 模型生成画作、音乐使之与人类创作无法区分，还是设计加密算法使加密的信息和不包含有意义信息的随机串之间不可区分，这样的哲学都在背后指导着计算机科学的发展进步。

Wigderson 在不可区分与随机性上的深刻见解，在帮助我们更好地认识计算与随机之间关系的同时，也给了我们启发：当发现两片看起来一模一样的叶子时，在沮丧于它们的难以区分之前，也许值得高兴的一点是——我们找到了与前一片叶子能够胜任的工作相同的又一片叶子！

[^fn:1]: Biever, Celeste.  _ChatGPT broke the Turing test — the race is
    on for new ways to assess AI_ Nature. 2023-07-25, 619 (7971)
[^fn:2]: Solovay, Robert M., Strassen, Volker.  _A fast Monte-Carlo test
    for primality_.  SIAM Journal on Computing. 6 (1): 84–85 (1977).
[^fn:3]: Noam Nisan, Avi Wigderson.  _Hardness vs Randomness._ Journal
    of Computer and System Sciences. 49(2): 149-167 (1994).
[^fn:4]: Babai, L., Fortnow, L., Nisan, N. et al.  _BPP has
    subexponential time simulations unless EXPTIME has publishable
    proofs._ Computational Complexity 3, 307–318 (1993).
[^fn:5]: Russell Impagliazzo, Avi Wigderson.  _P = BPP if E Requires
    Exponential Circuits: Derandomizing the XOR Lemma._ STOC 1997: 220-229
