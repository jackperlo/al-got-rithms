package unionfindset;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class UnionFindSet_TestsRunner {
  public static void main(String[] args) throws UnionFindSetException {
    Result result = JUnitCore.runClasses(UnionFindSetTests.class);
    for (Failure failure : result.getFailures()) {
      System.out.println(failure.toString());
    }
  
    System.out.println(result.wasSuccessful());
  }
  
}