# **Job Management System** 🎯  

This **Job Management System** is a console-based **C++ application** designed to facilitate job postings, applicant tracking, and company management. The system allows **companies to post jobs**, **applicants to apply for them**, and **an admin to manage all records**. It uses **file handling** to persist data across sessions and provides **interactive menus** for different user roles.  

---

## **📌 Features**  

### ✅ **Company Functionalities**  
- Companies can log in using their **Company ID** and **Company Name** (used as a password).  
- Companies can **add, edit, and delete jobs**.  
- Companies can **view all applicants** who applied for a specific job.  
- Companies can update their **company profile information**.  

### ✅ **Applicant Functionalities**  
- Applicants can log in using their **Applicant ID** and **Applicant Name** (used as a password).  
- Applicants can **view all available jobs**.  
- Applicants can **apply for a job or cancel their application**.  
- Applicants can **view the list of jobs they applied for**.  
- Applicants can **update their personal information**.  

### ✅ **Admin Functionalities**  
- The admin can log in using the **default credentials (username: admin, password: password)**.  
- The admin can **add new companies and applicants**.  
- The admin can **view all registered companies and applicants**.  

### ✅ **Persistent Data Storage**  
- Uses **text files (`jobs.txt`, `companies.txt`, `applicants.txt`)** to store records.  
- Ensures data is **retrieved automatically** when the system starts.  

### ✅ **User-Friendly Console UI**  
- Displays **current time** on the main menu.  
- Shows **motivational quotes** on startup.  
- Provides **clear navigation** and easy-to-follow prompts.  

---

## **🛠️ Installation and Usage**  

### **1️⃣ Clone the Repository**  
```bash
git clone https://github.com/yourusername/job-management-system.git
cd job-management-system
```

### **2️⃣ Compile the Code**  
```bash
g++ -o job_management JobManagement.cpp
```

### **3️⃣ Run the Program**  
```bash
./job_management   # For Linux/macOS
job_management.exe  # For Windows
```

---

## **🖼️ Screenshot**  

Below is an image of the **first console page** when running the program.  

![Job Management System Console Screenshot](console_output.png)  

_(Make sure `console_output.png` exists in the repository for proper display.)_  

---

## **📜 File Structure**  
```
📂 job-management-system
 ┣ 📜 JobManagement.cpp      # Main source code file
 ┣ 📜 README.md              # This file
 ┣ 📜 applicants.txt         # Stores applicant data
 ┣ 📜 companies.txt          # Stores company data
 ┣ 📜 console_output.png     # Screenshot of the first console page
 ┣ 📜 jobs.txt               # Stores job data
```

---

## **📚 Technologies Used**  
- **C++**
- **File Handling**
- **OOP (Object-Oriented Programming)**
- **ANSI Escape Codes (for colored text on terminal)**  

---

## **👥 Contributing**  
Want to improve this project? Follow these steps:  
1. **Fork** the repository.  
2. **Create** a new branch (`git checkout -b feature-xyz`).  
3. **Commit** changes (`git commit -m "Added new feature"`).  
4. **Push** to GitHub (`git push origin feature-xyz`).  
5. **Submit a Pull Request** 🎉.  

---

## **📝 License**  
This project is licensed under the **MIT License**. Feel free to use and modify it.  

---
