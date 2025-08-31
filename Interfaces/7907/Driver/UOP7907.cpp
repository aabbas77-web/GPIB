//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#include "UOP7907.h"
#include "decl-32.h"
//---------------------------------------------------------------------------
#include <stdio.h>      // sscanf + sprintf
#include <mmSystem.h>   // timeGetTime
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------
TUOP7907 UOP7907;
//---------------------------------------------------------------------------
int TUOP7907::uop7907_err=0;
int TUOP7907::instr_addr=0;
int TUOP7907::instr_ID=0;
int TUOP7907::TimeOut=T10s;
//---------------------------------------------------------------------------
HINSTANCE TUOP7907::Gpib32Lib = NULL;
int *TUOP7907::Pibsta = NULL;
int *TUOP7907::Piberr = NULL;
long *TUOP7907::Pibcntl = NULL;
//---------------------------------------------------------------------------
TUOP7907::TUOP7907()
{
}
//---------------------------------------------------------------------------
TUOP7907::~TUOP7907()
{
}
//---------------------------------------------------------------------------
/* ====== Unipolar Operational Power Supply ================================ */
/*                                                                           */
/*  C under Windows Instrument Driver                                        */
/*  By:  Mazen FAWAZ                                                         */
/*  Originally written in C                                                  */

/* ========================================================================= */
/* = INTERNAL DATA ========================================================= */
/*  cmd is a buffer for GPIB I/O strings  */
static char  cmd[256];
/* = INSTRUMENT-DEPENDENT COMMAND ARRAYS =================================== */
static char *resulation[3];
static char *trigger[2];
static char *force[2];
static char *input[2];

/* ========================================================================= */
/*  Function: Initialize                                                     */
/*  Purpose:  This function opens the instrument, queries the instrument     */
/*            for its ID, and initializes the instrument to a known state.   */
/* ========================================================================= */
int TUOP7907::uop7907_init (int addr, int reset_config)
{

    if (uop7907_invalid_integer_range (addr, 0, 30,  -1) != 0)
        return uop7907_err;
    if (uop7907_invalid_integer_range (reset_config, 0, 1,  -2) != 0)
        return uop7907_err;

    if (uop7907_open_instr (addr)!= 0)
        return uop7907_err;

    if (reset_config == 1)  {
        if (uop7907_write_data (instr_ID, "K0;I0;U0;R0;S0;A0;T0;Q0\r\n", 25) != 0){
            uop7907_close_instr (instr_ID);
            return uop7907_err;
        }
    }
    else
        if (uop7907_write_data (instr_ID, "K0;I0;U0;R0;S0;A0;T1;Q0\r\n", 25) != 0){
            uop7907_close_instr (instr_ID);
            return uop7907_err;
        }

    resulation[0]= "R0";
    resulation[1]= "R1";
    resulation[2]= "R2";

    trigger[0]   = "T0";
    trigger[1]   = "T1";

    force[0]     = "S0";
    force[1]     = "S1";

    input[0]     = "A0";
    input[1]     = "A1";

//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Voltage Resulation                                         */
/*  Purpose:  This function selects the voltage resulation.                  */
/* ========================================================================= */
int TUOP7907::uop7907_set_voltage_resulation (int ID, int res)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_integer_range (res, 0, 2,  -3) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;%s\r\n", resulation[res]);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Trigger Mode                                               */
/*  Purpose:  This function selects the trigger mode.                        */
/* ========================================================================= */
int TUOP7907::uop7907_set_trigger_mode (int ID, int trig_mode)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_integer_range (trig_mode, 0, 1, -4) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;%s\r\n", trigger[trig_mode]);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Force Mode                                                 */
/*  Purpose:  This function selects the force mode.                          */
/* ========================================================================= */
int TUOP7907::uop7907_set_force_mode (int ID, int force_mode)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_integer_range (force_mode, 0, 1, -5) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;%s\r\n", force[force_mode]);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Trigger Mode                                               */
/*  Purpose:  This function selects the trigger mode.                        */
/* ========================================================================= */
int TUOP7907::uop7907_set_analog_input_mode (int ID, int input_mode)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_integer_range (input_mode, 0, 1, -5) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;%s\r\n", input[input_mode]);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Voltage Value                                              */
/*  Purpose:  This function selects the Voltage Value.                       */
/* ========================================================================= */
int TUOP7907::uop7907_set_voltage_value (int ID, float value)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_real_range (value, 0.0, 50.0, -6) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;U%f\r\n", value);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Current Value                                              */
/*  Purpose:  This function selects the Current Value.                       */
/* ========================================================================= */
int TUOP7907::uop7907_set_current_value (int ID, float value)
{
    AnsiString Str;
    if (uop7907_device_closed (ID) !=0)
        return uop7907_err;
    if (uop7907_invalid_real_range (value, 0.0, 5.0, -7) != 0)
        return uop7907_err;

    sprintf (cmd, "K0;I%f\r\n", value);
    Str=cmd;
    if (uop7907_write_data (ID, cmd, Str.Length ()) != 0)
        return uop7907_err;
//    uop7907_error_check (instrID);
    return uop7907_err;
}


/* ========================================================================= */
/*  Function: Trigger                                                        */
/*  Purpose:  This function sends a trigger to the instrument using ibtrg.   */
/* ========================================================================= */
int TUOP7907::uop7907_trig (int instrID)
{
    if (uop7907_device_closed (instrID) != 0)
        return uop7907_err;
    if (ibtrg (instrID) & 0x8000)  {
        uop7907_err = 225;
        return uop7907_err;
    }
//    uop7907_error_check (instrID);
    return uop7907_err;
}
/* ========================================================================= */
/*  Function: Set Timeout                                                    */
/*  Purpose:  This function sets the GPIB timout limit.                      */
/* ========================================================================= */
int TUOP7907::uop7907_set_timeout (int instrID, int tmo_val)
{
    if (uop7907_invalid_real_range (tmo_val, 1, 17,  -2) != 0)
        return uop7907_err;
    if (uop7907_device_closed (instrID) != 0)
        return uop7907_err;
    TimeOut = tmo_val;
    return uop7907_err;
}


/* = UTILITY ROUTINES ====================================================== */
/* ========================================================================= */
/*  Function: Open Instrument                                                */
/*  Purpose:  This function locates and initializes an entry in the          */
/*            Instrument Table and the GPIB device table for the             */
/*            instrument.  If successful, the instrument ID is returned,     */
/*            else a -1 is returned.  The size of the Instrument Table can   */
/*            be changed in the include file by altering the constant        */
/*            uop7907_MAX_INSTR.                                              */
/* ========================================================================= */
int TUOP7907::uop7907_open_instr (int addr)
{
    uop7907_err = 0;

/* If the device has not been opened in the GPIB device table (bd[ID] = 0),*/
/*  then open it.                                                          */

    if (instr_ID <= 0) {
        instr_ID = ibdev(0, addr, 0, TimeOut, 1, 0);
        if (instr_ID <= 0) {
            uop7907_err = 220;
            return uop7907_err;
        }
     }

/*  Change the primary address of the device    */

    if (ibpad (instr_ID, addr) & 0x8000) {
        uop7907_err = 233;
        return uop7907_err;
    }

    return uop7907_err;
}

/* ========================================================================= */
/*  Function: Close Instrument                                               */
/*  Purpose:  This function closes the instrument by removing it from the    */
/*            GPIB device table and setting the address and the bd to zero   */
/*            in the Instrument Table.  The return value is equal to the     */
/*            global error variable.                                         */
/* ========================================================================= */
int TUOP7907::uop7907_close_instr (int instrID)
{
      if (instrID !=0){
  /*  Call the ibonl function to disable the hardware and software.           */
           ibonl(instrID, 0);
           instr_ID = 0;
           instr_addr = 0;
           uop7907_err = 0;
      }
      else
        uop7907_err = 221;
      return uop7907_err;
}

/* ========================================================================= */
/*  Function: Invalid Real Range                                             */
/*  Purpose:  This function checks a real number to see if it lies between   */
/*            a minimum and maximum value.  If the value is out of range,    */
/*            set the global error variable to the value err_code.  If the   */
/*            value is OK, error = 0.                                        */
/* ========================================================================= */
int TUOP7907::uop7907_invalid_real_range (double val, double min, double max, int err_code)
{
    if (val < min || val > max)  {
        uop7907_err = err_code;
        return  uop7907_err;
    }
    return 0;
}

/* ========================================================================= */
/*  Function: Invalid Integer Range                                          */
/*  Purpose:  This function checks an integer to see if it lies between a    */
/*            minimum and maximum value.  If the value is out of range, set  */
/*            the global error variable to the value err_code.  If the       */
/*            value is OK, error = 0.                                        */
/* ========================================================================= */
int TUOP7907::uop7907_invalid_integer_range (int val, int min, int max, int err_code)
{
    if (val < min || val > max)  {
        uop7907_err = err_code;
        return  uop7907_err;
    }
    return 0;
}

/* ========================================================================= */
/*  Function: Device Closed                                                  */
/*  Purpose:  This function checks to see if the module has been             */
/*            initialized.  If the device has not been opened, a 1 is        */
/*            returned, 0 otherwise.                                         */
/* ========================================================================= */
int TUOP7907::uop7907_device_closed (int instrID)
{
    if (instrID <= 0)  {
        uop7907_err = 232;
        return  uop7907_err;
    }
    return 0;
}

/* ========================================================================= */
/*  Function: Read Data                                                      */
/*  Purpose:  This function reads a buffer of data from the instrument. The  */
/*            return value is equal to the global error variable.            */
/* ========================================================================= */
int TUOP7907::uop7907_read_data (int instrID, char *buf, int cnt)
{
    if (uop7907_device_closed(instrID) != 0)
        return uop7907_err;

    if (ibrd (instrID, buf, (long)cnt) & 0x8000)
        uop7907_err = 231;
    else
        uop7907_err = 0;
    return uop7907_err;
}

/* ========================================================================= */
/*  Function: Write Data                                                     */
/*  Purpose:  This function writes a buffer of data to the instrument. The   */
/*            return value is equal to the global error variable.            */
/* ========================================================================= */
int TUOP7907::uop7907_write_data (int instrID, char *buf, int cnt)
{
    if (uop7907_device_closed(instrID) != 0)
        return uop7907_err;

    if (ibwrt (instrID, buf, (long)cnt) & 0x8000)
        uop7907_err = 230;
    else
        uop7907_err = 0;
    return uop7907_err;
}

/* ========================================================================= */
/*  Function: Serial Poll                                                    */
/*  Purpose:  This function performs a serial poll on the instrument.        */
/*            The status byte of the instrument is placed in the response    */
/*            variable. The return value is equal to the global error        */
/*            variable.                                                      */
/* ========================================================================= */
int TUOP7907::uop7907_poll (int instrID, char *response)
{

    if (ibrsp (instrID, response) & 0x8000)
        uop7907_err = 226;
    else
        uop7907_err = 0;
    return uop7907_err;
}

/* ========================================================================= */
/*  Function: Set Timeout                                                    */
/*  Purpose:  This function changes or disables the timeout of the device.   */
/*            Refer to the LabWindows Standard Libraries Reference Manual    */
/*            for timeout codes.                                             */
/* ========================================================================= */
int TUOP7907::uop7907_set_tmo (int instrID, int tmo_code, int *old_timeout)
{
    if (ibtmo (instrID, tmo_code) & 0x8000)
        uop7907_err = 239;
    else {
          *old_timeout = iberr;
          uop7907_err = 0;
    }
    return uop7907_err;
}

/* ========================================================================= */
/*  Function: Error Check                                                    */
/*  Purpose:  This function checks the instrument status byte to see if a    */
/*            programming error has occured.                                 */
/* ========================================================================= */

int TUOP7907::uop7907_error_check (int instrID)
{
    char status;
    int i;
    int err_code;

    uop7907_err = 0;
    for (i = 0; i < 10; i++)  {
        if (uop7907_poll (instrID, &status) != 0)  {
            uop7907_err = 226;
            return uop7907_err;
        }
        if ((status & 32 + 1) == 32 + 1)  {
            uop7907_err = 300;
            return uop7907_err;
        }
        if ((status & 32 + 4) == 32 + 4)  {
            uop7907_err = 301;
            return uop7907_err;
        }
    }
    return uop7907_err;
}
/*=========================================================================*/
void TUOP7907::uop7907_gpiberr(char *msg) {
    AnsiString e;
    sprintf(e.c_str(),"%s\n The UOP7907_Error=%d",msg,uop7907_err);
    MessageDlg(e.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
    ibonl(0, 0); /* Disable hardware and software */
    Application->Terminate();        
}
/*=========================================================================*/

