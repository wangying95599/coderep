package com.coderep.rpc.test;

import java.io.IOException;
import java.net.InetSocketAddress;

import com.coderep.rpc.RPCClient;
/**
 * http://www.cnblogs.com/codingexperience/p/5930752.html
 * @author wangy
 *
 */
/**
RPC�ܹ���Ϊ�����֣�

1�������ṩ�ߣ������ڷ������ˣ��ṩ����ӿڶ��������ʵ���ࡣ

2���������ģ������ڷ������ˣ����𽫱��ط��񷢲���Զ�̷��񣬹���Զ�̷����ṩ������������ʹ�á�

3�����������ߣ������ڿͻ��ˣ�ͨ��Զ�̴���������Զ�̷���
 
 */
/**
 ���������RPC�ĺ���ԭ��RPC�ܹ��ñ���Ӧ�ü򵥡���Ч�ص��÷������еĹ��̣����񣩡�����ҪӦ���ڷֲ�ʽϵͳ����Hadoop�е�IPC�����������ʵ��һ��RPC����أ�

�����漸������˼���������ο���

1.ͨ��ģ�ͣ�����ͨ�ŵ�ΪA������B������A��B֮����ͨ��ģ�ͣ���Java��һ�����BIO��NIO����

2.���̣����񣩶�λ��ʹ�ø�����ͨ�ŷ�ʽ����ȷ��IP��˿ڼ���������ȷ������Ĺ��̻򷽷���

3.Զ�̴�����󣺱��ص��õķ���(����)��ʵ��Զ�̷����ı��ش�����˿�����Ҫһ��Զ�̴�����󣬶���Java���ԣ�Զ�̴���������ʹ��Java�Ķ�̬����ʵ�֣���װ�˵���Զ�̷������ã�

4.���л������������ơ��������ơ������ȶ�����Ϣ�������紫����Ҫת���ɶ����ƴ��䣬���������Ҫ��ͬ�����л�������������:protobuf��Arvo��
 */
public class RPCTest {
	 
    public static void main(String[] args) throws IOException {
        new Thread(new Runnable() {
            public void run() {
                try {
                    Server serviceServer = new ServiceCenter(8088);
                    serviceServer.register(HelloService.class, HelloServiceImpl.class);
                    serviceServer.start();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
        HelloService service = RPCClient.getRemoteProxyObj(HelloService.class, new InetSocketAddress("localhost", 8088));
        System.out.println(service.sayHi("test"));
    }
}