package com.coderep.rpc.test;

public class HelloServiceImpl implements HelloService {
	 
    public String sayHi(String name) {
        return "Hi, " + name;
    }
 
}