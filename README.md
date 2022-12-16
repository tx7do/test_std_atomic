# 测试std::atomic

| 类型  | 结果       | 耗时         |
|-----|----------|------------|
| 不加锁 | 无        | 无          |
| 加锁  | 10000000 | 1157.28 ms |
| 原子  | 10000000 | 223.048 ms |

不加锁根本没有办法完成，Crash了。

使用原子操作明显比加锁操作要效率高。

## 参考资料

- [std::atomic 用法與範例](https://shengyu7697.github.io/std-atomic/)
- [C++11中的原子操作（atomic operation）](https://blog.csdn.net/yockie/article/details/8838686)
