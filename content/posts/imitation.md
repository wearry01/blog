+++
title = "不可区分、随机与零知识"
author = ["Wearry"]
lastmod = 2024-05-12T23:31:03+08:00
draft = true
+++

## 模仿游戏 {#模仿游戏}

1950 年，英国曼彻斯特。

阿兰·图灵 (Alan Turing) 在其影响深远的论文 _Computing Machinery and Intelligence_
中探讨了 “机器能否思考” 这一问题，并给出了他的判断方法——即著名的 “图灵测试” (The Turing Test):

{{< figure src="~/Downloads/aHR0cDovL3AuYW5hbmFzLmNoYW94aW5nLmNvbS9zdGFyMy9vcmlnaW4vNzYwNzI1NDI1MWY4ZDFjOWIwMDJiODQ1N2M2Zjc2NmIuanBn.png" >}}

> 如果人类无法区分屏幕后与其对话的是另一个人类个体还是某种计算机器，则称这台它具有机器智能。

大半个世纪后的今天，GPT 的横空出世和快速发展已经让越来越多的人相信，
机器智能将在可预见的未来中实现，一些观点甚至认为 GPT 已经通过了 “图灵测试”&nbsp;[^fn:1]。
尽管自提出以来，类似的争议以及对图灵测试本身的质疑从未停息，
其中 **不可区分** 的哲学却为计算机科学的另一个分支——理论计算——埋下了一颗种子。
在图灵测试提出 6 年后，以色列海法一个护士和电气工程师组成的家庭中诞生的一个孩子，
将为这颗种子长成参天大树的过程作出突出贡献，并以此让自己的名字和图灵紧密联系在一起。


## Avi Widgerson 简介 {#avi-widgerson-简介}

1956 年，Avi Widgerson 出生在以色列海法。

1977 年，Widgerson 进入以色列理工学院学习并于 1980 年毕业，之后进入普林斯顿大学攻读研究生，
1983 年在导师 Richard Lipton (理查德·利普顿) 指导下完成题为
_Studies in Combinatorial Complexity_ 的博士论文，并获得了计算机科学博士学位。
1999 年，Wigderson 加入了普林斯顿高等研究院 (IAS)，并在那里工作至今。
2016 年，在一场庆祝 Wigderson 60 岁生日的活动中，IAS 院长 Robbert Dijkgraaf 说，
他开创了该研究院在理论计算机科学领域的黄金时代。

因 **理论计算机科学与离散数学方面的奠基性贡献** ，
Widgerson 于 2021 年与布达佩斯罗兰大学的数学家 László Lovász 共享了阿贝尔奖。
并于 2024 年 4 月 10 日，被 ACM 授予 2023 年图灵奖，
以表彰他对 **计算理论的基础性贡献，包括塑造对计算中随机性作用的理解** 。
由此，他也成为了唯一一个同时摘得数学领域阿贝尔奖和计算机科学领域图灵奖的学者。


## 理解随机性 {#理解随机性}

Widgerson 其中一系列具有重大影响力的工作——
也是 ACM 官方在授予 Widgerson 图灵奖的通告中提到的代表性工作——是关于计算中随机性的理解。

到 20 世纪 70 年代末，计算机科学家已经意识到，对于许多难题，
允许计算机通过抛掷硬币来使用随机性可以得到相比确定性替代方案更好的算法。
例如，在 1977 年，Robert Solovay 和 Volker Strassen 引入了一种随机算法，
可以比当时最好的确定性算法更快地确定一个数字是否为素数。

另一方面，对于某些问题，概率算法似乎可以指向确定性算法。
20 世纪 80 年代初，Wigderson 与加州大学伯克利分校的 Richard Karp 合作，
他和 Karp 发现了一种针对某个难题的随机算法，后来他们能够将其去随机化，
从而有效地揭示了它的确定性算法。大约在同一时间，
其他研究人员展示了密码学问题中的计算难度假设如何能够实现一般的去随机化。


## 不包含知识的 “证明” {#不包含知识的-证明}

[^fn:1]: Biever, Celeste. ChatGPT broke the Turing test — the race is on for new ways to assess AI. Nature. 2023-07-25, 619 (7971)