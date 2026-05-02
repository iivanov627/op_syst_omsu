public class MultiThreadSum {
    private static final int ARRAY_SIZE = 1000;
    private static final int NUM_THREADS = 4;
    private static int[] array = new int[ARRAY_SIZE];

    static class SumThread extends Thread {
        private int start, end;
        private int partialSum;

        public SumThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public void run() {
            partialSum = 0;
            for (int i = start; i < end; i++) {
                partialSum += array[i];
            }
        }

        public int getPartialSum() {
            return partialSum;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = i + 1;
        }

        SumThread[] threads = new SumThread[NUM_THREADS];
        int blockSize = ARRAY_SIZE / NUM_THREADS;

        for (int i = 0; i < NUM_THREADS; i++) {
            int start = i * blockSize;
            int end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : start + blockSize;
            threads[i] = new SumThread(start, end);
            threads[i].start();
        }

        int totalSum = 0;

        for (int i = 0; i < NUM_THREADS; i++) {
            threads[i].join();
            totalSum += threads[i].getPartialSum();
        }

        System.out.println("Total sum: " + totalSum);
    }
}