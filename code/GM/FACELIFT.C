/*----------------------------------------------------------*/
/* Graphics Screen Display routines                         */
/* Include:  pal.h and graph.h                              */
/*----------------------------------------------------------*/

#include "gen.h"
#include "gmgen.h"
#include "palette.h"
#include "graph.h"
#include "facelift.h"

unsigned char FaceCols[MAXFACECOL];
unsigned char HiCols[4];

/*----------------ROUTINES FOR SCREENS FRONT END----------------*/

void BoxWithText(int x,int y,char *str,unsigned char *Cols)
  {
  int lp=-1;

  while (str[++lp]!=0);
  Line(x-1,y-1,x+lp*8,y-1,Cols[GREY4]);
  Line(x-1,y,x-1,y+8,Cols[GREY3]);
  BoxFill(x,y,x+lp*8,y+8,Cols[GREEN]);
  GWrite(x+1,y+1,Cols[BLACK],str);
  }

void DrawArrows(int x,int y,int blnum,char selected,unsigned char *Cols)
  {
  unsigned char left1,left2,left3,right1,right2,right3;
  int lp;

  switch(selected)
    {
    case LEFT :  left1=Cols[GREY1]; left2=(left3=Cols[RED3]); right1=(right2=Cols[RED1]); right3=Cols[RED2]; break;
    case RIGHT:  right1=Cols[GREY1]; right2=(right3=Cols[RED3]); left1=(left2=Cols[RED1]); left3=Cols[RED2]; break;
    case NONE :
    default   : left1=(right1=(left2=(right2=Cols[RED1]))); left3=(right3=Cols[RED2]); break;
    }
  for (lp=0;lp<7;lp++)
    {
    Line(lp+x-11,y+BLEN/2-lp,lp+x-11,y+BLEN/2+lp,left2);
    Line(x+blnum*BLEN+10-lp,y+BLEN/2-lp,x+blnum*BLEN+10-lp,y+BLEN/2+lp,right2);
    Point(lp+x-11,y+BLEN/2-lp,left1);
    Point(lp+x-11,y+BLEN/2+lp,left1);
    Point(x+blnum*BLEN+10-lp,y+BLEN/2-lp,right1);
    Point(x+blnum*BLEN+10-lp,y+BLEN/2+lp,right1);
    }
  Line(x-4,y+BLEN/2-6,x-4,y+BLEN/2+6,left3);
  Line(x+blnum*BLEN+3,y+BLEN/2-6,x+blnum*BLEN+3,y+BLEN/2+6,right3);
  }


// Draw border AROUND object at x,y with dimensions xlen,ylen
void drawborder(int x,int y,int xlen,int ylen,int xthick,int ythick,unsigned char *Cols)
  {
  Box(x-xthick-3,y-ythick-3,x+xlen+xthick+1,y+ythick+ylen+1,Cols[GREY3]);
  Box(x-xthick-2,y-ythick-2,x+xlen+xthick,y+ythick+ylen,Cols[GREY2]);
  BoxFill(x-xthick-1,y-ythick-1,x-1,y+ylen+ythick-1,Cols[GREY1]);
  BoxFill(x+xlen,y-ythick-1,x+xlen+xthick-1,y+ylen+ythick-1,Cols[GREY1]);
  if (xlen>0)
    {
    BoxFill(x,y-ythick-1,x+xlen,y-2,Cols[GREY1]);
    BoxFill(x,y+ylen,x+xlen,y+ylen+ythick-1,Cols[GREY1]);
    Line(x-1,y-1,x+xlen-1,y-1,Cols[GREY4]);
    }
  if (ylen>0) Line(x-1,y,x-1,y+ylen-1,Cols[GREY3]);
  }

void drawsurface(int x,int y,int xlen,int ylen,unsigned char *Cols)
  {
  Box(x-2,y-2,x+xlen+1,y+ylen+1,Cols[GREY3]);
  Box(x-1,y-1,x+xlen,y+ylen,Cols[GREY2]);
  BoxFill(x,y,x+xlen-1,y+ylen-1,Cols[GREY1]);
  }

void drawlistframe(int x,int y,int blnum,unsigned char *Cols)
  {
  drawborder(x,y,BLEN*blnum+1,BLEN,12,1,Cols);       //  Draw the bloc list
  Line(x+BLEN*blnum,y,x+BLEN*blnum,y+BLEN-1,Cols[GREY3]);
  DrawArrows(x,y,blnum,0,Cols);
  }

void SetCols(RGBdata *colors,unsigned char *Cols)
  {
  Cols[GREY1]=PalFindCol(33,33,33,colors);       //light gray (surfaces)
  Cols[GREY2]=PalFindCol(28,28,28,colors);       //a shade darker than above
  Cols[GREY3]=PalFindCol(23,23,23,colors);       //a shade darker than above
  Cols[GREY4]=PalFindCol(18,18,18,colors);       //a shade darker than above
  Cols[RED1]=PalFindCol(43,00,00,colors);        //medium red (buttons)
  Cols[RED2]=PalFindCol(28,00,00,colors);        //dark red (button sides)
  Cols[RED3]=PalFindCol(53,00,00,colors);        //bright red (pressed buttons)
  Cols[BLACK]=PalFindCol(00,00,00,colors);       //imitation LCD letters
  Cols[GREEN]=PalFindCol(8,48,24,colors);        //imitation LCD back-lighting

  HiCols[0]=Cols[GREY1];     //HIGHLIGHT BUTTONS:    0==background==light grey
  HiCols[1]=Cols[RED3];      //1==forground==bright red
  HiCols[2]=Cols[GREY1];     //2==button edge==background==lightgrey
  HiCols[3]=Cols[GREEN];     //3==picture==green
  }

void helpb(int x,int y, unsigned char col[4])
  {
  static char helpar[] = "         UUUUUUU@U]UUUWUTU��u_�UTUU��u]wUUUU��u_�UUUU��u]UUU�U���WUVU]UUUUUT)UUUUUUUh��������";
  draw4dat(x,y,helpar,35,10,col);
  }

void menub(int x,int y, unsigned char col[4])
  {
  static char menuar[] = "         UUUUUUU@UUUUUUUTU���]�UTUU��W��UUUU�����UUUU��W}�UU�U���]}UVUUUUUUUT)UUUUUUUh��������";
  draw4dat(x,y,menuar,35,10,col);
  }

void noneb(int x,int y, unsigned char col[4])
  {
  static char nonear[] = "         UUUUUUU@UUUUUUUTU�_]w�UTUU�u�wUUUUU�u���UUUU�u��UUU�U�_]w�UVUUUUUUUT)UUUUUUUh��������";
  draw4dat(x,y,nonear,35,10,col);
  }

void doneb(int x,int y, unsigned char col[4])
  {
  static char donear[] = "         UUUUUUU@UUUUUUUTU�_]w�UTUU�u�wUUUUU�u���UUUU�u��UUU�U�_]w�UVUUUUUUUT)UUUUUUUh��������";
  draw4dat(x,y,donear,35,10,col);
  }
