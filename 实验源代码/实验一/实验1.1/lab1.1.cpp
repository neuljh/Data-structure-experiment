#include <stdio.h>
#include <stdlib.h>

typedef struct CLnode{
    int id;
    int key;
    struct CLnode* next;
}CLnode,*CLinklist;

void Create_Empty_CL(CLinklist &CL);
void Insert_Head_CL(int elem,CLinklist &CL,int pos);
void Insert_Tail_CL(int elem,CLinklist &CL,int idn);
void Display_CL(CLinklist &CL);
CLnode* Solution_Joseph(int m,int numperson,int* keyperson,CLinklist &CL);


void Create_Empty_CL(CLinklist &CL){
    CL=NULL;
}

void Insert_Head_CL(int elem,CLinklist &CL,int pos){
    int index=1;
    CLnode* p=CL;
    while(index<pos){
        p=p->next;
        index++;
    }
    CLnode* temp=(CLinklist)malloc(sizeof(CLnode));
    temp->key=elem;
    temp->next=NULL;
    temp->next=p->next;
    p->next=temp;
}

void Insert_Tail_CL(int elem,CLinklist &CL,int idn){
    //int idn=1;
    CLnode* temp=(CLinklist)malloc(sizeof(CLnode));
    temp->id=idn;
    temp->key=elem;
    temp->next=NULL;
    CLnode* p=CL;
    if(CL==NULL){
        p=temp;
        CL=temp;
        p->next=CL;
    }else{
        while(p->next!=CL){
            p=p->next;
        }
        temp->next=p->next;
        p->next=temp;
    }
    

}

void Display_CL(CLinklist &CL){
    CLnode* p=CL;
    if(p!=NULL){
        if(p->next==CL){
            printf("(%d,%d)",p->id,p->key);
        }else{
            printf("(%d,%d)",p->id,p->key);
            printf("->");
            p=p->next;
            while(p!=CL){
                
                printf("(%d,%d)",p->id,p->key);
                //printf("%d",p->key);
                if(p->next!=CL){
                    printf("->");
                }
                
                p=p->next;
            }
        }
        printf("\n");
    }else{
        exit(0);
    }
 
}

CLnode* Solution_Joseph(int m,int numperson,int* keyperson,CLinklist &CL){
    CLinklist res;
    Create_Empty_CL(res);
    Create_Empty_CL(CL);
    
    CLnode* op=res;
    int index;
    int id=1;
    // CL->id=id;
    // CL->key=keyperson[0];
    for(index=0;index<numperson;index++){
        Insert_Tail_CL(keyperson[index],CL,id+index);
    }
    CLnode* p=CL;
    CLnode* pre=CL;
    int times=1;
    //p=p->next;
    // int flag=0;
    while(pre->next!=p){
        pre=pre->next;
    }
    while(CL!=NULL){
        if(CL->next==CL){
            Insert_Tail_CL(CL->id,res,id++);
            break;
        }
        if(times==m){
            
            CLnode* temp=p;
            if(pre->next==CL){
                CL=CL->next;
                p=CL;
                pre->next=temp->next;
                temp->next=NULL;
                m=temp->key;
                times=1;
                Insert_Tail_CL(temp->id,res,id++);
                free(temp);
            }else{
                p=p->next;
                pre->next=temp->next;
                temp->next=NULL;
                m=temp->key;
                times=1;
                Insert_Tail_CL(temp->id,res,id++);
                free(temp);
            }
        }else{
            times++;
            p=p->next;
            while(pre->next!=p){
                pre=pre->next;
            }
        }
    }
    return res;
}

int main(){
    int m=20;
    int numperson=7;
    int a[7]={3,1,7,2,4,8,4};
    CLnode* l;
    int* p=&a[0];
    CLnode* res=Solution_Joseph(m,numperson,p,l);
    Display_CL(res);
    system("pause");
}