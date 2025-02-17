/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  HEARTBEAT_OFF();


  LcdCommand(LCD_CLEAR_CMD);

  LcdMessage(LINE2_START_ADDR, ">");
  LcdMessage(LINE2_START_ADDR + 6, "$");
  LcdMessage(LINE2_START_ADDR + 12, "<-");
  LcdMessage(LINE2_END_ADDR - 1 , "->");

  /* If good initialization, set state to Idle */

  if( 1 )
  {
 
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void UserApp1SM_Idle(void)
{
  u32 current_song_index = 0; // Used to index the song list
  u32 num_of_songs; // Number of tracks loaded onto the board/SD Card
  

  if(IsButtonPressed(BUTTON0)) // Play Current Track; Current Title Displayed. Press again to cease current song. Just the left arrow, perhaps a custom play button if I get to it
  {
    ButtonAcknowledge(BUTTON0);
  }

  if(IsButtonPressed(BUTTON1)) // Play Shuffle. Press again to cease shuffle/current song.
  {
    ButtonAcknowledge(BUTTON1);

    current_song_index = G_u32SystemTime1ms % num_of_songs;
    
  }

  if(IsButtonPressed(BUTTON2)) // Scroll Left. Symbol Left arrow on ASCII
  {
    ButtonAcknowledge(BUTTON2);

    if(current_song_index > 0)
      current_song_index--;

  }

  if(IsButtonPressed(BUTTON3)) // Scroll Left. Symbol left arrow on ASCII
  {
    ButtonAcknowledge(BUTTON3);

    if (current_song_index < num_of_songs)
      current_song_index++;

  }



  // static u16 au16NotesRight[] =    {0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 416, 0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 416, 0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 467, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 467, 0, 350, 0, 467, 0, 467, 0, 524, 0, 588, 0, 623, 0, 699, 0, 699, 0, 699, 0, 740, 0, 831, 0, 933, 0, 933, 0, 933, 0, 933, 0, 831, 0, 740, 0, 831, 0, 740, 0, 699, 0, 699, 0, 623, 0, 623, 0, 699, 0, 740, 0, 699, 0, 623, 0, 555, 0, 555, 0, 623, 0, 699, 0, 623, 0, 555, 0, 524, 0, 524, 0, 588, 0, 660, 0, 784, 0, 699, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 467, 0, 350, 0, 467, 0, 467, 0, 524, 0, 588, 0, 623, 0, 699, 0, 699, 0, 699, 0, 740, 0, 831, 0, 933, 0, 1109, 0, 1047, 0, 880, 0, 699, 0, 740, 0, 933, 0, 880, 0, 699, 0, 699, 0, 740, 0, 933, 0, 880, 0, 699, 0, 588, 0, 623, 0, 740, 0, 699, 0, 555, 0, 467, 0, 524, 0, 524, 0, 588, 0, 660, 0, 784, 0, 699, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0, 350, 0};
  // static u16 au16DurationRight[] = {0, 3243, 1081, 355, 186, 355, 186, 355, 186, 355, 186, 524, 557, 355, 186, 2162, 541, 355, 186, 355, 186, 355, 186, 355, 186, 524, 557, 355, 186, 2416, 287, 355, 186, 355, 186, 355, 186, 355, 186, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 541, 270, 1081, 541, 2416, 422, 389, 17, 389, 17, 389, 17, 389, 17, 389, 17, 3226, 828, 541, 270, 524, 17, 524, 17, 524, 17, 3767, 17, 524, 17, 524, 17, 524, 17, 524, 17, 524, 17, 524, 557, 524, 17, 3226, 17, 1605, 17, 794, 17, 389, 17, 389, 17, 3226, 17, 794, 17, 794, 17, 794, 17, 389, 17, 389, 17, 3226, 17, 794, 17, 794, 17, 794, 17, 389, 17, 389, 17, 3226, 17, 1605, 17, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 541, 270, 1081, 541, 2416, 422, 389, 17, 389, 17, 389, 17, 389, 17, 389, 17, 3226, 828, 541, 270, 524, 17, 524, 17, 524, 17, 4848, 17, 1605, 17, 811, 811, 2703, 541, 1605, 17, 3514, 1351, 1605, 17, 811, 811, 2703, 541, 1605, 17, 3226, 1639, 1605, 17, 794, 828, 3226, 17, 1605, 17, 3226, 1639, 1605, 17, 794, 828, 3226, 17, 1605, 17, 794, 17, 389, 17, 389, 17, 3226, 17, 1605, 17, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 270, 135, 270, 135, 541, 270, 541, 0};
 
  // static u16 au16NotesLeft[] = {0, 117, 0, 117, 0, 117, 0, 117, 0, 117, 0, 117, 0, 117, 0, 117, 0, 104, 0, 104, 0, 104, 0, 104, 0, 104, 0, 104, 0, 104, 0, 104, 0, 93, 0, 93, 0, 93, 0, 93, 0, 93, 0, 93, 0, 93, 0, 93, 0, 93, 0, 88, 0, 88, 0, 98, 0, 110, 0, 117, 0, 117, 0, 117, 0, 104, 0, 117, 0, 117, 0, 104, 0, 104, 0, 104, 0, 93, 0, 104, 0, 104, 0, 93, 0, 93, 0, 93, 0, 83, 0, 93, 0, 93, 0, 139, 0, 139, 0, 139, 0, 124, 0, 139, 0, 139, 0, 124, 0, 124, 0, 124, 0, 117, 0, 124, 0, 124, 0, 124, 0, 124, 0, 117, 0, 117, 0, 117, 0, 104, 0, 117, 0, 117, 0, 117, 0, 117, 0, 131, 0, 131, 0, 131, 0, 117, 0, 131, 0, 131, 0, 131, 0, 131, 0, 88, 0, 88, 0, 88, 0, 98, 0, 110, 0, 117, 0, 117, 0, 117, 0, 104, 0, 117, 0, 117, 0, 104, 0, 104, 0, 104, 0, 93, 0, 104, 0, 104, 0, 93, 0, 93, 0, 93, 0, 83, 0, 93, 0, 93, 0, 88, 0, 88, 0, 88, 0, 78, 0, 88, 0, 88, 0, 83, 0, 117, 0, 139, 0, 165, 0, 234, 0, 278, 0, 330, 0, 350, 0, 88, 0, 88, 0, 88, 0, 88, 0, 83, 0, 117, 0, 139, 0, 165, 0, 234, 0, 278, 0, 330, 0, 350, 0, 88, 0, 88, 0, 88, 0, 88, 0, 124, 0, 124, 0, 124, 0, 117, 0, 124, 0, 124, 0, 124, 0, 124, 0, 117, 0, 117, 0, 117, 0, 104, 0, 117, 0, 117, 0, 117, 0, 117, 0, 131, 0, 131, 0, 131, 0, 131, 0, 131, 0, 131, 0, 131, 0, 131, 0, 88, 0, 88, 0, 88, 0, 98, 0, 110, 0};
  // static u16 au16DurationLeft[] = {0, 1081, 541, 355, 186, 355, 186, 355, 186, 1081, 541, 355, 186, 355, 186, 355, 186, 1081, 541, 355, 186, 355, 186, 355, 186, 1081, 541, 355, 186, 355, 186, 355, 186, 1081, 541, 355, 186, 355, 186, 355, 186, 1081, 541, 355, 186, 355, 186, 355, 186, 794, 828, 541, 1081, 541, 1081, 794, 17, 794, 17, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 794, 828, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 524, 17, 524, 17, 524, 17, 794, 828, 524, 17, 524, 17, 524, 17, 541, 1081, 541, 1081, 541, 1081, 794, 17, 794, 17, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1081, 541, 1081, 355, 186, 355, 186, 524, 17, 541, 1081, 541, 1081, 355, 186, 355, 186, 355, 186, 355, 186, 355, 186, 355, 186, 541, 2703, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 2703, 355, 186, 355, 186, 355, 186, 355, 186, 355, 186, 355, 186, 541, 2703, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 2703, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 355, 186, 355, 186, 355, 186, 541, 1081, 541, 1216, 541, 946, 794, 17, 794, 0};

  // static u32 u32IndexRight = 0;
  // static u32 u32RightTimer = 0;
  // static u16 u16CurrentDurationRight = 0;

  // static u32 u32IndexLeft = 0;
  // static u32 u32LeftTimer = 0;
  // static u16 u16CurrentDurationLeft = 0;

  // u32 u32CurrentIndex;

  // if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  // {
  //   u32RightTimer = G_u32SystemTime1ms;
  //   u32CurrentIndex = u32IndexRight;

  //   u16CurrentDurationRight = au16DurationRight[u32CurrentIndex];
        
  //   if(u32IndexRight < sizeof(au16NotesRight) / sizeof(u16))
  //     u32IndexRight++;

  //   if(au16NotesRight[u32CurrentIndex] != 0)
  //   {
  //     PWMAudioSetFrequency(BUZZER1, au16NotesRight[u32CurrentIndex]);
  //     PWMAudioOn(BUZZER1);
  //   }
  //   else
  //   {
  //     PWMAudioOff(BUZZER1);
  //   }
  // }

  // if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  // {
  //   u32LeftTimer = G_u32SystemTime1ms;
  //  u32CurrentIndex = u32IndexLeft;

  //   u16CurrentDurationLeft = au16DurationLeft[u32CurrentIndex];

  //   if(u32IndexLeft < sizeof(au16NotesLeft) / sizeof(u16))
  //     u32IndexLeft++;

  //   if(au16NotesRight[u32CurrentIndex] != 0)
  //   {
  //     PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u32CurrentIndex]);
  //     PWMAudioOn(BUZZER2);
  //   }
  //   else
  //   {
  //     PWMAudioOff(BUZZER2);
  //   }
  // }
} /* end UserApp1SM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
