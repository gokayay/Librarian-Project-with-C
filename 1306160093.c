#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 30

//1306160093- Gökay AY

struct Book
{
    int book_id;
    char book_name[30];
    char author_name[30];

};

struct Record
{
    struct Book data;
    struct Record *link;


};

void insert(struct Book bookshelf_record, struct Record *hash_table[])

{     struct Record *ptr;
      int count =0;
      int key, h;
      struct Record *temp;
      key = bookshelf_record.book_id;
      h =hash_function(key);


      if(hash_table[h] != NULL)
            {
                  ptr = hash_table[h];
                  while(ptr != NULL)
                  {
                        count ++;
                        ptr=ptr->link;
                  }
                  if(count<5){
                        temp = malloc(sizeof(struct Record));
                        temp->data = bookshelf_record;
                        temp->link = hash_table[h];
                        hash_table[h] = temp;

                  }
                  else{
                    printf("Kitap rafi doludur! Baska yere ekleme yapiniz ");

                  }

            }
            else{


            temp = malloc(sizeof(struct Record));
            temp->data = bookshelf_record;
            temp->link = hash_table[h];
            hash_table[h] = temp;

            }

}

void getFromFile(struct Book bookshelf_record, struct Record *hash_table[])
{
    int h,j,a;
    struct Record *temp;
    struct Record *ptr;
    int dizi[30][5];
    FILE *fp;
    FILE *sp;
    char str[1000];
    char datastr[300][30];
    char *Ptr0;
    char cp;
    char dp;
    int line=0;
    int i=0;

    char dizi2[30];

    fp=fopen("index.txt","r");

      if (fp == NULL){
        printf("Could not open file ");
        return 1;
    }
    while (!feof(fp)){
        cp=fgetc(fp);
     if(cp!='\n'){
     str[line++]=cp;
     }
    }

       Ptr0=strtok(str,"|");

    for(h=0;h<30;h++){
        for(j=0;j<5;j++){
            i=atoi(Ptr0);
            Ptr0=strtok(NULL,"|");
            dizi[h][j]=i;
       //     printf("%d ",dizi[h][j]);
        }
    }

    //////////////////////////////////////////////

     for(h=0;h<30;h++){
        for(j=0;j<5;j++){

         if(dizi[h][j]!=0){
            temp = malloc(sizeof(struct Record));
            temp->data.book_id = dizi[h][j];
            temp->link = hash_table[h];
            hash_table[h] = temp;

      if(hash_table[h] != NULL)
            {
                  ptr = hash_table[h];
                  while(ptr != NULL)
                  {

                        ptr=ptr->link;
                  }


            }
            else{


            temp = malloc(sizeof(struct Record));
            temp->data.book_id = dizi[h][j];
            temp->link = hash_table[h];
            hash_table[h] = temp;

            }


        }
        }
    }

fclose(fp);

    //////////////////////////////////////////////////

h=0;
j=0;

 sp = fopen("books.txt", "r");
    if (sp == NULL){
        printf("Could not open file ");
        return 1;
    }

printf("\n");
while (!feof(sp)){
     dp=fgetc(sp);
     if(dp!='\n'&&dp!='|'&&dp!=','){
            datastr[h][j]=dp;
            j++;
     }
     else if(dp!='\n'){
        datastr[h][j]='\0';
        h++;
        j=0;
     }
     else{
        h++;
        j=0;
     }

    }
    h=0;
    j=0;
    for(h=0;h<300;h++){
          while(datastr[h][j]!='\0'){
         // printf("%c",datastr[h][j]);
          j++;
          }
          //printf("\t");
    j=0;
    }

 //printf("\n");

    for(h=0;h<300;h+=2){

       for(j=0;datastr[h][j]!='\0';j++)
      {

                dizi2[j]=datastr[h][j];
            //    printf("%c",dizi2[j]);
      }



            a=h/10;
           // temp->data.book_name=dizi2;

 //Kitaplari el ile girince file islemlerinde bir sıkıntı çıkmıyor lakin dosyadan çekerken hash_table'a atmada ufak problemler var. Bu fonksiyon dönmüyor.
    }


   ////////////////////////////////////////////////

    fclose(sp);



}





void SendtoFile(struct Record *hash_table[])
{

      char isim[5] = {'N','U','L','L'};
      int count;
      int tur;
      struct Record *ptr;
      FILE *fptr;


    //for Index File

    fptr=fopen("index.txt","w");
    if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
      for(count = 0; count < MAX; count++)
      {
            //int raf=count +1;
            tur =5;
            if(hash_table[count] != NULL)
            {
                  ptr = hash_table[count];
                  while(ptr != NULL)
                  {
                        tur--;
                        fprintf(fptr,"%d|", ptr->data.book_id);
                        ptr=ptr->link;
                  }
                  int j1;
                  for(j1=0;j1<tur;j1++){
                    fprintf(fptr,"%s|",isim);
                  }
            }
            else{
                ptr = hash_table[count];
                int j2;
                for(j2=0;j2<tur;j2++){
                    fprintf(fptr,"%s|",isim);
                  }

      }
    fputc('\n',fptr);
}
    fclose(fptr);

    //for Data file

    fptr=fopen("books.txt","w");

    if(fptr == NULL)
   {
      printf("File not exist!");
      exit(1);
   }
      for(count = 0; count < MAX; count++)
      {
        tur =5;

            if(hash_table[count] != NULL)
            {
                  ptr = hash_table[count];
                  while(ptr != NULL)
                  {
                        tur--;
                        fprintf(fptr,"%s, %s|", ptr->data.book_name , ptr->data.author_name);
                        ptr=ptr->link;
                  }
                  int j4;
                  for(j4=0;j4<tur;j4++){
                    fprintf(fptr,"%s,%s|",isim,isim);
                  }
            }
            else{
                ptr = hash_table[count];
                int j3;
                for(j3=0;j3<tur;j3++){
                    fprintf(fptr,"%s,%s|",isim,isim);
                  }
            }
            fputc('\n',fptr);
      }

      fclose(fptr);


}

void list(struct Record *hash_table[])
{
      int ara;
      char isim[5] = {'N','U','L','L'};
      int count;
      int j;
      struct Record *ptr;

      for(count = 0; count < MAX; count++)
      {
            ara=5;
            printf("\n[%3d]", count);
            if(hash_table[count] != NULL)
            {
                  ptr = hash_table[count];
                  while(ptr != NULL)
                  {
                        ara--;
                        printf(" %s ,",ptr->data.book_name);
                        ptr=ptr->link;
                  }
            }
            for(j=0;j<ara;j++){
            printf(" %s,",isim);
            }
      }
      printf("\n");
}

int search_element(int key, struct Record *hash_table[])
{
      int h;
      struct Record *ptr;
      h = hash_function(key);
      ptr = hash_table[h];
      while(ptr != NULL)
      {
            if(ptr->data.book_id == key)
            {
                  return h;
            }
            ptr = ptr->link;
      }
      return -1;
}

void searchBook(struct Record *hash_table[])
{
      char searching[50];
      printf("Enter the book to search:\t");

      fgets (searching, 50, stdin);
      scanf ("%[^\n]%c", &searching);

      int h;
      struct Record *ptr;


      for(h=0;h<30;h++)
      {
      ptr = hash_table[h];
      while(ptr != NULL)
      {
            if(strcmp(searching,ptr->data.book_name)==0){
            printf("%d ,%s , %s\n",ptr->data.book_id,ptr->data.book_name,ptr->data.author_name);
            }
            ptr = ptr->link;
      }


      }
      return -1;

}
void searchAuthor(struct Record *hash_table[])
{
      char searching[50];
      printf("Enter the author to search:\t");

      fgets (searching, 50, stdin);
      scanf ("%[^\n]%c", &searching);

      int h;
      struct Record *ptr;


      for(h=0;h<30;h++)
      {
      ptr = hash_table[h];
      while(ptr != NULL)
      {
            if(strcmp(searching,ptr->data.author_name)==0){
            printf("%d ,%s , %s\n",ptr->data.book_id,ptr->data.book_name,ptr->data.author_name);
            }
            ptr = ptr->link;
      }


      }
      return -1;

}



int hash_function(int key)
{
      return (key % MAX);
}




//Main buradan itibaren basliyor-----------------------------------------------------------------------

int main()
{
      struct Record *hash_table[MAX];
      struct Book bookshelf_record;
      int count,count2, key, option;

      for(count2=0;count2<5;count2++)
    {
      for(count = 0; count <= MAX - 1; count++)
      {
            hash_table[count] = NULL;
      }

    }
    printf("Welcome!\n");
    printf("If you add a new book, you should Send to file.(Press 6.)\n");

    getFromFile(bookshelf_record, hash_table);  // file'daki datalarý hash table'da kullanmak için

while(1)
      {
            printf("\n");
            printf("1. Insert a Record in Hash Table\n");
            printf("2. Search for a Record's Shelf\n");
            printf("3. Search for a Book\n");
            printf("4. Search for an Author\n");
            printf("5. List all the books\n");
            printf("6. Send Books To File\n");
            printf("7. Quit\n");
            printf("Select your option in this menu:\n");
            scanf("%d",&option);
            switch(option)
            {
                  case 1:
                        printf("Enter the book details\n");

                        printf("Book ID:\t");
                        scanf("%d", &bookshelf_record.book_id);

                        printf("Book Name:\t");


                        fgets (bookshelf_record.book_name, 50, stdin);
                        scanf ("%[^\n]%c", &bookshelf_record.book_name);

                        printf("Author Name:\t");

                        scanf ("%[^\n]%c", &bookshelf_record.author_name);

                        insert(bookshelf_record, hash_table);
                        break;
                  case 2:
                        printf("Enter the id to search:\t");
                        scanf("%d", &key);
                        count = search_element(key, hash_table);
                        if(count == -1)
                        {
                            printf("Element Not Found\n");
                        }
                        else
                        {
                            printf("Element Found in Chain:\t%d\n", count);
                        }
                        break;

                  case 3:
                        searchBook(hash_table);
                        break;
                  case 4:
                        searchAuthor(hash_table);
                        break;
                  case 5:
                        list(hash_table);
                        break;
                  case 6:
                        SendtoFile(hash_table);
                        break;
                  case 7:
                        exit(1);
            }
      }
      return 0;
}
