public class RunOnSet<T> extends Thread {
    private RunnableWithArg<T> ru;
    private Collection<? extends T> col;

    public RunOnSet(RunnableWithArg<T> r, Collection<? extends T> c) {
        ru = r;
        col = c;
    }

    @Override
    public void run() {
        for (T t : c) {
            new Thread() {
                @Override
                public void run() {
                    r.run(t);
                }
            }.start();
        }
    }
}