#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct customer
{
   char name[30];
   int age;
   char add[50];
   char contact[11];
   char accType[8];
   char accNo[15];
   char password[50];
   int balance;

}c;

FILE *fp = NULL;
void NewAcc(){
fp = fopen("bank management.std","ab");
if (fp == NULL)
{
   printf("error");
   exit(1);
}

printf("enter the name: ");
 fgets(c.name, sizeof(c.name),stdin);
 c.name[strcspn(c.name, "\n")] = '\0';
// // fwrite(&c.name,sizeof(c.name),1,fp);
// getchar();

printf("enter the age of candidate: ");
scanf("%d",&c.age);
// fwrite(&c.age,sizeof(c.age),1,fp);
getchar();

printf("enter the contact of candidate: ");
scanf("%s",c.contact);
// fwrite(&c.contact,sizeof(c.contact),1,fp);
getchar();

printf("enter the address of candidate: ");
fgets(c.add,sizeof(c.add),stdin);
// fwrite(&c.add,sizeof(c.add),1,fp);

printf("enter the account type(saving/current): ");
scanf("%s",c.accType);
// fwrite(&c.accType,sizeof(c.accType),1,fp);
getchar();

printf("enter the account no. :");
scanf("%s",c.accNo);
// fwrite(&c.accNo,sizeof(c.accNo),1,fp);
getchar();

printf("create the password: ");
scanf("%49s", c.password);

fwrite(&c,sizeof(struct customer),1,fp);


fclose(fp);


}

void Login(){
   char pass[50];
   char ac[16];
   int flag = 0;
    
   printf("enter the account no.: ");
   scanf("%15s",ac);
   
   printf("enter the password: ");
   scanf("%49s",pass);
   fp = fopen("bank management.std", "rb");
   while(  fread(&c,sizeof(c),1,fp) == 1)
   {
      // if (c.accNo[0] == '\0')  continue;
   
      if (strcmp(c.password,pass) == 0 )//&& strcmp(c.accNo,ac) == 0)
      {
         flag =1;
         printf("Account found!\n");
       printf("Name: %s\n", c.name);
       printf("Age: %d\n", c.age);
       printf("Contact: %s\n", c.contact);
       printf("Address: %s", c.add);
       printf("Account Type: %s\n", c.accType);
       printf("Account No: %s\n", c.accNo);
       printf("Balance: %d\n", c.balance);
       break;
      }
      
   }
   if (flag == 0)
   {
      printf("acccount not found");
   }
   fclose(fp);
}

  void addMoney(){
   char pass[50];
   char n[30];
   int amt,flag=0;
   printf("Enter the name: ");
   scanf("%29s",n);
   printf("enter the password: ");
   scanf("%49s",pass);
   printf("enter the amount to be added: ");
   scanf("%d", &amt);

   fp = fopen("bank management.std","r+b");
   while(fread(&c,sizeof(c),1,fp) == 1)
  
   {
      if (strcmp(c.password, pass) == 0)
      {
         flag = 1;
        c.balance = c.balance + amt;
        fseek(fp, -(long)sizeof(c),SEEK_CUR);
        fwrite(&c,sizeof(c),1,fp);
        printf("amount is added sucessfully!\n");
        break;
      }
      
   }

   if( flag == 0){
      printf("passwor is wrong or candidate is not register\n");

   }
   fclose(fp);

}

void DebitMoney(){
   char n[30];
   char pass[50];
   int d,flag=0;
   printf("enter the name: ");
   scanf("%29s",n);

   printf("enter the password: ");
   scanf("%49s", pass);
  
   fp = fopen("bank management.std","r+b");
   while (fread(&c,sizeof(c),1,fp) == 1)
    {
   
   
   if(strcmp(c.password,pass) == 0)
      {
         flag =1;
         printf("enter the amount to debit: ");
         scanf("%d", &d);
         if (d > c.balance)
         {
          printf("the debit amount is higher than the balance amount");
           break;
          }
   
         c.balance = c.balance - d;
         fseek(fp, -(long)sizeof(c), SEEK_CUR);
         fwrite(&c, sizeof(c),1,fp);
         printf("amount is debited succesfully!!");
         break;
      }
   
   }
   if (flag == 0)
   {
      printf("passwor is wrong or candidate is not register\n");

   }
   fclose(fp);
   
   
}


void delete(){
   FILE *fp2;
   char ac[16];
   char pass[50];
   int f = 0;
   printf("Enter the account no.: ");
   scanf("%15s",ac);
   printf("enter the password: ");
   scanf("%49s",pass);  
   fp = fopen("bank management.std","r+b");
   fp2 = fopen("temp.std", "w+b");

   while(!feof(fp))
   {
      fread(&c, sizeof(c),1,fp);
      if (feof(fp))
         break;
      
      if(strcmp(c.password,pass) && strcmp(c.accNo,ac) == 0)
      {
      f = 1;
      printf("account delete successfully!\n");
     }
     else
     {
       fwrite(&c,sizeof(c),1,fp2);
   
     }
   }
   if (f == 0)
   {
     printf("account no. or password is incorrect");
   }
   fclose(fp);
   fclose(fp2);
remove("bank management.std");
rename("temp.std","bank management.std");
}

void balance(){
   char acc[16];
   char pass[50];
   int f = 0;
   printf("enter the account no.: ");
   scanf("%15s",acc);
   printf("enter the password: ");
   scanf("%49s",pass);
   
   fp = fopen("bank management.std","rb");
   while (fread(&c,sizeof(c),1,fp) == 1)
   {
      if (strcmp(c.password,pass) == 0 && strcmp(c.accNo,acc) == 0)
      {
        f = 1;
        printf("Bank Balance is: %d", c.balance);
        break;
      }
     
   }

   if (f == 0)
   {
     printf("account number or password is wrong!");
   }
   
   fclose(fp);
}

void transfer(){
   char acc[16];
   char acc2[16];
   char pass[50];
   int t;
   int f = 0;
                
   printf("Enter your account no.: ");
   scanf("%s",acc);
   printf("Enter your password: ");
   scanf("%s",pass);

   fp = fopen("bank management.std","r+b");

   while (fread(&c, sizeof(c),1,fp) == 1)
   {
      if (strcmp(c.password,pass)  == 0)
      {
         f = 1;
         printf("enter the account no. to transfer amount to: ");
         scanf("%s",acc2);
         printf("enter the amount to transfer: ");
         scanf("%d", &t);
         c.balance = c.balance - t;
         fseek(fp, -(long)sizeof(c),SEEK_CUR);
         fwrite(&c, sizeof(c),1,fp);

         while (fread(&c, sizeof(c),1,fp) == 1)
         {
           if (strcmp(c.accNo,acc2) == 0)
           {
            f = 1;
            c.balance = c.balance + t;
            fseek(fp, -(long)sizeof(c),SEEK_CUR);
            fwrite(&c, sizeof(c),1,fp);

           }
         
         }
         

      }
      break;
   }

   if (f == 0)
   {
     printf("password is incorrect!!");
   }
   
   
}

int main() {
    int n = 0;
    while(1){
    printf("\n1. Creat new account\n");
    printf("2. Login to account\n");
    printf("3. check balance\n");
    printf("4. transfer money\n");
    printf("5. creadit money\n");
    printf("6. debit money\n");
    printf("7. delete account\n");
    printf("8.Exit\n");
    printf("your choice: ");
    scanf("%d", &n);
    getchar();

    switch (n)
    {
    case 1:
       NewAcc();
      break;
    case 2:
       Login();
       break;
    case 3:
       balance();
       break;
    case 4:
       transfer();
       break;
    case 5:
       addMoney();
       break;
    case 6:
       DebitMoney();
       break;
    case 7:
       delete();
    case 8:
        return 1;
    
    default: 
     printf("you enter the wrong prefrence!!");
     break;;
    }
   }

   return 0;
}
   
   