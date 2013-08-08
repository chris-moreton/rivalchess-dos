#define DOUBLE 0
#define SINGLE 1
#define LEFT 0
#define RIGHT 1

#define DVert 186
#define SVert 179
#define DHoriz 205
#define SHoriz 196
#define DTLeft 201
#define DBLeft 200
#define DTRight 187
#define DBRight 188
#define STLeft 218
#define SBLeft 192
#define STRight 191
#define SBRight 217
#define DCross 206
#define SCross 197
#define DVRSplit 204
#define DVLSplit 185
#define DHDSplit 203
#define DHUSplit 202
#define SVRSplit 195
#define SVLSplit 180
#define SHDSplit 194
#define SHUSplit 193

void textbox(char type, int x, int y, int sizex, int sizey);
void joinvert(char type1, char type2, int x, int y, int length);
void clear_area(int x, int y, int sizex, int sizey);