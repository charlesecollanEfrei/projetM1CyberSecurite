// Implementing a symmetric cryptographic protocol : DES
// Project by Bastien Robert and Charles Ecollan
// BI - PROMO 2019

#include <iostream>
#include "permutations.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "data_messages_examples.h"

using namespace std;

int main()
{
    char *firstperm;
    char *L_table;
    char *R_table;
    char *R_expand;
    char *random_key;
    char *computed_key;
    char *after_xor;
    char *after_subsitude;
    char *encrypted_message;
    
    // Menu and message
    int choice;
    int choice_message;
    int choice_key;
    char *message;
    
    cout << "Implementing a symmetric cryptographic protocol : DES" << endl;
    cout << "Project by Bastien Robert and Charles Ecollan" << endl;
    
    do{
        do{
            // Choice of the message
            cout << endl << "Which message do you want?" << endl;
            cout << "1 - Message 1" << endl;
            cout << "2 - Message 2" << endl;
            cout << "3 - Message 3" << endl;
            cin >> choice_message;
        }while(choice_message != 1 && choice_message != 2 && choice_message != 3);
        
        switch (choice_message) {
            case 1:
                message = message_01;
                break;
            case 2:
                message = message_02;
                break;
            case 3:
                message = message_03;
                break;
                
            default: message = message_03;
                break;
        }
        
        // Display message in hexadecimal and bits
        cout << endl << "Base message : " << endl;
        displayBitTable(message,64);
        displayAsHex(message,64);
        
        // Choice of the key
        do{
            cout << endl << endl << " Which key do you want? " << endl;
            cout << "1 - 01CD 08CD DB99 DCCD " << endl ;
            cout << "2 - Random key " << endl ;
            cin >> choice_key;
        }while(choice_key != 1 && choice_key != 2);
        
        switch (choice_key) {
            case 1:{
                char not_random_key[64]=
                {
                    0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,1
                };
                random_key = not_random_key;
                break;
            }
                
            case 2:
                // We generate a key randomly
                random_key = generateRandomKey(64);
                break;
                
            default: random_key = generateRandomKey(64);
                break;
        }
        
        
        // Display the random 
        cout << endl << "Random key : " << endl;
        displayBitTable(random_key,64);
        displayAsHex(random_key,64);
        
        // Initial permutation
        cout << endl << "First permutation : " << endl;
        firstperm = permute(message,init_perm,64);
        displayBitTable(firstperm,64);
        displayAsHex(firstperm,64);
        
        // Message splitte in two 32-bit blocks
        // L0
        cout << endl << "Left table : " << endl;
        L_table = extractL(firstperm);
        displayBitTable(L_table,32);
        displayAsHex(L_table,32);
        
        // R0
        cout << endl << "Right table : " << endl;
        R_table = extractR(firstperm);
        displayBitTable(R_table,32);
        displayAsHex(R_table,32);
        
        for (int i = 0; i < 16; i++) {
            cout << "--------------------" << endl;
            cout << endl << "Round " << i + 1 << endl;
            
            // Expand Ri with the expansion_table
            cout << endl << "Expand Right : " << endl;
            R_expand = expandR(R_table, expansion_table);
            displayBitTable(R_expand,48);
            displayAsHex(R_expand,48);
            
            // Generate 48 bits subkeys key i
            cout << endl << "Computed key : " << endl;
            computed_key = computeKey(random_key, pc_1_left, pc_1_right, pc_2, keyshift[i]);
            displayBitTable(computed_key,48);
            displayAsHex(computed_key,48);
            
            // Operate a XOR between expanded version of Ri and key i
            cout << endl << "After xor : " << endl;
            after_xor = xorFunction(R_expand, computed_key, 48);
            displayBitTable(after_xor,48);
            displayAsHex(after_xor,48);
            
            // Input the 48 bit computed value to the S-Box
            // Permute the previous result
            cout << endl << "Substitude box : " << endl;
            after_subsitude = substitutionBox(after_xor, s_boxes, permut_32);
            displayBitTable(after_subsitude,32);
            displayAsHex(after_subsitude,32);
            
            // XOR operation between the previous result and Li
            cout << endl << "Ri+1 (after second xor) : " << endl;
            after_xor = xorFunction(after_subsitude, L_table, 32);
            L_table = R_table;
            R_table = after_xor;
            displayBitTable(R_table,32);
            displayAsHex(R_table,32);
            
            cout << endl << "Li+1 : " << endl;
            displayBitTable(L_table,32);
            displayAsHex(L_table,32);
            
        }
        
        // Encrypted message with reverse_perm function
        cout << endl << "Encrypted message : " << endl;
        encrypted_message = reversePerm( R_table, L_table, reverse_perm);
        displayBitTable(encrypted_message,64);
        displayAsHex(encrypted_message,64);
        cout << endl << endl;
        
        // Restart or not
        do{
            cout << "Restart? (0: Yes & 1: No)" << endl;
            cin >> choice;
        }while(choice != 0 && choice != 1);
        
    }while(choice == 0);
    
    // Message
    cout << endl << "Thanks you to use our program" << endl;
    cout << endl << "Implementing a symmetric cryptographic protocol : DES" << endl;
    cout << "Project by Bastien Robert and Charles Ecollan" << endl;
    
}
