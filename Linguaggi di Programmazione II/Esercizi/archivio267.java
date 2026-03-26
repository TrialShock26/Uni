public class B<T> extends ArrayList<Integer> {
    public B() {}

    public B (Object o) {}

    public static <U> String buildMessage(U u) {return null;}

    public boolean check (Set<Integer> set, Integer n) {return true;}

    public Set<? super Number> process (Set<?> setA, Set<?> setB, Integer n) {return null;}
}