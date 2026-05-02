public class CounterWithMutex {
    private static int counter = 0;

    public static synchronized void increment() {
        counter++;
    }

    static class IncrementThread extends Thread {
        public void run() {
            for (int i = 0; i < 1000; i++) {
                increment();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int numThreads = 4;
        Thread[] threads = new Thread[numThreads];

        for (int i = 0; i < numThreads; i++) {
            threads[i] = new IncrementThread();
            threads[i].start();
        }

        for (int i = 0; i < numThreads; i++) {
            threads[i].join();
        }

        System.out.println("Final counter: " + counter);
    }
}