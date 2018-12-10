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
    name = bname+fnum+"."+ext
    return [bname, fnum, ext, name]

def int_match(file):
    dir = os.path.dirname(file)
    basename = os.path.basename(file)
    pattern = re.compile(r"(\S+_)(\d+).(\S+)")
    m = re.search(pattern, basename)
    bname, fnum, ext = m.groups()
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
    name = bname+fnum+"."+ext
    return [bname, fnum, ext, name]

ext = ".vdb"
file = node.parm("../../../ffxvdbfile").rawValue()
doss = node.parm("doss").eval()
isvalid_filename = 1

#
# build list
if len(file)>0:

    directory = os.path.dirname(file)+"/"
    filename = os.path.basename(file)
    name_x = filename.split("_")
    basename = filename.split(name_x[-1])
    
    try:
        int_match_start(filename)
    except AttributeError:
        isvalid_filename = 0
    
    namecount = 0
    pattern = ""
    for a in name_x:
        if namecount<len(name_x)-1:
            pattern+=a+"_"
            namecount+=1
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
        
    recount = -1
    for a in new_f:
        filename = os.path.basename(a)
        try:
            i = int_match(filename)
        except AttributeError:
            isvalid_filename = 0
            pass
        if i[0]==basename[0]:
            recount+=1
    
    countsub = 0
    count = 0
    for a in new_f:
        if count<=recount:
            filename = os.path.basename(a)
            match = int_match(filename)
            us_split = filename.split("_")
            dot_split = us_split[-1].split(".")
            if len(dot_split)==2:
                new_f[count] = directory+match[0]+match[1]+".0."+match[2]
            else:
                other_fn = os.path.basename(new_f[count])
                other_dir = os.path.dirname(new_f[count])+"/"
                new_f[count] = other_dir+other_fn
                countsub+=1
            count+=1

    geo.addAttrib(hou.attribType.Global, "FFXISVALIDfilename", isvalid_filename)
    geo.addAttrib(hou.attribType.Global, "FFXSUBSAMPLEScheck", 0)
    
    geo.addAttrib(hou.attribType.Global, "FFXSUBSAMPLEScount", 0)   

    if countsub>1:
        
        geo.setGlobalAttribValue("FFXSUBSAMPLEScheck", 1)
        geo.setGlobalAttribValue("FFXSUBSAMPLEScount", countsub)
        
        if doss:
        
            new_f.sort()
            
            int_f = list()
            count = 0
            for b in new_f:
                if count<=recount:
                    filename = os.path.basename(b)
                    match = sub_match(filename)
                    if match[2]=="0":
                        new_f[count] = directory+match[0]+match[1]+ext
                        int_f.append(new_f[count])
                    count+=1
            # end build list
            #
    
            # start frame int
            frame = os.path.split(new_f[0])
            bb = frame[1].split("_")
            if len(bb)<=1:
                isvalid_filename = 0
                geo.setGlobalAttribValue("FFXSUBSAMPLEScheck", 0)
                geo.setGlobalAttribValue("FFXSUBSAMPLEScount", 0)
                geo.setGlobalAttribValue("FFXISVALIDfilename", isvalid_filename)
                
            cc = bb[-1].split(".")
            
            # silence ValueError:
            try:
                start_frame = int(cc[0])
            except ValueError:
                isvalid_filename = 0
                geo.setGlobalAttribValue("FFXSUBSAMPLEScheck", 0)
                geo.setGlobalAttribValue("FFXSUBSAMPLEScount", 0)
                geo.setGlobalAttribValue("FFXISVALIDfilename", isvalid_filename)
                pass
                
            # proceed if it is a valid filename
            if isvalid_filename==1:
                geo.addAttrib(hou.attribType.Global, "FFXSTARTsubframe", start_frame)
                    
                # end frame int
                f_end = int_match(new_f[-1])
                frame_end = int(f_end[1])
                end_frame = recount+start_frame
                geo.addAttrib(hou.attribType.Global, "FFXENDsubframe", end_frame)
                geo.addAttrib(hou.attribType.Global, "FFXENDframe", frame_end)
                
                geo.addArrayAttrib(hou.attribType.Global, "FFXVDBsubframeArray", hou.attribData.String, 1)
                geo.setGlobalAttribValue("FFXVDBsubframeArray", new_f)
                