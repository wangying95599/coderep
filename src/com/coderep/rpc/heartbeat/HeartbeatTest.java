package com.coderep.rpc.heartbeat;

/**
 * 来源：https://www.cnblogs.com/codingexperience/p/5939059.html
 * @author wangy
 *
 */
/**
	时间差策略
	      收到一个心跳后，记录当前时间(记为recvedTime)。
	      判断定时器时间到达，计算多久没收到心跳的时间(T)=当前时间 - recvedTime(上面记录的时间)。如果T大于某个设定值，就可以认为Client超时了。
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
