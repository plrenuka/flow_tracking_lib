

//#define DEBUG
#ifdef DEBUG
#define DPRINT(x) Serial.print(x)
#define DPRINTln(x) Serial.println(x)
#else
#define DPRINT(x)
#define DPRINTln(x) 
#endif

/* 
	 flow_tracking_lib allows you to create and track flow of your c++ program.
*/

struct condn_func_data
{
  long prev_millis = 0;
  int internal_state = 0;
  bool callback_func_result = false;

};
int seq1_step_no = 1;
condn_func_data seq1_step_memory[25];
int seq2_step_no = 1;
condn_func_data seq2_step_memory[25];




void libMultiSeqFuncCall(int *seq_step_no, struct condn_func_data *Intseq_step_memory, int this_step_no, void (*callbackWrapperfunction)(), int func_Exe_complete_step_no)
{

  if ((this_step_no == *seq_step_no) && ((Intseq_step_memory + this_step_no)->internal_state == 0))
  {

    callbackWrapperfunction();
    *seq_step_no = func_Exe_complete_step_no;
    DPRINTln("Current Step No ");
    DPRINT(*seq_step_no);
    DPRINTln();

  }

}


void libMultiSeqCdnExpressionWithTimeout(int *seq_step_no, struct condn_func_data *Intseq_step_memory, int this_step_no, bool condition, long timeout_inmillis, int true_step_no, int true_timeout_step_no)
{
  //DPRINTln((Intseq_step_memory+this_step_no)->internal_state);
  if ((this_step_no == *seq_step_no) && ((Intseq_step_memory + this_step_no)->internal_state == 0))
  {
    (Intseq_step_memory + this_step_no)->internal_state = 1;
    (Intseq_step_memory + this_step_no)->prev_millis = millis();
    //DPRINT("in function");

  }

  if ((condition == false) && ((Intseq_step_memory + this_step_no)->internal_state == 1))
  {
    if(millis()<0?((Intseq_step_memory + this_step_no)->prev_millis-millis()>= timeout_inmillis):(millis() - ((Intseq_step_memory + this_step_no)->prev_millis)>= timeout_inmillis))
    {

      *seq_step_no = true_timeout_step_no;
      (Intseq_step_memory + this_step_no)->internal_state = 0;

      DPRINTln("Current Step No ");
      DPRINT(*seq_step_no);
      DPRINTln();
    }

  }
  if ((condition == true) && ((Intseq_step_memory + this_step_no)->internal_state == 1))
  {

    (Intseq_step_memory + this_step_no)->internal_state = 0;
    *seq_step_no = true_step_no;

    DPRINT("Current Step No ");
    DPRINT(*seq_step_no);
    DPRINTln();
  }
}

void libMultiSeqFuncCallWithBoolReturn(int *seq_step_no, struct condn_func_data *Intseq_step_memory, int this_step_no, bool (*callbackfunction)(), long timeout_inmillis, int true_step_no, int true_timeout_step_no)
{
 
  if ((this_step_no == *seq_step_no) && ((Intseq_step_memory + this_step_no)->internal_state == 0))
  {
    (Intseq_step_memory + this_step_no)->internal_state = 1;
    (Intseq_step_memory + this_step_no)->prev_millis = millis();
    (Intseq_step_memory + this_step_no)->callback_func_result = callbackfunction();

  }

  if (((Intseq_step_memory + this_step_no)->callback_func_result == false) && ((Intseq_step_memory + this_step_no)->internal_state == 1))
  {
    if(millis()<0?((Intseq_step_memory + this_step_no)->prev_millis-millis()>= timeout_inmillis):(millis() - ((Intseq_step_memory + this_step_no)->prev_millis)>= timeout_inmillis))
    {
      *seq_step_no = true_timeout_step_no;
      (Intseq_step_memory + this_step_no)->internal_state = 0;

      DPRINTln("Current Step No ");
      DPRINT(*seq_step_no);
      DPRINTln();
    }

  }
  if (((Intseq_step_memory + this_step_no)->callback_func_result == true) && ((Intseq_step_memory + this_step_no)->internal_state == 1))
  {

    (Intseq_step_memory + this_step_no)->internal_state = 0;
    *seq_step_no = true_step_no;

    DPRINT("Current Step No ");
    DPRINT(*seq_step_no);
    DPRINTln();
  }
}
