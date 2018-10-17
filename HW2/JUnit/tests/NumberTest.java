import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;
class NumberTest {

    @Test
    public void multiplicationOfZeroIntegersShouldReturnZero() {
        Number tester = new Number();

        // assert statements
        assertEquals(0, tester.multiply(15, 0), "15 * 0 must be 0");
        assertEquals(0, tester.multiply(0, 25), "0 * 25 must be 0");
        assertEquals(0, tester.multiply(0, 0), "0 * 0 must be 0");
    }

    public void negativeNumbersShouldReturnTrue() {
        Number tester = new Number();
        assertEquals(true, tester.isNegative(-2), "-2 must return true");
        assertEquals(true, tester.isNegative(25), "25 must return false");

    }

}