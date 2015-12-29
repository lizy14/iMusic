# iMusic

Searching and recommending songs by their text-based metadata. 

Term project of the course _Data Stucture_. 

基于文本内容的音乐检索与推荐（《数据结构与算法（1）》课程实验）

![图形用户界面](http://tu.etang.info/uploads/2015/12/485221448920550539.jpg)

Written in C++.

详细文档，含可执行文件使用方法，请见 `doc/`。

* 实验一组织为 `Parser` 工程，主要实现 HTML 解析、中文分词。

* 实验二组织为 `Indexer` 工程，主要实现B-树数据结构、倒排文档索引。引用了 `Parser` 中的代码。

* `Test` 工程含有一些单元测试。

Authored winter 2015 by Li Zhaoyang.
