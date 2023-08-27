//declaration of all the header files used
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<time.h>

//!-------------------------------------------------------------------------

//Helper functions

//reads from keypress and doesnt echo
char getch(void){
    struct termios oldattr,newattr;
    char ch;
    tcgetattr(STDIN_FILENO,&oldattr);
    newattr=oldattr;
    newattr.c_lflag &=~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newattr);
    ch=getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldattr);
    return ch;
}

//Adds a divider 
void divider(){
    for(int i=0;i<50;i++){
        printf("-");
    }
    printf("\n");

}

//!-------------------------------------------------------------------------

//declarartion of structure account
struct account{
    char first_name[30];
    char last_name[30];
    char username[50];
    char gender;
    char DOB[12];
    char pass1[30];
};

//!-------------------------------------------------------------------------

//all the function prototypes are declared here
int menu();
void signup();
void login();
void change_password();
void delete_account();
int check_username(char user[]);
//!-------------------------------------------------------------------------

int main(){
    while(1){
        system("clear");
        switch(menu()){
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                change_password();
                break;
            case 4:
                delete_account();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid Option\n");
                break;
        }
    }


    return 0;
}

//!-------------------------------------------------------------------------

//All the function definations are here
int menu(){
    int choice;
    printf("\n***************MAIN MENU***************\n");
    divider();
    printf("1.Signup\n");
    printf("2.Login\n");
    printf("3.Change Password\n");
    printf("4.Delete Account\n");
    printf("5.Exit\n");
    divider();
    printf("Enter Your Choice : ");
    scanf("%d",&choice);
    return choice;
}

//!-------------------------------------------------------------------------

void take_password(char pass[30]){
    int i=0;
    char ch;
    while(1){
        ch=getch();
        if( ch==10 ){ 
            pass[i]='\0';
            break;
        }else if( ch==127 && i>0){
                i--;
                printf("\b \b");
        }else if ( ch==9 || ch==32 ){
            continue;
        }else{
            pass[i++]=ch;
            printf("*");
        }
    }
}

//!-------------------------------------------------------------------------

void signup(){
    struct account temp;
    system("clear");
    char pass2[30];

    printf("Creating New Account\n");
    divider();
    printf("Enter Your First Name : ");
    scanf("%s",temp.first_name);
    printf("Enter Your Last Name : ");
    scanf("%s",temp.last_name);
    again:
    printf("Enter Your Username : ");
    scanf("%s",temp.username);
    if(check_username(temp.username)){
        printf("Username already exists..... Choose a different username\n");
        goto again;
    }
    while((getchar()) != '\n');
    printf("Enter your gender(f/m/o) : ");
    scanf("%c",&temp.gender);
    while((getchar())!='\n');
    printf("Enter your DOB(dd/mm/yyyy) : ");
    scanf("%s",temp.DOB);
    
    while((getchar()) != '\n');
    printf("Enter your Password : ");
    take_password(temp.pass1);
    printf("\n");

conf_pass:
    printf("Confirm Password : ");
    take_password(pass2);
    printf("\n");
    
    if(strcmp(temp.pass1,pass2)){
        printf("###############| Incorrect Password |###############\n");
        goto conf_pass;
    }else{
        printf("Account Created Successfully\n");
        getch();
        char* file="./records/account.txt";
        FILE *fp=fopen(file,"a");
        fprintf(fp,"%s %s %s %c %s %s\n",temp.first_name,temp.last_name,temp.username,temp.gender,temp.DOB,temp.pass1);
        fclose(fp);
    }
}

//!------------------------------------------------------------------------

int check_username(char user[]){
    char command[200]={0};
    sprintf(command,"./scripts/check_username.sh %s",user);
    system(command);
    char* file="./records/exist.txt";
    FILE* fp=fopen(file,"r");
    int check;
    fscanf(fp,"%d",&check);
    return check;
}

//!-------------------------------------------------------------------------

void login(){
    system("clear");
    char user[50],log_pass[30];
    struct account temp;
    name:
    printf("Enter Username : ");
    scanf("%s",user);
    if(!check_username(user)){
        printf("###############| Username does not exist |###############\n");
        goto name;
    }else{
        char command[200]={0};
        sprintf(command,"./scripts/current_user.sh %s",user);
        system(command);
        char* file="./records/exist.txt";
        FILE* fp=fopen(file,"r");
        fscanf(fp,"%s %s %s %c %s %s",temp.first_name,temp.last_name,temp.username,&temp.gender,temp.DOB,temp.pass1);
        while((getchar()) != '\n');
    logpass:
        printf("Enter password : ");
        take_password(log_pass);
        if(strcmp(temp.pass1,log_pass)){
            printf("\n################| Incorrect Password |###############\n");
            goto logpass;
        }else{
            system("clear");
            if(temp.gender=='m' || temp.gender=='M'){
                printf("\n****************Welcome Mr.%s %s****************",temp.first_name,temp.last_name);
            }else if(temp.gender=='f' || temp.gender=='F'){
                 printf("\n****************Welcome Ms.%s %s****************",temp.first_name,temp.last_name);
            }else{
                printf("\n****************Welcome %s %s****************",temp.first_name,temp.last_name);
            }
            
            printf("\nYour Details\n");
            
            divider();
            printf("\nusername     : %s\n",temp.username);
            printf("\nFirst name   : %s\n",temp.first_name);
            printf("\nLast name    : %s\n",temp.last_name);
            printf("\nDOB          : %s\n",temp.DOB);
            printf("\npassword     : %s\n",temp.pass1);
            
            }
            fclose(fp);
            getch();
        }
}

//!------------------------------------------------------------------------

void change_password(){
    system("clear");
    char user[50];
    repeat:
    printf("\nPlease enter your username : ");
    scanf("%s",user);
    if(!check_username(user)){
        printf("###############| Username does not exist |###############");
        goto repeat;
    }
    while((getchar()) != '\n');
    int num1,num2;
    srand(time(0));

    number:
        num1=(rand())/10000;
        printf("\nThe OTP is %d\n",num1);
        printf("Enter the OTP : ");
        scanf("%d",&num2);

        while((getchar()) != '\n');
        if(num1==num2){
            struct account temp;
            char command1[200]={0};
            char command2[200]={0};

            sprintf(command1,"./scripts/current_user.sh %s",user);
            system(command1);

            char* file="./records/exist.txt";
            FILE* fp=fopen(file,"r");
            fscanf(fp,"%s %s %s %c %s %s",temp.first_name,temp.last_name,temp.username,&temp.gender,temp.DOB,temp.pass1);
            
            
            char pass2[30],current_pass[30];
            put_pass:
            printf("Enter the current password : ");
            take_password(current_pass);
            if(strcmp(temp.pass1,current_pass)){
                printf("\n###############| INCORRECT PASSWORD |###############\n");
                goto put_pass;
            }
            
            
            printf("\nEnter new password : ");
            take_password(temp.pass1);
            pass:
                printf("\nConfirm new password :");
                take_password(pass2);
                if(strcmp(temp.pass1,pass2)){
                    printf("\n###############| INCORRECT PASSWORD |###############\n");
                goto pass;
                }else{
                    sprintf(command2,"./scripts/delete.sh %s",user);
                    system(command2);
                    file="./records/account.txt";
                    fp=fopen(file,"a");
                    fprintf(fp,"%s %s %s %c %s %s\n",temp.first_name,temp.last_name,temp.username,temp.gender,temp.DOB,pass2);
                    fclose(fp);
                    
                    printf("\n**********PASSWORD RESET SUCCESSFUL**********\n");
                    getch();
                }
        }else{
            printf("###############| Please enter correct OTP |###############\n");
            goto number;
        }

}

//!-------------------------------------------------------------------------

void delete_account(){
    struct account temp;
    char user[50],pass[30];
    repeat:
    system("clear");
    printf("Enter the username : ");
    scanf("%s",user);
    if(!check_username(user)){
        printf("\n###############| Username does not exist |###############\n");
        goto repeat;
    }
    char command1[200]={0};
    char command2[200]={0};
    sprintf(command1,"./scripts/current_user.sh %s",user);
    system(command1);
    
    char* file="./records/exist.txt";
    FILE* fp=fopen(file,"r");
    fscanf(fp,"%s %s %s %c %s %s",temp.first_name,temp.last_name,temp.username,&temp.gender,temp.DOB,temp.pass1);
    while( (getchar()) != '\n');
    pass:
    printf("Enter password : ");
    take_password(pass);
    if(strcmp(temp.pass1,pass)){
        printf("\n###############| INCORRECT PASSWORD |###############\n");
        goto pass;
    }
    char choice;
    again:
        printf("\nARE YOU SURE[Y/N] : ");
        scanf("%c",&choice);
        while((getchar()!='\n'));
        if(choice=='y' || choice=='Y'){
            sprintf(command2,"./scripts/delete.sh %s",user);
            system(command2);
            printf("***************ACCOUNT TERMINATION SUCCESSFUL***************\n");
            getch();
        }else if(choice=='n' || choice=='N'){
            printf("***************ACCOUNT TERMINATION ABORTED***************\n");
            getch();
        }else{
            printf("###############| Invalid option |###############");
            goto again;
        }
    fclose(fp);
}
//#-------------------------------------------------------------------------
