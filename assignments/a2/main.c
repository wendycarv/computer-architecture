#include <stdio.h>
#include <math.h>
#include <stdbool.h>


typedef union{
        float   floating_value_in_32_bits;
        int     floating_value_as_int;
        struct  sign_exp_mantissa{
                unsigned  mantissa:23;
                unsigned  exponent:8;
                unsigned      sign:1;
        } f_bits;
    struct single_bits{
        unsigned  b0 :1;
        unsigned  b1 :1;
        unsigned  b2 :1;
        unsigned  b3 :1;
        unsigned  b4 :1;
        unsigned  b5 :1;
        unsigned  b6 :1;
        unsigned  b7 :1;
        unsigned  b8 :1;
        unsigned  b9 :1;
        unsigned  b10:1;
        unsigned  b11:1;
        unsigned  b12:1;
        unsigned  b13:1;
        unsigned  b14:1;
        unsigned  b15:1;
        unsigned  b16:1;
        unsigned  b17:1;
        unsigned  b18:1;
        unsigned  b19:1;
        unsigned  b20:1;
        unsigned  b21:1;
        unsigned  b22:1;
        unsigned  b23:1;
        unsigned  b24:1;
        unsigned  b25:1;
        unsigned  b26:1;
        unsigned  b27:1;
        unsigned  b28:1;
        unsigned  b29:1;
        unsigned  b30:1;
        unsigned  b31:1;
    }bit;
} float_un;

int main(int argc, char * argv[]) {
    
    int i,j,k;
    float_un float1, float2, float3;
    int mant1, mant2, mant_result, exp1, exp2;
    bool denorm1 = true, denorm2 = true;
    
    char bit_string[43];
    char bit_string_2[43];
    char bit_string_result[43];

    for(i = 0; i < 42; i++) {
        bit_string[i] = ' ';
        bit_string_2[i] = ' ';
        bit_string_result[i] = ' ';
    }
    bit_string[42] = '\0';
    bit_string_2[42] = '\0';
    bit_string_result[42] = '\0';
    
    printf("Please enter two positive floating point values each with:\n");
    printf("    - no more than 6 significant digits\n");
    printf("    - a value between +10^37 and 10^-37\n\n");
    
    printf("Enter Float 1: ");
    scanf("%g", &float1.floating_value_in_32_bits);

    printf("Enter Float 2: ");
    scanf("%g", &float2.floating_value_in_32_bits);

    // extract mantissa and exponent of each float
    mant1 = float1.f_bits.mantissa; // & Ox7FFFFF
    mant2 = float2.f_bits.mantissa;
    exp1 = float1.f_bits.exponent;
    exp2 = float2.f_bits.exponent;
    
    // check denormalization and expose hidden bit in mantissa
    if (exp1) {
        mant1 |= (1<<23);
        denorm1 = false;
    }
    if (exp2) {
        mant2 |= (1<<23);
        denorm2 = false;
    }
    
    // determine smaller exponent and align mantissas
    int shift = float1.f_bits.exponent - float2.f_bits.exponent;
    if (shift < 0) {
        shift = -(shift);
        if (shift > 24) {
            shift = 24;
        }
        if (shift >= 1 && denorm1) {
            mant1 = (mant1 >> (shift - 1));
        } else {
            mant1 >>= shift;
        }
        float3.f_bits.exponent = exp2;
    } else {
        if (shift > 24) {
            shift = 24;
        }
        if (shift >= 1 && denorm2) {
            mant2 = (mant2 >> (shift - 1));
        } else {
            mant2 >>= shift;
        }
        float3.f_bits.exponent = exp1;
    }
    
    // perform addition on aligned mantissas
    mant_result = mant1 + mant2;

    // check for overflow
    if (mant_result & (1 << 24)){
      mant_result >>= 1; // shift overflow to the right
      float3.f_bits.exponent++;
      float3.f_bits.mantissa = (mant_result & ~(1 << 23));
    } else {
      float3.f_bits.mantissa = (mant_result & ~(1 << 23));
    }
    
    bit_string[0] = float1.bit.b31?'1':'0';

    bit_string[2] = float1.bit.b30?'1':'0';
    bit_string[3] = float1.bit.b29?'1':'0';
    bit_string[4] = float1.bit.b28?'1':'0';
    bit_string[5] = float1.bit.b27?'1':'0';

    bit_string[7] = float1.bit.b26?'1':'0';
    bit_string[8] = float1.bit.b25?'1':'0';
    bit_string[9] = float1.bit.b24?'1':'0';
    bit_string[10] = float1.bit.b23?'1':'0';

    bit_string[12] = float1.bit.b22?'1':'0';
    bit_string[13] = float1.bit.b21?'1':'0';
    bit_string[14] = float1.bit.b20?'1':'0';

    bit_string[16] = float1.bit.b19?'1':'0';
    bit_string[17] = float1.bit.b18?'1':'0';
    bit_string[18] = float1.bit.b17?'1':'0';
    bit_string[19] = float1.bit.b16?'1':'0';

    bit_string[21] = float1.bit.b15?'1':'0';
    bit_string[22] = float1.bit.b14?'1':'0';
    bit_string[23] = float1.bit.b13?'1':'0';
    bit_string[24] = float1.bit.b12?'1':'0';

    bit_string[26] = float1.bit.b11?'1':'0';
    bit_string[27] = float1.bit.b10?'1':'0';
    bit_string[28] = float1.bit.b9?'1':'0';
    bit_string[29] = float1.bit.b8?'1':'0';

    bit_string[31] = float1.bit.b7?'1':'0';
    bit_string[32] = float1.bit.b6?'1':'0';
    bit_string[33] = float1.bit.b5?'1':'0';
    bit_string[34] = float1.bit.b4?'1':'0';

    bit_string[36] = float1.bit.b3?'1':'0';
    bit_string[37] = float1.bit.b2?'1':'0';
    bit_string[38] = float1.bit.b1?'1':'0';
    bit_string[39] = float1.bit.b0?'1':'0';

    /**********/
    
    bit_string_2[0] = float2.bit.b31?'1':'0';

    bit_string_2[2] = float2.bit.b30?'1':'0';
    bit_string_2[3] = float2.bit.b29?'1':'0';
    bit_string_2[4] = float2.bit.b28?'1':'0';
    bit_string_2[5] = float2.bit.b27?'1':'0';

    bit_string_2[7] = float2.bit.b26?'1':'0';
    bit_string_2[8] = float2.bit.b25?'1':'0';
    bit_string_2[9] = float2.bit.b24?'1':'0';
    bit_string_2[10] = float2.bit.b23?'1':'0';

    bit_string_2[12] = float2.bit.b22?'1':'0';
    bit_string_2[13] = float2.bit.b21?'1':'0';
    bit_string_2[14] = float2.bit.b20?'1':'0';

    bit_string_2[16] = float2.bit.b19?'1':'0';
    bit_string_2[17] = float2.bit.b18?'1':'0';
    bit_string_2[18] = float2.bit.b17?'1':'0';
    bit_string_2[19] = float2.bit.b16?'1':'0';

    bit_string_2[21] = float2.bit.b15?'1':'0';
    bit_string_2[22] = float2.bit.b14?'1':'0';
    bit_string_2[23] = float2.bit.b13?'1':'0';
    bit_string_2[24] = float2.bit.b12?'1':'0';

    bit_string_2[26] = float2.bit.b11?'1':'0';
    bit_string_2[27] = float2.bit.b10?'1':'0';
    bit_string_2[28] = float2.bit.b9?'1':'0';
    bit_string_2[29] = float2.bit.b8?'1':'0';

    bit_string_2[31] = float2.bit.b7?'1':'0';
    bit_string_2[32] = float2.bit.b6?'1':'0';
    bit_string_2[33] = float2.bit.b5?'1':'0';
    bit_string_2[34] = float2.bit.b4?'1':'0';

    bit_string_2[36] = float2.bit.b3?'1':'0';
    bit_string_2[37] = float2.bit.b2?'1':'0';
    bit_string_2[38] = float2.bit.b1?'1':'0';
    bit_string_2[39] = float2.bit.b0?'1':'0';
    
    bit_string_result[0] = float3.bit.b31?'1':'0';

    bit_string_result[2] = float3.bit.b30?'1':'0';
    bit_string_result[3] = float3.bit.b29?'1':'0';
    bit_string_result[4] = float3.bit.b28?'1':'0';
    bit_string_result[5] = float3.bit.b27?'1':'0';

    bit_string_result[7] = float3.bit.b26?'1':'0';
    bit_string_result[8] = float3.bit.b25?'1':'0';
    bit_string_result[9] = float3.bit.b24?'1':'0';
    bit_string_result[10] = float3.bit.b23?'1':'0';

    bit_string_result[12] = float3.bit.b22?'1':'0';
    bit_string_result[13] = float3.bit.b21?'1':'0';
    bit_string_result[14] = float3.bit.b20?'1':'0';

    bit_string_result[16] = float3.bit.b19?'1':'0';
    bit_string_result[17] = float3.bit.b18?'1':'0';
    bit_string_result[18] = float3.bit.b17?'1':'0';
    bit_string_result[19] = float3.bit.b16?'1':'0';

    bit_string_result[21] = float3.bit.b15?'1':'0';
    bit_string_result[22] = float3.bit.b14?'1':'0';
    bit_string_result[23] = float3.bit.b13?'1':'0';
    bit_string_result[24] = float3.bit.b12?'1':'0';

    bit_string_result[26] = float3.bit.b11?'1':'0';
    bit_string_result[27] = float3.bit.b10?'1':'0';
    bit_string_result[28] = float3.bit.b9?'1':'0';
    bit_string_result[29] = float3.bit.b8?'1':'0';

    bit_string_result[31] = float3.bit.b7?'1':'0';
    bit_string_result[32] = float3.bit.b6?'1':'0';
    bit_string_result[33] = float3.bit.b5?'1':'0';
    bit_string_result[34] = float3.bit.b4?'1':'0';

    bit_string_result[36] = float3.bit.b3?'1':'0';
    bit_string_result[37] = float3.bit.b2?'1':'0';
    bit_string_result[38] = float3.bit.b1?'1':'0';
    bit_string_result[39] = float3.bit.b0?'1':'0';

    printf("\n");
    printf("Original pattern of Float 1: %s\n", bit_string);
    printf("Original pattern of Float 2: %s\n", bit_string_2);
    printf("Bit pattern of result:\t\t %s\n", bit_string_result);
        
    // print emulated and hardware floating results
    printf("\nEMULATED FLOATING RESULT FROM PRINTF ==>>> %.2f\n", float3.floating_value_in_32_bits);
    printf("HARDWARE FLOATING RESULT FROM PRINTF ==>>> %.2f\n", float1.floating_value_in_32_bits + float2.floating_value_in_32_bits);
    
    return 0;
}

