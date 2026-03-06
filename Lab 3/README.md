# Lab 3: Parallel Order Processing

Processing food delivery orders one by one is _so_ last century. This lab simulates a high-demand delivery platform by using **forking** to process batches of orders in parallel.

---

## 🚀 The Mission

You need to write a C program that acts as a platform manager (parent process) which spawns N dispatchers (child processes) to calculate free-delivery eligibility across a batch of orders.

### Dispatcher Logic

Each dispatcher is responsible for a specific batch of orders and must:

- **Calculate Total Price**: Multiply the number of items by the price per item.

- **Determine Eligibility**: If the total price is ≥V (minimum order value), the order qualifies for free delivery.
    
- **Report Results**: Count the eligible orders in their batch and send that count back to the parent.
    

---

## 📊 Batch Assignment

Orders (M) are distributed among dispatchers (N) as follows:

- The first N−1 dispatchers receive ⌊M/N⌋ orders.
    
- The N-th (last) dispatcher handles all remaining "overflow" orders.
    

---

## 🛠️ Usage & Execution

The program must accept exactly three command-line arguments:

1. **File Path**: Path to the `orders.txt` file.
    
2. **N**: The number of dispatchers (N>0).
    
3. **V**: The minimum order value for free delivery (V>0).
    

### Compilation

Bash

```
gcc firstName_secondName_ID.c -o orderProcessor.o
./orderProcessor.o "orders.txt" 3 50
```

The output must be a single line containing N space-separated integers representing the counts from each dispatcher.

---

## ⚠️ Vital Constraints

- **No Assumptions**: Do not assume children PIDs are sequential or greater than the parent PID.
    
    
- **No Standard Input**: Use command-line arguments only; `scanf` or `gets` will cause a timeout.
    
- **Communication**: You must decide how the parent and children will communicate (e.g., pipes or exit codes).
    
- **Clean Code**: Comment out all debug `printf` statements before submission.
