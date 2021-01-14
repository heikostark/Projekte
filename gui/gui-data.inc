{ *************************************** File ******************************* }

datanote_file := incnote_sub;
_page ('File ');
_vbox;
_expand;
      _vbox;
            _hbox;
            _hbox;
            _shrink;
                  {bfiledown := }_tooltip (_button (@xpm_yellow_down,@dir_down,@macro_self),'Copy dir to working dir');
                  fileed := _tooltip (_label,'Last file');
            _endbox;
            _endbox;
            _hbox;
            _hbox;
            _shrink;
                  {bdirup := }_tooltip (_button (@xpm_yellow_up,@dir_up,@macro_self),'Copy dir to file dir');
                  {bdir := }_tooltip (_button (@xpm_open,@dir_dialog,@macro_self),'Change working dir');
                  workdir := _tooltip (_label,'Working dir');;
            _endbox;
            _endbox;
      _endbox;
      _separator;
      _hbox;
            toggle_punctuation := _tooltip (_checkbutton ('1.0',@check_punctuation,@macro_self),'1.0 or 1,0'+#10+'<i>Note: Please check the correct input!</i>'); macro_self.putprocedure ('set.punctuation','','','Set punctuation (1.234)',@set_punctuation); macro_self.putprocedure ('unset.punctuation','','','Unset punctuation (1,234)',@unset_punctuation);
            toggle_format := _tooltip (_uncheckbutton ('<1, 1, 1, 1>',@check_format,@macro_self),'<1, 1, 1, 1> or 1, 1, 1, 1'); macro_self.putprocedure ('set.format','','','Set format (<0, 0, 0, 0>)',@set_format); macro_self.putprocedure ('unset.format','','','Unset format (0, 0, 0, 0)',@unset_format);
            toggle_exponent := _tooltip(_uncheckbutton ('1E+3',@check_exponent,@macro_self),'1E+3 or 1000'); macro_self.putprocedure ('set.exponent','','','Set exponent (10E2)',@set_exponent); macro_self.putprocedure ('unset.exponent','','','Unset exponent (1000)',@unset_exponent);
            toggle_deg_rad := _tooltip (_checkbutton ('deg',@check_deg_rad,@macro_self),'deg or rad'+#10+'<i>Note: Please check the correct input!</i>'); macro_self.putprocedure ('set.degree','','','Set degree (10°)',@set_degree); macro_self.putprocedure ('set.radian','','','Set radian (1.2 rad)',@set_radian);
            _label (' | ');
            _tooltip(_label ('Ignore:'),'Ignore points, vectors or lines when loading.');
            _hbox;
            _shrink;
                    load_ignore := _smalledit ('0'); _label ('%');
            _endbox;
      _endbox;
      _separator;
      _hbox;
            command (@xpm_new,' New project','','','','Creates a new project',@proc_new_project);
            command (@xpm_open,' Load project','','','','Load a project (layers and macros from a directory)',@proc_load_project);
            command (@xpm_save,' Save project','','','','Save a project (only active layers and macros to a directory)',@proc_save_project);
      _endbox;
      _separator;
      _hbox;
            command (@xpm_new,'New','new','','','Creates a new layer',@proc_new);
            command (@xpm_reopen,'Reload','reload','dots[bool] amount[0-100%]','','Reload a layer (x y z t [x y z t])',@proc_reload);
            command (@xpm_open,'Load','load','file dots[bool] amount[0-100%]','','Load a layer (x y z t [x y z t])',@proc_load,@proc_load_1);
            command (@xpm_save,'Save','save','dots[bool] vector[bool] scientific[bool]','','Save a layer (x [y [z [t]]])',@proc_save,@proc_save_1);
      _endbox;
      _separator;
      _hbox;
            command (@xpm_all_new,' New all','new.all','','','Creates new layers',@proc_newall);
            command (@xpm_all_reopen,' Reload all','reload.all','dots[bool] amount[0-100%]','','Reload all layers (x y z t [x y z t])',@proc_reloadall); { see reload }
            command (@xpm_all_open,' Load all','','','','Load all layers (x y z t [x y z t])',@proc_loadall); { see load }
            command (@xpm_all_save,' Save all','','','','Save all layers (x [y [z [t]]])',@proc_saveall); { see save }
      _endbox;
      _separator;
      _hbox;
            command (@xpm_open,' Load rows','load.rows','file','','Load a layer [rows are separated lines]',@proc_rows,@proc_rows_1);
            command (@xpm_save,' Save rows','save.rows','file','','Save a layer [rows are separated lines]',@proc_save_rows,@proc_save_rows_1);
            command (@xpm_open,' Load columns','load.columns','file','','Load a layer [colums are separated lines]',@proc_columns,@proc_columns_1);
            command (@xpm_save,' Save columns','save.columns','file','','Save a layer [colums are separated lines]',@proc_save_columns,@proc_save_columns_1);
      _endbox;
_endbox;
_endpage;

{ ********************************* Clipboard ******************************** }

inc(incnote_sub);
_page ('Clipboard ');
_vpanedbox;
_shrink;
           _vbox;
           _expand;
                 _hbox;
                       command (@xpm_clipboard_empty,'Clear','','','','Clear clipboard',@proc_clipboard_clear);
                       _label ('|');
                       command ('Get point','','','','Get selected point',@proc_clipboard_point);
                       command ('Get line','','','','Get selected line',@proc_clipboard_line);
                       command ('Get object','','','','Get selected object',@proc_clipboard_object);
                       command ('Get layer','','','','Get layer',@proc_clipboard_layer);
                       data_clipboard_digits := _smalledit ('5');
                 _endbox;
                 _hbox;
                       command ('Insert','','','','Insert in a layer (x y z t [x y z t])',@proc_clipboard_insert);
                       hidecommand ('Insert gaps','','','','Insert in a layer (x y z t [x y z t]) and fill up empty rows',@proc_clipboard_insert_gaps);
                       _label ('|');
                       command ('Insert rows','','','','Insert rows in a layer [rows are separated lines]',@proc_clipboard_insert_rows);
                       command ('Insert columns','','','','Insert columns in a layer [colums are separated lines]',@proc_clipboard_insert_columns);
                       _label ('|');
                       command ('Insert field','','','','Insert field in a layer [t] - t are the values',@proc_clipboard_insert_field);
                       _label ('|');
                       command (@xpm_new,'New','','','','Creates a new layer',@proc_new);
                 _endbox;
                 macro_self.putprocedure ('insert.line',@proc_insert_line); { only as command - insert.line <x,y,z> <x,y,z> ... }
           _endbox;
_expand;
      _hbox;
      _shrink;
           _vbox;
                 command ('P','clipboard.point','','','Copy points direct to the system clipboard',@proc_system_clipboard_point); macro_self.putfunction ('clipboard.point','','','Copy points direct to a variable',@proc_system_clipboard_point);
                 command ('L','clipboard.line','','','Copy lines direct to the system clipboard',@proc_system_clipboard_line);
                 command ('O','clipboard.object','','','Copy objects direct the to system clipboard',@proc_system_clipboard_object);
                 command ('A','clipboard.layer','','','Copy layer (all elements) direct to the system clipboard',@proc_system_clipboard_layer);
                 _label ('-');
                 command ('HL','clipboard.hline','','','Copy lines (horizontal) direct to the system clipboard',@proc_system_clipboard_hline);
                 command ('VL','clipboard.vline','','','Copy lines (vertical) direct to the system clipboard',@proc_system_clipboard_vline);
                 command ('H0','clipboard.hline.zero','','','Copy lines (horizontal without zeros) direct to the system clipboard',@proc_system_clipboard_hline_zero);
                 command ('V0','clipboard.vline.zero','','','Copy lines (vertical without zeros) direct to the system clipboard',@proc_system_clipboard_vline_zero);
           _endbox;
      _fill;
           _vbox;
           _fill;
                     _scrollbox;
                                   _edittext (clipboard);
                     _endbox;
           _endbox;
      _endbox;
_endbox;
_endpage;

{ ******************************* Microscribe ******************************** }

inc(incnote_sub);
datanote_inscribe := incnote_sub;
_page ('Inscribe ');
_vpanedbox;
_shrink;
        _vbox;
        _expand;
             _framebox ('Set virtual keyboard');
             _vbox;
             _expand;
                   _hbox;
                         command ('Set r','','','','Set virtual red vertex.',@proc_setred);
                         command ('Set g','','','','Set virtual green vertex.',@proc_setgreen);
                         command ('Set b','','','','Set virtual blue vertex.',@proc_setblue);
                         command ('Set y','','','','Set virtual yellow vertex.',@proc_setyellow);
                         command ('Set c','','','','Set virtual cyan vertex.',@proc_setcyan);
                         command ('Set p','','','','Set virtual purple vertex.',@proc_setpurple);
                   _endbox;
                   _hbox;
                         command ('Set newline','','','','Set virtual newline vertex.',@proc_setnewline);
                         command ('Set newobject','','','','Set virtual newobject vertex.',@proc_setnewobject);
                         _label ('|');
                         _label('Sensitivity radius:');
                         edit_microscribe_keyboard_sensitivity := _smalledit ('50');
                   _endbox;
             _endbox;
             _endbox;

             {_separator; see _framebox }

             _hbox;
                 _label ('Input:');
                 _vbox;
                 _expand;
                        m3dlabel := _label;
                 _endbox;
             _endbox;

        if not(small) then
        begin
            _hbox;
            _expand;
                  _buttonbox (@proc_input,@macro_self);
                          label_microscribe_input := _label;
                          _tooltip (label_microscribe_input,'Choice points, distances, lines or curves');
                  _endbox;
                   command ('New point','','','','Make a new point (keys: p P #)',@proc_mic_newpoint);
                   command ('New line','','','','Make a new line (keys: l L space)',@proc_mic_newline);
                   command ('New object','','','','Make a new object (keys: o O return)',@proc_mic_newobject);
            _endbox;

            _separator;

            _hbox;
            _expand;
                  _button (@xpm_left,@m3ll,@macro_self);
                  _button (@xpm_leftleft,@m3lll,@macro_self);
                  _button (@xpm_leftstop,@m3lls,@macro_self);
                  m3dstat := _label;
                  _button (@xpm_rightstop,@m3lrs,@macro_self);
                  _button (@xpm_rightright,@m3lrr,@macro_self);
                  _button (@xpm_right,@m3lr,@macro_self);
            _endbox;

        _expand;
           _vbox;
           _fill;
                  _scrollbox;
                  _text (m3dstat1);
                  _endbox;
           _endbox;
        end;
        _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('Import ');
_vbox;
_expand;
      _hbox;
            command ('Files with date','import.date','file','','Read files with date (x y z date [x y z date])',@proc_import_date,@proc_import_date_1);
      _endbox;
      _separator;
      _hbox;
            command ('Splited files','import.split','file begin end','','Read files and split in two (source & destination)',@proc_import_split,@proc_import_split_1);
            _label ('Destination:');
            import_begin := _tooltip(_edit ('Begin'),'Start with split into destination.');
            import_end := _tooltip(_edit ('End'),'End with split for destination.');
      _endbox;
      _separator;
      _hbox;
            command ('Triggered files','load.trigger','file value[real] centre[0-100%]','','Read files [colums are separated lines] and split it after trigger',@proc_columns_trigger,@proc_columns_trigger_1);
            _tooltip(_label ('Trigger:'),'Trigger value.'); export_trigger_value := _smalledit ('1');
            _tooltip(_label ('Centre:'),'Centre of trigger.');
            _hbox;
            _shrink;
                    export_trigger_centre := _smalledit ('50'); _label ('%');
            _endbox;
      _endbox;
      _separator;
      _hbox;
            _tooltip(_label ('Header:'),'Position of header (first row) – 0 = no header'); import_header := _smalledit ('0');
            _tooltip(_label ('Index:'),'Position of index (first column) – 0 = no index'); import_index := _smalledit ('0');
      _endbox;
      _hbox;
            command ('Rows','load.line.rows','','','Read line [x,y] - in y are the values after header & index and without # lines',@proc_line_rows,@proc_line_rows_1);
            command ('Columns','load.line.columns','','','Read line [x,y] - in y are the values after header & index and without # lines',@proc_line_columns,@proc_line_columns_1);
      _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('2D ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Import field:</b>');
            _expand;
            command ('Field','load.field','','','Read field [x,y,z] - in z are the values without 0',@proc_field,@proc_field_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Import bitmap:</b>');
            _expand;
            command ('Gray','load.gray','','','Read gray-bitmap [x,y,z] - in z are the gray values without 0',@proc_gray,@proc_gray_1);
            command ('RGB –≻ Gray','load.rgb.gray','','','Read rgb-bitmap [x,y,z] - in z are the r+g+b values without 0',@proc_rgb_gray,@proc_rgb_gray_1);
            command ('RGB','load.rgb','','','Read rgb-bitmap [x,y,z] - in z are the r|g|b values separated as objects without 0',@proc_rgb,@proc_rgb_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('                            ');
            _expand;
            command ('RGB –≻ Point','load.rgb.point','','','Read rgb-bitmap [r,g,b] –≻ [x,y,z]',@proc_rgb_point,@proc_rgb_point_1);
            command ('RGB –≻ Count','load.rgb.count','','','Read rgb-bitmap [r,g,b,count] –≻ [x,y,z,t]',@proc_rgb_count,@proc_rgb_count_1);
            command ('(RGB shr 1)–≻Count','load.rgb.halfcount','','','Read rgb-bitmap [r,g,b,count] –≻ [x,y,z,t]',@proc_rgb_halfcount,@proc_rgb_halfcount_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Import Matlab:</b>');
            _expand;
            command ('Points','import.matlab.2dpoints','','','Read 2d points from Matlab-file - scatter (x,y)',@proc_import_matlab_2dpoints,@proc_import_matlab_2dpoints_1);
            command ('Vectors','import.matlab.2dvectors','','','Read 2d vectors from Matlab-file - quiver (x,y,u,v)',@proc_import_matlab_2dvectors,@proc_import_matlab_2dvectors_1);
            command ('Lines','import.matlab.2dlines','','','Read 2d lines from Matlab-file - plot (x1,y1,x2,y2,...)',@proc_import_matlab_2dlines,@proc_import_matlab_2dlines_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>Export Matlab:</b>');
            _expand;
            command (@xpm_save,'Points','export.matlab.2dpoints','','','Write points to Matlab-file for scatter (x,y)',@proc_export_matlab_2dpoints,@proc_export_matlab_2dpoints_1);
            command (@xpm_save,'Vectors','export.matlab.2dvectors','','','Write vectors to Matlab-file for quiver (x,y,u,v)',@proc_export_matlab_2dvectors,@proc_export_matlab_2dvectors_1);
            command (@xpm_save,'Lines','export.matlab.2dlines','','','Write lines to Matlab-file for plot (x1,y1,x2,y2,...)',@proc_export_matlab_2dlines,@proc_export_matlab_2dlines_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Recurrence plot:</b>');
            _expand;
            command ('Gray points','export.recurrence','','','Export recurrence plot length[x,y,z] -> gray',@proc_export_recurrence,@proc_export_recurrence_1);
            command ('Gray gap points','export.recurrence.gaps','','','Export recurrence plot length[x,y,z] -> gray with gaps for lines',@proc_export_recurrence_gaps,@proc_export_recurrence_gaps_1);
            command ('RGB points','export.recurrence.rgb','','','Export recurrence plot [x,y,z] -> [rgb]',@proc_export_recurrence_rgb,@proc_export_recurrence_rgb_1);
            command ('RGB gap points','export.recurrence.rgb.gaps','','','Export recurrence plot [x,y,z] -> [rgb] with gaps for lines',@proc_export_recurrence_rgb_gaps,@proc_export_recurrence_rgb_gaps_1);
      _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('3D Import ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Mesh (obj, dxf, iv, stl):</b>');
            _expand;
            command ('Points','import.mesh.points','','','Read points from mesh-file',@proc_import_mesh_points,@proc_import_mesh_points_1);
            command ('Normals','import.mesh.normals','','','Read normals from mesh-file',@proc_import_mesh_normals,@proc_import_mesh_normals_1);
            command ('Areas','import.mesh.faces','','','Read triangles from mesh-file',@proc_import_mesh_faces,@proc_import_mesh_faces_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>OBJ:</b>');
            _expand;
            command ('Points','import.obj.points','','','Read points from obj-file',@proc_import_obj_points,@proc_import_obj_points_1);
            command ('Normals','import.obj.normals','','','Read normals from obj-file',@proc_import_obj_normals,@proc_import_obj_normals_1);
            command ('Lines','import.obj.faces','','','Read lines (points, vectors, triangles and polylines) from obj-file',@proc_import_obj_faces,@proc_import_obj_faces_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>DXF:</b>');
            _expand;
            command ('Splines','import.dxf.splines','','','Read splines from dxf-file',@proc_import_dxf_splines,@proc_import_dxf_splines_1);
            command ('Lines','import.dxf.lines','','','Read lines from dxf-file',@proc_import_dxf_lines,@proc_import_dxf_lines_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>VTK:</b>');
            _expand;
            command ('Polygonal data','import.vtk.poly','','','Read polygonal data (points, lines or faces) from vtk-file (ascii)',@proc_import_vtk,@proc_import_vtk_1);
            command ('Unstructured grid','import.vtk.grid','','','Read unstructured grid (with cells) from vtk-file (ascii)',@proc_import_vtk_vectors,@proc_import_vtk_vectors_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Matlab:</b>');
            _expand;
            command ('Points','import.matlab.points','','','Read points from Matlab-file - scatter3 (x,y,z)',@proc_import_matlab_points,@proc_import_matlab_points_1);
            command ('Vectors','import.matlab.vectors','','','Read vectors from Matlab-file - quiver3 (x,y,z,u,v,w)',@proc_import_matlab_vectors,@proc_import_matlab_vectors_1);
            command ('Lines','import.matlab.lines','','','Read lines from Matlab-file - plot3 (x1,y1,z1,x2,y2,z2,...)',@proc_import_matlab_lines,@proc_import_matlab_lines_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>TrackVis:</b>');
            _expand;
            command ('Tracks','import.trackvis','','','Read tracks from TrackVis (DTI)',@proc_import_trackvis,@proc_import_trackvis_1);
            _label ('Min. points:');
            export_trackvis := _edit ('10');
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>SWC:</b>');
            _expand;
            command ('Neurons','import.swc','','','Read neurons from SWC file',@proc_import_swc,@proc_import_swc_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Amira:</b>');
            _expand;
            command ('Vectors','import.amira.vectors','','','Read vectors from Amira',@proc_none);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Sphere-Tree:</b>');
            _expand;
            command ('Spheres','import.sphere-tree','','','Read spheres from Sphere-Tree Construction Toolkit',@proc_import_sphere_tree,@proc_import_sphere_tree_1);
      _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('3D Export ');
_vbox;
_expand;
     _hbox;
           _shrink;
           _label ('<b>OBJ:</b>');
           _expand;
           command (@xpm_save,'P L & F','export.obj','','','Write points, lines and faces to obj-file (x y z)',@proc_export_obj,@proc_export_obj_1);
           command (@xpm_save,'*P *L & *F','export.ref.obj','','','Write connected points, lines and faces to obj-file (x y z)',@proc_export_ref_obj,@proc_export_ref_obj_1);
           command (@xpm_save,'only Mesh','export.mesh.obj','','','Write solid mesh [4,5,6 faces] (ignore points and lines) to obj-file (x y z)',@proc_export_mesh_obj,@proc_export_mesh_obj_1);
     _endbox;
     _hbox;
           _shrink;
           _label ('                      ');
           _expand;
           command ('Tubes','export.tube.obj','','','Write lines as cubic tubes to obj-file (x y z)',@proc_export_tube_obj,@proc_export_tube_obj_1);
           _label ('Size:'); export_obj_tube_size := _smalledit('1');
     _endbox;
     _hbox;
            _shrink;
            _label ('<b>DXF:</b>');
            _expand;
            command (@xpm_save,'Points and lines','export.dxf','','','Write points and lines to dxf-file (x y z)',@proc_export_dxf,@proc_export_dxf_1);
     _endbox;
     _separator;
     _hbox;
           _shrink;
           _label ('<b>MEL script:</b>');
           _expand;
           command (@xpm_save,'Polylines','export.maya','','','Write lines to mel-file (Maya)',@proc_export_mel,@proc_export_mel_1);
     _endbox;
     _hbox;
           _shrink;
           _label ('<b>PY script:</b>');
           _expand;
           export_blender := _combobox;
                             _item ('Nurbs');
                             _item ('Metaball');
                             _item ('low res UV-Mesh');
                             _item ('high res UV-Mesh');
                             _item ('low res Ico-Mesh');
                             _item ('high res Ico-Mesh');
           _endcombobox (0);
           command (@xpm_save,'Points','export.blender.points','','','Write points (also line points) to py-file (Blender)',@proc_export_py,@proc_export_py_1);
           command (@xpm_save,'Lines','export.blender.lines','','','Write points and lines to py-file (Blender)',@proc_export_py_lines,@proc_export_py_lines_1);
     _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Matlab:</b>');
            _expand;
            command (@xpm_save,'Points','export.matlab.points','','','Write points to Matlab-file for scatter3 (x,y,z)',@proc_export_matlab_points,@proc_export_matlab_points_1);
            command (@xpm_save,'Vectors','export.matlab.vectors','','','Write vectors to Matlab-file for quiver3 (x,y,z,u,v,w)',@proc_export_matlab_vectors,@proc_export_matlab_vectors_1);
            command (@xpm_save,'Lines','export.matlab.lines','','','Write lines to Matlab-file for plot3 (x1,y1,z1,x2,y2,z2,...)',@proc_export_matlab_lines,@proc_export_matlab_lines_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>TrackVis:</b>');
            _expand;
            command (@xpm_save,'Tracks','export.trackvis','','','Write tracks to TrackVis (DTI)',@proc_export_trackvis,@proc_export_trackvis_1);
            export_trackvis_toggle_olddim := _checkbutton ('Imported dim values');
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>SWC:</b>');
            _expand;
            command ('Neurons','export.swc','','','Write neurons/tracks to SWC file',@proc_export_swc,@proc_export_swc_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Amira:</b>');
            _expand;
            command (@xpm_save,'Vectors','export.amira.vectors','','','Write vectors to Amira',@proc_export_amira_vectors,@proc_export_amira_vectors_1);
            _label ('Steps:');
            export_amira_step := _edit ('1');
      _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('Mol ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Import PDB:</b>');
            _expand;
            import_pdb := _combobox;
                             _item ('Atomic');
                             _item ('Ionic');
                             _item ('Van der Waals');
            _endcombobox (0);
      _endbox;
      _hbox;
            _shrink;
            _label ('                      ');
            _expand;
            macro_self.putprocedure ('import.pdb.info',@proc_import_pdb_info_1);
            command ('Atom','import.pdb.atom','file [radius mode]','','Read atoms from pdb-file',@proc_import_pdb_data,@proc_import_pdb_data_1);
            command ('Atom & Links','import.pdb.atom.link','file [radius mode]','','Read atoms and links from pdb-file',@proc_import_pdblink_data,@proc_import_pdblink_data_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('                      ');
            _expand;
            command ('Atom & Backbone','import.pdb.backbone','file [radius mode]','','Read atoms from pdb-file (backbone atoms are negative)',@proc_import_pdbbb_data,@proc_import_pdbbb_data_1);
            command ('Aminoacid (P)','import.pdb.paa','file [radius mode]','','Read aminoacids as points from pdb-file',@proc_import_pdbpaa_data,@proc_import_pdbpaa_data_1);
            command ('Aminoacid (L)','import.pdb.laa','file [radius mode]','','Read aminoacids as line from pdb-file',@proc_import_pdblaa_data,@proc_import_pdblaa_data_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Export Seq:</b>');
            _expand;
            _hbox;
                  _shrink;
                  command (@xpm_save,'Triplets','export.triplets','sb','','Write triplet code',@proc_export_triplets,@proc_export_triplets_1);
                  command (@xpm_save_plus,'append.triplets','sb','','Append triplet code',@proc_append_triplets,@proc_append_triplets_1);
            _endbox;
            _hbox;
                  toggle_seq_empty := _tooltip (_uncheckbutton ('Empty'),'Store empty triplets or aminoacids sequences');
            _endbox;
            _hbox;
                  _shrink;
                  command (@xpm_save,'Aminoacids','export.aminoacids','sb','','Write aminoacid short code',@proc_export_aminoacids,@proc_export_aminoacids_1);
                  command (@xpm_save_plus,'append.aminoacids','sb','','Append aminoacid short code',@proc_append_aminoacids,@proc_append_aminoacids_1);
            _endbox;
      _endbox;
_endbox;
_endpage;

inc(incnote_sub);
_page ('FEBio ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _tooltip (_label ('<b>Import FEBio:</b>'),'Reads febio output file. (The first entry [1] is the element number!)');
            _expand;
            _tooltip (_label ('Mask:'),'Febio mask substitutions from [123456789ABCDEF] to [23415671].');
            import_febio_mask := _edit ('23415671');
      _endbox;
      _separator;
      _hbox;
            _label ('From time:'); import_febio_from_time := _edit ('0');
            _label ('To:'); import_febio_to_time := _edit ('1');
      _endbox;
      _hbox;
            _label ('From step:'); import_febio_from_step := _edit ('1');
            _label ('To:'); import_febio_to_step := _edit ('999999');
      _endbox;
      _hbox;
            command ('Info','import.febio.info','','','Read only first entry after mask [2,3,4,1] (ignore time and step)',@proc_import_febio_info,@proc_import_febio_info_1);
            command ('Point','import.febio.point','','','Read entries after mask [2,3,4,1]',@proc_import_febio_point,@proc_import_febio_point_1);
            command ('Vector','import.febio.vector','','','Read entries after mask [2,3,4,1] [5,6,7,1]',@proc_import_febio_vector,@proc_import_febio_vector_1);
            command ('Line','import.febio.line','','','Read entries after mask [2,3,4,1] ...',@proc_import_febio_line,@proc_import_febio_line_1);
      _endbox;
      _hbox;
            command ('ΔPoint','import.febio.dpoint','','','Read entries (delta from time zero) after mask [2,3,4,1]',@proc_import_febio_dpoint,@proc_import_febio_dpoint_1);
            command ('ΔVector','import.febio.dvector','','','Read entries (delta from time zero) after mask [2,3,4,1] [5,6,7,1]',@proc_import_febio_dvector,@proc_import_febio_dvector_1);
            command ('ΔLine','import.febio.dline','','','Read entries (delta from time zero) after mask [2,3,4,1] ...',@proc_import_febio_dline,@proc_import_febio_dline_1);
      _endbox;
      _separator;
      _hbox;
            _tooltip (_label ('Raster:'),'Grid/Raster width.');
            import_febio_raster := _edit ('1');
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>1D:</b>');
            _expand;
            command ('Sum lines','import.febio.line.sum','','','Read t entries (as sum on x) after mask [2,3,4,5]',@proc_import_febio_line_sum,@proc_import_febio_line_sum_1);
            command ('Sum double','import.febio.dline.sum','','','Read t entries (as sum on x | for -y and y) after mask [2,3,4,5]',@proc_import_febio_dline_sum,@proc_import_febio_dline_sum_1);
            command ('Mean lines','import.febio.line.mean','','','Read t entries (as mean on x) after mask [2,3,4,5]',@proc_import_febio_line_mean,@proc_import_febio_line_mean_1);
            command ('Mean double','import.febio.dline.mean','','','Read t entries (as mean on x | for -y and y) after mask [2,3,4,5]',@proc_import_febio_dline_mean,@proc_import_febio_dline_mean_1);
      _endbox;
      _hbox;
            _shrink;
            _label ('<b>2D:</b>');
            _expand;
            command ('Sum planes','import.febio.plane.sum','','','Read t entries (as sum on x y) after mask [2,3,4,5]',@proc_import_febio_plane_sum,@proc_import_febio_plane_sum_1);
            command ('Sum double','import.febio.dplane.sum','','','Read t entries (as sum on x y | for -z and z) after mask [2,3,4,5]',@proc_import_febio_dplane_sum,@proc_import_febio_dplane_sum_1);
            command ('Mean planes','import.febio.plane.mean','','','Read t entries (as mean on x y) after mask [2,3,4,5]',@proc_import_febio_plane_mean,@proc_import_febio_plane_mean_1);
            command ('Mean double','import.febio.dplane.mean','','','Read t entries (as mean on x y | for -z and z) after mask [2,3,4,5]',@proc_import_febio_dplane_mean,@proc_import_febio_dplane_mean_1);
      _endbox;
      _hbox;
            _label ('<i>Note: You can rearrange n,x,y,z [1234] via Mask –≻ z,y,x [432]!</i>');
      _endbox;
_endbox;
_endpage;

{$ifndef free}
inc(incnote_sub);
_page ('GPS ');
_vbox;
_expand;
      _hbox;
            _shrink;
            _label ('<b>Import TRK:</b>');
            _expand;
            command ('Lines','import.gps.data','','','Read lines from magellan track-file',@proc_import_gps_data,@proc_import_gps_data_1);
      _endbox;
      _separator;
      _hbox;
            _shrink;
            _label ('<b>Export TRK:</b>');
            _expand;
      _endbox;

_endbox;
_endpage;
{$endif}