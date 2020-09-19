#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct LinkedList{
    char username[50];
    char password[10];
    int status;
    struct LinkedList *next;
 };
 
typedef struct LinkedList *node; //Từ giờ dùng kiểu dữ liệu LinkedList có thể thay bằng node cho ngắn gọn
 
node CreateNode(char username[], char password[], int status){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct LinkedList)); // Cấp phát vùng nhớ dùng malloc()
    temp->next = NULL;// Cho next trỏ tới NULL
    temp->status = status; // Gán giá trị cho Node
    strcpy(temp->username,username);
    strcpy(temp->password,password);
    return temp;//Trả về node mới đã có giá trị
}

node AddTail(node head, char username[], char password[], int status){
    node temp,p;// Khai báo 2 node tạm temp và p
    temp = CreateNode(username,password,status);//Gọi hàm createNode để khởi tạo node temp có next trỏ tới NULL và giá trị là value
    if(head == NULL){
        head = temp;     //Nếu linked list đang trống thì Node temp là head luôn
    }
    else{
        p  = head;// Khởi tạo p trỏ tới head
        while(p->next != NULL){
            p = p->next;//Duyệt danh sách liên kết đến cuối. Node cuối là node có next = NULL
        }
        p->next = temp;//Gán next của thằng cuối = temp. Khi đó temp sẽ là thằng cuối(temp->next = NULL mà)
    }
    return head;
}

node InitHead(){
    node head;
    head = NULL;
    return head;
}

int Search(node head, char username[]){
    int position = 0;
    for(node p = head; p != NULL; p = p->next){
        if(strcmp(username,p->username)==0){
            return position;
        }
        ++position;
    }
    return -1;
}

node readfile(node head)
{
    FILE *f;
    f = fopen("account.txt","r");
    char c;
    while (c != EOF)
    {
        char username_tmp[50];
        char password_tmp[10];
        int status_tmp;
        fscanf(f,"%s %s %d",username_tmp,password_tmp,&status_tmp);
        head = AddTail(head,username_tmp,password_tmp,status_tmp);
        c = fgetc(f);
    }
    
    fclose(f);
    return head;
}

void print_account(node head)
{
    for(node p = head; p != NULL; p = p->next){
        printf("%s %s %d\n",p->username,p->password,p->status);
    }
}

void menu()
{
    printf("USER MANAGEMENT PROGRAM\n");
    printf("---------------------------------------------\n");
    printf("\t1. Register\n");
    printf("\t2. Sign in\n");
    printf("\t3. Search\n");
    printf("\t4. Sign out\n");
    printf("Your choice (1-4, other to quit):");
}

void Register(node head)
{
    char username[50], password[10];
        do
        {
            printf("Nhap username:");
            scanf("%s",username);
            printf("Nhap password:");
            scanf("%s",password);
            if (Search(head,username)==-1)
            {
                head = AddTail(head,username,password,1);
                
                break;
            }
            else printf("Username already existed!\n");
        } while (1);
}

int main()
{
    node head = InitHead();
    head = readfile(head);
    menu();
    int choice;
    scanf("%d",&choice);
    if (choice == 1)
        Register(head);
    return 0;
}