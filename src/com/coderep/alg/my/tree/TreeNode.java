package wangy.tree;
/**
 * 树是数据结构，不是存储结构。存储依然用数组，链表等。
 * @author wangy
 *
 * 多个TreeNode通过指针连着，就是树。
 */
public class TreeNode {
	int val;
	TreeNode left;
	TreeNode right;
	
	public TreeNode(int val) {
		this.val =val;
	}
	@Override
	public String toString() {
		return "TreeNode@val="+val;
	}
}
