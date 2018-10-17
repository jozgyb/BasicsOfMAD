public class Sheep {

    private String name;

    public void baa() {
        System.out.println(this.name + " is making a noise.");

    }

    private static Sheep instance = new Sheep();

    public static Sheep getInstance(String name) {
        instance.name = name;
        return instance;
    }

    private Sheep() {
        System.out.println("I'm the only sheep BAAAAAAA!");
    }
}
