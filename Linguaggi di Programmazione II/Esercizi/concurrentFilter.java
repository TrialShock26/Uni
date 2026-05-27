public static <T> Set<T> concurrentFilter(Set<? extends T> x, Predicate<? super T> p) {
    Set<T> ans = new HashSet<>();
    List<Thread> workers = new ArrayList<>();
    for (T val : x) {
        Thread t = new Thread() {
            @Override
            public void run() {
                synchronized (ans) {
                    if (p.test(val)) ans.add(val);
                }
            }
        };
        workers.add(t);
        t.start();
    }
    for (Thread w : workers) {
        try {
            w.join();
        } catch (InterruptedException e) {return null;}
    }
    return ans;
}