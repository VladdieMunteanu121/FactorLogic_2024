//Used for building strings from program memory
//type == 0 for title string; type == 1 for instruction string; type == 2 for message string; type == 3 for other
//newString == 1 to start new string; newString == 0 to concatenate
//number == instruction list number
//stringNumber == titleX character array (X = stringNumber); instructionX character array (X = stringNumber)
//leadingReturn == # of leading '\n' before string
//leadingSpace == # of leading ' ' before string (leading return comes before leading space if both are in the same string)

//Title and Instruction String Builder
void stringBuilder(int type, int newString, int number, int stringNumber, int leadingReturn, int leadingSpace)   
{
    //determine max bytes that can be copied into array 
    int maxSize;    
    
    if(newString)   maxSize = sizeof(messageArray) - 1;  
    else            maxSize = sizeof(messageArray) - 1 - strlen(messageArray);     

    //Check errors
    if(maxSize <= 0 || strcmp(messageArray, "ERROR") == 0)  return;    //messageArray too small

    //Write leading returns and spaces (returns come before spaces)
    if(leadingReturn || leadingSpace)   
    {
        for(int i = 0; i < leadingReturn && maxSize > 0; i++, maxSize--)
        {
            if(newString)
            {
                messageArray[i] = '\n';
                messageArray[i+1] = 0x00;
            }
            else
            {
                strncat(messageArray, "\n", maxSize);
            }
        }

        for(int i = 0; i < leadingSpace && maxSize > 0; i++, maxSize--)
        {
            if(newString)
            {
                messageArray[i] = ' ';
                messageArray[i+1] = 0x00;
            }
            else
            {
                strncat(messageArray, " ", maxSize);
            }
        }
               
        newString = 0;    //concatenate string below
    }

    //Write number
    if(number)    //maxSize adjusted for number characters above
    {
        if(newString)
        {
            snprintf(messageArray, maxSize, "%i. ", number);
            newString = 0;
        }
        else
        {
            snprintf(messageArray + strlen(messageArray), maxSize, "%i. ", number);
        }  

        //account for "%i. "
        if(number < 10)  maxSize = maxSize - 3;
        else             maxSize = maxSize - 4;      
    }

    //Write string 
    if(!type)   //title
    {     
        if(newString)   //copy starting at [0]
        {
            strncpy_P(messageArray, (char *)pgm_read_word(&(title_table[stringNumber])), maxSize);
        }
        else    //concatenate
        {
            strncat_P(messageArray, (char *)pgm_read_word(&(title_table[stringNumber])), maxSize);
        }
    }
    else if(type == 1)   //instruction
    {
        if(newString)   //copy starting at [0]
        {
            strncpy_P(messageArray, (char *)pgm_read_word(&(instruction_table[stringNumber])), maxSize);
        }
        else    //concatenate
        {
            strncat_P(messageArray, (char *)pgm_read_word(&(instruction_table[stringNumber])), maxSize);
        }
    }
    else if(type == 2)    //Message
    {
        if(newString)   //copy starting at [0]
        {
            strncpy_P(messageArray, (char *)pgm_read_word(&(message_table[stringNumber])), maxSize);
        }
        else    //concatenate
        {
            strncat_P(messageArray, (char *)pgm_read_word(&(message_table[stringNumber])), maxSize);
        }
    }
    
    //Serial.println(messageArray);
}   //stringBuilder()





//works for 1-3 lines of text
//center each line then add leading '\n'
//characters == max # of characters per line
//NUMreturn == # of leading return before first line
void centerMessageArray(int characters, int NUMreturn)
{    
    int a, b, c;                      //a, b, c = # of characters in first/second/third line (not including '\n')
    int origNUMreturn = 0;            //origNUMreturn == # of leading '\n' from string before centerMessageArray()
    int return2, return3;             //returnX = # of '\n' between line 1 & line 2 or line 2 & line 3
    int spaces1, spaces2, spaces3;    //spacesX = leading spaces in first/second/third line

    //Determine if string has leading '\n'
    for(a = 0; messageArray[a] == '\n'; a++) {}   //a = # of leading '\n'
    if(a > 0)   //leading '\n' exists
    {
        origNUMreturn = a;               
    }

    //Determine # of characters in first line
    for(a; messageArray[a] != '\n' && messageArray[a] != 0x00; a++) {}    //a = origNUMreturn + # of characters in first line (index of '\n' or 0x00)

    if(messageArray[a] == 0x00)   //no more lines
    {
        b = 0;  c = 0;
        spaces2 = 0; spaces3 = 0;
    }
    else if(messageArray[a] == '\n')    //second line
    {
        //Determine # of '\n' between first and second lines
        for(b = a; messageArray[b] == '\n'; b++) {}   //b = a + # of '\n' between line 1 & line 2 (index of character after '\n')
        return2 = b - a;    //return2 = # of '\n' between line 1 & line 2

        //Determine # of characters in second line
        for(b; messageArray[b] != '\n' && messageArray[b] != 0x00; b++) {}    //b = a + return2 + # of characters in second line (index of '\n' or 0x00)
        
        if(messageArray[b] == 0x00)    //no more lines
        {
            c = 0;
            spaces3 = 0;
        }
        else if(messageArray[b] == '\n')    //third line
        {
            //Determine # of '\n' between second and third lines
            for(c = b; messageArray[c] == '\n'; c++) {}   //c = b + # of '\n' between line 2 & line 3 (index of character after '\n')
            return3 = c - b;    //return3 = # of '\n' between line 2 & line 3

            //Determine # of characters in third line
            for(c; messageArray[c] != '\n' && messageArray[c] != 0x00; c++) {}    //c = b + return3 + # of characters in third line (index of 0x00)

            if(messageArray[c] != 0x00)   //ERROR
            {
                stringError(0, 3); return;
            } 

            c = c - b - return3;              //c = # of characters in third line  
            spaces3 = (characters - c) / 2;   //line 3 leading spaces          
        }
        else
        {
            stringError(0, 2); return;
        }

        b = b - a - return2;              //b = # of characters in second line
        spaces2 = (characters - b) / 2;   //line 2 leading spaces
    }
    else
    {
        stringError(0, 1); return;
    }

    a = a - origNUMreturn;              //a = # of characters in first line
    spaces1 = (characters - a) / 2;     //line 1 leading spaces (+origNUMreturn to account for leading '\n')
 
    int i = strlen(messageArray);   //i = length of original array (index of 0x00)
    int j = i + NUMreturn + spaces1 + spaces2 + spaces3;   //j = length of final array (index of 0x00)
    //int n = j;    //for Serial test
    
    //Check that final string with reuturns and leading spaces fits in array
    if(j > sizeof(messageArray) - 1)
    {
        stringError(0, 4); return;
    }

    //Check that # of characters in each line is less than max # of characters per line
    if(a > characters || b > characters || c > characters)
    {
        stringError(0, 5); return;
    }

    int t;    //# of times to run for loop below
    int spaces;
    int returns;
    if(c)       t = 3;
    else if(b)  t = 2;
    else if(a)  t = 1; 

    for(t; t > 0; t--)
    {
        //Add line X leading spaces
        if(t == 3)        
        {
            spaces = spaces3;
            returns = return3;
        }
        else if(t == 2)   
        {
            spaces = spaces2;
            returns = return2;
        }
        else if(t == 1)   
        {
            spaces = spaces1;
            returns = origNUMreturn + NUMreturn;
        }
       
        //right shift line X characters
        for(i; messageArray[i] != '\n' && i >= origNUMreturn; i--, j--)
        {
            messageArray[j] = messageArray[i];    
        }

        //Add line X leading ' '            
        for(int k = 0; k < spaces && j >= 0; k++, j--)
        {
            messageArray[j] = ' ';
        }

        //Add line X leading '\n'
        for(int k = 0; k < returns; k++, i--, j--)
        {
            messageArray[j] = '\n';
        }
    }

    if(j != -1)  stringError(0, 6);   //Error check
}   //centerMessageArray()





void stringError(int type, int format)
{
    if(!type)   snprintf(messageArray, sizeof(messageArray) - 1, "ERROR %i", format);
}



void writeDisplayString(int stringNum)
{   
    genie.WriteStr(stringNum, messageArray);
}