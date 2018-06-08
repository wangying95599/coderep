package wangy.search;

import java.util.LinkedList;

//���broad ע���к��в�һ����ȡ� �жϲ�Ҫд��
//�Ա����������������  ���е�ѭ��������ݹ顣 ��������ά�ֹ�ȵ�˳��
//��ͼ�ƶ����ص�=��������+·����mark
public class NumIsland_200_med_bfs {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		int[][] grid = {
				{1,1,1,0,0},
				{0,0,1,1,1},
				{0,0,1,0,0},
				{0,0,0,1,1}};
		int[][] mark = new int[4][5];
		printMark(mark);
		int num = numIslands(grid, mark);
		System.out.println("num     "+num);
	}
	
	 public static int numIslands(int[][] grid,int[][] mark) {
		 int number = 0;
		 
		 for(int i=0;i<grid.length;i++) {
			for(int j=0;j<grid[i].length;j++) {
				
				if(mark[i][j]==0 && grid[i][j]==1) {
					System.out.println("numIsLandas "+i+","+j);
					dfs(grid,mark,i,j);
					
					number ++;
					System.out.println(number +"������  ");
					printMark(mark);
				}
			} 
		 }
		 return number;
	 }
	 
	 public static void bfs(int[][] grid,int[][] mark,int x, int y) {
		
		printMark(mark);
		/**
		 * ��x�������ƶ�����y�����¶���
		 */
		int[] dx = {-1,1,0,0};
		int[] dy = {0,0,-1,1};
		LinkedList<Point> queue = new LinkedList<Point>();
		
		queue.add(new Point(x,y));
		mark[x][y] =1;//����Ķ������ ����У��ͱ�ǡ� ������Ѳ��ܵݹ顣
		
		while(!queue.isEmpty()) {
			Point p =queue.pop();
			x = p.x;
			y=p.y;
			for(int i=0;i<dx.length;i++) {
				int new_x = x+dx[i];
				int new_y = y+dy[i];
				
				if(new_x<0||new_x>= mark.length ||new_y<0||new_y>=mark[new_x].length) {
					continue;
				}
				
				System.out.println("mark   "+new_x+", "+new_y);
				if(mark[new_x][new_y]==0 && grid[new_x][new_y]==1) {
					//dfs(grid, mark,new_x,new_y);
					queue.push(new Point(new_x,new_y));
					mark[new_x][new_y]=1;
				}
			}
		}
		
		
	 }
	
	public static void dfs(int[][] grid,int[][] mark,int x, int y) {
		//������������Ǻţ������·
		mark[x][y] =1;
		printMark(mark);
		/**
		 * ��x�������ƶ�����y�����¶���
		 */
		int[] dx = {-1,1,0,0};
		int[] dy = {0,0,-1,1};
		
		for(int i=0;i<dx.length;i++) {
			int new_x = x+dx[i];
			int new_y = y+dy[i];
			
			if(new_x<0||new_x>= mark.length ||new_y<0||new_y>=mark[new_x].length) {
				continue;
			}
			
			System.out.println("mark   "+new_x+", "+new_y);
			if(mark[new_x][new_y]==0 && grid[new_x][new_y]==1) {
				dfs(grid, mark,new_x,new_y);
			}
		}
	}
	
	public static void printMark(int[][] mark) {
		System.out.println("----------------");
		for(int i=0;i<mark.length;i++) {
			for(int j=0;j<mark[i].length;j++) {
				System.out.print(mark[i][j]);
			} 
			System.out.println();
		 }
		System.out.println("----------------");
	}
}
class Point{
	int x;
	int y;
	public Point(int x,int y) {
		this.x =x;
		this.y = y;
	}
}