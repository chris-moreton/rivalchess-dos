int kinglet_evaluate(struct postype *pos, char depth);
void kinglet_quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path);
void kinglet_minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char extend);