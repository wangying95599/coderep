package wangy.tree;

import java.util.Stack;

/**
 * 后序遍历
 * 左子树 右子树  根  按照数字从小到大的顺序。
 * @author wangy
 *	
 * 中序的非递归，难了很多。
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
	 * 左子树，右子树, 根，

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
