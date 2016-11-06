/*This program simulates a simpler version of a terminal where files and 
  directories are created dynamically. The purpose of this project is to
  learn how dynamically allocate memory for potential use from the user. 
  In our simulated terminal, the user can make as many files and directory
  as possible without the limitation of have static memory. Although, 
  the user may have to worry about hardware limitations, the software
  will create the environment to create and change data actively in real
  time.

  Author: Brian Servia
*/


#include "fs-sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void in_first(const char arg[], Node *bef, Node *cur, Node *new, Fs_sim *files);
void inf_not_root(const char arg[], Node *bef, Node *cur, Node *new, Fs_sim *files);
void inserting(const char arg[], Node *befo, Node *curr, Node *new, Fs_sim *files);
void rm_aux(Node *start);
void path_aux(Fs_sim *files, Node *start);
/*----------------------------------------------------------------------------*/
/*fuction that will remove the entire file system and deallocate the memory
  associated with the file system. This function in particular uses 
  a helper function that will recursively go through every node in the 
  file system and free the memory. At the end files is set to NULL.*/
void rm_system (Fs_sim *files) {
  /*free every memory in the system*/
  
  if (files != NULL) {
    Node *start = files -> root;
    Node *fre;
    if (start != NULL) {
      while (start -> next != NULL) {
	fre = start;
	start = start -> next;
	
	if (start -> child !=  NULL) {
	  rmfs_aux (start);
	}
	free (fre -> data);
	free (fre);
      }
      free (start -> data);
      free (start);
      fre = NULL;
      start = NULL;
      files = NULL;
    }
  }

}
/*----------------------------------------------------------------------------*/
/*helper function that will help any function that is trying to deallocate 
  memory from a parent node. The entire sub directory of the parent directory
  will be deleted.This function is used to recursively deallocate the memory for
  both rmfs and rm functions.*/
void rm_aux (Node *start) {
  if (start != NULL) {
    Node *troy;
    Node *foll = start -> child;

    if (start -> next == NULL && start -> child == NULL) {
      return;
    }
  
    while (foll -> next != NULL) {
      troy = foll;
      foll = foll -> next;
      if (foll -> child != NULL) {
	rmfs_aux(foll);
	foll = troy -> next;
      }
      free (troy -> data);
      free (troy);
    }
    
    free (foll -> data);
    free (foll);
  }
}

/*----------------------------------------------------------------------------*/
/*This function removes specific files, or subdirectory (not only its children
  but the directory itself). By removing it also deallocates the memory 
  associated with that node.*/
int remov (Fs_sim *files, const char arg[]) {

  if (files != NULL) {
  
  Node *curr = files -> current;
  Node *del, *front;
  char *frd = strchr(arg, '/');

  /*arg != file/directory in current, or . | .. | / | '\0', or / anywhere.
    return 0*/
  if (strcmp(".", arg) == 0 || strcmp("..", arg) == 0 ||
     strcmp("/", arg) == 0 || arg[0] == '\0') {
    return 0;
  }

  if (frd != NULL) {
    if ((strlen(arg) > 1 && (frd[0] == '/'))) {
      return 0;
    }
  }
  
  /*if arg = file in current remove file, return 1 */
  if (arg != NULL) {
    if (curr == files -> root) {
      while (curr != NULL) {
	if (strcmp(arg, curr -> data) == 0
	   && curr -> dir0_file1 == 1) {
	  del = curr;
	  front = curr;
	  if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }
	  return 1;
	} else if (strcmp(arg, curr -> data) == 0
		  && curr -> dir0_file1 == 0){
	  if (curr -> child != NULL) {
	    del = curr;
	    front = curr;
	    rmfs_aux (curr);
	    if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }
	    return 1;
	  } else {
	    del = curr;
	    front = curr;
	    if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }
	    return 1;
	  }
	}
	curr = curr -> next;
      }
    } else {
      curr = curr -> child;
      while (curr != NULL) {
	if (strcmp(arg, curr -> data) == 0
	   && curr -> dir0_file1 == 1) {
	  del = curr;
	  front = curr;
	  if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }
	  return 1;
	} else if (strcmp(arg, curr -> data) == 0
		  && curr -> dir0_file1 == 0) {
	  if (curr -> child != NULL) {
	    del = curr;
	    front = curr;
	    rmfs_aux (curr);
	    if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }	    
	    return 1;
	  } else {
	    del = curr;
	    front = curr;
	    if (front -> next != NULL) {
	      front = front -> next;
	    } else {
	      front = NULL;
	    }
	    curr = curr -> prev;
	    del -> next = NULL;
	    del -> prev = NULL;
	    free (del -> data);
	    free (del);
	    curr -> next = front;
	    if (front != NULL) {
	    front -> prev = curr;
	    }
	    return 1;
	  }
	  
	}
	curr = curr -> next;
      }
    }
  }
  }

  /*if arg = directory then remove directory and its content. return 1*/

  
  
  
  return 0;

}


/*----------------------------------------------------------------------------*/

/*Creates an abstract system where two pointers (current and root) will point
  to the root node of the potential growing of a linkedlist*/
void make_idea_map (Fs_sim *files) {
  if(files != NULL){
  Node *head = (Node *)malloc(sizeof(Node));
  files -> root = head;
  files -> current = head;
  files -> root -> data = malloc((strlen("/") + 1) * sizeof(char));
  /*plus 1 null char, and scalar does not need malloc*/
  strcpy(files -> root -> data, "/");
  files -> root -> next = NULL;
  files -> root -> prev = NULL;
  files -> root -> child = NULL;
  files -> root -> parent = NULL;
}
}
/*----------------------------------------------------------------------------*/
/*This function will create a node where it will have 4 pointers (child, parent
  next and previous), and will set an integer dir0_file1 to 1 for identifying
  that its a file and not a directory.Esentially the child and parent pointer
  will always be set to null.*/
int supporting (Fs_sim *files, const char arg[]) {

if(files != NULL){
  Node *curr = files -> current;
  Node *befo = files -> current;
  Node *check = files -> current;
  Node *new = (Node *) malloc (sizeof (Node));
  char *frd = strchr (arg, '/');
  
  new -> data = malloc ((strlen (arg) + 1) * sizeof (char));
  new -> child = NULL;
  new -> parent = NULL;

  /*if arg has / in any postion in addition to other chars then return 0,
    and don't modify anything, and arg can't be just solely / */
  /*if arg is an empty string return 0, and don't modify*/
  /*if arg is . | .. | / don't modify anything*/
  if (frd != NULL) {
    if ((strlen (arg) > 1 && (frd[0] == '/'))) {
      return 0;
    }
  }
  if (strcmp (arg, ".") == 0 || strcmp (arg, "..") == 0 ||
     strcmp (arg, "/") == 0 || arg[0] == '\0') {
    return 0;
     }
  
     /*return 1 if the file is not an existing file or directory located in 
       the current directory*/
     /*check NULL*/

 if (strcmp (files -> current -> data, "/") == 0) {
    check = check -> next;
  } else {
    check =  check -> child;
  }

 while (check != NULL) {
    if (strcmp (arg, check -> data) == 0) {
      return 0;
    }
    check =  check -> next;
  }
  
    if (arg != NULL) {
    strcpy (new -> data, arg);
    new -> dir0_file1 = 1;

    
    if (strcmp (befo -> data, "/") == 0) {
      if(befo -> next == NULL){
	in_first(arg, befo, curr, new, files);
	return 1;
      } else if(befo -> next -> next == NULL){
	in_first(arg, befo, curr, new, files);
	return 1;
      }
    } else {
      if(befo -> child == NULL){
	inf_not_root(arg, befo, curr, new, files);
	return 1;
      } else if(befo -> child -> next == NULL){
	inf_not_root(arg, befo, curr, new, files);
	return 1;
      }
    }
    
    if(curr != NULL){
      inserting(arg, befo, curr, new, files);
      return 1;
    }
    
  }
}
  
  
    return 0;
}
/*----------------------------------------------------------------------------*/
/*This function will create a node that has 4 pointers (child, parent, next,
  and previous), that will set an identification integer dir0_file1 to 0, so 
  that its clear its a directory. Once we know its a directory, we have 
  the possibility of setting child and parent to subdirectory or a new file.*/
int idea (Fs_sim *files, const char arg[]) {
  
  if(files != NULL){
  Node *curr = files -> current;
  Node *befo = files -> current;
  Node *check = files -> current;
  Node *new = (Node *) malloc (sizeof (Node));
  char *frd = strchr(arg, '/');

  new -> data = malloc ((strlen (arg) + 1) * sizeof (char));
  new -> parent = NULL;
  new -> child = NULL;

 
  /*if arg already exists (file or sub) in current, or is . | .. | / | empty
    string, return 0 and don't modify*/
  /*if arg doesn't solely consist of '/' but its somewhere in arg, return 0
    and don't modify*/
  
  if (frd != NULL) {
    if ((strlen (arg) > 1 && (frd[0] == '/'))) {
      return 0;
    }
  }  
  if (strcmp (arg, ".") == 0 || strcmp (arg, "..") == 0
      || strcmp (arg, "/") == 0 || arg[0] == '\0') {
    
    
    return 0;
  }

  if (strcmp (files -> current -> data, "/") == 0) {
    check = check -> next;  /*touch th, there, pi, mkdir hel*/
  } else {
    check =  check -> child;
  }

  
  while (check != NULL) {
    if (strcmp(arg, check -> data) == 0) {
      return 0;
    }
    
    check =  check -> next;
    }

  /*check after*/

  /*if arg is not an exisisting file or directory in the current dir,
    and not a special error value, then create a subdirectory in current dir
    return 1*/
  /*check if in current*/

  
  
   if (arg != NULL) {
    strcpy (new -> data, arg);
    new -> dir0_file1 = 0;
    
    if (strcmp (befo -> data, "/") == 0) {
      if (befo -> next == NULL) {
        in_first(arg, befo, curr, new, files);
	return 1;
      } else if (befo -> next -> next == NULL) {
	in_first(arg, befo, curr, new, files);
	return 1;
      }
    } else { 
      if(befo -> child == NULL){
	inf_not_root(arg, befo, curr, new, files);
	return 1;
      } else if(befo -> child -> next == NULL){
	inf_not_root(arg, befo, curr, new, files);
	return 1;
      }
    }

    
    if(curr != NULL){
      inserting(arg, befo, curr, new, files);
      return 1;
    }
  }
			    

  
      
}
    
  
  return 0;
}
/*----------------------------------------------------------------------------*/
  /*This function will change the current of the file system, to child or
    parent to a sub directory if found in the current directory's linkedlist*/
int connect_idea (Fs_sim *files, const char arg[]) {
  /*if arg does not refer to any existing file or dir in current dir, and 
    not a special case, return 0 and don't modify*/


  if(files != NULL){
  Node *curr = files -> current;
  Node *befo = files -> current;
  Node *check = files -> current;
  char *frd = strchr(arg, '/');
  int on = 0;


  

  while (curr !=  NULL && strcmp (arg, "..") != 0
	&& strcmp (arg, ".") != 0) {
    if (strcmp (files -> current -> data, "/") == 0) {
      if (strcmp (curr -> data, arg) == 0 &&
	 curr -> dir0_file1 == 0) {
	files -> current = curr;
	return 1;
      }
    } else {
      
      if (curr -> child != NULL && on == 0) {
	on++;
	curr = curr -> child;
      }
      
      if (strcmp (curr -> data, arg) == 0 &&
	 curr -> dir0_file1 == 0) {
	files -> current = curr;
	return 1;
      }
      
    }
    curr = curr -> next;
  }
  curr = files -> current;
/*if arg is . then no modification ( . = change current to current), return
  1*/
if (strcmp (arg, ".") == 0) {
    return 1;
  }
  /*if arg doesn't has chars and one '/' somewhere, return 0 and don't 
    modify*/
  if (frd != NULL) {
    if ((strlen (arg) > 1 && (frd[0] == '/'))) {
      return 0;
    }
  }

  /*if arg is the name of just a file in the current, return 0 and don't
    modify*/
  if (check -> child != NULL) {
    check = check -> child;
  } 
  
  while (check -> next != NULL) {
    if (strcmp (check -> data, arg) == 0 && (check -> dir0_file1) == 1) {
      return 0;
    } else if (strcmp (arg, check -> data) != 0 && check -> next == NULL) {
      return 0;
    }
    check = check -> next;
  }
  
  /*if arg is '/' | '\0', the root will become current, regardless where current
    is at that moment, return 1*/

  if (strcmp (arg, "/") == 0 || arg[0] == '\0') {
    files -> current = files -> root;
    return 1;
  }
  
  /*if arg is the name of an immediate sub of current, that sub is the
    new current dir of files, return 1*/
  /*implement here*/
  if (arg != NULL) {
    if (strcmp (arg, "..") == 0 &&
       strcmp ("/", (files -> current -> data)) == 0) {
      
      return 1;
    } else if (strcmp (arg, "..") == 0) {
      befo = files -> current;
      
      if (befo -> prev == NULL) {
	files -> current =  befo -> parent;
	} else if (befo -> parent == NULL) {
	while (befo -> prev != NULL) {
	  befo = befo -> prev;
	}
     
	if (befo -> parent != NULL) {
	  files -> current = befo -> parent;
	  } else if (befo -> parent == NULL) {
	  
	  
	    files -> current = befo;
	    }
      }
      return 1;
    }
    
  }
  }
  
  
  return 0;
}
/*----------------------------------------------------------------------------*/
/*The ls function will print specific files or a specific directory's files and 
  subdirectories. ls does not change current, even if another directory 
  should be printed*/
int list (Fs_sim *files, const char arg[]) {


  if(files != NULL){
  
  Node *curr = files -> current;
  Node *befo = files -> current;
  Node *check = files -> current;
  char *frd = strchr(arg, '/');
  int dirfil;

  /*more chars around /, don't print/modify, return 0*/
  if (frd != NULL) {
    if ((strlen (arg) > 1 && (frd[0] == '/'))) {
      return 0;
    }
  }
  
  /*if current is root, and arg = .. | / | '/0', would be the same as if
    arg = .  (no output), return 0*/
  
  if (strcmp (curr -> data, files -> root -> data) == 0 &&
     (strcmp (arg, "..") == 0 || strcmp (arg, "/") == 0 ||
      arg[0] == '\0') && files -> root -> next == NULL) {
    return 1;
  }

  if (strcmp (arg, files -> root -> data) == 0) {
    curr = files -> root -> next;
    while (curr != NULL) {
      dirfil = curr -> dir0_file1;
      if (dirfil == 0) {
	printf ("%s/\n", curr -> data);
      } else if (dirfil == 1) {
	printf ("%s\n", curr -> data);
      }
      curr = curr -> next;
    }
    return 1;
  }
  if (check -> child != NULL) {
    check = check -> child;
  }
  while (check != NULL) {
    if (strcmp (check -> data, arg) == 0 &&
       check -> child == NULL &&
       check -> dir0_file1 == 0) {
      return 1;
    } else if (strcmp (check -> data, arg) == 0
	      && check -> child == NULL &&
	      check -> dir0_file1 == 1) {
      printf ("%s\n", check -> data);
      return 1;
    }
    check = check -> next;
  }
   /*if arg does not refer to file or sub, or is a special char, in 
    current dir. return 0, don't print/modify*/


  if (strcmp (arg, "..") != 0) {
    if (strcmp (arg, ".") != 0) {
      if (strcmp (arg, "/") != 0) {
	if (arg[0] != '\0') {
	  check = files -> current;
	  while (check != NULL) {
	    if (strcmp (check -> data, arg) != 0) {
	      
	      if (check -> next == NULL) {
		return 0;
	      }
	    } else {
	      if (strcmp (check -> data, arg) == 0
		 && check -> dir0_file1 == 0) {
		curr = check;
		curr = curr -> child;
	      }
	      
	      if (strcmp (files -> root -> data, arg) == 0) {
		curr = files -> root;
		curr = curr -> next;
		
		while (curr != NULL) {
		  dirfil = curr -> dir0_file1;
		  if (dirfil == 0) {
		    printf ("%s%c\n", curr -> data, '/');
		  } else if (dirfil == 1) {
		    printf ("%s\n", curr -> data);
		  }
		  curr = curr -> next;
		}
		return 1;
	      } else {
	        
		while (curr != NULL) {
		  dirfil = curr -> dir0_file1;
		  if (dirfil == 0) {
		    printf ("%s%c\n", curr -> data, '/');
		  } else if (dirfil == 1) {
		    printf ("%s\n", curr -> data);
		  }
		  curr = curr -> next;
		}
		return 1;
	      }
	    }
	    check = check -> next;
	  }
	}
      }
    }
  }
  /*if arg /, print all from root, regarless where current is, return 1*/
  
  
  
  /*if arg =  a file name, then print that single name followed by /n on 
    a line by itself (no preceding or following whitespace/punctuation),
    return 1*/

  /*if arg = . || '/0', then all files and dir of current should be printed
   return 1*/
  
  curr = files -> current;
  while (curr != NULL) {

     if (strcmp (arg, ".") == 0 ||
	      arg[0] == '\0') {
      if (strcmp (files -> current -> data, "/") == 0) {
	  befo = befo -> next;
	} else {
	  befo = befo -> child;
	}
      
      while (befo != NULL) {
	  dirfil = befo -> dir0_file1;
	  if (dirfil == 0) { 
	    printf ("%s%c\n", befo -> data, '/');
	  } else if (dirfil == 1) {
	    printf ("%s\n", befo -> data);
	  }
	  befo = befo -> next;
	}
	return 1;
    } else if (strcmp (arg,"..") == 0) {
     
       if (files -> current == NULL) {
	befo =  befo -> parent;
	dirfil = befo -> child -> dir0_file1;
	if (dirfil == 0) {
	  printf ("%s%c\n", befo -> child -> data, '/');
	} else if (dirfil == 1) {
	  printf ("%s\n", befo -> child -> data);
	}
	befo = befo -> next;
	while (befo != NULL) {
	  dirfil = befo -> next -> dir0_file1;
	  if (dirfil == 0) {
	    printf ("%s%c\n", befo -> data, '/');
	  } else if (dirfil == 1) {
	    printf ("%s\n", befo -> data);
	  }
	  befo = befo -> next;
	}
        
	return 1;
      }

       while (befo -> prev != NULL) {
	befo = befo -> prev;
      }
       befo = befo -> next;
       while (befo != NULL) {
	 dirfil = befo -> dir0_file1;
	 
	 if (dirfil == 0) {
	   printf ("%s%c\n", befo -> data, '/');
	 } else if (dirfil == 1) {
	   printf ("%s\n", befo -> data);
	 }
	 befo = befo -> next;
       }
      return 1;
    
     } 
      curr = curr -> next;
    }  
  

  /*if arg = dir then print all files and subs with /n on each line on its
   own. Increasing order strcmp(str1,str2) < 0 then str1 < str2. dir must
   printed with / at the end. if arg = dir where there are no files or subs
   don't print output. return 1*/
  

  

  /*if arg = .. all the files and dir on the parent of current, print all.
    guranteed to have one sub from parent, return 1*/

  }

  
  return 0;
}
/*----------------------------------------------------------------------------*/
/*This function backtracks the path from the current directory to the parent
  directories till it reaches the root director. Once it reaches the root 
  directory it will print the output from the root to the current directory.
*/
void path (Fs_sim *files) {

  if(files != NULL){

    
    pwd_aux(files, files -> current);
    if(files -> current != files -> root){
      printf("/%s\n", files -> current -> data);
    } else {
      printf("%s\n", files -> root -> data);
    }
    
  /*purpose: print path from root to current. path must begin with /. However,
    / must not follow the last (current) directory, it should be a /n.*/
  
  /*pwd will always produce output, if current is root, then pwd = / */

  }

}

/*----------------------------------------------------------------------------*/
/*helper method that will recursively search for the parent directories and 
  print them out*/
void path_aux(Fs_sim *files, Node *start) {

  if(files != NULL && start != NULL){
    if(start == files -> root){
      return;
    }
 
    while(start -> prev != NULL){
      start = start -> prev;
    }

    if(start != files -> root){
      start = start -> parent;
    }
  

  
    pwd_aux(files, start);

    if(strcmp(start -> data, "/") != 0){
      printf("/%s", start -> data);
    }
  }
}
/*----------------------------------------------------------------------------*/

void in_first(const char arg[], Node *bef, Node *cur, Node *new, Fs_sim *files){
  
  if (bef -> next == NULL) {  
    new -> next = NULL;
    bef -> prev = NULL;
    bef -> next = new;
    new -> prev = bef;
    return;
  } else {
    cur = cur -> next;
    bef = bef -> next;
    if (cur -> next == NULL) {
      if (strcmp (cur -> data, arg) < 0) {
	cur -> next = new;
	new -> prev = cur;
	new -> next = NULL;
	return;
      } else if (strcmp (cur -> data, arg) > 0) {
	files -> current -> next = new;
	new -> prev = files -> current;
	new -> next = cur;
	cur -> prev = new;
	cur -> next = NULL;
	return;
      }
    }
  }
}

void inf_not_root(const char arg[], Node *bef, Node *cur, Node *new, Fs_sim *files){
  if (bef -> child == NULL) {
    new -> next = NULL;
    new -> prev = NULL;
    bef -> child = new;
    new -> parent = bef;
    return;
  } else {
	
    bef = bef -> child;
    cur = cur -> child;
	
    if (cur -> next == NULL) {
      if (strcmp (cur -> data, arg) < 0) {
	cur -> next = new;
	new -> prev = cur;
	new -> next = NULL;
	return;
      } else if (strcmp (cur -> data, arg) > 0) {
	cur -> parent = NULL;
	files -> current -> child = new;
	new -> parent = files -> current;
	new -> next = cur;
	cur -> prev = new;
	return;
      }
    }
  }
}

void inserting(const char arg[], Node *befo, Node *curr, Node *new, Fs_sim *files){

  if(strcmp(befo -> data, "/") == 0){
    curr = curr -> next;
    befo = befo -> next;
  } else {
    befo = befo -> child;
    curr = curr -> child;
  }
  while (curr != NULL) {
    
    if (strcmp (files -> current -> data, "/") == 0) {
       
      if (strcmp (curr -> data, arg) < 0 && curr -> next == NULL) {
	curr -> next = new;
	new -> prev = curr;
	new -> next = NULL;
	return;
	} else if (strcmp (curr -> data, arg) < 0 &&
		 strcmp (curr -> next -> data, arg) > 0) {
	befo = curr;
	curr = curr -> next;
	befo -> next = new;
	new -> prev = befo;
	curr -> prev = new;
	new -> next = curr;
	return;
	} else if (strcmp (curr -> data, arg) < 0 &&
		 strcmp (curr -> next -> data, arg) < 0) {
	curr = curr -> next;
      } else if (strcmp (curr -> data, arg) > 0) {
	befo = befo -> prev;
	befo -> next = new;
	new -> prev = befo;
	curr -> prev = new;
	new -> next = curr;
	return;
      }
      } else {
      if (strcmp (curr -> data, arg) < 0
	  && curr -> next == NULL) {
	curr -> next = new;
	new -> prev = curr;
	new -> next = NULL;
	return;
      } else if (strcmp (curr -> data, arg) < 0 &&
		 strcmp (curr -> next -> data, arg) > 0) {
	befo = curr;
	curr = curr -> next;
	befo -> next = new;
	new -> prev = befo;
	curr -> prev = new;
	new -> next = curr;
	return;
      } else if (strcmp (curr -> data, arg) < 0 &&
		 strcmp (curr -> next -> data, arg) < 0) {
	curr = curr -> next;
      } else if (strcmp (curr -> data, arg) > 0) {
	files -> current -> child = new;
	new -> parent = files -> current;
	curr -> parent = NULL;
	curr -> prev = new;
	new -> next = curr;
	return;
      }
    }
  }
}
