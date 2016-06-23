#         Just A Midi Pad 
# www.github.com/luxarts/JustAMidiPad
# Created by LuxARTS, OG-Jonii & pablonobile99
#               2016
# emacs-mode: -*- python-*-
# -*- coding: utf-8 -*-

import Live
from JAMP_alpha import JAMP_alpha

def create_instance(c_instance):
    ' Creates and returns the APC20 script '
    return JAMP_alpha(c_instance)


# local variables:
# tab-width: 4
