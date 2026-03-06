#ifndef SUB_TOOL_H
#define SUB_TOOL_H
int getfileLinesNumber(const char *filename);
void viewAll(const char *filename);
void viewLine(const char *filename, int target);
void viewFirstNLines(const char *filename, int num);
void viewLastNLines(const char *filename, int num);
void InsertEndLineOld(const char *filename, char *line);
void InsertEndLineNew(const char *filename,const char *outfile, char *line);
void EditLineOld(const char *filename,const char *line, int target);
void EditLineNew(const char *filename,const char *outfile,char *line, int target);
#endif