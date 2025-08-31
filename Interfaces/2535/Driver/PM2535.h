/* = Philips PM2535 Digital Multimeter Include File =================== */

#ifndef __pm253x_HEADER
#define __pm253x_HEADER

class TPM2535
{
 public:
   TPM2535();
   ~TPM2535();
   static int pm2535_err;
   static int instr_addr;
   static int instr_ID;
   static int TimeOut;
   static HINSTANCE Gpib32Lib;
   static int *Pibsta;
   static int *Piberr;
   static long *Pibcntl;

/*== GLOBAL FUNCTION DECLARATIONS =========================================*/
int pm2535_init (int address, int reset);
int pm2535_set_function (int instrumentID, int function);
int pm2535_set_range (int instrumentID, double range);
int pm2535_set_speed (int instrumentID, int speed);
int pm2535_set_resolution (int instrumentID, int resolution);
int pm2535_set_settling_time (int instrumentID, int mode);
int pm2535_set_filter (int instrumentID, int filter);
int pm2535_set_trig_source (int instrumentID, int source);
int pm2535_set_trig_delay (int instrumentID, int mode, double delay);
int pm2535_measure (int instrumentID, float &measurement);// * -> &
int pm2535_read_result (int instrumentID, float &result);
int pm2535_get_min_max (int instrumentID, float &min, float &max);
int pm2535_trig (int instrumentID);
int pm2535_reset_min_max (int instrumentID);
int pm2535_store_settings (int instrumentID, int location);
int pm2535_recall_settings (int instrumentID, int location);
int pm2535_set_timeout (int instrumentID, int timeout);

/* = UTILITY ROUTINES ====================================================== */
int pm2535_open_instr (int);
int pm2535_close_instr (int);
int pm2535_invalid_real_range (double, double, double, int);
int pm2535_invalid_integer_range (int, int, int, int);
int pm2535_device_closed (int);
int pm2535_read_data (int, char *, int);
int pm2535_write_data (int, char *, int);
int pm2535_poll (int, char *);
int pm2535_set_tmo (int, int, int*);
int pm2535_error_check (int);
void gpiberr(char *msg);

//bool LoadDll ();
//void FreeDll ();

};
//---------------------------------------------------------------------------
extern  TPM2535 PM2535;
//---------------------------------------------------------------------------
#endif

