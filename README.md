<svg clip-rule="evenodd" fill-rule="evenodd" stroke-linejoin="round" stroke-miterlimit="1.414" viewBox="0 0 24 24" xml:space="preserve" xmlns="http://www.w3.org/2000/svg"><path d="M19 20H4a2 2 0 0 1-2-2V6c0-1.11.89-2 2-2h6l2 2h7c1.097 0 2 .903 2 2H4v10l2.14-8h17.07l-2.28 8.5c-.23.87-1.01 1.5-1.93 1.5z" fill="#0277bd"/><path d="m16.275 21.115-2.538.002V17.31l-1.903 2.441-1.903-2.441v3.807H7.393v-7.613h2.538l1.903 2.538 1.903-2.538 2.538-.003zm3.789.634L16.91 17.31h1.903v-3.806h2.538v3.806h1.903z" fill="#b3e5fc"/></svg>
<p align="center"><h1 align="center">X/Shell</h1></p>


# **X/Shell: Kernel-Level Shell Interaction for Linux**
**XShell** is a lightweight, kernel-level Linux shell application designed to interact directly with the operating system’s kernel, bypassing traditional shells like Bash. It features a GUI built using GTK, offering an intuitive interface for performing system-level operations. This project demonstrates expertise in system programming, Linux kernel interaction, and advanced GUI development.

---

## **Key Technologies**
![folder-markdown-open](https://github.com/user-attachments/assets/d1d30b4d-5c92-49de-809b-4f647e8952ac)

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
