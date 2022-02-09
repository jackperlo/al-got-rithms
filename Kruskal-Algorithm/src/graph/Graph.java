package graph;

import java.util.*;

/**
 * T -> value of the node
 * E -> label of the arch
 */
public class Graph<T, E>{
  private HashMap<T, ArrayList<Pair<T, E>>> map;
  private boolean directedGraph;
  
  public static final boolean directed = true;
  public static final boolean notDirected = false;
  
  public Graph(boolean directedGraph){
    this.map = new HashMap<T, ArrayList<Pair<T, E>>>();
    this.directedGraph = directedGraph;
  }

  /**
   * <p>
   * It adds a node into the graph.
   * </p>
   * <p>
   * <b>Usage Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * 
   * @param nodeValue value of the &lt T &gt element of the node which will be
   *                  inserted in the graph
   * @exception GraphException when nodeValue parameter is null
   */
  public void addNode(T nodeValue) throws GraphException{
    if(nodeValue == null)
      throw new GraphException("addNode: nodeValue cannot be null");
    if(checkContainsNode(nodeValue))
      throw new GraphException("addNode: nodeValue already belongs to this graph");

    ArrayList<Pair<T, E>> empt = new ArrayList<Pair<T, E>>();
    map.put(nodeValue, empt);
  }

   /**
    * <p>
    * It adds an arch into the graph
    * </p>
    * <p>
    * If the graph is not directed it automatically adds the return-arch.
    * </p>
    * <p>
    * <b>Usage Example</b>
    * </p>
    * <p>
    * <p>
    * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.notDirected);}
    * </p>
    * <p>
    * {@code graph.addNode(1);}
    * </p>
    * <p>
    * {@code graph.addNode(2);}
    * </p>
    * <p>
    * {@code graph.addArch(1, 2, 0);}
    * </p>
    * 
    * @param fromNode &lt T &gt from node: node from which the arch starts
    * @param toNode   &lt T &gt to node: node to which the arch ends
    * @param label    E label: arch's label
    */
  public void addArch(T fromNode, T toNode, E label) throws GraphException{    
    if(fromNode == null)
      throw new GraphException("addArch: fromNode parameter cannot be null");
    if(!checkContainsNode(fromNode))
      throw new GraphException("addArch: the fromNode passed as a parameter does not belong to this graph");
    if(toNode == null)
      throw new GraphException("addArch: toNode parameter cannot be null");
    if(!checkContainsNode(toNode))
      throw new GraphException("addArch: the toNode passed as a parameter does not belong to this graph");
    if(label == null)
      throw new GraphException("addArch: label value of the node cannot be null");
    if(checkContainsArch(fromNode, toNode))
      throw new GraphException("addArch: arch between fromNode and toNode parameters already exists");
      
    Pair<T, E> toAdd = new Pair<T, E>(toNode, label);
    map.get(fromNode).add(toAdd);
    if(!this.directedGraph){
      Pair<T, E> toAdd2 = new Pair<T, E>(fromNode, label);
      map.get(toNode).add(toAdd2);
    }
  }

  /**
   * <p>Check if the graph is directed</p>
   * 
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code graph.isDirectedGraph();}
   * </p>
   * 
   * @return true if the graph is directed, false otherwise
   */
  public boolean isDirectedGraph(){
    return directedGraph;
  }

  /**
   * <p>
   * It checks Node passed as a parameter belongs to this graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code checkContainsNode(nodeToCheck);}
   * </p>
   * 
   * @param nodeToCheck Node &lt T &gt nodeToCheck: node to check if owned by the
   *                    graph or not
   * @return true if the node belongs to the graph, false otherwise
   */
  public boolean checkContainsNode(T nodeToCheck) throws GraphException{
    if(nodeToCheck == null)
      throw new GraphException("checkContainsNode: nodeToCheck parameter cannot be null");

    return map.get(nodeToCheck) != null;
  }
  
  /**
   * <p>
   * It checks if the graph contains an arch.
   * </p>
   * 
   * <p>
   * <b>Usege Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * </p>
   * {@code graph.addNode(1);}
   * </p>
   * </p>
   * {@code graph.addNode(2);}
   * </p>
   * </p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code boolean returnValue = graph.checkContainsArch(1, 2);}
   * </p>
   * 
   * @param fromNode
   * @param toNode
   * @return TRUE iff the arch is contenined into the graph, FALSE otherwise.
   * @exception GraphException if fromNode, ToNode are null or if fromNode, toNode
   *                           doesn't not belong to the graph
   */
  public boolean checkContainsArch(T fromNode, T toNode) throws GraphException{
    if(fromNode == null)
      throw new GraphException("checkContainsArch: fromNode parameter cannot be null");
    if (!checkContainsNode(fromNode))
      throw new GraphException("checkContainsArch: the fromNode passed as a parameter does not belong to this graph");
    if(toNode == null)
      throw new GraphException("checkContainsArch: toNode parameter cannot be null");
    if(!checkContainsNode(toNode))
      throw new GraphException("checkContainsArch: the toNode passed as a parameter does not belong to this graph");
    
    boolean found = false;
    for (Pair<T, E> element : map.get(fromNode)) {
      if(element.getKey() == toNode){
        found = true;
        break;
      }
    }
    return found;
  }

  /**
   * <p>
   * It delete the node into the graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code graph.deleteNode(1);}
   * </p>
   * 
   * @param nodeToDelete Node &lt T &gt nodeToDelete: node to delete
   *            
   */
  public void deleteNode(T nodeToDelete) throws GraphException{
    if(nodeToDelete == null)
      throw new GraphException("deleteNode: nodeToDelete parameter cannot be null");
    if(!checkContainsNode(nodeToDelete))
      throw new GraphException("deleteNode: the nodeToDelete passed as a parameter does not belong to this graph");

    for (T nodo : map.keySet()){
      if(nodo != nodeToDelete){
        int i = 0;
        ArrayList<Pair<T, E>> lst = map.get(nodo);
        for (Pair<T, E> el : lst){
          if(el.getKey() == nodeToDelete){
            lst.remove(i);
            break;
          }
          i++;
        }
      }
    }
    map.remove(nodeToDelete);
  }

  /**
   * <p>
   * It delete the arch between two nodes
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code graph.deleteArch(1, 2);}
   * </p>
   * 
   * @param fromNode
   * @param toNode
   * 
   */
  public void deleteArch(T fromNode, T toNode) throws GraphException{
    if(fromNode == null)
      throw new GraphException("deleteArch: fromNode parameter cannot be null");
    if(!checkContainsNode(fromNode))
      throw new GraphException("deleteArch: the fromNode passed as a parameter does not belong to this graph");
    if(toNode == null)
      throw new GraphException("deleteArch: toNode parameter cannot be null");
    if(!checkContainsNode(toNode))
      throw new GraphException("deleteArch: the toNode passed as a parameter does not belong to this graph");
    
    int i = 0;
    ArrayList<Pair<T, E>> lst = map.get(fromNode);
    for (Pair<T, E> element : lst) {
      if(element.getKey() == toNode){
        lst.remove(i);
        break;
      }
      i++;
    }

    if(!this.directedGraph){
      i=0;
      ArrayList<Pair<T, E>> lst2 = map.get(toNode);
      for (Pair<T, E> element : lst2) {
        if(element.getKey() == fromNode){
          lst2.remove(i);
          break;
        }
        i++;
      }
    }
  }

  /**
   * <p>
   * It returns the number of the nodes into the graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.getNodesCount();}
   * </p>
   * 
   * @return Integer number rapresenting the nodes number
   * 
   */
  public int getNodesCount(){
    return map.size();
  }

  /**
   * <p>
   * It returns the number of the arch into the graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code graph.getArchsCount();}
   * </p>
   * 
   * @return Integer number rapresenting the archs number
   * 
   */
  public int getArchsCount(){
    int size = 0;
    for (ArrayList<Pair<T, E>> el : map.values()) {
      size += el.size();
    }
    if(!this.isDirectedGraph())
      size = size/2;
    return size;
  }

  /**
   * <p>
   * It returns all the nodes of the graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code Set<Integer> graphNodesList = graph.getNodes();}
   * </p>
   * 
   * @return Set &lt T &gt of nodes
   * 
   */
  public Set<T> getNodes(){
    return map.keySet();
  }

  /**
   * puntatore ad ArrayArchs
   *    |
   *    V
   * A -> | A, 10, B | A, 30, D     -->1op
   * B -> | B, 20, C |              -->1op
   * C -> | \                       -->0op
   * D -> | D,  5, C |              -->1op
   * -----------------------------------------------------
   *                                   3op = numero di nodi, mentre GitLab indica che ci deve mettere O(n=#archi)
   */

  /**
   * <p>
   * It returns all the archs of the graph
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code ArrayList<Pair<Integer, Integer>> graphArchsList = graph.getArchs();}
   * </p>
   * 
   * @return ArrayList &lt Pair &lt Integer, Integer &gt &gt of archs
   * 
   */
  public ArrayList<Pair<T, T>> getArchs() throws GraphException{
    ArrayList<Pair<T, T>> arrayArchsToReturn = new ArrayList<Pair<T, T>>();
    HashMap<T, HashMap<T, Boolean>> got = new HashMap<T, HashMap<T, Boolean>>();
    for (T node : map.keySet()) {
      for (Pair<T, E> el : map.get(node)) {
        if(!this.isDirectedGraph()){
          if(got.get(el.getKey()) == null || got.get(el.getKey()).get(node) == null){
            if(got.get(node) == null){
              HashMap<T, Boolean> aus = new HashMap<T, Boolean>();
              aus.put(el.getKey(), true);
              got.put(node, aus);
            }else{
              HashMap<T, Boolean> aus = got.get(node);
              aus.put(el.getKey(), true);
            }
            Pair<T, T> toAdd = new Pair<T, T>(node, el.getKey());
            arrayArchsToReturn.add(toAdd);
          }
        }else{
          Pair<T, T> toAdd = new Pair<T, T>(node, el.getKey());
          arrayArchsToReturn.add(toAdd);
        }
      }
    }
    return arrayArchsToReturn;
  }

  /**
   * <p>
   * It returns all the nodes that are adjacent to the one passed as input
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code ArrayList<Integer> adjacentNodes = graph.getAdjacentNodes(1);}
   * </p>
   * 
   * @param node
   * @return ArrayList &lt Integer &gt of nodes
   * 
   */
  public ArrayList<T> getAdjacentNodes(T node) throws GraphException{
    if(node == null)
      throw new GraphException("getAdjacentNodes: node parameter cannot be null");
    if(!checkContainsNode(node))
      throw new GraphException("getAdjacentNodes: the node passed as a parameter does not belong in this graph");

    ArrayList<T> toReturn = new ArrayList<T>();
    for (Pair<T, E> el : map.get(node)) {
      toReturn.add(el.getKey());
    }
    return toReturn;
  }

  /**
   * <p>
   * It returns the label associated with the two nodes passaed as input
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code Graph<Integer, Integer> graph = new Graph<Integer, Integer>(Graph.directed);}
   * </p>
   * <p>
   * {@code graph.addNode(1);}
   * </p>
   * <p>
   * {@code graph.addNode(2);}
   * </p>
   * <p>
   * {@code graph.addArch(1, 2, 0);}
   * </p>
   * <p>
   * {@code int label = graph.getLabelBetweenNodes(1, 2);}
   * </p>
   * 
   * @param fromNode
   * @param toNode
   * @return E label between nodes
   * 
   */
  public E getLabelBetweenNodes(T fromNode, T toNode) throws GraphException{
    if(fromNode == null)
      throw new GraphException("getLabelBetweenNodes: fromNode parameter cannot be null");
    if(!checkContainsNode(fromNode))
      throw new GraphException("getLabelBetweenNodes: the fromNode passed as a parameter does not belong to this graph");
    if(toNode == null)
      throw new GraphException("getLabelBetweenNodes: toNode parameter cannot be null");
    if(!checkContainsNode(toNode))
      throw new GraphException("getLabelBetweenNodes: the toNode passed as a parameter does not belong to this graph");

    E archLabel = null;
    for (Pair<T, E> arch : map.get(fromNode)) {
      if(arch.getKey() == toNode){
        archLabel = arch.getValue();
        break;
      }
    }
    return archLabel;
  }
}