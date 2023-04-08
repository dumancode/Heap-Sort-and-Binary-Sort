//FURKAN DUMAN
//2453173

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*Assumptions
 -> All printf() functions O(1)
 -> I predict all string functions have a O(1)*/

struct mail
{
    int Email_ID;
    char Sender[50];
    char Receipt[50];
    int Day_of_the_month;
    int countWords;
};






struct mail *  readMails(char *, int);
void printEmails(struct mail *, int );
void swap(int *, int *);
void heapify(struct mail *, int, int,int );
void buildHeap(struct mail *, int,int );
void heapSort(struct mail *, int,int);
void binSearch(struct mail *, int,int );
void menu();



int main()
{




    int choose,number;

    char filePath[50];
    printf("Enter data path: ");
    scanf("%s",filePath);

    fflush(stdin);

    printf("How many files: ");
    scanf("%d",&number);

    struct mail*Furkan = readMails(filePath, number);

// For do while we don't know O().It depends.
    do
    {


        menu(); // O(1)


        printf("Command: ");
        scanf("%d",&choose);

        if(choose == 5)  //O(1)
        {
            printf("Bye");
            exit(1);
        }


        else if (choose == 4)  //// O(N*LogN)+ O(logN),so  Complexity of this "else if " O(N*LogdN)
        {

            int key;
            printf("Enter the search key: ");
            scanf("%d",&key);

            heapSort(Furkan,number,1);  // heapSort is O(N*logN), Because heapify is O(logN) and it executes N times

            binSearch(Furkan,number,key); // O(logN)



        }
        else // O(N*LogN)+ O(N),so  Complexity of this "else" O(N*LogN)
        {

            heapSort(Furkan,number,choose); // heapSort is O(N*logN), Because heapify is O(logN) and it executes N times

            printEmails(Furkan,number); // O(N) because there is a for loop with the size times.
        }

    }
    while(choose != 5);

    return 0;
}


/*

First for loop complexity is O(N) because it depends on number.
While read character(inner loop) have a complexity O(N) since it depends on the words number.

So total complexity is O(N^2)
*/
struct mail * readMails(char *filePath,int number)
{
    struct mail* C = (struct mail*)malloc(number * sizeof(struct mail));


    char *token;
    char name[50];
    FILE *inFile1;
    char fileName[50];
    char fileNumber[3] = "";
    int i;

    strcat(filePath,"\\");
    for(i=0; i < number; i++)  // O(N)
    {
        strcpy(fileName,filePath);
        itoa(i+1, fileNumber, 10);
        strcat(fileName,fileNumber);
        strcat(fileName,".txt");


        inFile1 = fopen(fileName,"r");


        if(i== 0)  // If the datapath is written incorrectly, the file will be empty so
            //I can find out that the data path name is misspelled.
        {
            if(inFile1 == NULL)
            {
                printf("There is no datapath !!!\n");
                exit(1);


            }

        }


        if(inFile1 == NULL)  // For more than 50 arguments
            printf("Much argument error!\n");

        fscanf(inFile1,"%d\n",&(C[i].Email_ID));  // Read integer value and store this value in my structure.


        fgets(name, 50, inFile1);
        token = strtok(name,":");
        token = strtok(NULL," ");       // I'm reading string values after ':'

        strcpy(C[i].Sender,token);    // Then store in my structure.



        fgets(name, 50, inFile1);
        token = strtok(name,":");
        token = strtok(NULL," ");        // I'm reading string values after ':'

        strcpy(C[i].Receipt,token);       // Then store in my structure.

        fscanf(inFile1,"%*s %d\n",&C[i].Day_of_the_month );  //skip string and read integer value, then store in my structure.


        int countforwords = 1; //I assumed content has least one word.
        char ch;


        while((ch = fgetc(inFile1)) != EOF)  // O(N)
        {

            if((ch == ' ')) // I read the spaces
            {
                countforwords++;
            }
        }


        C[i].countWords = countforwords;


        strcpy(fileName,"");
        fclose(inFile1);

    }
    printf("\n%d emails have been read successfully! \n ",number);


    return (C);
}


// It has a complexity O(N) because the loop runs count times.

void printEmails(struct mail *mails,int count)
{
    int i;
    for( i = 0; i<count ; i++)
    {
        printf("\n");
        printf("Id: %d\n",mails[i].Email_ID);
        printf("Sender: %s",mails[i].Sender);
        printf("Receipt: %s",mails[i].Receipt);
        printf("Month: %d\n",mails[i].Day_of_the_month);
        printf("Words: %d\n",mails[i].countWords);
    }
}

// It has a complexity O(1)
void menu()
{
    printf("\nPlease choose one of the following options:\n") ;
    printf("(1) Display emails sorted by id\n") ;
    printf("(2) Display emails sorted by number of words\n");
    printf("(3) Display emails sorted by date\n");
    printf("(4) Search email by ID\n");
    printf("(5) Exit\n");



}
//// It has a complexity O(1)
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

////While performing operations, it looks at a certain side of the tree each time (operation is halved).
//O(LogN)
void heapify(struct mail *mails, int N, int i,int criteria)
{
    char temp1[100];

    int largest = i; //  Largest value is  root
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    switch(criteria)
    {
    case 1 :
        // If left child is larger than root
        if (l < N && mails[l].Email_ID > mails[largest].Email_ID)
            largest = l;

        // If right child is larger than largest so far
        if (r < N && mails[r].Email_ID > mails[largest].Email_ID)
            largest = r;
        break;

    case 2:

        if (l < N && ((mails[l].countWords)) > (mails[largest].countWords))
            largest = l;


        if (r < N && (mails[r].countWords) > (mails[largest].countWords))
            largest = r;
        break;


    case 3 :

        if (l < N && mails[l].Day_of_the_month > mails[largest].Day_of_the_month)
            largest = l;


        if (r < N && mails[r].Day_of_the_month > mails[largest].Day_of_the_month)
            largest = r;


        break;



    }





    // If largest is not root
    if (largest != i)
    {

        swap(&mails[i].Email_ID, &mails[largest].Email_ID);
        swap(&mails[i].Day_of_the_month, &mails[largest].Day_of_the_month);
        swap(&mails[i].countWords, &mails[largest].countWords);





        strcpy(temp1,mails[i].Receipt);
        strcpy(mails[i].Receipt,mails[largest].Receipt);
        strcpy(mails[largest].Receipt,temp1);

        strcpy(temp1,mails[i].Sender);
        strcpy(mails[i].Sender,mails[largest].Sender);
        strcpy(mails[largest].Sender,temp1);




        // Recursive call
        heapify(mails, N, largest,criteria);

    }
}

// IF WE LOOK AT TIGHT ANALYSIS : the sum of the heights of all the nodes in the heap
//Thus it is O(n)

void buildHeap(struct mail *mails, int N,int criteria)
{
    // Index of last non-leaf node
    int startIdx = (N / 2) - 1;
    int i;


    for ( i = startIdx; i >= 0; i--)
    {
        heapify(mails, N, i,criteria);
    }
}



//First I call buildHeap which has a complexity O(N), Then  heapSort is O(N*logN), Because heapify is O(logN) and it executes N times
// So Complexity of heapSort  O(N*LogN)

void heapSort(struct mail *mails, int N,int criteria)
{
    char temp1[100];

    buildHeap(mails,N,criteria);
    int i;

    for ( i = N - 1; i >= 0; i--)
    {

        swap(&mails[0].Email_ID, &mails[i].Email_ID);


        swap(&mails[0].Day_of_the_month, &mails[i].Day_of_the_month);

        swap(&mails[0].countWords, &mails[i].countWords);

        strcpy(temp1,mails[0].Receipt);
        strcpy(mails[0].Receipt,mails[i].Receipt);
        strcpy(mails[i].Receipt,temp1);

        strcpy(temp1,mails[0].Sender);
        strcpy(mails[0].Sender,mails[i].Sender);
        strcpy(mails[i].Sender,temp1);



        // Heapify root element to get highest element at
        // root again
        heapify(mails, i, 0,criteria);
    }
}



 // I already heap sort, therefore the complexity of binary search algorithm is O(logN)
void binSearch(struct mail *mails, int N,int id)
{

    int low =0;
    int high = N-1;
    int x;
    int count = 0;


    while(low<=high)
    {

        x  =  (high+low)/2 ;

        if( mails[x].Email_ID == id )
        {
            count++;
            printf("\n");
            printf("Id of mail: %d\n",mails[x].Email_ID);
            printf("Sender: %s",mails[x].Sender);
            printf("Receipt: %s",mails[x].Receipt);
            printf("Month: %d\n",mails[x].Day_of_the_month);
            printf("Words: %d\n",mails[x].countWords);
            break;
        }

        else if(id  <  mails[x].Email_ID )
        {

            high = x-1;


        }
        else
            low = x+1;



    }
    if(count ==0)
        printf("There is no this ID\n");
}


































