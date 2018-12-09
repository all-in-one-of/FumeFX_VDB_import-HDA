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

# Ourself
node = hou.pwd()
geo = node.geometry()

# Info about non SS caches
node1 = hou.node("../python_frame_count_no_ss")
geo1 = node1.geometry()

# Info about SS caches
node2 = hou.node("../python_SS")
geo2 = node2.geometry()

# Info about: is it part of an NSim?
node3 = hou.node("../FFXNSIMcountcheck")
geo3 = node3.geometry()

# Info about NSims caches data
node4 = hou.node("../FFXNSIMdata")
geo4 = node4.geometry()

# HDA UI checkboxes
doss = node.evalParm("doss")
donsim = node.evalParm("donsim")

# How many NSims caches are we loading?
try:
    nsimcount = geo4.intAttribValue("FFXNSIMcount")
except:
    pass

# Get the max END frame number for NSIM int frames and sub frames
nsimendmax = 0
nsimsubendmax = 0
nsimsubend = 0
nsimend = 0
for x in range(nsimcount):
    try:
        nsimsubend = geo4.intAttribValue("FFXNSIMENDsubframe"+str(x))
        nsimend = geo4.intAttribValue("FFXNSIMENDframe"+str(x))
    except:
        pass
    if nsimsubend>nsimsubendmax:
        nsimsubendmax=nsimsubend
    if nsimend>nsimendmax:
        nsimendmax=nsimend

# Get the start and end frame nuber for non NSim cache
try:
    FFXSTARTframe = geo1.intAttribValue("FFXSTARTframe")
    FFXENDframe = geo1.intAttribValue("FFXENDframe")
except:
    pass
try:
    FFXENDsubframe = geo2.intAttribValue("FFXENDsubframe")
except:
    pass

# Set FFX_START and FFX_END frame
FFXSUBSAMPLEScheck = geo2.intAttribValue("FFXSUBSAMPLEScheck")
FFXSNSIMcheck = 0
try:
    FFXSNSIMcheck = geo3.intAttribValue("FFXNSIMcountcheck")
except:
    pass

# Set FFXTART frame ( this will alway be the same )
geo.addAttrib(hou.attribType.Global, "FFXSTART", FFXSTARTframe)

# Set FFXEND frame based on user choices.
if FFXSUBSAMPLEScheck and doss and FFXSNSIMcheck and donsim==0:
    geo.addAttrib(hou.attribType.Global, "FFXEND", FFXENDsubframe)
elif FFXSUBSAMPLEScheck and doss and FFXSNSIMcheck and donsim:
    geo.addAttrib(hou.attribType.Global, "FFXEND", nsimsubendmax)
elif FFXSUBSAMPLEScheck and FFXSNSIMcheck and donsim:
    geo.addAttrib(hou.attribType.Global, "FFXEND", nsimendmax)
elif FFXSUBSAMPLEScheck and FFXSNSIMcheck==0 and doss:
    geo.addAttrib(hou.attribType.Global, "FFXEND", FFXENDsubframe)
elif FFXSUBSAMPLEScheck and FFXSNSIMcheck==0 and doss==0:
    geo.addAttrib(hou.attribType.Global, "FFXEND", FFXENDframe)
else:
    geo.addAttrib(hou.attribType.Global, "FFXEND", FFXENDframe)