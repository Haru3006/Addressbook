#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount=0;
    FILE *fp=fopen("contact.txt","r");
    if(fp==NULL)
    {
        printf("Reading Contacts.txt failed\n");
        return ;
    }
    else
    {
        printf("Initialized successfuly\n");
    }
    int i=0;
    //will run till the end of file.
    while(fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email)!=EOF) 
    {
        i++;
        addressBook->contactCount++;
    }
    fclose(fp);
}


void listContacts(AddressBook *addressBook)
{
    printf("________________________________________________________________________________________\n");
    //printf("\n");
    printf("| %-6s | %-25s | %-15s | %-30s|\n", "Sl No", "Name", "Phone Number", "Email");
    printf("________________________________________________________________________________________\n");

    
    for(int i=0; i<addressBook->contactCount; i++)
    {
        printf("| %-6d | %-25s | %-15s | %-30s|\n",i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("________________________________________________________________________________________\n");

}


void createContact(AddressBook *addressBook)
{
    char temp_name[30];
    char temp_phone[15];
    char temp_mail[30];
    int i,flag,chances;

    //Name
    chances=0;
    while(chances < 3)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",temp_name);

        flag=1; //name is valid(assumption)
        for(i=0;temp_name[i]!=0;i++)
        {
            if(!((temp_name[i] >= 'A' && temp_name[i] <= 'Z') ||
                 (temp_name[i] >= 'a' && temp_name[i] <= 'z') ||
                 (temp_name[i] == ' ')))
            {
                flag=0;
                break;
            }
        }
        
        if(flag==1)
        {
            break;
        }
        printf("Invalid Name\n");
        chances++;
    }

    if(chances == 3 && flag != 1)
    {
        printf("Too many Attempts. Exiting...\n");
        return;
    }


    chances=0;
    while(chances < 3)
    {
        printf("Enter the Phone number: ");
        scanf(" %s",temp_phone);

        flag=1; //phone number is valid(assumption)

        if (strlen(temp_phone) != 10)
            flag = 0;

        for (i = 0; temp_phone[i] != '\0' && flag; i++)
        {
            if (!(temp_phone[i] >= '0' && temp_phone[i] <= '9'))
                flag = 0;
        }
        
        if(flag==1)
        {
            break;
        }
        printf("Invalid Phone Number\n");
        chances++;
    }

    if(chances == 3 && flag != 1)
    {
        printf("Too many Attempts. Exiting...\n");
        return;
    }

    chances = 0;
    while(chances < 3)
    {
        printf("Enter the mail ID: ");
        scanf(" %s", temp_mail);

        flag=1;

        int count = 0;
        int index = -1; //if not available will remain as -1(NULL)
        
        // Count '@' and store position
        for (int i = 0; temp_mail[i] != '\0'; i++)
        {
            if (temp_mail[i] == '@')
            {
                count++;
                index = i;
            }
        }
        
        // Only one '@' and must have at least one char before and after '@'

        if (count != 1 || index == 0 || temp_mail[index + 1] == '\0')
        {
            flag = 0;
        }
        else
        {
            // Username(mail) part must be only letters or digits
            for (int i = 0; i < index; i++)
            {
                if (!((temp_mail[i] >= 'a' && temp_mail[i] <= 'z') || (temp_mail[i] >= '0' && temp_mail[i] <= '9')))
                {
                    flag = 0;
                    break;
                }
            }
            // Mail end must be .com
            int len = strlen(temp_mail);
            // compare if the last 4 letters ends with '.com'
            if (len < 5 || strcmp(temp_mail + len - 4, ".com") != 0) 
            {
                flag = 0;
            }
        }

        if (flag == 1)
        {
            break;
        }
        else
        {
            printf("Invalid mail ID\n");
            chances++;
        }
    }
    
    if(chances == 3 && flag != 1)
    {
        printf("Too many Attempts. Exiting...\n");
        return;
    }


   
 i = addressBook->contactCount; 

    strcpy(addressBook->contacts[i].name, temp_name);
    strcpy(addressBook->contacts[i].phone, temp_phone);
    strcpy(addressBook->contacts[i].email, temp_mail);

    addressBook->contactCount++; // increase count

    printf("Contact added successfully!\n");

}

void searchContact(AddressBook *addressBook)
{
    char temp_name[30];
    char temp_phone[15];
    char temp_mail[30];
    int choose,chances = 0,found;
    /*
    1. ask user based on what to search
        1.name
        2.phone
        3.mail
    */
    printf("\nSearch Contact Menu:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    //2.Read option
    scanf("%d", &choose);

    while(chances < 3)
    {
        found = 0;
        switch(choose)
        {
            /*
            3. switch option
        case 1:
        //search based on name
       step 1. Read now
       step 2. Run a loop from 0 to contactCount-1
        {
            1.Fetch addressBook->contacts.name[i] 
            2.strstr(find substring name is found)
            yes -> print then goto step 2
            no -> goto step 2
        }
            */
            case 1:
                printf("Enter the name to search: ");
                scanf(" %[^\n]", temp_name);
                
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].name, temp_name))
                    {

                        printf("%-20s %-15s %-30s\n",addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                            found = 1;

                    }
                }
                break;

                /*
                case 2:
        //search based on phone number
       step 1. Read now
       step 2. Run a loop from 0 to contactCount-1
        {
            1.Fetch addressBook->contacts.phone[i] 
            2.strstr(find substring phone is found)
            yes -> print then goto step 2
            no -> goto step 2
        }
                */

            case 2:
                printf("Enter the phone number to search: ");
                scanf("%s",temp_phone);
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strstr(addressBook->contacts[i].phone, temp_phone))
                    {
                        printf("%-20s %-15s %-30s\n",addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                break; 
            case 3:
                printf("Enter the email to search: ");
                scanf("%s",temp_mail);
                for(int i=0; i<addressBook->contactCount; i++)
                {
                    if(strstr(addressBook->contacts[i].email, temp_mail))
                    {
                        printf("%-20s %-15s %-30s\n",addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                break;
            default :
                printf("Invalid choice\n");
                return;
        }
        
        if(found == 1)
        {
            return;
        }

        printf("Not found. Try again.\n");
        chances++;

    }
}

void editContact(AddressBook *addressBook)
{
    char temp_name[30];
    char temp_phone[15];
    char temp_mail[30];
    int i, flag, chances;

    chances = 0;
    while (chances < 3)
    {
        printf("Enter the name to edit: ");
        scanf(" %[^\n]", temp_name);

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, temp_name) == 0)
            {
                // For editing Name
                chances = 0;
                while (chances < 3)
                {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", temp_name);

                    flag = 1; // assuming to be correct
                    for (int j = 0; temp_name[j] != '\0'; j++)
                    {
                        if (!((temp_name[j] >= 'A' && temp_name[j] <= 'Z') ||
                              (temp_name[j] >= 'a' && temp_name[j] <= 'z') ||
                              temp_name[j] == ' '))
                        {
                            flag = 0; //Invalid Name
                            break;
                        }
                    }

                    if (flag == 1)
                        break;

                    printf("Invalid name\n");
                    chances++;
                }

                if (chances == 3) 
                return;

                //  For editing Phone number
                chances = 0;
                while (chances < 3)
                {
                    printf("Enter new phone: ");
                    scanf("%s", temp_phone);

                    flag = 1;
                    if (strlen(temp_phone) != 10)
                        flag = 0;

                    for (int j = 0; temp_phone[j] != '\0' && flag; j++)
                    {
                        if (!(temp_phone[j] >= '0' && temp_phone[j] <= '9'))
                            flag = 0;
                    }

                    if (flag)
                        break;

                    printf("Invalid phone\n");
                    chances++;
                }

                if (chances == 3) return;

                // For editing EMAIL 
                chances = 0;
                while (chances < 3)
                {
                    printf("Enter new email: ");
                    scanf("%s", temp_mail);

                    flag = 1;
                    int count = 0, index = -1;

                    for (int j = 0; temp_mail[j] != '\0'; j++)
                    {
                        if (temp_mail[j] == '@')
                        {
                            count++;
                            index = j;
                        }
                    }

                    int len = strlen(temp_mail);
                    if (count != 1 || index == 0 || temp_mail[index + 1] == '\0')
                        flag = 0;
                    else if (len < 5 || strcmp(temp_mail + len - 4, ".com") != 0)
                        flag = 0;

                    if (flag == 1)
                        break;

                    printf("Invalid email\n");
                    chances++;
                }

                if (chances == 3) return;

                //Copying DATA
                strcpy(addressBook->contacts[i].name, temp_name);
                strcpy(addressBook->contacts[i].phone, temp_phone);
                strcpy(addressBook->contacts[i].email, temp_mail);

                printf("Contact updated successfully!\n");
                return;
            }
        }

        printf("Name not found. Try again.\n");
        chances++;
    }

    printf("Too many attempts. Exiting...\n");
}

void deleteContact(AddressBook *addressBook)
{
    char temp_name[30];
    int i, j, chances = 0, found;

    while (chances < 3)
    {
        //read complete name
        printf("Enter the name to delete: ");
        scanf(" %[^\n]", temp_name);

        found = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            /* Find name is present?
            No-> chances 3(got to step 1)
            */
            if (strcmp(addressBook->contacts[i].name, temp_name) == 0)
            {
                /* shift contacts */
                for (j = i; j < addressBook->contactCount - 1; j++)
                {
                    /*
                    Yes->  run a j loop from index(where the contact to delete is found/present) to contactCount-1;
                    {strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name)}
                    contactCount--;
                    */
                    strcpy(addressBook->contacts[j].name,
                           addressBook->contacts[j + 1].name);
                    strcpy(addressBook->contacts[j].phone,
                           addressBook->contacts[j + 1].phone);
                    strcpy(addressBook->contacts[j].email,
                           addressBook->contacts[j + 1].email);
                }

                addressBook->contactCount--;
                printf("Contact deleted successfully!\n");
                return;
            }
        }

        printf("Name not found. Try again.\n");
        chances++;
    }

    printf("Too many attempts. Exiting...\n");
}

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fw = fopen("contact.txt", "w");
    if(fw == NULL)
    {
        printf("Not saved contacts to file.\n");
        return;
    }

    // Run a loop contactCount times
    for(int i=0; i<addressBook->contactCount; i++)
    {
        /*
        1. Read  name from addressBoard, write it to the file.
            2. Write ','
            3. Read phone, write to file
            4. Write ','
            5. Read mail
            6. Write '\n'
        */
        fprintf(fw, "%s,%s,%s\n",addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);

    }

    // Close the file
    fclose(fw);

    printf("Contacts saved successfully.\n");
            
    //stop
        
}