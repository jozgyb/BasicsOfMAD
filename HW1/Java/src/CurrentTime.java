public interface CurrentTime extends TimeTeller {
    default void tellTime() {
        System.out.println("I honestly don't know.");
    }
}
