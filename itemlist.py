import csv
import random

# Create CSV file with 100 random items
with open('items.csv', mode='w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['ID', 'Value', 'Weight', 'ShelfLife'])  # Add Shelf Life header

    for i in range(1, 101):
        value = random.randint(1, 100)  # Value between 1 and 100
        weight = random.randint(1, 10)   # Weight between 1 and 10
        shelf_life = random.randint(1, 30)  # Shelf life between 1 and 30 days
        writer.writerow([i, value, weight, shelf_life])  # Write Shelf Life

print("CSV file 'items.csv' has been created with 100 items.")
