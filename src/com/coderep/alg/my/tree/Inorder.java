package wangy.tree;

import java.util.Stack;

/**
 * 中序遍历
 * 左子树 根 右子树 按照数字从小到大的顺序。
 * @author wangy
 *	
 * 中序的非递归，难了很多。
 */
public class Inorder {

	public static void main(String[] args) {

	}
	
	
	public static void inorder(TreeNode root) {
		inorder1(root);
	}
	
	public static void inorder1(TreeNode root) {
		if(root == null) {
			return ;
		}
		inorder1(root.left);
		System.out.print(root.val+",");
		inorder1(root.right);
	}
	/**
	 * 左子树，根，右子树
	 * 1找到最左的那个节点L1，他排第一位。
	 * 2需要知道L1的根R1，再通过根R1，找到R1. 这一枝完成。再找到R1的根。也就说所有的根点，都需要记录下来。
	 * 树 的特点 就是 以根为中心， 由根生出分支来。所有找到 最左节点时，需要记住过程中的所有根。
	 * 
	 * 3 找到右子树的时候， 需要重新走1的逻辑
	 * 
	 * @param root
	 */
	public static void inorder2(TreeNode root) {
		if(root == null) {
			return ;
		}
		Stack<TreeNode> stack = new Stack<TreeNode>();
		TreeNode head = root;
		
		//右子树为空 且 栈为空，就不循环了。这两条件都是第二个循环用的。
		//里面的两个while 都是一个条件还满足时始终走自己，所有 可以改成 while1->if while2->else
		while(head!=null && !stack.isEmpty()) {
		
			/**
			 * 1找到最左节点，同时记录所有根
			 */
			while(head!=null) {
				stack.push(head);	
				head = head.left;
			}
			
			/**
			 * 找到右子树时，需要进入新的一轮找到左子树的过程（右子树中的最左节点）
			 * 所有还需要重回上面的分支，那么就 上下放在一个循环里
			 */
			while(!stack.isEmpty()) {
				head = stack.pop();
				System.out.print(head.val+",");
				head = head.right;
			}
		}
		
	}
	
}
