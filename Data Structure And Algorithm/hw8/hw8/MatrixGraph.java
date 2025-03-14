package hw8;

public class MatrixGraph {
	private int size;
	private boolean [][] matrix;
	private Vertex [] vertex;
	public MatrixGraph(int size,boolean [][] matrix,Vertex [] vertex) {
		super();
		this.size = size;
		this.matrix =matrix;
		this.vertex = vertex;
	}
	public int getSize() {
		return size;
	}
	public void setSize(int size) {
		this.size = size;
	}
	public boolean[][] getMatrix() {
		return matrix;
	}
	public void setMatrix(boolean[][] matrix) {
		this.matrix = matrix;
	}
	
	public void print() {
		int i=0,k=0;
		System.out.print("             ");
		for(i=0;i<size;i++) {
			if(vertex[i] != null) {
				System.out.print(vertex[i].getLabel()+ " ");
			}
			else {
				System.out.print("         ");
			}
			
		}
		System.out.println("");
		for(i=0;i< size;i++ ) {
			if(vertex[i] != null) {
				System.out.print(vertex[i].getLabel()+ "      ");
			}
			else {
				System.out.print("               ");
			}
			for(k=0;k <size;k++) {
				if(matrix[i][k]) {
					System.out.print(1 +"         " );
				}
				else {
					System.out.print(0 +"         " );
				}
				
			}
			System.out.println("");
		}
	}
	
}
