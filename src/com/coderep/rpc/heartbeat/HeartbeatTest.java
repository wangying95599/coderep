package com.coderep.rpc.heartbeat;

/**
 * ��Դ��https://www.cnblogs.com/codingexperience/p/5939059.html
 * @author wangy
 *
 */
/**
	ʱ������
	      �յ�һ�������󣬼�¼��ǰʱ��(��ΪrecvedTime)��
	      �ж϶�ʱ��ʱ�䵽�������û�յ�������ʱ��(T)=��ǰʱ�� - recvedTime(�����¼��ʱ��)�����T����ĳ���趨ֵ���Ϳ�����ΪClient��ʱ�ˡ�
 */
public class HeartbeatTest {
	public static void main(String[] args) {
		new Thread(new Runnable() {
			public void run() {
				try {
					ServiceCenter serviceServer = ServiceCenter.getInstance();
					serviceServer.register(HeartbeatHandler.class, HeartbeatHandlerImpl.class);
					serviceServer.start();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}).start();
		
		Thread client1 = new Thread(new HeartbeatClient());
		client1.start();
		Thread client2 = new Thread(new HeartbeatClient());
		client2.start();
	}
}
