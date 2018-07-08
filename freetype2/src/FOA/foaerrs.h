  /*************************************************************************/
  /*                                                                       */
  /* This file is used to define the Windows FOA error enumeration         */
  /* constants.                                                            */
  /*                                                                       */
  /*************************************************************************/

#ifndef FOAERRS_H_
#define FOAERRS_H_

#include FT_MODULE_ERRORS_H

#undef FTERRORS_H_

#undef  FT_ERR_PREFIX
#define FT_ERR_PREFIX  FOA_Err_
#define FT_ERR_BASE    FT_Mod_Err_FOA

#include FT_ERRORS_H

#endif /* FOAERRS_H_ */


/* END */
