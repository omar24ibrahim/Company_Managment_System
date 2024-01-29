#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int d,m,y;
} Date;
typedef struct
{
    char lname[40],fname[40],address[100],phone[12],email[40];
    int id;
    float salary;
    Date bd;
} Employee;
Employee x[100];
char filename[50],Id[10],Lastn[40],Firstn[40],Sal[10],Ad[100],D[3],M[3],Y[5],Ph[12],E[40];
int n=0,c=0;
int validInteger(char *s)
{
    int l=strlen(s),i;
    for(i=0; i<l; i++)
    {
        if(s[i]<'0' || s[i]>'9')
            return 0;
    }
    return 1;
}
int validFloat(char *s)
{
    int l=strlen(s),i,dot=0,num=0;
    for(i=0; i<l; i++)
    {
        if(s[i]>='0' && s[i]<='9')
            num++;
        else if(s[i]=='.')
        {
            if(num<=0)
                return 0;
            else
                dot++;
        }
        else
            return 0;
    }
    if(dot>1)
        return 0;
    return 1;
}
int validFilename()
{
    int l=strlen(filename);
    if(!(filename[l-4]=='.' && filename[l-3]=='t' && filename[l-2]=='x' && filename[l-1]=='t'))
    {
        printf("Invalid file name.\n");
        return 0;
    }
    return 1;
}
int validID()
{
    if(!validInteger(Id))
        printf("Invalid ID!\n");
    return validInteger(Id);
}
int validLname()
{
    int l=strlen(Lastn),i;
    for(i=0; i<l; i++)
    {
        if(!((Lastn[i]>='A' && Lastn[i]<='Z') || (Lastn[i]>='a' && Lastn[i]<='z') || (Lastn[i]=='-')))
        {
            printf("Invalid Name!\n");
            return 0;
        }
    }
    return 1;
}
int validFname()
{
    int l=strlen(Firstn),i;
    for(i=0; i<l; i++)
    {
        if(!((Firstn[i]>='A' && Firstn[i]<='Z') || (Firstn[i]>='a' && Firstn[i]<='z') || (Firstn[i]=='-')))
        {
            printf("Invalid Name!\n");
            return 0;
        }
    }
    return 1;
}
int validSalary()
{
    if(!validFloat(Sal))
        printf("Invalid Salary!\n");
    return validFloat(Sal);
}
int validDOB()
{
    if(validInteger(D) && validInteger(M) && validInteger(Y))
    {
        int d=atoi(D),m=atoi(M),y=atoi(Y);
        if(d>31 || d<1 || m>12 || m<1 || y>2003 || y<1962)
        {
            printf("Invalid Date of Birth!\n");
            return 0;
        }
        else
            return 1;
    }
    printf("Invalid Date of Birth!\n");
    return 0;
}
int validPhone()
{
    int b=validInteger(Ph);
    if(b)
    {
        if(Ph[0]=='0' && Ph[1]=='1' && strlen(Ph)==11)
            return 1;
        printf("Invalid Phone!\n");
        return 0;
    }
    printf("Invalid Phone!\n");
    return 0;
}
int validEmail()
{
    int l=strlen(E),i,at=0,t=0;
    if(E[l-4]=='.' || E[l-3]=='.')
    {
        for(i=0; i<l-4; i++)
        {
            if(E[i]=='@')
            {
                at++;
                if((E[i+1]>='a' && E[i+1]<='z') || (E[i+1]>='A' && E[i+1]<='Z') || (E[i+1]>='0' && E[i+1]<='9'))
                    t=1;
                else
                    t=0;
            }
            if(at>1)
            {
                printf("Invalid E-mail!\n");
                return 0;
            }
        }
        if(!t)
        {
            printf("Invalid E-mail!\n");
            return 0;
        }
        return 1;
    }
    return 0;
}
int loadFile()
{
    int i;
    char p[sizeof(Employee)+1];
    char t;
    FILE *fp=fopen(filename,"r");
    if(!fp)
    {
        printf("Error occurred during opening file %s!\n",filename);
        exit(0);
    }
    else
    {
        for(i=0; !feof(fp); i++)
        {
            t=fgetc(fp);
            if(t==EOF)
                break;
            else
                fseek(fp,-1,SEEK_CUR);
            fgets(p,sizeof(Employee)+1,fp);
            char *token=strtok(p,",");
            x[i].id=atoi(token);
            token=strtok(NULL,",");
            strcpy(x[i].lname,token);
            token=strtok(NULL,",");
            strcpy(x[i].fname,token);
            token=strtok(NULL,",");
            x[i].salary=atof(token);
            token=strtok(NULL,"-");
            x[i].bd.d=atoi(token);
            token=strtok(NULL,"-");
            x[i].bd.m=atoi(token);
            token=strtok(NULL,",");
            x[i].bd.y=atoi(token);
            token=strtok(NULL,",");
            strcpy(x[i].address,token);
            token=strtok(NULL,",");
            strcpy(x[i].phone,token);
            token=strtok(NULL,"\n");
            strcpy(x[i].email,token);
            n++;
        }
        fclose(fp);
        printf("Data loaded successfully.\n");
        return 1;
    }
}
void printEmployee(Employee a)
{
    printf("ID: %d\nLast Name: %s\nFirst Name: %s\nSalary: %f\nDate of Birth: %d-%d-%d\nAddress: %s\nPhone: %s\nE-mail: %s\n",a.id,a.lname,a.fname,a.salary,a.bd.d,a.bd.m,a.bd.y,a.address,a.phone,a.email);
    printf("____________________________________\n");
}
void queryEmployee()
{
    printf("QUERY\n-----\n");
    int i,q=0;
    do
    {
        printf("Enter Last Name of employee: ");
        scanf("%s",Lastn);
    }while(!validLname());
    for(i=0; i<n; i++)
    {
        if(!strcasecmp(x[i].lname,Lastn))
        {
            printf("Employee Found:\n");
            printEmployee(x[i]);
            q++;
        }
    }
    if(!q)
        printf("No employees found!\n");
}
void addEmployee()
{
    printf("ADD\n---\nEnter information of added employee.\n");
    do
    {
        printf("ID: ");
        scanf("%s",Id);
        x[n].id=atoi(Id);
    }while(!validID());
    do
    {
        printf("Last Name: ");
        scanf("%s",Lastn);
        if(Lastn[0]>='a' && Lastn[0]<='z')
            Lastn[0]=Lastn[0]-32;
        strcpy(x[n].lname,Lastn);
    }while(!validLname());
    do
    {
        printf("First Name: ");
        scanf("%s",Firstn);
        if(Firstn[0]>='a' && Firstn[0]<='z')
            Firstn[0]=Firstn[0]-32;
        strcpy(x[n].fname,Firstn);
    }while(!validFname());
    do
    {
        printf("Salary: ");
        scanf("%s",Sal);
        x[n].salary=atof(Sal);
    }while(!validSalary());
    do
    {
        printf("Date of Birth.\nDay: ");
        scanf("%s",D);
        printf("Month: ");
        scanf("%s",M);
        printf("Year: ");
        scanf("%s",Y);
        x[n].bd.d=atoi(D);
        x[n].bd.m=atoi(M);
        x[n].bd.y=atoi(Y);
    }while(!validDOB());
    printf("Address: ");
    getchar();
    gets(Ad);
    strcpy(x[n].address,Ad);
    do
    {
        printf("Phone: ");
        scanf("%s",Ph);
        strcpy(x[n].phone,Ph);
    }while(!validPhone());
    do
    {
        printf("E-mail: ");
        scanf("%s",E);
        strcpy(x[n].email,E);
    }while(!validEmail());
    printf("Employee added successfully.\nNew Employee:\n");
    printEmployee(x[n]);
    n++;
}
void deleteEmployee()
{
    printf("DELETE\n------\n");
    int i,j,del=0;
    do
    {
        printf("Last Name: ");
        scanf("%s",Lastn);
    }while(!validLname());
    do
    {
        printf("First Name: ");
        scanf("%s",Firstn);
    }while(!validFname());
    for(i=0; i<n; i++)
    {
        if(!strcasecmp(x[i].lname,Lastn) && !strcasecmp(x[i].fname,Firstn))
        {
            printf("Employee to be deleted:\n");
            printEmployee(x[i]);
            printf("Press 1 to confirm the delete, press 0 to cancel: ");
            scanf("%d",&c);
            if(c)
            {
                for(j=i; j<n-1; j++)
                {
                    x[j]=(Employee)x[j+1];
                }
                n--;
                del++;
                i--;
            }
        }
    }
    if(!del)
        printf("No employees found!\n");
}
void modifyEmployee()
{
    printf("MODIFY\n------\n");
    int i,employee=0;
    do
    {
        printf("Enter ID of employee to modify: ");
        scanf("%s",Id);
    }while(!validID());
    for(i=0; i<n; i++)
    {
        if(x[i].id==atoi(Id))
        {
            employee++;
            printf("Employee to be modified is:\n");
            printEmployee(x[i]);
            printf("Press 1 to modify,press 0 to cancel and return to main menu: ");
            scanf("%d",&c);
            if(c)
            {
                printf("Press 1 to modify the field, press 0 to skip:\n");
                printf("ID: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("ID -> ");
                        getchar();
                        gets(Id);
                        x[i].id=atoi(Id);
                    }while(!validID());
                }
                printf("Last Name: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("Last Name -> ");
                        getchar();
                        gets(Lastn);
                        if(Lastn[0]>='a' && Lastn[0]<='z')
                            Lastn[0]=Lastn[0]-32;
                        strcpy(x[i].lname,Lastn);
                    }while(!validLname());
                }
                printf("First Name: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("First Name -> ");
                        getchar();
                        gets(Firstn);
                        if(Firstn[0]>='a' && Firstn[0]<='z')
                            Firstn[0]=Firstn[0]-32;
                        strcpy(x[i].fname,Firstn);
                    }while(!validFname());
                }
                printf("Salary: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("Salary -> ");
                        scanf("%s",Sal);
                        x[i].salary=atof(Sal);
                    }while(!validSalary());
                }
                printf("Date of Birth: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("Date of Birth:\nDay -> ");
                        scanf("%s",D);
                        printf("Month -> ");
                        scanf("%s",M);
                        printf("Year -> ");
                        scanf("%s",Y);
                        x[i].bd.d=atoi(D);
                        x[i].bd.m=atoi(M);
                        x[i].bd.y=atoi(Y);
                    }while(!validDOB());
                }
                printf("Address: ");
                scanf("%d",&c);
                if(c)
                {
                    printf("Address -> ");
                    getchar();
                    gets(Ad);
                    strcpy(x[i].address,Ad);
                }
                printf("Phone: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("Phone -> ");
                        scanf("%s",Ph);
                        strcpy(x[i].phone,Ph);
                    }while(!validPhone());
                }
                printf("E-mail: ");
                scanf("%d",&c);
                if(c)
                {
                    do
                    {
                        printf("E-mail -> ");
                        scanf("%s",E);
                        strcpy(x[i].email,E);
                    }while(!validEmail());
                }
                printf("Employee modified successfully.\n");
                printEmployee(x[i]);
            }
        }
    }
    if(!employee)
        printf("No employees found!\n");
}
void sortByLname()
{
    printf("SORT BY LAST NAME\n-----------------\n");
    int i,j;
    Employee t;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
        {
            if((strcmp(x[j].lname,x[j+1].lname))==1)
            {
                t=x[j];
                x[j]=x[j+1];
                x[j+1]=t;
            }
        }
    }
    for(i=0;i<n;i++)
        printEmployee(x[i]);
}
void sortByDOB()
{
    printf("SORT BY DATE OF BIRTH\n--------------------\n");
    int i,j;
    Employee t;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
        {
            if(x[j].bd.y>x[j+1].bd.y)
            {
                t=x[j];
                x[j]=x[j+1];
                x[j+1]=t;
            }
            else if(x[j].bd.y==x[j+1].bd.y)
            {
                if(x[j].bd.m>x[j+1].bd.m)
                {
                    t=x[j];
                    x[j]=x[j+1];
                    x[j+1]=t;
                }
                else if(x[j].bd.m==x[j+1].bd.m)
                {
                    if(x[j].bd.d>x[j+1].bd.d)
                    {
                        t=x[j];
                        x[j]=x[j+1];
                        x[j+1]=t;
                    }
                }
            }
        }
    }
    for(i=0;i<n;i++)
        printEmployee(x[i]);
}
void sortBySalary()
{
    printf("SORT BY SALARY\n--------------\n");
    int i,j;
    Employee t;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
        {
            if(x[j].salary<x[j+1].salary)
            {
                t=x[j];
                x[j]=x[j+1];
                x[j+1]=t;
            }
        }
    }
    for(i=0;i<n;i++)
        printEmployee(x[i]);
}
void saveFile()
{
    printf("SAVE\n----\n");
    int i;
    FILE *fp=fopen(filename,"w");
    if(!fp)
    {
        printf("Error occurred during saving!\n");
        return;
    }
    for(i=0; i<n; i++)
    {
        fprintf(fp,"%d,%s,%s,%f,%d-%d-%d,%s,%s,%s\n",x[i].id,x[i].lname,x[i].fname,x[i].salary,x[i].bd.d,x[i].bd.m,x[i].bd.y,x[i].address,x[i].phone,x[i].email);
    }
    printf("Data Saved Successfully.\n");
    fclose(fp);
    printf("To Quit press 1, to return to main menu press 0: ");
    scanf("%d",&c);
    if(c)
        exit(0);
}
void exitFile()
{
    printf("EXIT\n----\n");
    printf("Warning!! Do you want to quit without saving?\nTo save press 1, to quit press 0: ");
    scanf("%d",&c);
    if(c)
    {
        saveFile();
        exit(0);
    }
    else
        {
            printf("To exit without saving press 1, to return to main menu press 0: ");
            scanf("%d",&c);
            if(c)
                exit(0);
        }
}
int main()
{
    printf("Welcome Guest.\nBefore starting your session, please make sure you have inserted your file of type(.txt) into the folder of the code running to be able to work on.\n");
    do
    {
        printf("Enter name of file to work on: ");
        scanf("%s",filename);
    }while(!validFilename() && !loadFile());
    loadFile();
    do
    {
        printf("Main Menu:\n1.Query\n2.Add\n3.Delete\n4.Modify\n5.Sort and Print\n6.Save\n7.Exit\n");
        printf("Enter number of your choice: ");
        scanf("%d",&c);
        switch(c)
        {
        case 1:
            queryEmployee();
            break;
        case 2:
            addEmployee();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            modifyEmployee();
            break;
        case 5:
            printf("Choose reference of sorting -> 1.Last Name\t2.Date of Birth\t3.Salary: ");
            scanf("%d",&c);
            switch(c)
            {
            case 1:
                sortByLname();
                break;
            case 2:
                sortByDOB();
                break;
            case 3:
                sortBySalary();
                break;
            }
            break;
        case 6:
            saveFile();
            break;
        case 7:
            exitFile();
            break;
        }
    }while(1);
    return 0;
}
