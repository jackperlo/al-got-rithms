package unionfindset;

/**
 * @param <T> collection's element type
 */
public class UnionFindSet<T>{
  private UnionFindSet<T> p = null;
  private T value;
  private int rank;
  
  /**
   * <p>It override the default constructor.
   * It creates a one element collection of type &lt T &gt.
   * It accepts as a parmeter the value of the only element contined in the UnionFindSet collection just initialized</p>
   * <p><b>Example</b></p>
   * <p>{@code UnionFindSet<Integer> x = new UnionFindSet<Integer>(0);}</p>
   * 
   * @param value value of the T element which will be inserted in the UnionFindSet collection
   */
  public UnionFindSet(T value){
    makeSet(value);
  }

  /**
   * <p>It creates a one element collection of type &lt T &gt.</p><p>It accepts as a
   * parameter the value of the only one element which will be inserted in the
   * UnionFindSet collection just initialized.</p><p> It sets the father's pointer
   * pointing itself because this collection contains just one element. The rank
   * of the collection is set to 0 because it contains just one element.</p>
   * 
   * <p><b>Example</b></p>
   * <p>{@code UnionFindSet<Integer> x;}</p>
   * <p>{@code x.makeSet(1);}</p>
   * 
   * @param value value of the &lt T &gt element which will be inserted in the
   *              UnionFindSet collection
   */
  public void makeSet(T value){
    this.p = this;
    this.value = value;
    this.rank = 0;
  }

  /**
   * <p>
   * It calls itself recursively while the considered element is not the
   * representative of its collection.
   * </p>
   * <p>
   * <b>Example</b>
   * </p>
   * <p>
   * {@code UnionFindSet<Integer> x = new unionFindSet<Integer>(1);}</p><p>
   * {@code x.findSet();} returns himself, because he is the representative element
   * </p>
   * 
   * @return {@code UnionFindSet<T>} It returns the collections's representative on which is called
   */
  public UnionFindSet<T> findSet() {
    if(this != this.p){
      this.p = this.p.findSet();
    }

    return this.p;
  }

  /** 
   * <p>It links two collections passed as parameters creating implicity a new collection (results of the linkning).</p> 
   * <p>The lower rank representative element will be linked to 
   * the higher rank representative element. This solution is adopted in order to allows 
   * the new collection's rank not to grow (or in the worst case: when the two linked collections have the
   * same rank, to grow the less as possible). </p>
   * <p>It checks the user is not trying to merge two elements which already belong to the same collection</p>
   * 
   * @param x pointer to the X collection's representative element
   * @param y pointer to the Y collection's representative element
  */
  private void link(UnionFindSet<T> x, UnionFindSet<T> y){
    if(x.p != y.p){
      if(x.rank >= y.rank){
        y.p = x;
        if(x.rank == y.rank)
          x.rank = x.rank + 1;
      }else{
        x.p = y;
      }
    } 
  }

  /**
   * <p>It merge two collections
   * It accepts as a parameter an element of a collection which will be merged with the collection to which
   * the element (which has called this method) belongs. </p>
   * 
   * <p><b>Example</b></p>
   * <p>{@code UnionFindSet<Integer> a = new UnionFindSet<Integer>(0);}</p>
   * <p>{@code UnionFindSet<Integer> b = new UnionFindSet<Integer>(1);}</p>
   * <p>{@code a.union(b);} is the same as doing {@code b.union(a);}</p>
   * 
   * @param y an element belonging the collection to merge with
   * @throws UnionFindSetException is throwed if (this.p is null) or (y is null) or we're trying to merge to different collection types
   */
  public void union(UnionFindSet<T> y) throws UnionFindSetException{
    if(this.p == null)
      throw new UnionFindSetException("union(unionfindset.UnionFindSet) element not initilized.");

    if(y == null)
      throw new UnionFindSetException("union(unionfindset.UnionFindSet) input parameter can't be NULL.");

    if(this.value.getClass() != y.value.getClass())
      throw new UnionFindSetException("union(unionfindset.UnionFindSet) trying to merge two different types.");

    this.link(this.findSet(), y.findSet());
  }

  /**
   * <p>It returns the value of the element on which is called<p>
   * <p><b>Example</b></p>
   * <p>{@code UnionFindSet<Integer> x = new UnionFindSet<Integer>(0);}</p>
   * <p>{@code x.getValue();}</p>
   * 
   * @return &lt T &gt value of the element
   */
  public T getValue(){
    return this.value;
  }
  
  /**
   * It modifies the value of the element on which is called
   * <p><b>Example</b></p><p>
   * {@code UnionFindSet<Integer> x = new UnionFindSet<Integer>(0);}<br>
   * {@code x.setValue(1);}
   * </p>
   * 
   * @param value value of the &lt T &gt element which will be modified in the
   *              element value
   */
  public void setValue(T value){
    this.value = value;
  }
}