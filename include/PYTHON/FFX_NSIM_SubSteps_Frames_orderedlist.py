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
    
## This code run inside a non time dependant python SOP
## every time the user load a FumeFX VDB cache or click the update button
## so no need to wrap it inside a main function, really.
    
ext = ".vdb"
file = node.parm("../../../ffxvdbfile").rawValue()

donsim = node.parm("loadnsim").eval()
isvalid_filename = 1

#
# build NSIM list

new_f = list()
int_f = list()

if len(file)>0:

    directory = os.path.dirname(file)+"/"
    filename = os.path.basename(file)

    try:
        basename = int_match_start(filename)
    except AttributeError:
        isvalid_filename = 0
        pass

    file_ref = file
    #
    # NSIM base filename list START
    allvdb = glob.glob(directory+"*.vdb")
    
    new_allvdb = list()
    newcount=0
    for j in allvdb:
        try:
            m = neg_match(j)
        except AttributeError:
            new_allvdb.append(j)
        newcount+=1
    try:
        nsim_basename = int_match(new_allvdb[0])
    except AttributeError:
        isvalid_filename = 0
        pass
    except IndexError:
        isvalid_filename = 0
        pass
        
    # If it is a valid filename, go ahead
    if isvalid_filename:
    
        nsim_list = list()
        nsim_list.append(nsim_basename[0])
    
        check = nsim_list[0]
    
        # Find all NSIM sequences basenames
        for file in new_allvdb:
            try:
                nsim_basename = int_match(file)
            except AttributeError:
                isvalid_filename = 0
                pass
            if check!=nsim_basename[0]:
                check=nsim_basename[0]
                nsim_list.append(nsim_basename[0])
        # NSIM base filename list END
        #
    
        geo.addAttrib(hou.attribType.Global, "FFXNSIMcount", len(nsim_list))   
        
        name_x = filename.split("_")
        basename = nsim_list
    
    #if isvalid_filename:
    
        if len(nsim_list)>1:
        
            nsimcount = -1
            for nsim in nsim_list:
            
                nsimcount+=1
                
                f = [x for x in glob.glob(directory+"*.vdb") if nsim_list[nsimcount] in x]
                
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
                    i = int_match(filename)
                    if i[0]==basename[nsimcount]:
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
                            new_f[count] = directory+basename[nsimcount]+match[1]+".0."+match[2]
                        else:
                            other_fn = os.path.basename(new_f[count])
                            other_dir = os.path.dirname(new_f[count])+"/"
                            new_f[count] = other_dir+other_fn
                            countsub+=1
                        count+=1
                
                geo.addAttrib(hou.attribType.Global, "FFXNSIMISVALIDfilename"+str(nsimcount), isvalid_filename)
                geo.addAttrib(hou.attribType.Global, "FFXNSIMSUBSAMPLEScheck"+str(nsimcount), 0)
                
                geo.addAttrib(hou.attribType.Global, "FFXNSIMSUBSAMPLEScount"+str(nsimcount), 0)   
            
                if countsub>1:
                    geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScheck"+str(nsimcount), 1)
                    geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScount"+str(nsimcount), countsub)
                
                new_f.sort()
                int_f = list()
                count = 0
                for b in new_f:
                    if count<=recount:
                        filename = os.path.basename(b)
                        match = sub_match(filename)
                        if match[2]=="0":
                            new_f[count] = directory+basename[nsimcount]+match[1]+ext
                            int_f.append(new_f[count])
                            
                        count+=1
                # end build NSIM list
                #
                
                
                # MAKE ARRAYS OF FILENAMES for INTEGER and SUB FRAMES
                #################################################################################################################
                geo.addArrayAttrib(hou.attribType.Global, "FFXNSIMVDBsubframeArray"+str(nsimcount), hou.attribData.String, 1)
                geo.addArrayAttrib(hou.attribType.Global, "FFXNSIMVDBintframeArray"+str(nsimcount), hou.attribData.String, 1)
                geo.setGlobalAttribValue("FFXNSIMVDBsubframeArray"+str(nsimcount), new_f)
                geo.setGlobalAttribValue("FFXNSIMVDBintframeArray"+str(nsimcount), int_f)
                #################################################################################################################
                
                geo.addAttrib(hou.attribType.Global, "FFXNSIMVDBrefintframe"+str(nsimcount), "")
                geo.setGlobalAttribValue("FFXNSIMVDBrefintframe"+str(nsimcount), int_f[0])
                
                if donsim:
                    # start frame int
                    frame = os.path.split(new_f[0])
                    bb = frame[1].split("_")
                    if len(bb)<=1:
                        isvalid_filename = 0
                        geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScheck"+str(nsimcount), 0)
                        geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScount"+str(nsimcount), 0)
                        geo.setGlobalAttribValue("FFXNSIMISVALIDfilename"+str(nsimcount), isvalid_filename)
                        
                    cc = bb[-1].split(".")
                    
                    # silence ValueError:
                    try:
                        start_frame = int(cc[0])
                    except ValueError:
                        isvalid_filename = 0
                        geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScheck"+str(nsimcount), 0)
                        geo.setGlobalAttribValue("FFXNSIMSUBSAMPLEScount"+str(nsimcount), 0)
                        geo.setGlobalAttribValue("FFXNSIMISVALIDfilename"+str(nsimcount), isvalid_filename)
                        pass
        
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMSTARTframe"+str(nsimcount), start_frame)
                        
                    # end frame int
                    f_end = int_match(int_f[-1])
                    frame_end = int(f_end[1])
                    end_frame = recount+start_frame
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMENDsubframe"+str(nsimcount), end_frame)
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMENDframe"+str(nsimcount), frame_end)
                        
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMVDBsubframe"+str(nsimcount), "")
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMVDBintframe"+str(nsimcount), "")
                    geo.addAttrib(hou.attribType.Global, "FFXNSIMVDBrefintendframe"+str(nsimcount), "")
        
                    geo.setGlobalAttribValue("FFXNSIMVDBrefintframe"+str(nsimcount), int_f[0])
                    geo.setGlobalAttribValue("FFXNSIMVDBrefintendframe"+str(nsimcount), int_f[-1])
                
                    #if nsimcount==0:
                    int_f_match = int_match(int_f[0])
                    file_ref_match = int_match_start(file_ref)
                    if int_f_match[0] == file_ref_match[0]:
                        geo.addAttrib(hou.attribType.Global, "FFXNSIMVDBrefloadedintframe"+str(nsimcount), "")
                        geo.setGlobalAttribValue("FFXNSIMVDBrefloadedintframe"+str(nsimcount), int_f[0])          
