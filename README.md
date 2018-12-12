# FFX import HDA for SideFX Houdini 16.5.x to 17.x.x
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_WELCOME.jpg)

FFX_import is a SideFX Houdini HDA to work with FumeFX caches inside Houdini in an easy and fun way. It works like "DOP import fields" node does for Pyro but instead of referencing a live DOP it will operate on simulation VDB caches done with FumeFX v5 and up. 
It will let you load FumeFX VDB Caches, FumeFX Sub Frames and Nsims caches without any effort. And much more.
It will also give you the ability to quickly export a set of AOVs new vdb caches to load them back into 3DSMax ▸ FumeFX in one click.

### FFX Virtuous Fumes clip 
FumeFX import was born during the production of "Virtuous Fumes":
https://vimeo.com/264618048

Check out the making of also:
https://vimeo.com/268214826

# Features List

- FFX_import HDA it’s FREE!
- UI inspired and designed with FumFX UI in mind.
- UI live FumeFX grid informations available at any time.
- UI Dynamically load and unload parameters based on the input FumeFX VDB cache selected.
- FumeFX Fields/Channels import selection.
- FumeFX Fields/Channels auto rename to follow the common Houdini nameing convention.
- Check for missing vector fields components. (Velocities wint only X or Colors with only R and G…)
- Smart fields/channels shuffling and merging.
- Load VDB caches as Fields or as BBOX for fast bounding preview. ( the Bounding Box information come from the file chache header file so as long as there are information to be read, it will display the bbox in realtime without the need to load the cache volume fields first.)
- Load FumeFX Sub Frames if exported. (Check "Save Sub Frames" in the FumeFX simulation tab)
- Load NSims all at once. You must have saved all of them into the same folder (This include sub frames for each of them if they     have been exported. The Load sub frames option must be enabled). The tool is smart enough to check witch one of the caches present in the selected folder belong to an NSim and witch one does not.
- NSIM as ONE convert all NSims caches into one and prepare it to succesfully load it back into FumeFX if you desire so.
During this mode, you will still be able to import, merge, shuffle and rename fields with one click.
- Live Z-Depth manipulation for artistic control on the output values.
- String auto formatting and simple errors checking anywhere you can input either a field name, a prefix or a filename.
- Useful warning messages to keep you informed of the status of your caches and operations.
- HDA help/documentation with live links to the online FumeFX doc.
- Automated output file system and file naming. Just focus on crafting your work as quick as possible.

The following feature make use of the Automated output filesystem.
- Export a Normals/Positions/Z-Depth Field in one click to load it back into 3DSMax ▸ FumeFX or Maya ▸ FumeFX and render it with your scene.
(FumeFX v5 and up has some great AOVs to output for the Arnold renderer but it is always nice to have those data stored on a per voxel level so why not.) 

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_powered_by.jpg)



# FFX import - Brief introduction
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx.jpg)
`Image generated with FumeFX v5.0.2`

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_ui_001.jpg)

FFX import HDA has a compact and functional interface that accomodate every FumeFX features with easy
and bring them into the Houdini workflow and mentality.

Loading FumeFX VDB caches in one click has never been this easy and fun,
and no matter if you are loading a single FumeFX VDB cache sequence, or FumeFX sub frames and FumeFX NSim;
every tool's functionality will work in all modes.

You will be able to import fields/channels on demand, rename and merge them with one click.
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_007.jpg)


Although everything looks simple and mondane, there is a certain level of complexity underneath to ensure
everything will go smooth and in a fast execution as the tool scale up well from one single VDB cache
to loading multiple FumeFX NSims caches at once while all their fields are smartly managed and keeping the UI responsive
and active based on the user choices and loaded FumeFX VDB cache data.

![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_002c.jpg)
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_003c.jpg)
![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_004e.jpg)
`A little progression of navigating inside some of the layer of this HDA.`



![alt text](https://github.com/alexnardini/FFX_import/blob/master/imgs/ffx_import_h_005.jpg)

FFX import HDA come with a nice Help/Documentation. It does include also live web link to the online FumeFX documentation
anywhere a close correspondence of the feature you are using in order to set it correctly inside FumeFX to make it work.
