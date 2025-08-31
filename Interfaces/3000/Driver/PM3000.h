//---------------------------------------------------------------------------
/* = Voltech PM3000A Universal Power Analyzer include Header File ========= */
//---------------------------------------------------------------------------
#ifndef PM3000H
#define PM3000H
//---------------------------------------------------------------------------
class TPM3000
{
 public:
   TPM3000();
   ~TPM3000();
   static int pm3000_err; 
   static int instr_addr;
   static int instr_ID;
   static int instr_TimeOut;//must chose in setting file

/*== GLOBAL FUNCTION DECLARATIONS =========================================*/
int pm3000_init (int , int);
int pm3000_conf_operation (int , int , int , int , int , int , int , int);
int pm3000_conf_meas_select_list (int , int , int);
int pm3000_meas_read_back_data (int , int , DWORD , int ,float *,int &Size);
int pm3000_meas_read_fore_data (int, int, float *,int &Size);

int pm3000_conf_range_set (int, int, int, int,int);
int pm3000_conf_scaling_factors (int , double, double);
int pm3000_conf_wiring (int , int, int);
int pm3000_conf_sum_formulas (int, int, int);
int pm3000_conf_sampling (int, int,double);
int pm3000_conf_trig (int, int);
int pm3000_conf_meas_integrator (int, int, int, int, int, char[], char[], char [],char[], char[], int, char[], char[], char[], char[], char[], char[]);
int pm3000_conf_meas_sel_harm (int , int);
int pm3000_conf_meas_harm_analy (int, int, int, int,int, int, int);
int pm3000_conf_meas_IEC555_mode (int, int, int);
int pm3000_conf_flicker_meter (int, int, double , double, int, double , double);
int pm3000_conf_meas_efficiency (int, int, int, int, double);
int pm3000_conf_meas_PF (int, double , int);
int pm3000_conf_PWM_drive_mode (int, int, double, int, double, double, double);
int pm3000_conf_ballast_mode (int, int);
int pm3000_conf_high_band (int, int);
int pm3000_conf_chart_rec (int, int, int , int, int, double, double);
int pm3000_conf_aux_inputs (int, int, int, double, int, int, double, int);
int pm3000_exec_trigger (int);
int pm3000_exec_res_avg (int);
int pm3000_exec_acq_control (int, int);
int pm3000_exec_disp_control (int, int);
int pm3000_meas_read_single_meas (int, int, int, float &val);
int pm3000_meas_read_fund_data (int, int, int, float &val);
int pm3000_meas_read_fluct_data (int, float[]);
int pm3000_meas_read_flick_data (int, long[]);
int pm3000_meas_read_dlog_vals (int, int, long, DWORD, int, float[]);
int pm3000_meas_read_dlog_samps (int, int, long, DWORD, int, long[]);
int pm3000_synchronize (int, int, int, DWORD);
int pm3000_instr_self_test (int, int*);
int pm3000_firm_rev (int, char[]);
int pm3000_power_up_program (int, int);



int pm3000_conf_display (int, int , int , int , int , int , int , int , int);
int pm3000_read_display (int , char[]);

int pm3000_language (int , int);
int pm3000_reset (int);
int pm3000_clear(int);
int pm3000_set_timeout_val(int , int , int*);
int pm3000_goto_local(int);


/*= UTILITY ROUTINES ======================================================*/
int pm3000_poll (int , char*);
int pm3000_set_timeout (int, int, int*);
int pm3000_check_instr_listen (int);
int pm3000_time_parser (char *, int *, int *, int);
int pm3000_date_parser (char *, int *, int *, int *, int);
int pm3000_open_instr (int);
int pm3000_close_instr (int);
int pm3000_device_closed (int);
int pm3000_invalid_integer_range (int, int, int, int);
int pm3000_invalid_longint_range (long, long, long, int);
int pm3000_invalid_real_range (double, double, double, int);
int pm3000_read_data (int, char *, int);
int pm3000_write_data (int, char *, int);
void gpiberr(char*);
};
//---------------------------------------------------------------------------
extern  TPM3000 PM3000;
//---------------------------------------------------------------------------
#endif
