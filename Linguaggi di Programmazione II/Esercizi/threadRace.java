public static int threadRaceV1(Runnable r1, Runnable r2) {
    AtomicInteger winner = new AtomicInteger();

    Thread t1 = new Thread() {
        @Override
        public void run() {
            r1.run();
            synchronized (winner) {
                if (winner.get() == 0) {
                    winner.setPlain(1);
                }
            }
        }
    };
    Thread t2 = new Thread() {
        @Override
        public void run() {
            r2.run();
            synchronized (winner) {
                if (winner.get() == 0) {
                    winner.setPlain(2);
                }
            }
        }
    };

    t1.start();
    t2.start();

    try {
        t1.join();
        t2.join();
    } catch (InterruptedException e) {return 0;}
    return winner.get();
}

public static int threadRaceV2(Runnable r1, Runnable r2) {
    AtomicInteger winner = new AtomicInteger();
    
    new Thread() {
        @Override
        public void run() {
            r1.run();
            synchronized (winner) {
                if (winner.get() == 0) {
                    winner.setPlain(1);
                    winner.notifyAll();
                }
            }
        }
    }.start();
    new Thread() {
        @Override
        public void run() {
            r2.run();
            synchronized (winner) {
                if (winner.get() == 0) {
                    winner.setPlain(2);
                    winner.notifyAll();
                }
            }
        }
    }.start();

    synchronized (winner) {
        while (winner.get() == 0) {
            try {
                winner.wait();
            } catch (InterruptedException e) {return 0;}
        }
        return winner.get();
    }
}