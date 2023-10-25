//
//  s-des.c
//  Task_1
//
//  Created by Shreya Wagley 20591029
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variables
char output[9];// ciphertext
char key_tmp[11];// used as intermediate
char k1[9];	// subkey k1
char k2[9];	// subkey k2
char l[5];	// 4-bit left part of the data block.
char r[5];  // 4-bit right part of the data block.
char binary_tmp[3]; // Stores a 2-bit binary string with a null terminator.
char s0_box[4][4]; // Represents the S-box S0, a 4x4 matrix used in substitution.
char s1_box[4][4]; // Represents the S-box S1, another 4x4 matrix used in substitution.


//-------Constants used for Permutation and Switching -------
const int IP[8] = 
{1, 5, 2, 0, 3, 7, 4, 6};

const int IPI[8] = 
{3, 0, 2, 4, 6, 1, 7, 5};

const int EP[8] = 
{3, 0, 1, 2, 1, 2, 3, 0};

const int P4[4] =
{1, 3, 2, 0};

const int P10[11] = 
{2, 4, 1, 6, 3, 9, 0, 8, 7, 5};

const int P8[8] =
{5, 2, 6, 3, 7, 4, 9, 8};

const int SW[8] =
{4, 5, 6, 7, 0, 1, 2, 3};

// --------------Standard S-DES Functions--------------

// Perform an initial permutation on the 'input' array.
void initial_permutation(char *input)
{
    int i;

    // Iterate through the elements of the 'input' array and rearrange them based
    //on the IP (Initial Permutation) table, storing the result in the 'output' array.
    for (i = 0; i < 8; i++) {
        output[i] = input[IP[i]];
    }

    output[8] = '\0'; // Add a null terminator to create a valid string.

    // The 'output' array now contains the result of the initial permutation.
}

// Perform an inverse initial permutation on the 'input' array.
void initial_permutation_inverse(char *input)
{
    char output_final[9]; // Initialize an array to store the output of the inverse permutation.
    int i;

    // Iterate through the elements of the 'input' array and rearrange them based
    //on the IPI (Inverse Initial Permutation) table, storing the result in 'output_final'.
    for (i = 0; i < 8; i++) {
        output_final[i] = input[IPI[i]];
    }

    output_final[8] = '\0'; // a null terminator to create a valid string.

    // Copy the result, which is the inverse-permuted input, back to the 'output' array.
    strcpy(output, output_final);
}


// Perform a switch on halves of the input.
void switch_halves(char *input)
{
    char out_tmp_switched[9]; // Initialize a temporary array to store the switched halves.
    int i;

    // Iterate through the elements of the 'input' array and rearrange them based
    //on the SW (Switch) table, storing the result in 'out_tmp_switched'.
    for (i = 0; i < 8; i++) {
        out_tmp_switched[i] = input[SW[i]];
    }
    
    out_tmp_switched[8] = '\0'; // Add a null terminator to create a valid string.

    // Copy the result back to the 'output' array.
    strcpy(output, out_tmp_switched);
}

// Perform an Expansion/Permutation (EP) on the input.
void expansion_permutation(char *input)
{
    int i;

    // Apply the expansion permutation by copying elements from the 'input' array to
    //the 'output' array based on the EP table.
    for (i = 0; i < 8; i++) {
        output[i] = input[EP[i]];
    }

    output[8] = '\0'; // Add a null terminator to create a valid string.
}

// Perform a P4 permutation on the input.
void p4_permutation(char *input)
{
    char F_output[5]; // Initialize a character array to hold the permuted result.
    int i;

    // Apply the permutation by copying elements from the 'input' array to 'F_output' based on P4 table.
    for (i = 0; i < 4; i++) {
        F_output[i] = input[P4[i]];
    }
   
    F_output[4] = '\0'; // Add a null terminator to create a valid string.
    // Copy the permuted result back to the 'output' array.
    strcpy(output, F_output);
}

// Divide an 8-bit input into two 4-bit parts: l (left) and r (right).
void divide_block(char *output)
{
    int i, j;
    // Copy the first 4 bits of the input into the 'l' array
    for (i = 0; i < 4; i++) {
        l[i] = output[i];
    }
    // Add a null terminator to create a valid string
    l[i] = '\0';

    // Copy the next 4 bits of the input into the 'r' array
    for (j = 0; j < 4; j++) {
        r[j] = output[i];
        i++;
    }
    r[j] = '\0'; // Add a null terminator to create a valid string
}

// Perform decimal conversion from a 2-bit binary string to an integer
int convert_to_decimal(char *str)
{
    // Check if the binary string has a length other than 2
    if (strlen(str) != 2)
        return -1;

    // Check the binary string value and return the corresponding decimal value
    if (strcmp(str, "00") == 0)
        return 0;
    else if (strcmp(str, "01") == 0)
        return 1;
    else if (strcmp(str, "10") == 0)
        return 2;
    else if (strcmp(str, "11") == 0)
        return 3;

    // If the binary string is not recognized, return -1 to indicate an error
    return -1;
}


// Perform binary conversion from an integer to a 2-bit binary string
void convert_to_binary(int num, char *binary)
{
    // Check the integer value and assign the corresponding binary string
    if (num == 0)
        strcpy(binary, "00");
    else if (num == 1)
        strcpy(binary, "01");
    else if (num == 2)
        strcpy(binary, "10");
    else if (num == 3)
        strcpy(binary, "11");
}


// Perform XOR operation on two binary strings (str1 and str2)
void xor(char *str1, char *str2)
{
    unsigned long int i;
    // Check if the input binary strings have different lengths
    if (strlen(str1) != strlen(str2)) {
        printf("Error: XOR operation does not support different string lengths.\n");
        exit(0);
    }
    // Iterate through the binary strings and perform XOR on each corresponding bit
    for (i = 0; i < strlen(str1); i++) {
        if (str1[i] == str2[i]) {
            // If the bits are the same, set the result bit to '0'
            output[i] = '0';
        }
        else {
            // If the bits are different, set the result bit to '1'
            output[i] = '1';
        }
    }
    // Terminate the result string with a null character to make it a valid C string
    output[i] = '\0';
}


// Function for S0
void s0_items()
{
	int i, j, k = 0;
    // Predefined values for S-box S2 (16 values in a 4x4 array)
	int item[16] = {1, 0, 3, 2,
					3, 2, 1, 0,
					0, 2, 1, 3,
					3, 1, 3, 2};
    // Loop through rows and columns to populate S-box S0 with the predefined values
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			s0_box[i][j] = item[k];
			k++;
		}
	}
}

// Function for initializing S-box S1 with predefined values
void s1_items()
{
    int i, j, k = 0;
    // Predefined values for S-box S1 (16 values in a 4x4 array)
    int item[16] = {0, 1, 2, 3,
                    2, 0, 1, 3,
                    3, 0, 1, 0,
                    2, 1, 0, 3};

    // Loop through rows and columns to populate S-box S1 with the predefined values
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s1_box[i][j] = item[k];
            k++;
        }
    }
}



// Calculate the output for the given S-box (0 or 1) and return a decimal number.
int sbox_s(char *output, int i)
{
    char tmp[3];
    int row;
    int column;
    int s0;
    int s1;

    // Check which S-box (0 or 1) to process
    if (i == 0) {
        // S-box S0
        // Extract the bits from the input string for S0
        tmp[0] = output[0];
        tmp[1] = output[3];
        tmp[2] = '\0';
        // Convert the extracted bits to a decimal value (row)
        row = convert_to_decimal(tmp);
        tmp[0] = output[1];
        tmp[1] = output[2];
        tmp[2] = '\0';
        // Convert the extracted bits to a decimal value (column)
        column = convert_to_decimal(tmp);
        // Retrieve the S0-box value at the specified row and column
        s0_items();
        s0 = s0_box[row][column];
        // Return the decimal value obtained from S0
        return s0;
    } else if (i == 1) {
        // S-box S1
        // Extract the bits from the input string for S1
        tmp[0] = output[4];
        tmp[1] = output[7];
        tmp[2] = '\0';
        // Convert the extracted bits to a decimal value (row)
        row = convert_to_decimal(tmp);
        tmp[0] = output[5];
        tmp[1] = output[6];
        tmp[2] = '\0';
        // Convert the extracted bits to a decimal value (column)
        column = convert_to_decimal(tmp);
        // Retrieve the S1-box value at the specified row and column
        s1_items();
        s1 = s1_box[row][column];
        // Return the decimal value obtained from S1
        return s1;
    } else {
        // Invalid S-box index, return -1 to indicate an error
        return -1;
    }
}



// Perform the F_mapping intermediate process between input and subkey
void F_mapping(char *output, char *subkey)
{
    /*
        This mapping is an intermediate process
        between the input and subkey passed
        to the fk function
    */
    char binary[3];
    int s0;
    int s1;
    char output_sbox[5];

    // Divide the output into left (l) and right (r) halves
    divide_block(output);

    // Expand and permute the right half (r)
    expansion_permutation(r);

    // Perform an XOR operation between the expanded right half (r) and the provided subkey
    xor(output, subkey);

    // Apply S-box operation S0 to the XOR result and convert the output to binary
    s0 = sbox_s(output, 0);
    convert_to_binary(s0, binary);

    // Copy the binary result into the output_sbox
    strcpy(output_sbox, binary);

    // Apply S-box operation S1 to the XOR result and convert the output to binary
    s1 = sbox_s(output, 1);
    convert_to_binary(s1, binary);

    // Concatenate the binary result with the output_sbox
    strcat(output_sbox, binary);

    // Perform P4 permutation on the concatenated result
    p4_permutation(output_sbox);
}


// Perform the Feistel function (Fk) using the provided subkey
void fk(char *output, char *subkey)
{
    // Apply the F_mapping function to expand and permute the right half (r) with the subkey
    F_mapping(output, subkey);
    
    // Perform an XOR operation between the left half (l) and the output of F_mapping
    xor(l, output);
    
    // Concatenate the result of the XOR operation (l XOR Fk) with the right half (r)
    strcat(output, r);
}


//---------Keys Generation Functions-----------

// Perform P10 permutation on the original 10-bit key
void p10_key_permutation(char *key)
{
    int i;

    for (i = 0; i < 10; i++) {
        // Use the P10 permutation table to rearrange the bits in the original key
        key_tmp[i] = key[P10[i]];
    }
    key_tmp[10] = '\0'; // Add the null terminator to the end of key_tmp
}


// Perform a circular left shift on the key_tmp
void circular_left_shift(char *key_tmp)
{
    // Store the first bit in a temporary variable
    char temp = key_tmp[0];
    int i;

    for (i = 0; i < 5; i++) {
        // Shift each bit in the first half of the key left by 1 position
        key_tmp[i] = key_tmp[i+1];
    }
    // Place the first bit at the end of the first half
    key_tmp[4] = temp;

    // Store the first bit of the second half in the temporary variable
    temp = key_tmp[5];

    for (i = 5; i < 10; i++) {
        // Shift each bit in the second half of the key left by 1 position
        key_tmp[i] = key_tmp[i+1];
    }
    // Place the first bit at the end of the second half
    key_tmp[9] = temp;
}


// Perform P8 permutation to extract subkey k1 or k2
void p8_key_permutation(char *key_tmp, int k)
{
    int i;
    // Check whether to generate k1 or k2
    if (k == 1) {
        // Generate subkey k1
        for (i = 0; i < 8; i++) {
            // Use the P8 permutation table to rearrange the bits in key_tmp
            k1[i] = key_tmp[P8[i]];
        }
        k1[8] = '\0'; // Add the null terminator to the end of k1
    }
    else if (k == 2) {
        // Generate subkey k2
        for (i = 0; i < 8; i++) {
            // Use the P8 permutation table to rearrange the bits in key_tmp
            k2[i] = key_tmp[P8[i]];
        }
        k2[8] = '\0'; // Add the null terminator to the end of k2
    }
    else {
        // Handle an invalid value of k
        return;
    }
}


//Generate k1 and K2
void keys_generation(char *key)
{
    // Step 1: Generate the first subkey (k1)
    // Perform P10 permutation on the original 10-bit key
    p10_key_permutation(key);

    // Step 2: Perform a circular left shift (shift left by 1 bit)
    circular_left_shift(key_tmp);

    // Step 3: Perform P8 permutation to extract the 8-bit subkey k1
    p8_key_permutation(key_tmp, 1);

    // Step 4: Generate the second subkey (k2)
    // Perform another circular left shift (shift left by 2 bits)
    circular_left_shift(key_tmp);
    circular_left_shift(key_tmp); // Repeated shift left by 2 bits

    // Step 5: Perform P8 permutation to extract the 8-bit subkey k2
    p8_key_permutation(key_tmp, 2);
}


// --------------Encrypt Function--------------
void encrypt(char *input, char *key)
{
    // Perform the inverse of the initial permutation
    initial_permutation(input);
    
    // Apply the function fk with k1 (subkey 1)
    fk(output, k1);
    
    // Switch the halves
    switch_halves(output);
    
    // Apply the function fk with k2 (subkey 2)
    fk(output, k2);
    
    // Perform the inverse of the initial permutation
    initial_permutation_inverse(output);

    // Print the generated subkeys
    printf("K1: %s\n", k1);
    printf("K2: %s\n", k2);
}

// ---------------Decrypt Function---------------
void decrypt(char *input, char *key) {
    // Initialize the subkeys
    keys_generation(key);

    // Perform the inverse of the initial permutation
    initial_permutation(input);

    // Apply the function fk with k2 (subkey 2)
    fk(output, k2);

    // Switch the halves
    switch_halves(output);

    // Apply the function fk with k1 (subkey 1)
    fk(output, k1);

    // Perform the inverse of the initial permutation
    initial_permutation_inverse(output);
    
    // Print the generated subkeys
    printf("K1: %s\n", k1);
    printf("K2: %s\n", k2);
    
}



int main(int argc, char const *argv[])
{
    char input[9];
    char key[11];
    int opt;

    do {
        //Menu
        printf("\nSelect an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("Enter your choice: ");
        scanf("%d", &opt);
    } while (opt < 1 || opt > 2);

    if (opt == 1) {
        // Encrypt
        printf("\nEnter Plaintext (8-bit): ");
        scanf("%s", input);
        printf("Enter Key (10-bit): ");
        scanf("%s", key);
        printf("--------------Generated subkeys and Ciphertext---------------\n");
        keys_generation(key);
        encrypt(input, key);
        printf("Ciphertext (8-bit): %s\n", output);
    } else {
        // Decrypt
        printf("\nEnter Ciphertext (8-bit): ");
        scanf("%s", input);
        printf("Enter Key (10-bit): ");
        scanf("%s", key);
        printf("--------------Generated subkeys and Plaintext---------------\n");
        keys_generation(key);
        decrypt(input, key);
        printf("Plaintext (8-bit): %s\n", output);
    }

    printf("\n");

    return 0;
}


