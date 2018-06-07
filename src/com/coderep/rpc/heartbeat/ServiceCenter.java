package com.coderep.rpc.heartbeat;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.Method;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;

public class ServiceCenter {
	 
    private ExecutorService executor = Executors.newFixedThreadPool(20);
 
    private final ConcurrentHashMap<String, Class> serviceRegistry = new ConcurrentHashMap<String, Class>();
 
    private AtomicBoolean isRunning = new AtomicBoolean(true);
 
    // �����������˿�
    private int port = 8089;
 
    // ����������
    HeartbeatLinstener linstener;
 
    // ����ģʽ
    private static class SingleHolder {
        private static final ServiceCenter INSTANCE = new ServiceCenter();
    }
 
    private ServiceCenter() {
    }
 
    public static ServiceCenter getInstance() {
        return SingleHolder.INSTANCE;
    }
 
    public void register(Class serviceInterface, Class impl) {
        System.out.println("regeist service " + serviceInterface.getName());
        serviceRegistry.put(serviceInterface.getName(), impl);
    }
 
    public void start() throws IOException {
        ServerSocket server = new ServerSocket();
        server.bind(new InetSocketAddress(port));
        System.out.println("start server");
        linstener = HeartbeatLinstener.getInstance();
        System.out.println("start listen heart beat");
        try {
            while (true) {
                // 1.�����ͻ��˵�TCP���ӣ��ӵ�TCP���Ӻ����װ��task�����̳߳�ִ��
                executor.execute(new ServiceTask(server.accept()));
            }
        } finally {
            server.close();
        }
    }
 
    public void stop() {
        isRunning.set(false);
        executor.shutdown();
    }
 
 
    public boolean isRunning() {
        return isRunning.get();
    }
 
    public int getPort() {
        return port;
    }
 
    public void settPort(int port) {
        this.port = port;
    }
 
    public ConcurrentHashMap<String, Class> getServiceRegistry() {
        return serviceRegistry;
    }
 
    private class ServiceTask implements Runnable {
        Socket clent = null;
 
        public ServiceTask(Socket client) {
            this.clent = client;
        }
 
        public void run() {
            ObjectInputStream input = null;
            ObjectOutputStream output = null;
            try {
                // 2.���ͻ��˷��͵����������л��ɶ��󣬷�����÷���ʵ���ߣ���ȡִ�н��
                input = new ObjectInputStream(clent.getInputStream());
                String serviceName = input.readUTF();
                String methodName = input.readUTF();
                Class<?>[] parameterTypes = (Class<?>[]) input.readObject();
                Object[] arguments = (Object[]) input.readObject();
                Class serviceClass = serviceRegistry.get(serviceName);
                if (serviceClass == null) {
                    throw new ClassNotFoundException(serviceName + " not found");
                }
                Method method = serviceClass.getMethod(methodName, parameterTypes);
                Object result = method.invoke(serviceClass.newInstance(), arguments);
 
                // 3.��ִ�н�������л���ͨ��socket���͸��ͻ���
                output = new ObjectOutputStream(clent.getOutputStream());
                output.writeObject(result);
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if (output != null) {
                    try {
                        output.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (input != null) {
                    try {
                        input.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (clent != null) {
                    try {
                        clent.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
 
        }
    }
}