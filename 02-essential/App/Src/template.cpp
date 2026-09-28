#include "mcal_reg.h"
#include "uart.h"

// int int_add(int a, int b){
// 
//   return a+b;
// }
// 
// int float_add(float a, float b){
// 
//   return a+b;
// }

template<class T>
T add(T a, T b)
{
    return a + b;
}

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    int num1  = 45;
	int num2  = 67;
	int ans;
	
	float fnum1 =  78.9;
	float fnum2 = 54.78;
	float f_ans;

    // ans =  float_adder(num1,num2);
    // f_ans = float_adder(fnum1,fnum2);
	ans  = add(num1,num2);
	f_ans = add(fnum1,fnum2);
	
	printf("The int result is %d  \n\r",ans);
	printf("The float result is %.2f \n\r",f_ans);

    while(1)
    {
        
    }
}

