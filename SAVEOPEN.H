int FAR DoFileOpenDlg (HANDLE hInst, HWND hWnd, char *szFileSpecIn, 
                       char *szDefExtIn, WORD wFileAttrIn, char *szFileNameOut,
                       POFSTRUCT pof);
int FAR DoWildFileOpenDlg (HANDLE hInst, HWND hWnd, char *szFileSpecIn, 
                       char *szDefExtIn, WORD wFileAttrIn, char *szFileNameOut,
                       POFSTRUCT pof);
int FAR DoFileSaveDlg (HANDLE hInst, HWND hWnd, char *szFileSpecIn, 
                       char *szDefExtIn, WORD *pwStatusOut, char *szFileNameOut,
                       POFSTRUCT pof);

#define FILESAVE 270
#define FILEOPEN 271
#define WILDFILEOPEN 272
