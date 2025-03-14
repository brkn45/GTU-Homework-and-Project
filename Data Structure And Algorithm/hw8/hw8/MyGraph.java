package hw8;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class MyGraph implements DynamicGraph {
	
	private List < Vertex > [] vertex;
	private int id =0;
	private int size;
	private int count =0;
	
	
	public MyGraph(int numV) {
	    this.size = numV;
	    vertex = new List[numV];
	    for (int i = 0; i < numV; i++) {
	      vertex[i] = new LinkedList < Vertex > ();
	    }
	  }
	
	/**
	 * create new vertex
	 */
	@Override
	public Vertex newVertex(String label, double weight) {
		Vertex vertex = new Vertex(id,label,weight);
		id++;
		return vertex;
	}

	/**
	 * add new vertex
	 */
	@Override
	public void addVertex(Vertex new_vertex) {
		if(count <size) {
			vertex[count].add(new_vertex);
			count++;
		}
		
	}

	/**
	 * add new edge
	 */
	@Override
	public void addEdge(int vertexID1, int vertexID2, double weight) {
		int i=0;
		int index1=0,index2=0;
		int flag =0;
		for(i=0;i < size ;i++) {
			if(vertex[i].get(0).getIndex() == vertexID1) {
				index1 = i;
				flag++;
				break;
			}
		}
		
		for(i=0;i < size ;i++) {
			if(vertex[i].get(0).getIndex() == vertexID2) {
				index2 = i;
				flag++;
				break;
			}
		}
		if(flag ==2) {
			vertex[index1].add(vertex[index2].get(0)); // directed olursa buraya if koy
			vertex[index2].add(vertex[index1].get(0));
		}
		connectEdge(vertex[index1].get(0),vertex[index2].get(0),weight);
	}
	
	/**
	 * @param vt1
	 * @param vt2
	 * @param weight
	 */
	private void connectEdge(Vertex vt1,Vertex vt2,double weight){
		 vt1.addEdge(vt2,weight);
		 vt2.addEdge(vt1,weight);
	}
	/**
	 * Remove vertex given between two vertex
	 */
	@Override
	public void removeEdge(int vertexID1, int vertexID2) {
		int i=0,index1=0,index2=0;
		int flag =0;
		for(i=0;i < size ;i++) {
			if(vertex[i].get(0).getIndex() == vertexID1) {
				index1 = i;
				flag++;
				break;
			}
		}
		
		for(i=0;i < size ;i++) {
			if(vertex[i].get(0).getIndex() == vertexID2) {
				index2 = i;
				flag++;
				break;
			}
		}
		if(flag == 2) {
			vertex[index1].remove(vertex[index2].get(0));
			vertex[index1].get(0).removeEdge(vertex[index2].get(0));
			vertex[index2].remove(vertex[index1].get(0));
			vertex[index2].get(0).removeEdge(vertex[index1].get(0));
		}
		
	}

	/**
	 * Remove vertex given string id
	 */
	@Override
	public void removeVertex(int vertexID) {
		int i=0,index1=0;
		for(i=0;i < size ;i++) {
			if(vertex[i].get(0).getIndex() == vertexID) {
				index1 = i;
				
				break;
			}
		}
		
		for(i=0;i< vertex.length;i++) {
			if(vertex[i] != null && vertex[i].size() > 0 && i != index1) {
				if(vertex[i].contains(vertex[index1].get(0))) {
					vertex[i].remove(vertex[index1].get(0));
				}
				
			}
		}
		vertex[index1].clear();
		/*
		for(i=0; i< vertex[index1].size();i++) {
			vertex[index1].get(i).removeEdge(vertex[index1].get(0));
		}*/
		
	}

	/**
	 * Remove vertex given string label
	 */
	@Override
	public void removeVertex(String label) {
		int i=0;
		for(i=0;i<vertex.length;i++) {
			if(vertex[i].size() > 0) {
				if(vertex[i].get(0).getLabel().equals(label) == true) {
					removeVertex(vertex[i].get(0).getIndex());
					break;
				}
			}
			
		}
		
	}

	@Override
	public void filterVertices(String key, String filter) {
		// TODO Auto-generated method stub
		
	}

	/**
	 * Tranform to list to matrix graph
	 */
	@Override
	public MatrixGraph exportMatrix() {
		int i=0,k=0;
		boolean [][] tmp = new boolean[vertex.length][vertex.length];
		for(i=0;i<vertex.length;i++) {
			
			if(vertex[i].size() >0) {
				for(k=0; k< vertex[i].size();k++) {
					tmp[i][vertex[i].get(k).getIndex()] = true;
				}
			}
			
			
		}
		
		MatrixGraph mt = new MatrixGraph(vertex.length,tmp,makeArrayVertex());
		return mt;
		
	}
	/**
	 * Helper function
	 * Tranform to list to matrix graph
	 * @return
	 */
	private Vertex [] makeArrayVertex() {
		int i=0;
		Vertex [] tmp = new Vertex[vertex.length];
		for(i=0;i<vertex.length;i++) {
			if(vertex[i].size() > 0) {
				tmp[i] = vertex[i].get(0);
			}
			else {
				tmp[i] = null;
			}
			
		}
		return tmp;
	}
	/**
	 *Print graph list format
	 */
	@Override
	public void printGraph() {
		int i =0;
		for(i=0;i<size;i++) {
			Iterator<Vertex> iter = vertex[i].iterator();
			System.out.print("i: " );
			while(iter.hasNext()) {
				System.out.print(iter.next().getLabel()+", ");
			}
			System.out.println("");
		}
		
	}
	public void print() {
		
	}

}
