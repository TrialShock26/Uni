public static <T> Iterator<T> delayIterator(Iterator<T> i, int n) {
    return new Iterator<T>() {
        @Override
        public T next() {
            try {
                Thread.sleep(n*1000);
            } catch (InterruptedException e) {return null;}
            return i.next();
        }

        @Override
        public boolean hasNext() {return i.hasNext();}
    };
}