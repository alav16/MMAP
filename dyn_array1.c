#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#define BUF_SIZE 1024

int* create_buffer()
{
	int* p;
	p = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if(p == NULL){
	perror("mmap");
	}
}
int* extend(int* buffer, int size){
	int* new_buffer = mmap(NULL, BUF_SIZE * 2, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	if(new_buffer == NULL){
		perror("mmap");
	}
	for(int i = 0; i < size; ++i){
		new_buffer[i] = buffer[i];
	}
	munmap(buffer, BUF_SIZE);
	return new_buffer;
}
int* push_front(int* buffer, int* size, const int element)
{
	if(*size == 0){
		buffer[0] = element;
		(*size)++;
		return buffer;
	}
	if((*size) + 1 > BUF_SIZE){
		buffer = extend(buffer, *size);
	}
	for(int i = (*size); i >= 0; --i){
		buffer[i] = buffer[i - 1];
	}
	buffer[0] = element;
	(*size)++;
	return buffer;
}
int* push_back(int* buffer, int* size, const int element)
{
	if((*size) + 1 > BUF_SIZE){
		buffer = extend(buffer, *size);
	}
	buffer[*size] = element;
	(*size)++;
	return buffer;
}
int* remove_element(int* buffer, int* size, const int index)
{
	for(int i = index; i < (*size) - 1; ++i){
		buffer[i] = buffer[i + 1];
	}
	buffer[(*size) - 1] = 0;
	(*size)--;
	return buffer;
}
void current_state(int* buffer, const int size)
{
	for(int i = 0; i < size; ++i){
		printf("%d ", buffer[i]);
	}
}
int* insert(int* buffer, int* size, const int index, const int element)
{
	if((*size) + 1 > BUF_SIZE){
		buffer = extend(buffer, *size);
	}
	for(int i = (*size); i > index; --i){
		buffer[i] = buffer[i - 1];
	}
	buffer[index] = element;
	(*size)++;
	return buffer;
}
void destroy_buffer(int** buffer, int* size)
{
	if(*buffer != NULL){
		munmap(*buffer, (*size) * sizeof(int));
		*buffer = NULL;
	}
	*size = 0;
}
