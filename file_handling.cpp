#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int searchFile(const char *directoryPath, const char *fileName) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open the directory
    dir = opendir(directoryPath);

    if (dir == NULL) {
        perror("opendir");
        return 1; // Error opening directory
    }

    // Iterate through directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file
        if (stat(entry->d_name, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            // Compare the current file name with the target file name
            if (strcmp(entry->d_name, fileName) == 0) {
                printf("File found: %s\n", entry->d_name);
                closedir(dir);
                return 0; // File found
            }
        }
    }

    printf("File not found: %s\n", fileName);
    closedir(dir);
    return 1; // File not found
}

int main() {
    const char *directoryPath = ".";  // Specify the directory path
    const char *fileName = "example.txt";  // Specify the file name to search

    // Call the searchFile function
    int result = searchFile(directoryPath, fileName);

    return result;
}
