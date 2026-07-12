#include "cacheSim.h"

// In this question, we will assume DRAM will take a 4-byte values starting from 0 to 
void init_DRAM()
{
	unsigned int i=0;
	DRAM = malloc(sizeof(char) * DRAM_SIZE);
	for(i=0;i<DRAM_SIZE/4;i++)
	{
		*((unsigned int*)DRAM+i) = i;
	}
}

void printCache()
{
	int i,j,k;
	printf("===== L1 Cache Content =====\n");
	for(i=0;i<2;i++)
	{
		printf("Set %d :", i);
		for(j=0;j<2;j++)
		{
			printf(" {(TAG: 0x%x)", (unsigned int)(L1_cache[i][j].tag));
			for(k=0;k<16;k++)
				printf(" 0x%x,", (unsigned int)(L1_cache[i][j].data[k]));
			printf(" |");
		}
		printf("\n");
	}
	printf("===== L2 Cache Content =====\n");
	for(i=0;i<4;i++)
	{
		printf("Set %d :", i);
		for(j=0;j<4;j++)
		{
			printf(" {(TAG: 0x%x)", (unsigned int)(L2_cache[i][j].tag));
			for(k=0;k<16;k++)
				printf(" 0x%x,", (unsigned int)(L2_cache[i][j].data[k]));
			printf(" |");
		}
		printf("\n");
	}
}

// part 2 
u_int32_t read_fifo(u_int32_t address){
	u_int32_t result = 0;
	int i;
	for( i = 0; i < 4; i++){
		u_int32_t current_addr = address + i;
		fetch_block_to_cashes(current_addr)
		unsigned int l1_set = getL1SetID(current_addr);
		unsigned int l1_tag = getL1Tag(current_addr);
		unsigned int offset = current_addr & 0xF;
		unsigned char byte_val = 0;

		int w;
		for (w= 0; w < 2; w ++ ){
			if ( L1_cache[l1_set][w]. valid && L1_cache[l1_set][w].tag == l1_tag){
				byte_val = L1_cache[l1_set][w].data[offset];
				break;
			}
			result |= ((u_int32_t)byte_val) << (8 * i);
		}
	}
	return result;
}

// part 1
int L1lookup(u_int32_t address){
	unsigned int set = getL1SetID(address)
	u_int32_t tag = getL1Tag(address);
	for (int way = 0; way < 2; way ++){
		if (L1_cache[set][way].timeStamp != 0 && L1_cache[set][way].tag == tag){
			return 1;
		}
	}
	return 0;
}

int L2lookup(u_int32_t address){
	unsigned int set = getL2SetID(address)
	u_int32_t tag = getL2Tag(address);
	for (int way = 0; way < 4; way ++){
		if (L2_cache[set][way].timeStamp != 0 && L2_cache[set][way].tag == tag){
			return 1;
		}
	}
	return 0;
}

unsigned int getL1SetID(u_int32_t address){
	return (address >> 4) & 0x1;
}

unsigned int getL1Tag(u_int32_t address){
	return address >> 5;
}

unsigned int getL2SetID(u_int32_t address){
	return (address >> 4) & 0x3;
}

unsigned int getL2Tag(u_int32_t address){
	return address >> 6;
}

// part 3
void write(u_int32_t address, u_int32_t data){
	int i;
	for (i = 0; i < 4; i ++){
		u_int32_t current_addr = address +i;
		unsigned char byte_val = (data >> (8 * i)) & 0xFF;
		if (current_addr < DRAM_SIZE){
			DRAM[current_addr] = byte_val;
		}
		unsigned int l1_set = getL1SetID(current_addr);
		unsigned int l1_tag = getL1Tag(current_addr);
		unsigned int offset = current_addr & 0xF;
		int w;
		for (w = 0; w < 2; w++){
			if (L1_cache[l1_set][w].valid && L1_cache[l1_set][w].tag == l1_tag){
				L1_cache[l1_set][w].data[offset] = byte_val;
				break;
			}
		}
		unsigned int l2_set = getL2SetID(current_addr);
		unsigned int l2_tag = getL2Tag(current_addr);
		for (w = 0; w < 4; w++){
			if(L2_cache[l2_set][w].valid && L2_cache[l2_set][w].tag == l2_tag){
				L2_cache[l2_set][w].data[offset] = byte_val;
				break;
			}
		}
	} 
	read_fifo(address);
	return;
}


int main()
{
	init_DRAM();
	cacheAccess buffer;
	int timeTaken=0;
	FILE *trace = fopen("input.trace","r");
	int L1hit = 0;
	int L2hit = 0;
	cycles = 0;
	while(!feof(trace))
	{
		fscanf(trace,"%d %x %x", &buffer.readWrite, &buffer.address, &buffer.data);
		printf("Processing the request for [R/W] = %d, Address = %x, data = %x\n", buffer.readWrite, buffer.address, buffer.data);

		// Checking whether the current access is a hit or miss so that we can advance time correctly
		if(L1lookup(buffer.address))// Cache hit
		{
			timeTaken = 1;
			L1hit++;
		}
		else if(L2lookup(buffer.address))// L2 Cache Hit
		{
			L2hit++;
			timeTaken = 5;
		}
		else timeTaken = 50;
		if (buffer.readWrite) write(buffer.address, buffer.data);
		else read_fifo(buffer.address);
		cycles+=timeTaken;
	}
	printCache();
	printf("Total cycles used = %ld\nL1 hits = %d, L2 hits = %d", cycles, L1hit, L2hit);
	fclose(trace);
	free(DRAM);
	return 0;
}




