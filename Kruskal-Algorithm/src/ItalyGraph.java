import unionfindset.*;
import graph.*;
import kruskal.*;

import java.io.File;
import java.io.FileNotFoundException;  
import java.util.*; 

public class ItalyGraph{
  public static void main(String[] args) throws Exception, GraphException, UnionFindSetException{
    if(args.length <= 0)
      throw new Exception("Source File Name not found. Specify that and retry.");

    Graph<String, Double> graph = readFile(args[0]);
    ArrayList<Pair<String, String>> mst_graph = Kruskal.mst(graph);
    int archNumber = mst_graph.size();
    Double totalWeight = 0.0;
    int nodeNumber = graph.getNodesCount();
    for (Pair<String,String> pair : mst_graph){
      totalWeight += graph.getLabelBetweenNodes(pair.getKey(), pair.getValue())/1000;
    }
    System.out.println("Archs Number: " + archNumber);
    System.out.println("Nodes Number: " + nodeNumber);
    System.out.printf("Total Weight: %.3fkm", totalWeight);
  }

  /*
   * This method create a graph based on file passed as input
   */
  private static Graph<String, Double> readFile(String fileName) throws GraphException{
    try {
      File myObj = new File(fileName);
      Scanner myReader = new Scanner(myObj);
      Graph<String, Double> graph = new Graph<String, Double>(Graph.notDirected);
      while (myReader.hasNextLine()) {
        String data = myReader.nextLine();
        String[] values = data.split(",");
        if(!graph.checkContainsNode(values[0]))
          graph.addNode(values[0]);
        if(!graph.checkContainsNode(values[1]))
          graph.addNode(values[1]);
        graph.addArch(values[0], values[1], Double.parseDouble(values[2]));
      }
      myReader.close();

      return graph;
    } catch (FileNotFoundException e) {
      System.out.println(e.getMessage());
      e.printStackTrace();
      return null;
    }
  }
}
