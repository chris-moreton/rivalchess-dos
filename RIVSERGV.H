void giveaway_quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path);
int giveaway_evaluate(struct postype *pos, char depth);
void giveaway_minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char extend);
