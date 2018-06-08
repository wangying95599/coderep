package wangy.tree;
/**
 * ���������нڵ�С�ڸ������������нڵ㲻С�ڸ��� 
 *
 * ���ʣ�pre,next, left,right,root,current
 */
public class BinarySearchTree {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BinarySearchTree tree = new BinarySearchTree();
	}
	/**
	 * �������Ĳ��ң�
	 * 1���ڸ����ͷ���
	 * 2С�ڸ����Ͳ�������
	 * 3���ڸ����Ͳ�������
	 * 
	 * ����һ������ĵݹ飬���ǲ���Ҫ���ݡ�һ�����ߵ�ͷ�ͽ�����������һ������ĵ㣬��������һ����ѷ�����
	 * ʲô���£�
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
	 * 1 ��� root Ϊ�գ������ڵ����root�����ء�
	 * 2 ����ֵ С�� current�ڵ� ������current�ڵ��������
	   3 ����ֵ��С�� current�ڵ㣬����current�ڵ��������
	   
	         �ʣ��ɲ����Բ��ݹ飬Ϊʲô��
	         �����ԣ�find һֱ�ڱȽϣ�һֱ�Ҳ���Ҷ�ӽڵ㣬�������ͷ���null while(head!=null) ��һֱ�ҵ�head=null
	         insert������һֱ�Ҳ�����������ĳ��Ҷ�ӽڵ㣬Ҳ�����Ǵ�һ��Ҷ�ӽڵ���м�ڵ㣬�����ҵ�head=null
	   �ݹ�=���÷���+�ݹ鷽��
	   
	   �ʣ������ô�죿
	   
	 �ʣ������Ҫ�ݹ���ô�죿
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
	 * ��Ҫ �ݹ���ô�죿
	 * ֮ǰ ���� �ǵݹ��ԭ����ʲô�� ���� ��head==null�� ��Ϊ����Ҫ���룬��Ҫpre�ڵ㣬
	   ���ˣ�֪����pre �ڵ㣬 ��left����right�� �ٺ�pre��һ�ξ�֪����
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
	 * ɾ�����鷳�ˣ� �����Ҷ�ӽڵ� ��ֱ��ɾ����û�˹��ġ������о��鷳�ˣ��������ϣ�
	 * ɾ�� ��֧�ڵ���ô���� �ӳи�ҵ���Լ�ɾ���������Ӷ����Լ���λ�á�
	 * ɾ��˫֧�ڵ���ô������������˭�̳��Լ����̳����������Լ���������ʞɣ�
	 * 
	 * ֱ��ǰ�������Լ�С���������Լ���ֵ����Ľڵ㡣Ҳ���������������ֵ��Ҳ�������������ҽڵ㡣
	 * ֱ�Ӻ�̣����Լ��󣬵������Լ���ֵ����Ľڵ㡣Ҳ��������������Сֵ��Ҳ��������������ڵ㡣
	 * 
	 * �ҵ�p��ֱ�Ӻ��d����Ϊdû������������ɾ����֧��ɾ��d��ͬʱ��d����p��
	 * 
	 * ���̣� 1����p��ֱ�Ӻ�̵�ֵ��p 2 ɾ��ֱ�Ӻ��
	 * 
	 */
	
	
	public void deleteChildless(TreeNode parent, TreeNode node) {
		//parent��ɾ���ڵ�ĸ��ڵ�
		if(parent.left == node) {
			parent.left = null;
		}else {
			parent.right = null;
		}
	}
	/**
	 * parent��ɾ���ڵ��parent�ڵ�
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
	 * 1 ���� ɾ���ڵ�node��parent��while()�м�¼parent
	 * 2�ж�node���ʣ������� ֱ��ɾ���� ����ɾ����֧���������Ҷ��ڣ����Ҷ��ڣ��͵��Ҹ��Ӱ��ˣ�
	 * 3 �ҵ�ֱ�Ӻ������Լ���ɾ��ֱ�Ӻ�̡�
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
			//��node ������������ ** Ѱ������ڵ��ͬʱ����¼�丸�׽ڵ㡣
			//????��while(node!=null)�������¼��Ҳֻ�ܼ�סҶ�ӽڵ�죿 
			//��Ȼ�ҵ��Ǹ��ף��ж��߼�Ҳ��Ӧ���Ǹ��ס� �жϾ��� node.left �Ƿ�Ϊ�ա�
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
