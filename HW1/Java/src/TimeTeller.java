public interface TimeTeller {
    default void tellTime()  {
        System.out.println("What time Zone are you in ?");
    };
}
