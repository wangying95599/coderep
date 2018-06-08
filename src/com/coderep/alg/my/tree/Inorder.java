package wangy.tree;

import java.util.Stack;

/**
 * �������
 * ������ �� ������ �������ִ�С�����˳��
 * @author wangy
 *	
 * ����ķǵݹ飬���˺ܶࡣ
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
	 * ������������������
	 * 1�ҵ�������Ǹ��ڵ�L1�����ŵ�һλ��
	 * 2��Ҫ֪��L1�ĸ�R1����ͨ����R1���ҵ�R1. ��һ֦��ɡ����ҵ�R1�ĸ���Ҳ��˵���еĸ��㣬����Ҫ��¼������
	 * �� ���ص� ���� �Ը�Ϊ���ģ� �ɸ�������֧���������ҵ� ����ڵ�ʱ����Ҫ��ס�����е����и���
	 * 
	 * 3 �ҵ���������ʱ�� ��Ҫ������1���߼�
	 * 
	 * @param root
	 */
	public static void inorder2(TreeNode root) {
		if(root == null) {
			return ;
		}
		Stack<TreeNode> stack = new Stack<TreeNode>();
		TreeNode head = root;
		
		//������Ϊ�� �� ջΪ�գ��Ͳ�ѭ���ˡ������������ǵڶ���ѭ���õġ�
		//���������while ����һ������������ʱʼ�����Լ������� ���Ըĳ� while1->if while2->else
		while(head!=null && !stack.isEmpty()) {
		
			/**
			 * 1�ҵ�����ڵ㣬ͬʱ��¼���и�
			 */
			while(head!=null) {
				stack.push(head);	
				head = head.left;
			}
			
			/**
			 * �ҵ�������ʱ����Ҫ�����µ�һ���ҵ��������Ĺ��̣��������е�����ڵ㣩
			 * ���л���Ҫ�ػ�����ķ�֧����ô�� ���·���һ��ѭ����
			 */
			while(!stack.isEmpty()) {
				head = stack.pop();
				System.out.print(head.val+",");
				head = head.right;
			}
		}
		
	}
	
}
