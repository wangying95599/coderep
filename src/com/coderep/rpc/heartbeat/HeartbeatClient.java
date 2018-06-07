package com.coderep.rpc.heartbeat;

import java.net.InetSocketAddress;
import java.util.UUID;

public class HeartbeatClient implements Runnable {
	 
    private String serverIP = "127.0.0.1";
    private int serverPort = 8089;
    private String nodeID = UUID.randomUUID().toString();
    private boolean isRunning = true;
    //  ���������ʱ��
    private long lastHeartbeat;
    // �������ʱ��
    private long heartBeatInterval = 10 * 1000;
 
    public void run() {
        try {
            while (isRunning) {
                HeartbeatHandler handler = RPClient.getRemoteProxyObj(HeartbeatHandler.class, new InetSocketAddress(serverIP, serverPort));
                long startTime = System.currentTimeMillis();
                // �Ƿ�ﵽ��������������ʱ��
                if (startTime - lastHeartbeat > heartBeatInterval) {
                    System.out.println("send a heart beat");
                    lastHeartbeat = startTime;
 
                    HeartbeatEntity entity = new HeartbeatEntity();
                    entity.setTime(startTime);
                    entity.setNodeID(nodeID);
 
                    // �������������������������Ҫִ�е�����
                    Cmder cmds = handler.sendHeartBeat(entity);
 
                    if (!processCommand(cmds))
                        continue;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
 
    private boolean processCommand(Cmder cmds) {
        // ...
        return true;
    }
 
}