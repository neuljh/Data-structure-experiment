#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include<limits.h>
#include<string.h>

typedef struct SElemtype{
    void* type;
}Elemtype;

typedef struct LNode{
    Elemtype data;
    struct LNode* next;
}LNode,*LinkStack;

void Init_stack(LinkStack &stack);
int Isempty_stack(LinkStack &stack);
int push_stack(LinkStack &stack,SElemtype e);
SElemtype pop_stack(LinkStack &stack);
SElemtype top_stack(LinkStack &stack);
int priority(char c);
int number_of_brackets(char* s,int length);
char* Infix_to_Postfix(char* infix,int length);
int char_match(char ch);
int caclulate_Postfix(char* s,int length);

void Init_stack(LinkStack &stack){
    stack=(LinkStack)malloc(sizeof(LNode));
    stack->next=NULL;
}

int Isempty_stack(LinkStack &stack){
    return (stack->next==NULL?1:0);
}

int push_stack(LinkStack &stack,SElemtype e){
    LNode *temp=(LinkStack)malloc(sizeof(LNode));
    if(!temp){
        return -1;
    }
    temp->next=NULL;
    temp->data=e;
    temp->next=stack->next;
    stack->next=temp;
    return 1;

}

SElemtype pop_stack(LinkStack &stack){
    if(Isempty_stack(stack)){
        exit(-1);
    }else{
        LNode* temp=stack->next;
        SElemtype e;
        stack->next=temp->next;
        temp->next=NULL;
        e=temp->data;
        free(temp);
        return e;
    }
}

SElemtype top_stack(LinkStack &stack){
    if(Isempty_stack(stack)){
        exit(-1);
    }
    return stack->next->data;
}

int priority(char c){
    int res;
    switch(c){
        case '+':
            res=1;
            break;
        case '-':
            res=1;
            break;
        case '*':
            res=2;
            break;
        case '/':
            res=2;
            break;
        case '(':
            res=0;
            break;
        case '[':
            res=0;
            break;
        case '{':
            res=0;
            break;
        case '#':
            res=0;
            break;
        default:
            res=-1;
            break;
    }
    return res;
}



int number_of_brackets(char* s,int length){
    int i=0;
    int res=0;
    while(i<length){
        if(s[i]=='('||s[i]==')'||s[i]=='['||s[i]==']'||s[i]=='{'||s[i]=='}'){
            res++;
        }
        i++;
    }
    return res;
}

char* Infix_to_Postfix(char* infix,int length){
    LinkStack stack;
    Elemtype e;
    e.type=(char*)malloc(sizeof(char));
    *(char*)e.type='#';
    Init_stack(stack);
    push_stack(stack,e);
    char res[1024];
    char* re = (char*)malloc((length-number_of_brackets(infix,strlen(infix))) * sizeof(char));
    int i=0;
    int j=0;
    char ch=infix[i];
    while(ch!='\0'){
        switch(ch){
            case '+':
            case '-':
            case '*':
            case '/':
                while(priority(*(char*)top_stack(stack).type)>=priority(ch)){
                    res[j]=*(char*)pop_stack(stack).type;
                    j++;
                    // i++;
                    // ch=infix[i];
                }
                Elemtype e1;
                e1.type=(char*)malloc(sizeof(char));
                *(char*)e1.type=ch;
                push_stack(stack,e1);
                i++;
                ch=infix[i];
                break;
            case '(':
            case '[':
            case '{':
                Elemtype e2;
                e2.type=(char*)malloc(sizeof(char));
                *(char*)e2.type=ch;
                push_stack(stack,e2);
                i++;
                ch=infix[i];
                break;
            case ')':
                while(*(char*)top_stack(stack).type!='('){
                    res[j]=*(char*)pop_stack(stack).type;
                    j++;
                }
                i++;
                ch=infix[i];
                pop_stack(stack);
                break;
            case ']':
                while(*(char*)top_stack(stack).type!='['){
                    res[j]=*(char*)pop_stack(stack).type;
                    j++;
                }
                i++;
                ch=infix[i];
                pop_stack(stack);
                break;
            case '}':
                while(*(char*)top_stack(stack).type!='('){
                    res[j]=*(char*)pop_stack(stack).type;
                    j++;
                }
                pop_stack(stack);
                i++;
                ch=infix[i];
                break;
            default:
                res[j]=ch;
                i++;
                j++;
                ch=infix[i];
                break;

        }
    }
    while(!Isempty_stack(stack)){
        res[j++]=*(char*)pop_stack(stack).type;
    }
    int index=0;
    while(index<strlen(res)&&res[index]!='#'){
        re[index]=res[index];
        index++;
    }
    char* p=re;
    return p;
}

int char_match(char ch){
    int sign=0;
    if(ch>='0'&&ch<='9'){
        sign=1;
    }
    if(ch=='+'){
        sign=2;
    }
    if(ch=='-'){
        sign=3;
    }
    if(ch=='*'){
        sign=4;
    }
    if(ch=='/'){
        sign=5;
    }
    return sign;
}

int caclulate_Postfix(char* s,int length){
    LinkStack stack;
    Init_stack(stack);
    int index=0;
    while(index<length){
        if(char_match(s[index])==1){
            Elemtype e;
            e.type=(int*)malloc(sizeof(int));
            *(int*)e.type=(s[index]-'0');
            push_stack(stack,e);
            index++;
        }else{
            int temp2=*(int*)pop_stack(stack).type;
            int temp1=*(int*)pop_stack(stack).type;
            Elemtype e1;
            e1.type=(int*)malloc(sizeof(int));
            if(char_match(s[index])==2){
                *(int*)e1.type=temp1+temp2;
            }
            if(char_match(s[index])==3){
                *(int*)e1.type=temp1-temp2;
            }
            if(char_match(s[index])==4){
                *(int*)e1.type=temp1*temp2;
            }
            if(char_match(s[index])==5){
                *(int*)e1.type=temp1/temp2;
            }
            push_stack(stack,e1);
            index++;

        }
    }
    return *(int*)top_stack(stack).type;
}




int main(){
    char input[1024];
    printf("Please enter a valid arithmetic expression:\n");
    scanf("%s",input);//读取表达式
    char *pinput=input;
    printf("The expression you entered is:\n");
    printf("%s\n",pinput);
    int num=number_of_brackets(pinput,strlen(pinput));
    char *ss=new char;
    ss=Infix_to_Postfix(pinput,strlen(pinput));
    printf("The converted postfix expression is:\n");
    printf("%s\n",ss);
    printf("The expression you entered evaluates to:\n");
    printf("%d",caclulate_Postfix(ss,strlen(input)-num));//需要减去括号的数量！！！-num
    system("pause");
    system("pause");
}
// 中缀表达式a + b*c + (d * e + f) * g，其转换成后缀表达式则为a b c * + d e * f  + g * +。

// 转换过程需要用到栈，具体过程如下：

// 1）如果遇到操作数，我们就直接将其输出。

// 2）如果遇到操作符，则我们将其放入到栈中，遇到左括号时我们也将其放入栈中。

// 3）如果遇到一个右括号，则将栈元素弹出，将弹出的操作符输出直到遇到左括号为止。注意，左括号只弹出并不输出。

// 4）如果遇到任何其他的操作符，如（“+”， “*”，“（”）等，从栈中弹出元素直到遇到发现更低优先级的元素(或者栈为空)为止。弹出完这些元素后，才将遇到的操作符压入到栈中。有一点需要注意，只有在遇到" ) "的情况下我们才弹出" ( "，其他情况我们都不会弹出" ( "。

// 5）如果我们读到了输入的末尾，则将栈中所有元素依次弹出。




// char* Infix_to_Postfix(char* infix,int length){
//     LinkStack stack;
//     SElemtype e;
//     e.type=(char*)malloc(sizeof(char));
//     *(char*)e.type='#';
//     Init_stack(stack);
//     push_stack(stack,e);
//     char res[length+1];
//     char re[length];
//     int i=0;
//     int j=0;
//     char ch=infix[i];
//     while(ch!='#'){
//         printf("%c\n",ch);
//         switch(ch){
//             case '+':
//             case '-':
//             case '*':
//             case '/':
//                 if(priority(*(char*)top_stack(stack).type)>=priority(ch)){
//                     res[j]=*(char*)top_stack(stack).type;
//                     j++;
//                     // i++;
//                     // ch=infix[i];
//                 }
//                 SElemtype e1;
//                 e1.type=(char*)malloc(sizeof(char));
//                 *(char*)e1.type=ch;
//                 push_stack(stack,e1);
//                 i++;
//                 ch=infix[i];
//                 break;
//             case '(':
//             case '[':
//             case '{':
//                 SElemtype e2;
//                 e2.type=(char*)malloc(sizeof(char));
//                 *(char*)e2.type=ch;
//                 push_stack(stack,e2);
//                 i++;
//                 ch=infix[i];
//                 break;
//             case ')':
//                 while(*(char*)top_stack(stack).type!='('){
//                     res[j]=*(char*)pop_stack(stack).type;
//                     j++;
//                 }
//                 break;
//             case ']':
//                 while(*(char*)top_stack(stack).type!='['){
//                     res[j]=*(char*)pop_stack(stack).type;
//                     j++;
//                 }
//                 break;
//             case '}':
//                 while(*(char*)top_stack(stack).type!='('){
//                     res[j]=*(char*)pop_stack(stack).type;
//                     j++;
//                 }
//                 break;
//             default:
//                 res[j]=ch;
//                 i++;
//                 j++;
//                 ch=infix[i];
//                 break;

//         }
//     }
//     while(!Isempty_stack(stack)){
//         res[j++]=*(char*)pop_stack(stack).type;
//     }
//     int index=0;
//     while(index<length){
//         re[index]=res[index];
//     }
//     char* p=re;
//     return p;
// }