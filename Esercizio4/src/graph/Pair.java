package graph;

public class Pair<T, E> {
  private T key;
  private E value;

  public Pair(T key, E value){
    this.key = key;
    this.value = value;
  }
    
  public T getKey(){
    return this.key;
  }

  public E getValue(){
    return this.value;
  }

  public void delete(){
    this.key = null;
    this.value = null;
  }
}
