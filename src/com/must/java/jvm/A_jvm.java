package com.must.java.jvm;
/**
 * JVM =分五块，1线程共享的java堆和方法区 2线程私有的jvm栈 本地方法栈 程序计数器
 * https://www.cnblogs.com/lifescolor/p/5481588.html
 * 
 * JVM调试和优化
 * https://blog.csdn.net/HLhakey/article/details/55225845
 * https://blog.csdn.net/zhoutao198712/article/details/7783070
 * https://blog.csdn.net/qq_34707744/article/details/78690540
 * 
 * jvm cpu高 分析
 * https://blog.csdn.net/bolg_hero/article/details/53126744
 * 用自己的语言
 * 0 8核CPU  最高 800%
 * 1、top找出cpu高的java进程号9592
2、top -Hp  9592查看cpu占用time最高的线程编号28178
3、执行 printf "%x\n" 28178 获取线程十六进制地址6e12 （十六进制一定要小写）
4、执行 jstack 9592|grep  -10 6e12（线程十六进制号）
 *
 */
public class A_jvm {

}
