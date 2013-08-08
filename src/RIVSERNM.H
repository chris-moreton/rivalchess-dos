void quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path,
	  char lastmovecheck);
int evaluate(struct postype *pos);
void minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char lastmovecheck,
	  char extend);
char get_opening(mvtype *move);
