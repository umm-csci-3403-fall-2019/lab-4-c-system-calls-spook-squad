#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  struct stat* fileStat;
  fileStat = malloc(sizeof(struct stat));
  int fileExists = stat(path, fileStat);
   
  bool isadirectory = (fileExists == 0 && S_ISDIR(fileStat->st_mode));  
  free(fileStat);
  return isadirectory;
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {  
  
  num_dirs++; 
  DIR *dir = opendir(path);
  
  struct dirent *f;
  f = readdir(dir);
  
  while(f != NULL){
    char* name = f->d_name;    
   
    if(!(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)){
      chdir(path);
      process_path(name);
      chdir("..");
    }
    f = readdir(dir);
  }
  closedir(dir);
  free(f);
  
  
	/*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
}

void process_file(const char* path) {
  num_regular++;
}

void process_path(const char* path) {

  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
 
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  
  process_path(argv[1]);
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
