#include <ft2build.h>
#include FT_INTERNAL_DEBUG_H
#include FT_INTERNAL_STREAM_H
#include FT_INTERNAL_OBJECTS_H

#include "foa.h"
#include "foaerrs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> /* for wait */
					/* include service header here*/

#include FT_SERVICE_FOA_FACE_INFO_H 

		/* Functions implementations */

/* This function is for making command to pass to program 2 */
char *concatenate(const char *a, const char *b, const char *c) {
	int num;
	size_t alen = strlen(a);
	size_t blen = strlen(b);
	size_t clen = strlen(c);
	char *res = malloc(alen + blen + clen + 2);
	num  = sprintf(res,"%s %s %s",a,b,c);
	if (num < 0)
	{
		printf("error in concatination function\n");
		exit(1);
	}
    return res;
}

char *concatenate_MF(const char *a, const char *b) {
	int num;
	size_t alen = strlen(a);
	size_t blen = strlen(b);
	char *res = malloc(alen + blen + 2);
	num  = sprintf(res,"%s %s",a,b);
	if (num < 0)
	{
		printf("error in concatination function\n");
		exit(1);
	}
    return res;
}
/* This function is for extracting font file name from a file path */
char *Get_font_file_name(const char *Font_file_path) {
	const char *str = Font_file_path;
	const char ch = '/';
	char *ret;
	ret = strrchr(str, ch);
	if(!ret)
		{
   		printf("error in get font file name function");
		exit(1);
	} 
   return ret+1;
}
/* This function is for converting a TTF font file name to TTX font file name */
char *Get_TTX_font_file_name(char *TTF_Font_name) {
	size_t alen = strlen(TTF_Font_name);
	char mystring[alen];
	const char* extension = ".ttx";
	char *new = malloc(alen+1);
	strncpy(mystring, TTF_Font_name, alen-4);
	strcat( mystring, extension );
	strncpy(new, mystring, alen);
	if(!new)
		{
   		printf("error in get TTX conversion function");
		exit(1);
	} 
    return new;
}

/* Get pfb font file name from METAFONT file name */
char *Get_PFB_font_file_name(char *TTF_Font_name) {
	size_t alen = strlen(TTF_Font_name);
	alen = alen+1; 
	char mystring[alen];
	const char* extension = ".pfb";
	char *PFB_File = malloc(alen+1);
	strncpy(mystring, TTF_Font_name, alen-4);
	mystring[alen-4] = '\0';
	strcat( mystring, extension );
	strncpy(PFB_File, mystring, alen);
	if(!PFB_File)
		{
   		printf("error in get PFB conversion function");
		exit(1);
	} 
    return PFB_File;
}

 /* FOA custom service function*/

void FOA_File_Info_Func()    
  {
	printf("************ In FOA service File Get Information Function ************\n\n");	
	pid_t child;
	char *Command_flags = "ttx -d";
	char *Directory_path = "/home/sungmin/dummy_programs/TTX/";
	char *Font_file_path = "/home/sungmin/dummy_programs/AbyssinicaSIL-R.ttf";
	char *executable_name = "/home/sungmin/dummy_programs/pro2"; 
	char *Command = NULL;
	char *TTF_Font_file_name;
	char *TTX_Font_file_name;
	char *c1= "cd /home/sungmin/dummy_programs/TTX/ && cp AbyssinicaSIL-R.ttx text.ttx"; 

	Command = concatenate(Command_flags, Directory_path, Font_file_path);
	TTF_Font_file_name = Get_font_file_name(Font_file_path);
	TTX_Font_file_name = Get_TTX_font_file_name(TTF_Font_file_name);

	printf("Concatenated string is %s \n", Command);
	printf("TTF extension font file name %s \n", TTF_Font_file_name);
	printf("Font name with TTX extension %s \n", TTX_Font_file_name);


     /*Calling fork function */
	if((child=fork())==0){
	printf("Iam Child process\n\n");
	char *argv[] = { executable_name, Command, NULL };
	execv(argv[0], argv);
        exit(127); 
    }
    else { 
	printf("Iam parent, waiting for child process to exit\n\n");        
	waitpid(child,0,0); 
	system(c1);
	printf("Existing parent\n\n");
	}
 printf("************ Finished with coverting TTF to XML file ************\n\n");
  }

  /* FOA function to call Mftrace */

    char*  FOA_Call_Mftrace(char*  pathname)    
     {
		printf("Metafont file to be converted to PFB is %s \n", pathname);

		printf("************ In FOA service File Get Information Function ************\n\n");	
		pid_t child;
		char *Command_flags = "cd /home/sungmin/METAFONT/ && mftrace -f PFB";
		char *Directory_path = "/home/sungmin/METAFONT/";
		char *Font_file_path = pathname;
		char *Default_file_path = "/home/sungmin/METAFONT/test.pfb";
		char *executable_name = "/home/sungmin/dummy_programs/pro2"; 
		char *Command = NULL;
		char *MF_Font_file_name;
		char *PFB_Font_file_name;
		
	   /*  FOA cache manager module */

	   /* First of all check if the requested METAFONT file exsists or not. 
	   I could have written another function for that but iam not using that :) */
	    
	    if( access( Font_file_path, F_OK ) != -1 ) {
		    printf("METAFONT file is installed \n");
		    PFB_Font_file_name = Get_PFB_font_file_name(Font_file_path);
		    /* If it exsists than check if the corresponding PFB file is preapred or not*/
		    if( access( PFB_Font_file_name, F_OK ) != -1 ) 
		    {
	    		/* Return the PFB file dont dont call mftrace*/
		    	printf("PFB of requested METAFONT file exsists \n");
		    	return PFB_Font_file_name;
		    	exit(1);
			} 
			/* METAFONT file exsists but its PFB font file does not exsists so call mftrace :) */
			else {
		    	printf("PFB of requested METAFONT file does not exsists \n");
		    	MF_Font_file_name = Get_font_file_name(Font_file_path);
		    	Command = concatenate_MF(Command_flags, MF_Font_file_name);
		    	PFB_Font_file_name = Get_PFB_font_file_name(Font_file_path);
		    	printf("METAFONT file name is %s \n", MF_Font_file_name);
		    	printf("Command for mftrace is %s \n", Command);
		    	printf("PFB font file name is %s \n", PFB_Font_file_name);
		    	printf("CALLING MFtrace external module \n");
		    	/*Calling fork function */
				
				if((child=fork())==0){
				printf("Iam Child process\n\n");
				char *argv[] = { executable_name, Command, NULL };
				execv(argv[0], argv);
				exit(127); 
				}
				else { 
				printf("Iam parent, waiting for child process to exit\n\n");        
				waitpid(child,0,0); 
				printf("Existing parent\n\n");
				}
			}

		}
		/* Requested METAFONT file is not installed so, display a default font on screen */
		else {
		    printf("METAFONT file is not installed \n");
	     	PFB_Font_file_name = Default_file_path;
	      
	      return PFB_Font_file_name;
	      exit(1);
		}

		printf("************ Finished with coverting METAFONT to PFB file ************\n\n");

	      return PFB_Font_file_name;
     }

     /* This FOA function is for extracting font file extension from a file path */
	char* FOA_Call_Mffinder(char *Font_file_path) {
		const char *str = Font_file_path;
		const char ch = '.';
		char *ret;
		ret = strrchr(str, ch);
		if(!ret)
			{
	   		printf("error in get font file name function");
			exit(1);
		} 
	   return ret+1;
	}


	/* This FOA function is for extracting font file extension from a file path */
	char* FOA_Call_GF_DVI(char*  pathname, char*  file_ext) {
		printf("Path of file in GF_DVI service function is %s \n", pathname);
		printf("File extension of GF OR DVI file is %s \n", file_ext);

		if (strcmp( file_ext, "2602gf") == 0)
		{
			printf("This is a GF file");
		}
		else if(strcmp( file_ext, "dvi") == 0)
		{
			printf("This is a DVI file");
		}
		else{
			printf("none of GF or DVI\n");
		}

	}

			/* FOA module service defination */

  static const FT_Service_FOAInfoRec  face_service_foa_info =
  {
    (FOA_Get_File_Info_Func)   FOA_File_Info_Func,    /* FOA_get_file_info   */
    (FOA_MF_TO_PFB_Custom_Func)   FOA_Call_Mftrace,    /* FOA_MF_TO_PFB   */
    (Get_font_file_ext)           FOA_Call_Mffinder,    /* FOA_MF_Finder   */
    (FOA_GF_DVI_Custom_Func)   FOA_Call_GF_DVI    /* FOA_GF_DVI   */
  };

 			/* FOA service list */

  static const FT_ServiceDescRec  foa_services[] =
  {
    { FT_SERVICE_ID_FOA_CUSTOM_INFO,      &face_service_foa_info },
    { NULL, NULL }
  };

			/* FOA module get_interface implementaion */

  FT_CALLBACK_DEF( FT_Module_Interface )
  FOA_Get_Interface( FT_Module         module,
                 const FT_String*  foa_interface )
  {
    FT_UNUSED( module );

    return ft_service_list_lookup( foa_services, foa_interface );
  }

			/* FOA Class implementation */

  FT_DEFINE_MODULE(
    foa_driver_class,

    0,  /* this is not a font driver, nor a renderer , FOA helping module*/
    sizeof ( FT_ModuleRec ),

    "FOA",  /* driver name                         */
    0x10000L,   /* driver version                      */
    0x20000L,   /* driver requires FreeType 2 or above */

    NULL, /* module-specific interface */

    (FT_Module_Constructor)NULL,                                       /* module_init   */
    (FT_Module_Destructor) NULL,                                       /* module_done   */
    FOA_Get_Interface  /* get_interface */
  )


/* END */