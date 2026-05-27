public static void executeInParallel(Runnable[] r, int k) {
    if (k < 1) throw new IllegalArgumentException();
    if (r.length < k) k = r.length;

    int count = 0;
    Object cond = new Object();
    for (int i = 0; i < r.length; i++) {
        final int j = i;
        synchronized (cond) {
            while (count == k) {
                try {
                    cond.wait();
                    count--;
                } catch (InterruptedException e) {return;}
            }
            count++;
            new Thread() {
                @Override
                public void run() {
                    r[j].run();
                    synchronized (cond) {
                        cond.notifyAll();
                    }
                }
            }.start();
        }
    }
}

public static void executeInParallelCorrect(Runnable[] runnables, int k) {
    BlockingQueue<Thread> queue = new ArrayBlockingQueue<>(k);

    for (Runnable r : runnables) {
        Thread t = new Thread() {
            @Override
            public void run() {
                r.run();
                queue.remove(this);
            }
        };
        try {
            queue.put(t);
            t.start();
        } catch (InterruptedException e) {return;}
    }
}