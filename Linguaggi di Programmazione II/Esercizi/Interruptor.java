public class Interruptor {
    public Interruptor(Thread t, int n) {
        new Thread() {
            @Override
            public void run() {
                try {
                    Thread.sleep(n*1000);
                } catch (InterruptedException e) {return;}
                t.interrupt();
            }
        }.start();
    }
}