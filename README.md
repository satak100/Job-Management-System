# Job-Management-System
This Job Management System is a console-based C++ application designed to facilitate job postings, applicant tracking, and company management. The system allows companies to post jobs, applicants to apply for them, and an admin to manage all records. It uses file handling to persist data across sessions and provides interactive menus for different user roles.

📌 Features
✅ Company Functionalities

Companies can log in using their Company ID and Company Name (used as a password).
Companies can add, edit, and delete jobs.
Companies can view all applicants who applied for a specific job.
Companies can update their company profile information.
✅ Applicant Functionalities

Applicants can log in using their Applicant ID and Applicant Name (used as a password).
Applicants can view all available jobs.
Applicants can apply for a job or cancel their application.
Applicants can view the list of jobs they applied for.
Applicants can update their personal information.
✅ Admin Functionalities

The admin can log in using the default credentials (username: admin, password: password).
The admin can add new companies and applicants.
The admin can view all registered companies and applicants.
✅ Persistent Data Storage

Uses text files (jobs.txt, companies.txt, applicants.txt) to store records.
Ensures data is retrieved automatically when the system starts.
✅ User-Friendly Console UI

Displays current time on the main menu.
Shows motivational quotes on startup.
Provides clear navigation and easy-to-follow prompts.
🛠️ Installation and Usage
1️⃣ Clone the Repository
bash
Copy
Edit
git clone https://github.com/yourusername/job-management-system.git
cd job-management-system
2️⃣ Compile the Code
bash
Copy
Edit
g++ -o job_management main.cpp
3️⃣ Run the Program
bash
Copy
Edit
./job_management   # For Linux/macOS
job_management.exe  # For Windows
🖼️ Screenshot
Below is an image of the first console page when running the program.


(Replace this with an actual screenshot after running the program.)

📜 File Structure
perl
Copy
Edit
📂 job-management-system
 ┣ 📜 main.cpp            # Main source code file
 ┣ 📜 jobs.txt            # Stores job data
 ┣ 📜 companies.txt       # Stores company data
 ┣ 📜 applicants.txt      # Stores applicant data
 ┣ 📜 README.md           # This file
 ┣ 📜 console_screenshot.png  # Screenshot of the first console page
📚 Technologies Used
C++
File Handling
OOP (Object-Oriented Programming)
ANSI Escape Codes (for colored text on terminal)
👥 Contributing
Want to improve this project? Follow these steps:

Fork the repository.
Create a new branch (git checkout -b feature-xyz).
Commit changes (git commit -m "Added new feature").
Push to GitHub (git push origin feature-xyz).
Submit a Pull Request 🎉.
📝 License
This project is licensed under the MIT License. Feel free to use and modify it.
