#
# FreeType 2 Type1_Test module definition
#


# Copyright 1996-2016 by
# David Turner, Robert Wilhelm, and Werner Lemberg.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.


FTMODULE_H_COMMANDS += FOA_DRIVER

define FOA_DRIVER
$(OPEN_DRIVER) FT_Module_Class, foa_driver_class $(CLOSE_DRIVER)
$(ECHO_DRIVER)FOA     $(ECHO_DRIVER_DESC)FOA Driver module doesnt support and specific font format$(ECHO_DRIVER_DONE)
endef

# EOF
