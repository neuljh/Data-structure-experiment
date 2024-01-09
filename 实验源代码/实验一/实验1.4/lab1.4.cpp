#include <stdio.h>
#include <stdlib.h>

typedef struct Elemtype{
    void* type;
}Elemtype;

typedef struct DCLNode{
    Elemtype data;
    struct DCLNode* next;
    struct DCLNode* pre;
}DCLNode,*DCLinkedlist;

int Init_list(DCLinkedlist &list,char* input);
void Display(const DCLinkedlist &list);
int length(DCLinkedlist &list);
int size_cmp(DCLinkedlist &a,DCLinkedlist &b);
void sub_list(DCLinkedlist &a,DCLinkedlist &b);
void add_list(DCLinkedlist &a,DCLinkedlist &b);
void run_caculate(DCLinkedlist &a,DCLinkedlist &b);

int Init_list(DCLinkedlist &list,char* input){
    list=(DCLinkedlist)malloc(sizeof(DCLNode));
    list->next= NULL;
    list->pre=NULL;
    if(list==NULL){
        return 0;
    }
    int i=0;
    DCLNode* p=list;
    if(input[i]=='-'){
        Elemtype e;
        e.type=(int*)malloc(sizeof(int));
        *(int*)e.type=1;
        list->data=e;
        i++;
    }else{
        Elemtype e;
        e.type=(int*)malloc(sizeof(int));
        *(int*)e.type=0;
        list->data=e;
    }
    while(input[i]!='\0'){
        int index=0;
        char temp[5]="";
        //char temp[5];
        while(input[i]!=','&&input[i]!='\0'){
            temp[index++]=input[i++];
        }
        int data=atoi(temp);
        DCLinkedlist newnode=(DCLinkedlist)malloc(sizeof(DCLNode));
        newnode->next=NULL;
        newnode->pre=NULL;
        Elemtype e;
        e.type=(int*)malloc(sizeof(int));
        // if(*(int*)list->data.type==1){
        //     data=-data;
        // }
        *(int*)e.type=data;
        newnode->data=e;
        p->next=newnode;
        newnode->pre=p;
        p=newnode;
        if(input[i]==','){
            i++;
            continue;
        }
        if(input[i]=='\0'){
            p->next=list;
            list->pre=p;
            break;
        }
        
    }
    return 1;
}

void Display(const DCLinkedlist &list){
    DCLinkedlist p,q;
    p=list;
    q=list;
    p=p->next;
    q=q->next;
    int sum=0;
    while(p!=list){
        sum=sum+*(int*)p->data.type;
        p=p->next;
    }
    if(sum==0){
        printf("%d",sum);
        return;
    }
    if(*(int*)list->data.type==1){
        printf("-");
    }
    while(q->next!=list){
        if(*(int*)q->data.type==0){
            printf("0000,");
        }else{
            if(list->next!=q){
                int times=0;
                if(0<*(int*)q->data.type&&*(int*)q->data.type<10){
                    times=3;
                }
                if(9<*(int*)q->data.type&&*(int*)q->data.type<100){
                    times=2;
                }
                if(99<*(int*)q->data.type&&*(int*)q->data.type<1000){
                    times=1;
                }
                for(int index=0;index<times;index++){
                    printf("0");
            }
            }
            printf("%d",*(int*)q->data.type);
            printf(",");
        }
        q=q->next;
    }
    if(*(int*)q->data.type==0){
        printf("0000");
    }else{
        int times=0;
        if(0<*(int*)q->data.type&&*(int*)q->data.type<10){
            times=3;
        }
        if(9<*(int*)q->data.type&&*(int*)q->data.type<100){
            times=2;
        }
        if(99<*(int*)q->data.type&&*(int*)q->data.type<1000){
            times=1;
        }
        for(int index=0;index<times;index++){
            printf("0");
        }
        printf("%d",*(int*)q->data.type);
    }   

}
int length(DCLinkedlist &list){
    DCLinkedlist p=list;
    p=p->next;
    int leng=0;
    while(p!=list){
        leng++;
        p=p->next;
    }
    return leng;
}

int size_cmp(DCLinkedlist &a,DCLinkedlist &b){
    if(length(a)!=length(b)){
        return 0;
    }else{
        DCLinkedlist starta=a->next;
        DCLinkedlist startb=b->next;
        while(starta!=a&&startb!=b){
            if(*(int*)starta->data.type<*(int*)startb->data.type){
                return 0;
            }else{
                return 1;
            }
        }

    }
    return 1;
}

void sub_list(DCLinkedlist &a,DCLinkedlist &b){
    DCLinkedlist enda=a->pre;
    DCLinkedlist endb=b->pre;
    int borrow=0;
    if(length(a)>length(b)||size_cmp(a,b)){
        while(enda!=a&&endb!=b){
            *(int*)enda->data.type=*(int*)enda->data.type-*(int*)endb->data.type-borrow;
            borrow=0;
            if(*(int*)enda->data.type<0){
                *(int*)enda->data.type=*(int*)enda->data.type+10000;
                borrow=1;
            }
            enda=enda->pre;
            endb=endb->pre;
        }
        while(enda!=a){
            *(int*)enda->data.type=*(int*)enda->data.type-borrow;
            borrow=0;
            if(*(int*)enda->data.type<0){
                *(int*)enda->data.type=*(int*)enda->data.type+10000;
                borrow=1;
            }
            enda=enda->pre;
        }
        
        while(*(int*)a->next->data.type==0&&a->next->next!=a){
            a->next=a->next->next;
            a->next->pre=a;
        }
        Display(a);
    }
    if(length(a)<length(b)||size_cmp(b,a)){
        while(enda!=a&&endb!=b){
            *(int*)endb->data.type=*(int*)endb->data.type-*(int*)enda->data.type-borrow;
            borrow=0;
            if(*(int*)endb->data.type<0){
                *(int*)endb->data.type=*(int*)endb->data.type+10000;
                borrow=1;
            }
            enda=enda->pre;
            endb=endb->pre;
        }
        while(endb!=b){
            *(int*)endb->data.type=*(int*)endb->data.type-borrow;
            borrow=0;
            if(*(int*)endb->data.type<0){
                *(int*)endb->data.type=*(int*)endb->data.type+10000;
                borrow=1;
            }
            endb=endb->pre;
        }
        
        while(*(int*)b->next->data.type==0&&b->next->next!=b){
            b->next=b->next->next;
            b->next->pre=b;
        }
        Display(b);
    }
}

void add_list(DCLinkedlist &a,DCLinkedlist &b){
    DCLinkedlist enda=a->pre;
    DCLinkedlist endb=b->pre;
    int carry=0;
    if(length(a)>=length(b)){
        while(enda!=a&&endb!=b){
            *(int*)enda->data.type=*(int*)enda->data.type+*(int*)endb->data.type+carry;
            carry=0;
            if(*(int*)enda->data.type>=10000){
                *(int*)enda->data.type=*(int*)enda->data.type-10000;
                carry=1;
            }
            enda=enda->pre;
            endb=endb->pre;
        }
        while(enda!=a){
            *(int*)enda->data.type=*(int*)enda->data.type+carry;
            carry=0;
            if(*(int*)enda->data.type>=10000){
                *(int*)enda->data.type=*(int*)enda->data.type-10000;
                carry=1;
            }
            enda=enda->pre;
        }
        if(carry==1){
            DCLinkedlist newnode=(DCLinkedlist)malloc(sizeof(DCLNode));
            newnode->next=NULL;
            newnode->pre=NULL;
            Elemtype e;
            e.type=(int*)malloc(sizeof(int));
            *(int*)e.type=carry;
            newnode->data=e;

            newnode->next=a->next;
            a->next->pre=newnode;
            newnode->pre=a;
            a->next=newnode;
        }
        Display(a);
    }else{
        while(enda!=a&&endb!=b){
            *(int*)endb->data.type=*(int*)enda->data.type+*(int*)endb->data.type+carry;
            carry=0;
            if(*(int*)endb->data.type>=10000){
                *(int*)endb->data.type=*(int*)endb->data.type-10000;
                carry=1;
            }
            enda=enda->pre;
            endb=endb->pre;
        }
        while(endb!=b){
            *(int*)endb->data.type=*(int*)endb->data.type+carry;
            carry=0;
            if(*(int*)endb->data.type>=10000){
                *(int*)endb->data.type=*(int*)endb->data.type-10000;
                carry=1;
            }
            endb=endb->pre;
        }
        if(carry==1){
            DCLinkedlist newnode=(DCLinkedlist)malloc(sizeof(DCLNode));
            newnode->next=NULL;
            newnode->pre=NULL;
            Elemtype e;
            e.type=(int*)malloc(sizeof(int));
            *(int*)e.type=carry;
            newnode->data=e;

            newnode->next=b->next;
            b->next->pre=newnode;
            newnode->pre=b;
            b->next=newnode;
        }
        Display(b);
    }
}

void run_caculate(DCLinkedlist &a,DCLinkedlist &b){
    if(*(int*)a->data.type==*(int*)b->data.type){
        add_list(a,b);
    }else{
        sub_list(a,b);
    }
}
int main(){
    DCLinkedlist a;
    DCLinkedlist b;
    char caa[]="34,5544,5367";
    char cba[]="-5,5443,5333";
    char* ca=&caa[0];
    char* cb=&cba[0];
    Init_list(a,ca);
    Init_list(b,cb);
    run_caculate(a,b);
    system("pause");
}