### Overview:
The School Management System is a console-based application designed to manage records for students, faculty, fees, and sections in a school. The program is implemented in C and provides a modular structure for handling different operations.

### Student Management:

1.Add new student records.
2.Delete existing student records.
3.Update student details.
4.Display all student records.
5.Sort students by ID or name.
6.Count the total number of students.
7.Search for a student by ID.

### Faculty Management:

1.Add new faculty records.
2.Delete existing faculty records.
3.Update faculty details.
4.Display all faculty records.
5.Sort faculty by ID or name.
6.Count the total number of faculty.
7.Search for a faculty member by ID.

### Fees Management:

1.Add fee payment records for students.
2.Display all fee payment records.
  
Section Management:

1.Assign sections to students.
2.Display all sections.

### File Operations:

student.h: Header file for student-related functions and data structures.
faculty.h: Header file for faculty-related functions and data structures.
fees.h: Header file for fee management.
section.h: Header file for section management.
fileoperation.h: Handles file input/output for persisting data.

Student data: StudentRecords.txt
Faculty data:FacultyRecords.txt 
Fees data: fees.txt
Section data: sections.txt

## Data Structures:
Uses linked lists for managing records dynamically.  

## Setup Instructions
Prerequisites:

compiler: GCC.
Basic knowledge of compiling and running C programs.

## File Structure:

main.c: Contains the main program logic.
fileoperation.h: Handles file I/O operations for loading and saving data.
admin.h: Includes admin login and related operations.
student.h: Handles student-related functions.
faculty.h: Handles faculty-related functions.
fees.h: Handles fees-related functions.
section.h: Handles section-related functions.
Compilation: Compile the program using a command like:

Copy code
gcc main.c -o SchoolManagementSystem
Running the Program: Run the compiled program:

## How to Use

Login as Admin:

Upon starting, the program prompts for admin login credentials.
Default credentials should be set in the admin.h file.
Main Menu:

Select the desired operation by entering the corresponding number.
Choices:
Student Operations
Faculty Operations
Fees Operations
Section Operations
Close files and exit.
Navigating Submenus:

Each operation opens a submenu for further actions.
Enter the number corresponding to the action you want to perform.
Exiting:

To exit a submenu, select the Exit option within that submenu.
To exit the program, choose option 5 (Save and Exit) in the main menu.
File Details
school.txt:

Stores all the program's data persistently.
Data is updated whenever changes are made, and saved upon exiting the program.
Header Files:

Each header file contains specific logic for one of the subsystems (e.g., students, faculty).
Error Handling
Ensure all inputs are valid to avoid unexpected errors.
If invalid input is entered, the program will display an appropriate error message and prompt the user to try again.
Future Enhancements
Implement authentication for different user roles (e.g., student, faculty).
Add search functionality for quick retrieval of records.


Project developed by: https://github.com/PallaviT2001











# School_management_system_project
