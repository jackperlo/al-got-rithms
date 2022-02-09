package graph;

import java.util.*;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Test;

public class GraphTests{
  @Test
  public void createEmptyGraphNotDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    assertTrue(graph.getNodes().size() == 0);
  }
  @Test
  public void createEmptyGraphDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    assertTrue(graph.getNodesCount() == 0);
  }

  //---------------------------------------

  @Test
  public void addNode2aGraphNotDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);

    assertTrue(graph.getNodesCount() == 1);
  }
  @Test
  public void addNode2aGraphDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    
    assertTrue(graph.getNodesCount() == 1);
  }

  //-------------------------------------

  @Test
  public void addArch2aGraphNotDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);

    assertTrue(graph.getArchsCount() == 1);
  }
  @Test
  public void addArch2aGraphDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);
    
    assertTrue(graph.getArchsCount() == 1);
  }

  //----------------------------------------------

  @Test
  public void verifyDirectedGraphIsDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    assertTrue(graph.isDirectedGraph());
  }

  @Test
  public void verifyNotDirectedGraphIsDirected() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    assertFalse(graph.isDirectedGraph());
  }

  //----------------------------------------------

  @Test
  public void verifyIfDirectedGraphContainsThatNode() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);

    assertTrue(graph.checkContainsNode(1));
  }

  @Test
  public void verifyIfNotDirectedGraphContainsThatNode() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    
    assertTrue(graph.checkContainsNode(1));
  }

  //-------------------------------------------------
  @Test
  public void verifyIfDirectedGraphContainsThatArch() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 1);

    assertTrue(graph.checkContainsArch(1, 2));
  }

  @Test
  public void verifyIfNotDirectedGraphContainsThatArch() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 1);
  
    assertTrue(graph.checkContainsArch(1, 2));
    assertTrue(graph.checkContainsArch(2, 1));
  }

  //-----------------------------------------
  @Test
  public void checkNodeDeleteDirectedGraph() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0);
    
    graph.deleteNode(1);

    assertTrue((graph.getArchsCount() == 0) && (graph.getNodesCount() == 1));
  }

  @Test
  public void checkNodeDeleteNotDirectedGraph() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0);
    
    graph.deleteNode(1);

    assertTrue((graph.getArchsCount() == 0) && (graph.getNodesCount() == 1));
  }

  //----------------------------------------------

  @Test
  public void checkArchDeleteDirectedGraph() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 3);
    graph.deleteArch(1, 2);

    assertTrue(graph.getArchsCount() == 0);
  }

  @Test
  public void checkArchDeleteNotDirectedGraph() throws GraphException{
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0); 

    graph.deleteArch(1, 2);

    assertTrue(graph.getArchsCount() == 0);
  }

  // ----------------------------------------------

  @Test
  public void directedGraphNodesCount() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);

    assertTrue(graph.getNodesCount() == 2);
  }

  @Test
  public void notDirectedGraphNodesCount() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);

    assertTrue(graph.getNodesCount() == 2);
  }

  // ----------------------------------------------

  @Test
  public void directedGraphArchsCount() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0);
    graph.addNode(3);
    graph.addArch(2, 3, 5); 
    
    assertTrue(graph.getArchsCount() == 2);
  }

  @Test
  public void notDirectedGraphArchCount() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0);
    graph.addNode(3);
    graph.addArch(2, 3, 5);

    assertTrue(graph.getArchsCount() == 2);
  }
  
  // ----------------------------------------------

  @Test
  public void directedGraphGetNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    Set<Integer> expectedList = new HashSet<Integer>();
    expectedList.add(1);
    expectedList.add(2);
    expectedList.add(3);
    Set<Integer> graphNodesList = graph.getNodes();
    
    assertTrue(expectedList.equals(graphNodesList));
  }

  @Test
  public void notDirectedGraphGetNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    Set<Integer> expectedList = new HashSet<Integer>();
    expectedList.add(1);
    expectedList.add(2);
    expectedList.add(3);
    Set<Integer> graphNodesList = graph.getNodes();

    assertTrue(expectedList.equals(graphNodesList));
  }

  //---------------------------------------------------------------
  @Test
  public void directedGraphGetArchs() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 0);
    graph.addNode(3);
    graph.addArch(2, 3, 5); 
    ArrayList<Pair<Integer, Integer>> expectedList = new ArrayList<Pair<Integer, Integer>>();
    expectedList.add(new Pair<Integer, Integer>(1, 2));
    expectedList.add(new Pair<Integer, Integer>(2, 3));

    ArrayList<Pair<Integer, Integer>> graphArchsList = graph.getArchs();
    int i = 0;
    boolean allFine = true;
    for (Pair<Integer,Integer> pair : expectedList) {
      if(pair.getKey() != graphArchsList.get(i).getKey() || pair.getValue() != graphArchsList.get(i).getValue())
        allFine = false;
      i++;
    }
    assertTrue(allFine);
  }

  @Test
  public void notDirectedGraphGetArchs() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);
    graph.addNode(3);
    graph.addArch(2, 3, 30);
    ArrayList<Pair<Integer, Integer>> expectedList = new ArrayList<Pair<Integer, Integer>>();
    expectedList.add(new Pair<Integer, Integer>(2, 1));
    expectedList.add(new Pair<Integer, Integer>(3, 2));

    ArrayList<Pair<Integer, Integer>> graphArchsList = graph.getArchs();
    int i=0;
    boolean allFine = false;
    for (Pair<Integer, Integer> pair : expectedList) {
      if((pair.getKey() == graphArchsList.get(i).getKey() && pair.getValue() == graphArchsList.get(i).getValue()) || (pair.getKey() == graphArchsList.get(i).getValue() && pair.getValue() == graphArchsList.get(i).getKey()))
        allFine = true;
      i++;
    }
    assertTrue(allFine);
  }

  //---------------------------------------------

  @Test
  public void directedGraphAdjacentNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(2, 1, 15);
    graph.addNode(3);
    graph.addArch(2, 3, 5); 
    ArrayList<Integer> expectedList = new ArrayList<Integer>();
    expectedList.add(1);
    expectedList.add(3);
    ArrayList<Integer> graphAdjacentNodesList = graph.getAdjacentNodes(2);
    
    assertTrue(expectedList.equals(graphAdjacentNodesList));
  }

  @Test
  public void notDirectedGraphAdjacentNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);
    graph.addNode(3);
    graph.addArch(2, 3, 30);
    ArrayList<Integer> expectedList = new ArrayList<Integer>();
    expectedList.add(1);
    expectedList.add(3);
    ArrayList<Integer> graphAdjacentNodesList = graph.getAdjacentNodes(2);
    
    assertTrue(expectedList.equals(graphAdjacentNodesList));
  }

  // ---------------------------------------------

  @Test
  public void directedGraphGetLabelBetweenNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);

    assertTrue(graph.getLabelBetweenNodes(1, 2) == 15);
  }

  @Test
  public void notdirectedGraphGetLabelBetweenNodes() throws GraphException {
    Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);
    graph.addNode(1);
    graph.addNode(2);
    graph.addArch(1, 2, 15);

    assertTrue(graph.getLabelBetweenNodes(1, 2) == 15);
  }
}
