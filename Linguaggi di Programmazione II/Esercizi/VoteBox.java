public class VoteBox {
    private Map<Thread, Boolean> elector = new HashMap<>();
    private int total;
    private boolean done = false;

    public VoteBox(int n) {
        total = n;
    }

    public synchronized void vote(boolean v) {
        if (done) throw new IllegalCallerException();
        if (elector.keySet().contains(Thread.currentThread())) throw new IllegalCallerException();
        elector.put(Thread.currentThread(), v);
        if (elector.size() == total) {
            done = true;
            this.notifyAll();
        }
    }

    public boolean waitForResult() {
        synchronized (this) {
            while (!done) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    return false;
                }
            }
        }
        int t = 0, f = 0;
        for (Boolean b : elector.values()) {
            if (b) t++;
            else f++;
        }
        if (f < t) return true;
        return false;
    }

    public boolean isDone() {
        return done;
    }
}