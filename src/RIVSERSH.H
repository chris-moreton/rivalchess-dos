void shatranj_quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path,
	  char lastmovecheck);
int shatranj_evaluate(struct postype *pos, char depth);
void shatranj_minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char lastmovecheck,
	  char extend);
