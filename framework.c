#include <stdio.h>
#include <stdlib.h>
#include <line.h>

#define fieldValueSize 50 
#define menuSize 300
#define recordsFileName "records.dat" 
#define fieldNamesFileName "fields.cfg"
#define menuFileName "menu.cfg"


void createRecord(int);
void showAllRecords();
void updateRecord();
void deleteAllRecord();
int fieldCount();
void printMenu();
void printfield(int);

char **fieldNames;

void main()
{
	int choice;
	int fieldcount = fieldCount();
	printfield(fieldcount);
	system("cls");
	while (1)
	{
		printMenu();
		scanf(" %d", &choice);
		fflush(stdin);
		switch (choice)
		{
		case 1: createRecord(fieldcount);
			   	break;
		case 2: showAllRecords(fieldcount);
				break;
		case 3: updateRecord(fieldcount);
				break;
		case 4: deleteAllRecord();
				break;
		case 5: exit(0);
		}
	}
}

void showAllRecords(int fieldCount)
{
	char fieldscontent[fieldCount][fieldValueSize];
	int counter = 1;
	system("cls");
	FILE *fp_account = fopen(recordsFileName, "r");
	while (fread(fieldscontent, sizeof(fieldscontent), 1, fp_account))
	{
		printf("\nCustomer %d details are:\n",counter);
		for (int counter = 0; counter < fieldCount; counter++)
		{	
			printf("%s is    %s\n", fieldNames[counter], fieldscontent[counter]);			
		}	
		counter++;
	}
	printf("\n");
	
	fclose(fp_account);
}

void deleteAllRecord()
{
	FILE *fp_accounts = fopen(recordsFileName, "w");
	fclose(fp_accounts);
}

void createRecord(int fieldCount)
{
	char fieldsContent[fieldCount][fieldValueSize];
	FILE *fp_account = fopen(recordsFileName, "a");
	
	for (int counter = 0; counter < fieldCount; counter++)
	{
		printf("Enter %s: ",fieldNames[counter]);
		fgets(fieldsContent[counter], sizeof(fieldsContent[counter]), stdin);
		removenewline(fieldsContent[counter]);	
	}
	fwrite(fieldsContent, sizeof(fieldsContent), 1, fp_account);
	fclose(fp_account);
	system("cls");
}

void updateRecord(int fieldCount)
{
	char actualIdNumber[fieldValueSize];
	char recordValues[fieldCount][fieldValueSize];
	printf("Enter %s: ",fieldNames[0]);
	scanf("%s", actualIdNumber);
	fflush(stdin);
	FILE *fp_account = fopen(recordsFileName, "r+");

	while (fread(recordValues, sizeof(recordValues), 1, fp_account))
	{
		if(strcmp(actualIdNumber, recordValues[0]) == 0)
		{
			int choice;
			for (int counter = 0; counter < fieldCount; counter++)
			{
				printf("%d %s\n", counter + 1, fieldNames[counter]);
			}
			printf("Which field do you want to update? ");
			scanf("%d", &choice);
			fflush(stdin);			
			printf("Enter new %s", fieldNames[choice - 1]);
			fgets(recordValues[choice - 1], sizeof(recordValues[choice]), stdin);
			removenewline(recordValues[choice - 1]);
			fseek(fp_account, - sizeof(recordValues), SEEK_CUR);
			fwrite(recordValues, sizeof(recordValues), 1, fp_account);
			fclose(fp_account);
		}
	}

}
void printMenu()
{
	char menuOptions[menuSize];
	FILE *fp_menu = fopen(menuFileName, "r+");
    int n = fread(menuOptions, 1, sizeof(menuOptions), fp_menu);
    menuOptions[n] = '\0';
    printf("%s ", menuOptions);
    fclose(fp_menu);
}

void printfield(int count)
{
	
	FILE *fp_fields = fopen(fieldNamesFileName, "r");
	int  fieldCounter = 0;
	fieldNames = malloc(count * sizeof(char*));
	for (int counter = 0;counter < count; counter++)
	{
		fieldNames[counter] = malloc(fieldValueSize);
	}

	while (fgets(fieldNames[fieldCounter], fieldValueSize, fp_fields) != NULL)
		{
			removenewline(fieldNames[fieldCounter]);
			fieldCounter++;
		}
	
	fclose(fp_fields);	
}

int fieldCount()
{
	int fieldCounter = 0;
	char field[fieldValueSize];
	FILE *fp_field = fopen(fieldNamesFileName, "r");

	while (fgets(field, sizeof(field), fp_field) != NULL)
	{
		fieldCounter++;
	}
	fclose(fp_field);
	return fieldCounter;
}
