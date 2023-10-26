S-DES Encryption and Decryption

Description
S-DES (Simplified Data Encryption Standard) is a symmetric-key block cipher that encrypts and decrypts 8-bit data blocks using a 10-bit key. This C program demonstrates the S-DES encryption and decryption processes, including key generation and subkey creation.

Usage
1. Compile the program using a C compiler such as `gcc`:

   gcc s-des.c -o s-des

2. Run the program:

   ./s-des

3. Follow the on-screen prompts to select either encryptionor decryption and provide the necessary input.

Options
Encrypt: This option allows you to encrypt an 8-bit plaintext using a 10-bit key. It will display the generated subkeys and the resulting ciphertext.
Decrypt: This option allows you to decrypt an 8-bit ciphertext using the same 10-bit key used for encryption. It will display the generated subkeys and the resulting plaintext.

Input
For encryption, you need to provide an 8-bit plaintext and a 10-bit key.
For decryption, you need to provide an 8-bit ciphertext and the same 10-bit key used for encryption.

Output
The program will display the generated subkeys for encryption and decryption.
For encryption, it will display the 8-bit ciphertext.
For decryption, it will display the 8-bit plaintext.

Subkey Generation
The program generates two 8-bit subkeys, `k1` and `k2`, from the 10-bit key provided.

Important Notes
Ensure that the input plaintext/ciphertext and key have the correct number of bits.
The program performs initial permutation, expansion, substitution using S-boxes, and permutation operations as specified in the S-DES algorithm.
Subkey generation is based on the provided 10-bit key.

Authors
Shreya Wagley

License
This program is provided under an open-source license. You are free to use and modify it as needed.
