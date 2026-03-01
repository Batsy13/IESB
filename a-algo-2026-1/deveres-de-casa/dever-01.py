import time
import random

def insertion_sort(array):
  array_size = len(array)

  for i in range(1, array_size):
    j = i
    while array[j - 1] > array[j] and j > 0:
      array[j - 1], array[j] = array[j], array[j - 1]
      j -= 1

sizes = [1000, 5000, 10000, 20000, 50000]

print(f"{'n':<10} | {'Insertion Sort (s)':<20} | {'Timsort (s)':<20}")
print("-" * 55)

for n in sizes:
  data = [random.randint(0, 100000) for _ in range(n)]

  data_insertion = data.copy()
  start_insertion = time.time()
  insertion_sort(data_insertion)
  end_insertion = time.time()

  data_timsort = data.copy()
  start_timsort = time.time()
  data_timsort.sort()
  end_timsort = time.time()

  final_insertion = end_insertion - start_insertion
  final_timsort = end_timsort - start_timsort

  print(f"{n:<10} | {final_insertion:<20.5f} | {final_timsort:<20.5f}")
