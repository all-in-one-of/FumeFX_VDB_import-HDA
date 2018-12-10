// FFX_IMPORT v1.5
// SideFX Houdini OTL
//
// Author/Copyrights: Alessandro Nardini
// Email: alexnardini@gmail.com
// Creation date: 09th October 2018
//
// "FFX_import" is a little houdini OTL to work
// with FumeFX caches inside Houdini in an easy way.
// It works like "DOP import fields" node does for Pyro
// but instead of referencing a live DOP
// it will operate on simulation VDB caches
// done with FumeFX v5 and up.
//

string fields_name = getattrib(0, "prim","name", @primnum, 1);

if(ch("blastflags")==0){
    if(fields_name == "Flags")
        removeprim(0, @primnum, 1);
    }  
if(ch("blastsmoke")==0){
    if(fields_name == "Smoke")
        removeprim(0, @primnum, 1);
    }
if(ch("blastvel")==0){
    if(fields_name == "VelocitiesX" || fields_name == "VelocitiesY" || fields_name == "VelocitiesZ")
        removeprim(0, @primnum, 1);
    }
if(ch("blasttemp")==0){
    if(fields_name == "Temperature")
        removeprim(0, @primnum, 1);
    }
if(ch("blastfire")==0){
    if(fields_name == "FireFuel")
        removeprim(0, @primnum, 1);
    }
if(ch("blastoxygen")==0){
    if(fields_name == "Oxygen")
        removeprim(0, @primnum, 1);
    }
if(ch("blastcolor")==0){
    if(fields_name == "ColorR" || fields_name == "ColorG" || fields_name == "ColorB")
        removeprim(0, @primnum, 1);
    }
if(ch("blastextra")==0){
    if( fields_name == "TextureX" || fields_name == "TextureY" || fields_name == "TextureZ")
        removeprim(0, @primnum, 1);
    }
if(ch("blastextrafm")==0){
    if( fields_name == "TextureBX" || fields_name == "TextureBY" || fields_name == "TextureBZ")
        removeprim(0, @primnum, 1);
    }
if(ch("blastenergy")==0){
    if(fields_name == "HFenergy")
        removeprim(0, @primnum, 1);
    }
