#include <iostream>
#include <vector>
#include <math.h>
#include <string>

int exponent_constant = 127;

std::string vector_to_string(std::vector<int> vector)//Вектор к строке
{
    std::string buffer_string = "";
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector.at(i) == -1)
        {
            buffer_string += ".";
            continue;
        }
        buffer_string += std::to_string(vector.at(i));
    }
    return buffer_string;
}

int find_one(std::string string)
{
    for (int i = 0; i < string.size(); i++)
    {
        if (string.at(i) == '1')
        {
            return i;
        }
    }
    return -1;
}

int find_one_before_dot(std::string string)//Находит единицу перед точкой в строке, возвращает позицию единицы; если нет возвращает -1
{
    for (int i = 0; i < string.size(); i++)
    {
        if (string.at(i) == '1')
        {
            return i;
        }
        if (string.at(i) == '.')
        {
            return -1;
        }
    }
}

int find_dot(std::string string)//находит позицию первоой точки в строке
{
    for (int i = 0; i < string.size(); i++)
    {
        if (string.at(i) == '.')
        {
            return i;
        }
    }
}
std::vector<int> string_to_vector(std::string string)//Строку к вектору
{
    std::vector<int> result;
    for (int i = 0; i < string.size(); i++)
    {
        if (string.at(i) == '.')
        {
            continue;
        }
        result.push_back((int)string.at(i) - 48);
    }
    return result;
}

int max_int(int number1, int number2)
{
    if (number1 > number2)
    {
        return number1;
    }
    else
    {
        return number2;
    }
}


std::vector<int> decimal_to_binary_direct_order(int decimal)//десятичное к бинарке прямого порядка
{
    std::vector<int> bits;
    int ticks_of_bits = 0;
    int number_of_bits;
    if (abs(decimal) < 100)
    {
        number_of_bits = 8;
    }
    else 
    {
        number_of_bits = 16;
    }
    if (decimal < 0) 
    {
        decimal = -decimal;
        bits.push_back(1);
    }
    else 
    {
        bits.push_back(0);
    }
    std::vector<int> buffer_bits;
    while (decimal >= 1) {
        int bit;

        bit = decimal % 2;
        buffer_bits.push_back(bit);
        ticks_of_bits += 1;
        decimal /= 2;
    }
    for (int i = buffer_bits.size() - 1; i >= 0; i--)
    {
        bits.push_back(buffer_bits.at(i));
    }
    if (ticks_of_bits < number_of_bits)
    {
        for (int i = 0; i < (number_of_bits - ticks_of_bits - 1); i++)
        {
            bits.insert(bits.begin() + 1, 0);
        }
    }
    return bits;
}

std::vector<int> decimal_to_binary_reverse_order(int decimal) //десятичку к бинарке обратного порядка
{
    if (decimal >= 0)
    {
        return decimal_to_binary_direct_order(decimal);
    }
    std::vector<int> inverted = decimal_to_binary_direct_order(decimal);
    for (int i = 1; i < inverted.size(); i++)
    {
        if (inverted.at(i) == 0)
        {
            inverted.at(i) = 1;
        }
        else
        {
            inverted.at(i) = 0;
        }
    }
    return inverted;
}

std::vector<int> add_binary_strings(std::vector<int> vector1, std::vector<int> vector2) 
{
    std::vector<int> result;
    int carry = 0, max_len, bufferLen;
    if (vector1.size() > vector2.size())
    {
        bufferLen = vector2.size();
        max_len = vector1.size();
        for (int i = 0; i < max_len - bufferLen; i++)
        {
            vector2.insert(vector2.begin(), 0);
        }
    }
    else
    {
        bufferLen = vector1.size();
        max_len = vector2.size();
        for (int i = 0; i < max_len - bufferLen; i++)
        {
            vector1.insert(vector1.begin(), 0);
        }
    }
    
    for (int i = max_len - 1; i >= 0; i--)
    {
        int bit_sum = vector1[i] + vector2[i] + carry;
        result.insert(result.begin(), bit_sum);
        carry = bit_sum / 2;
    }

    if (carry != 0) 
    {
        result.insert(result.begin(), carry);
    }
    return result;
}

std::vector<int> decimal_to_binary_additional_order(int decimal)//десятичку к дополненной бинарке
{
    std::vector<int> additional_binary, inverted = decimal_to_binary_reverse_order(decimal);
    if (decimal < 0)
    {
        std::vector<int> temp_vector;
        temp_vector.push_back(1);
        additional_binary = add_binary_strings(inverted, temp_vector);
        return additional_binary;
    }
    else
    {
        return decimal_to_binary_direct_order(decimal);
    }
}

std::vector<std::vector<int>> length_comparison(std::vector<int> vector1, std::vector<int> vector2) //выравнивает две бинарки к 1 длине и возвращает обоих
{
    std::vector<std::vector<int>> result;
    int max_len;
    if (vector1.size() > vector2.size())
    {
        max_len = vector1.size();
    }
    else
    {
        max_len = vector2.size();
    }
    if (vector1.at(0) == 0 and vector2.at(0) == 0)
    {
        for (int i = 0; i < max_len - vector2.size(); i++)
        {
            vector2.insert(vector2.begin(), 0);
        }
        for (int i = 0; i < max_len - vector1.size(); i++)
        {
            vector1.insert(vector1.begin(), 0);
        }
    }
    if (vector1[0] == 1)
    {
        for (int i = 1; i < max_len - vector1.size(); i++)
        {
            vector1.insert(vector1.begin(), 0);
        }
    }
    if (vector2[0] == 1)
    {
        for (int i = 1; i < max_len - vector2.size(); i++)
        {
            vector2.insert(vector2.begin(), 0);
        }
    }
    result.push_back(vector1);
    result.push_back(vector2);
    return result;
}

std::vector<int> sum_of_binary_numbers(std::vector<int> vector1, std::vector<int> vector2)//сумма бинарок
{
    std::vector<std::vector<int>> buffer_length_comparison_vector = length_comparison(vector1, vector2);
    vector1 = buffer_length_comparison_vector.at(0);
    vector2 = buffer_length_comparison_vector.at(1);
    std::vector<int> sum_of_numbers;
    int remainder = 0, counter = 0;
    for (int i = vector1.size() - 1; i >= 0; i--)
    {
        remainder = vector1.at(i) + vector2.at(i);
        if (remainder == 0 and counter == 0)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 0);
            counter = 0;
            continue;
        }
        if (remainder == 0 and counter == 1)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 1);
            counter = 0;
            continue;
        }
        if (remainder == 1 and counter == 0)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 1);
            counter = 0;
            continue;
        }
        if (remainder == 1 and counter == 1)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 0);
            counter = 1;
            continue;
        }
        if (remainder == 2 and counter == 0)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 0);
            counter = 1;
            continue;
        }
        if (remainder == 2 and counter == 1)
        {
            sum_of_numbers.insert(sum_of_numbers.begin(), 1);
            counter = 1;
            continue;
        }
    }
    if (counter > 0)
    {
        sum_of_numbers.insert(sum_of_numbers.begin(), 1);
    }
    return sum_of_numbers;
}

std::vector<int> from_additional_to_reverse(std::vector<int> binary_number)//от дополненной бинарки к обратной
{
    int index_of_first_1 = 0;
    for (int i = binary_number.size() - 1; i >= 0; i--)
    {
        if (binary_number.at(i) == 1)
        {
            index_of_first_1 = i;
            binary_number[i] = 0;
            break;
        }
    }
    for (int i = index_of_first_1 + 1; i < binary_number.size(); i++)
    {
        binary_number.at(i) = 1;
    }
    return binary_number;
}

std::vector<int>  from_reverse_to_direct(std::vector<int> binary_number)//от обратной к прямой
{
    for (int i = 1; i < binary_number.size(); i++)
    {
        if (binary_number.at(i) == 1)
        {
            binary_number.at(i) = 0;
        }
        else
        {
            binary_number.at(i) = 1;
        }
    }
    return binary_number;
}

std::vector<int> binary_multiplication(std::vector<int>vector1, std::vector<int> vector2)//умножение бинарок
{
    vector1.erase(vector1.begin());
    vector2.erase(vector2.begin());
    int result_length = vector1.size() + vector2.size();
    std::vector<int> result;
    for (int i = 0; i < result_length; i++)
    {
        result.push_back(0);
    }
    for (int i = vector1.size() - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = vector2.size() - 1; j >= 0; j--)
        {
            int digit, bufferElement = vector1.at(i) * vector2.at(j) + carry;
            carry = (result.at(i + j + 1) + (bufferElement)) / 2;
            digit = (result.at(i + j + 1) + (bufferElement)) % 2;
            result.at(i + j + 1) = digit;
        }
        result.at(i) += carry;
    }
    result.insert(result.begin(), vector1.at(0) ^ vector2.at(0));
    while (result.size() > 1 and result.at(0) == 0)
    {
        result.erase(result.begin());
    }
    while (result.size() < result_length+1)
    {
        result.insert(result.begin(), 0);
    }
    return result;
}

std::vector<int> binary_division(std::vector<int> dividend, std::vector<int> divisor)//деление бинарок
{
    std::vector<int> quotient;
    bool flag = true;
    if (dividend.at(0) == 1 or divisor.at(0) == 1)
    {
        flag = false;
    }
    int dividend_int = 0, divisor_int = 0, convert_counter = 0;
    for (int i = dividend.size() - 1; i >= 0 ; i--)
    {
        dividend_int += dividend.at(i) * pow(10, convert_counter);
        convert_counter++;
    }
    convert_counter = 0;
    for (int i = divisor.size() - 1; i >= 0; i--)
    {
        divisor_int += divisor.at(i) * pow(10, convert_counter);
        convert_counter++;
    }
    if (divisor_int == 0)
    {
        return quotient;
    }
    int quotient_int = dividend_int / divisor_int;
    while (quotient_int != 0)
    {
        quotient.insert(quotient.begin(), quotient_int % 10);
        quotient_int /= 10;
    }
    while (quotient.size() < dividend.size() - divisor.size() +1)
    {
        quotient.insert(quotient.begin(), 0);
    }
    if (!flag)
    {
        for(int i = 0; i < quotient.size(); i++)
        {
            if (quotient.at(i) == 0)
            {
                quotient.at(i) = 1;
            }
            else
            {
                quotient.at(i) = 0;
            }
        }
    }
    quotient.insert(quotient.begin(), 0);
    return quotient;
}

std::vector<int> vector_revers(std::vector<int> data)
{
    std::vector<int> result;
    for (int i = data.size() - 1; i >= 0; i--)
    {
        result.push_back(data.at(i));
    }
    return result;
}

std::vector<int> from_decimal_to_float(std::string decimal)
{
    std::vector<int> result, exp_bits, mantissa, buffer;
    int exp_sign = -1;
    std::string bufferStr;
    int flag = find_one_before_dot(decimal);
    if(flag != -1)
    {
        exp_sign = 1;
    }
    std::vector<int> sign_bit;
    sign_bit.push_back(0);
    std::vector<int> buffer_vector_for_operation;
    
    if (flag == -1)
    {
        
        buffer = decimal_to_binary_direct_order(exponent_constant + ((flag - find_dot(decimal) - 1) * exp_sign));
        for (int i = buffer.size() - 1; i > buffer.size() - 9; i--)
        {
            exp_bits.push_back(buffer.at(i));
        }
        exp_bits = vector_revers(exp_bits);
    }
    else
    {
        buffer = decimal_to_binary_direct_order(exponent_constant + ((find_dot(decimal) - flag - 1) * exp_sign));
        for (int i = buffer.size() - 1; i > buffer.size() - 9; i--)
        {
            exp_bits.push_back(buffer.at(i));
        }
        exp_bits = vector_revers(exp_bits);
    }
    for (int i = 0; i < find_dot(decimal); i++)
    {
        bufferStr += decimal.at(i);
    }
    for (int i = find_dot(decimal) + 1; i < decimal.size(); i++)
    {
        bufferStr += decimal.at(i);
    }
    decimal = bufferStr;
    for (int i = find_one(decimal) + 1; i < decimal.size(); i++)
    {
        mantissa.push_back(decimal.at(i) - 48);
    }
    result = sign_bit;
    for (int i = 0; i < exp_bits.size(); i++)
    {
        result.push_back(exp_bits.at(i));
    }
    for (int i = 0; i < mantissa.size(); i++)
    {
        result.push_back(mantissa.at(i));
    }


    return result;
}

std::vector<int> to_fix(double decimal)
{
    std::vector<int> result;
    if (decimal == 0)
    {
        
        for (int i = 0; i < 24; i++)
        {
            result.push_back(0);
        }
        return result;
    }
    int number1 = (int)decimal, i = 0, mantissa_size = 23, index_of_one = 0 ,bufferInt;
    double fraction_part = decimal - (double)number1;
    std::vector<int> number2 = decimal_to_binary_additional_order(number1);
    for (int i = 0; i < number2.size(); i++)
    {
        if (number2.at(i) == 1)
        {
            index_of_one = i;
            break;
        }
    }
    if (index_of_one == 0)
    {
        result = { 0 };
    }
    else
    {
        for (int i = index_of_one; i < number2.size(); i++)
        {
            result.push_back(number2.at(i));
        }
    }
    result.push_back(-1);
    bufferInt = mantissa_size - result.size();
    while (i <= (bufferInt))
    {
        bufferInt = mantissa_size - result.size();
        fraction_part *= 2;
        if ((int)fraction_part == 0) 
        {
            result.push_back(0);
        }
        else
        {
            if ((int)fraction_part == 1)
            {
                fraction_part -= 1;
                result.push_back(1);
                if (fraction_part == 0)
                    for (int i = 0; i < (23 - result.size() + 1); i++)
                    {
                        result.push_back(0);
                    }
            }
        }
    }
    return result;
}

double from_float_to_decimal(std::vector<int> number)
{
    int sing = -1, exp = 0;
    double result = 0, frac = 0;
    if(number.at(0) == 0)
    {
        sing = 1;
    }
    for(int i = 1; i < 8; i++)
    {
        exp += number.at(i) * (pow(2, (8 - i)));
    }
    exp -= 127;
    for(int i = 9; i < 32; i++)
    {
        frac += number.at(i) * (pow(2, -(i - 8)));
    }
    result = sing * (1 + frac) * pow(2, exp);
    return result;
}


std::string delDot(std::string data)
{
    std::string result;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == '.') continue;
        result += data[i];
    }
    return result;
}

std::vector<int> summ_of_floating(double decimal1, double decimal2)
{
    std::vector<int> decimal1_buffer = to_fix(decimal1), decimal2_buffer = to_fix(decimal2), result;
    std::string decimal1_str = vector_to_string(decimal1_buffer), decimal2_str = vector_to_string(decimal2_buffer), numsumm1 = "", numsumm2 = "", temp_floating_summ, bufferResult = "";
    int unitnum1 = find_one_before_dot(decimal1_str), unitnum2 = find_one_before_dot(decimal2_str), exp1, exp2, diff_exp, add_numbers;


    if (find_one_before_dot(decimal1_str) == -1)
    {
        exp1 = 0;
    }
    else
    {
        exp1 = find_dot(decimal1_str) - unitnum1 - 1;
    }
    if (find_one_before_dot(decimal2_str) == -1)
    {
        exp2 = 0;
    }
    else
    {
        exp2 = find_dot(decimal2_str) - unitnum1 - 1;
    }
    if (exp1 >= exp2)
    {
        diff_exp = exp1 - exp2;
        for (int i = 0; i < diff_exp; i++)
        {
            numsumm2 += "0";
        }
        for (int i = 0; i < decimal2_str.size() - diff_exp; i++)
        {
            numsumm2 += decimal2_str.at(i);
        }
        numsumm1 = decimal1_str;
        numsumm1 = delDot(numsumm1);
        numsumm2 = delDot(decimal2_str);
    }
    else
    {
        diff_exp = exp2 - exp1;
        for (int i = 0; i < diff_exp; i++)
        {
            numsumm1 += "0";
        }
        for (int i = 0; i < decimal1_str.size() - diff_exp; i++)
        {
            numsumm1 += decimal1_str.at(i);
        }
        numsumm1 = delDot(numsumm1);
        numsumm2 = delDot(decimal2_str);
    }

    temp_floating_summ = vector_to_string(sum_of_binary_numbers(string_to_vector(numsumm1), string_to_vector(numsumm2)));
    add_numbers = temp_floating_summ.size() - numsumm2.size();
    for (int i = 0; i < (max_int(find_dot(decimal1_str), find_dot(decimal2_str)) + add_numbers); i++)
    {
        bufferResult += temp_floating_summ.at(i);
    }
    bufferResult += '.';
    for (int i = (max_int(exp1, exp2) + 1 + add_numbers); i < temp_floating_summ.size(); i++)
    {
        bufferResult += temp_floating_summ.at(i);
    }

    result = from_decimal_to_float(bufferResult);
    //for (int i = 0; i < (max_int(find_dot(decimal1_str), find_dot(decimal2_str)) + add_numbers); i++)
    //{
    //    result.push_back(temp_floating_summ.at(i) - 48);
    //}
    //result.push_back(-1);
    //for (int i = (max_int(exp1, exp2) + 1 + add_numbers); i < temp_floating_summ.size(); i++)
    //{
    //    result.push_back(temp_floating_summ.at(i) - 48);
    //}

    return result;
}

int from_binary_to_decimal(std::vector<int> binary_number)
{
    int result = 0;
    if (binary_number.at(0) == 1)
    {
        result += (-binary_number.at(1)) * pow(2, binary_number.size() - 2);
        for (int i = 2; i < binary_number.size(); i++)
        {
            result += binary_number.at(i) * pow(2, binary_number.size() - (i + 1));
        }
    }
    else
    {
        for (int i = 0; i < binary_number.size(); i++)
        {
            result += binary_number.at(i) * pow(2, binary_number.size() - (i + 1));
        }
    }
    return result;
}

void viewVector(std::vector<int> data)
{
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data.at(i) << " ";
    }
    std::cout << std::endl;
}

int main()
{
    while (true)
    {
        std::vector<int> binary1, binary2;
        std::vector<std::vector<int>> bufferVector;
        std::cout << "Input first number: ";
        double decimal1, decimal2, bufferDecimal;
        int key1, key2;
        std::cin >> decimal1;
        std::cout << "Input second number: ";
        std::cin >> decimal2;
        std::cout << "Select type of codes:\n1 - direct and reverce\n2 - direct and additional\n3 - additional and reverce\n4 - for float: ";
        std::cin >> key1;
        std::cout << "Select operation:\n1 - summ\n2 - difference\n3 - multiplication\n4 - division\n5 - summ of float: ";
        std::cin >> key2;
        if (key2 == 2)
        {
            decimal2 = -decimal2;
        }
        if(key2 == 3)
        {
            decimal1 = abs(decimal1);
            decimal2 = abs(decimal2);
        }
        if (key2 == 4)
        {
            decimal1 = abs(decimal1);
            decimal2 = abs(decimal2);
            if(decimal1 == 0 or decimal2 == 0)
            {
                decimal1 = 0;
                decimal2 = 0;
            }
            if (decimal1 < decimal2)
            {
                bufferDecimal = decimal1;
                decimal1 = decimal2;
                decimal2 = bufferDecimal;
            }
        }
        switch(key1)
        {
        case 1:
            if(decimal1 < 0 and 0 < decimal2)
            { 
                bufferDecimal = decimal1;
                decimal1 = decimal2;
                decimal2 = bufferDecimal;
            }
            binary1 = decimal_to_binary_direct_order(decimal1);
            binary2 = decimal_to_binary_reverse_order(decimal2);
            std::cout << "First number: ";
            viewVector(binary1);
            std::cout << "Second number: ";
            viewVector(binary2);
            break;
        case 2:
            if (decimal1 < 0 < decimal2)
            {
                bufferDecimal = decimal1;
                decimal1 = decimal2;
                decimal2 = bufferDecimal;
            }
            binary1 = decimal_to_binary_direct_order(decimal1);
            binary2 = decimal_to_binary_additional_order(decimal2);
            std::cout << "First number: ";
            viewVector(binary1);
            std::cout << "Second number: ";
            viewVector(binary2);
            break;
        case 3:
            binary1 = decimal_to_binary_additional_order(decimal1);
            binary2 = decimal_to_binary_additional_order(decimal2);
            std::cout << "First number: ";
            viewVector(binary1);
            std::cout << "Second number: ";
            viewVector(binary2);
            break;
        }
        switch (key2)
        {
        case 1:
        case 2:
            std::cout << "Summ/diff in binary: ";
            viewVector(sum_of_binary_numbers(binary1, binary2));
            std::cout << "in decimal: " << from_binary_to_decimal(sum_of_binary_numbers(binary1, binary2)) << std::endl;
            break;
        case 3:
            bufferVector = length_comparison(binary1, binary2);
            binary1 = bufferVector.at(0);
            binary2 = bufferVector.at(1);
            viewVector(binary_multiplication(binary1, binary2));
            std::cout << "in decimal: " << from_binary_to_decimal(binary_multiplication(binary1, binary2)) << std::endl;
            break;
        case 4:
            bufferVector = length_comparison(binary1, binary2);
            binary1 = bufferVector.at(0);
            binary2 = bufferVector.at(1);
            viewVector(binary_division(binary1, binary2));
            std::cout << "in decimal: " << from_binary_to_decimal(binary_division(binary1, binary2)) << std::endl;
            break;
        case 5:
            std::cout << from_float_to_decimal(summ_of_floating(decimal1, decimal2)) << "\n";
            break;
        }
    }
}
