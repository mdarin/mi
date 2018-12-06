/* * * * *
 * Название: mi - команда сборки заготовок имитаторов
 * Версия: 0.2.0
 * Описание: производит сборку и компиляцию указанного имитатора
 * Программист разработчик: Дарьин М.В.
 * Программист сопровождения: 
 * Дата создания: 10.12.2012
 * Дата последнего изменения: 08.04.2013
 * Организация: ЗАО "ОКБ "ИКАР"
 * Лицензия: "AS-IS" "NO WARRENTY"
 * Контакты:
 * почта: 
 * адрес: 
 * 
 * 2012
 * 
 * * */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

//__DEBUG 
// если определён, то отладочный режим = ВКЛ
#define DEBUG 1
// иначе отладочный режим = ВЫКЛ
#undef DEBUG

#define get_vsn() ("0.2.0")
#define get_usage() ("Usage: <cmd> [OPTIONS] IMITATOR|[IMITATORS]\n"\
"\n"\
"Make IMITATOR(s)"\
"\n"\
"  -c | --complex\n"\
"  -v | --version\n"\
"  -h | --help")

// пути для размещения сгенерированных файлов
#define get_project_root_dir() ("C://Project//ikar2")
#define get_ipanels_dir() ("C://Project//ikar2//ipanels")
#define get_wrappers_dir() ("C://Project//ikar2//wrapper")
#define get_virtual_wrappers_dir() ("C://Project//ikar2//wrappers//virtual")
#define get_icfg_dir() ("C://Project//ikar2//icfg")
#define get_complexes_dir() ("C://Project//ikar2//icfg//complexes")
#define get_profile_dir() ("C://Project//ikar2//icfg//profile")
#define get_scripts_dir() ("C://Project//ikar2//scripts")

 /* direct.h
int chdir(char* path)
int chdrive(int drive)
char* getcwd(char* buffer, size_t length)
int getdrive(void)
int mkdir(const char* pathname)
int rmdir(const char* pathname)
void fnmerge(char* path, const char* drive, const char* dir, const char* name, const char* ext)
int fnsplit(const char* path, char* drive, char* dir, char* name, char* ext)
char* searchpath(const char* file)
*/

char *ProjectRoot = NULL;
char IpanelsDir[256] = {0};
char WrappersVirtualDir[256] = {0};
char IcfgDir[256] = {0};
char ProfileDir[256] = {0};
char ScriptsDir[256] = {0};
char TemplatesDir[256] = {0};

/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
void initialize_dirstruct(void)
{
  strcpy(IpanelsDir, ProjectRoot);
  strcat(IpanelsDir, "\\ipanels");

  strcpy(IcfgDir, ProjectRoot);
  strcat(IcfgDir, "\\icfg");

  strcpy(ProfileDir, IcfgDir);
  strcat(ProfileDir, "\\profile");

  strcpy(WrappersVirtualDir, ProjectRoot);
  strcat(WrappersVirtualDir, "\\wrappers\\virtual");

  strcpy(ScriptsDir, ProjectRoot);
  strcat(ScriptsDir, "\\scripts");

  strcpy(TemplatesDir, ProjectRoot);
  strcat(TemplatesDir, "\\utils\\ci\\templates");

  printf("ipanels: %s\nicfg: %s\nprofile: %s\nvirtual: %s\nscripts: %s\n", IpanelsDir, IcfgDir, ProfileDir, WrappersVirtualDir, ScriptsDir);

  return;
}

/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
int main(int argc, char **argv)
{
  int Status = 0;
  FILE *Stream = stdout;
  #ifdef DEBUG
  printf("argc: %d\n", argc);
  #endif
  ProjectRoot = getenv("IKAR_ROOT");
  if (NULL == ProjectRoot) {
    printf("%s:Can't find IKAR_ROOT env variable, please setup and try again.\n", argv[0]);
    exit(0);
  }
  printf("IKAR_ROOT: [%s]\n", ProjectRoot);
  initialize_dirstruct();
  char FullPath[256] = {0};
  char Imitator[256] = {0};
  char Cmd[256] = {0};
  switch(argc) {
  case 0:
  case 1:
    printf("\nmake imitator v.%s\n\n%s", get_vsn(), get_usage());
    break;
  case 2:
    strcpy(Imitator, argv[1]);
    strcpy(FullPath, IpanelsDir);
    strcat(FullPath, "//");
    strcat(FullPath, Imitator); 
    chdir(FullPath);
    strcpy(Cmd, " nmake clean");
    system(Cmd);
    strcpy(Cmd, " qmake");
    system(Cmd);
    strcpy(Cmd, " nmake release");
    system(Cmd);
    #ifdef DEBUG
    printf("ipanel: %s\n", FullPath);
    #endif
    strcpy(FullPath, WrappersVirtualDir);
    strcat(FullPath, "//"); 
    strcat(FullPath, Imitator);
    chdir(FullPath);
    strcpy(Cmd, " nmake clean");
    system(Cmd);
    strcpy(Cmd, " qmake");
    system(Cmd);
    strcpy(Cmd, " nmake release");
    system(Cmd); 
    #ifdef DEBUG
    printf("virtual wrapper: %s\n", FullPath);   
    #endif
    break;	  
  default:    
     
    break;  
  } // eof switch
  return Status;
}
