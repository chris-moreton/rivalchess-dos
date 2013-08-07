void makemv(mvtype mv);
int __near evaluate(struct postype *pos);
int kinglet_evaluate(struct postype *pos, char depth);
void take_back(void);
void menu_option(unsigned char number);
void static __near check_time(struct pathtype *path);
void static __near quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path,
	  char lastmovecheck);
void static __near minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char lastmovecheck,
	  char todepth);
void kinglet_quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path);
void kinglet_minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path,
	  char todepth);
void solveminimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path,
	  char lastmovecheck);
char get_opening(mvtype *move);
mvtype get_computer_move(struct postype brd);
void solvey(void);