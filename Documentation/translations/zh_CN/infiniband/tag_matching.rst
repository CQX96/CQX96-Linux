.. include:: ../disclaimer-zh_CN.rst

:Original: Documentation/infiniband/tag_matching.rst

:翻译:

 司延腾 Yanteng Si <siyanteng@loongson.cn>

:校译:

 王普宇 Puyu Wang <realpuyuwang@gmail.com>
 时奎亮 Alex Shi <alexs@cqx96.org>

.. _cn_infiniband_tag_matching:

============
标签匹配逻辑
============

MPI标准定义了一套规则，称为标签匹配，用于将源发送操作与目的接收匹配。以下参数必
须与以下源和目的参数相匹配:

*	沟通者
*	用户标签--通配符(wild card)可由接收方指定
*	来源等级--通配符可由接收方指定
*	目的地等级 – wild

排序规则要求，当一对以上的发送和接收消息信封可能匹配时，包括最早发布-发送和最早
发布-接收的一对是必须用来满足匹配操作的一对。然而，这并不意味着标签是按照它们被
创建的顺序消耗的，例如，如果早期的标签不能用来满足匹配规则，那么后来生成的标签
可能被消耗。

当消息从发送方发送到接收方时，通信库可能试图在相应的匹配接收被发布之后或之前处
理该操作。如果匹配的接收被发布，这就是一个预期的消息，否则就被称为一个意外的消
息。实现时经常为这两种不同的匹配实例使用不同的匹配方案。

为了减少MPI库的内存占用，MPI实现通常使用两种不同的协议来实现这一目的:

1.	Eager协议--当发送方处理完发送时，完整的信息就会被发送。在send_cq中会收到
一个完成发送的通知，通知缓冲区可以被重新使用。

2.	Rendezvous协议--发送方在第一次通知接收方时发送标签匹配头，也许还有一部分
数据。当相应的缓冲区被发布时，响应者将使用头中的信息，直接向匹配的缓冲区发起
RDMA读取操作。为了使缓冲区得到重用，需要收到一个fin消息。

标签匹配的实现
==============

使用的匹配对象有两种类型，即发布的接收列表和意外消息列表。应用程序通过调用发布
的接收列表中的MPI接收例程发布接收缓冲区，并使用MPI发送例程发布发送消息。发布的
接收列表的头部可以由硬件来维护，而软件则要对这个列表进行跟踪。

当发送开始并到达接收端时，如果没有为这个到达的消息预先发布接收，它将被传递给软
件并被放在意外（unexpect）消息列表中。否则，将对该匹配进行处理，包括交会处理，
如果合适的话，将数据传送到指定的接收缓冲区。这允许接收方MPI标签匹配与计算重叠。

当一个接收信息被发布时，通信库将首先检查软件的意外信息列表，以寻找一个匹配的接
收信息。如果找到一个匹配的，数据就会被送到用户缓冲区，使用一个软件控制的协议。
UCX的实现根据数据大小，使用急切或交会协议。如果没有找到匹配，整个预置的接收列
表由硬件维护，并且有空间在这个列表中增加一个预置的接收，这个接收被传递给硬件。
软件要对这个列表进行跟踪，以帮助处理MPI取消操作。此外，由于硬件和软件在标签匹
配操作方面预计不会紧密同步，这个影子列表被用来检测预先发布的接收被传递到硬件的
情况，因为匹配的意外消息正在从硬件传递到软件。
