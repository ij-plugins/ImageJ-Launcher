/*
This is an application that can be used to launch Java 
applications by just clicking on a exe file.

You can rename launcher.exe to anything you want.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>

void deletenewlines(char* buffer)
{
  while(*buffer != '\0')
  {
    if (*buffer == '\n')
    {
      *buffer = '\0';
      return;
    }
    ++buffer;
  }
}

void getExecutable(char *result, char* lpCmdLine)
{ //returns the name of the executable appended with .cfg
  const char* constCommandLine = ::GetCommandLine();
  char* commandLine = new char[strlen(constCommandLine)+1];
  strcpy(commandLine,constCommandLine);

  // Remove lpCmdLine from back
  int lastpos = strlen(commandLine)-strlen(lpCmdLine);
  commandLine[lastpos] = '\0';
  lastpos--;
  while(commandLine[lastpos]=='\"' || commandLine[lastpos]==' ')
  {
    commandLine[lastpos]='\0';
    lastpos--;
  }  
  int firstpos = lastpos;
  while(commandLine[firstpos] > 0 && commandLine[firstpos]!='\\' 
    && commandLine[firstpos]!=':' && commandLine[firstpos]!='/')
    firstpos--;

  strcpy(&result[0], &commandLine[firstpos+1]);
  int resultlength = strlen(result);

  bool containsdot = false;
  for (int i=0; i<resultlength; i++)
    if (result[i]=='.')
      containsdot = true;

  if (containsdot)
    while(result[resultlength]!='.')
      resultlength--;

  strcpy(&result[resultlength],".cfg");

  resultlength = strlen(result);  
  result[resultlength+1] = '\0';
}

void getExecutablePath(char *result, char* lpCmdLine)
{ // returns the path to the executable
  const char* constCommandLine = ::GetCommandLine();
  char* commandLine = new char[strlen(constCommandLine)+1];
  strcpy(commandLine,constCommandLine);

  // Remove lpCmdLine from back
  int lastpos = strlen(commandLine)-strlen(lpCmdLine);
  commandLine[lastpos] = '\0';
  lastpos--;
  while(commandLine[lastpos]!='\\')
  {
    commandLine[lastpos]='\0';
    lastpos--;
  }  
  int firstpos = 0;
  while(commandLine[firstpos]=='\"' || commandLine[firstpos]==' ')
    firstpos++;

  strcpy(&result[0], &commandLine[firstpos]);
  int resultlength = strlen(result);
  resultlength = strlen(result);  
  result[resultlength+1] = '\0';
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  FILE* file = NULL;

  // Look for config file with same name as executable but with cfg suffix.
  char executable[1000];
  getExecutable(executable,lpCmdLine);
  char executablePath[1000];
  getExecutablePath(executablePath,lpCmdLine);
  char executablePathWithName[1000];

  file = fopen(executable,"rt"); // Check for the executable.cfg -file in the current working directory
  char cfgFileName[1000];
  if (file)
    strcpy(cfgFileName,executable);

  if (!file)
  { // Check for the cfg executable.file in the directory of the application
    sprintf(executablePathWithName,"%s%s",executablePath,executable);
  file = fopen(executablePathWithName,"rt");
    strcpy(cfgFileName, executablePath);
  _chdir(executablePath);
  }

  // Open default config file
  if (!file)
  {
    file = fopen("ImageJ.cfg","rt");
    strcpy(cfgFileName, "ImageJ.cfg");
  }

  if (file==NULL)
  {
    char temp[1000];
    sprintf(temp,"Could not find file %s or ImageJ.cfg. Please\n" 
      "reinstall the application.", executable);
    MessageBox(NULL, temp,"Error loading configuration file", MB_OK);
    return 1;
  }

  char buffer[10000];

  // Read new directory from config file. We will change to this dir
  // before starting execution.
  fgets(buffer,10000,file);
  deletenewlines(buffer);
  int result = _chdir(buffer);

  if (result!=0)
  {
    char temp[1000];
    sprintf(temp, "Could not find the directory given in %s\n" \
      "Please reinstall the application.", cfgFileName);
    MessageBox(NULL, temp, "Error changing directory",MB_OK);
    return 2;
  }

  // Read the name of the executable. Is usually java.exe or javaw.exe
  char exe[1000];
  fgets(exe,1000,file);
  deletenewlines(exe);

  // Read any extra parameters you want to give to the program.
  // such as -jar parameters.
  char parameter[1000];
  fgets(parameter,1000,file);
  deletenewlines(parameter);

  // Add parameters given to the exe
  strcat(parameter," ");
  strcat(parameter, lpCmdLine);

  char thecwd[1000];
  _getcwd(thecwd,1000);
  if (ShellExecute(NULL,NULL,exe,parameter,thecwd,SW_SHOWNORMAL)<=(HINSTANCE)32)
  {
    MessageBox(NULL,
      "Could not start the application",
      "Please reinstall the application",MB_OK);
    return 2; 
  }

  return 0;
}