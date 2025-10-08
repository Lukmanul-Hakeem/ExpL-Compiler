#include "./global_symbol_table.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int binding_addr = 4096;
int flag_label = 0;


gst_node* head = NULL;
gst_node* tail = NULL;
p_node* param_head = NULL;
p_node* param_tail = NULL;

gst_node* create_gst_node(char* name, int type, int outer_size, int inner_size, p_node* param_list, gst_node* next){

    gst_node* new_node = (gst_node*)malloc(sizeof(gst_node));

    new_node->name = strdup(name);
    new_node->type = type;
    new_node->inner_size = inner_size;
    new_node->out_size = outer_size;
    new_node->param_list = param_list;
    new_node->binding = binding_addr;
    new_node->next = next;

    if(param_list == NULL){

        if(inner_size != 0) binding_addr += inner_size * outer_size;
        else binding_addr += outer_size;

        new_node->flag_label = -1 ;

    }else{

        new_node->flag_label = flag_label;
        flag_label += 1;

    }

    return new_node;
}

p_node* create_p_node(char* name, int type){

    p_node* new_node = (p_node*)malloc(sizeof(p_node));
    new_node->name = strdup(name);
    new_node->next = NULL;

    return new_node;
}

void gst_install(char *name, int type, int outer_size, int inner_size, p_node* param_list){
   gst_node* temp = look_up(name);
    if (temp) {
        fprintf(stderr, "Error: variable '%s' is already declared.\n", name);
        exit(1);   
    } 

    gst_node* new_node = create_gst_node(name, type, outer_size, inner_size, param_list, NULL);

    if(!head){
        head = tail = new_node;
    }else{
        tail->next = new_node;
        tail = tail->next;
    }
}

void param_install(char* name, int type){

    if(param_head == NULL){

        param_head = param_tail = create_p_node(name, type);

    }else {

        p_node* temp = param_look_up(name);

        if(temp){
            fprintf(stderr, "Error: parameter '%s' is already declared.\n", name);
            exit(1);
        }

        param_tail->next = create_p_node(name, type);
        param_tail = param_tail->next;

    }

}

gst_node* look_up(char* name){

    gst_node* temp = head;

    while(temp){
        if(strcmp(temp->name, name) == 0)return temp;
        temp = temp->next;
    }

    return NULL;
}

p_node* param_look_up(char* name){

    p_node* temp = param_head;

    while(temp){
        if(strcmp(temp->name, name) == 0)return temp;
        temp = temp->next;
    }

    return NULL;
}


// void print_gstable(){
//     gst_node* temp = head;

//     while(temp){

//         printf("ID : %s, Type : %d, outer_size : %d, inner_size : %d\n", temp->name, temp->type, temp->out_size, temp->inner_size);

//         if(temp->param_list != NULL){
//             p_node* temp_list = temp->param_list;
//             while(temp_list){
//                 printf("FUNCTION --> F_ID : %s, Type : %d\n", temp_list->name, temp_list->type);
//                 temp_list = temp_list->next;
//             }
//         }

//         temp = temp->next;
//     }
// }


void print_gstable() {
    gst_node* temp = head;

    if (!temp) {
        printf("\n📜 Global Symbol Table is empty.\n");
        return;
    }

    printf("\n==============================\n");
    printf("     🌐 GLOBAL SYMBOL TABLE    \n");
    printf("==============================\n\n");

    while (temp) {
        printf("ID Name     : %-15s\n", temp->name);
        printf("Type        : %-10d\n", temp->type);
        printf("Outer Size  : %-10d\n", temp->out_size);
        printf("Inner Size  : %-10d\n", temp->inner_size);
        printf("Binding     : %-10d\n", temp->binding);

        if (temp->param_list != NULL) {
            printf("Parameters  :\n");
            p_node* temp_list = temp->param_list;
            while (temp_list) {
                printf("   ➜ %-12s | Type : %-3d\n", temp_list->name, temp_list->type);
                temp_list = temp_list->next;
            }
        } else {
            printf("Parameters  : None\n");
        }

        printf("------------------------------\n");
        temp = temp->next;
    }

    printf("\n✅ End of Global Symbol Table\n\n");
}