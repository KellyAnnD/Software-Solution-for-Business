

// This program manages clients information for a garbage disposal
// company such as their information, jobs that are done and payments made.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXRECORD 100
#define MAXSERVICE 10

typedef struct
{
   char compname[20], contperson[20];
   char address1 [20], address2[15];
   char phonenum [12];
} clientrecord;

typedef struct
{
   char service [45];
   float cost;
}servicerecord;

typedef struct
{
   int comp;
   char service[45];
   float freq;
   char date [8];
   float total;
}jobrecord;

typedef struct
{
  char compname[20], date[8];
  float amtpaid;
}paymentrecord;

typedef struct
{
  jobrecord information[15];
  float ttotal;
}invoicerecord;

typedef struct
{
  int id, amountofservice;
  char clientservice[MAXSERVICE][45];
}clientservicerecord;

int popservicedata( servicerecord servicedata[], int scount);
int popclientdata( clientrecord clientdata[], int count);
int popclientservicedata ( clientservicerecord clientservicedata[], int cscount);
int menuoption ( int option);
void updateclientsacc ( clientrecord clientdata[], servicerecord servicedata[], clientservicerecord clientservicedata[],int count, int scount,int cscount);
float calclientsbal( clientrecord clientdata[], clientservicerecord clientservicedata[],int count, int balonly , int ncount);
void viewclientsinfo( clientrecord clientdata[], clientservicerecord clientservicedata[], int count);
void addclient(clientservicerecord clientservicedata[], servicerecord servicedata[], int cscount, int scount);
void choosecompany( clientrecord clientdata[], int *ncount, int count);
void jobentry1(servicerecord servicedata[],clientrecord clientdata[], clientservicerecord clientservicedata[], int ncount, int scount, int cscount);
void jobentry2(servicerecord servicedata[],clientrecord clientdata[], clientservicerecord clientservicedata[] ,int ncount,int scount);
void clientpayment(clientrecord clientdata[],clientservicerecord clientservicedata[],int count, int ncount, int *balonly);
int chooseservice (clientservicerecord clientservicedata[], servicerecord servicedata[], int cscount, int scount);
FILE *clientftr, *serviceftr, *jobftr, *paymentftr, *invoiceftr, *receiptftr, *clientserviceftr;


int main()
{
    // Main Program

    int option;
    int count,ncount;
    int scount;
    int cscount;
    int balonly;
    clientrecord clientdata[MAXRECORD] = {0};
    servicerecord servicedata [MAXRECORD];
    clientservicerecord clientservicedata [MAXRECORD];

     system("color 70");

    scount = 0;
    scount = popservicedata( servicedata, scount);

   do
   {
      count = 0;
      cscount = 0;
      balonly = 0;


      count = popclientdata( clientdata, count);

      cscount = popclientservicedata (clientservicedata,cscount);

      option = menuoption(option);
      printf("\n");


       switch (option)
       {
              case 1: updateclientsacc( clientdata, servicedata, clientservicedata, count, scount ,cscount);
                      break;
              case 2: printf("View Clients Balance\n");
                      system("pause");
                      choosecompany( clientdata, &ncount, count);
                      calclientsbal( clientdata, clientservicedata, count, balonly,ncount );
                      break;
              case 3: viewclientsinfo( clientdata, clientservicedata, count);
                      break;
              case 4:addclient(clientservicedata, servicedata, cscount,scount);
                      break;
              case 5: printf("Program ending\n");
                      break;
              default: printf("invalid response\n");
       }               system("Pause");
    }while( option != 5);



  system("PAUSE");
  return 0;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int popservicedata(servicerecord servicedata[], int scount)
{
    // This function puts the information stored in the service file( name of service and cost)
    //in an array so that the //user can choose the option when required

    servicerecord servicerec;

    scount = 0;

    serviceftr = fopen("servicefile.txt", "r");
    if (serviceftr == NULL)
    {
      puts("File not found \n");
      system("pause");
      exit(1);
    }
    else
    {

        while(fscanf(serviceftr, "%s%f", servicerec.service,&servicerec.cost)==2)
          {

              strcpy(servicedata[scount].service, servicerec.service);

              servicedata[scount].cost = servicerec.cost;

              scount++;

          }

          fclose(serviceftr);
          return scount;
    }
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int popclientservicedata( clientservicerecord clientservicedata[], int cscount)
{
    // This function puts the information stored in the client service file
    //in an array so that the user can choose the option when required


    clientservicerecord clientservicerec;
    int i;

    cscount = 0;

    clientserviceftr = fopen("clientservicefile.txt", "r");
    if (clientserviceftr == NULL)
    {
      puts("File not found\n");
      system("pause");
      exit(1);
    }
    else
    {

        while(!feof(clientserviceftr))
          {
              fscanf(clientserviceftr, "%d", &clientservicerec.id);

              clientservicedata[cscount].id = clientservicerec.id;

              fscanf(clientserviceftr, "%d", &clientservicerec.amountofservice);

               clientservicedata[cscount].amountofservice = clientservicerec.amountofservice;

               for( i =0; i < clientservicerec.amountofservice; i++)
               {
                    fscanf(clientserviceftr, "%s", clientservicerec.clientservice[i]);
                    strcpy(clientservicedata[cscount].clientservice[i], clientservicerec.clientservice[i]);
               }


              cscount++;

            }
            cscount = cscount - 1;

            fclose(clientserviceftr);
            return cscount;
    }
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int popclientdata( clientrecord clientdata[], int count)
{
    // This function puts all the clients information stored in the clients file in an array of records

    clientrecord clientrec;

    count = 0;

    clientftr = fopen("clientfile.txt", "r");

    if(clientftr == NULL)
    {
        puts("File not found\n");
        system("pause");
        exit(1);
    }
    else
    {

       while(!feof(clientftr))
        {
            fscanf(clientftr, "%s", clientrec.compname);
            strcpy(clientdata[count].compname, clientrec.compname);
            fscanf(clientftr, "%s", clientrec.contperson);
            strcpy(clientdata[count].contperson, clientrec.contperson);
            fscanf(clientftr, "%s", clientrec.address1);
            strcpy(clientdata[count].address1, clientrec.address1);
            fscanf(clientftr, "%s", clientrec.address2);
            strcpy(clientdata[count].address2, clientrec.address2);
            fscanf(clientftr, "%s", clientrec.phonenum);
            strcpy(clientdata[count].phonenum, clientrec.phonenum);

            count++;

        }
    }
        fclose(clientftr);

        return (count);
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int menuoption ( int option)
{
    // This function will display the menu options and accepts the choice of the user

    printf("0000000000000000000000000000000000000000000000000000000\n");
    printf("0              Hans Services System                   0\n");
    printf("0                    Welcome!!                        0\n");
    printf("0                                                     0\n");
    printf("0  Choose one of the option :                         0\n");
    printf("0                                                     0\n");
    printf("0    1. Update Clients Account                        0\n");
    printf("0    2. View Clients Balance                          0\n");
    printf("0    3. View Clients information                      0\n");
    printf("0    4. Set up new client                             0\n");
    printf("0    5. Exit                                          0\n");
    printf("0                                                     0\n");
    printf("0000000000000000000000000000000000000000000000000000000\n");

    printf("Type response here :");
    scanf("%d", &option);
    system("cls");
    return option;

}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

void updateclientsacc ( clientrecord clientdata[], servicerecord servicedata[], clientservicerecord clientservicedata[], int count, int scount, int cscount)
{
     // This function gives the user an option to add a payment to a clients account or add a new job that was done .

     char response;
     int ncount, endcount,balonly;
     int endcount2 = 0, response2;


     balonly = 1;
     endcount = 0;
     printf("Update Clients Account\n");
     system("pause");
     system("cls");

     do
     {
       printf("    Hans Services Update Client Menu  \n\n");
       printf("Enter A - To Add New Job Entry\n");
       printf("      B - To Add Payment to Client Account\n");
       printf("      C - To Exit\n");
       printf("Response:");
       scanf(" %c", &response);
       response  = toupper(response);


       if (response == 'A')
       {

            printf("Adding Job\n");
            system("pause");
            system("cls");
            choosecompany(clientdata, &ncount, count);
            do
            {

                printf("Enter 1 for regular service or 2 for special services done \n");
                scanf("%d", &response2);
                if (response2 == 1)

                     jobentry1 (servicedata, clientdata, clientservicedata, ncount, scount,cscount );

                else
                {

                    if ( response2 == 2)

                        jobentry2 (servicedata, clientdata ,clientservicedata, ncount, scount);

                    else
                    {
                        printf("Invalid Response\n");
                        endcount2++;
                     }
                }

            }while((response <= 2) && (endcount2!= 3));

        }
       else
       {
           if ( response == 'B')
           {
           printf("Adding Payment\n");
           system("pause");
           system("cls");
           choosecompany(clientdata, &ncount, count);

           clientpayment(clientdata, clientservicedata,count, ncount, &balonly);


           }
           else
           {
               if( response == 'C')
               {
                return;
                }

                else
                {

                   printf("Invalid Response\n");
                   system("Pause");
                   system("cls");
                   endcount++;
                }
           }
       }
       system("cls");

     }while((response != 'C') && (endcount != 3));
     system("pause");
     system("cls");
     return;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000


void jobentry1(servicerecord servicedata[],clientrecord clientdata[], clientservicerecord clientservicedata[], int ncount, int scount, int cscount)
{
        invoicerecord invoicerec;
        jobrecord jobrec;
        int count1, count2 = 0,found = 0,option, endcount, j, result = 0;
        float frequency;
        float ttotal = 0;


        for(count1 = 0; count1 < clientservicedata[ncount].amountofservice ; count1++)
        {
            jobrec.comp = clientservicedata[ncount].id;
            invoicerec.information[count1].comp =  clientservicedata[ncount].id;

            found = 0;
            while(found!= 1 )
            {

                result = strcmp(clientservicedata[ncount].clientservice[count1], servicedata[count2].service);


                if (result == 0)
                {
                        strcpy(jobrec.service,servicedata[count2].service);
                        strcpy(invoicerec.information[count1].service ,jobrec.service);
                        found++;

                        do
                        {
                            printf("How much %s was collected\n",servicedata[count2].service);

                            scanf("%f", &frequency);
                            endcount++;
                        }while((frequency <= 0) && (endcount != 3));
                        if(endcount == 3)
                        {
                                return;
                        }
                        jobrec.freq = frequency;
                        invoicerec.information[count1].freq = jobrec.freq;

                        printf("What is the date when it was performed\n");
                        scanf("%s", jobrec.date);
                        strcpy(invoicerec.information[count1].date, jobrec.date);

                        jobrec.total = jobrec.freq * servicedata[count2].cost;
                        invoicerec.information[count1].total = jobrec.total;

                        ttotal = ttotal + jobrec.total;

                        jobftr = fopen("jobfile.txt","a");

                        if(jobftr == NULL)
                        {
                            printf("File not found\n");
                            system("pause");
                            return;
                        }
                        else
                        {
                            fprintf(jobftr, "%d\n", jobrec.comp);
                            fprintf(jobftr, "%s\n", jobrec.service);
                            fprintf(jobftr, "%f\n", jobrec.freq);
                            fprintf(jobftr, "%s\n", jobrec.date);
                            fprintf(jobftr, "%f\n", jobrec.total);
                        }

                        fclose(jobftr);
                        printf("Job successfully added to file\n");
                        system("pause");
                        system("cls");
                    }
                    count2++;
                }

            }

            printf("Total cost of job is $%f\n",ttotal);

            invoicerec.ttotal = ttotal ;
            printf("Do you want an invoice printed 1 for yes and 2 for no\n");
            scanf("%d", &option);

            if (option == 1)
            {
                system("cls");
                printf("       Hans Services     \n\n");

                printf("Company Name :   %s\n\n",clientdata[ncount].compname);
                printf("Date  Quantity      Jobs Done          Cost\n");
                for(j = 0; j < clientservicedata[ncount].amountofservice; j++)
                {
                    printf("\n%s", invoicerec.information[j].date);
                    printf("      %.1f", invoicerec.information[j].freq);
                    printf("       %s",invoicerec.information[j].service);
                    printf("          $%f", invoicerec.information[j].total);
                }
                printf("\n\nTOTAL AMOUNT DUE:  $%f\n",  ttotal);
                printf ("        HAVE A GOOD DAY  :) ");

            }
            system("pause");
            system("cls");

            return;

}


void jobentry2(servicerecord servicedata[],clientrecord clientdata[], clientservicerecord clientservicedata[] ,int ncount, int scount)
{
     // This function adds jobs done to the jobfile

    int nservice,  endcount, jobsdone, j, x ;
    float ttotal, cost, jobfreq  ;
    jobrecord jobrec;
    invoicerecord invoicerec;
    int option ;

        endcount = 0;

        do
        {
                 printf("How many Jobs were done  for %s\n", clientdata[ncount].compname);
                 scanf(" %d", &jobsdone);
                 if (jobsdone >= 1)
                {
                    endcount = 3;

                 }
                 else
                 {

                     printf(" Invalid response\n");
                     system("Pause");
                     endcount++;

                     if (endcount == 3)
                     {
                          return;
                     }
                 }
                 system("cls");
        }while(endcount != 3);

        endcount = 0;
        ttotal = 0;


        for(j= 0; j < jobsdone; j++)
        {

              jobrec.comp = clientservicedata[ncount].id;
              invoicerec.information[j].comp = clientservicedata[ncount].id;
              endcount = 0;

              do
              {

                       for( x = 0; x < scount; x++)
                       {
                            printf("%d ---- %s\n",x+1 ,servicedata[x].service);
                       }
                       printf("Choose the number for the service performed\n");
                       scanf("%d", &nservice);
                       endcount++;
                       system("cls");
              }while((( nservice > scount) || (nservice <= 0)) && (endcount != 3));


             if (endcount == 3)
              {
                    return;
              }

              printf("Adding %s\n",servicedata[nservice-1].service);
              system("pause");
              system("cls");

             strcpy(jobrec.service, servicedata[nservice-1].service);
             strcpy(invoicerec.information[j].service, servicedata[nservice-1].service);
             cost = servicedata[nservice-1].cost;
             endcount = 0;

             do
             {
                  printf("What is the frequency\n");
                  scanf("%f", &jobfreq);
                  if(jobfreq <= 0)
                  {
                     endcount++;
                     if (endcount == 3)
                     {
                       return;
                     }
                   }
                  else
                  {
                     endcount = 3;
                  }
                     system("cls");
              }while((jobfreq <= 0) && (endcount != 3));


        jobrec.freq = jobfreq;
        invoicerec.information[j].freq = jobrec.freq;
        printf("What is the date when it was performed\n");
        scanf("%s", jobrec.date);
        strcpy(invoicerec.information[j].date ,jobrec.date);
        jobrec.total = jobrec.freq * cost;
        invoicerec.information[j].total = jobrec.total;
        ttotal = ttotal + jobrec.total;

        jobftr = fopen("jobfile.txt","a");

        if(jobftr == NULL)
        {
            printf("File not found\n");
            system("pause");
            return;
        }
        else
        {
            fprintf(jobftr, "%d\n", jobrec.comp);
            fprintf(jobftr, "%s\n", jobrec.service);
            fprintf(jobftr, "%f\n", jobrec.freq);
            fprintf(jobftr, "%s\n", jobrec.date);
            fprintf(jobftr, "%f\n", jobrec.total);
         }
          fclose(jobftr);
          printf("Job successfully added to file\n");
          system("pause");
          system("cls");

    }
    printf("Total cost of job is $%f\n",ttotal);

     invoicerec.ttotal = ttotal ;
     printf("Do you want an invoice printed 1 for yes and 2 for no\n");
     scanf("%d", &option);

    if (option == 1)
    {
        system("cls");
        printf("       Hans Services     \n\n");

        printf("Company Name :   %s\n\n",clientdata[ncount].compname);
        printf("Date  Quantity      Jobs Done          Cost\n");
        for(j = 0; j < jobsdone; j++)
        {
            printf("\n%s", invoicerec.information[j].date);
            printf("      %.1f", invoicerec.information[j].freq);
            printf("       %s",invoicerec.information[j].service);
            printf("          $%f", invoicerec.information[j].total);
        }
         printf("\n\nTOTAL AMOUNT DUE:  $%f\n",  ttotal);
         printf ("        HAVE A GOOD DAY :) ");

    }
   system("pause");
   system("cls");

    return;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void clientpayment(clientrecord clientdata[], clientservicerecord clientservicedata[],int count,int ncount, int *balonly)
{


     // This function gets the payment a client is paying and adds it to the payment file

     paymentrecord paymentrec;
     int option ;
     float amountpaid, change,companybal, ramptpaid;

    *balonly = 1;
     strcpy(paymentrec.compname, clientdata[ncount].compname);
     companybal = calclientsbal(clientdata, clientservicedata, count, *balonly,ncount);


     printf("When was this paid\n");
     scanf(" %s", paymentrec.date);
     printf("How much is being paid\n");
     scanf(" %f", &amountpaid);
     if( amountpaid >= 1)
     {
            ramptpaid = amountpaid;
             paymentftr = fopen("paymentfile.txt","a");
             if(paymentftr == NULL)
             {
                 printf("File not found\n");
                 system("pause");
                 return;
             }
             else

             {

                 change =  companybal - amountpaid;
                 if (change < 0)
                 {
                     change = change /-1;
                     printf(" Your change is $%f\n",change);
                     amountpaid = companybal;
                 }
                 else
                 {
                     printf("You owe %f\n",change);
                     change = 0;
                 }

                 paymentrec.amtpaid = amountpaid;
                 fprintf(paymentftr, "%s\n", paymentrec.compname);
                 fprintf(paymentftr, "%s\n", paymentrec.date);
                 fprintf(paymentftr, "%f\n", paymentrec.amtpaid);
                 fclose(paymentftr);

                 printf("Payment sucessfully added to file\n");
                 system("PAUSE");

             }
        }
         else
         {
             printf("Invalid response\n");
             system("Pause");
             printf("How much is being paid\n");
             scanf("%f", &amountpaid);
             if( amountpaid >= 1)
             {
                 ramptpaid = amountpaid;

                paymentftr = fopen("paymentfile.txt","a");
                if(paymentftr == NULL)
                {
                    printf("File not found\n");
                    system("pause");
                    return;
                }
                else
                {
                    change =  companybal - amountpaid;
                    if (change < 0)
                    {
                        change = change /-1;
                        printf(" Your change is $%f\n",change);
                        amountpaid = companybal;
                    }
                    else
                    {
                        printf("You owe %f\n",change);
                        change = 0;
                    }

                    paymentrec.amtpaid = amountpaid;
                    fprintf(paymentftr,"%s\n", paymentrec.compname);
                    fprintf(paymentftr,"%s\n", paymentrec.date);
                    fprintf(paymentftr,"%f\n", paymentrec.amtpaid);
                    fclose(paymentftr);
                    printf("Payment sucessfully added to file\n");
                    system("PAUSE");
               }
            }
            else
             {
                  return;
             }

         }
                   system("cls");
                   printf("Do you want a reciept 1 for yes and 2 for no\n");
                   scanf("%d", &option);
                    if(option == 1);
                     {
                        system("cls");
                         printf("      Hans Services \n\n");
                         printf("Date of Payment :   %s\n", paymentrec.date);
                         printf("Company         :   %s\n\n", paymentrec.compname);
                         printf("TOTAL AMOUNT PAID   $%f\n", ramptpaid);
                         printf("CHANGE          :   $%f\n\n",change);
                         printf("    Have a good day \n");
                     }

             system("pause");
             system("cls");
             return;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
float calclientsbal( clientrecord clientdata[], clientservicerecord clientservicedata[], int count, int balonly,int ncount)
{
     //This function  displays the balance on a clients account  by finding the difference between  all the payments
     //made and the total cost of the jobs

   jobrecord jobrec;
   paymentrecord paymentrec;
   float totalcostjob, totalpaymentjob, compowe;
   int result;



   totalcostjob = 0;

   jobftr = fopen("jobfile.txt","r");

   if(jobftr == NULL)
   {
       printf("File not found\n");
       system("pause");
       exit(1);
   }
   else
   {

           while(fscanf(jobftr, "%d%s%f%s%f", &jobrec.comp, jobrec.service, &jobrec.freq, jobrec.date, &jobrec.total)== 5)

          {

             if (jobrec.comp == clientservicedata[ncount].id)
             {

               totalcostjob = totalcostjob +  jobrec.total;

             }

           }
    }
    fclose(jobftr);


    totalpaymentjob = 0;
    result = 0;

    paymentftr = fopen("paymentfile.txt","r");
    if (paymentftr == NULL)
    {
        printf("File not found\n");
        system("pause");
        exit(1);
    }
    else
    {

         while(fscanf(paymentftr, "%s%s%f",paymentrec.compname,paymentrec.date,&paymentrec.amtpaid ) == 3)
         {
                result = strcmp(paymentrec.compname,clientdata[ncount].compname);

                if (result == 0)
                {
                    totalpaymentjob = totalpaymentjob + paymentrec.amtpaid;
               }

          }
    }
    fclose(paymentftr);

    compowe =  totalcostjob - totalpaymentjob;


    if ( balonly == 0)
    {
        if (compowe < 0)
        {
            compowe = compowe/-1;
        }

            printf("                                                    Hans Services System\n");
            printf("                                    Clients Balance Information Report\n");
            printf("                                                    Report date\n\n\n");
            printf(" Name of Client : %s\n",clientdata[ncount].compname);
            printf(" Amount Owed :    $%f\n",compowe);
            system("pause");
    }

    system("cls");

    return(compowe);



}


//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000


void viewclientsinfo( clientrecord clientdata[],clientservicerecord clientservicedata[], int count)
{
     //This function allows the user to view the information stored on a client such as the address, contact person
     //and phone number

     int  x, ncount;
     printf("View Clients Information\n");
     system("pause");

     choosecompany(clientdata, &ncount, count);

     printf("Company  Name                  - %s\n",clientdata[ncount].compname);
     printf("Company ID number              - %d\n",clientservicedata[ncount].id);
     printf("Contact person                 - %s\n",clientdata[ncount].contperson);
     printf( "Address                        - %s, %s\n",clientdata[ncount].address1,clientdata[ncount].address2 );
     printf("Phone number                   - %s\n",clientdata[ncount].phonenum);
     printf("Amount of Contracted services  - %d\n",clientservicedata[ncount].amountofservice);
     printf("Service                        -\n");
     for( x= 0 ; x <clientservicedata[ncount].amountofservice ; x++)
     {
        printf("                               %s\n",clientservicedata[ncount].clientservice[x]);
     }


      system("pause");
      system("cls");

}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

void choosecompany( clientrecord clientdata[], int *ncount, int count)
{
     //This function  displays the list of the company names and puts the clients information in an array so that when
     //the user chooses the company from the list the information can be retrieved from the array

     int comresponse, j;

     do
     {
         printf("          Hans Services System      \n");
         printf("             Client list             \n\n");
         printf("Pick the client you want to service :\n");
         for(j = 0; j < (count-1); j++)
         {
               printf("    %d . %s\n", j+1, clientdata[j].compname);
         }

         printf("\nType your response here  ");
         scanf(" %d",&comresponse);

         if ((comresponse <= count) && ( comresponse>= 1))
         {
             *ncount = comresponse - 1;
         }
         else
         {
             printf("Invalid response choose between 1 and %d\n",count-1);
             system("Pause");
             system("cls");
         }

     }while((comresponse > count) || (comresponse <= 0));

     printf("Processing %s \n", clientdata[*ncount].compname);

     system("Pause");
     system("cls");
     return;

}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000


void addclient( clientservicerecord clientservicedata[], servicerecord servicedata[] , int cscount, int scount)

{
     // This function allows the user to enter a new client and save this information in the client file

     clientrecord clientrec;
     int working;

        printf("Setting up new Client\n");
        system("Pause");
        system("cls");

         printf("Fill in all the slot for the new client \n\n\n");

         printf("Company's name             :");
         scanf("%s", clientrec.compname);
         printf("Contact Person             :");
         scanf("%s", clientrec.contperson);
         printf("Company Address line 1     :");
         scanf("%s", clientrec.address1);
         printf("Company Address line 2     :");
         scanf("%s", clientrec.address2);
         printf("Company Phone Number       :");
         scanf("%s", clientrec.phonenum);

       working = chooseservice( clientservicedata, servicedata, cscount, scount);


    if (working == 0)
    {

        clientftr = fopen("clientfile.txt", "a");

       if(clientftr == NULL)
        {
            printf("File not found\n");
            system("pause");
            return;
        }
        else
        {
            fprintf(clientftr, " %s\n", clientrec.compname);
            fprintf(clientftr, " %s\n", clientrec.contperson);
            fprintf(clientftr, " %s\n", clientrec.address1);
            fprintf(clientftr, " %s\n", clientrec.address2);
            fprintf(clientftr, " %s\n", clientrec.phonenum);
        }
     fclose(clientftr);
     printf("Client  successfully added\n");

    }

    system("pause");
     system("cls");
}

int chooseservice( clientservicerecord clientservicedata[], servicerecord servicedata[], int cscount, int scount)
{
    int nservice, x,endcount, amount,k, working;
    clientservicerecord clientservicerec;



    working = 0;

    clientserviceftr = fopen("clientservicefile.txt", "a");
                if(clientserviceftr == NULL)
     {
        printf("File not found\n");
        return working + 1;
        exit(1);
        system("pause");
        system("cls");
     }
     else
     {

            clientservicerec.id = (clientservicedata[cscount-2].id + 1);
            endcount = 0;

            fprintf(clientserviceftr, "%d\n", clientservicerec.id);
            do
            {
                    printf("Amount of services         :");
                    scanf("%d",&amount);
                    endcount++;
                    printf("%d\n",endcount);
            }while((amount >= 1) && (endcount == 3));

            if (endcount == 3)
                return working + 1;

            clientservicerec.amountofservice = amount;
            fprintf(clientserviceftr, "%d\n",clientservicerec.amountofservice);
            endcount = 0;
            system("cls");
            for ( k = 0; k < amount; k++)

            {
                    do
                    {

                        for( x = 0; x < scount ; x++)
                        {
                            printf("%d ---- %s\n",x+1 ,servicedata[x].service);
                        }
                        printf("\nChoose the number for service %d performed\n",k+1);
                        scanf("%d", &nservice);
                        endcount++;

                    }while((( nservice > scount) || (nservice <= 0)) && (endcount != 3));

                    if (endcount == 3)
                    {
                        return working + 1;
                    }
                    else
                    {
                        printf("Adding %s to file\n",servicedata[nservice].service);
                        strcpy( clientservicerec.clientservice[k], servicedata[nservice].service);
                        fprintf(clientserviceftr, "%s\n", clientservicerec.clientservice[k]);
                        system("pause");
                        system("cls");
                    }

            }
     }

    fclose(clientserviceftr);
    return working;
    system("cls");
}
