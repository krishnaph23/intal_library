#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

static void stripping_zeroes(char* result)  //Used in intal_add and intal_diff
{
    int len = strlen(result);
    while(result[strlen(result) - len] == '0')
    {
        for(int i = 0; i < len; i++)
            result[i] = result[i+1];
        len--;
    }
    if(strlen(result) == 0)
    {
        result[0] = '0';
        result[1] = '\0';
    }
}

static char* adding_zeroes(char* a, int n)  //Used in mod to add succeeding zeroes
{
    if(n < 1)
    {
        char* temp = (char*)malloc(sizeof(char)*(strlen(a)+1));
        strcpy(temp, a);
        return temp;
    }
    int i;
    char* temp = (char*)malloc(sizeof(char)*(strlen(a)+1+n));
    for(i = 0; i < strlen(a); i++)
        temp[i] = a[i];
    for(int j = 0; j < n; j++)
        temp[i++] = '0';
    temp[i] = '\0';
    return temp; 
}

static void intal_heapify(char** arr, int n, int i)     //Used in heap sort
{ 
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
  
    if (l < n && (intal_compare(arr[l], arr[largest]) == 1))
        largest = l; 

    if (r < n && (intal_compare(arr[r], arr[largest]) == 1)) 
        largest = r; 

    if (largest != i) 
    {
        char* temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        intal_heapify(arr, n, largest); 
    } 
} 
/* Non-static function */
char* intal_add(const char* intal1, const char* intal2)
{
    int carry = 0;
    int m = strlen(intal1);
    int n = strlen(intal2);
    int i = m > n ? m : n;
    int count = i+1;

    char* result = (char*)malloc(sizeof(char)*(i+2));
    result[i+1] = '\0';
    
    m--; n--;

    while(m > -1 || n > -1)
    {
        int temp;
        if(m > -1 && n < 0)
            temp = (int)intal1[m] + carry - 48;

        else if(n > -1 && m < 0)
            temp = (int)intal2[n] + carry - 48;

        else
            temp = (int)intal1[m] + (int)intal2[n] + carry - 96;

        result[i] = temp % 10;
        carry = temp / 10;
        m--; n--; i--;
    }
    result[i] = carry;

    for(i = 0; i < count; i++)
        result[i] = result[i] + 48;

    stripping_zeroes(result);
    return result;
}

int intal_compare(const char* intal1, const char* intal2)
{
    int m = strlen(intal1);
    int n = strlen(intal2);
    if(m > n)
        return 1;
    else if(m < n)
        return -1;
    else
    {
        while(m > -1)
        {
            if((int)intal1[n-m] == (int)intal2[n-m])
                m--;
            else if((int)intal1[n-m] > (int)intal2[n-m])
                return 1;
            else
                return -1;
        }
        return 0;
    }
}

char* intal_diff(const char* intal1, const char* intal2)
{
    int comparison_flag = intal_compare(intal1, intal2);    //To find the absolute value of difference
    if(comparison_flag == 0)        //If both the values are same
    {
        char* result = (char*)malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int carry = 0;
    int m = strlen(intal1);
    int n = strlen(intal2);
    int i = m > n ? m : n;
    char* result = (char*)malloc(sizeof(char)*(i+1));

    int count = i;
    result[i] = '\0';

    m--; n--; i--;

    while(m > -1 || n > -1)
    {
        int temp;
        if(comparison_flag == 1)    //intal1 > intal2
        {
            if(m > -1 && n < 0)
                temp = (int)intal1[m] - carry - 48;
            else
                temp = (int)intal1[m] - (int)intal2[n] - carry;
        }
        else
        {
            if(m < 0 && n > -1)
                temp = (int)intal2[n] - carry - 48;
            else
                temp = (int)intal2[n] - (int)intal1[m] - carry;
        }

        if(temp < 0)
        {
            temp = temp + 10;
            carry = 1;
        }
        else
            carry = 0;

        result[i] = temp % 10;
        m--; n--; i--;
    }
    
    for(i = 0; i < count; i++)
        result[i] = result[i] + 48;

    stripping_zeroes(result);
    return result;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    if(intal_compare(intal1, "0") == 0 || intal_compare(intal2, "0") == 0) //If anyone value is "0"
    {
        char* res = (char*)malloc(sizeof(char)*2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }
    else if(intal_compare(intal1, "1") == 0)
    {
        char* res = (char*)malloc(sizeof(char)*(strlen(intal2)+1));
        strcpy(res, intal2);
        return res;
    }
    else if(intal_compare(intal2, "1") == 0)
    {
        char* res = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(res, intal1);
        return res;
    }
    int a[1000], b[1000];
    int ans[1200] = {0};
    int i, j, tmp;
    char* res = (char*)malloc(1201 * sizeof(char));
    char* temp = (char*)calloc(1201, sizeof(char));

    int m = strlen(intal1);
    int n = strlen(intal2);

    for(i = m-1, j = 0; i >= 0; i--, j++)
        a[j] = intal1[i] - '0';
    
    for(i = n-1, j = 0; i >= 0; i--, j++)
        b[j] = intal2[i] - '0';

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            ans[i+j] += b[i]*a[j];

    for(i = 0; i < m+n; i++)
    {
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }

    for(i = m+n; i >= 0; i--)
        if(ans[i] > 0)
            break;

    for(; i >= 0; i--)
        temp[i] = ans[i] + 48;

    for(i = 0; i < strlen(temp); i++)
        res[i] = temp[strlen(temp)-i-1];

    free(temp);
    res[i] = '\0';
    return res;
}

char* intal_mod(const char* intal1, const char* intal2)
{
    if(intal_compare(intal1, intal2) == -1)
    {
        char* result = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(result, intal1);
        return result;
    }
    if(intal_compare(intal2, "1") == 0 || intal_compare(intal1, intal2) == 0)
    {
        char* result = (char*)malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    char* a = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
    char* b = (char*)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a, intal1);
    strcpy(b, intal2);

    int m = strlen(intal1);
    int n = strlen(intal2);
    
    int range = m-n;
    int comp = 0;

    while(1)
    {
        if(range > 0)
        {
            char* temp = adding_zeroes(b, range--);
            free(b);
            b = temp;
        }

        comp = (intal_compare(a, b) == -1) ? 1 : 0;

        while(intal_compare(a, b) == 1)
        {
            char* temp = intal_diff(a, b);
            free(a);
            a = temp;

            int comp1 = intal_compare(a, intal2);
            if(comp1 == -1 || comp1 == 0)
            {
                if(!comp)
                    break;
                else
                    comp = 0;
            }

        }
        
        strcpy(b, intal2);
        int res = intal_compare(a, b);
        if(res == 0)
        {
            char* result = intal_diff(a, b);
            free(a);
            free(b);
            return result;
        }
        else if(res == -1)
        {
            free(b);
            return a;
        }
    }
}

char* intal_pow(const char* intal1, unsigned int n)
{
    if(intal_compare(intal1, "0") == 0)   //0^n = 0
    {
        char* result = (char*)malloc(sizeof(char)*2);        
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if(n == 1)  //x^1 = x
    {
        char* result = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(result, intal1);
        return result;
    }
    else if(n == 0 || intal_compare(intal1, "1") == 0)  //x^0 = 1 or 0^n = 1
    {
        char* result = (char*)malloc(sizeof(char)*2);        
        result[0] = '1';
        result[1] = '\0';
        return result;
    }
    else
    {
        if(n % 2 == 1)
        {
            char* temp1 = intal_pow(intal1, n/2);
            char* temp2 = intal_multiply(temp1, temp1);
            free(temp1);

            char* result = intal_multiply(temp2, intal1);
            free(temp2);

            return result;
        }
        else
        {
            char* temp = intal_pow(intal1, n/2);
            char* result = intal_multiply(temp, temp);
            free(temp);

            return result;
        }
    }
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    if(intal_compare(intal2, "0") == 0)     //gcd(a, 0) = a
    {
        char* result = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
        strcpy(result, intal1);
        return result; 
    }
    else if(intal_compare(intal1, "0") == 0)    //gcd(0, b) = b
    {
        char* result = (char*)malloc(sizeof(char)*(strlen(intal2)+1));
        strcpy(result, intal2);
        return result;  
    }
    else                                //gcd(a, b) = gcd(a, a mod b)
    {
        char* temp = intal_mod(intal1, intal2);
        char* result = intal_gcd(intal2, temp);
        free(temp);
        return result;
    }
}

char* intal_fibonacci(unsigned int n)
{
    char* temp1 = (char*)malloc(sizeof(char)*1001);
    temp1[0] = '0'; temp1[1] = '\0';

    char* result = (char*)malloc(sizeof(char)*1001);
    result[0] = '1'; result[1] = '\0';

    if(n == 0)
    {
        free(result);
        return temp1;
    }

    for(int i = 2; i <= n; i++)
    {
        char* temp2 = intal_add(temp1, result);
        strcpy(temp1, result);
        strcpy(result, temp2);
        free(temp2);
    }

    free(temp1);
    return result;
}

char* intal_factorial(unsigned int n)
{
    char* result = (char*)malloc(sizeof(char)*1001);
    result[0] = '1'; result[1] = '\0';

    char* temp1 = (char*)malloc(sizeof(char)*1001);
    temp1[0] = '2'; temp1[1] = '\0';

    if(n == 0 || n == 1)
    {
        free(temp1);
        return result;
    }
    else
        strcpy(result, temp1);
    
    for(int i = 3; i <= n; i++)
    {
        char* temp2 = intal_add(temp1, "1");
        free(temp1);
        temp1 = temp2;
        
        char* temp3 = intal_multiply(result, temp1);
        strcpy(result, temp3);
        free(temp3);
    }
    free(temp1);
    return result;
}

static char* int_to_str(int n)
{
    int i;
    char* res = (char*) malloc(1001 * sizeof(char));
    char* rev = (char*) malloc(1001 * sizeof(char));
    
    for(i = 0; n != 0; i++)
    {
        res[i] = (n % 10)+48;
        n = n / 10;
    }
    res[i] = '\0';
    
    int len = strlen(res)-1;
    for(i = 0; i <= len; i++)
        rev[i] = res[len-i];
    rev[i] = '\0';

    free(res);
    return rev;
}

static char* longDivision(char* number, int divisor) 
{ 
    char* ans = (char*)malloc(sizeof(char)*1001); 
    int idx = 0; 
    int temp = number[idx] - '0';
    while (temp < divisor) 
       temp = temp * 10 + (number[++idx] - '0'); 
    int i = 0;
    while (strlen(number) > idx) 
    { 
        ans[i++] = (temp / divisor) + '0'; 
        temp = (temp % divisor) * 10 + number[++idx] - '0'; 
    } 
    ans[i] = '\0';
    if (strlen(ans) == 0)
        strcpy(ans, "0");

    return ans; 
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    k = (n-k < k) ? n-k : k;

    char **dp = (char**) malloc((k+1) * sizeof(char*));

    dp[0] = (char*) calloc(2, sizeof(char));
    dp[0][0] = '1'; dp[0][1] = '\0';

    for(int i = 1; i <= k; i++)
    {
        int sum_i = n-i+1;

        char* sum = int_to_str(sum_i);
        char* num = intal_multiply(dp[i-1], sum);

        free(sum);

        dp[i] = longDivision(num, i);
        free(num);
    }

    char* result = (char*) calloc(1001, sizeof(char));
    strcpy(result, dp[k]);

    for(int i = 0; i <= k; i++)
        free(dp[i]);
    free(dp);
    
    return result;
}

int intal_max(char **arr, int n)
{
    int i, max = 0;
    for(i = n-1; i > -1; i--)
    {
        int comp = intal_compare(arr[i], arr[max]);
        
        if(comp == 1 || comp == 0)
            max = i;
    }
    return max;
}

int intal_min(char **arr, int n)
{
    int i, min = 0;
    for(i = n-1; i > -1; i--)
    {
        int comp = intal_compare(arr[i], arr[min]);
        
        if(comp == -1 || comp == 0)
            min = i;
    }
    return min;
}

int intal_search(char **arr, int n, const char* key)
{
    int i;
    for(i = 0; i < n; i++)
        if(intal_compare(arr[i], key) == 0)
            return i;
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int l = 0;
    int r = n-1;

    while(l <= r)
    {
        int m = (l+r)/2;
        if(intal_compare(arr[m], key) == 0)
        {
            while(m != 0 && intal_compare(arr[m-1], arr[m]) == 0)
                m--;
            return m;
        }
        if(intal_compare(arr[m], key) == 1)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

void intal_sort(char **arr, int n)
{
    for(int i = (n/2)-1; i >= 0; i--) 
        intal_heapify(arr, n, i); 

    for(int i = n-1; i > 0; i--) 
    {
        char* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        intal_heapify(arr, i, 0); 
    } 
}

char* coin_row_problem(char **arr, int n)
{
    if(n == 0)
    { 
        char* res = (char*)malloc(sizeof(char)*2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    char* prev = (char*)malloc(sizeof(char)*1001);
    prev[0] = '0';
    prev[1] = '\0';

    char* cur = (char*)malloc(sizeof(char)*1001);
    strcpy(cur, arr[0]);

    for(int i = 2; i <= n; i++)
    {
        char* next;
        char* temp = intal_add(prev, arr[i-1]);
        int max = intal_compare(temp, cur);

        if(max == 1 || max == 0)
            next = temp;
        else
            next = cur;
            
        strcpy(prev, cur);
        strcpy(cur, next);
        free(temp);
    }
    free(prev);
    return cur;
}
