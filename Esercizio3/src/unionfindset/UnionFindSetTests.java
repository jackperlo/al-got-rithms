package unionfindset;

import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Test;

public class UnionFindSetTests{
  
  @Test
  public void unionTwoArraysString() throws UnionFindSetException{
    String[] s1 = {"ciao", "a", "b"};
    String[] s2 = {"c", "d", "e"};
    UnionFindSet<String[]> e1 = new UnionFindSet<String[]>(s1);
    UnionFindSet<String[]> e2 = new UnionFindSet<String[]>(s2);
    e1.union(e2);
    assertTrue(e1.findSet() == e2.findSet());
  }

  @Test
  public void unionTwoEmptyCollectionString() throws UnionFindSetException{
    UnionFindSet<String> e1 = new UnionFindSet<String>("");
    UnionFindSet<String> e2 = new UnionFindSet<String>("");
    e1.union(e2);
    assertTrue(e1.findSet() == e2.findSet());
  }

  @Test
  public void unionTwoCollectionOneElementInteger() throws UnionFindSetException{
    UnionFindSet<Integer> e1 = new UnionFindSet<Integer>(1);
    UnionFindSet<Integer> e2 = new UnionFindSet<Integer>(2);
    e1.union(e2);
    assertTrue(e1.findSet() == e2.findSet());
  }

  @Test
  public void unionTwOCollectionOneElementString() throws UnionFindSetException{
    UnionFindSet<String> e1 = new UnionFindSet<String>("A");
    UnionFindSet<String> e2 = new UnionFindSet<String>("B");
    e1.union(e2);
    assertTrue(e1.findSet() == e2.findSet());
  }

  @Test
  public void unionTwoCollectionTwoElementsInteger() throws UnionFindSetException{
    UnionFindSet<Integer> e1 = new UnionFindSet<Integer>(1);
    UnionFindSet<Integer> e2 = new UnionFindSet<Integer>(2);
    e1.union(e2);

    UnionFindSet<Integer> e3 = new UnionFindSet<Integer>(3);
    UnionFindSet<Integer> e4 = new UnionFindSet<Integer>(4);
    e3.union(e4);

    e1.union(e3);
    assertTrue((e1.findSet() == e2.findSet()) && (e2.findSet() == e3.findSet()) && (e3.findSet() == e4.findSet()));
  }

  @Test
  public void unionTwoCollectionTwoElementsString() throws UnionFindSetException{
    UnionFindSet<String> e1 = new UnionFindSet<String>("A");
    UnionFindSet<String> e2 = new UnionFindSet<String>("B");
    e1.union(e2);

    UnionFindSet<String> e3 = new UnionFindSet<String>("C");
    UnionFindSet<String> e4 = new UnionFindSet<String>("D");
    e3.union(e4);

    e1.union(e3);
    
    assertTrue((e1.findSet() == e2.findSet()) && (e2.findSet() == e3.findSet()) && (e3.findSet() == e4.findSet()));
  }

  @Test
  public void unionTwoCollectionNmElementsString() throws UnionFindSetException{
    UnionFindSet<String> e1 = new UnionFindSet<String>("A");
    UnionFindSet<String> e2 = new UnionFindSet<String>("B");
    e1.union(e2);

    UnionFindSet<String> e3 = new UnionFindSet<String>("C");
    UnionFindSet<String> e4 = new UnionFindSet<String>("D");
    UnionFindSet<String> e5 = new UnionFindSet<String>("E");
    UnionFindSet<String> e6 = new UnionFindSet<String>("F");
    UnionFindSet<String> e7 = new UnionFindSet<String>("G");
    e3.union(e4);
    e4.union(e5);
    e5.union(e6);
    e6.union(e7);

    e1.union(e7);
    assertTrue((e1.findSet() == e2.findSet()) && (e2.findSet() == e3.findSet()) && (e3.findSet() == e4.findSet()) && (e4.findSet() == e5.findSet()) && (e5.findSet() == e6.findSet()) && (e6.findSet() == e7.findSet()));
  }

  @Test
  public void unionTwoCollectionNmElementsInteger() throws UnionFindSetException{
    UnionFindSet<Integer> e1 = new UnionFindSet<Integer>(1);
    UnionFindSet<Integer> e2 = new UnionFindSet<Integer>(2);
    e1.union(e2);

    UnionFindSet<Integer> e3 = new UnionFindSet<Integer>(3);
    UnionFindSet<Integer> e4 = new UnionFindSet<Integer>(4);
    UnionFindSet<Integer> e5 = new UnionFindSet<Integer>(5);
    UnionFindSet<Integer> e6 = new UnionFindSet<Integer>(6);
    UnionFindSet<Integer> e7 = new UnionFindSet<Integer>(7);
    e3.union(e4);
    e4.union(e5);
    e5.union(e6);
    e6.union(e7);

    e1.union(e7);
    assertTrue((e1.findSet() == e2.findSet()) && (e2.findSet() == e3.findSet()) && (e3.findSet() == e4.findSet()) && (e4.findSet() == e5.findSet()) && (e5.findSet() == e6.findSet()) && (e6.findSet() == e7.findSet()));
  }
}
