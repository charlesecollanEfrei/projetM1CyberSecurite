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
    
    cout << "Base message : " << endl;
    displayBitTable(message_03,64);
    displayAsHex(message_03,64);
    
    cout << endl << "First permutation : " << endl;
    firstperm = permute(message_03,init_perm,64);
    displayBitTable(firstperm,64);
    displayAsHex(firstperm,64);
    
    
    
    cout << endl << "Left table : " << endl;
    L_table = extractL(firstperm);
    displayBitTable(L_table,32);
    displayAsHex(L_table,32);
    
    cout << endl << "Right table : " << endl;
    R_table = extractR(firstperm);
    displayBitTable(R_table,32);
    displayAsHex(R_table,32);
    
    for (int i = 0; i < 16; i++) {
    
        cout << endl << "Expang Right : " << endl;
        R_expand = expandR(R_table, expansion_table);
        displayBitTable(R_expand,48);
        displayAsHex(R_expand,48);
        
        cout << endl << "Random key : " << endl;
        random_key = generateRandomKey(64);
        displayBitTable(random_key,64);
        displayAsHex(random_key,64);
        
        cout << endl << "Computed key : " << endl;
        computed_key = computeKey(random_key, pc_1_left, pc_1_right, pc_2, keyshift[i]);
        displayBitTable(computed_key,48);
        displayAsHex(computed_key,48);
        
        cout << endl << "After xor : " << endl;
        after_xor = xorFunction(R_expand, computed_key, 48);
        displayBitTable(after_xor,48);
        displayAsHex(after_xor,48);
        
        cout << endl << "Substitude box : " << endl;
        after_subsitude = substitutionBox(after_xor, s_boxes, permut_32);
        displayBitTable(after_subsitude,32);
        displayAsHex(after_subsitude,32);
        
        
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
    
    
    cout << endl << "Encrypted message : " << endl;
    encrypted_message = reversePerm(L_table, R_table, reverse_perm);
    displayBitTable(encrypted_message,64);
    displayAsHex(encrypted_message,64);
    cout << endl << endl;
}
