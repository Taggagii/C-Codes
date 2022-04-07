#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

// static char *string_duplicate(const char *input, const char *ending_point) {
//     assert(input);
//     assert(ending_point);
//     assert(ending_point > input);

//     int length = ending_point - input;
//     char *new = malloc((length + 1) * sizeof(char));
//     for (int i = 0; i < length; ++i) {
//         new[i] = input[i];
//     }
//     new[length] = '\0';
//     return new;
// }

static char *reset_temp(int *temp_size, int *temp_len) {
    assert(temp_size);
    assert(temp_len);

    char *temp = malloc(sizeof(char));
    *temp_size = 1;
    *temp_len = 0;
    return temp;
}

static void store_temp(char **output, char *temp, int *length, int temp_len) {
    assert(output);
    assert(temp);

    temp[temp_len] = '\0';
    temp = realloc(temp, (temp_len + 1) * sizeof(char));

    output[(*length)++] = temp;
}



char **split_strings(const char *input_string, int *length) {
    assert(input_string);
    assert(length);
    assert(strlen(input_string)); // non-zero length input

    *length = 0;

    // dynamically sized within loop
    // count of objects contained held in [length]
    char **output = malloc(sizeof(char *));
    int output_size = 1;

    // dynamically sized within loop
    int temp_size, temp_len;
    char *temp = reset_temp(&temp_size, &temp_len);

    
    int index = 0;
    while (input_string[index] != '\0') {

        if (input_string[index] == ' ') {
            // move the index up to the next real character
            while (input_string[++index] == ' ');

            // only save the value if it's not empty
            if (!temp_len) continue;

            // dynamically update output space
            if (*length == output_size - 1) {
                output_size *= 2;
                output = realloc(output, output_size * sizeof(char *));
            }
            
            store_temp(output, temp, length, temp_len);

            // now that temp is saved we can create the next memory address
            temp = reset_temp(&temp_size, &temp_len);
            
            
        } else {
            // dynamically update temp space
            if (temp_len == temp_size - 1) {
                temp_size *= 2;
                temp = realloc(temp, temp_size * sizeof(char));
            }
            
            // save each character
            temp[temp_len] = input_string[index];
            ++temp_len;
            ++index;
        }
   
    }

    if (temp_len) store_temp(output, temp, length, temp_len);
    
    output = realloc(output, *length * sizeof(char *));
    

    return output;
}   

static void print_array(char **array, int length) {
    assert(array);
    printf("[");
    for (int i = 0; ;) {
        printf("%s", array[i]);
        if (++i == length) break;
        printf(", ");
    }
    printf("]\n");
}



int main(void) {
    int length = 0;
    char **output = split_strings("testing things that happen in my word", &length);
    print_array(output, length);

    free(output);

}