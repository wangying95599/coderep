package bfs;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

/*��ȱ����Ǳ�����ĳ�����㣬Ȼ���L�������ӵ�a,b�������L��a�����ӱ�
 �ǳ���Ȼ�ģ��������ݽṹ����HashMap���Զ���Ϊkey������ÿһ����������ӱ�
 */
public class BFS {
	static int count=0;
	/*
	 * HashMap<Character,LinkedList<Character>> graph ���HashMap�����ڴ��ͼ��ÿһ��node���ڽӱ�
	 * ��ʾ��ӳ����ά���ļ�������ΪCharacter����ӳ��ֵ������ΪLinkedList<Character> graph
	 * ��ʾ��ӳ���ϵ�����graph��ӳ����
	 * 
	 * LinkedList<Character> ��ʾ�ڴ�Collection�б���Ԫ������ΪCharacter
	 * 
	 * HashMap<Character,Integer> dist ���HashMap �����ڴ��ÿһ��node����붥��s�ľ����ӳ���ϵ
	 * ��ʾ��ӳ����ά���ļ�������ΪCharacter ��ӳ����ά����ֵ������ΪInteger��dist��ʾ��ӳ���ϵ��ŵ�dist��ӳ����
	 */
	private void bfs(HashMap<Character, LinkedList<Character>> graph,
			HashMap<Character, Integer> dist, char start) {
		// Queue<Character> ��ʾ�ڴ�Collection���������Ԫ�ص�����ΪCharacter
		Queue<Character> q = new LinkedList<Character>();
		q.add(start);// ��ָ��Ԫ��s������У��ɹ�ʱ����true������û�п��ÿռ䡣�򷵻�illegalStateException
		//put(start,0) startΪָ��ֵ��Ҫ�����ļ���0Ϊָ��ֵ��Ҫ������ֵ�� ����start��0��ӳ���ϵ�Ѵ��ڣ��򷵻ز��滻��ֵ0
		//���� start��0��ӳ���ϵ�����ڣ��򷵻�null
		dist.put(start, 0);
		int i = 0;
		while (!q.isEmpty())//
		{
			char top = q.poll();// ��ȡ���Ƴ����е�ͷ�����ض��е�ͷ���������Ϊ�ա�����null
			i++;
			// dist.get(top) ����ָ����top��ӳ���ֵ
			System.out.println("The " + i + "th element:" + top+ " Distance from s is:" + dist.get(top));
			int d = dist.get(top) + 1;// �ó����ܱ߻�δ���L�ʵĽڵ�ľ���
			/*
			 * graph.get(top)�����ӳ�����һ������ (key==null ? k==null : key.equals(k))
			 * �Ĵ� k ���� v ֵ��ӳ���ϵ����˷������� v�����򷵻� null��������������һ������ӳ���ϵ��
��
			 * for��Ԫ�ر�����Ԫ�ؼ��ϣ�������Ԫ�ؼ�����ȫ��Ԫ�ض��ѱ��������������ѭ���� ��������forѭ����ĳ����
			 */
			for (Character c : graph.get(top)) {
				// containskey(key) �����ӳ���������ָ����key��ӳ���ϵ���򷵻�true
				if (!dist.containsKey(c))// ����dist�л�û�и�Ԫ��˵����û�б��L��
				{
					//����ָ����c��ָ��ֵd�����������ϵ�Ѵ��ڡ����滻��ֵd�����ؾ�ֵd�� ������ӳ���ϵ���򷵻�null
					dist.put(c, d);
					q.add(c); // ��ָ��Ԫ��c������У��ɹ�ʱ����true������û�п��ÿռ䣬�򷵻�illegalStateException
				}
			}
		}
	}	
	private static void dfs(HashMap<Character , LinkedList<Character>> graph,HashMap<Character, Boolean> visited)
	{
	    visit(graph, visited, 's');
	}
	private static void visit(HashMap<Character , LinkedList<Character>> graph,HashMap<Character, Boolean> visited,char start)
	{
		
		if (!visited.containsKey(start)) {
			count++;
			System.out.println("The time into element " + start + ":" + count);// ��¼����ýڵ��ʱ��
			visited.put(start, true);
			for (Character c : graph.get(start)) {
				if (!visited.containsKey(c)) {
					visit(graph, visited, c);// �ݹ��L�����ڽ��ڵ�
				}
			}
			count++;
			System.out.println("The time out element " + start + ":" + count);// ��¼�뿪�ýڵ��ʱ��
		}
	}
	/**
	 * ����������һ������ͼ��
	 * @param args
	 */
	public static void main(String args[]) {
		BFS bb = new BFS();
		// s������ڽӱ�
		LinkedList<Character> list_s = new LinkedList<Character>();
		list_s.add('w');
		list_s.add('r');
		LinkedList<Character> list_w = new LinkedList<Character>();
		list_w.add('s');
		list_w.add('x');
		list_w.add('i');
		LinkedList<Character> list_r = new LinkedList<Character>();
		list_r.add('s');
		list_r.add('v');
		LinkedList<Character> list_x = new LinkedList<Character>();
		list_x.add('w');
		list_x.add('y');
		list_x.add('u');
		LinkedList<Character> list_v = new LinkedList<Character>();
		list_v.add('r');
		LinkedList<Character> list_i = new LinkedList<Character>();
		list_i.add('w');
		LinkedList<Character> list_u = new LinkedList<Character>();
		list_u.add('x');
		LinkedList<Character> list_y = new LinkedList<Character>();
		list_y.add('x');
		HashMap<Character, LinkedList<Character>> graph = new HashMap<Character, LinkedList<Character>>();
		graph.put('s', list_s);
		graph.put('w', list_w);
		graph.put('r', list_r);
		graph.put('x', list_x);
		graph.put('v', list_v);
		graph.put('i', list_i);
		graph.put('y', list_y);
		graph.put('u', list_u);
		System.out.println("BFS starts:");
		HashMap<Character, Integer> dist = new HashMap<Character, Integer>();
		char start = 's';
		/**
		 * ͨ��������ȱ������ӽ���Զ�ҳ����е㵽���ľ��롣
		 * ���У������ӣ� ��һ���㣬�ͽ���������е��ڽӵ㣨δ���ʵģ���ӡ�
		 * ������ֵ��һֱѭ����
		 * һȦһȦ����ɢ
		 */
		bb.bfs(graph, dist, start);
		printMap(dist);
		System.out.println("DFS starts:");
		HashMap<Character, Boolean> visited=new HashMap<Character, Boolean>();
		/**
		 * ͨ��������ȱ������ݹ�+ѭ����������ݣ�Ϊʲô�������л��ݵ���ʲô����
		 * һ��·�ߵ���
		 * ���s�������ڽӵ�w��r��
		 * s ������w���͵ݹ�Ĳ��ϵ���w���ڽӵ㣬һֱ���յ㡣
		 *   �ݹ�ı���s��w����ģ������㣨������r��
		 *   
		 */
		bb.dfs(graph, visited);
		printMap(visited);
	}
	
	public static void printMap(HashMap map) {
		Set set = map.keySet();
		Iterator it = set.iterator();
		while(it.hasNext()) {
			Character key = (Character) it.next();
			System.out.println(key+"--------"+map.get(key));
		}
	}
}