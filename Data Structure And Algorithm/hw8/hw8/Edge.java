package hw8;

public class Edge {
	private Double weight;
	private Vertex source;
	private Vertex destination;
	public Edge(Double weight, Vertex source, Vertex destination) {
		super();
		this.weight = weight;
		this.source = source;
		this.destination = destination;
	}
	public Double getWeight() {
		return weight;
	}
	public void setWeight(Double weight) {
		this.weight = weight;
	}
	public Vertex getSource() {
		return source;
	}
	public void setSource(Vertex source) {
		this.source = source;
	}
	public Vertex getDestination() {
		return destination;
	}
	public void setDestination(Vertex destination) {
		this.destination = destination;
	}
	
	
}
