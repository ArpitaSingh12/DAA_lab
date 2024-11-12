import csv
import random

# Function to generate a random 6-digit course code
def generate_course_code():
    return f"{random.randint(0, 999999):06d}"

# Create a list to hold student IDs and course codes
student_data = []

# Generate data for 100 students
for student_id in range(1, 101):
    course_code = generate_course_code()
    student_data.append((student_id, course_code))

# Write the data to a CSV file
with open('course_codes.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['StudentID', 'CourseCode'])  # Write the header
    writer.writerows(student_data)  # Write student data

print("CSV file 'course_codes.csv' created successfully with 100 random course codes.")
