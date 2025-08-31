/* = Unipolar Operational Power Supply Include Header File =============== */

#ifndef __uop7907_HEADER
#define __uop7907_HEADER

class TUOP7907
{
 public:
   TUOP7907();
   ~TUOP7907();
   static int uop7907_err;
   static int instr_addr;
   static int instr_ID;
   static int TimeOut;
   static HINSTANCE Gpib32Lib;
   static int *Pibsta;
   static int *Piberr;
   static long *Pibcntl;

/*== GLOBAL FUNCTION DECLARATIONS =========================================*/
int uop7907_init (int address, int reset);

int uop7907_set_voltage_resulation (int instrumentID, int resulation);

int uop7907_set_trigger_mode (int instrumentID, int trigger_mode);

int uop7907_set_force_mode (int instrumentID, int force_mode);

int uop7907_set_analog_input_mode (int instrumentID, int input_mode);

int uop7907_trig (int instrumentID);

int uop7907_set_timeout (int instrumentID, int tmo_val);

int uop7907_set_voltage_value (int instrumentID, float value);

int uop7907_set_current_value (int instrumentID, float value);

/* = UTILITY ROUTINES ====================================================== */
int uop7907_open_instr (int);
int uop7907_close_instr (int);
int uop7907_invalid_real_range (double, double, double, int);
int uop7907_invalid_integer_range (int, int, int, int);
int uop7907_device_closed (int);
int uop7907_read_data (int, char *, int);
int uop7907_write_data (int, char *, int);
int uop7907_poll (int, char *);
int uop7907_set_tmo (int, int, int*);
int uop7907_error_check (int);
void uop7907_gpiberr(char *msg);
};
//---------------------------------------------------------------------------
extern  TUOP7907 UOP7907;
//---------------------------------------------------------------------------
#endif

