#include <stdio.h>  // Include the standard input/output library for I/O functions like printf
#include <stdlib.h> // Include the standard library for general purpose functions (like malloc, free)
#include <string.h> // Include string handling functions like strcpy, strlen, and strtok
#include <unistd.h> // Include POSIX functions, particularly for system calls like fork, getcwd
#include <sys/types.h> // Include definitions for types used in system calls (e.g., pid_t)
#include <sys/stat.h> // Include definitions for file status and attributes (e.g., mkdir)
#include <fcntl.h>  // Include file control definitions (e.g., open, O_RDONLY)
#include <dirent.h> // Include directory handling functions (e.g., opendir, readdir, closedir)
#include <errno.h> // Include the error handling library to capture error codes
#include <time.h> // Include time handling functions (e.g., time, strftime)
#include <sys/syscall.h> // Include system call numbers for platform-specific functionality
#include <gtk/gtk.h> // Include GTK library for creating the graphical user interface (GUI)
#include <stdarg.h> // Include for handling variable argument lists (e.g., for formatted output)
#include <sys/wait.h> // Include for handling wait and process termination

// Define constants for the maximum path length and maximum number of commands in history
#define MAX_PATH_LEN 1024 // Maximum length of file paths
#define MAX_HISTORY 100   // Maximum number of commands to store in history

// Declare a global history array to store the last commands
char *command_history[MAX_HISTORY]; // Array to store command history
int history_count = 0;              // Counter to keep track of the number of commands in history

// Function prototypes for various commands that will be implemented
void list_my_dir(const char *path);
void execute_command(const char *command);
void get_into(const char *path);
void create_file(const char *file_name);
void remove_file(const char *file_name);
void display_pwd();
void make_directory(const char *dir_name);
void remove_directory(const char *dir_name);
void count_files(const char *path);
void display_current_time();
void display_history();
void save_command_to_history(const char *command);
void get_out(const char *dir_name);
void update_prompt(char *prompt, size_t size);
void append_to_output(const char *fmt, ...);
void on_entry_activate(GtkEntry *entry, gpointer user_data);

// Declare global variables for GTK UI components
GtkWidget *window; // GTK window to hold all UI components
GtkWidget *output_text_view; // Text view widget to display output
GtkWidget *entry; // Entry widget for user to input commands
GtkTextBuffer *text_buffer; // Buffer to hold and manipulate text in the output text view

// Main function to initialize the GTK application and set up the window
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Initialize GTK library

    // Create a new window widget with the type of top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Custom Shell GUI"); // Set the title of the window
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400); // Set the default size of the window (600x400)
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Set up the signal to close the window

    // Create a vertical box to contain the widgets (arrange them vertically)
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox); // Add the vbox to the window

    // Create a text view widget to display output (non-editable)
    output_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_text_view), FALSE); // Make the text view non-editable
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text_view)); // Get the text buffer for output manipulation

    // Create a scrollable window to wrap the text view widget (makes it scrollable if the content is too large)
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), output_text_view); // Add the text view to the scrolled window
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0); // Pack the scrolled window into the vertical box

    // Create an entry widget where users can type commands
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0); // Pack the entry widget into the vbox

    // Connect the entry widget to a function that will handle when the user presses enter
    g_signal_connect(entry, "activate", G_CALLBACK(on_entry_activate), NULL);

    // Display all the widgets in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop (wait for user events)
    gtk_main();

    return 0; // Return from the main function
}

// This function is called when the user presses Enter in the entry widget
void on_entry_activate(GtkEntry *entry, gpointer user_data) {
    const char *input = gtk_entry_get_text(entry); // Get the text input from the entry widget
    char prompt[256]; // Buffer to hold the prompt (current working directory)
    update_prompt(prompt, sizeof(prompt)); // Update the prompt with the current directory

    if (strlen(input) == 0) return; // If the input is empty, do nothing and return

    save_command_to_history(input); // Save the entered command to the history

    // Append the entered command to the output text view with a prompt (shell-like behavior)
    append_to_output("customShell> %s\n", input);

    // Determine which function to call based on the command entered
    if (strncmp(input, "listmyDir", 9) == 0) {
        list_my_dir("."); // List the files in the current directory
    } else if (strncmp(input, "getInto", 7) == 0) {
        get_into(input + 8); // Change directory (input path follows the "getInto" command)
    } else if (strncmp(input, "createFile", 10) == 0) {
        create_file(input + 11); // Create a new file (file name follows the "createFile" command)
    } else if (strncmp(input, "removeFile", 10) == 0) {
        remove_file(input + 11); // Remove a file (file name follows the "removeFile" command)
    } else if (strncmp(input, "displayPwd", 10) == 0) {
        display_pwd(); // Display the current working directory (pwd)
    } else if (strncmp(input, "makeDir", 7) == 0) {
        make_directory(input + 8); // Make a new directory (directory name follows the "makeDir" command)
    } else if (strncmp(input, "removeDir", 9) == 0) {
        remove_directory(input + 10); // Remove a directory (directory name follows the "removeDir" command)
    } else if (strncmp(input, "countFiles", 10) == 0) {
        count_files(input + 11); // Count files in a given directory (directory follows the "countFiles" command)
    } else if (strncmp(input, "displayTime", 11) == 0) {
        display_current_time(); // Display the current system time
    } else if (strncmp(input, "history", 7) == 0) {
        display_history(); // Display the command history
    } else if (strncmp(input, "getOut", 6) == 0) {
        get_out(input + 7); // Go back to the previous directory (input path follows the "getOut" command)
    } else if (strncmp(input, "installFile", 11) == 0) {
        // Handle installation of a file with sudo privileges
        const char *file_path = input + 12; // Extract the file path after the "installFile" command
        char *args[] = {"/usr/bin/sudo", "/usr/bin/install", (char *)file_path, "/usr/local/bin/", NULL};

        pid_t pid = fork(); // Fork the process to create a new child process
        if (pid < 0) {
            append_to_output("Fork failed\n"); // If fork fails, show an error message
            return;
        }
        if (pid == 0) { // If in the child process
            if (execve(args[0], args, environ) == -1) { // Execute the install command with sudo
                append_to_output("Install command execution failed: %s\n", strerror(errno)); // Handle exec failure
                exit(EXIT_FAILURE); // Exit if the command fails
            }
        } else { // If in the parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to finish
            if (WIFEXITED(status)) {
                append_to_output("Installation command finished with exit code %d\n", WEXITSTATUS(status));
            } else {
                append_to_output("Installation command terminated abnormally\n");
            }
        }
    } else {
        execute_command(input); // If the input doesn't match any predefined commands, execute it as a system command
    }

    gtk_entry_set_text(entry, ""); // Clear the input entry field after execution
}

// Function to append output to the text view (show the result of a command)
void append_to_output(const char *fmt, ...) {
    va_list args; // Define a variable argument list
    va_start(args, fmt); // Initialize the argument list to start after the format string
    gchar *text = g_strdup_vprintf(fmt, args); // Format the string using the arguments
    va_end(args); // End the argument list processing

    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(text_buffer, &end_iter); // Get the iterator pointing to the end of the text buffer

    // If the text starts with the shell prompt "customShell>", color it green for better readability
    if (g_str_has_prefix(text, "customShell>")) {
        gchar *colored_text = g_strdup_printf("<span foreground='lightgreen'>%s</span>", text); // Format text with color
        gtk_text_buffer_insert_markup(text_buffer, &end_iter, colored_text, -1); // Insert colored text into the buffer
        g_free(colored_text); // Free the formatted text
    } else {
        gtk_text_buffer_insert(text_buffer, &end_iter, text, -1); // Insert the regular text into the buffer
    }

    g_free(text); // Free the memory allocated for the formatted text
}

// Function to list files in a directory (used with the "listmyDir" command)
void list_my_dir(const char *path) {
    DIR *dir = opendir(path); // Open the directory at the given path
    if (!dir) {
        append_to_output("Error opening directory: %s\n", strerror(errno)); // Show error message if the directory can't be opened
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) { // Loop through each entry in the directory
        // Skip the special entries "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            append_to_output("%s\n", entry->d_name); // Print the name of each directory entry
        }
    }
    closedir(dir); // Close the directory after processing
}

// Function to execute a system command by forking a child process and calling exec
void execute_command(const char *command) {
    pid_t pid = fork(); // Fork a new process
    if (pid < 0) {
        append_to_output("Fork failed\n"); // If fork fails, print an error
        return;
    }
    if (pid == 0) { // In the child process
        execlp(command, command, (char *)NULL); // Execute the command using execlp
        append_to_output("Command execution failed: %s\n", strerror(errno)); // Print an error if exec fails
        exit(EXIT_FAILURE); // Exit if command execution fails
    } else { // In the parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            append_to_output("Command finished with exit code %d\n", WEXITSTATUS(status)); // Print exit code of the command
        } else {
            append_to_output("Command terminated abnormally\n"); // Print error if the command fails
        }
    }
}

// Function to change the current working directory (used with the "getInto" command)
void get_into(const char *path) {
    if (chdir(path) == -1) { // Attempt to change the directory
        append_to_output("Error changing directory: %s\n", strerror(errno)); // If it fails, print an error
    } else {
        display_pwd(); // Display the new current working directory
    }
}

// Function to create a new file (used with the "createFile" command)
void create_file(const char *file_name) {
    FILE *file = fopen(file_name, "w"); // Open the file for writing (creates the file if it doesn't exist)
    if (!file) {
        append_to_output("Error creating file: %s\n", strerror(errno)); // Print error if file creation fails
        return;
    }
    fclose(file); // Close the file after creation
    append_to_output("File '%s' created successfully\n", file_name); // Print success message
}

// Function to remove a file (used with the "removeFile" command)
void remove_file(const char *file_name) {
    if (remove(file_name) == -1) { // Attempt to remove the file
        append_to_output("Error removing file: %s\n", strerror(errno)); // Print error if file removal fails
    } else {
        append_to_output("File '%s' removed successfully\n", file_name); // Print success message
    }
}

// Function to display the current working directory (used with the "displayPwd" command)
void display_pwd() {
    char cwd[MAX_PATH_LEN]; // Buffer to store the current working directory path
    if (getcwd(cwd, sizeof(cwd)) != NULL) { // Get the current working directory
        append_to_output("Current working directory: %s\n", cwd); // Print the current working directory
    } else {
        append_to_output("Error getting current directory: %s\n", strerror(errno)); // Print error if it fails
    }
}

// Function to make a new directory (used with the "makeDir" command)
void make_directory(const char *dir_name) {
    if (mkdir(dir_name, 0777) == -1) { // Attempt to create the directory with full permissions
        append_to_output("Error creating directory: %s\n", strerror(errno)); // Print error if directory creation fails
    } else {
        append_to_output("Directory '%s' created successfully\n", dir_name); // Print success message
    }
}

// Function to remove a directory (used with the "removeDir" command)
void remove_directory(const char *dir_name) {
    if (rmdir(dir_name) == -1) { // Attempt to remove the directory
        append_to_output("Error removing directory: %s\n", strerror(errno)); // Print error if directory removal fails
    } else {
        append_to_output("Directory '%s' removed successfully\n", dir_name); // Print success message
    }
}

// Function to count the number of files in a directory (used with the "countFiles" command)
void count_files(const char *path) {
    DIR *dir = opendir(path); // Open the directory
    if (!dir) {
        append_to_output("Error opening directory: %s\n", strerror(errno)); // Print error if directory can't be opened
        return;
    }

    struct dirent *entry;
    int file_count = 0; // Initialize the file counter
    while ((entry = readdir(dir)) != NULL) { // Loop through the directory entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) { // Skip "." and ".."
            file_count++; // Increment the counter for each file
        }
    }
    closedir(dir); // Close the directory

    append_to_output("Total files in '%s': %d\n", path, file_count); // Print the file count
}

// Function to display the current time (used with the "displayTime" command)
void display_current_time() {
    time_t now; // Variable to store the current time
    struct tm *tm_info; // Structure to hold the local time

    time(&now); // Get the current time
    tm_info = localtime(&now); // Convert the time to local time

    char time_string[100]; // Buffer to hold the formatted time string
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", tm_info); // Format the time into a string

    append_to_output("Current time: %s\n", time_string); // Print the formatted time
}

// Function to display the command history (used with the "history" command)
void display_history() {
    if (history_count == 0) {
        append_to_output("No commands in history.\n"); // If history is empty, display a message
        return;
    }

    append_to_output("Command History:\n");
    for (int i = 0; i < history_count; i++) {
        append_to_output("%d: %s\n", i + 1, command_history[i]); // Print each command in history
    }
}

// Function to save a command to the history array
void save_command_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        command_history[history_count] = strdup(command); // Copy the command into the history
        history_count++; // Increment the history count
    } else {
        free(command_history[0]); // Free the memory of the oldest command
        // Shift all previous commands one slot to the left
        for (int i = 1; i < MAX_HISTORY; i++) {
            command_history[i - 1] = command_history[i];
        }
        command_history[MAX_HISTORY - 1] = strdup(command); // Add the new command at the end
    }
}

// Function to navigate out of the current directory (used with the "getOut" command)
void get_out(const char *dir_name) {
    if (chdir("..") == -1) { // Attempt to move one level up in the directory structure
        append_to_output("Error going back: %s\n", strerror(errno)); // Print error if it fails
    } else {
        display_pwd(); // Display the current working directory after moving up
    }
}

// Function to update the shell prompt (current directory)
void update_prompt(char *prompt, size_t size) {
    char cwd[MAX_PATH_LEN]; // Buffer to hold the current directory path
    if (getcwd(cwd, sizeof(cwd)) != NULL) { // Get the current working directory
        snprintf(prompt, size, "customShell> %s$ ", cwd); // Format the prompt string
    } else {
        snprintf(prompt, size, "customShell> Unknown$ "); // Fallback if unable to get the current directory
    }
}
