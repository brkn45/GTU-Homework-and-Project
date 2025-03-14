package hw8;

public class Main {

	public static void main(String[] args) {
		MyGraph mg = new MyGraph(10); //  Create myGraph
		Vertex vt = mg.newVertex("manisa   ", 30);  // id 0  // create vertex
		mg.addVertex(vt);   // Add vertex
		vt = mg.newVertex("izmir    ", 50);   		// id 1
		mg.addVertex(vt);
		
		vt = mg.newVertex("konya    ", 70);			// id 2
		mg.addVertex(vt);
		
		vt = mg.newVertex("antalya  ", 40);		// id 3
		mg.addVertex(vt);
		
		vt = mg.newVertex("mersin   ", 100);		// id 4
		mg.addVertex(vt);
		
		vt = mg.newVertex("Bursa    ", 50);			// id 5
		mg.addVertex(vt);
		
		MatrixGraph mt = mg.exportMatrix(); // translate adjencj matrix graph
		mg.printGraph();
		
		mt.print();   // print adjency matrix
		System.out.println("Add Edge");
		mg.addEdge(1, 2, 30);    // Add Adge
		mg.addEdge(0,3,40);
		mg.addEdge(3, 1, 40);
		mg.printGraph();  // print graph
		
		System.out.println("Remove Edge");
		mg.removeEdge(1, 3);  // remove edge
		
		mg.printGraph();  // print graph
		
		System.out.println("Remove Vertex with given id ");
		mg.removeVertex(0); // remove vertex with given id
		mg.printGraph();
		
		System.out.println("remove vertex with string");
		mg.removeVertex("antalya"); // remove vertex with string
		mg.printGraph();
		
		
		
		
		
		
	}

}
