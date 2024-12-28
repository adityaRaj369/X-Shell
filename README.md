<p align="center">
  <h1 align="center">X/Shell</h1>
</p>
<p align="center">
  <img src="https://github.com/user-attachments/assets/700f55a0-ecb1-43b8-9b21-f5ba67bb8416" alt="X/Shell Logo" width="300"/>
</p>
# **X/Shell: Kernel-Level Shell Interaction for Linux**
**XShell** is a lightweight, kernel-level Linux shell application designed to interact directly with the operating system’s kernel, bypassing traditional shells like Bash. It features a GUI built using GTK, offering an intuitive interface for performing system-level operations. This project demonstrates expertise in system programming, Linux kernel interaction, and advanced GUI development.

---

## **Key Technologies**

- **C Programming**: Core development in C, showcasing system-level programming skills, memory management, and efficient file I/O handling.
- **Linux Kernel Interaction**: Uses direct system calls (`execve`, `fork`, etc.) to interact with the kernel, bypassing intermediary shells.
- **GTK 3**: Modern GUI creation using GTK, enabling cross-platform graphical interfaces.
- **Command History**: Tracks previously executed commands with optimized data structures, highlighting algorithm design expertise.
- **Real-Time Output Rendering**: Non-blocking, real-time display of command output in the GUI, demonstrating multithreading and asynchronous programming.

---

## **Features**

### **1. Direct Kernel Interaction**
Performs core tasks like file manipulation, directory management, and process control by directly communicating with the Linux kernel.

### **2. Intuitive GUI**
- Built with GTK3 for a modern, user-friendly interface.
- Commands and outputs are displayed in an interactive terminal-like environment.

### **3. Command Set**
Implements essential system operations:
- `listmyDir`: List files in the current directory.
- `getInto <directory>`: Navigate to a specific directory.
- `createFile <file_name>`: Create a new file.
- `removeFile <file_name>`: Delete a file.
- `makeDir <directory_name>`: Create a new directory.
- `removeDir <directory_name>`: Remove an existing directory.
- `countFiles`: Count files in the current directory.
- `displayPwd`: Show the current working directory.
- `displayTime`: Display the current system time.
- `history`: View the last 100 executed commands.

### **4. Modular Architecture**
Encapsulates functionality in separate modules for scalability and maintainability.

### **5. Real-Time Output**
Displays command execution results instantly using non-blocking processes.

---

## **Skills Demonstrated**

- **Low-Level System Programming**: Mastery of system calls, process management, and memory handling.
- **Cross-Platform GUI Development**: Advanced GUI design with GTK for seamless user interaction.
- **Linux Fundamentals**: Extensive understanding of Linux internals and core system operations.
- **C Programming Expertise**: Proficient use of pointers, data structures, and efficient algorithms.
- **Multithreading & Asynchronous Execution**: Implements non-blocking designs for enhanced responsiveness.

---

## **Installation**

### **Prerequisites**
- Install GTK+3 development libraries:
  ```bash
  sudo apt-get install libgtk-3-dev

### **Steps**
## **Clone the Repository**
- Run the following commands to clone the repository and navigate to the project directory:
  ```bash
  git clone https://github.com/yourusername/X-Shell.git
  cd XShell

### **Compile the Application**
- Use the following command to compile the application:
  ```bash
  gcc -o xshell xshell.c `pkg-config --cflags --libs gtk+-3.0`


### **Run the Application**
- Launch the application with:
  ```bash
  ./xshell

  
- Example Usage
    ```bash

    - List Files in the Current Directory
      listmyDir

    - Navigate to a Directory
      getInto <directory_name>

    - Create a New File
      createFile example.txt
    
    - Remove a File
      removeFile example.txt
    
    - Create a New Directory
      makeDir <directory_name>
    
    - Remove a Directory
      removeDir <directory_name>
  
    - Count Files in the Current Directory
      countFiles
    
    - Display Current Working Directory
      displayPwd
    
    - Display Current System Time
      displayTime


## **Project Architecture**
Command Execution Engine: The heart of the application, responsible for parsing user commands and issuing corresponding system calls. It also manages error handling and the execution flow between different shell commands.
Modular Components: The project is structured in a modular fashion to allow scalability. Each component (file operations, process control, etc.) has been encapsulated into separate modules for ease of maintenance and potential future extensions.
GUI Interface: Designed to be lightweight yet feature-rich, allowing users to interact with the Linux kernel through an intuitive graphical interface. It supports real-time command output rendering, making the user experience seamless.
Screenshots
(Include screenshots of the GUI with command input/output examples. Here, you can add images of the interactive terminal-like interface with different commands executed, showing the results in real-time.)


## **Contributing**
This project is open for enhancements and feature additions. To contribute:

## **Conclusion**

XShell is a powerful demonstration of advanced system-level programming and GUI development. By combining low-level system programming with high-level graphical design, it showcases your ability to interact with Linux kernel internals, perform essential system operations, and create a modern, user-friendly interface.

This project not only demonstrates proficiency in C programming, system calls, and Linux but also illustrates the use of multithreading for real-time command output rendering and advanced GUI development with GTK3. XShell is an excellent showcase for roles in system programming, embedded development, or Linux-based software engineering.


## **Future Work**

XShell is a work in progress and offers several opportunities for further enhancement, such as:

Adding support for more advanced system operations (e.g., network management, user management).
Extending the GUI to allow customization of commands and aliases.
Improving error handling and adding logs for system diagnostics.
Enhancing the real-time output rendering with visual progress indicators.
Supporting multiple shells or integrating other system tools.
