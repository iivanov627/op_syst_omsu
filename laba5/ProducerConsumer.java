import java.util.LinkedList;
import java.util.Queue;

public class ProducerConsumer {
    private static final int CAPACITY = 5;
    private static Queue<Integer> queue = new LinkedList<>();

    static class Producer extends Thread {
        public void run() {
            int value = 0;
            while (true) {
                synchronized (queue) {
                    while (queue.size() == CAPACITY) {
                        try {
                            queue.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    queue.add(value);
                    System.out.println("Produced: " + value);
                    value++;

                    queue.notify();
                }

                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {}
            }
        }
    }

    static class Consumer extends Thread {
        public void run() {
            while (true) {
                synchronized (queue) {
                    while (queue.isEmpty()) {
                        try {
                            queue.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    int value = queue.poll();
                    System.out.println("Consumed: " + value);

                    queue.notify();
                }

                try {
                    Thread.sleep(800);
                } catch (InterruptedException e) {}
            }
        }
    }

    public static void main(String[] args) {
        new Producer().start();
        new Consumer().start();
    }
}