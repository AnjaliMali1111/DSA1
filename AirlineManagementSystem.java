import java.util.LinkedList;
import java.util.Queue;

class SharedBuffer {
    private final int capacity;
    private final Queue<Integer> buffer;

    public SharedBuffer(int capacity) {
        this.capacity = capacity;
        this.buffer = new LinkedList<>();
    }

    // Method for producer to add data to buffer
    public synchronized void produce(int item) throws InterruptedException {
        while (buffer.size() == capacity) {
            // Wait if buffer is full
            System.out.println("Buffer is full, Producer is waiting...");
            wait();
        }
        buffer.add(item);
        System.out.println("Produced: " + item);
        // Notify the consumer thread that an item is available
        notify();
    }

    // Method for consumer to consume data from buffer
    public synchronized int consume() throws InterruptedException {
        while (buffer.isEmpty()) {
            // Wait if buffer is empty
            System.out.println("Buffer is empty, Consumer is waiting...");
            wait();
        }
        int item = buffer.poll();
        System.out.println("Consumed: " + item);
        // Notify the producer thread that space is available in the buffer
        notify();
        return item;
    }
}

class Producer implements Runnable {
    private final SharedBuffer buffer;

    public Producer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        int item = 0;
        try {
            while (true) {
                buffer.produce(item++);
                // Simulating production time with sleep
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Consumer implements Runnable {
    private final SharedBuffer buffer;

    public Consumer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            while (true) {
                buffer.consume();
                // Simulating consumption time with sleep
                Thread.sleep(1500);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class ProducerConsumerExample {
    public static void main(String[] args) {
        SharedBuffer buffer = new SharedBuffer(5);  // Create a buffer with capacity of 5
        Thread producerThread = new Thread(new Producer(buffer));
        Thread consumerThread = new Thread(new Consumer(buffer));

        producerThread.start();  // Start the producer thread
        consumerThread.start();  // Start the consumer thread
    }
}
