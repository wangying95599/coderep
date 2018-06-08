package wangy.tree;

import java.util.Stack;

/**
 * 前序遍历
 * 根左子树右子树
 * @author wangy
 *
 */
public class Preorder {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	
	public static void preorder(TreeNode root) {
		preorder1(root);
	}
	
	public static void preorder1(TreeNode root) {
		if(root == null) {
			return ;
		}
		System.out.print(root.val+",");
		preorder1(root.left);
		preorder1(root.right);
	}
	
	public static void preorder2(TreeNode root) {
		if(root == null) {
			return ;
		}
		Stack<TreeNode> stack = new Stack<TreeNode>();
		stack.add(root);
		
		while(!stack.isEmpty()) {
			TreeNode node = stack.pop();
			
			System.out.println(node.val+",");
			if(node.right != null) {
				stack.add(node.right);
			}
			if(node.left !=null) {
				stack.add(node.left);
			}
		}
	}
}
