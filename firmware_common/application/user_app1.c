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
/* Jukebox Interface*/
static void UserApp1SM_Idle(void)
{
//   static u32 current_song_index = 0; // Used to index the song list
//   static u32 num_of_songs; // Number of tracks loaded onto the board/SD Card
//   static bool playing; //  Tell us whether or not a song is currently playing
//   static bool shuffling; // Whether or not the shuffle mode is currently enabled
//   static bool shuffle_play; // Shuffle play state

//   LcdMessage(LINE1_START_ADDR, current_song_index);

//   if(IsButtonPressed(BUTTON0)) // Play Current Track; Current Title Displayed. Press again to cease current song. Just the left arrow, perhaps a custom play button if I get to it
//   {
//     ButtonAcknowledge(BUTTON0);

//     if (!playing)
//       playing = TRUE;
//     else
//       playing = FALSE;
    
//     if (playing)
//     {
//       Jukebox(current_song_index); // Doesn't work yet
//     }
//   }

//   if(IsButtonPressed(BUTTON1)) // Play Shuffle. Press again to cease shuffle/current song. Selects a random song
//   {
//     ButtonAcknowledge(BUTTON1);

//     current_song_index = G_u32SystemTime1ms % num_of_songs;
    
//   }

//   if(IsButtonPressed(BUTTON2)) // Scroll Left. Symbol Left arrow on ASCII
//   {
//     ButtonAcknowledge(BUTTON2);

//     if(current_song_index > 0)
//       current_song_index--;
//   }

//   if(IsButtonPressed(BUTTON3)) // Scroll Left. Symbol left arrow on ASCII
//   {
//     ButtonAcknowledge(BUTTON3);

//     if (current_song_index < num_of_songs)
//       current_song_index++;
//   }

// } /* end UserApp1SM_Idle() */

// static void Jukebox(u32 current_song_index) 
// {
  static u32 au32NotesRight[] =    {0, 294, 0, 330, 0, 370, 0, 392, 0, 440, 0, 467, 0, 494, 0, 494, 0, 494, 0, 494, 0, 494, 0, 392, 0, 660, 0, 623, 0, 660, 0, 392, 0, 440, 0, 494, 0, 524, 0, 588, 0, 660, 0, 623, 0, 699, 0, 660, 0, 392, 0, 588, 0, 555, 0, 588, 0, 392, 0, 440, 0, 494, 0, 524, 0, 555, 0, 588, 0, 392, 0, 699, 0, 660, 0, 392, 0, 784, 0, 784, 0, 784, 0, 784, 0, 880, 0, 784, 0, 699, 0, 699, 0, 699, 0, 699, 0, 784, 0, 699, 0, 660, 0, 440, 0, 494, 0, 699, 0, 660, 0, 660, 0, 660, 0, 494, 0, 524, 0, 294, 0, 330, 0, 370, 0, 392, 0, 440, 0, 467, 0, 494, 0, 494, 0, 494, 0, 494, 0, 494, 0, 392, 0, 660, 0, 623, 0, 660, 0, 392, 0, 440, 0, 494, 0, 524, 0, 588, 0, 660, 0, 623, 0, 699, 0, 660, 0, 392, 0, 588, 0, 555, 0, 588, 0, 392, 0, 440, 0, 494, 0, 524, 0, 555, 0, 588, 0, 392, 0, 699, 0, 660, 0, 392, 0, 784, 0, 784, 0, 784, 0, 784, 0, 880, 0, 784, 0, 699, 0, 699, 0, 699, 0, 699, 0, 784, 0, 699, 0, 660, 0, 440, 0, 494, 0, 699, 0, 660, 0, 660, 0, 660, 0, 494, 0, 524, 0};
  static u32 au32DurationRight[] = {0, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 182, 91, 182, 91, 543, 139, 134, 3, 815, 3, 815, 3, 815, 139, 134, 3, 134, 3, 134, 3, 134, 3, 134, 3, 815, 3, 543, 3, 270, 3, 815, 685, 134, 3, 815, 3, 815, 3, 815, 139, 134, 3, 134, 3, 134, 3, 134, 3, 134, 3, 815, 3, 543, 3, 270, 3, 815, 685, 134, 3, 815, 3, 815, 3, 815, 3, 270, 3, 270, 139, 134, 3, 815, 3, 815, 3, 815, 3, 270, 3, 270, 139, 134, 3, 815, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 406, 3, 134, 3, 815, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 182, 91, 182, 91, 543, 139, 134, 3, 815, 3, 815, 3, 815, 139, 134, 3, 134, 3, 134, 3, 134, 3, 134, 3, 815, 3, 543, 3, 270, 3, 815, 685, 134, 3, 815, 3, 815, 3, 815, 139, 134, 3, 134, 3, 134, 3, 134, 3, 134, 3, 815, 3, 543, 3, 270, 3, 815, 685, 134, 3, 815, 3, 815, 3, 815, 3, 270, 3, 270, 139, 134, 3, 815, 3, 815, 3, 815, 3, 270, 3, 270, 139, 134, 3, 815, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 406, 3, 134, 3, 815};
 
  static u32 au32NotesLeft[] = {0, 294, 0, 278, 0, 262, 0, 247, 0, 262, 0, 278, 0, 294, 0, 294, 0, 294, 0, 330, 0, 350, 0, 392, 0, 370, 0, 392, 0, 392, 0, 370, 0, 440, 0, 392, 0, 350, 0, 330, 0, 350, 0, 350, 0, 247, 0, 440, 0, 392, 0, 660, 0, 588, 0, 555, 0, 588, 0, 555, 0, 524, 0, 262, 0, 350, 0, 392, 0, 494, 0, 494, 0, 494, 0, 494, 0, 350, 0, 330, 0, 294, 0, 278, 0, 262, 0, 247, 0, 262, 0, 278, 0, 294, 0, 294, 0, 294, 0, 330, 0, 350, 0, 392, 0, 370, 0, 392, 0, 392, 0, 370, 0, 440, 0, 392, 0, 350, 0, 330, 0, 350, 0, 350, 0, 247, 0, 440, 0, 392, 0, 660, 0, 588, 0, 555, 0, 588, 0, 555, 0, 524, 0, 262, 0, 350, 0, 392, 0, 494, 0, 494, 0, 494, 0, 494, 0, 350, 0, 330, 0};
  static u32 au32DurationLeft[] = {0, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 270, 3, 270, 3, 543, 276, 815, 3, 815, 3, 815, 821, 815, 3, 543, 3, 270, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 543, 3, 270, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 270, 139, 134, 3, 815, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 270, 3, 270, 3, 543, 276, 815, 3, 815, 3, 815, 821, 815, 3, 543, 3, 270, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 543, 3, 270, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 815, 3, 815, 821, 815, 3, 270, 3, 270, 3, 270, 3, 134, 3, 134, 3, 270, 139, 134, 3, 815};
  
  static u32 u32IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u32 u32CurrentDurationRight = 0;

  static u32 u32IndexLeft = 0;
  static u32 u32LeftTimer = 0;
  static u32 u32CurrentDurationLeft = 0;

  u32 u32CurrentIndex;

  if(IsTimeUp(&u32RightTimer, (u32)u32CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u32CurrentIndex = u32IndexRight;

    u32CurrentDurationRight = au32DurationRight[u32CurrentIndex];
        
    if(u32IndexRight < sizeof(au32NotesRight) / sizeof(u32))
      u32IndexRight++;

    if(au32NotesRight[u32CurrentIndex] != 0)
    {
      PWMAudioSetFrequency(BUZZER1, au32NotesRight[u32CurrentIndex]);
      PWMAudioOn(BUZZER1);
    }
    else
    {
      PWMAudioOff(BUZZER1);
    }
  }

  if(IsTimeUp(&u32LeftTimer, (u32)u32CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u32CurrentIndex = u32IndexLeft;

    u32CurrentDurationLeft = au32DurationLeft[u32CurrentIndex];

    if(u32IndexLeft < sizeof(au32NotesLeft) / sizeof(u32))
      u32IndexLeft++;

    if(au32NotesRight[u32CurrentIndex] != 0)
    {
      PWMAudioSetFrequency(BUZZER2, au32NotesLeft[u32CurrentIndex]);
      PWMAudioOn(BUZZER2);
    }
    else
    {
      PWMAudioOff(BUZZER2);
    }
  }

} // end Jukebox()

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
