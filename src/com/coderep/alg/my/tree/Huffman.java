package wangy.tree;

import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

/**
 * 字符和字符对应的二进制编码配对问题。分为编码和解码，目的是压缩 字符对应的二进制数据长度。
 * 
 * 无损压缩编码，出现概率越高的用越短的编码，贪心算法。编码后的字符串长度期望最小
 * 
 * 过程： A(15) B(7) C(6) D(6) E(5) 
 * 为了让出现次数最多的字母接近根，需要自底向上构建树。每次选两个次数最低的最为叶子节点合成一枝。
 * D和E合并，父节点DE=11，  B和C合并，父节点BC=13，都比A小。 DE和BC合并父节点DEBC24和A合并。
 * 要点：字母均为叶子节点，分支结点都是 合并节点。 根为最后的合并节点。 
 * 
 * 
 * 完全二叉树：叶节点只能出现在最下层和次下层，并且最下面一层的结点都集中在该层最左边的若干位置的二叉树
 * 数据结构=完全二叉树+优先级队列(最小值优先)
 * 
 * 
 * 
 * 最后一个疑问，字符010101 如何转成1个byte
 * @author wangy
 *
 */
public class Huffman {
	/**
	 * 1map 统计每个字符的次数
	 * 2encode 将字符编成对应的二进制
	 * 3
	 * 	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str="when I was yong I'd listen to the radio";
		
        String oriStr = "Huffman codes compress data very effectively: savings of 20% to 90% are typical, "  
                + "depending on the characteristics of the data being compressed. 中华崛起";  
        
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
	 * 统计每个字符出现的次数
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
	 * 核心算法 构建树， 所有字符挂到一个 完全二叉树的叶子节点，左叶子的出现频率不能大于右叶子。优先队列保证
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
		//??? 33个节点，1次2个，17次就取光了。但是不只33个，合成节点不断放入。33=2*16+1
		//33 16次循环  剩余1 生成 16
		//17 8次循环 剩余1生成8
		//9  4次循环 剩余1生成4
		//5  2次循环剩余1生成2
		//3  1次循环剩余1生成1
		//2  1次循环剩余0生成1
		// 两两合成，最终都将生成1个节点-根。 循环 32次。
		//规律呢，如果是偶数32，就少了最后的一次。 共31次。 规律，就是永远都是size-1次。
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
	 * 编码
	 * 
	 * 1通过统计map，创建树
	 * 2找出每个字符，对应的二进制表示，存map，对应关系都是map
	 * 3将输入替换成二进制
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
	 * 找出每个字母（每个叶子节点）的所对应的二进制表示，左节点用0表示，右节点用1表示。
	 * 找出 从root到叶子的路径，路径中每个节点，左0右1.
	 * 因为需要从叶子找到根，所以node除了左右还需要parent。
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
	 * 解码的前提，知道统计map，通过map构建树
	 * 1 通过map得到树和叶子列表
	 * 从二进制取一个数字0或者1，从tree中取root，如果数字=0，就找左节点，否则找右节点，只要当前不是叶子节点，一直找到那个叶子节点。就是第一个字母
	 * 二进制串不为空，就继续从tree开始，
	 * 一个循环双迭代：不是叶子，取二进制和子节点。
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

