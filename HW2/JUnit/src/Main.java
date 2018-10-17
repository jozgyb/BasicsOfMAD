import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class Main {

    public static void main(String[] args) {
        Result testresult = JUnitCore.runClasses(NumberTest.class);

        for (Failure failure : testresult.getFailures()) {
            System.out.println(failure.toString());
        }

        System.out.println(testresult.wasSuccessful());
    }
    }
}
