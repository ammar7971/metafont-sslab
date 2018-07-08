/***************************************************************************/
/*                                                                         */
/*  svfoa.h                                                                */
/*  This is a service for FOA module                                       */
/***************************************************************************/




#ifndef SVFOA_H_
#define SVFOA_H_

#include FT_INTERNAL_SERVICE_H

FT_BEGIN_HEADER


#define FT_SERVICE_ID_FOA_CUSTOM_INFO  "foacustom-info"


  typedef void  
  (*FOA_Get_File_Info_Func)();
  
  typedef char*  
  (*FOA_MF_TO_PFB_Custom_Func)( char*  pathname );

  typedef char*  
   (*Get_font_file_ext)( char* Font_file_path ) ;

  typedef char*  
  (*FOA_GF_DVI_Custom_Func)( char*  pathname, char*  file_ext );

  FT_DEFINE_SERVICE( FOAInfo )
  {
    FOA_Get_File_Info_Func        FOA_get_file_info;
    FOA_MF_TO_PFB_Custom_Func     FOA_MF_TO_PFB;
    Get_font_file_ext             FOA_MF_Finder;
    FOA_GF_DVI_Custom_Func        FOA_GF_DVI;    
  };

  /* */


FT_END_HEADER


#endif /* SVFOA_H_ */


/* END */


