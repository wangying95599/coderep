package wangy.tree;
/**
 * �������ݽṹ�����Ǵ洢�ṹ���洢��Ȼ�����飬����ȡ�
 * @author wangy
 *
 * ���TreeNodeͨ��ָ�����ţ���������
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
