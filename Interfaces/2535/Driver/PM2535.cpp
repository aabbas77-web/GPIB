//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#include "PM2535.h"
#include "decl-32.h"
//---------------------------------------------------------------------------
#include <stdio.h>      // sscanf + sprintf
#include <mmSystem.h>   // timeGetTime
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------
TPM2535 PM2535;
//---------------------------------------------------------------------------
int TPM2535::pm2535_err=0; 
int TPM2535::instr_addr=0;
int TPM2535::instr_ID=0;
int TPM2535::TimeOut=T10s;
//---------------------------------------------------------------------------
HINSTANCE TPM2535::Gpib32Lib = NULL;
int *TPM2535::Pibsta = NULL;
int *TPM2535::Piberr = NULL;
long *TPM2535::Pibcntl = NULL;
//---------------------------------------------------------------------------
TPM2535::TPM2535()
{
}
//---------------------------------------------------------------------------
TPM2535::~TPM2535()
{
}
//---------------------------------------------------------------------------
/* = Philips PM2534/2535 Digital Multimeter ================================ */
/*                                                                           */
/*  C under Windows Instrument Driver                                             */
/*  By:  Mazen FAWAZ                                                       */
/*  Originally written in C                                                  */

/* ========================================================================= */
/* = INTERNAL DATA ========================================================= */
/*  cmd is a buffer for GPIB I/O strings  */
static char  cmd[1024];
/* = INSTRUMENT-DEPENDENT COMMAND ARRAYS =================================== */
static char * function[7];
static char * on_off[2];
static char * trig_src[4];

/* ========================================================================= */
/*  Function: Initialize                                                     */
/*  Purpose:  This function opens the instrument, queries the instrument     */
/*            for its ID, and initializes the instrument to a known state.   */
/* ========================================================================= */
int TPM2535::pm2535_init (int addr, int reset_config)
{

    if (pm2535_invalid_integer_range (addr, 0, 30,  -1) != 0)
        return pm2535_err;
    if (pm2535_invalid_integer_range (reset_config, 0, 1,  -3) != 0)
        return pm2535_err;

    if (pm2535_open_instr (addr)!= 0)
        return pm2535_err;

    if (reset_config == 1)  {
        if (pm2535_write_data (instr_ID, "FNC VDC;RNG A;MSP 2;FIL OFF;IST ON;TRG B;DLY OFF;OUT N", 54) != 0)  {
            pm2535_close_instr (instr_ID);
            return pm2535_err;
        }
    }
    else  if (pm2535_write_data (instr_ID, "OUT N", 5) != 0)  {
        pm2535_close_instr (instr_ID);
        return pm2535_err;
    }
    if (pm2535_write_data (instr_ID, "BUR OFF;LIM OFF;SEQ OFF;BLP OFF;SCL OFF;DBM OFF;PRC OFF;ZER OFF", 63) != 0)  {
       pm2535_close_instr (instr_ID);
       return pm2535_err;
    }

    function[0] = "VDC";
    function[1] = "VAC";
    function[2] = "IDC";
    function[3] = "IAC";
    function[4] = "RTW";
    function[5] = "RFW";
    function[6] = "TDC";

    on_off[0] = "OFF";
    on_off[1] = "ON";

    trig_src[0] = "I";
    trig_src[1] = "E";
    trig_src[2] = "B";
    trig_src[3] = "K";

    pm2535_error_check (instr_ID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Function                                                   */
/*  Purpose:  This function selects the function tto be measured.            */
/* ========================================================================= */
int TPM2535::pm2535_set_function (int instrID, int func)
{
    AnsiString Str;
    if (pm2535_device_closed (instrID) !=0)
        return pm2535_err;
    if (pm2535_invalid_integer_range (func, 0, 6,  -2) != 0)
        return pm2535_err;

    sprintf (cmd, "FNC %s", function[func]);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Range                                                      */
/*  Purpose:  This function selects the range.                               */
/* ========================================================================= */
int TPM2535::pm2535_set_range (int instrID, double rng)
{
    AnsiString Str;
    if (pm2535_invalid_real_range (rng, 0.0, 300000000.0,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    if (rng == 0.0)
        sprintf (cmd, "RNG A");
    else
        sprintf (cmd, "RNG %f", rng);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Speed                                                      */
/*  Purpose:  This function selects the measurement speed.                   */
/* ========================================================================= */
int TPM2535::pm2535_set_speed (int instrID, int speed)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (speed, 1, 4,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "MSP %d", speed);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Resolution                                                 */
/*  Purpose:  This function selects the resolution.                          */
/* ========================================================================= */
int TPM2535::pm2535_set_resolution (int instrID, int res)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (res, 4, 7,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "RSL %d", res);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Settling Time                                              */
/*  Purpose:  This function sets settling time to on or off.                 */
/* ========================================================================= */
int TPM2535::pm2535_set_settling_time (int instrID, int set)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (set, 0, 1,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "IST %s", on_off[set]);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Filter                                                     */
/*  Purpose:  This function sets the filter to on or off.                    */
/*  details: Sets the filter mode.
                  If the multimeter is in DC or Ohms mode and the filter
                  is on then measurements are calculated as follows:
                  display result = 0.8 * prev_result + 0.2 * actual_meas

                  If the multimeter is in AC mode and the filter is
                  switched on then a 40Hz low pass filter is turned on. */

/* ========================================================================= */
int TPM2535::pm2535_set_filter (int instrID, int filter)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (filter, 0, 1,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "FIL %s", on_off[filter]);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Trigger Source                                                 */
/*  Purpose:  This function sets the trigger source.                         */
/* ========================================================================= */
int TPM2535::pm2535_set_trig_source (int instrID, int src)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (src, 0, 3,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "TRG %s", trig_src[src]);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Trigger Delay                                                  */
/*  Purpose:  This function sets the trigger delay.                          */
/* ========================================================================= */
int TPM2535::pm2535_set_trig_delay (int instrID, int mod, double del)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (mod, 0, 1,  -2) != 0)
        return pm2535_err;
    if (pm2535_invalid_real_range (del, 0.0, 8000.0,  -3) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "DLY %s,%d", on_off[mod], (int)(del * 1000.0));
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Measure                                                        */
/*  Purpose:  This function triggers the multimeter and reads the            */
/*            measurement taken.                                             */
/* ========================================================================= */
int TPM2535::pm2535_measure (int instrID, float &measurement)
{
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    /*  Call Trigger Function  */
    if (pm2535_trig (instrID) != 0)
        return pm2535_err;
    /*  Call Read Result Function  */
    Sleep(1000);
    if (pm2535_read_result (instrID, measurement) != 0)
        return pm2535_err;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Read Result                                                    */
/*  Purpose:  This function reads the last result from the multimeter.       */
/* ========================================================================= */
int TPM2535::pm2535_read_result (int instrID, float &result)
{
    char status;
    int done;
    DWORD t;
    float r;
//    AnsiString Str;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    done = 0;
    t = timeGetTime ();
    while (!done)  {
        if (pm2535_poll (instrID, &status) != 0)
            return pm2535_err;
        if ((status & 17) == 17)  {
            if (pm2535_read_data (instrID, cmd, 100) != 0)
                return pm2535_err;
            if (pm2535_write_data (instrID, " ", 1) != 0)
                return pm2535_err;
            if (sscanf (cmd, "%f", &r) != 1)  {
                pm2535_err = 236;
                return pm2535_err;
            }
            result= r;

            if ((status & 32 + 4) == 32 + 4)  {
                pm2535_err = 301;
                return pm2535_err;
            }
            return pm2535_err;
        }
        else
            /*  Incorrect Measurement  */
            if ((status & 32 + 4) == 32 + 4)  {
                pm2535_err = 301;
                return pm2535_err;
            }
////////TimeOut must has the correct value////////////////////
        if (timeGetTime () - t > TimeOut*1000.0)  {
            pm2535_err = 302;
            done = 1;
        }
    }
//    result= &r;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Get Min / Max                                                  */
/*  Purpose:  This function reads the max and min measurements.              */
/* ========================================================================= */
int TPM2535::pm2535_get_min_max (int instrID, float &min, float &max)
{
    float n,x;

    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    /*  Read Minimum  */
    if (pm2535_write_data (instrID, "MIN", 3) != 0)
        return pm2535_err;
    if (pm2535_error_check (instrID) != 0)
        return pm2535_err;
    if (pm2535_read_data (instrID, cmd, 100) != 0)
        return pm2535_err;
    if (pm2535_write_data (instrID, " ", 1) != 0)
        return pm2535_err;
    if (sscanf (cmd, "MIN,%f", &n) != 1)  {
        pm2535_err = 236;
        return pm2535_err;
    }
    min = n;
    /*  Read Maximum  */
    if (pm2535_write_data (instrID, "MAX", 3) != 0)
        return pm2535_err;
    if (pm2535_error_check (instrID) != 0)
        return pm2535_err;
    if (pm2535_read_data (instrID, cmd, 100) != 0)
        return pm2535_err;
    if (pm2535_write_data (instrID, " ", 1) != 0)
        return pm2535_err;
    if (sscanf (cmd, "MAX,%f", &x) != 1)  {
        pm2535_err = 236;
        return pm2535_err;
    }
    max = x;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Trigger                                                        */
/*  Purpose:  This function sends a trigger to the instrument using ibtrg.   */
/* ========================================================================= */
int TPM2535::pm2535_trig (int instrID)
{
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    if (ibtrg (instrID) & 0x8000)  {
        pm2535_err = 225;
        return pm2535_err;
    }
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Reset Min/Max                                                  */
/*  Purpose:  This function resets the min and max registers.                */
/* ========================================================================= */
int TPM2535::pm2535_reset_min_max (int instrID)
{
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    if (pm2535_write_data (instrID, "CLM", 3) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Store Settings                                                 */
/*  Purpose:  This function stores the current settings in one of the        */
/*            instruments program storage positions.                         */
/* ========================================================================= */
int TPM2535::pm2535_store_settings (int instrID, int pos)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (pos, 0, 9,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "STO %d", pos);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Recall Settings                                                */
/*  Purpose:  This function recalls the settings from one of the             */
/*            instruments program storage positions.                         */
/* ========================================================================= */
int TPM2535::pm2535_recall_settings (int instrID, int pos)
{
    AnsiString Str;
    if (pm2535_invalid_integer_range (pos, 0, 9,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    sprintf (cmd, "RCL %d", pos);
    Str=cmd;
    if (pm2535_write_data (instrID, cmd, Str.Length ()) != 0)
        return pm2535_err;
    pm2535_error_check (instrID);
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Timeout                                                    */
/*  Purpose:  This function sets the GPIB timout limit.                      */
/* ========================================================================= */
int TPM2535::pm2535_set_timeout (int instrID, int tmo_val)
{
    if (pm2535_invalid_real_range (tmo_val, 1, 17,  -2) != 0)
        return pm2535_err;
    if (pm2535_device_closed (instrID) != 0)
        return pm2535_err;
    TimeOut = tmo_val;
    return pm2535_err;
}


/* = UTILITY ROUTINES ====================================================== */
/* ========================================================================= */
/*  Function: Open Instrument                                                */
/*  Purpose:  This function locates and initializes an entry in the          */
/*            Instrument Table and the GPIB device table for the             */
/*            instrument.  If successful, the instrument ID is returned,     */
/*            else a -1 is returned.  The size of the Instrument Table can   */
/*            be changed in the include file by altering the constant        */
/*            pm2535_MAX_INSTR.                                              */
/* ========================================================================= */
int TPM2535::pm2535_open_instr (int addr)
{
    pm2535_err = 0;

/* If the device has not been opened in the GPIB device table (bd[ID] = 0),*/
/*  then open it.                                                          */

    if (instr_ID <= 0) {
        instr_ID = ibdev(0, addr, 0, TimeOut, 1, 0);
        if (instr_ID <= 0) {
            pm2535_err = 220;
            return pm2535_err;
        }
     }

/*  Change the primary address of the device    */

    if (ibpad (instr_ID, addr) & 0x8000) {
        pm2535_err = 233;
        return pm2535_err;
    }

    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Close Instrument                                               */
/*  Purpose:  This function closes the instrument by removing it from the    */
/*            GPIB device table and setting the address and the bd to zero   */
/*            in the Instrument Table.  The return value is equal to the     */
/*            global error variable.                                         */
/* ========================================================================= */
int TPM2535::pm2535_close_instr (int instrID)
{
      if (instrID !=0){
  /*  Call the ibonl function to disable the hardware and software.           */
           ibonl(instrID, 0);
           instr_ID = 0;
           instr_addr = 0;
           pm2535_err = 0;
      }
      else
        pm2535_err = 221;
      return pm2535_err;
}

/* ========================================================================= */
/*  Function: Invalid Real Range                                             */
/*  Purpose:  This function checks a real number to see if it lies between   */
/*            a minimum and maximum value.  If the value is out of range,    */
/*            set the global error variable to the value err_code.  If the   */
/*            value is OK, error = 0.                                        */
/* ========================================================================= */
int TPM2535::pm2535_invalid_real_range (double val, double min, double max, int err_code)
{

    if (val < min || val > max)  {
        pm2535_err = err_code;
        return  pm2535_err;
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
int TPM2535::pm2535_invalid_integer_range (int val, int min, int max, int err_code)
{

    if (val < min || val > max)  {
        pm2535_err = err_code;
        return  pm2535_err;
    }
    return 0;
}

/* ========================================================================= */
/*  Function: Device Closed                                                  */
/*  Purpose:  This function checks to see if the module has been             */
/*            initialized.  If the device has not been opened, a 1 is        */
/*            returned, 0 otherwise.                                         */
/* ========================================================================= */
int TPM2535::pm2535_device_closed (int instrID)
{

    if (instrID <= 0)  {
        pm2535_err = 232;
        return  pm2535_err;
    }
    return 0;
}

/* ========================================================================= */
/*  Function: Read Data                                                      */
/*  Purpose:  This function reads a buffer of data from the instrument. The  */
/*            return value is equal to the global error variable.            */
/* ========================================================================= */
int TPM2535::pm2535_read_data (int instrID, char *buf, int cnt)
{
    if (pm2535_device_closed(instrID) != 0)
        return pm2535_err;

    if (ibrd (instrID, buf, (long)cnt) & 0x8000)
        pm2535_err = 231;
    else
        pm2535_err = 0;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Write Data                                                     */
/*  Purpose:  This function writes a buffer of data to the instrument. The   */
/*            return value is equal to the global error variable.            */
/* ========================================================================= */
int TPM2535::pm2535_write_data (int instrID, char *buf, int cnt)
{
    if (pm2535_device_closed(instrID) != 0)
        return pm2535_err;

    if (ibwrt (instrID, buf, (long)cnt) & 0x8000)
        pm2535_err = 230;
    else
        pm2535_err = 0;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Serial Poll                                                    */
/*  Purpose:  This function performs a serial poll on the instrument.        */
/*            The status byte of the instrument is placed in the response    */
/*            variable. The return value is equal to the global error        */
/*            variable.                                                      */
/* ========================================================================= */
int TPM2535::pm2535_poll (int instrID, char *response)
{

    if (ibrsp (instrID, response) & 0x8000)
        pm2535_err = 226;
    else
        pm2535_err = 0;
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Set Timeout                                                    */
/*  Purpose:  This function changes or disables the timeout of the device.   */
/*            Refer to the LabWindows Standard Libraries Reference Manual    */
/*            for timeout codes.                                             */
/* ========================================================================= */
int TPM2535::pm2535_set_tmo (int instrID, int tmo_code, int *old_timeout)
{

    if (ibtmo (instrID, tmo_code) & 0x8000)
        pm2535_err = 239;
    else {
          *old_timeout = iberr;
          pm2535_err = 0;
    }
    return pm2535_err;
}

/* ========================================================================= */
/*  Function: Error Check                                                    */
/*  Purpose:  This function checks the instrument status byte to see if a    */
/*            programming error has occured.                                 */
/* ========================================================================= */
int TPM2535::pm2535_error_check (int instrID)
{
    char status;
    int i;
    int err_code;

    pm2535_err = 0;
    for (i = 0; i < 10; i++)  {
        if (pm2535_poll (instrID, &status) != 0)  {
            pm2535_err = 226;
            return pm2535_err;
        }
        if ((status & 32 + 1) == 32 + 1)  {
            pm2535_err = 300;
            return pm2535_err;
        }
        if ((status & 32 + 4) == 32 + 4)  {
            pm2535_err = 301;
            return pm2535_err;
        }
    }
    return pm2535_err;
}
/*=========================================================================*/
void TPM2535::gpiberr(char *msg) {
    AnsiString e;
    sprintf(e.c_str(),"%s\n The PM2535_Error=%d",msg,pm2535_err);
    MessageDlg(e.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
    ibonl(0, 0); /* Disable hardware and software */
}
/*=========================================================================*/

