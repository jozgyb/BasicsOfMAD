public class Main {

    public static void main(String[] args) {

        Sheep clarence = Sheep.getInstance("Clarence");
        clarence.baa();

        Sheep joseph = Sheep.getInstance("Joseph");
        joseph.baa();

        System.out.println("In reality are Clarence and Joseph the same sheep ?");
        if(clarence.hashCode() == joseph.hashCode()) {
            System.out.println("Yes they are!");
        } else { // ;)
            System.out.println("No they aren't!");
        }
    }
}
