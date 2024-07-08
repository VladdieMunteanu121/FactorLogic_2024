//Display Winbutton Array
//Command = resulting command of the button press
//State = resulting stateMachine state of the button press
//Screen = resulting screen (form) of the button press

//RUN buttons will have "false" as screen b/c this is controlled from the state table
//WAIT buttons will have a screen b/c the button triggers a screen change but not a state change

//If the button has conditional states then these states are input as State 2 and/or State 3; otherwise, these are "false"

int buttonMachine[buttonRows][buttonColumns] =
{
    //    Command         Screen          
    {     WAIT      ,     4        },   //Button 0
    {     WAIT      ,     6        },   //Button 1
    {     WAIT      ,     8        },   //Button 2
    {     WAIT      ,     9        },   //Button 3
    {     MANUAL    ,     false    },   //Button 4
    {     MANUAL    ,     false    },   //Button 5
    {     MANUAL    ,     false    },   //Button 6
    {     MANUAL    ,     false    },   //Button 7
    {     MANUAL    ,     false    },   //Button 8
    {     MANUAL    ,     false    },   //Button 9
    {     WAIT      ,     4        },   //Button 10
    {     WAIT      ,     4        },   //Button 11
    {     MANUAL    ,     false    },   //Button 12
    {     MANUAL    ,     false    },   //Button 13
    {     MANUAL    ,     false    },   //Button 14
    {     MANUAL    ,     false    },   //Button 15
    {     MANUAL    ,     false    },   //Button 16
    {     MANUAL    ,     false    },   //Button 17
    {     WAIT      ,     2        },   //Button 18
    {     WAIT      ,     15       },   //Button 19
    {     WAIT      ,     1        },   //Button 20

    {     WAIT      ,     3        },   //Button 21
    {     WAIT      ,     false    },   //Button 22
    {     WAIT      ,     false    },   //Button 23
    {     WAIT      ,     false    },   //Button 24
    {     WAIT      ,     false    },   //Button 25
    {     CALIBRATE ,     false    },   //Button 26
    {     WAIT      ,     false    },   //Button 27
    {     WAIT      ,     false    },   //Button 28
    {     WAIT      ,     false    },   //Button 29
    {     TIMER     ,     false    },   //Button 30
    {     WAIT      ,     false    },   //Button 31
    {     WAIT      ,     false    },   //Button 32
    {     RUN       ,     false    },   //Button 33
    {     WAIT      ,     false    },   //Button 34
    {     WAIT      ,     false    },   //Button 35
    {     WAIT      ,     22       },   //Button 36
    {     WAIT      ,     22       },   //Button 37
    {     WAIT      ,     1        },   //Button 38
    {     WAIT      ,     22       },   //Button 39
    {     RUN       ,     false    },   //Button 40 (Begin button on Form 19)

    {     WAIT      ,     10       },   //Button 41
    {     WAIT      ,     5        },   //Button 42
    {     WAIT      ,     5        },   //Button 43
    {     WAIT      ,     1        },   //Button 44
    {     WAIT      ,     5        },   //Button 45
    {     WAIT      ,     23       },   //Button 46
    {     WAIT      ,     23       },   //Button 47
    {     WAIT      ,     1        },   //Button 48
    {     WAIT      ,     false    },   //Button 49
    {     WAIT      ,     false    },   //Button 50
    {     WAIT      ,     false    },   //Button 51
    {     TIMER     ,     false    },   //Button 52 (Resume button on Form 12)
    {     MANUAL    ,     false    },   //Button 53   
    {     WAIT      ,     4        },   //Button 54
    {     MANUAL    ,     false    },   //Button 55
            {     WAIT      ,     false    },   //Button 56
    {     MANUAL    ,     false    },   //Button 57
    {     MANUAL    ,     false    },   //Button 58
    {     MANUAL    ,     false    },   //Button 59
    {     WAIT      ,     false    },   //Button 60

    {     MANUAL    ,     false    },   //Button 61
    {     MANUAL    ,     false    },   //Button 62
    {     MANUAL    ,     false    },   //Button 63
    {     MANUAL    ,     false    },   //Button 64
    {     WAIT      ,     4        },   //Button 65
    {     MANUAL    ,     false    },   //Button 66
    {     MANUAL    ,     false    },   //Button 67
    {     MANUAL    ,     false    },   //Button 68
    {     MANUAL    ,     false    },   //Button 69
    {     MANUAL    ,     false    },   //Button 70
    {     MANUAL    ,     false    },   //Button 71
    {     WAIT      ,     4        },   //Button 72
    {     WAIT      ,     24       },   //Button 73
    {     MANUAL    ,     false    },   //Button 74
    {     RUN       ,     false    },   //Button 75
    {     WAIT      ,     17       },   //Button 76
    {     WAIT      ,     1        },   //Button 77
    {     MANUAL    ,     false    },   //Button 78
    {     WAIT      ,     34       },   //Button 79
    {     MANUAL    ,     false    },   //Button 80

    {     MANUAL    ,     false    },   //Button 81
    {     MANUAL    ,     false    },   //Button 82
    {     MANUAL    ,     false    },   //Button 83
    {     MANUAL    ,     false    },   //Button 84
    {     WAIT      ,     false    },   //Button 85
    {     WAIT      ,     false    },   //Button 86
    {     WAIT      ,     false    },   //Button 87
    {     WAIT      ,     false    },   //Button 88
    {     WAIT      ,     false    },   //Button 89
    {     WAIT      ,     false    },   //Button 90
    {     WAIT      ,     false    },   //Button 91
    {     WAIT      ,     false    },   //Button 92
    {     WAIT      ,     false    },   //Button 93
    {     WAIT      ,     false    },   //Button 94
    {     WAIT      ,     false    },   //Button 95
    {     WAIT      ,     false    },   //Button 96
    {     WAIT      ,     false    },   //Button 97
    {     WAIT      ,     false    },   //Button 98
    {     WAIT      ,     false    },   //Button 99
    {     WAIT      ,     false    },   //Button 100

    {     WAIT      ,     false    },   //Button 101
    {     WAIT      ,     false    },   //Button 102
    {     WAIT      ,     false    },   //Button 103
    {     WAIT      ,     false    },   //Button 104
    {     WAIT      ,     false    },   //Button 105
    {     WAIT      ,     false    },   //Button 106
    {     WAIT      ,     false    },   //Button 107
    {     WAIT      ,     false    },   //Button 108
    {     WAIT      ,     false    },   //Button 109
    {     MANUAL    ,     false    },   //Button 110

    {     RECOVERY  ,     25       },   //Button 111
    {     RECOVERY  ,     26       },   //Button 112
    {     RECOVERY  ,     27       },   //Button 113
    {     RECOVERY  ,     28       },   //Button 114
    {     RECOVERY  ,     29       },   //Button 115
    {     RECOVERY  ,     30       },   //Button 116
    {     RECOVERY  ,     31       },   //Button 117
    {     WAIT      ,     1        },   //Button 118
    {     RECOVERY  ,     24       },   //Button 119
    {     RECOVERY  ,     24       },   //Button 120
    {     RECOVERY  ,     32       },   //Button 121
    {     RECOVERY  ,     32       },   //Button 122
    {     RECOVERY  ,     32       },   //Button 123
    {     RECOVERY  ,     32       },   //Button 124
    {     RECOVERY  ,     24       },   //Button 125
    {     RECOVERY  ,     32       },   //Button 126
    {     RECOVERY  ,     32       },   //Button 127
    {     RECOVERY  ,     32       },   //Button 128
    {     RECOVERY  ,     32       },   //Button 129
    {     RECOVERY  ,     32       },   //Button 130
    {     RECOVERY  ,     32       },   //Button 131
    {     RECOVERY  ,     32       },   //Button 132
    {     RECOVERY  ,     32       },   //Button 133
    {     RECOVERY  ,     32       },   //Button 134
    {     RECOVERY  ,     32       },   //Button 135
    {     RECOVERY  ,     24       },   //Button 136
    {     RECOVERY  ,     32       },   //Button 137
    {     RECOVERY  ,     32       },   //Button 138
    {     RECOVERY  ,     32       },   //Button 139
    {     RECOVERY  ,     32       },   //Button 140
    {     RECOVERY  ,     32       },   //Button 141
    {     RECOVERY  ,     32       },   //Button 142
    {     RECOVERY  ,     32       },   //Button 143
    {     RECOVERY  ,     32       },   //Button 144
    {     WAIT      ,     false    },   //Button 145
    {     RECOVERY  ,     32       },   //Button 146
    {     RECOVERY  ,     24       },   //Button 147
    {     RECOVERY  ,     32       },   //Button 148
    {     RECOVERY  ,     32       },   //Button 149
    {     RECOVERY  ,     32       },   //Button 150
    {     RECOVERY  ,     32       },   //Button 151
    {     RECOVERY  ,     32       },   //Button 152
    {     RECOVERY  ,     24       },   //Button 153
    {     RECOVERY  ,     32       },   //Button 154
    {     RECOVERY  ,     32       },   //Button 155
    {     RECOVERY  ,     32       },   //Button 156
    {     RECOVERY  ,     32       },   //Button 157

    {     RECOVERY  ,     32       },   //Button 158
    {     RECOVERY  ,     32       },   //Button 159
    {     RECOVERY  ,     32       },   //Button 160
    {     RECOVERY  ,     32       },   //Button 161
    {     RECOVERY  ,     32       },   //Button 162
    {     WAIT      ,     false    },   //Button 163
    {     RECOVERY  ,     24       },   //Button 164
    {     RECOVERY  ,     32       },   //Button 165
    {     RECOVERY  ,     32       },   //Button 166
    {     RECOVERY  ,     32       },   //Button 167
    {     RECOVERY  ,     32       },   //Button 168
    {     RECOVERY  ,     32       },   //Button 169
    {     RECOVERY  ,     32       },   //Button 170
    {     RECOVERY  ,     24       },   //Button 171
    {     RECOVERY  ,     false    },   //Button 172
    {     RECOVERY  ,     32       },   //Button 173
    {     RECOVERY  ,     32       },   //Button 174
    {     MANUAL    ,     false    },   //Button 175
    {     TIMER     ,     false    },   //Button 176
    {     TIMER     ,     false    },   //Button 177
    {     TIMER     ,     false    },   //Button 178
    {     MANUAL     ,     false    },   //Button 179
    {     MANUAL     ,     false    },   //Button 180
    {     MANUAL     ,     false    },   //Button 181
    {     MANUAL     ,     false    },   //Button 182
    {     MANUAL     ,     false    },   //Button 183
    {     MANUAL     ,     false    },   //Button 184

}; //buttonStateMachine()


int recoveryTable[recoveryRows][recoveryColumns] =
{
    // Routine     recoveryState          
    {  1        ,  1              },   //recoveryIndex 0
    {  1        ,  5              },   //recoveryIndex 1
    {  1        ,  7              },   //recoveryIndex 2
    {  2        ,  9              },   //recoveryIndex 3
    {  2        ,  10              },   //recoveryIndex 4
    {  2        ,  11              },   //recoveryIndex 5
    {  2        ,  12              },   //recoveryIndex 6
    {  2        ,  13              },   //recoveryIndex 7
    {  2        ,  14              },   //recoveryIndex 8
    {  2        ,  15              },   //recoveryIndex 9
    {  2        ,  16              },   //recoveryIndex 10
    {  2        ,  17              },   //recoveryIndex 11
    {  3        ,  18              },   //recoveryIndex 12
    {  3        ,  19              },   //recoveryIndex 13
    {  3        ,  20              },   //recoveryIndex 14
    {  4        ,  22              },   //recoveryIndex 15
    {  4        ,  23              },   //recoveryIndex 16
    {  4        ,  24              },   //recoveryIndex 17
    {  4        ,  25              },   //recoveryIndex 18
    {  4        ,  26              },   //recoveryIndex 19
    {  4        ,  27              },   //recoveryIndex 20
    {  4        ,  28              },   //recoveryIndex 21
    {  4        ,  29              },   //recoveryIndex 22
    {  5        ,  31              },   //recoveryIndex 23
    {  5        ,  32              },   //recoveryIndex 24
    {  5        ,  33              },   //recoveryIndex 25
    {  5        ,  34              },   //recoveryIndex 26
    {  5        ,  35              },   //recoveryIndex 27
    {  5        ,  36              },   //recoveryIndex 28
    {  7        ,  45              },   //recoveryIndex 29
    {  7        ,  46              },   //recoveryIndex 30
    {  7        ,  47              },   //recoveryIndex 31
    {  7        ,  48              },   //recoveryIndex 32
    {  7        ,  49              },   //recoveryIndex 33
    {  7        ,  50              },   //recoveryIndex 34
    {  7        ,  51              },   //recoveryIndex 35
    {  7        ,  52              },   //recoveryIndex 36
    {  8        ,  54              },   //recoveryIndex 37
    {  8        ,  55              },   //recoveryIndex 38
    {  8        ,  56              },   //recoveryIndex 39
    {  8        ,  57              },   //recoveryIndex 40
    {  8        ,  58              },   //recoveryIndex 41
    {  8        ,  59              },   //recoveryIndex 42
    {  2        ,  60              },   //recoveryIndex 43
    {  2        ,  8               },   //recoveryIndex 44
};