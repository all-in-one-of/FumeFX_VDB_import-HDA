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
//
// FFXFIELDrename START
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//

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
//
//
// FFXFORMATfilename START
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
string FFXFORMATfilename(string FFX_in_name, f){
    string vdb = ".vdb";
    string dir, file;
    splitpath(FFX_in_name, dir, file);
    string a_split[] = split(file,  ". _ -");

    int count = 0;
    string new = "";

    foreach(string i; a_split){
        if(count==0){
            new = concat(new, i);
            count++;
            }
        else if(count<=len(a_split)-3){
            new = concat(new, "_", i);
            count++;
            }
        }
        return new;
    }
// FFXFORMATfilrename END
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//

string OUTdir = chs("outdir");

string AOVdir = FFXFIELDrename(chs("aovdir"), "", "");
string DEFprefix = FFXFIELDrename(chs("defprefix"), "", "");

string nname = chs("nname");
string cname = chs("cname");
string directory, filename;
string FFXVDB_IN = chs("FFXVDB_IN");
splitpath(chs("FFXVDB_IN"), directory, filename);
string f = sprintf("%0004d", @Frame);

// Prepare Frame offset and account for negative Frame values.
int f_int = atoi(f);
int f_offset = chi("frame_offset");
int f_newtime = f_int + f_offset;
string f_newtime_reformat = "";

if(f_newtime>=0){
    f_newtime_reformat = sprintf("%0004d", f_newtime);
}
else{
    int abs_f_newtime = abs(f_newtime);
    f_newtime_reformat = concat("-", sprintf("%0004d", abs_f_newtime));
}

string new_in_name = FFXFORMATfilename(filename, f);
new_in_name = FFXFIELDrename(new_in_name, "", concat("_", f_newtime_reformat, ".vdb"));
string prefix = FFXFIELDrename(nname, DEFprefix, "");
string outname = FFXFIELDrename(cname, "", "");
string new_outname = concat(outname, "_", f_newtime_reformat, ".vdb");
string _tmp_filename = "";

if(strlen(outname)>1)
    _tmp_filename = concat(prefix, "_", new_outname);
else
    _tmp_filename = concat(prefix, "_", new_in_name);

string _tmp_fulloutput = "";
if(strlen(directory)>1)
    if(strlen(AOVdir)>1)
        if(strlen(OUTdir)>1)
            _tmp_fulloutput = concat(OUTdir, "/", AOVdir, "/");
        else
            _tmp_fulloutput = concat(directory, "/", AOVdir, "/");
    else
        if(strlen(OUTdir)>1)
            _tmp_fulloutput = concat(OUTdir, "/");
        else
            _tmp_fulloutput = concat(directory, "/");
else
    if(strlen(OUTdir)>1)
        _tmp_fulloutput = concat(OUTdir, "/");
    else
        _tmp_fulloutput = "";
    
// OUT filename and output dir
s@FFXNVDBfilename = _tmp_filename;
s@FFXNVDBfulloutput = _tmp_fulloutput;