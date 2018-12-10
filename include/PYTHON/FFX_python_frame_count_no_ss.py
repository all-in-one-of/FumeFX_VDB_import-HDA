## FFX_IMPORT v1.5
## SideFX Houdini OTL
##
## Author/Copyrights: Alessandro Nardini
## Email: alexnardini@gmail.com
## Creation date: 09th October 2018
##
## "FFX_import" is a little houdini OTL to work
## with FumeFX caches inside Houdini in an easy way.
## It works like "DOP import fields" node does for Pyro
## but instead of referencing a live DOP
## it will operate on simulation VDB caches
## done with FumeFX v5 and up.
##

node = hou.pwd()
geo = node.geometry()

import os
import glob
import re

def int_match_start(file):
    dir = os.path.dirname(file)
    basename = os.path.basename(file)
    pattern = re.compile(r"(\S+_)(\\$\S\d).(\S+)")
    m = re.search(pattern, basename)
    bname, fnum, ext = m.groups()
    strings = m.groups()
    name = bname+fnum+"."+ext
    return [bname, fnum, ext, name]
    
def int_match(file):
    dir = os.path.dirname(file)
    basename = os.path.basename(file)
    pattern = re.compile(r"(\S+_)(\d+).(\S+)")
    m = re.search(pattern, basename)
    bname, fnum, ext = m.groups()
    strings = m.groups()
    name = bname+fnum+"."+ext
    return [bname, fnum, ext, name]

def sub_match(file):
    dir = os.path.dirname(file)
    basename = os.path.basename(file)
    pattern = re.compile(r"(\S+_)(\d+).(\d).(\S+)")
    m = re.search(pattern, basename)
    bname, fnum, sfnum, ext = m.groups()
    name = bname+fnum+"."+sfnum+"."+ext
    return [bname, fnum, sfnum, ext, name]
    
def neg_match(file):
    dir = os.path.dirname(file)
    basename = os.path.basename(file)
    pattern = re.compile(r"(\S+_-)(\d+).(\S+)")
    m = re.search(pattern, basename)
    bname, fnum, ext = m.groups()
    strings = m.groups()
    name = bname+fnum+"."+ext
    return [bname, fnum, ext, name]
    
# .rawValue()
# So we dnt need this Python SOP time dependant
# and we update it everytime the user change FumeFX VDB cache file
# using a callback() script.
file = node.parm("../../../ffxvdbfile").rawValue()

isvalid_filename = 1

#
# build list
if len(file)>0:
    directory = os.path.dirname(file)+"/"
    filename = os.path.basename(file)
    try:
        basename = int_match_start(filename)
    except AttributeError:
        isvalid_filename = 0
        pass
    #print basename
    if isvalid_filename:
        pattern = basename[0]
        f = [x for x in glob.glob(directory+"*.vdb") if pattern in x]
        
        new_f = list()
        newcount=0
        for j in f:
            try:
                m = neg_match(j)
            except AttributeError:
                new_f.append(j)
            newcount+=1
        
        del f
            
        # How many frames we are trying to load?
        recount = -1
        for a in new_f:
            filename = os.path.basename(a)
            i = int_match(filename)
            if i[0]==basename[0]:
                recount+=1
        
        ff = list()
        # Get only what we need
        for a in new_f:
            filename = os.path.basename(a)
            match = int_match(filename)
            if match[0]==basename[0]:
               ff.append(a)
        geo.addAttrib(hou.attribType.Global, "FFXSTARTrefintstartframe", "")
        basenamestart = os.path.basename(ff[0])
        geo.setGlobalAttribValue("FFXSTARTrefintstartframe", directory+basenamestart)

        # Get Start and End frame values
        if len(ff)>1:
            ff_first = filename = os.path.basename(ff[0])
            ff_end = filename = os.path.basename(ff[-1])
            match_ff_first = int_match(ff_first)
            match_ff_end = int_match(ff_end)
            
            # Output Start and End frame number
            geo.addAttrib(hou.attribType.Global, "FFXSTARTframe", int(match_ff_first[1]))
            geo.addAttrib(hou.attribType.Global, "FFXENDframe", int(match_ff_end[1]))