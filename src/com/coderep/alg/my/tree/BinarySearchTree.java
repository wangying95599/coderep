package wangy.tree;
/**
 * 左子树所有节点小于根，右子树所有节点不小于跟。 
 *
 * 单词：pre,next, left,right,root,current
 */
public class BinarySearchTree {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BinarySearchTree tree = new BinarySearchTree();
	}
	/**
	 * 二叉树的查找：
	 * 1等于根，就返回
	 * 2小于根，就查左子树
	 * 3大于根，就查右子树
	 * 
	 * 这是一个特殊的递归，就是不需要回溯。一次性走到头就结束。就是找一个具体的点，而不是找一个最佳方案。
	 * 什么故事？
	 */
	public TreeNode find(int val, TreeNode root) {
		if(root == null) {
			return null;
		}
		TreeNode head = root;
		while(head != null) {
			if(head.val == val) {
				return head;
			}else if(head.val < val) {
				head = head.right;
			}else {
				head = head.left;
			}
		}
		
		return null;
	} 
	/**
	 * 1 如果 root 为空，则插入节点就是root，返回。
	 * 2 插入值 小于 current节点 ，插入current节点的左子树
	   3 插入值不小于 current节点，插入current节点的右子树
	   
	         问：可不可以不递归，为什么？
	         不可以，find 一直在比较，一直找不到叶子节点，不合作就返回null while(head!=null) 会一直找到head=null
	         insert，不能一直找不到，可能是某个叶子节点，也可能是带一个叶子节点的中间节点，不能找到head=null
	   递归=调用方法+递归方法
	   
	   问：相等怎么办？
	   
	 问：如果非要递归怎么办？
	 */
	
	public boolean insert_(int val,TreeNode root) {
		return insert(val, root);
	}
	
	public boolean insert(int val, TreeNode root) {
		if(root == null) {
			root= new TreeNode(val);
			return true;
		}
		
		if(root.val > val) {
			return insert(val, root.left);
		}else {
			return insert(val,root.right);
		}
		
	}
	/**
	 * 非要 递归怎么办？
	 * 之前 不能 非递归的原因是什么？ 不能 让head==null， 因为我们要插入，需要pre节点，
	   好了，知道了pre 节点， 插left还是right？ 再和pre比一次就知道了
	 */
	public boolean insert2(int val, TreeNode root) {
		if(root== null) {
			root = new TreeNode(val);
			return true;
		}
		TreeNode head = root;
		TreeNode current = null;
		while(head !=null) {
			current = head;
			
			if(head.val >val) {
				head = head.left;
			}else if(head.val < val) {
				head = head.right;
			}else {
				return false;
			}
		}
		if(current.val > val) {
			current.left = new TreeNode(val);
		}else {
			current.right = new TreeNode(val);
		}
		
		return true;
	}
	
	/**
	 * 删除就麻烦了， 如果是叶子节点 就直接删除，没人关心。但是有就麻烦了（养儿防老）
	 * 删除 单支节点怎么处理？ 子承父业，自己删除，独生子顶替自己的位置。
	 * 删除双支节点怎么处理？两个儿子谁继承自己，继承人是最像自己的子孙（朱允炆）
	 * 
	 * 直接前驱：比自己小，但是离自己的值最近的节点。也就是左子树的最大值，也是左子树的最右节点。
	 * 直接后继：比自己大，但是离自己的值最近的节点。也就是右子树的最小值，也是右子树的最左节点。
	 * 
	 * 找到p的直接后继d，因为d没有左子树，用删除单支法删除d，同时，d代替p。
	 * 
	 * 过程： 1拷贝p的直接后继的值到p 2 删除直接后继
	 * 
	 */
	
	
	public void deleteChildless(TreeNode parent, TreeNode node) {
		//parent是删除节点的父节点
		if(parent.left == node) {
			parent.left = null;
		}else {
			parent.right = null;
		}
	}
	/**
	 * parent是删除节点的parent节点
	 */
	public void deleteSingleSon(TreeNode parent, TreeNode node) {
		TreeNode grandNode = node.left!=null ?node.left:node.right;
		
		if(parent.left == node) {
			parent.left = grandNode;
		}else {
			parent.right = grandNode;
		}
	}
	
	/**
	 * 1 查找 删除节点node的parent，while()中记录parent
	 * 2判断node性质，决定是 直接删除， 还是删除单支。还是左右都在（左右都在，就得找个接班人）
	 * 3 找到直接后继替代自己，删除直接后继。
	 * 
	 */
	public void delete(TreeNode root, TreeNode node) {
		if(root == null) {
			return ;
		}
		
		TreeNode head = root;
		TreeNode parent=null;
		while(head!=null) {
			parent = head;
			if(head.val < node.val) {
				head = head.right;
			}else if(head.val > node.val) {
				head = head.left;
			}else {
				break;
			}
		}
		
		if(node.left ==null && node.right == null) {
			deleteChildless(parent, node);
		}else if(node.left==null || node.right == null) {
			deleteSingleSon(parent, node);
		}else {
			//找node 右子树的最左。 ** 寻找最左节点的同时，记录其父亲节点。
			//????用while(node!=null)，计算记录，也只能记住叶子节点办？ 
			//既然找的是父亲，判断逻辑也就应该是父亲。 判断就是 node.left 是否为空。
			TreeNode leftNode = node.right;
			TreeNode leftParentNode = null;
			while(leftNode.left != null) {
				leftParentNode = leftNode;
				leftNode = leftNode.left;
			}
			
			node.val = leftNode.val;
			if(leftNode.right==null) {
				deleteChildless(leftParentNode, leftNode);
			}else {
				deleteSingleSon(leftParentNode, leftNode);
			}
		}
		
	}
	
	
}
