package hw8;

public interface DynamicGraph {
	Vertex newVertex (String label, double weight);
	void addVertex (Vertex new_vertex);
	void addEdge (int vertexID1, int vertexID2, double weight);
	void removeEdge (int vertexID1, int vertexID2);
	void removeVertex (int vertexID);
	void removeVertex (String label);
	void filterVertices (String key, String filter);
	MatrixGraph exportMatrix();
	void printGraph();
}
