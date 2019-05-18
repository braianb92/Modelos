#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#define TAM_STRING 10

///ESTE PROGRAMA FUE COMPILADO EN WINDOWS. AUTOR BRAIAN BALDINO.
/** \brief  Asks user to enter something.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \return   return 0.
**/
int getString(char* pointerString, char* msg, char*msgE)
{
    char bufferStr[TAM_STRING];
    printf(msg);
    fgets(bufferStr,sizeof(bufferStr),stdin);
    bufferStr[strlen(bufferStr)-1] = '\0';
    if(pointerString!=NULL)
    {
        strncpy(pointerString,bufferStr,sizeof(bufferStr));
    }
    return 0;
}

/** \brief  Asks user to enter a number(integer).
* \param    pointerNumber Pointer to integer
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \return   return 0.
**/
int getInt (int *pointerNumber, char* msg, char* msgE)

{
    int number;
    int ret=-1;
    printf(msg);
    if(scanf("%d",&number)==1)
    {
        (*pointerNumber)=number;
        ret=0;
    }
    else
    {
        printf(msgE);
        fflush(stdin);
        //fpurge(stdin);
    }
    return ret;
}

/** \brief  Asks user to enter a number(float).
* \param    pointerNumber Pointer to integer
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \return   return 0.
**/
int getFloat (float *pointerNumber, char* msg, char* msgE)

{
    float number;
    int ret=-1;
    printf(msg);
    if(scanf("%f",&number)==1)
    {
        (*pointerNumber)=number;
        ret=0;
    }
    else
    {
        printf(msgE);
    }
    return ret;
}

/** \brief  Asks user to enter a number(integer)
*           withing a range.
* \param    pointerNumber Pointer to integer
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    minimo Minimum number to be entered.
* \param    maximo Maximum number to be entered.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getIntInRange(  int *pointerNumber,
                    char *msg,
                    char *msgE,
                    int minimo,
                    int maximo,
                    int tries)
{
    int retorno = -1;
    char bufferStr[TAM_STRING];
    int bufferInt;
    do
    {

        if((pointerNumber != NULL)&&(!getStringNumeros(bufferStr,msg,msgE,tries)))
        {
            bufferInt=atoi(bufferStr);
            if(bufferInt>=minimo&&bufferInt<=maximo)
            {
                retorno = 0;
                *pointerNumber = bufferInt;
            }
            else
            {
                printf("El numero esta fuera del rango!\n");
                tries--;
            }
        }
        else
        {
            printf("No es un numero valido!\n");
            tries--;
        }
    } while(retorno==-1&&tries>0);
    return retorno;
}

/** \brief  Asks user to enter text
*           validating that the text contains
*           no numbers or special characters.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getStringLetras (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
            &&(isLetter(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter text(number)
*           validating that the string is a number.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getStringNumeros (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int retorno=-1;
    while(retorno==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isNumber(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            retorno=0;
        }
        else
        {
            printf(msgE);
            retorno=-1;
            tries--;
        }
    }
    return retorno;
}

/** \brief  Asks user to enter text(float number)
*           validating that the string is a float number.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getStringNumerosFloat (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int retorno=-1;
    while(retorno==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isNumberFloat(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            retorno=0;
        }
        else
        {
            printf(msgE);
            retorno=-1;
            tries--;
        }
    }
    return retorno;
}

/** \brief  Asks user to enter text (alphanumeric)
*           validating that the text contains
*           only numbers or letters or '-'.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getStringAlphanumeric (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isAlphanumeric(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter a valid
*           phone number. One '-' is allowed.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getTelephone (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isTelephone(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter a valid DNI.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getDni (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isDni(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter a valid CUIT.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getCuit (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isCuit(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter a day, month and year
*           validating the values in the shape of date.
* \param    day Integer pointer to day value.
* \param    month Integer pointer to day value.
* \param    year Integer pointer to day value.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getDate (int* day,int* month, int* year, char* msgE,int tries)
{
    int auxDay;
    int auxMonth;
    int auxYear;
    int retorno=-1;
    if((day!=NULL)&&(month!=NULL)&&(year!=NULL))
    {
        while(retorno==-1 && tries>0)
        {
            if((!getInt(&auxDay,"\nIngrese Dia: ",msgE))
               &&(!getInt(&auxMonth,"\nIngrese Mes: ",msgE))
               &&(!getInt(&auxYear,"\nIngrese Year: ",msgE))
               &&(isDate(auxDay,auxMonth,auxYear)))
            {
                *day=auxDay;
                *month=auxMonth;
                *year=auxYear;
                retorno=0;
            }
            else
            {
                printf(msgE);
                retorno=-1;
                tries--;
            }
        }
    }
    return retorno;
}

/** \brief  Asks user to enter a valid MAIL
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getMail (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isMail(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Asks user to enter his/her gender.
* \param    pointerString Pointer to string array
* \param    msg Message to be shown to the user.
* \param    msgE Error message to be shown to the user.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int getGender (char* pointerString, char* msg, char* msgE,int tries)
{
    char bufferStr[TAM_STRING];
    int ret=-1;
    while(ret==-1 && tries>0)
    {
        if(!getString(bufferStr,msg,msgE)&&(pointerString!=NULL)
           &&(isGender(bufferStr)))
        {
            strncpy(pointerString,bufferStr,sizeof(bufferStr));
            ret=0;
        }
        else
        {
            printf(msgE);
            tries--;
        }
    }
    return ret;
}

/** \brief  Validates if sting contains only numbers (integer).
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isNumber (char* pointerString)
{
    int i=0;
    while(pointerString[i]!='\0')
    {
        if(pointerString[i]<'0' || pointerString[i]>'9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}
/** \brief  Validates if sting contains only numbers (float).
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isNumberFloat (char* pointerString)
{
    int i=0;
    int contadorPuntos=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]<'0' || pointerString[i]>'9')
           &&(pointerString[i]!='.'))
        {
            return 0;
        }
        if(pointerString[i]=='.')
        {
            contadorPuntos++;
            if(contadorPuntos>1)
            {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

/** \brief  Validates if sting contains only letters.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isLetter (char* pointerString)
{
    int i=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]!=' ')&&(pointerString[i]<'a'||pointerString[i]>'z')
           &&(pointerString[i]<'A'||pointerString[i]>'Z'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/** \brief  Validates if sting contains only letters,
*           numbers, spaces or a dot.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isAlphanumeric (char* pointerString)
{
    int i=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]!=' ')&&(pointerString[i]!='.')
           &&(pointerString[i]<'a'||pointerString[i]>'z')
           &&(pointerString[i]<'A'||pointerString[i]>'Z')
           &&(pointerString[i]<'0' || pointerString[i]>'9'))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/** \brief  Validates if sting contains only numbers,
*           spaces or a dash(only one).
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isTelephone (char* pointerString)
{
    int i=0;
    int contadorGuion=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]!=' ')
           &&(pointerString[i]!='-')
           &&(pointerString[i]<'0' || pointerString[i]>'9'))
        {
            return 0;
        }
        if(pointerString[i]=='-')
        {
            contadorGuion++;
        }
        i++;
    }
    if(contadorGuion==1 || contadorGuion==0)
        {
            return 1;
        }
    return 0;
}

/** \brief  Validates if sting contains only numbers
*           and if its lengh is 7 as minimun accepted
*           or 8 as maximum accepted for a DNI.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isDni (char* pointerString)
{
    int i=0;
    while(pointerString[i]!='\0')
    {
        if(!isNumber(pointerString))
        {
            return 0;
        }
        if(strlen(pointerString)<7 || strlen(pointerString)>8)
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/** \brief  Validates if sting contains only numbers,
*           and two dashes in fixed position.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isCuit (char* pointerString)
{
    int ret=0;
    int i=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]!='-')
           &&(pointerString[i]<'0' || pointerString[i]>'9'))
        {
            return 0;
        }
        else if((pointerString[2]=='-')
                &&(pointerString[10]=='-' || pointerString[11]=='-'))
        {
            ret=1;
        }
        i++;
    }
    return ret;
}

/** \brief  Validates a range of years,
*           month and day with appropriate
*           amount of days corresponding to
*           different months.
* \param    day value to be validated.
* \param    mont value to be validated.
* \param    year value to be validated.
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isDate (int day,int month,int year)
{
    int ret=0;
    if((year<1800 || year>2090)
       ||(month<1 || month>12)
       ||(day<1 || day>31))
    {
        return 0;
    }
    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ret=1;
            break;
        case 2:
            if(day<=29)
            {
                ret=1;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(day<=30)
            {
                ret=1;
            }
            break;
    }

    return ret;
}

/** \brief  Validates if sting contains only letters,
*           numbers, one '@' or a dot.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isMail (char* pointerString)
{
    int i=0;
    int contadorPunto=0;
    int contadorArroba=0;
    int retorno=0;
    while(pointerString[i]!='\0')
    {
        if((pointerString[i]!='@')&&(pointerString[i]!='.')
           &&(pointerString[i]<'a'||pointerString[i]>'z')
           &&(pointerString[i]<'A'||pointerString[i]>'Z')
           &&(pointerString[i]<'0' || pointerString[i]>'9'))
        {
            return 0;
        }
        if(pointerString[i]=='.')
        {
            contadorPunto++;
        }
        if(pointerString[i]=='@')
        {
            contadorArroba++;
        }
        i++;
    }
    if(contadorPunto>=1&&contadorArroba==1)
    {
        retorno=1;
    }
    return retorno;
}

/** \brief  Validates if sting contains only one
*           character. Only F or M.
* \param    pointerString Pointer to string array
* \return   return (1) if VALID, (0) if NO VALID.
**/
int isGender (char* pointerString)
{
    int retorno=0;
    if(strlen(pointerString)==1)
    {
        if((strcmp(pointerString,"F")==0)
           ||(strcmp(pointerString,"M")==0))
        {
            retorno=1;
        }
    }
    return retorno;
}
