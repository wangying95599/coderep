package wangy.tree;

import java.util.Stack;

/**
 * �������
 * ������ ������  ��  �������ִ�С�����˳��
 * @author wangy
 *	
 * ����ķǵݹ飬���˺ܶࡣ
 */
public class Postorder {

	public static void main(String[] args) {

	}
	
	
	public static void postorder(TreeNode root) {
		postorder1(root);
	}
	
	public static void postorder1(TreeNode root) {
		if(root == null) {
			return ;
		}
		postorder1(root.left);
		postorder1(root.right);
		System.out.print(root.val+",");
		
	}
	/**
	 * ��������������, ����

	 * 
	 * @param root
	 */
	public static void postorder2(TreeNode root) {
		if(root == null) {
			return ;
		}
		Stack<TreeNode> stack = new Stack<TreeNode>();
		TreeNode head = root;
		
		
		 
	}
	
}
