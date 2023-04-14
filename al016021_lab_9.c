#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct RecordType** record;
    int tableSize;
    int num;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz){
    
    int i;

	for (i=0;i<hashSz;++i)
	{
        printf("Index %d -> ", i);
		// if index is occupied with any records, print all
        for(int j = 0; j < hashSz; j++){
        if(pHashArray->record[j] != NULL){
            printf("%d, %c, %d -> ", pHashArray->record[j]->id, pHashArray->record[j]->name, pHashArray->record[j]->order);
        }
        else{
            printf("NULL");
        }

        printf("\n");
		}
	}
}


int main(void){
    struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("lab9inp.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
    struct HashType *pHashArray;
	int hashSz = 11;

	pHashArray = calloc(hashSz, sizeof(struct HashType));

    displayRecordsInHash(pHashArray, hashSz);

    free(pRecords);

    return 0;
}

