package com.must.java.jvm;
/**
 * JVM =����飬1�̹߳����java�Ѻͷ����� 2�߳�˽�е�jvmջ ���ط���ջ ���������
 * https://www.cnblogs.com/lifescolor/p/5481588.html
 * 
 * JVM���Ժ��Ż�
 * https://blog.csdn.net/HLhakey/article/details/55225845
 * https://blog.csdn.net/zhoutao198712/article/details/7783070
 * https://blog.csdn.net/qq_34707744/article/details/78690540
 * 
 * jvm cpu�� ����
 * https://blog.csdn.net/bolg_hero/article/details/53126744
 * ���Լ�������
 * 0 8��CPU  ��� 800%
 * 1��top�ҳ�cpu�ߵ�java���̺�9592
2��top -Hp  9592�鿴cpuռ��time��ߵ��̱߳��28178
3��ִ�� printf "%x\n" 28178 ��ȡ�߳�ʮ�����Ƶ�ַ6e12 ��ʮ������һ��ҪСд��
4��ִ�� jstack 9592|grep  -10 6e12���߳�ʮ�����ƺţ�
 *
 */
public class A_jvm {

}
