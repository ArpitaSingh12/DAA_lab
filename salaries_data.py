import csv
import random

# Parameters
num_employees = 2000
filename = 'salaries_data.csv'

# Generate random employee data
data = []
for _ in range(num_employees):
    basic_salary = round(random.uniform(30000, 120000), 2)  # Basic salary between 
    bonus = round(random.uniform(1000, 5000), 2)            
    tax_percentage = round(random.uniform(5, 20), 2)        # Tax percentage between 5% and 20%
    data.append([basic_salary, bonus, tax_percentage])

# Write data to CSV file
with open(filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['basicSalary', 'bonus', 'taxPercentage'])  # Optional header row
    writer.writerows(data)

print(f"CSV file '{filename}' created with {num_employees} employee records.")
