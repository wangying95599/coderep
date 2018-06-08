package wangy.tree;

public class FullBinaryTree {
	private Node root;

	public Node getRoot() {
		return root;
	}

	public void setRoot(Node root) {
		this.root = root;
	}
	
}
class Node implements Comparable<Node>{
	private Node left;
	private Node right;
	private Node parent;
	private int frequence=0;
	private String chars="";
	
	public boolean isLeaf() {
		//??? left==null&& right=null
		return chars.length() ==1;
	}
	public boolean isRoot() {
		return parent == null;
	}
	
	public boolean isLeftChild() {
		return parent.left==this;
	}
	
	@Override
	public int compareTo(Node o) {
		return this.frequence - o.frequence;
	}

	public Node getLeft() {
		return left;
	}

	public void setLeft(Node left) {
		this.left = left;
	}



	public Node getRight() {
		return right;
	}



	public void setRight(Node right) {
		this.right = right;
	}



	public Node getParent() {
		return parent;
	}



	public void setParent(Node parent) {
		this.parent = parent;
	}



	public int getFrequence() {
		return frequence;
	}



	public void setFrequence(int frequence) {
		this.frequence = frequence;
	}



	public String getChars() {
		return chars;
	}



	public void setChars(String chars) {
		this.chars = chars;
	}
	
	
}