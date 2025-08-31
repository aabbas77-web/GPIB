//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
//---------------------------------------------------------------------------
#include "PM3000.h"
#include "decl-32.h"
//---------------------------------------------------------------------------
#include <stdio.h>      // sscanf + sprintf
#include <mmSystem.h>   // timeGetTime
#include <Math.h>      // pow
//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------
TPM3000 PM3000;
//---------------------------------------------------------------------------
int TPM3000::pm3000_err=0;
int TPM3000::instr_addr=0;
int TPM3000::instr_ID=0;
int TPM3000::instr_TimeOut=T10s;
//---------------------------------------------------------------------------
TPM3000::TPM3000()
{
}
//---------------------------------------------------------------------------
TPM3000::~TPM3000()
{
}
//---------------------------------------------------------------------------
/*****************************************************************************/
/*= Voltech PM 3000A Universal Power Analyzer ===============================*/
/*  C under Windows Instrument Driver                                             */
/*  By:  Mazen FAWAZ                                                       */
/*  Originally written in C                                                  */


/*= STATIC VARIABLES ======================================================*/
/* cmd: a buffer for GPIB I/O strings.                                     */
/* pm3000_err: the error variable for the instrument module              */
/* instr_addr: the GPIB address of the instrument                          */
/* ibcnt: contains the number of bytes transferred by GPIB reads and       */
/*        writes.  See the GPIB library I/O Class for more information     */
/*=========================================================================*/
static char cmd[1024];
//static int pm3000_err; //must link to Messages error
//static int instr_addr;  //init only
//static int instr_ID;    //open & others

/*= INSTRUMENT-DEPENDENT COMMAND ARRAYS ===================================*/
static char *Freq_Source[4];
static char *Vlt_Amp[2];
static char *Coupling[2];
static char *Int_Ext[2];
static char *Ranging[13];
static char *Wiring[8];
static char *Action[2];
static char *Harmonic[2];
static char *IEC_Mode[4];
static char *Channel[7];
static char *Func_List[27];
static char *Select_List[22];
static char *Fund_List[18];
static char *Log_Mode[3];
static char *Ballast[3];

/*=========================================================================*/

/*= UTILITY ROUTINES ======================================================*/
//move to the header file
/*=========================================================================*/
/* Function: Initialize                                                    */
/* Purpose:  This function opens the instrument, queries the instrument    */
/*           for its ID, and initializes the instrument to a known state.  */
/*=========================================================================*/
int TPM3000::pm3000_init (int addr, int rest)
{

    if (pm3000_invalid_integer_range (addr, 0, 30, -1) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (rest, 0, 1, -3) != 0)
        return pm3000_err;
    instr_ID=0;
// init the variable instr_ID
    if (pm3000_open_instr (addr) != 0)
        return pm3000_err;

/* Assign instr_addr the GPIB address of the instrument */
    instr_addr = addr;

    if (rest) {
        if (pm3000_write_data (instr_ID, "*CLS;*RST\n", 10) != 0) {
            pm3000_close_instr (instr_ID);
            return pm3000_err;
        }
    }

 /* Enable the IEEE488.2 mode */
    if (pm3000_write_data (instr_ID, ":CFG 123,1\n", 11) != 0) {
        pm3000_close_instr (instr_ID);
        return pm3000_err;
    }

    Freq_Source[0] = "VLT";
    Freq_Source[1] = "AMP";
    Freq_Source[2] = "EXT";
    Freq_Source[3] = "SLW";

    Vlt_Amp[0] = "MEA";
    Vlt_Amp[1] = "TRU";

    Coupling[0] = "-DC";
    Coupling[1] = "+DC";

    Int_Ext[0] = "EXT";
    Int_Ext[1] = "INT";

    Ranging[0] = "AUT";
    Ranging[1] = "FIX 1";
    Ranging[2] = "FIX 2";
    Ranging[3] = "FIX 3";
    Ranging[4] = "FIX 4";
    Ranging[5] = "FIX 5";
    Ranging[6] = "FIX 6";
    Ranging[7] = "FIX 7";
    Ranging[8] = "FIX 8";
    Ranging[9] = "FIX 9";
    Ranging[10] = "FIX 10";
    Ranging[11] = "FIX 11";
    Ranging[12] = "FIX 12";

    Wiring[0] = "1P2";
    Wiring[1] = "1P3";
    Wiring[2] = "3P3";
    Wiring[3] = "3P4";
    Wiring[4] = "CH2";
    Wiring[5] = "CH3";
    Wiring[6] = "MIX";
    Wiring[7] = "ALL";

    Action[0] = "DIS";
    Action[1] = "ENB";

    Harmonic[0] = "ODD";
    Harmonic[1] = "ALL";

    IEC_Mode[1] = "FIX";
    IEC_Mode[2] = "FLU";
    IEC_Mode[3] = "FLI";

    Channel[0] = "ALL";
    Channel[1] = "CH1";
    Channel[2] = "CH2";
    Channel[3] = "CH3";
    Channel[4] = "SUM";
    Channel[5] = "CHN";
    Channel[6] = "AUX";

    Func_List[0] = "WAT";
    Func_List[1] = "VAS";
    Func_List[2] = "VAR";
    Func_List[3] = "VLT";
    Func_List[4] = "AMP";
    Func_List[5] = "PWF";
    Func_List[6] = "VPK";
    Func_List[7] = "APK";
    Func_List[8] = "VCF";
    Func_List[9] = "ACF";
    Func_List[10] = "IMP";
    Func_List[11] = "VDF";
    Func_List[12] = "ADF";
    Func_List[13] = "FRQ";
    Func_List[14] = "VHM";
    Func_List[15] = "AHM";
    Func_List[16] = "VHA";
    Func_List[17] = "AHA";
    Func_List[18] = "EFF";
    Func_List[19] = "WHR";
    Func_List[20] = "VAH";
    Func_List[21] = "VRH";
    Func_List[22] = "AHR";
    Func_List[23] = "APF";
    Func_List[24] = "TIM";
    Func_List[25] = "VDC";
    Func_List[26] = "ADC";

    Select_List[0] = "CH1";
    Select_List[1] = "CH2";
    Select_List[2] = "CH3";
    Select_List[3] = "SUM";
    Select_List[4] = "CHN";
    Select_List[5] = "FUN";
    Select_List[6] = "WAT";
    Select_List[7] = "VAS";
    Select_List[8] = "VAR";
    Select_List[9] = "VLT";
    Select_List[10] = "AMP";
    Select_List[11] = "PWF";
    Select_List[12] = "VPK";
    Select_List[13] = "APK";
    Select_List[14] = "VCF";
    Select_List[15] = "ACF";
    Select_List[16] = "IMP";
    Select_List[17] = "VDF";
    Select_List[18] = "ADF";
    Select_List[19] = "FRQ";
    Select_List[20] = "VHM";
    Select_List[21] = "AHM";

    Fund_List[0] = "WAT";
    Fund_List[1] = "VAS";
    Fund_List[2] = "VAR";
    Fund_List[3] = "VLT";
    Fund_List[4] = "AMP";
    Fund_List[5] = "PWF";
    Fund_List[6] = "IMP";
    Fund_List[7] = "VHM";
    Fund_List[8] = "AHM";
    Fund_List[9] = "VHA";
    Fund_List[10] = "AHA";
    Fund_List[11] = "EFF";
    Fund_List[12] = "WHR";
    Fund_List[13] = "VAH";
    Fund_List[14] = "VRH";
    Fund_List[15] = "AHR";
    Fund_List[16] = "APF";
    Fund_List[17] = "CVR";

    Log_Mode[0] = "DIS";
    Log_Mode[1] = "TRG";
    Log_Mode[2] = "EXT";

    Ballast[0] = "DIS";
    Ballast[1] = "50H";
    Ballast[2] = "60H";


    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Operation                                           */
/* Purpose:  This function configures the frequency reference, phase       */
/*           reference, shunt, coupling, and averaging of the instrument.  */
/*=========================================================================*/
int TPM3000::pm3000_conf_operation (int instrID, int source, int ref, int meas,
                             int aver, int depth, int cpl, int shunt )
{
    AnsiString Str;
    if (pm3000_device_closed (instrID) !=0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (source, 0, 3, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (ref, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (meas, 0, 1, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (aver, 0, 1, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (depth, 1, 64, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (cpl, 0, 1, -7) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (shunt, 0, 1, -8) != 0)
        return pm3000_err;

    if (source == 0) {
        if (aver == 0)
            sprintf (cmd, ":FSR:%s;:AVG:FIX %d;:CPL:%s;:SHU:%s;:RMS:%s\n",
                 Freq_Source[source], depth, Coupling[cpl],
                 Int_Ext[shunt], Vlt_Amp[meas]);
        else
            sprintf (cmd, ":FSR:%s;A00;:CPL:%s;:SHU:%s;:RMS:%s\n",
                 Freq_Source[source], Coupling[cpl], Int_Ext[shunt],
                 Vlt_Amp[meas]);
    }
    else {
        if (aver == 0)
            sprintf (cmd, ":FSR:%s;:CFG 34,%d;:AVG:FIX %d;:CPL:%s;:SHU:%s;:RMS:%s\n",
                 Freq_Source[source], ref, depth, Coupling[cpl],
                 Int_Ext[shunt], Vlt_Amp[meas]);
        else
            sprintf (cmd, ":FSR:%s;:CFG 34,%d;A00;:CPL:%s;:SHU:%s;:RMS:%s\n",
                 Freq_Source[source], ref, Coupling[cpl], Int_Ext[shunt],
                 Vlt_Amp[meas]);
    }
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure Range Settings                                      */
/* Purpose:  This function configures the voltage and current range        */
/*           settings for the instrument.                                  */
/*=========================================================================*/
int TPM3000::pm3000_conf_range_set (int instrID, int r_mode, int chan, int v_range,
                             int c_range)
{
    int count;
    AnsiString Str;

    if (pm3000_invalid_integer_range (r_mode, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 1, 3, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (v_range, 0, 12, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (c_range, 0, 12, -5) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Count contains bytes in command to be written */
    count = 0;

 /* Put in independent mode and set the ranges for the specified channel */
    if (r_mode == 1) {
        sprintf (cmd, ":CFG 28,1");
        Str=cmd;
        count += Str.Length ();
        if (v_range == 0)
            sprintf (cmd, ":CFG %d,0\n", 22+20*chan);
        else
            sprintf (cmd, ":CFG %d,1;:CFG %d,%d\n", 22+20*chan, 20+20*chan,
                 v_range-1);
        Str=cmd;
        count += Str.Length ();
        if (c_range == 0)
            sprintf (cmd, ":CFG %d,0\n", 23+20*chan);
        else
            sprintf (cmd, ":CFG %d,1;:CFG %d,%d\n", 23+20*chan, 21+20*chan,
                 c_range-1);
        Str=cmd;
        count += Str.Length ();
        if (pm3000_write_data (instrID, cmd, count) != 0)
            return pm3000_err;
    }

 /* Put into locked mode and set ranges for all channels */
    else {
        sprintf (cmd, ":CFG 28,0;:RNG:VLT:%s;:RNG:AMP:%s\n", Ranging[v_range],
             Ranging[c_range]);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;
    }

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure Scaling Factors                                     */
/* Purpose:  This function configures the current and voltage scaling      */
/*           factors for the instrument.                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_scaling_factors (int instrID, double v_scale, double c_scale)
{
    AnsiString Str;
    if (pm3000_invalid_real_range (v_scale, -1e5, 1e5, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (c_scale, -1e5, 1e5, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":SCL:VLT %f;:SCL:AMP %f\n", v_scale, c_scale);
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Wiring                                              */
/* Purpose:  This function configures the wiring configuration for the     */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_wiring (int instrID, int config, int ppv)
{
    AnsiString Str;
    if (pm3000_invalid_integer_range (config, 0, 7, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (ppv, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if ((config == 3)) {
        if (ppv == 1) {
            if (pm3000_write_data (instrID, ":WRG:3P4;:WRG:PHP\n", 18) != 0)
                return pm3000_err;
        }
        else {
            if (pm3000_write_data (instrID, ":WRG:3P3;:WRG:3P4\n", 18) != 0)
                return pm3000_err;
        }
    }
    else {
        sprintf (cmd, ":WRG:%s\n", Wiring[config]);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Summation Formulas                                  */
/* Purpose:  This function configures the summation formulas for the       */
/*           summation channel of the instrument.                          */
/*=========================================================================*/
int TPM3000::pm3000_conf_sum_formulas (int instrID, int ampform, int voltform)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (ampform, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (voltform, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 191,%d;:CFG 192,%d\n", ampform, voltform);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Sampling                                            */
/* Purpose:  This function configures the sampling rate for the instrument */
/*           as auto or fixed rate.                                        */
/*=========================================================================*/
int TPM3000::pm3000_conf_sampling (int instrID, int rate, double freq)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (rate, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (rate == 0) {
        if (pm3000_write_data (instrID, ":CFG 21,0\n", 10) != 0)
            return pm3000_err;
    }
    else {
        sprintf (cmd, ":CFG 21,1;:CFG 22,%f\n", freq);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Triggering                                          */
/* Purpose:  This function enables or disables the retriggering mode of    */
/*           the instrument                                                */
/*=========================================================================*/
int TPM3000::pm3000_conf_trig (int instrID, int retrig)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (retrig, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":RTR:%s\n", Action[retrig]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Integrator                                          */
/* Purpose:  This function enables/disables the integrator for the         */
/*           instrument and configures its operation.                      */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_integrator (int instrID, int state, int disp,
                                   int control, int trig, char run_time[],
                                   char i_date[], char f_date[], char i_time[],
                                   char f_time[], int cyclic, char interval[],
                                   char b1_time[], char b2_time[],
                                   char b3_time[], char b4_time[],
                                   char b5_time[])
{
    int count, val1, val2, val3;
    AnsiString Str;

    if (pm3000_invalid_integer_range (state, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (disp, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (control, 0, 1, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (trig, 0, 1, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (cyclic, 0, 1, -11) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Count contains bytes in the command to be written */
    count = 0;

 /* Enable the integration */
    if (state == 1) {
        sprintf (cmd, ":INT:ENB;:CFG 102,%d;:CFG 115,%d", control, disp);
        Str=cmd;
        count += Str.Length ();

     /* Integration control set to trigger */
        if (control == 0) {
            sprintf (cmd, ":CFG 101,%d", trig);
            Str=cmd;
            count += Str.Length ();

         /* Set the run-time if external trigger disabled */
            if (trig == 0) {
                if (pm3000_time_parser (run_time, &val1, &val2, -6) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -6) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -6) != 0)
                    return pm3000_err;
                sprintf (cmd, ":INT:RUN %d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
            }
        }

     /* Integration control set to timed */
        else {
            if (pm3000_date_parser (i_date, &val1, &val2, &val3, -7) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val1, 1, 31, -7) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val2, 1, 12, -7) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val3, 0, 99, -7) != 0)
                return pm3000_err;
            sprintf (cmd, ":CFG 105,%d", val3*512L+val2*32L+val1);
            Str=cmd;
            count += Str.Length ();
            if (pm3000_date_parser (f_date, &val1, &val2, &val3, -8) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val1, 1, 31, -8) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val2, 1, 12, -8) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val3, 0, 99, -8) != 0)
                return pm3000_err;
            sprintf (cmd, ":CFG 106,%d", val3*512L+val2*32L+val1);
            Str=cmd;
            count += Str.Length ();
            if (pm3000_time_parser (i_time, &val1, &val2, -9) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val1, 0, 23, -9) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val2, 0, 59, -9) != 0)
                return pm3000_err;
            sprintf (cmd, ":CFG 107,%d", val1*60+val2);
            Str=cmd;
            count += Str.Length ();
            if (pm3000_time_parser (f_time, &val1, &val2, -10) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val1, 0, 23, -10) != 0)
                return pm3000_err;
            if (pm3000_invalid_integer_range (val2, 0, 59, -10) != 0)
                return pm3000_err;
            sprintf (cmd, ":CFG 108,%d;:CFG 103,%d", val1*60+val2, cyclic);
            Str=cmd;
            count += Str.Length ();

         /* Cyclic integration is enabled */
            if (cyclic == 1) {
                if (pm3000_time_parser (interval, &val1, &val2, -12) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -12) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -12) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 104,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
            }

         /* Cyclic integration disabled */
            else {
                if (pm3000_time_parser (b1_time, &val1, &val2, -13) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -13) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -13) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 109,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
                if (pm3000_time_parser (b2_time, &val1, &val2, -14) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -14) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -14) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 110,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
                if (pm3000_time_parser (b3_time, &val1, &val2, -15) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -15) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -15) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 111,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
                if (pm3000_time_parser (b4_time, &val1, &val2, -16) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -16) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -16) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 112,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
                if (pm3000_time_parser (b5_time, &val1, &val2, -17) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val1, 0, 23, -17) != 0)
                    return pm3000_err;
                if (pm3000_invalid_integer_range (val2, 0, 59, -17) != 0)
                    return pm3000_err;
                sprintf (cmd, ":CFG 113,%d", val1*60+val2);
                Str=cmd;
                count += Str.Length ();
            }
        }
    }

 /* Disable the integrator */
    else {
        sprintf (cmd, ":INT:DIS");
        Str=cmd;
        count += Str.Length ();
    }

 /* Add a line feed to cmd and write the command */
    sprintf (cmd, "\n");
    count++;
    if (pm3000_write_data (instrID, cmd, count) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Select Harmonic                                     */
/* Purpose:  This function selects a single harmonic to be displayed or    */
/*           read back during a foreground read.                           */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_sel_harm (int instrID, int single)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (single, 0, 99, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":HRM %d\n", single);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Harmonic Analysis                                   */
/* Purpose:  This function sets the harmonic analysis parameters for the   */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_harm_analy (int instrID, int h_mode, int ref, int max,
                                   int odd_even, int form, int dc)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (h_mode, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (ref, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (max, 0, 99, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (odd_even, 0, 1, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (form, 0, 1, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (dc, 0, 1, -7) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 18,%d;:CFG 17,%d;:HMX:%s %d;:CFG 16,%d;:CFG 19,%d\n",
               h_mode, ref, Harmonic[odd_even], max, form, dc);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure IEC555 Mode                                         */
/* Purpose:  This function configures the IEC555 measurement mode          */
/*           of the instrument.                                            */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_IEC555_mode (int instrID, int iec, int chan)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (iec, 0, 3, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 0, 3, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (iec == 0)
        sprintf (cmd, ":IEC:DIS\n");
    else {
        if ((iec != 1) && (chan == 0)) {
            pm3000_err = 306;
            return pm3000_err;
        }
        sprintf (cmd, ":IEC:%s:%s\n", IEC_Mode[iec], Channel[chan]);
    }
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Flicker Meter                                       */
/* Purpose:  This function configures the IEC555 flicker meter mode        */
/*           of the instrument.                                            */
/*=========================================================================*/
int TPM3000::pm3000_conf_flicker_meter (int instrID, int state, double run,
                                 double drop, int method, double resist,
                                 double induct)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (state, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (run, 0.0, 15.0, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (drop, 0.0, 10.0, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (method, 0, 1, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (resist, 0.0, 1e9, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (induct, 0.0, 1e9, -7) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (state == 1) {
        sprintf (cmd, ":CFG 129,4;:CFG 262,%d;:CFG 263,%d;:CFG 264,%d;:CFG 260,%f;:CFG 261,%f\n",
             (int)(run / 0.1), (int) (drop / 0.05), method, resist, induct);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;
    }
    else
        if (pm3000_write_data (instrID, ":CFG 129,0\n", 11) != 0)
            return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure Selection List                                      */
/* Purpose:  This function configures the selection list to be read back   */
/*           from the instrument using a background or foreground read.    */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_select_list (int instrID, int clear, int select)
{
    AnsiString Str;
    if (pm3000_device_closed (instrID) !=0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (clear, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (select, 0, 21, -3) != 0)
        return pm3000_err;

 /* Clear the selection list if desired */
    if (clear == 1)
        sprintf (cmd, ":SEL:CLR;:SEL:%s\n", Select_List[select]);
    else
        sprintf (cmd, ":SEL:%s\n", Select_List[select]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure Efficiency                                          */
/* Purpose:  This function configures the efficiency measurement feature   */
/*           of the instrument.                                            */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_efficiency (int instrID, int state, int formula,
                                   int unit, double scale)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (state, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (formula, 0, 4, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (unit, 0, 3, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (scale, 0.0, 1e9, -5) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 270,%d;:CFG 271,%d;:CFG 272,%d;:CFG 273,%f\n",
        state, formula, unit, scale);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Power Factor                                        */
/* Purpose:  This function configures the target power factor and power    */
/*           factor sign for the instrument.                               */
/*=========================================================================*/
int TPM3000::pm3000_conf_meas_PF (int instrID, double target, int sign)
{
    AnsiString Str;

    if (pm3000_invalid_real_range (target, 0.0, 1.0, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (sign, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 2,%f;:CFG 190,%d\n", target, sign);
    Str=cmd; 
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure Display                                             */
/* Purpose:  This function configures front-panel display of the           */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_display (int instrID, int chan, int form, int u_left,
                           int u_right, int update, int blank, int primary,
                           int l_right)
{
    AnsiString Str;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 0, 4, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (form, 0, 2, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (u_left, 0, 7, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (u_right, 0, 7, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (update, 0, 99, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (blank, 0, 1, -7) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (primary, 0, 31, -8) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (l_right, 0, 7, -9) != 0)
        return pm3000_err;

    sprintf(cmd, ":CFG 180,%d;:CFG 185,%d;:CFG 181,%d;:CFG 182,%d;:CFG 183,%d;:CFG 186,%d;:CFG 26,%d;:CFG 20,%d\n",
         chan, form, primary, u_right, u_left, l_right, blank, update);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Configure PWM Drive Mode                                      */
/* Purpose:  This function configures the PMW drive mode for the           */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_PWM_drive_mode (int instrID, int f_mode, double window,
                                  int filter, double amps, double volts,
                                  double watts)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (f_mode, 0, 3, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (window, 1.0, 10.0, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (filter, 1, 3, -4) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    switch (f_mode) {
        case 0: sprintf (cmd, ":PWM:DIS\n");
                break;

        case 1: sprintf (cmd, ":PWM:INP %f\n", window);
                break;

        case 2: sprintf (cmd, ":PWM:OUT %d\n", filter);
                break;

        case 3: sprintf (cmd, ":PWM:REC;:CFG 116,%f;:CFG 117,%f;:CFG 118,%f;:CFG 120,%d\n",
                     amps, volts, watts, filter);
                break;
    }
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Ballast Mode                                        */
/* Purpose:  This function configures the ballast mode for the instrument. */
/*=========================================================================*/
int TPM3000::pm3000_conf_ballast_mode (int instrID, int blst_mode)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (blst_mode, 0, 2, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":BAL:%s\n", Ballast[blst_mode]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure High Bandwidth                                      */
/* Purpose:  This function configures the high bandwidth mode for the      */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_high_band (int instrID, int band)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (band, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":HGH:%s\n", Action[band]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Chart Recorder                                      */
/* Purpose:  This function configures the eight recorder outputs of the    */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_chart_rec (int instrID, int rec, int state, int chan,
                             int func, double min, double max)
{
    int cfg_num;
    AnsiString Str;

    if (pm3000_invalid_integer_range (rec, 0, 7, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (state, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 0, 4, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (func, 0, 31, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (min, -1e9, 1e9, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (max, -1e9, 1e9, -7) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* The variable cfg_num is configuration number for corresponding recorder */
    cfg_num = 200 + 6 * rec;

    sprintf (cmd, ":CFG %d,%d;:CFG %d,%d;:CFG %d,%d;:CFG %d,%f;:CFG %d,%f\n",
         cfg_num, state, cfg_num+2, chan, cfg_num+1, func, cfg_num+3, min,
         cfg_num+4, max);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Configure Auxiliary Inputs                                    */
/* Purpose:  This function configures the auxiliary input settings of the  */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_conf_aux_inputs (int instrID, int state, int t_range,
                              double t_scale, int t_units, int r_range,
                              double r_scale, int r_input)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (state, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (t_range, 0, 1, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (t_scale, -1e9, 1e9, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (t_units, 0, 1, -5) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (r_range, 0, 1, -6) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (r_scale, -1e9, 1e9, -7) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (r_input, 0, 1, -8) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 193,%d;:CFG 194,%d;:CFG 195,%f;:CFG 196,%d;:CFG 197,%d;:CFG 198,%f;:CFG 199,%d\n",
         state, t_range, t_scale, t_units, r_range, r_scale, r_input);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Execute Trigger                                               */
/* Purpose:  This function sends the common command *TRG to the instrument.*/
/*=========================================================================*/
int TPM3000::pm3000_exec_trigger (int instrID)
{

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (pm3000_write_data (instrID, "*TRG\n", 5) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Execute Reset Averaging                                       */
/* Purpose:  This function resets the averaging for the instrument.        */
/*=========================================================================*/
int TPM3000::pm3000_exec_res_avg (int instrID)
{

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (pm3000_write_data (instrID, ":RAV\n", 5) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Execute Acquisition Control                                   */
/* Purpose:  This function runs or stops the acquisition of the instrument.*/
/*=========================================================================*/
int TPM3000::pm3000_exec_acq_control (int instrID, int action)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (action, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 11,%d\n", action);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Execute Display Control                                       */
/* Purpose:  This function turns the hold feature of the display on or off.*/
/*=========================================================================*/
int TPM3000::pm3000_exec_disp_control (int instrID, int hold)
{
    AnsiString Str;

    if (pm3000_invalid_integer_range (hold, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 12,%d\n", hold);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read Single Measurement                                       */
/* Purpose:  This function reads a selected single measurement from the    */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_single_meas (int instrID, int chan, int func,
                                    float &value)
{
    AnsiString Str;
    float  v;
    if (pm3000_invalid_integer_range (chan, 1, 5, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (func, 0, 26, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":FNC:%s:%s?\n", Channel[chan], Func_List[func]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////
    if (sscanf (cmd, "%f", &v) != 1) {
        pm3000_err = 236;
        return pm3000_err;
    }
    value=v;
    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read Fundamental Data                                         */
/* Purpose:  This function reads a selected fundamental measurement from   */
/*           the instrument.                                               */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_fund_data (int instrID, int chan, int func,
                                  float &value)
{
    AnsiString Str;
    float v;
    if (pm3000_invalid_integer_range (chan, 1, 5, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (func, 0, 17, -3) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":FND:%s:%s?\n", Channel[chan], Fund_List[func]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////
    if (sscanf (cmd, "%f", &v) != 1) {
        pm3000_err = 236;
        return pm3000_err;
    }
    value=v;
    return pm3000_err;
}
/*=========================================================================*/
/* Function: Read Background Data                                          */
/* Purpose:  This function reads the background data measurements selected */
/*           from the instrument.                                          */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_back_data (int instrID, int trig, DWORD wait,
                                  int chan, float *arr, int &Size)
{
    AnsiString Str;
    char response;
    int i, k, j, num_vals, start;
    DWORD time1,time2;
    float vals[8];

    if (pm3000_device_closed (instrID) !=0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (trig, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (wait, 0.0, 3600.0, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 1, 6, -4) != 0)
        return pm3000_err;

 /* Send trigger to instrument if specified by user */
    if (trig == 1) {
        if (pm3000_write_data (instrID, "*TRG\n", 5) != 0)
            return pm3000_err;
    }

 /* Read the background status register to check for averaging full */
    sprintf (cmd, ":BSR?\n");
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;
//    Str=cmd;
    if (pm3000_read_data (instrID, cmd, 1000) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////
    if (sscanf (cmd, "%d", &i) != 1) {
        pm3000_err = 236;
        return pm3000_err;
    }

 /* Set the register mask according to the instrument's current status */
    if (i == 7)
     /* Mask the background status register to check for new data available */
        sprintf (cmd, ":BSE 2\n");
    else
     /* Mask the background status register to check for averaging full */
        sprintf (cmd, ":BSE 4\n");

    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

 /* Wait until averaging full or user-specified time has elapsed */
    time2=timeGetTime();
    response = 0;
    if (pm3000_poll (instrID, &response) != 0)
        return pm3000_err;
    while ((response & 0x2) == 0) {
        time1 = timeGetTime();
        if ((time1 - time2) > wait*1000)  // multiply by 1000 to convert wait from second to milisecond
        {
            pm3000_err = 305;
            return pm3000_err;
        }
        Sleep (1500); //55 miliseconds
        if (pm3000_poll (instrID, &response) != 0)
            return pm3000_err;
    }

 /* Send the Read Background query */
    sprintf (cmd, ":BRD:%s?\n", Channel[chan]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////

 /* start = index for double array returned */
    start = 0;

 /* num_vals = number of values returned in a single read */
    num_vals = 0;
    Str=cmd;
////////////////// Replace "," by " " //////////////
    for(k=1;k<=Str.Length();k++)
      if(Str.Pos(",")==k) {
        Str.Delete(k,1);
        Str.Insert(" ",k);
      }


    while (Str.Pos("END") <= 0) {
        num_vals = sscanf (Str.c_str(), "%f%f%f%f%f%f%f%f",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6], &vals[7]);
        j = 0;
        for (i = start; i < (start + num_vals); i++) {
            arr[i] = vals[j];
            j++;
        }
        start += num_vals;

     /* Read the next set of values from the instrument */
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
          if(Str.Pos(",")==k) {
             Str.Delete(k,1);
             Str.Insert(" ",k);
          }
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
    }
    Size=start;
    return pm3000_err;
}
/*=========================================================================*/
/* Function: Read Foreground Data                                          */
/* Purpose:  This function reads the foreground data measurements selected */
/*           from the instrument.                                          */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_fore_data (int instrID, int chan, float *arr, int &Size)
{
    int i, k, j, num_vals, start;
    float vals[8];
    AnsiString Str;

    if (pm3000_invalid_integer_range (chan, 1, 6, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Send the Foreground Read query */
    sprintf (cmd, ":FRD:%s?\n", Channel[chan]);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////

 /* start = index for double array returned */
    start = 0;

 /* num_vals = number of values returned in a single read */
    num_vals = 0;

    Str=cmd;
////////////////// Replace "," by " " //////////////
    for(k=1;k<=Str.Length();k++)
      if(Str.Pos(",")==k) {
        Str.Delete(k,1);
        Str.Insert(" ",k);
      }

    while (Str.Pos("END") <= 0) {
        num_vals = sscanf (cmd, "%f%f%f%f%f%f%f%f",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6], &vals[7]);
        j = 0;
        for (i = start; i < (start + num_vals); i++) {
            arr[i] = vals[j];
            j++;
        }
        start += num_vals;

     /* Read the next set of values from the instrument */
        if (pm3000_read_data (instrID, cmd, 1024) != 0)
            return pm3000_err;
        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
         if(Str.Pos(",")==k) {
           Str.Delete(k,1);
           Str.Insert(" ",k);
         }

///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
    }
    Size=start;
    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read IEC555 Fluctuating Data                                  */
/* Purpose:  This function reads the IEC555 fluctuating harmonic data from */
/*           the instrument.                                               */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_fluct_data (int instrID, float arr[])
{
    int i, k, j, num_vals, start;
    float vals[8];
    AnsiString Str;

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Send the IEC555 read query */
    if (pm3000_write_data (instrID, ":IEC:FLU?\n", 10) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////

 /* start = index for double array returned */
    start = 0;

 /* num_vals = number of values returned in a single read */
    num_vals = 0;

    Str=cmd;
////////////////// Replace "," by " " //////////////
    for(k=1;k<=Str.Length();k++)
      if(Str.Pos(",")==k) {
        Str.Delete(k,1);
        Str.Insert(" ",k);
      }

    while (Str.Pos("END") <= 0) {
//////////////////////////////////////////////////////////////////////
        num_vals = sscanf (cmd, "%f%f%f%f%f%f%f%f",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6], &vals[7]);
        j = 0;
        for (i = start; i < (start + num_vals); i++) {
            arr[i] = vals[j];
            j++;
        }
        start += num_vals;

     /* Read the next set of values from the instrument */
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
         if(Str.Pos(",")==k) {
           Str.Delete(k,1);
           Str.Insert(" ",k);
         }

///////////////////////////////////
       if (pm3000_write_data (instrID, " ",1) != 0)
           return pm3000_err;
//////////////////////////////////
    }//end while

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read IEC555 Flicker Data                                      */
/* Purpose:  This function reads the IEC555 flicker harmonic data from     */
/*           the instrument.                                               */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_flick_data (int instrID, long arr[])
{
    int i, k, j, num_vals, start;
    long vals[8];
    AnsiString Str;

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Send the IEC555 read query */
    if (pm3000_write_data (instrID, ":IEC:FLI?\n", 10) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////

 /* start = index for double array returned */
    start = 0;

 /* num_vals = number of values returned in a single read */
    num_vals = 0;

    Str=cmd;
////////////////// Replace "," by " " //////////////
    for(k=1;k<=Str.Length();k++)
      if(Str.Pos(",")==k) {
        Str.Delete(k,1);
        Str.Insert(" ",k);
      }

    while (Str.Pos("END") <= 0) {
//////////////////////////////////////////////////////////////////////
        num_vals = sscanf (cmd, "%d%d%d%d%d%d%d%d",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6], &vals[7]);
        j = 0;
        for (i = start; i < (start + num_vals); i++) {
            arr[i] = vals[j];
            j++;
        }
        start += num_vals;

     /* Read the next set of values from the instrument */
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
         if(Str.Pos(",")==k) {
           Str.Delete(k,1);
           Str.Insert(" ",k);
         }

///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read Datalog Values                                           */
/* Purpose:  This function reads the datalog background data from the      */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_meas_read_dlog_vals (int instrID, int l_mode, long window,
                                  DWORD wait, int chan, float arr[])
{
    char response;
    int i, k, j, num_vals, start;
    DWORD time1, time2;
    float vals[8];
    AnsiString Str;

    if (pm3000_invalid_integer_range (l_mode, 0, 2, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_longint_range (window, 18, 65000, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (wait, 0.0, 3600.0, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (chan, 1, 5, -5) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    switch (l_mode) {
        case 0: if (pm3000_write_data (instrID, ":LOG:DIS\n", 9) != 0)
                    return pm3000_err;
                break;

        case 1: sprintf (cmd, ":LOG:TRG;:BSR?\n");
                break;

        case 2: sprintf (cmd, ":LOG:EXT %d;:BSR?\n", window);
                break;
    }

 /* If logging mode is not disable, read dump data */
    if (l_mode != 0) {
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;

        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
        if (sscanf (cmd, "%d", &i) != 1) {
            pm3000_err = 236;
            return pm3000_err;
        }

      /* Set the register mask according to current status */
         if (i == 7)
         /* Mask the BSR to check for new data available */
            sprintf (cmd, ":BSE 2\n");
         else
         /* Mask the BSR to check for averaging full */
            sprintf (cmd, ":BSE 4\n");

        if (pm3000_write_data (instrID, cmd, 7) != 0)
            return pm3000_err;

     /* Wait until background averaging finished */
        time2 = timeGetTime ();
        response = 0;
        if (pm3000_poll (instrID, &response) != 0)
            return pm3000_err;
        while ((response & 0x2) == 0) {
            time1 = timeGetTime ();
            if ((time1 - time2) > wait*1000) {
                pm3000_err = 305;
                return pm3000_err;
            }
            Sleep(55);
            if (pm3000_poll (instrID, &response) != 0)
                return pm3000_err;
        }

     /* Send the Read Background query */
        sprintf (cmd, ":BRD:%s?\n", Channel[chan]);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;

        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////

     /* start = index for double array returned */
        start = 0;

     /* num_vals = number of values returned in a single read */
        num_vals = 0;

        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
         if(Str.Pos(",")==k) {
           Str.Delete(k,1);
           Str.Insert(" ",k);
         }

        while (Str.Pos("END") <= 0) {
///////////////////////////////////////////////////////////////////////////////////////
            num_vals = sscanf (cmd, "%f%f%f%f%f%f%f%f",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6], &vals[7]);
            j = 0;
            for (i = start; i < (start + num_vals); i++) {
                arr[i] = vals[j];
                j++;
            }
            start += num_vals;

         /* Read the next set of values from the instrument */
            if (pm3000_read_data (instrID, cmd, 100) != 0)
               return pm3000_err;

            Str=cmd;
////////////////// Replace "," by " " //////////////
            for(k=1;k<=Str.Length();k++)
             if(Str.Pos(",")==k) {
               Str.Delete(k,1);
               Str.Insert(" ",k);
             }

///////////////////////////////////
            if (pm3000_write_data (instrID, " ",1) != 0)
               return pm3000_err;
//////////////////////////////////
        }//end while

 /* Disable datalogging */
    if (pm3000_write_data (instrID, ":LOG:DIS\n", 9) != 0)
        return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Read Datalog Samples                                          */
/* Purpose:  This function reads the datalog dump data from the instrument.*/
/*=========================================================================*/
int TPM3000::pm3000_meas_read_dlog_samps (int instrID, int l_mode, long window,
                                   DWORD wait, int samples, long arr[])
{
    char response;
    int i, k, j, num_vals, start;
    long vals[7];
    DWORD time1, time2;
    AnsiString Str;

    if (pm3000_invalid_integer_range (l_mode, 0, 2, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_longint_range (window, 18, 65000, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (wait, 0.0, 3600.0, -4) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (samples, 200, 6000, -5) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    switch (l_mode) {
        case 0: if (pm3000_write_data (instrID, ":LOG:DIS\n", 9) != 0)
                    return pm3000_err;
                break;

        case 1: sprintf (cmd, ":LOG:TRG:DMP;:BSR?\n");
                break;

        case 2: sprintf (cmd, ":LOG:EXT:DMP %d;:BSR?\n", window);
                break;
    }

 /* If logging mode is not disable, read dump data */
    if (l_mode != 0) {
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
        if (sscanf (cmd, "%d", &i) != 1) {
            pm3000_err = 236;
            return pm3000_err;
        }

      /* Set the register mask according to current status */
         if (i == 7)
         /* Mask the BSR to check for new data available */
            sprintf (cmd, ":BSE 2\n");
         else
         /* Mask the BSR to check for averaging full */
            sprintf (cmd, ":BSE 4\n");

        if (pm3000_write_data (instrID, cmd, 7) != 0)
            return pm3000_err;

     /* Wait until datalogging finished */
        time2 = timeGetTime ();
        response = 0;
        if (pm3000_poll (instrID, &response) != 0)
            return pm3000_err;
        while ((response & 0x2) == 0) {
            time1 = timeGetTime ();
            if ((time1 - time2) > wait*1000) {
                pm3000_err = 305;
                return pm3000_err;
            }
            Sleep(55);
            if (pm3000_poll (instrID, &response) != 0)
                return pm3000_err;
        }

        sprintf (cmd, ":LOG:DMP? %d\n", 6000 / samples);
        Str=cmd;
        if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
            return pm3000_err;

        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////

     /* start = index for double array returned */
        start = 0;

     /* num_vals = number of values returned in a single read */
        num_vals = 0;

        Str=cmd;
////////////////// Replace "," by " " //////////////
        for(k=1;k<=Str.Length();k++)
         if(Str.Pos(",")==k) {
           Str.Delete(k,1);
           Str.Insert(" ",k);
         }

        while (Str.Pos("END") <= 0) {
            num_vals = sscanf (cmd, "%d%d%d%d%d%d%d",
                         &vals[0], &vals[1], &vals[2], &vals[3], &vals[4],
                         &vals[5], &vals[6]);
            j = 0;
            for (i = start; i < (start + num_vals); i++) {
                arr[i] = vals[j];
                j++;
            }
            start += num_vals;

         /* Read the next set of values from the instrument */
            if (pm3000_read_data (instrID, cmd, 100) != 0)
               return pm3000_err;

            Str=cmd;
////////////////// Replace "," by " " //////////////
            for(k=1;k<=Str.Length();k++)
              if(Str.Pos(",")==k) {
                 Str.Delete(k,1);
                 Str.Insert(" ",k);
              }

///////////////////////////////////
            if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
        }//end while

 /* Disable datalogging */
    if (pm3000_write_data (instrID, ":LOG:DIS\n", 9) != 0)
        return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Synchronize                                                   */
/* Purpose:  This function masks the display or background status register */
/*           for a specified event serial polls the instrument until the   */
/*           has taken place.                                              */
/*=========================================================================*/
int TPM3000::pm3000_synchronize (int instrID, int reg, int event, DWORD secs)
{
    char response;
    int i;
    DWORD time1, time2;
    AnsiString Str;

    if (pm3000_invalid_integer_range (reg, 0, 1, -2) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (event, 0, 2, -3) != 0)
        return pm3000_err;
    if (pm3000_invalid_real_range (secs, 0.0, 3600.0, -4) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

 /* Send the syncho commands for the appropriate status register */
    if (reg == 0) {
     /* Query the Background Status Register */
        if (pm3000_write_data (instrID, ":BSR?\n", 6) != 0)
            return pm3000_err;
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
        if (sscanf (cmd, "%d", &i) != 1) {
            pm3000_err = 236;
            return pm3000_err;
        }

     /* If the desired event has not occurred mask the register and poll */
        if ((i & ((int) pow (2, event))) == 0) {
            sprintf (cmd, ":BSE %d\n", (int) pow (2, event));
            Str=cmd;
            if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
                return pm3000_err;

        /* Wait for event or stop when user-specified time has elapsed */
            time2 = timeGetTime ();
            response = 0;
            if (pm3000_poll (instrID, &response) != 0)
                return pm3000_err;
            while ((response & 0x2) == 0) {
                time1 = timeGetTime ();
                if ((time1 - time2) > secs*1000) {
                    pm3000_err = 305;
                    return pm3000_err;
                }
                Sleep(55);
                if (pm3000_poll (instrID, &response) != 0)
                    return pm3000_err;
            }
        }
    }

    else {
     /* Query the Display Status Register */
        if (pm3000_write_data (instrID, ":DSR?\n", 6) != 0)
            return pm3000_err;
        if (pm3000_read_data (instrID, cmd, 100) != 0)
            return pm3000_err;
///////////////////////////////////
        if (pm3000_write_data (instrID, " ",1) != 0)
            return pm3000_err;
//////////////////////////////////
        if (sscanf (cmd, "%d", &i) != 1) {
            pm3000_err = 236;
            return pm3000_err;
        }

     /* If the desired event has not occurred mask the register and poll */
        if ((i & ((int) pow (2, event))) == 0) {
            sprintf (cmd, ":DSE %d\n", (int) pow (2, event));
            Str=cmd;
            if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
                return pm3000_err;

        /* Wait for event or stop when user-specified time has elapsed */
            time2 = timeGetTime ();
            response = 0;
            if (pm3000_poll (instrID, &response) != 0)
                return pm3000_err;
            while ((response & 0x1) == 0) {
                time1 = timeGetTime ();
                if ((time1 - time2) > secs*1000) {
                    pm3000_err = 305;
                    return pm3000_err;
                }
                Sleep(55);
                if (pm3000_poll (instrID, &response) != 0)
                    return pm3000_err;
            }
        }
    }

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Read Display                                                  */
/* Purpose:  This function reads back the current display of the           */
/*           instrument.                                                   */
/*=========================================================================*/
int TPM3000::pm3000_read_display (int instrID, char disp[])
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    disp="00000000000000000000000000000000000000000000";
    if (pm3000_write_data (instrID, ":DSP?\n", 6) != 0)
        return pm3000_err;

    if (pm3000_read_data (instrID, disp, 44) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Instrument Self Test                                          */
/* Purpose:  This function performs an internal self-test and obtains a    */
/*           value indicating the results of the test.                     */
/*=========================================================================*/
int TPM3000::pm3000_instr_self_test (int instrID, int *code)
{

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (pm3000_write_data (instrID, "*TST?\n", 6) != 0)
        return pm3000_err;
    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////
    if (sscanf (cmd, "%d", code) != 1) {
        pm3000_err = 236;
        return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Firmware Revision                                             */
/* Purpose:  This function will query the instrument for identification    */
/*           information and return the current firmware revision.         */
/*=========================================================================*/
int TPM3000::pm3000_firm_rev (int instrID, char revision[])
{

    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    revision="00000000000000000000";
    if (pm3000_write_data (instrID, "*IDN?\n", 6) != 0)
        return pm3000_err;
    if (pm3000_read_data (instrID, cmd, 100) != 0)
        return pm3000_err;
///////////////////////////////////
    if (pm3000_write_data (instrID, " ",1) != 0)
        return pm3000_err;
//////////////////////////////////
//////// how dose it appear ////////////////
    if (sscanf (cmd, "%s%s%s%s", revision) != 4) {
        pm3000_err = 236;
        return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Power Up Program                                              */
/* Purpose:  This function selects the power up program for the instrument.*/
/*=========================================================================*/
int TPM3000::pm3000_power_up_program (int instrID, int program)
{
    AnsiString Str;
    if (pm3000_invalid_integer_range (program, 0, 5, -2) != 0)
        return pm3000_err;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 1,%d\n", program);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Language                                                      */
/* Purpose:  This function selects the language used by the instrument     */
/*           display messages.                                             */
/*=========================================================================*/
int TPM3000::pm3000_language (int instrID, int language)
{
    AnsiString Str;
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (language, 0, 1, -2) != 0)
        return pm3000_err;

    sprintf (cmd, ":CFG 10,%d\n", language);
    Str=cmd;
    if (pm3000_write_data (instrID, cmd, Str.Length()) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Reset                                                         */
/* Purpose:  This function resets the instrument into a known state.       */
/*=========================================================================*/
int TPM3000::pm3000_reset (int instrID)
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (pm3000_write_data (instrID, "*RST\n", 5) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Clear                                                         */
/* Purpose:  This function sends the SCPI *CLS command to the instrument   */
/*           to clear the standard instrument registers and queues.        */
/*=========================================================================*/
int TPM3000::pm3000_clear(int instrID)
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (pm3000_write_data (instrID, "*CLS\n", 5 ) != 0)
        return pm3000_err;

    return pm3000_err;
}
/*=========================================================================*/
/* Function:  Set Timeout Value                                            */
/* Purpose:   This function changes the timeout limit for the instrument.  */
/*=========================================================================*/
int TPM3000::pm3000_set_timeout_val(int instrID, int new_value, int *old_value)
{
    if (pm3000_device_closed (instrID) !=0)
        return pm3000_err;
    if (pm3000_invalid_integer_range (new_value, 0, 17, -2) != 0)
        return pm3000_err;

    if (pm3000_set_timeout (instrID, new_value, old_value) != 0) {
        *old_value = -1;
        return pm3000_err;
    }

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Go to Local State                                             */
/* Purpose:  This function sets the instrument in the local state.         */
/*=========================================================================*/
int TPM3000::pm3000_goto_local(int instrID)
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (ibloc (instrID) & 0x8000) {
        pm3000_err = 234;
        return pm3000_err;
    }

    return pm3000_err;
}



/*= UTILITY ROUTINES ======================================================*/

/*=========================================================================*/
/* Function: Open Instrument                                               */
/* Purpose:  This function initializes Instrument's Address                */
/* The return value of this function is equal to the global error variable.*/
/*=========================================================================*/
int TPM3000::pm3000_open_instr (int addr)
{

    pm3000_err = 0;

/* If the device has not been opened in the GPIB device table (bd[ID] = 0),*/
/*  then open it.                                                          */

    if (instr_ID <= 0) {
        instr_ID = ibdev(0, addr, 0, instr_TimeOut, 1, 0);
        if (instr_ID <= 0) {
            pm3000_err = 220;//gpiberr("ibdev Error");
            return pm3000_err;
        }
     }

/*  Change the primary address of the device    */

    if (ibpad (instr_ID, addr) & 0x8000) {
        pm3000_err = 233;
        return pm3000_err;
    }

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Close Instrument                                              */
/* Purpose:  This function closes the instrument by removing it from the   */
/*           GPIB device table and setting the address and bd[instrID] to  */
/*           zero in the Instrument Table.  The return value is equal to   */
/*           the global error variable.                                    */
/*=========================================================================*/
int TPM3000::pm3000_close_instr (int instrID)
{
      if (instrID !=0){
  /*  Call the ibonl function to disable the hardware and software.           */
           ibonl(instrID, 0);
           instr_ID = 0;
           instr_addr = 0;
           pm3000_err = 0;
      }
      else
        pm3000_err = 221;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Device Closed                                                 */
/* Purpose:  This function checks to see if the module has been            */
/*           initialized.  If the device has not been opened, set the      */
/*           global error variable to 232, 0 otherwise. The return value   */
/*           is equal to the global error value.                           */
/*=========================================================================*/
int TPM3000::pm3000_device_closed (int instrID)
{
    if (instrID <= 0)
        pm3000_err = 232;
    else
        pm3000_err = 0;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Serial Poll                                                   */
/* Purpose:  This function performs a serial poll on the instrument.       */
/*           The status byte of the instrument is placed in the response   */
/*           variable. The return value is equal to the global error       */
/*           variable.                                                     */
/*=========================================================================*/
int TPM3000::pm3000_poll (int instrID, char *response)
{
    if (ibrsp (instrID, response) & 0x8000)
        pm3000_err = 226;
    else
        pm3000_err = 0;

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Set Timeout                                                   */
/* Purpose:  This function changes or disables the timeout of the device.  */
/*           Refer to the LabWindows Standard Libraries Reference Manual   */
/*           for timeout codes. The return value is equal to the global    */
/*           error variable.                                               */
/*=========================================================================*/
int TPM3000::pm3000_set_timeout (int instrID, int tmo_code, int *old_timeout)
{
    instr_TimeOut= tmo_code;
    if (ibtmo (instrID, instr_TimeOut) & 0x8000)
        pm3000_err = 239;
    else {
        *old_timeout = iberr;
        pm3000_err = 0;
    }
    return pm3000_err;
}
/*=========================================================================*/
/* Function: Time Parser                                                   */
/* Purpose:  This function parses a time string and obtains the two        */
/*           numeric values found in this time string. The return value is */
/*           equal to the global error variable.                           */
/*=========================================================================*/
int TPM3000::pm3000_time_parser (char *time_str, int *v1, int *v2, int err_code)
{
//////////////////////////////////////////////////////////////////////////////////////
    if (sscanf (time_str, "%i%i", v1, v2) != 2)
        pm3000_err = err_code;
    else
        pm3000_err = 0;
    return pm3000_err;
}

/*=========================================================================*/
/* Function: Date Parser                                                   */
/* Purpose:  This function parses a date string and obtains the three      */
/*           numeric values found in this time string. The return value is */
/*           equal to the global error variable.                           */
/*=========================================================================*/
int TPM3000::pm3000_date_parser (char *date_str, int *v1, int *v2, int *v3, int err_code)
{
    if (sscanf (date_str, "%i%i%i", v1, v2, v3) != 3)
        pm3000_err = err_code;
    else
        pm3000_err = 0;
    return pm3000_err;
}
/*=========================================================================*/
/* Function: Check if Instrument Listener                                  */
/* Purpose:  Checks to see if the instrument is a listener on the GPIB bus */
/*           due to communication conflicts.  This function keeps the      */
/*           instrument from entering a locked state after sending a       */
/*           command.                                                      */
/*=========================================================================*/
int TPM3000::pm3000_check_instr_listen (int instrID)
{
    short listen = 0;
    pm3000_err = 0;

 /* Check to see if instrument is listener due to communication conflicts */
    if (ibln (instrID, instr_addr, 0, &listen) & 0x8000) {
        pm3000_err = 242;
        return pm3000_err;
    }
    if (listen == 0) {
        pm3000_err = 243;
        return pm3000_err;
    }

    return pm3000_err;
}
/*=========================================================================*/
/* Function: Invalid Integer Range                                         */
/* Purpose:  This function checks an integer to see if it lies between a   */
/*           minimum and maximum value.  If the value is out of range, set */
/*           the global error variable to the value err_code.  If the      */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int TPM3000::pm3000_invalid_integer_range (int val, int min, int max, int err_code)
{
    if (val < min || val > max)
        pm3000_err = err_code;
    else
        pm3000_err = 0;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Invalid Long Integer Range                                    */
/* Purpose:  This function checks a long integer to see if it lies between */
/*           a minimum and maximum value.  If the value is out of range,   */
/*           set the global error variable to the value err_code.  If the  */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int TPM3000::pm3000_invalid_longint_range (long val,long min,long max,int err_code)
{
    if (val < min || val > max)
        pm3000_err = err_code;
    else
        pm3000_err = 0;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Invalid Real Range                                            */
/* Purpose:  This function checks a real number to see if it lies between  */
/*           a minimum and maximum value.  If the value is out of range,   */
/*           set the global error variable to the value err_code.  If the  */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int TPM3000::pm3000_invalid_real_range (double val, double min, double max, int err_code)
{
    if (val < min || val > max)
        pm3000_err = err_code;
    else
        pm3000_err = 0;

    return pm3000_err;
}


/*=========================================================================*/
/* Function: Read Data                                                     */
/* Purpose:  This function reads a buffer of data from the instrument. The */
/*           return value is equal to the global error variable.           */
/*=========================================================================*/
int TPM3000::pm3000_read_data (int instrID, char *buf, int cnt)
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (ibrd(instrID, buf, (long)cnt) & 0x8000) {
        pm3000_err = 231;
        return pm3000_err;
    }
    else
        pm3000_err = 0;

    return pm3000_err;
}

/*=========================================================================*/
/* Function: Write Data                                                    */
/* Purpose:  This function writes a buffer of data to the instrument. The  */
/*           return value is equal to the global error variable.           */
/*=========================================================================*/
int TPM3000::pm3000_write_data (int instrID, char *buf, int cnt)
{
    if (pm3000_device_closed(instrID) != 0)
        return pm3000_err;

    if (ibwrt(instrID, buf, (long)cnt) & 0x8000)
        pm3000_err = 230;
    else
        pm3000_err = 0;

    return pm3000_err;
}
/*=========================================================================*/
void TPM3000::gpiberr(char *msg) {
    AnsiString e;
    sprintf(e.c_str(),"%s\n The PM3000_Error=%d",msg,pm3000_err);
    MessageDlg(e.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
    ibonl(0, 0); /* Disable hardware and software */
}
/*=========================================================================*/

