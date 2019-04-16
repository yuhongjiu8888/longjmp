#include <setjmp.h>
#include <stdio.h>

jmp_buf env;
int count = 0;

typedef struct _tagExceptionSign
{
    jmp_buf _stackInfo;
    int _exceptype;
}tagExceptionSign;

#define ExcepType(ExcepSign)  ((ExcepSign)._exceptype)
#define Try(ExcepSign)  if(((ExcepSign)._exceptype=setjmp(ExcepSign._stackInfo))==0)
#define Catch(ExcepSign,ExcepType)  else if((ExcepSign)._exceptype == ExcepType)
#define Finally
#define Throw(ExcepSign,ExcepType) longjmp((ExcepSign._stackInfo),ExcepType)

void ExcepionTest(int expType){
    tagExceptionSign ex;
    expType = expType < 0 ? -expType:expType;

    Try(ex){
        if (expType > 0) {
            /* code */
            Throw(ex,expType);
        }else{
            printf("no exception!\n");
        }
        
    }Catch(ex,1){
        printf("exception 1!\n");
    }Finally{
        printf("other\n");
    }
}

int main()
{
    ExcepionTest(0);
    ExcepionTest(1);

    return 0;
}