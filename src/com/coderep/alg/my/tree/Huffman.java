package wangy.tree;

import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

/**
 * �ַ����ַ���Ӧ�Ķ����Ʊ���������⡣��Ϊ����ͽ��룬Ŀ����ѹ�� �ַ���Ӧ�Ķ��������ݳ��ȡ�
 * 
 * ����ѹ�����룬���ָ���Խ�ߵ���Խ�̵ı��룬̰���㷨���������ַ�������������С
 * 
 * ���̣� A(15) B(7) C(6) D(6) E(5) 
 * Ϊ���ó��ִ���������ĸ�ӽ�������Ҫ�Ե����Ϲ�������ÿ��ѡ����������͵���ΪҶ�ӽڵ�ϳ�һ֦��
 * D��E�ϲ������ڵ�DE=11��  B��C�ϲ������ڵ�BC=13������AС�� DE��BC�ϲ����ڵ�DEBC24��A�ϲ���
 * Ҫ�㣺��ĸ��ΪҶ�ӽڵ㣬��֧��㶼�� �ϲ��ڵ㡣 ��Ϊ���ĺϲ��ڵ㡣 
 * 
 * 
 * ��ȫ��������Ҷ�ڵ�ֻ�ܳ��������²�ʹ��²㣬����������һ��Ľ�㶼�����ڸò�����ߵ�����λ�õĶ�����
 * ���ݽṹ=��ȫ������+���ȼ�����(��Сֵ����)
 * 
 * 
 * 
 * ���һ�����ʣ��ַ�010101 ���ת��1��byte
 * @author wangy
 *
 */
public class Huffman {
	/**
	 * 1map ͳ��ÿ���ַ��Ĵ���
	 * 2encode ���ַ���ɶ�Ӧ�Ķ�����
	 * 3
	 * 	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str="when I was yong I'd listen to the radio";
		
        String oriStr = "Huffman codes compress data very effectively: savings of 20% to 90% are typical, "  
                + "depending on the characteristics of the data being compressed. �л�����";  
        
        Map<Character, Integer> statistics = statistics(oriStr.toCharArray());  
        String encodedBinariStr = encode(oriStr, statistics);  
        String decodedStr = decode(encodedBinariStr, statistics);  
  
        System.out.println("Original sstring: " + oriStr);  
        System.out.println("Huffman encoed binary string: " + encodedBinariStr);  
        System.out.println("decoded string from binariy string: " + decodedStr);  
  
        System.out.println("binary string of UTF-8: "  
                + getStringOfByte(oriStr, Charset.forName("UTF-8")));  
        System.out.println("binary string of UTF-16: "  
                + getStringOfByte(oriStr, Charset.forName("UTF-16")));  
        System.out.println("binary string of US-ASCII: "  
                + getStringOfByte(oriStr, Charset.forName("US-ASCII")));  
        System.out.println("binary string of GB2312: "  
                + getStringOfByte(oriStr, Charset.forName("GB2312"))); 
	}
	
	/**
	 * ͳ��ÿ���ַ����ֵĴ���
	 * @param charArray
	 * @return
	 */
	public static Map<Character, Integer> statistics(char[] charArray){
		Map<Character,Integer> map = new HashMap<Character,Integer>();
		for(char c:charArray) {
			Character character = new Character(c);
			if(map.containsKey(character)) {
				map.put(character, map.get(character)+1);
			}else {
				map.put(character, 1);
			}
		}
		
		return map;
	}
	/**
	 * �����㷨 �������� �����ַ��ҵ�һ�� ��ȫ��������Ҷ�ӽڵ㣬��Ҷ�ӵĳ���Ƶ�ʲ��ܴ�����Ҷ�ӡ����ȶ��б�֤
	 * 
	 * 
	 */
	public static FullBinaryTree buildTree(Map<Character,Integer> statistics, List<Node> leafs) {
		Character[] keys = statistics.keySet().toArray(new Character[0]);
		
		PriorityQueue<Node> priorityQueue = new PriorityQueue<Node>();
		for(Character key:keys) {
			Node node = new Node();
			node.setChars(key.toString());
			node.setFrequence(statistics.get(key));
			
			priorityQueue.add(node);
			leafs.add(node);
		}
		//??? 33���ڵ㣬1��2����17�ξ�ȡ���ˡ����ǲ�ֻ33�����ϳɽڵ㲻�Ϸ��롣33=2*16+1
		//33 16��ѭ��  ʣ��1 ���� 16
		//17 8��ѭ�� ʣ��1����8
		//9  4��ѭ�� ʣ��1����4
		//5  2��ѭ��ʣ��1����2
		//3  1��ѭ��ʣ��1����1
		//2  1��ѭ��ʣ��0����1
		// �����ϳɣ����ն�������1���ڵ�-���� ѭ�� 32�Ρ�
		//�����أ������ż��32������������һ�Ρ� ��31�Ρ� ���ɣ�������Զ����size-1�Ρ�
		int size = priorityQueue.size();
		for(int i=1;i<=size -1; i++) {
			Node node1 = priorityQueue.poll();
			Node node2 = priorityQueue.poll();
			
			Node sumNode = new Node();
			sumNode.setChars(node1.getChars()+node2.getChars());
			sumNode.setFrequence(node1.getFrequence()+node2.getFrequence());
			sumNode.setLeft(node1);
			sumNode.setRight(node2);
			
			node1.setParent(sumNode);
			node2.setParent(sumNode);
			
			priorityQueue.add(sumNode);
		}
		
		FullBinaryTree tree = new FullBinaryTree();  
	    tree.setRoot(priorityQueue.poll()); ;  
	    return tree;  
	}
	/**
	 * ����
	 * 
	 * 1ͨ��ͳ��map��������
	 * 2�ҳ�ÿ���ַ�����Ӧ�Ķ����Ʊ�ʾ����map����Ӧ��ϵ����map
	 * 3�������滻�ɶ�����
	 */
	public static String encode(String originalStr,  
            Map<Character, Integer> statistics) {  
        if (originalStr == null || originalStr.equals("")) {  
            return "";  
        }  
  
        char[] charArray = originalStr.toCharArray();  
        List<Node> leafNodes = new ArrayList<Node>();  
        buildTree(statistics, leafNodes);  
        Map<Character, String> encodInfo = buildEncodingInfo(leafNodes);  
  
        StringBuffer buffer = new StringBuffer();  
        for (char c : charArray) {  
            Character character = new Character(c);  
            buffer.append(encodInfo.get(character));  
        }  
  
        return buffer.toString();  
    }  
	/**
	 * �ҳ�ÿ����ĸ��ÿ��Ҷ�ӽڵ㣩������Ӧ�Ķ����Ʊ�ʾ����ڵ���0��ʾ���ҽڵ���1��ʾ��
	 * �ҳ� ��root��Ҷ�ӵ�·����·����ÿ���ڵ㣬��0��1.
	 * ��Ϊ��Ҫ��Ҷ���ҵ���������node�������һ���Ҫparent��
	 * 
	 */
	private static Map<Character, String> buildEncodingInfo(List<Node> leafNodes) {  
        Map<Character, String> codewords = new HashMap<Character, String>();  
        for (Node leafNode : leafNodes) {  
            Character character = new Character(leafNode.getChars().charAt(0));  
            String codeword = "";  
            Node currentNode = leafNode;  
  
            do {  
                if (currentNode.isLeftChild()) {  
                    codeword = "0" + codeword;  
                } else {  
                    codeword = "1" + codeword;  
                }  
  
                currentNode = currentNode.getParent();  
            } while (currentNode.getParent() != null);  
  
            codewords.put(character, codeword);  
        }  
  
        return codewords;  
    } 
	/**
	 * �����ǰ�ᣬ֪��ͳ��map��ͨ��map������
	 * 1 ͨ��map�õ�����Ҷ���б�
	 * �Ӷ�����ȡһ������0����1����tree��ȡroot���������=0��������ڵ㣬�������ҽڵ㣬ֻҪ��ǰ����Ҷ�ӽڵ㣬һֱ�ҵ��Ǹ�Ҷ�ӽڵ㡣���ǵ�һ����ĸ
	 * �����ƴ���Ϊ�գ��ͼ�����tree��ʼ��
	 * һ��ѭ��˫����������Ҷ�ӣ�ȡ�����ƺ��ӽڵ㡣
	 * 
	 */
	public static String decode(String binaryStr,  
            Map<Character, Integer> statistics) {  
        if (binaryStr == null || binaryStr.equals("")) {  
            return "";  
        }  
  
        char[] binaryCharArray = binaryStr.toCharArray();  
        LinkedList<Character> binaryList = new LinkedList<Character>();  
        int size = binaryCharArray.length;  
        for (int i = 0; i < size; i++) {  
            binaryList.addLast(new Character(binaryCharArray[i]));  
        }  
  
        List<Node> leafNodes = new ArrayList<Node>();  
        FullBinaryTree tree = buildTree(statistics, leafNodes);  
  
        StringBuffer buffer = new StringBuffer();  
  
        while (binaryList.size() > 0) {  
            Node node = tree.getRoot();  
  
            do {  
                Character c = binaryList.removeFirst();  
                if (c.charValue() == '0') {  
                    node = node.getLeft();  
                } else {  
                    node = node.getRight();  
                }  
            } while (!node.isLeaf());  
  
            buffer.append(node.getChars());  
        }  
  
        return buffer.toString();  
    } 
	
    public static String getStringOfByte(String str, Charset charset) {  
        if (str == null || str.equals("")) {  
            return "";  
        }  
  
        byte[] byteArray = str.getBytes(charset);  
        int size = byteArray.length;  
        StringBuffer buffer = new StringBuffer();  
        for (int i = 0; i < size; i++) {  
            byte temp = byteArray[i];  
            buffer.append(getStringOfByte(temp));  
        }  
  
        return buffer.toString();  
    }  
  
    public static String getStringOfByte(byte b) {  
        StringBuffer buffer = new StringBuffer();  
        for (int i = 7; i >= 0; i--) {  
            byte temp = (byte) ((b >> i) & 0x1);  
            buffer.append(String.valueOf(temp));  
        }  
  
        return buffer.toString();  
    }
}

