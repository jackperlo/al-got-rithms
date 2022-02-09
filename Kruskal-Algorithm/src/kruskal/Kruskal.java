package kruskal;

import graph.*;
import unionfindset.*;

import java.util.*;

public class Kruskal {
  /**
   * <p>
   * It returns the mst(Maximum Spanning Tree) of the graph passed as input
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
   * {@code ArrayList<Pair<String, String>> mst_graph = Kruskal.mst(graph);}
   * </p>
   * 
   * @param graph
   * @return ArrayList &lt Pair &lt T, T &gt &gt
   * 
   */
  /**
   * E extends Comparable so that arch labels can only be classes that can be
   * compared (Integer, Float, String, ...). It makes no sense to call Kruskal
   * with archs whose weights are not comparable
   */
  public static <T, E extends Comparable<E>> ArrayList<Pair<T,T>> mst(Graph<T, E> graph) throws GraphException, UnionFindSetException{
    ArrayList<Pair<T,T>> lA = new ArrayList<Pair<T,T>>();
    HashMap<T, UnionFindSet<T>> p = new HashMap<T, UnionFindSet<T>>();
    for (T node : graph.getNodes()) {
      UnionFindSet<T> el = new UnionFindSet<T>(node);
      p.put(node, el);
    }

    HashMap<Pair<T,T>, E> weightArchs = new HashMap<Pair<T,T>, E>();
    for (Pair<T,T> pair : graph.getArchs()) {
      weightArchs.put(pair, graph.getLabelBetweenNodes(pair.getKey(), pair.getValue()));
    }
    HashMap<Pair<T,T>, E> ordered = sortByValue(weightArchs);

    for (Pair<T,T> arch : ordered.keySet()) {
      UnionFindSet<T> u = p.get(arch.getKey());
      UnionFindSet<T> v = p.get(arch.getValue());
      if(u.findSet() != v.findSet()){
        lA.add(arch);
        u.union(v);
      }
    }
    return lA;
  }

  /**
   * <p>
   * It order the hash map based on elements values
   * </p>
   * 
   * @param hm
   * @return HashMap &lt T, E &gt ordered
   * 
   */
  private static <T, E extends Comparable<E>> HashMap<T, E> sortByValue(HashMap<T, E> hm)
  {
    // Create a list from elements of HashMap
    List<Map.Entry<T, E>> list = new LinkedList<Map.Entry<T, E>>(hm.entrySet());

    // Sort the list
    Collections.sort(list, new Comparator<Map.Entry<T, E> >() {
      public int compare(Map.Entry<T, E> o1, Map.Entry<T, E> o2){
        return (o1.getValue()).compareTo(o2.getValue());
      }
    });
      
    // put data from sorted list to hashmap
    HashMap<T, E> temp = new LinkedHashMap<T, E>();
    for (Map.Entry<T, E> aa : list) {
      temp.put(aa.getKey(), aa.getValue());
    }
    return temp;
  }
}