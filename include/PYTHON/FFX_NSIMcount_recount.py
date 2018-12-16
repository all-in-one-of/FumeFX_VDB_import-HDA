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

## This code run inside a non time dependant python SOP
## every time the user load a FumeFX VDB cache or click the update button
## so no need to wrap it inside a main function, really.

node = hou.pwd()
geo = node.geometry()

inputs = node.inputs()
geopython = inputs[1].geometry()

try:
    nsimcount = geopython.intAttribValue("FFXNSIMcount")
    FFXNSIMcountcheck = 0
    
    for x in range(nsimcount):
        myfile = geopython.stringAttribValue("FFXNSIMVDBrefintframe"+str(x))
        geo.loadFromFile(myfile)
        nsimcount = geo.intAttribValue("NSimCount")
        if nsimcount>=1:
            FFXNSIMcountcheck += 1
        geo.clear()
        
    geo.addAttrib(hou.attribType.Global, "FFXNSIMcountcheck", 0)
    
    if FFXNSIMcountcheck>1:
        geo.setGlobalAttribValue("FFXNSIMcountcheck", 1)
    else:
        geo.setGlobalAttribValue("FFXNSIMcountcheck", 0)
except:
    pass
