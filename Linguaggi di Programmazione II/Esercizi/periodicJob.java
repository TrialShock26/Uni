public static void periodicJob(Runnable r, long p) {
    new Thread() {
        @Override
        public void run() {
            while(true) {
                new Thread(r).start();
                try {
                    Thread.sleep(p);
                } catch (InterruptedException e) {return;}
            }
        }
    }.start();
}