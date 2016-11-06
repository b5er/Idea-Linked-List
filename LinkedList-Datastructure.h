#include <stdio.h>
#ifndef FS_DATA_SYM
#define FS_DATA_SYM


void rm_system (Fs_sim *files);
int remov (Fs_sim *files, const char arg[]);
void make_idea_map (Fs_sim *files);
int supporting (Fs_sim *files, const char arg[]);
int idea (Fs_sim *files, const char arg[]);
int connect_idea (Fs_sim *files, const char arg[]);
int list (Fs_sim *files, const char arg[]);
void path (Fs_sim *files);




/*Make structure that sets up a linked list, with both
  siblings and children (little node | files and directories)*/



typedef struct node{
  char *data;        /*name of file or directory*/
  int dir0_file1;
  struct node* child;
  struct node* parent;
  struct node* prev; 
  struct node* next; 
} Node;


typedef struct f_Sys{
  Node *root;
  Node *current; /*will have the two pointers*/
} Fs_sim;

#endif