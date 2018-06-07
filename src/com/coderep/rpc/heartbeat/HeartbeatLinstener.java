package com.coderep.rpc.heartbeat;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.Method;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;
 
/**
 * ��������������Ϣ
 *
 * @author cang
 * @create_time 2016-09-28 11:40
 */
public class HeartbeatLinstener {
 
    private ExecutorService executor = Executors.newFixedThreadPool(20);
 
    private final ConcurrentHashMap<String, Object> nodes = new ConcurrentHashMap<String, Object>();
    private final ConcurrentHashMap<String, Long> nodeStatus = new ConcurrentHashMap<String, Long>();
 
    private long timeout = 10 * 1000;
 
    // �����������˿�
    private int port = 8089;
 
    // ����ģʽ
    private static class SingleHolder {
        private static final HeartbeatLinstener INSTANCE = new HeartbeatLinstener();
    }
 
    private HeartbeatLinstener() {
    }
 
    public static HeartbeatLinstener getInstance() {
        return SingleHolder.INSTANCE;
    }
 
    public ConcurrentHashMap<String, Object> getNodes() {
        return nodes;
    }
 
    public void registerNode(String nodeId, Object nodeInfo) {
        nodes.put(nodeId, nodeInfo);
        nodeStatus.put(nodeId, System.currentTimeMillis());
    }
 
    public void removeNode(String nodeID) {
        if (nodes.containsKey(nodeID)) {
            nodes.remove(nodeID);
        }
    }
 
    // ���ڵ��Ƿ���Ч
    public boolean checkNodeValid(String key) {
        if (!nodes.containsKey(key) || !nodeStatus.containsKey(key)) return false;
        if ((System.currentTimeMillis() - nodeStatus.get(key)) > timeout) return false;
        return true;
    }
 
    // ɾ������ʧЧ�ڵ�
    public void removeInValidNode() {
        Iterator<Map.Entry<String, Long>> it = nodeStatus.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, Long> e = it.next();
            if ((System.currentTimeMillis() - nodeStatus.get(e.getKey())) > timeout) {
                nodes.remove(e.getKey());
            }
        }
    }
 
}