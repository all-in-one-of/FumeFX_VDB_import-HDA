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

// FFXFIELDrename START
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
string FFXFIELDrename(string FFX_in, FFX_def, FFX_ext)
    {
    string symbols = "!#$%^&*|()+[{]};:'/"",<.>/?* ";
    string fname_strip[] = split(FFX_in, symbols);
    int fname_strip_count = len(fname_strip);
    string fix_fname = "";
    string new_fname = "";
    int fcount = 0;
    if(fname_strip_count > 1){
        foreach(string i; fname_strip){
            if(fcount == 0){
                fix_fname = concat(fix_fname, i);
                fcount++;
                }
            else{
                fix_fname = concat(fix_fname, "_", i);
            } 
        }
        new_fname = fix_fname; 
    }

    if(strlen(fname_strip[0])==0)
        new_fname = concat(FFX_def, FFX_ext);
        
    else if(len(fname_strip)==1)
        new_fname = concat(fname_strip[0], FFX_ext);
        
    else
        new_fname = concat(new_fname, FFX_ext);
    
    return new_fname;
}
// FFXFIELDrename END
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


// Everything start here.
/////////////////////////////////////////////////////////////
//
string fields_name = getattrib(0, "prim", "name", @primnum, 1);

string smkname = chs("smokename");
string velname = chs("velxname");
string tempname = chs("tempname");
string fuelname = chs("fuelname");
string colname = chs("colrname");
string texwtpname = chs("texwtpname");
string texfmname = chs("texfmname");

// We need to store the new fields names in attributes
// and access them later from the VDB Merge node.
// This way we can change their name as we wish
// and have the VDBB Merge nodes understand whats the new name is
// for a set of fields he attempt to merge.
//
s@FFXsmkname = "";
s@FFXvelnameX = "";
s@FFXvelnameY = "";
s@FFXvelnameZ = "";
s@FFXtmpname = "";
s@FFXfulname = "";
s@FFXcolnameR = "";
s@FFXcolnameG = "";
s@FFXcolnameB = "";
s@FFXtexnameX = "";
s@FFXtexnameY = "";
s@FFXtexnameZ = "";
s@FFXtexnameBX = "";
s@FFXtexnameBY = "";
s@FFXtexnameBZ = "";

// If a field is renamed,
// it will be marked so we can keep track of it.
i@FFXfieldrenamed = 0;

// SMOKE
if(ch("rensmoke")==1){
    if(fields_name == "Smoke"){
    string new_name = FFXFIELDrename(smkname, "density", "");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "density";
    s@FFXsmkname = s@name;
        }
    }

// VELOCITIES
if(ch("renvel")==1){
    if(fields_name == "VelocitiesX"){
        string new_name = FFXFIELDrename(velname, "vel", ".x");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "vel.x";
    s@FFXvelnameX = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "VelocitiesY"){
        string new_name = FFXFIELDrename(velname, "vel", ".y");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "vel.y";
    s@FFXvelnameY = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "VelocitiesZ"){
        string new_name = FFXFIELDrename(velname, "vel", ".z");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "vel.z";
    s@FFXvelnameZ = s@name;
    i@FFXfieldrenamed = 1;
        }
    }

// TEMPERATURE 
if(ch("rentemp")==1){
    if(fields_name == "Temperature"){
        string new_name = FFXFIELDrename(tempname, "temperature", "");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "temperature";
    s@FFXtmpname = s@name;
        }
    }

// FIRE/FUEL 
if(ch("renfirefuel")==1){
    if(fields_name == "FireFuel"){
        string new_name = FFXFIELDrename(fuelname, "fuel", "");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "fuel";
    s@FFXfulname = s@name;
        }
    }

// COLORS
if(ch("rencol")==1){
    if(fields_name == "ColorR"){
        string new_name = FFXFIELDrename(colname, "Cd", ".x");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "Cd.x";
    s@FFXcolnameR = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "ColorG"){
        string new_name = FFXFIELDrename(colname, "Cd", ".y");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "Cd.y";
    s@FFXcolnameG = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "ColorB"){
        string new_name = FFXFIELDrename(colname, "Cd", ".z");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "Cd.z";
    s@FFXcolnameB = s@name;
    i@FFXfieldrenamed = 1;
        }
    }
    
// Texture WTP
if(ch("rentexwtp")==1){
    if(fields_name == "TextureX"){
        string new_name = FFXFIELDrename(texwtpname, "texWTP", ".x");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texWTP.x";
    s@FFXtexnameX = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "TextureY"){
        string new_name = FFXFIELDrename(texwtpname, "texWTP", ".y");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texWTP.y";
    s@FFXtexnameY = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "TextureZ"){
        string new_name = FFXFIELDrename(texwtpname, "texWTP", ".z");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texWTP.z";
    s@FFXtexnameZ = s@name;
    i@FFXfieldrenamed = 1;
        }
    }
    
// Texture FM
if(ch("rentexfm")==1){
    if(fields_name == "TextureBX"){
        string new_name = FFXFIELDrename(texfmname, "texFM", ".x");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texFM.x";
    s@FFXtexnameBX = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "TextureBY"){
        string new_name = FFXFIELDrename(texfmname, "texFM", ".y");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texFM.y";
    s@FFXtexnameBY = s@name;
    i@FFXfieldrenamed = 1;
        }
    if(fields_name == "TextureBZ"){
        string new_name = FFXFIELDrename(texfmname, "texFM", ".z");
    if(ch("modifynames")==1)
        s@name = new_name;
    else
        s@name = "texFM.z";
    s@FFXtexnameBZ = s@name;
    i@FFXfieldrenamed = 1;
        }
    }