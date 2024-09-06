int* create_buffer();
int* push_front(int* buffer, int* size, const int element);
int* push_back(int * buffer, int * size, const int element);
int* remove_element(int* buffer, int* size, const int index);
void current_state(int* buffer, const int size);
int* insert(int* buffer, int* size, const int index, const int element);
void destroy_buffer(int** buffer, int* size);
