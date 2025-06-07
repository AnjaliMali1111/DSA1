#include<stdio.h>
#include<string.h>
#define MAX 5

typedef struct 
{
    int ti_id;
    char scr[20];
    char des[20];
}tick;

tick tic[MAX];
int f =-1;
int r = -1;
 
 int isFull()
 {
    return(r+1)%MAX ==f;
 }
int isEmpty()
{
    return f==-1;
}
void  equeue( int ti_id,char scr[],char des[])
{
    if(isFull())
    {
        printf("full");
    }
    if(isEmpty())
    {
        f=0;
    }
       r = (r + 1) % MAX;
        tic[r].ti_id=ti_id;
       strcpy(tic[r].scr,scr);
       strcpy(tic[r].des,des);
        printf("adding %d from (%s to %s)\n",ti_id, scr,des);
    
}


  void dequeue()
  {
    
    if(isEmpty())
   {
     printf("Queue is empty! No tickets to process.\n");
        return;
   }
   printf("Processing ticket %d (From %s to %s).\n",
           tic[f].ti_id,tic[f].scr,tic[f].des);
   if(f==r)
    {
        f=r=-1;
    }
    else{
        
        f=(f+1)%MAX;
    }

  }
 void display()
 {

    
   int i = f;
   while(1)
   {
     printf("tic id :%d,(src %s to des %s)\n",tic[i].ti_id,tic[i].scr,tic[i].des);
     if(i == r)
     {
        break;
     }
     i=(i+1)%MAX;   }

 }



void main()
{
    int ch,ti_id;
    char src[20];
    char des[20];


   do{
       
    printf("\n 1.Add\n 2.delete \n 3. display\n4.exit");
    printf("\n enter the choice");
    scanf("%d",&ch);

    switch(ch)
    {
        case 1: printf("enter the ticket id\n");
        scanf("%d",&ti_id);
        printf("src\n");
        scanf("%s",src);
        printf("des\n");
        scanf("%s",des);
        equeue(ti_id,src,des);
        break;
        case 2:
        dequeue();
        break;
        case 3:
        display();
        break;
        case 4:
        break;
        default:
        printf("bye");
    }

   }while(ch!=4);

}