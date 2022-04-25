/* Khanh Dong - U14837275 */
/* Functions for tshirt store */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tshirt.h"
#include "readline.h"

void help() {
	printf("List of operation codes:\n");
	printf("\t'a' for adding a t-shirt to the inventory;\n");
	printf("\t'h' for help;\n");
	printf("\t'o' for searching t-shirts by organization;\n");
	printf("\t's' for searching t-shirts by size;\n");
	printf("\t'p' for printing the inventory;\n");
	printf("\t'q' for quit.\n");
}

struct tshirt * add_to_inventory(struct tshirt *inventory) {
	struct tshirt *new_node, *current, *prev;
	new_node = malloc(sizeof(struct tshirt));
	if(new_node == NULL){
	   printf("Database is full\n");
 	   return inventory;
	}
    printf("Enter student organization name:\n");
	read_line(new_node->org_name, ORG_NAME_LEN);
	printf("Enter tshirt size:\n");
    read_line(new_node->size, SIZE_LEN);
        
	for(current = inventory, prev=NULL; current!=NULL && strcmp(new_node->org_name, current->org_name)>0; prev=current, current = current->next);

    printf("Enter price:\n");
	scanf("%lf", &new_node->price);
	printf("Enter quantity:\n");
	scanf("%d", &new_node->quantity);
        
	if(inventory == NULL){
	   inventory = new_node;
	}
	else if(current == NULL) prev->next = new_node;
	else {
	    while(current->next!=NULL && strcmp(new_node->org_name, current->org_name)==0){
			if(strlen(new_node->size)>strlen(current->size)){ 
				prev = current;
				current = current->next;
				continue;
			}
			else if(strlen(new_node->size) < strlen(current->size)) break;
			prev = current;
			current = current->next;
	        if (strcmp(new_node->size, current->size) > 0) break;   
	    }
	    if(strlen(new_node->size)>strlen(current->size)){
			current->next = new_node;
			return inventory;
	    }
	    if(prev!=NULL) prev->next = new_node;
	    else if(strlen(new_node->size)<= strlen(current->size)) inventory = new_node;
	    else{
			current->next = new_node;
			return inventory;
	    }
	    if(current != NULL) new_node->next = current; 
	}

	return inventory;
}

void search_by_organization(struct tshirt *inventory) {
 	char orgName[ORG_NAME_LEN+1];
	int count = 0;
	struct tshirt *p;
	printf("Enter student organization name:\n");
	read_line(orgName, ORG_NAME_LEN);
	for(p = inventory; p!=NULL; p = p->next){
            if(strcmp(orgName, p->org_name)==0) count++;
	}
	if(count == 0){
	   printf("No tshirt found!\n");
	   return;
	}
	printf("|----------------------------------------------------|-----|-------|------|\n");
	printf("| Student organization                               | Sz. | Price | Qty. |\n");
	printf("|----------------------------------------------------|-----|-------|------|\n"); 
	for(p = inventory; p!=NULL; p = p->next){
	    if(strcmp(orgName, p->org_name)==0){
	      printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity); 
	    }   
	}
        printf("|----------------------------------------------------|-----|-------|------|\n");
}

void search_by_size(struct tshirt *inventory) {
 	char size_n[SIZE_LEN+1];
	int count = 0;
        struct tshirt *p;
        printf("Enter tshirt size:\n");
        read_line(size_n, SIZE_LEN);
	for(p = inventory; p!=NULL; p = p->next){
	   if(strcmp(size_n, p->size)==0) count++;
	}
	if(count == 0){
	   printf("No tshirt found!\n");
	   return;
	}
	printf("|----------------------------------------------------|-----|-------|------|\n");
	printf("| Student organization                               | Sz. | Price | Qty. |\n");
	printf("|----------------------------------------------------|-----|-------|------|\n");   
	for(p = inventory; p!=NULL; p = p->next){
           if(strcmp(size_n, p->size)==0){
             printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity);
           }
	}
	printf("|----------------------------------------------------|-----|-------|------|\n");
}


void print_inventory(struct tshirt *inventory) {
	struct tshirt *p;
        if(inventory==NULL){
	   printf("No tshirt found!\n");
           return;
	}
	printf("|----------------------------------------------------|-----|-------|------|\n");
	printf("| Student organization                               | Sz. | Price | Qty. |\n");
	printf("|----------------------------------------------------|-----|-------|------|\n");
	for(p = inventory; p!= NULL; p = p->next){
            printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity);
	}
	printf("|----------------------------------------------------|-----|-------|------|\n");
}

void clear_inventory(struct tshirt *inventory) {
	struct tshirt *p;
	while(inventory != NULL){
  	     p = inventory;
	     inventory = inventory->next;
             if(p!=NULL) free(p);
        }
}
