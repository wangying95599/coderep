package com.must.java.thread;

import java.util.List;
import java.util.Vector;
/**
 * 偏向锁
 * -XX:+UseBiasedLocking -XX:BiasedLockingStartupDelay=0 -client -Xmx521 -Xms512
 * -XX:-UseBiasedLocking -client -Xmx512m -Xms512m
 * 设置了偏向锁，会加快。
 * 不设置堆，也会变慢。
 * 
 * @author wangy
 *
 */
public class Biased {

    public static List<Integer> numberList = new Vector<Integer>();
    public static void main(String[] args) {
        long begin = System.currentTimeMillis();
        int count = 0;
        int startnum = 0;
        while(count<10000000){
            numberList.add(startnum);
            startnum+=2;
            count++;        
        }
        long end = System.currentTimeMillis();
        System.out.println(end-begin);
    }
}