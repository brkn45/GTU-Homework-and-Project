package hw8;

import java.util.ArrayList;

public class Vertex {
	private int index;
	private String label;
	private double weight;
	private int edgeSize=0;
	private int edgeCount =0;
	private ArrayList<Edge> edge;
	
	public Vertex(int index, String label, double weight) {
		super();
		this.index = index;
		this.label = label;
		this.weight = weight;
		this.edge = new ArrayList<Edge>();
	}
	
	
	public int getIndex() {
		return index;
	}
	public void setIndex(int index) {
		this.index = index;
	}
	public String getLabel() {
		return label;
	}
	


	public int getEdgeSize() {
		return edgeSize;
	}


	public void setEdgeSize(int edgeSize) {
		this.edgeSize = edgeSize;
	}


	public int getEdgeCount() {
		return edgeCount;
	}


	public void setEdgeCount(int edgeCount) {
		this.edgeCount = edgeCount;
	}


	public ArrayList<Edge> getEdge() {
		return edge;
	}


	public void setEdge(ArrayList<Edge> edge) {
		this.edge = edge;
	}


	public void setLabel(String label) {
		this.label = label;
	}
	public double getWeight() {
		return weight;
	}
	public void setWeight(double weight) {
		this.weight = weight;
	}
	
	public void addEdge(Vertex vtDestination,double weight) {
		
		Edge tmp = new Edge(weight, this, vtDestination);
		
		edge.add(tmp);
		
	}
	
	public void removeEdge(Vertex vtDestination) {
		int i=0;
		for(i=0; i < edge.size();i++) {
			if(edge.get(i).getDestination().equals(vtDestination) == true) {
				edge.remove(i);
				break;
			}
		}
	}
	
}
