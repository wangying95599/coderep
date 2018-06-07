package com.coderep.rpc.heartbeat;

public interface HeartbeatHandler {
	public Cmder sendHeartBeat(HeartbeatEntity info);
}
