#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>
struct timeval tm;
typedef struct Set {
    int data;
    struct Set* next;
} Set;



Set* newSet(int data) {
    Set* set = (Set*)malloc(sizeof(Set));
    if(set != NULL){
        set->data = data;
        set->next = NULL;
    }
    else{
        printf("failed to create set!\n");
        return 0;
    }
    return set;
}

void OrderlyAddittion(Set* i, int d){
    Set* temp = NULL;
    temp = i;
    do{
        if(d < i->data){
            break;
        }
        else if((temp->data < d) && (temp->next->data < d)){
            temp = temp->next;
        }
        else if((temp->data < d) && (temp->next->data > d)){
            Set* set = (Set*)malloc(sizeof(Set));
            if(set != NULL){
            set->data = d;
            set->next = temp->next;
            temp->next = set;
            break;
            }
         }
        else if((temp->data == d) || (temp->next->data == d)){
            break;
        }
    }while(1);
}

Set* Append(Set* i, Set* f, int c){
    if (f->next == NULL){
        f->next = (Set*)malloc(sizeof(Set));
        f->next->data = c;
        f = f->next;
        f->next = NULL;
        return f;
    }
    else if(f->next != NULL){
        printf("f is not the final node! %d\n",f->next->data);
        return f;
    }
}
void printSet(Set* i, char* c){
    printf("Set %s contents: {",c);
    do{
        if(i->next != NULL){
        printf("%d,",i->data);
        }
        else{
            printf("%d",i->data);
        }
        i = i->next;
    }while(i != NULL);
    printf("}\n");
}
Set* generateRandomOrderedSet(Set* i, Set* f, int length,int seed){
    int counter = 0;
    int r_1 = 0;
    int r_2 = 0;
    int r_3 = 0;
    mingw_gettimeofday(&tm, NULL);
    srand(tm.tv_sec + tm.tv_usec * 1000000ul);
    do{
        r_1 = (rand());
        r_2 = (rand());
        r_3 = ((r_1*r_2)%100);
        if(f->data < r_3){
        f = Append(i,f,r_3);
        counter++;
        }
        else{
            Set* temp = NULL;
            temp = i;
            do{
                if(r_3 < i->data){
                    break;
                }
                else if((temp->data < r_3) && (temp->next->data < r_3)){
                    temp = temp->next;
                }
                else if((temp->data < r_3) && (temp->next->data > r_3)){
                    Set* set = (Set*)malloc(sizeof(Set));
                    if(set != NULL){
                    set->data = r_3;
                    set->next = temp->next;
                    temp->next = set;
                    counter++;
                    break;
                    }
                }
                else if((temp->data == r_3) || (temp->next->data == r_3)){
                    break;
                }
            }while(1);
        }
    }while(counter < length);
    return f;
}

Set* symDifMerge(Set* A,Set* B){
    Set* C = newSet(0);
    Set* c_f = C;
    Set* temp_a = A;
    Set* temp_b = B;

    do{
        if(temp_a->next != NULL && temp_b->next != NULL){
        if(temp_a->data == temp_b->data){
            temp_a = temp_a->next;
            temp_b = temp_b->next;
        }
        else if(temp_a->data > temp_b->data){
            do{
                if(temp_a->data > temp_b->data){
                    c_f = Append(C,c_f,temp_b->data);
                    temp_b = temp_b->next;
                }
                else if(temp_a->data == temp_b->data){
                    temp_b = temp_b->next;
                    temp_a = temp_a->next;
                    break;
                }
                else{
                    c_f = Append(C,c_f,temp_a->data);
                    temp_a = temp_a->next;
                    break;
                }
            }while(temp_a->data > temp_b->data && temp_b->next != NULL);
        }
        else if(temp_a->data < temp_b->data){
            do{
                if(temp_a->data < temp_b->data){
                    c_f = Append(C,c_f,temp_a->data);
                    temp_a = temp_a->next;
                }
                else if(temp_a->data == temp_b->data){
                    temp_a = temp_a->next;
                    temp_b = temp_b->next;
                }
                else{
                    c_f = Append(C,c_f,temp_b->data);
                    temp_b = temp_b->next;
                    break;
                }
            }while(temp_b->data > temp_a->data && temp_a->next != NULL);
        }
        }
        else if(temp_a->next != NULL && temp_b->next == NULL){
            do{
                if(temp_a->data > temp_b->data){
                    c_f = Append(C,c_f,temp_b->data);
                    do{
                        c_f = Append(C,c_f,temp_a->data);
                        temp_a = temp_a->next;
                    }while(temp_a->next != NULL);
                    c_f = Append(C,c_f,temp_a->data);
                }
                else if(temp_a->data == temp_b->data){
                    temp_a = temp_a->next;
                    if(temp_a->next==NULL){
                        c_f = Append(C,c_f,temp_a->data);
                    }
                    else{
                       do{
                        c_f = Append(C,c_f,temp_a->data);
                        temp_a = temp_a->next;
                    }while(temp_a->next != NULL);
                    c_f = Append(C,c_f,temp_a->data); 
                    }
                }
                else if(temp_a->data < temp_b->data){
                    do{
                        c_f = Append(C,c_f,temp_a->data);
                        temp_a = temp_a->next;
                    }while(temp_a->data < temp_b->data && temp_a->next != NULL);
                    if(temp_a->next == NULL){
                        if(temp_a->data < temp_b->data){
                            c_f = Append(C,c_f,temp_a->data);
                            c_f = Append(C,c_f,temp_b->data);
                        }
                        else if(temp_a->data == temp_b->data){
                            break;
                        }
                        else if(temp_a->data > temp_b->data){
                            c_f = Append(C,c_f,temp_b->data);
                            c_f = Append(C,c_f,temp_a->data);
                        }
                    }
                    else if(temp_a->next != NULL){
                        if(temp_a->data == temp_b->data){
                            temp_a = temp_a->next;
                            if(temp_a->next==NULL){
                                c_f = Append(C,c_f,temp_a->data);
                            }
                            else{
                            do{
                                c_f = Append(C,c_f,temp_a->data);
                                temp_a = temp_a->next;
                            }while(temp_a->next != NULL);
                                c_f = Append(C,c_f,temp_a->data); 
                            }
                        }
                        else{
                           do{
                                c_f = Append(C,c_f,temp_a->data);
                                temp_a = temp_a->next;
                            }while(temp_a->next != NULL);
                            c_f = Append(C,c_f,temp_a->data); 
                        }
                    }
                }
            }while(temp_a->next != NULL);
            }
        else if(temp_b->next != NULL && temp_a->next == NULL){
            do{
                if(temp_b->data > temp_a->data){
                    c_f = Append(C,c_f,temp_a->data);
                    do{
                        c_f = Append(C,c_f,temp_b->data);
                        temp_b = temp_b->next;
                    }while(temp_b->next != NULL);
                    c_f = Append(C,c_f,temp_b->data);
                }
                else if(temp_b->data == temp_a->data){
                    temp_b = temp_b->next;
                    if(temp_b->next==NULL){
                        c_f = Append(C,c_f,temp_b->data);
                    }
                    else{
                       do{
                        c_f = Append(C,c_f,temp_b->data);
                        temp_b = temp_b->next;
                    }while(temp_b->next != NULL);
                    c_f = Append(C,c_f,temp_b->data); 
                    }
                }
                else if(temp_b->data < temp_a->data){
                    do{
                        c_f = Append(C,c_f,temp_b->data);
                        temp_b = temp_b->next;
                    }while(temp_b->data < temp_a->data && temp_b->next != NULL);
                    if(temp_b->next == NULL){
                        if(temp_b->data < temp_a->data){
                            c_f = Append(C,c_f,temp_b->data);
                            c_f = Append(C,c_f,temp_a->data);
                        }
                        else if(temp_b->data == temp_a->data){
                            break;
                        }
                        else if(temp_b->data > temp_a->data){
                            c_f = Append(C,c_f,temp_a->data);
                            c_f = Append(C,c_f,temp_b->data);
                        }
                    }
                    else if(temp_b->next != NULL){
                        if(temp_b->data == temp_a->data){
                            temp_b = temp_b->next;
                            if(temp_b->next==NULL){
                                c_f = Append(C,c_f,temp_b->data);
                            }
                            else{
                            do{
                                c_f = Append(C,c_f,temp_b->data);
                                temp_b = temp_b->next;
                            }while(temp_b->next != NULL);
                                c_f = Append(C,c_f,temp_b->data); 
                            }
                        }
                        else{
                           do{
                                c_f = Append(C,c_f,temp_b->data);
                                temp_b = temp_b->next;
                            }while(temp_b->next != NULL);
                            c_f = Append(C,c_f,temp_b->data); 
                        }
                    }
                }
            }while(temp_b->next != NULL);
        }
    }
    while(temp_a->next != NULL || temp_b->next !=NULL);
    return C;
}

int main() {
    setlocale(LC_CTYPE, "Russian");
	system("chcp 1251");
    Set* A = newSet(1);
    Set* B = newSet(1);
    Set* A_f = A;
    Set* B_f = B;
    generateRandomOrderedSet(A,A_f,30,913);
    printSet(A,"A");
    generateRandomOrderedSet(B,B_f,30,404);
    printSet(B,"B");
    Set* C=symDifMerge(A,B);
    printSet(C,"C");
    return 0;
}
