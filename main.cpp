

/*-----Prototype Declaration----------*/
#include<dos.h>
#include<io.h>
#include<conio.h>
#include<dirent.h>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<string>
#include<process.h>
#include<stdlib.h>
#include<dir.h>
/*prototype declaration ends here-------*/


#define DIRNAME "C:\\Documents and Settings\\All Users\\Application Data\\PC_Cleaner"
/* ---------- prototype Declaration ends here -------------- */

/* ---------- Function prototype ------------*/
void Initialize();
void WelcomeScreen();
void Components();
void getDate();
void LogFile(char *s);
void ClickEvent();
void whatWillBeNext(char *s);
void about();
void driverS();
void silentOperation(char *path);
void adminOperation(char *s);

/*--------Function prototype ends here-------------*/

/* Global Variable Declaration ----------- */

char osDependentFilePath1[100]="C:\\ProgramData\\PC_Cleaner\\", osDependentFilePath2[100]="C:\\Documents and Settings\\All Users\\Application Data\\PC_Cleaner\\",UserName[100],drives[50];
char actualDate[20],actualTime[20];
/* ----------Global Variable Declaration ends here ---------- */

/* ---------- MAIN function -------------*/
int main()
{
    initwindow(930,600,"PC Cleaner");
    mkdir(DIRNAME);
    
    Initialize();
    WelcomeScreen();
    driverS();
    Components();
    ClickEvent();
    getch();
    closegraph();
    return 0;
}
/* ------------- MAIN function ends here ---------- */

/*--------- Initialize starts here ------------- */
void Initialize()
{
     setfillstyle(8,8);
     bar(0,0,getmaxx(),getmaxy());
     settextstyle(0,0,3);
     outtextxy(165,100,"Initializing Environment");
     outtextxy(290,225,"Loading");
     setfillstyle(1,0);
     int k;
     bar(480,getmaxy()/3+30,627,getmaxy()/3+47);
     for(int i=480,k=1;i<621;i+=5,++k)
     {
             setfillstyle(1,3);
             bar(i,getmaxy()/3+30,i+5,getmaxy()/3+47);
             delay(200);
             {
                        int j= (int)((float)k/29 *100);
                        char s[3];
                        sprintf(s,"%d",j);
                        strcat(s,"%");
                        setbkcolor(3);
                        setcolor(YELLOW);
                        settextstyle(0,0,2);
                        outtextxy(678,getmaxy()/3+30,s);
             }
     }
     delay(100);
     char deleteallfile[200];
     FILE *del; 
     strcpy(deleteallfile,osDependentFilePath1);
     strcat(deleteallfile,"del.bat");
     del = fopen(deleteallfile,"w+");
     fprintf(del,"if exist %sCleaner.bat del %sCleaner.bat\nif exist %srefresh.bat del %srefresh.bat\nif exist %sDefrag.bat del %sDefrag.bat\nif exist %ssilent_operation.vbs del %ssilent_operation.vbs\ndel %s",osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,osDependentFilePath1,deleteallfile);
     fclose(del);     
     system(deleteallfile);
}
/* -------- Initialization ends here ----------- */

/* ------- WelcomeScreen Starts here -------------*/
void WelcomeScreen()
{
     char s[100];
     {
          strcpy(s,osDependentFilePath1);
          strcat(s,"Ostest.bat");
          
          FILE *testOS=fopen(s,"w+");
          if(testOS==NULL)
          {
              strcpy(osDependentFilePath1,osDependentFilePath2);
          }
          else
          {
              fprintf(testOS,"@echo off\ndel %s",s);
              fclose(testOS);
              system("C:\\ProgramData\\PC_Cleaner\\Ostest.bat");
          }         
          
     }
     getDate();                    
     setfillstyle(1,5);
     bar(0,0,getmaxx(),getmaxy());
     settextstyle(1,0,3);
     setbkcolor(5);
     setcolor(15);
     outtextxy(340,50,"Hi!");
     setcolor(14);
     outtextxy(395,50,UserName);
     setcolor(3);
     outtextxy(230,90,"Welcome To PC Cleaner");
     setcolor(WHITE);
     outtextxy(75,250,"Input Your Password: ");
     strcpy(s,osDependentFilePath1);
     strcat(s,"password.bat");
     FILE *password=fopen(s,"w+");
     fprintf(password,"@echo off\ntitle User Interaction: Input Your Password\nset /p p=\"Input Your PassWord: \"\nif exist %spassword.txt (set /p c=<%spassword.txt) else ( echo %cp%c >%spassword.txt\necho new>%sfound.txt\ndel %s\nexit)\nif %cp%c==%cc%c (echo Yes>%sfound.txt)else (echo No>%sfound.txt)\ndel %s",osDependentFilePath1,osDependentFilePath1,37,37,osDependentFilePath1,osDependentFilePath1,s,37,37,37,37,osDependentFilePath1,osDependentFilePath1,s);
     fclose(password);
     system(s);
     delay(300);
     strcpy(s,osDependentFilePath1);
     strcat(s,"found.txt");
     FILE *confirmation=fopen(s,"r+");
     char c;
     int i;
     if((c=getc(confirmation))=='Y')
     {
         fclose(confirmation);
         setcolor(2);
         outtextxy(430,251,"PW MATCHED");
         settextstyle(3,0,3);
         setcolor(14);
         outtextxy(290,290,"Congratulations!!!");
         delay(1000);
     }
     else if(c=='N')
     {
         fclose(confirmation);         
         setcolor(4);
         outtextxy(430,250,"PW MISMATCHED");
         delay(1000);
         cleardevice();
         setfillstyle(8,3);
         settextstyle(6,0,5);
         setcolor(8);
         outtextxy(getmaxx()/3,250,"Exiting");
         int x=0;
         for(i=1;i<=5;i++)
         {
             x=20*i;
             setfillstyle(1,8);
             bar(490+x+10,280,490+x+20,285);
             delay(700);
         }
         system("del C:\\ProgramData\\PC_Cleaner\\found.txt C:\\ProgramData\\PC_Cleaner\\username.txt");
         LogFile("Tried To LOGIN with WRONG Password");
         exit(1);
     }
     
     else if(c=='n')
     {
         fclose(confirmation);  
         setcolor(9);
         outtextxy(430,250,"Password is Now SET.");
         settextstyle(3,0,3);
         setcolor(14);
         outtextxy(290,290,"Congratulations!!!");
         setcolor(3);
         outtextxy(210,340,"Remember For Future Login");
         delay(1500);
     }
     
     system("del C:\\ProgramData\\PC_Cleaner\\found.txt C:\\ProgramData\\PC_Cleaner\\username.txt");
     
     
}
/* ----------welcomeScreen() ends here --------------*/

/*=------getDate() starts here ------------ */
void getDate()
{
     char time[10],Date[20],s[30];
     strcpy(s,osDependentFilePath1);
     strcat(s,"Username.bat");
     FILE* userName=fopen(s,"w+");
     fprintf(userName,"@echo off\nhostname>%susername.txt\necho %cdate%c %ctime%c>%sdateTime.txt\ndel %s",osDependentFilePath1,37,37,37,37,osDependentFilePath1,s);
     fclose(userName);
     system(s);
     char c;
     strcpy(s,osDependentFilePath1);
     strcat(s,"username.txt");
     FILE *user=fopen(s,"r+");
     int i=0;
     while((c=getc(user))!='-')
     {
           UserName[i++]=c;
           UserName[i]='\0';
     }
     fclose(user);
     strcpy(s,osDependentFilePath1);
     strcat(s,"dateTime.txt");
     FILE *dT=fopen(s,"r+");
     int space=0;i=0;
     while((c=getc(dT))!='.')
     {
           actualDate[i++]=c;
           actualDate[i]='\0';
     }
     fclose(dT);           
     char systemToPerform[200];
     char useR[100],Dtime[100];
     strcpy(useR,osDependentFilePath1);
     strcat(useR,"Username.txt ");
     strcpy(Dtime,osDependentFilePath1);
     strcat(Dtime,"dateTime.txt");
     strcat(useR,Dtime);
     strcpy(systemToPerform,"del ");
     strcat(systemToPerform,useR);
     system(systemToPerform);
}
/*======end of getDate()---------*/


/*--------- Components()=------------ starts------*/

void Components()
{
     getDate();
     LogFile("USER");
     cleardevice();
     setfillstyle(1,BLACK);
     bar(0,0,930,600);
     //Upper tab
     {
          setfillstyle(1,3);
          bar(0,0,930,40);
          settextstyle(0,0,3);
          setcolor(WHITE);
          setbkcolor(BLACK);
          outtextxy(330,12,"PC Cleaner");
          //for exit button
          //setfillstyle(1,0);
          setcolor(RED);
          setlinestyle(SOLID_LINE,1,3);
          rectangle(getmaxx()-27,2,getmaxx()-2,17);
          //for cross lines in exit box
	      setcolor(RED);
	      setlinestyle(SOLID_LINE,1,2);
	      line(getmaxx()-27,2,getmaxx()-2,17);
	      line(getmaxx()-2,2,getmaxx()-27,17);
     }
     // Side Tab starts
     {
          setfillstyle(1,RED);
          bar(0,41,130,574);  
          setcolor(RED);
          line(240,41,240,574); //to show where it's working LINE shows
          /*1 -> CLEANER*/
          {
              setcolor(3);
              setlinestyle(SOLID_LINE,1,2);
              rectangle(5,45,125,145);
              setfillstyle(1,0);
              bar(10,50,120,140);
              settextstyle(1,0,1);
              setcolor(WHITE);
              outtextxy(18,90,"Cleaner");
          }
          
          
          /*2 -> System*/
          {
              setcolor(3);
              setlinestyle(SOLID_LINE,1,2);    
              rectangle(5,150,125,250);
              setfillstyle(1,0);
              bar(10,155,120,245);
              setcolor(WHITE);
              outtextxy(18,195,"System");
          }
          
          /*3 -> Refresh*/
          {
              setcolor(3);
              setlinestyle(SOLID_LINE,1,2);    
              rectangle(5,255,125,355);
              setfillstyle(1,0);
              bar(10,260,120,350);
              setcolor(WHITE);
              outtextxy(18,300,"Refresh");
          }
          
          /*4 ->Q. Defrag*/
          {
              setcolor(3);
              setlinestyle(SOLID_LINE,1,2);
              rectangle(5,360,125,460);
              setfillstyle(1,0);
              bar(10,365,120,455);
              setcolor(WHITE);
              outtextxy(11,405,"Q.defrag");
          }
          /*5 -> Help */
          {
              setcolor(3);
              setlinestyle(SOLID_LINE,1,2);
              rectangle(5,465,125,565);
              setfillstyle(1,0);
              bar(10,470,120,560);
              setcolor(WHITE);
              outtextxy(18,510,"Help");
          }
          
          
     } 
     // side tab ends
     
     //lower tab starts here
     setfillstyle(1,3);
     bar(0,575,930,600);
     char s[50];
     strcpy(s,"Logged in As--> ");
     strcat(s,UserName);
     char timeDatE[100];
     strcpy(timeDatE,actualDate);
     setbkcolor(3);
     setcolor(BLACK);
     settextstyle(8,0,2);
     outtextxy(10,580,s);
     outtextxy(698,580,timeDatE);
     
}
/*--------Components() ends-----------*/

/*====== logFile() starts here -------------*/
void LogFile(char *s)
{
     char path[90];
     strcpy(path,osDependentFilePath1);
     strcat(path,"PC_Cleaner_Log.txt");
     getDate();
     FILE *log=fopen(path,"a+");
     rewind(log);
     if(strcmp(s,"USER")==0)
     {
            fprintf(log,"Logged in @");                
            fprintf(log,actualDate);
            fprintf(log,"\n");
     }
     else if(strcmp(s,"EXIT")==0)
     {
            fprintf(log,"Logged Out@"); 
            getDate();               
            fprintf(log,actualDate);
            fprintf(log,"\n");
     }
     else if(strcmp(s,"Tried To LOGIN with WRONG Password")==0)
     {
            fprintf(log,s);
            fprintf(log," @ %s",actualDate);
            fprintf(log,"\n");
     }            
     else if(strcmp(s,"REFRESH")==0)
     {
            fprintf(log,"%s done @%s\n","Refreshing",actualDate);
     }
     else if(strcmp(s,"CLEANER")==0)
     {
            fprintf(log,"%s done @%s\n","Cleaning",actualDate);
     }
     else if(strcmp(s,"Logged off")==0)
     {
          fprintf(log,"%s of your PC is done @%s\n",s,actualDate);
     }
     else if(strcmp(s,"Restart")==0)
     {
          fprintf(log,"%s of your PC is done @%s\n",s,actualDate);
     }     
     else if(strcmp(s,"Shutdown")==0)
     {
          fprintf(log,"Shut Down of your PC is done @%s\n",actualDate);
     }     
     else if(strcmp(s,"DEFRAG")==0)
     {
          fprintf(log,"Defragment done @%s\n",actualDate);
     }
     fclose(log);
     
}
/*----------LogFile() ends here-----------*/

/*-------------- clickEvent() ======= starts here----------*/
void ClickEvent()
{
     
     int x,y;
     while(1)
     {
             x=mousex();
             y=mousey();
             
             /* for exit button------*/
             if(x>=getmaxx()-27&& x<=getmaxx()-2 && y>=2 && y<=17)
             {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                           LogFile("EXIT");                                       
                           exit(1);
                    }
                    
             }
             else
             {
                    setcolor(RED);
                    setlinestyle(SOLID_LINE,1,3);
                    rectangle(getmaxx()-27,2,getmaxx()-2,17);
	                setcolor(RED);
	                setlinestyle(SOLID_LINE,1,2);
	                line(getmaxx()-27,2,getmaxx()-2,17);
                    line(getmaxx()-2,2,getmaxx()-27,17);
              }
             
             if(x>=5 && x<=125 && y>=45 && y<=145)
             {
                     if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               setfillstyle(1,BLACK);
                               bar(130,45,238,574);
                               setcolor(3);
                               int p[8]={235,45,235,145,135,(45+145)/2,235,45};
                               fillpoly(4,p);
                               clearmouseclick(WM_LBUTTONDOWN);
                               whatWillBeNext("CLEANER");
                     }
             }
                     
             if(x>=5 && x<=125 && y>=150 && y<=250 )
             {
                     if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               setfillstyle(1,BLACK);
                               bar(130,45,238,574);   
                               setcolor(3);                   
                               int p[8]={235,150,235,250,135,(150+250)/2,235,150};                      
                               fillpoly(4,p);
                               clearmouseclick(WM_LBUTTONDOWN);
                               whatWillBeNext("SYSTEM");
                     }
             }
             if(x>=5 && x<=125 && y>=255 && y<=355)
             {
                     if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               setfillstyle(1,BLACK);
                               bar(130,45,238,574);   
                               setcolor(3);                   
                               int p[8]={235,255,235,355,135,(255+355)/2,235,255};                      
                               fillpoly(4,p);
                               clearmouseclick(WM_LBUTTONDOWN);
                               whatWillBeNext("REFRESH");
                     }
             }
             if(x>=5 && x<=125 && y>=360 && y<=460)
             {
                     if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               setfillstyle(1,BLACK);
                               bar(130,45,238,574);   
                               setcolor(3);                   
                               int p[8]={235,360,235,460,135,(360+460)/2,235,360};                      
                               fillpoly(4,p);
                               clearmouseclick(WM_LBUTTONDOWN);
                               
                               whatWillBeNext("DEFRAG");
                     }
             }
             if(x>=5 && x<=125 && y>465 && y<=565)
             {
                     if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               setfillstyle(1,BLACK);
                               bar(130,45,238,574);   
                               setcolor(3);                   
                               int p[8]={235,465,235,565,135,(465+565)/2,235,465};                      
                               fillpoly(4,p);
                               clearmouseclick(WM_LBUTTONDOWN);
                               whatWillBeNext("HELP");
                     }
             }
             else if(ismouseclick(WM_LBUTTONDOWN))
             clearmouseclick(WM_LBUTTONDOWN);
     }
}
     
/*---------ClickEvent()====ends---------*/
void whatWillBeNext(char *s)
{
     setfillstyle(1,3);
     bar(245,42,930,573);
     if(strcmp(s,"CLEANER")==0)
     {
             setcolor(WHITE);
             int p[10]={390,155,800,155,800,190,390,190,390,155};
             drawpoly(5,p);                  
             setcolor(BLACK);
             outtextxy(395,163,"Clean %temp%,Recent,Temp,prefetch");
             int x ,y ;
             while(1)
             {
                     x = mousex();
                     y = mousey();
                     if(x>=390 && x<=800 && y>=155 && y <=190 ) 
                     {
                               if(ismouseclick(WM_LBUTTONDOWN))
                               {
                                      char x[90];
                                      strcpy(x,osDependentFilePath1);
                                      strcat(x,"Cleaner.bat");      
                                      LogFile("CLEANER");
                                      FILE *cleaner;   
                                      adminOperation(x); 
                                      cleaner = fopen(x,"a+");
                                      fprintf(cleaner,"DEL /S /F /Q \"%cUSERPROFILE%c\\Local\\Temp\\*.*\"\ndel /s /q \"%cuserprofile%c\\cookies\\*.*\"\ndel /f /q %cwindir%c\\Prefetch\\*.*\ndel /f /q %cwindir%c\\Temp\\*.*\ndel /s /f /q %cUSERPROFILE%c\\Recent\\*.*\ndel /f /s /q %ctemp%c\\*.*\ncd %cuserprofile%c\\recent\ndel /f /s /q *.*\ncd %cwindir%c/Prefetch\nRMDIR /S /Q \"%cwindir%c/Prefetch\"",37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37);
                                      fprintf(cleaner,"\ndel %s%s %s",osDependentFilePath1,"silentOperation.vbs",x);
                                      fclose(cleaner);
                                      silentOperation(x);
                                      char s[200];
                                      strcpy(s,osDependentFilePath1);
                                      strcat(s,"silent_operation.vbs");
                                      system(s);
                                      setcolor(YELLOW);
                                      outtextxy(450,400,"Cleaning Going On");
                                      delay(5000);
                                      setcolor(BLUE);
                                      outtextxy(450,400,"Operation Successful");
                                      delay(2000);
                                      clearmouseclick(WM_LBUTTONDOWN);
                                      strcpy(s,"del ");
                                      strcat(s,osDependentFilePath1);
                                      strcat(s,"silent_operation.vbs");
                                      system(s);
                                      whatWillBeNext("CLEANER");
                                      
                               }
                     }
                     else if(ismouseclick(WM_LBUTTONDOWN))
                     {
                               ClickEvent();
                     }
                     
             }
     }
     else if(strcmp(s,"SYSTEM")==0)
     {
          
             setcolor(BLACK);
             rectangle(390,235,510,265);
             outtextxy(395,240,"Shut Down");
             rectangle(530,235,650,265);
             outtextxy(535,240," Restart");
             rectangle(670,235,790,265);
             outtextxy(675,240," Log Off");
             int x, y;
             while(1)
             {
                     x = mousex();
                     y = mousey();
                     if(x >= 390 && x<=510 && y>=235 && y<=265)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                 char x[90];
                                 strcpy(x,osDependentFilePath1);
                                 strcat(x,"del.bat");      
                                 LogFile("Shutdown");
                                 FILE *del;   
                                 del = fopen(x,"w+");
                                 fprintf(del,"shutdown -f -s -t 1\ndel %s",x);
                                 fclose(del);
                                 clearmouseclick(WM_LBUTTONDOWN);
                                 LogFile("EXIT");
                                 system(x);
                          }
                     }
                     else if(x >= 530 && x<=650 && y>=235 && y<=265 )
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                 char x[90];
                                 strcpy(x,osDependentFilePath1);
                                 strcat(x,"del.bat");      
                                 LogFile("Restart");
                                 FILE *del;   
                                 del = fopen(x,"w+");
                                 fprintf(del,"shutdown -f -r -t 1\ndel %s",x);
                                 fclose(del);
                                 clearmouseclick(WM_LBUTTONDOWN);
                                 LogFile("EXIT");                                 
                                 system(x);
                          }
                     }
                     else if( x >= 670 && x<=790 && y>= 235 && y<=265)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                 char x[90];
                                 strcpy(x,osDependentFilePath1);
                                 strcat(x,"del.bat");      
                                 LogFile("Logged off");
                                 FILE *del;   
                                 del = fopen(x,"w+");
                                 fprintf(del,"shutdown -f\ndel %s",x);
                                 fclose(del);
                                 LogFile("EXIT");                                 
                                 clearmouseclick(WM_LBUTTONDOWN);
                                 system(x);
                          }
                     }     
                     else if(ismouseclick(WM_LBUTTONDOWN))
                     {
                          ClickEvent();
                     }
                     clearmouseclick(WM_LBUTTONDOWN);
             }  
     }
     else if(strcmp(s,"REFRESH")==0)
     {
             setcolor(WHITE);
             int p[10]={390,155,800,155,800,190,390,190,390,155};
             drawpoly(5,p);                  
             setcolor(BLACK);
             outtextxy(395,163,"  Refresh Full Hard Drive Now");
             int x,y;
             while(1)
             {
                     x = mousex();
                     y = mousey();
                     if(x>=390 && x<=800 && y>=155 && y<=190)
                     {
                             
                             if(ismouseclick(WM_LBUTTONDOWN))
                             {
                                      char path[90];
                                      strcpy(path,osDependentFilePath1);
                                      strcat(path,"refresh.bat");
                                      FILE *drive=fopen(path,"w+");
                                      fprintf(drive,"@echo off\n");
                                      int i;
                                      for(i=0;i<strlen(drives);i++)
                                      {
                                                  fprintf(drive,"tree %c:\n",drives[i]);
                                      }
                                      fprintf(drive,"del %s%s %s",osDependentFilePath1,"silent_operation.vbs",path);
                                      fclose(drive);
                                      strcpy(path,osDependentFilePath1);
                                      strcpy(path,"silent_operation.vbs");
                                      system(path);
                                      setcolor(YELLOW);
                                      outtextxy(450,400,"Refreshing Going On");
                                      delay(5000);
                                      LogFile("REFRESH");
                                      setcolor(BLUE);
                                      outtextxy(450,400,"Operation Successful");
                                      delay(2000);
                                      clearmouseclick(WM_LBUTTONDOWN);
                                      whatWillBeNext("REFRESH");
                             }
                             
                     }
                     else if(ismouseclick(WM_LBUTTONDOWN))
                     {
                             ClickEvent();
                     }
                             
             }
                                               
             
     }  
     else if(strcmp(s,"DEFRAG")==0)
     {
             int dlen=strlen(drives);
             int i=0;
             setcolor(WHITE);
             int p[10]={390,155,800,155,800,190,390,190,390,155};
             drawpoly(5,p);                  
             setcolor(BLACK);
             outtextxy(395,163,"  Defrag Full Hard Drive Now");
             int x,y;
             while(1)
             {
                     x = mousex();
                     y = mousey();
                     if(x >= 390 && x<= 800 && y>= 155 && y<=190)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                  LogFile("DEFRAG");
                                  char s[90];
                                  strcpy(s,osDependentFilePath1);
                                  strcat(s,"Defrag.bat");      
                                  LogFile("Defrag");
                                  FILE *defrag;   
                                  adminOperation(s); 
                                  defrag = fopen(s,"a+");  
                                  fprintf(defrag,"defrag /C /H /V\ndel %s ",s);
                                  fclose(defrag);
                                  silentOperation(s);
                                  strcpy(s,osDependentFilePath1);
                                  strcat(s,"silentOperation.vbs");
                                  char y[200];
                                  strcat(y,"del ");
                                  strcat(y,s);
                                  system(y);
                                  setcolor(YELLOW);
                                  outtextxy(450,400,"Defragment Going On");
                                  delay(5000);
                                  setcolor(BLUE);
                                  outtextxy(450,400,"Operation Successful");
                                  delay(2000);
                                  clearmouseclick(WM_LBUTTONDOWN);
                                  char fileP[200];
                                  FILE *dele;
                                  strcat(fileP,osDependentFilePath1);
                                  strcat(fileP,"Defrag.bat");
                                  dele = fopen(fileP,"w+");
                                  fprintf(dele,"del %ssilent_operation.vbs\ndel %sDefrag.bat",osDependentFilePath1,osDependentFilePath1);
                                  fclose(dele);
                                  system(fileP);
                                  whatWillBeNext("DEFRAG");
                                  
                                  
                          }      
                     }    
                     else if(ismouseclick(WM_LBUTTONDOWN))
                          ClickEvent();
             }
                                
     }  
     else if(strcmp(s,"HELP")==0)
     {
             setcolor(BLACK);
             rectangle(390,235,490,265);
             rectangle(510,235,610,265);
             rectangle(630,235,730,265);
             rectangle(390,295,730,325);
             outtextxy(400,240," About");
             outtextxy(520,240,"  Log ");
             outtextxy(640,240," Help ");
             outtextxy(440,300,"   Delete Log File   ");
             int x,y;
             while(1)
             {
                     x=mousex();
                     y=mousey();
                     
                     if(x>=390 &&x <=490 && y>=235 && y<=265)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                                about();
                          clearmouseclick(WM_LBUTTONDOWN);
                     }
                     else if(x>=510 && x<=610 && y>=235 && y<=265)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                 char path[90];
                                 strcpy(path,osDependentFilePath1);
                                 strcat(path,"PC_Cleaner_Log.txt");
                                 system(path);
                                 clearmouseclick(WM_LBUTTONDOWN);                        
                          }
                          
                     }
                     else if(x>=390 && x<=730 && y>=295 && y<=325)
                     {
                          if(ismouseclick(WM_LBUTTONDOWN))
                          {
                                 char path[90];
                                 strcpy(path,osDependentFilePath1);
                                 strcat(path,"PC_Cleaner_Log.txt");
                                 char del[90];
                                 strcat(del,"del ");
                                 strcat(del, path);
                                 system(del);
                                 FILE *f = fopen(path,"w+");
                                 fclose(f);
                                 clearmouseclick(WM_LBUTTONDOWN);  
                          }
                     }
                     else if(ismouseclick(WM_LBUTTONDOWN))
                     {
                           ClickEvent();
                     }
             }
     }                    
}

/*---about Function()------*/


void about()
{
     setfillstyle(1,3);
     bar(245,42,930,573);
     setcolor(BLACK);
     outtextxy(540,120,"©");
     setcolor(WHITE);
     outtextxy(480,150,"Reserved By   ");
     outtextxy(400,190,"Syed Sirajul Islam Anik");
     outtextxy(440,230,"   CE - 11017 ");
     outtextxy(440,280,"  Dept. Of CSE");
     outtextxy(270,320,"  Mawlana Bhashani Science And Technology University");
}
/*-------admin operation starts here-------*/


/*---driver function()-----*/


void driverS()
{
     char path[100];
     strcpy(path,osDependentFilePath1);
     strcat(path,"Drives.bat");
     FILE *drive=fopen(path,"w+");
     fprintf(drive,"@echo off\n");
     int i;
     for(i=0;i<24;i++)
     {
            fprintf(drive,"if exist %c: (echo %c>>%sgetDriveList.txt) else ( del %s\nexit)\n",67+i,67+i,osDependentFilePath1,path);
     }
     fclose(drive);
     system(path);
     strcpy(path,osDependentFilePath1);
     strcat(path,"getDriveList.txt");
     FILE *f=fopen(path,"r+");
     char c;
     i=0;
     rewind(f);
     while(!feof(f))
     {
            c=getc(f);
            if(c=='\n')
               continue;
            if(c>='A' && c<='Z')
            {
                                             
                 drives[i++]=c;
                 drives[i]='\0';
            }
     }
     fclose(f);
     char del[30];
     strcpy(del,"del ");
     strcat(del,path);
     system(del);
}
/*----driverS() ends----*/

/*------silent operation function starts here----------*/
void silentOperation(char *foundPath)
{
     char p[90] ;
     strcpy(p,osDependentFilePath1);
     strcat(p,"silent_operation.vbs");
     FILE *sop=fopen(p,"w+");
     fprintf(sop,"Set WshShell = CreateObject(\"WScript.Shell\")\nWshShell.Run chr(34) & \"");
     fprintf(sop,foundPath);
     fprintf(sop,"\" & Chr(34), 0");
     fprintf(sop,"\nSet WshShell = Nothing");
     fclose(sop);
}
/*------------silent_operation ends here ------------*/
void adminOperation(char *s)
{
     FILE *admin;
     admin=fopen(s,"w+");
     fprintf(admin,"@echo off\ntitle admin right\n:: BatchGotAdmin\n:-------------------------------------\nREM  --> Check for permissions\n>nul 2>&1 \"%cSYSTEMROOT%c\\system32\\cacls.exe\" \"%cSYSTEMROOT%c\\system32\\config\\system\"\nREM --> If error flag set, we do not have admin.\nif '%cerrorlevel%c' NEQ '0' (\n    echo Requesting administrative privileges...\n    goto UACPrompt\n) else ( goto gotAdmin )\n\n:UACPrompt\n    echo Set UAC = CreateObject^(\"Shell.Application\"^) > \"%ctemp%c\\getadmin.vbs\"\n    echo UAC.ShellExecute \"%c~s0\", \"\", \"\", \"runas\", 1 >> \"%ctemp%c\\getadmin.vbs\"\n\n    \"%ctemp%c\\getadmin.vbs\"\n    exit /B\n\n:gotAdmin\n    if exist \"%ctemp%c\\getadmin.vbs\" ( del \"%ctemp%c\\getadmin.vbs\" )\n    pushd \"%cCD%c\"\n    CD /D \"%c~dp0\"\n:--------------------------------------\n",37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37);
     fclose(admin);
}
/*-------admin operation ends here --------*/
