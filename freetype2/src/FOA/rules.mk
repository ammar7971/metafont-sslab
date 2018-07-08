#
# FreeType 2 Windows FOA/FON driver configuration rules
#


# Copyright 1996-2017 by
# David Turner, Robert Wilhelm, and Werner Lemberg.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.


# FOA driver directory
#
FOA_DIR := $(SRC_DIR)/FOA


FOA_COMPILE := $(CC) $(ANSIFLAGS)                            \
                     $I$(subst /,$(COMPILER_SEP),$(FOA_DIR)) \
                     $(INCLUDE_FLAGS)                        \
                     $(FT_CFLAGS)


# FOA driver sources (i.e., C files)
#
FOA_DRV_SRC := $(FOA_DIR)/foa.c

# FOA driver headers
#
FOA_DRV_H := $(FOA_DRV_SRC:%.c=%.h) \
             $(FOA_DIR)/foaerrs.h 


# FOA driver object(s)
#
#   FOA_DRV_OBJ_M is used during `multi' builds
#   FOA_DRV_OBJ_S is used during `single' builds
#
FOA_DRV_OBJ_M := $(FOA_DRV_SRC:$(FOA_DIR)/%.c=$(OBJ_DIR)/%.$O)
FOA_DRV_OBJ_S := $(OBJ_DIR)/foa.$O

# FOA driver source file for single build
#
FOA_DRV_SRC_S := $(FOA_DIR)/foa.c


# FOA driver - single object
#
$(FOA_DRV_OBJ_S): $(FOA_DRV_SRC_S) $(FOA_DRV_SRC) $(FREETYPE_H) $(FOA_DRV_H)
	$(FOA_COMPILE) $T$(subst /,$(COMPILER_SEP),$@ $(FOA_DRV_SRC_S))


# FOA driver - multiple objects
#
$(OBJ_DIR)/%.$O: $(FOA_DIR)/%.c $(FREETYPE_H) $(FOA_DRV_H)
	$(FOA_COMPILE) $T$(subst /,$(COMPILER_SEP),$@ $<)


# update main driver object lists
#
DRV_OBJS_S += $(FOA_DRV_OBJ_S)
DRV_OBJS_M += $(FOA_DRV_OBJ_M)


# EOF
