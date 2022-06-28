#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct tag{

    int vehicleID; //ex:32
    char make[10];//ex:Mercedes
    char model[10];//ex:E220
    int year;//ex:2002
    int mileage;//ex:180000
    int cost;//ex:$16000
    struct tag *next;//ptr of the that hold adr of the following node
   
}node;

int check=0;
int flag2=1;

void menu();
node* create_node(node* head,int count);
node* add_toLL(node* head,node *Toadd);
void display_LL(node* head);
void SubMenuUpdate(node* head);
node* delete_vehicle(node* head,int id);
int count_cars(node* head);
void search_car(node* head);
void bubble_sort(node*head);
void display_LL_file(node* head,FILE *fp);
void exit_fun();


int main(void){
    int num_from_menu;//to choose from the menu
    node *Toadd,*v;
    node* head=NULL;
    int count=0,id;
    int cnt;
    FILE* fp;
   
   
    while(count < 3){
    Toadd=create_node(head,count);
    head=add_toLL(head,Toadd);
    count++;
    }
    printf("\n\t\t\t\t\t\t\t|Hello User|");
    printf("\n\t\t\t\t\t\t\t************\n");
    menu();
    printf("\n\n==>Please choose out from the menu above: ");
    scanf("%d",&num_from_menu);
    while(num_from_menu != 7){
        if(num_from_menu == 1){
            printf("\n\t\t\t\t*You have chosen 1-Display all cars.*\n");
            display_LL(head);
         }
        else if(num_from_menu == 2){
            printf("\n\t\t\t\t*You have chosen 2-Add a car.*\n");
            Toadd=create_node(head,count);
            //printf("\ncheck is:%d\n",check);
            if(check ==0){//we have to ensure that to vehicle doesn't exist before adding it to LL
      head=add_toLL(head,Toadd);
      printf("\n==>This car was added successfully.\n");
            }
           
        }
        else if(num_from_menu == 3){
            printf("\n\t\t\t\t*You have chosen 3-Update a car.*\n");
            SubMenuUpdate(head);
           
        }
        else if(num_from_menu == 4){
            printf("\n\t\t\t\t*You have chosen 4-Delete a car by vehicleId.*\n");
            printf("Please enter the Id of the vehicle that you want to delete: \n==>");
  scanf("%d",&id);
            head=delete_vehicle(head,id);
            if(flag2 == 0){
             printf("\n-This vehicle was successfully deleted.\n");
            }
           
        }
        else if(num_from_menu == 5){
            printf("\n\t\t\t\t*You have chosen 5-Count the number of cars.*\n");
            cnt=count_cars(head);
            printf("\n The number of cars is: %d\n",cnt);
        }
        else if(num_from_menu == 6){
            printf("\n\t\t\t\t*You have chosen 6-Search for a car.*\n");
            search_car(head);
           
        }
       
        else if(num_from_menu > 7 || num_from_menu < 0 ){
            printf("ERROR,wrong number[1-2-3-4-5-6-7].\n");
           
            menu();
        }
        printf("\n**************************************************\n");
        menu();
        printf("\n -Please choose again a number from the menu: ");//this is the menu
        scanf("%d",&num_from_menu);
    }
    bubble_sort(head);
    display_LL_file(head,fp);
    exit_fun();
   

return 0;
}

void menu(){
    printf("\n\n\t\t\t\t\t\t\t   menu:\n");
    printf("\t\t\t\t\t\t\t   ----");
    printf("\n\t\t\t\t      1-Display all cars.\t    2-Add a car.\n\t\t\t\t      3-Update a car.\t\t    4-Delete a car by vehicleId.\n\t\t\t\t      5-Count the cars' number.     6-Search for a car.\n\t\t\t\t      7-Quit.");
}

node* create_node(node* head,int count){
node* ptr;
node* walker=head;
int flag=0;
int ID,yr,milg,cst;
char mk[10],modl[10];


if(count == 0){
 ptr=(node*)malloc(sizeof(node));
    ptr->vehicleID=32;
    strcpy(ptr->make,"Mercedes");
    strcpy(ptr->model,"E220");
    ptr->year=2002;
    ptr->mileage=180000;
    ptr->cost=16000;
    ptr->next=NULL;
    return(ptr);
}
if(count == 1){
 ptr=(node*)malloc(sizeof(node));
    ptr->vehicleID=20;
    strcpy(ptr->make,"Toyota");
    strcpy(ptr->model,"Rav4");
    ptr->year=2010;
    ptr->mileage=56000;
    ptr->cost=30000;
    ptr->next=NULL;
    return(ptr);
}
if(count == 2){
 ptr=(node*)malloc(sizeof(node));
    ptr->vehicleID=15;
    strcpy(ptr->make,"Peugeot");
    strcpy(ptr->model,"206");
    ptr->year=2004;
    ptr->mileage=150000;
    ptr->cost=12000;
    ptr->next=NULL;
    return(ptr);
}
else if(count != 0 && count != 1 && count != 2){
 printf("-please enter the vehicle' Id:");
 scanf("%d",&ID);
 
 printf("-please enter the brand of the vehicle:");
 scanf("%s",mk);
 
 printf("-please enter the model of the vehicle:");
 scanf("%s",modl);
 
 printf("-please enter the vehicle' year:");
 scanf("%d",&yr);
 
 printf("-please enter the vehicle' mileage:");
 scanf("%d",&milg);
 
 printf("-please enter the vehicle' cost:");
 scanf("%d",&cst);
 
 //now we need to traverse the whole LL to ensure that this vehicle doesn't exist
 while(walker!=NULL){
  if(walker->vehicleID == ID && strcmp(walker->make,mk)==0 && strcmp(walker->model,modl)==0 && walker->year == yr && walker->mileage == milg && walker->cost == cst){
   flag=1;
  }
  walker=walker->next;
 }
 
 if(flag == 0){
  ptr=(node*)malloc(sizeof(node));
     ptr->vehicleID=ID;
     strcpy(ptr->make,mk);
     strcpy(ptr->model,modl);
     ptr->year=yr;
     ptr->mileage=milg;
     ptr->cost=cst;
     ptr->next=NULL;
     return(ptr);
 }
 if(flag == 1){
  printf("\n==>This vehicle already exists.\n");
  check=1;
  return;
 }
}

}

node* add_toLL(node* head,node *Toadd){
node* walker;
if(head == NULL)
 head=Toadd;
else{
 walker=head;
 while(walker->next!=NULL){
  walker=walker->next;
 }
  walker->next=Toadd;
}
return(head);
}

void display_LL(node* head){
node* walker;
walker=head;
if(head == NULL){
 printf("The list is empty");
}
else{
 printf("\n-The cars are:\n\n");
 while(walker!=NULL){
  printf(" ==> VehicleID: %d | Make:%s | Model:%s | Year:%d | Mileage:%d | Cost:%d |",walker->vehicleID,walker->make,walker->model,walker->year,walker->mileage,walker->cost);
  printf("\n");
  printf("\t\t        *********************************************\n");
  walker=walker->next;
 }
 
 
}
}
void SubMenuUpdate(node* head){
int num;
int id;
int flg=0;
node* walker;
walker=head;
printf("Please enter the ID of the vehicle that you want to update:");
scanf("%d",&id);
while(walker!=NULL){
  if(walker->vehicleID == id){
   flg=1;//just to confirm that the given id exists
   break;
  }
  walker=walker->next;
 }


if(flg == 1){
 printf("\n\n\t\t\t\t\t\t\t   Sub_Menu:\n");
    printf("\t\t\t\t\t\t\t   ---------");
    printf("\n\t\t\t\t\t      1-The mileage.\t    2-The cost.");
    printf("\nIn order to update the car please choose from this sub menu: \n ==> ");
    scanf("%d",&num);
//     if(num == 1){
//       printf("-please enter the new vehicle' mileage: ");
//       scanf("%d",&walker->mileage);
 
//   }
//   else if(num == 2){
//    printf("-please enter the new vehicle' cost: ");
//       scanf("%d",&walker->cost);
 
//   }
 while(!(num == 1 || num == 2)){
  printf("\n\n\t\t\t\t\t\t\t   Sub_Menu:\n");
     printf("\t\t\t\t\t\t\t   ---------");
     printf("\n\t\t\t\t\t      1-The mileage.\t    2-The cost.");
     printf("\nError, please choose a number from the menu [1-2]: ");
     scanf("%d",&num);
 }
 if(num == 1){
     printf("-please enter the new vehicle' mileage: ");
     scanf("%d",&walker->mileage);
 
 }
 else if(num == 2){
  printf("-please enter the new vehicle' cost: ");
     scanf("%d",&walker->cost);
 
 }
    }
    else if(flg == 0){
 printf("\nvehicle doesn't exists.");
}
     

}

node* delete_vehicle(node* head,int id){
node* walker,*temp;
int flag=0;


if(head == NULL){
 printf("\n The list is empty.\n");

 return;
}
else{
 walker=head;
 if(walker->vehicleID == id){
  head=walker->next;
  //temp=walker;
 
  free(walker);
  flag2=0;
 }//if

else{
 while(walker->next != NULL){
  if(walker->next->vehicleID == id){
   temp=walker->next;
   walker->next=walker->next->next;
   free(temp);
   flag=1;
   flag2=0;
   break;
  }
  else{
   walker=walker->next;
  }
 
 }
 if(flag==0){
  printf("\nThis vehicle doesn't exists.");
 }
 }//else
}
return(head);
}
int count_cars(node* head){
int i=0;
node* walker;
walker=head;

if(walker == NULL){
 printf("\n the list is empty");
 
}
else{
 
 while(walker!=NULL){
  i++;
  walker=walker->next;
 }
}
return(i);
}

void search_car(node* head){
int yr;
int flag=0;
char brand[10];
node* walker;
walker=head;


printf("please enter the brand of the vehicle\n==>");
scanf("%s",brand);
printf("please enter the year of the vehicle\n==>");
scanf("%d",&yr);

if(walker == NULL){
 printf("\n the list is empty");
 
}
else{
 
 while(walker!=NULL){
  if(strcmpi(walker->make,brand) == 0 &&  walker->year == yr){
   flag=1;
   break;
  }
  walker=walker->next;
 }
 if(flag == 1){
  printf("\nThis vehicle exists.\n");
  printf(" ==> VehicleID: %d | Make:%s | Model:%s | Year:%d | Mileage:%d | Cost:%d |",walker->vehicleID,walker->make,walker->model,walker->year,walker->mileage,walker->cost);
 }
 else if(flag == 0){
  printf("\nThis vehicle doesn't exist.\n");
 }
}//else

}

void bubble_sort(node*head){

node* help=NULL,*store=head;
int swap_id;
char swap_make[10];//ex:Mercedes
    char swap_model[10];//ex:E220
    int swap_year;//ex:2002
    int swap_mileage;//ex:180000
    int swap_cost;//ex:$16000

  while(head){
help=store;
while(help){
 if(help->next && help->vehicleID > help->next->vehicleID){

        //swap id//
 swap_id=help->vehicleID;
 help->vehicleID=help->next->vehicleID;
 help->next->vehicleID=swap_id;
 //swap year//
 swap_year=help->year;
 help->year=help->next->year;
 help->next->year=swap_year;
        //swap mileage//
 swap_mileage=help->mileage;
 help->mileage=help->next->mileage;
 help->next->mileage=swap_mileage;
        //swap cost//
 swap_cost=help->cost;
 help->cost=help->next->cost;
 help->next->cost=swap_cost;
 //swap make//
 strcpy(swap_make,help->make);
 strcpy(help->make,help->next->make);
 strcpy(help->next->make,swap_make);
 //swap model//
 strcpy(swap_model,help->model);
 strcpy(help->model,help->next->model);
 strcpy(help->next->model,swap_model);



 }

      //Move next node of linked list
 help=help->next;
}

    //Move next node of linked list
head=head->next;
  }

}
void display_LL_file(node* head,FILE *fp){
node* walker;
walker=head;

fp=fopen("cars.txt","w");
if(head == NULL){
 
 fprintf(fp,"The list is empty");
}
else{
 fprintf(fp,"\n-The cars are:\n\n");
 while(walker!=NULL){
  fprintf(fp," ==> VehicleID: %d | Make:%s | Model:%s | Year:%d | Mileage:%d | Cost:%d |",walker->vehicleID,walker->make,walker->model,walker->year,walker->mileage,walker->cost);
  fprintf(fp,"\n");
  fprintf(fp, "\t\t        *********************************************\n");
  walker=walker->next;
 }
 
 
}
fclose(fp);
}

void exit_fun(){
printf("\n\t\t\t\t\t   *Thank you for using our program*\n\t\t\t\t\t\t\t*GoodBye*\n");
}