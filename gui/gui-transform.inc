{ *********************************** Transform ****************************** }

_page ('Info ');
_eventbox;
_backcolor ($FFFF,$FFFF,$BFFF);
      _vbox;
            _label ('<b>Bold</b> - Single selection - LMB');
            _label ('<span foreground="#FF8000">Color</span> - Multiple selection - RMB');
            _separator;
            _label ('<b>Source</b>');
            _label ('All operations work on multiple selected sources.');
            _label;
            _label ('<b>Destination</b>  (=<i>Reference</i>)');
            _label ('All operations work with multiple selected references.');
            _separator;
            _label ('<i>Note: Only multiple selection of destinations have a focus.</i>');
            if table_long then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_wide then _label ('<i>Control + Click on screen (xy and zt) to take a screenshot.</i>')
            else if table_special then _label ('<i>Control + Click on screen (xy, xz, xt) to take a screenshot.</i>')
            else _label ('<i>Control + Click on screen (xy, xz, yz) to take a screenshot.</i>');
      _endbox;
_endbox;
_endpage;


_page ('Transform ');
_vbox;
_expand;
      _hbox;
           if table_long then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else if table_wide then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else if table_special then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 command ('(F4) Screen XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 command ('(F3) Screen YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end;
       _endbox;
      _label ('<i>Note: Operations works only on selected screens!</i>');
      _label ('<i>(With exception of center and scale)</i>');
      _separator;
      _hbox;
            command ('_Center','transform.center','','','Center layer',@proc_transform_center);
            _label (' | ');
            command (@xpm_left,'transform.move.left','','','Move left',@movel); { for compatibility }
            command (@xpm_up,'transform.move.up','','','Move up',@moveu); { for compatibility }
            command (@xpm_down,'transform.move.down','','','Move down',@moved); { for compatibility }
            command (@xpm_right,'transform.move.right','','','Move right',@mover); { for compatibility }
            _label ('Motion step:');
            transform_move := _smalledit('1');
            { Special replace upper commands }  macro_self.putprocedure ('transform.move','','','',@proc_move);
      _endbox;
      _separator;
     _hbox;
            { ??? Move <x,y,z,t> ??? }
            { ??? Norm ??? }
            { ??? Scale step ??? }
            { ??? Rotate <x,y,z,t> ??? }
            command ('InvScale','transform.invscale','','','Let''s inverse scale layers around origin',@proc_invscale);
            _tooltip (_label (' o '),'Origin');
            command ('Scale','transform.scale','','','Let''s scale layers around origin',@proc_scale);
             _label ('Step:');
             transform_scale := _edit('<1, 1, 1, 1>');
             command ('Scale','transform.scale.pivot','','','Let''s scale layers around pivot',@proc_scale_pivot);
             _tooltip (_label (' x '),'Pivot');
             command ('InvScale','transform.invscale.pivot','','','Let''s inverse scale layers around pivot',@proc_invscale_pivot);
     _endbox;
     _hbox;
             command ('Giga','transform.gigascale','','','Let''s (1 000 000 000 *) scale layers around origin',@proc_gigascale);
             command ('Mega','transform.megascale','','','Let''s (1 000 000 *) scale layers around origin',@proc_megascale);
             command ('Kilo','transform.kiloscale','','','Let''s (1 000 *) scale layers around origin',@proc_kiloscale);
             command ('Hecto','transform.hectoscale','','','Let''s (100 *) scale layers around origin',@proc_hectoscale);
             command ('Deca','transform.decascale','','','Let''s (10 *) scale layers around origin',@proc_decascale);
             _tooltip (_label (' 1 '),'No scaling');
             command ('Deci','transform.deciscale','','','Let''s (0.1 *) scale layers around origin',@proc_deciscale);
             command ('Centi','transform.centiscale','','','Let''s (0.01 *) scale layers around origin',@proc_centiscale);
             command ('Milli','transform.milliscale','','','Let''s (0.001 *) scale layers around origin',@proc_milliscale);
             command ('Micro','transform.microscale','','','Let''s (0.000 001 *) scale layers around origin',@proc_microscale);
             command ('Nano','transform.nanoscale','','','Let''s (0.000 000 001 *) scale layers around origin',@proc_nanoscale);
     _endbox;
     _separator;
     _hbox;
            _hbox;
            _shrink;
                    command (@xpm_redo,'transform.rotate.right','','','Rotate right around origin',@rotr); { for compatibility }
                    _tooltip (_label (' o '),'Origin');
                    command (@xpm_undo,'transform.rotate.left','','','Rotate left around origin',@rotl); { for compatibility }
                    { Special replace upper commands }  macro_self.putprocedure ('transform.rotate','','','',@proc_rotate);
            _endbox;
            _label ('Angle:');
            transform_rotation := _tooltip(_smalledit ('45'),'For degree or radian see Data≻File');
            _hbox;
            _shrink;
                    command (@xpm_redo,'transform.rotate.pivot.right','','','Rotate right around pivot',@rotor); { for compatibility }
                    _tooltip (_label (' x '),'Pivot');
                    command (@xpm_undo,'transform.rotate.pivot.left','','','Rotate left around pivot',@rotol);  { for compatibility }
                    { Special replace upper commands }  macro_self.putprocedure ('transform.rotate.pivot','','','',@proc_rotate_pivot);
            _endbox;
     _endbox;
     _hbox;
           _hbox;
           _shrink;
                   command (@xpm_redo,'transform.rotate.vector.right','','','Rotate right around origin',@rotvr); { for compatibility }
                   _tooltip (_label (' o '),'Origin');
                   command (@xpm_undo,'transform.rotate.vector.left','','','Rotate left around origin',@rotvl); { for compatibility }
                   { Special replace upper commands }  macro_self.putprocedure ('transform.rotate.vector','','','',@proc_rotate_vector);
            _endbox;
            _label ('Around vector:');
            transform_vector := _edit ('<1, 0, 0>');
            _hbox;
            _shrink;
                    command (@xpm_redo,'transform.rotate.pivot.vector.right','','','Rotate right around pivot',@rotvor); { for compatibility }
                    _tooltip (_label (' x '),'Pivot');
                    command (@xpm_undo,'transform.rotate.pivot.vector.left','','','Rotate left around pivot',@rotvol);  { for compatibility }
                    { Special replace upper commands }  macro_self.putprocedure ('transform.rotate.pivot.vector','','','',@proc_rotate_pivot_vector);
            _endbox;
     _endbox;
_endbox;
_endpage;

_page ('T≻ ');
_vbox;
_expand;
     _hbox;
            _label (' ');
            transform_vector1 := _edit ('<1, 0, 0>');
            _tooltip (_label ('from –≻ vector –≻ to'),'Similar to rotate around vector with (v1 angle v2) and (v1xv2).');
            transform_vector2 := _edit ('<0, 0, 1>');
            _label (' ');
     _endbox;
     _hbox;
           _label (' ');
            command ('Rotate to','transform.rotate.to','','','Rotate to new vector',@proc_rotate_to);
            command ('Swap vectors','transform.rotate.swap','','','Swap vectors',@proc_rotate_swap);
            command ('Rotate relative to','transform.rotate.pivot.to','','','Rotate to new vector around pivot',@proc_rotate_pivot_to);
            _label (' ');
     _endbox;
     _separator;
     _hbox;
            _label (' ');
            _label ('Tait-Bryan (Cardan) angles:'); transform_cardan := _tooltip(_edit ('<0, 0, 0>'),'For degree or radian see Data≻File');
            _label (' ');
     _endbox;
     _hbox;
            command ('X – Y'' – Z''''','transform.rotate.xyz','','','Rotate around cardan angles',@proc_transform_rotate_xyz);
            command ('X – Z'' – Y''''','transform.rotate.xzy','','','Rotate around cardan angles',@proc_transform_rotate_xzy);
            command ('Y – X'' – Z''''','transform.rotate.yxz','','','Rotate around cardan angles',@proc_transform_rotate_yxz);
            command ('Y – Z'' – X''''','transform.rotate.yzx','','','Rotate around cardan angles',@proc_transform_rotate_yzx);
            command ('Z – X'' – Y''''','transform.rotate.zxy','','','Rotate around cardan angles',@proc_transform_rotate_zxy);
            command ('Z – Y'' – X''''','transform.rotate.zyx','','','Rotate around cardan angles',@proc_transform_rotate_zyx);
     _endbox;
     _hbox;
            _label (' ');
            _label ('Euler angles:'); transform_euler := _tooltip(_edit ('<0, 0, 0>'),'For degree or radian see Data≻File');
            _label (' ');
     _endbox;
     _hbox;
            command ('X – Y'' – X''''','transform.rotate.xyx','','','Rotate around euler angles',@proc_transform_rotate_xyx);
            command ('X – Z'' – X''''','transform.rotate.xzx','','','Rotate around euler angles',@proc_transform_rotate_xzx);
            command ('Y – X'' – Y''''','transform.rotate.yxy','','','Rotate around euler angles',@proc_transform_rotate_yxy);
            command ('Y – Z'' – Y''''','transform.rotate.yzy','','','Rotate around euler angles',@proc_transform_rotate_yzy);
            command ('Z – X'' – Z''''','transform.rotate.zxz','','','Rotate around euler angles',@proc_transform_rotate_zxz);
            command ('Z – Y'' – Z''''','transform.rotate.zyz','','','Rotate around euler angles',@proc_transform_rotate_zyz);
     _endbox;
      _separator;
      _hbox;
             command ('_Center','','','','Center layer',@proc_transform_center); { siehe move }
             _label ('+');
             command ('_Global','transform.balance.global','','','Global balance layer',@proc_transform_globalbalance);
             _label ('+');
             command ('_Local','transform.balance.local','','','Local (specific screen) balance layer',@proc_transform_localbalance);
             _label ('+');
             command ('MaxX','transform.balance.maxx','','','Maximal x (specific screen) balance layer',@proc_transform_maxxbalance);
             command ('MaxY','transform.balance.maxy','','','Maximal y (specific screen) balance layer',@proc_transform_maxybalance);
      _endbox;
      _hbox;
             _label ('=');
      _endbox;
      _hbox;
            _label (' ');
             command ('_Adjust','transform.adjust','','','Center, global balance, screen3(local balance and maxy) and screen1(maxx)',@proc_transform_adjust);
             command ('Fast adjust','transform.adjust.fast','','','Center, fast global balance (imprecise - 5%), screen3(imprecise local balance and maxy) and screen1(maxx)',@proc_transform_adjust_fast);
             command ('Adjust lines','transform.adjust.lines','','','Center and balance each line',@proc_transform_adjust_lines);
            _label (' ');
      _endbox;
_endbox;
_endpage;

_page ('Matrix ');
_vbox;
_expand;
      _hbox;
             command ('Move','transform.matrix.move','','','Set matrix move',@proc_transform_matrix_move_set);
             command ('Zero move','transform.matrix.move.zero','','','Reset matrix move',@proc_transform_matrix_move_reset);
             command ('Scale','transform.matrix.scale','','','Set matrix scale',@proc_transform_matrix_scale_set);
             command ('Norm scale','transform.matrix.scale.norm','','','Norm matrix scale',@proc_transform_matrix_scale_norm);
             _label ('Vector:');
             transform_matrix_set := _edit ('<10, 10, 10>');
      _endbox;
      _hbox;
             command ('Shear xy','transform.matrix.shear.xy','','','Set matrix shear along xy',@proc_transform_matrix_shearxy); macro_self.putprocedure ('transform.matrix.shear.yx','','','Set matrix shear along xy',@proc_transform_matrix_shearxy);
             command ('Shear xz','transform.matrix.shear.xz','','','Set matrix shear along xz',@proc_transform_matrix_shearxz); macro_self.putprocedure ('transform.matrix.shear.zx','','','Set matrix shear along xz',@proc_transform_matrix_shearxz);
             command ('Shear yz','transform.matrix.shear.yz','','','Set matrix shear along yz',@proc_transform_matrix_shearyz); macro_self.putprocedure ('transform.matrix.shear.zy','','','Set matrix shear along yz',@proc_transform_matrix_shearyz);
             _label ('Vector:');
             transform_matrix_set2 := _edit ('<10, 10>');
      _endbox;
      _hbox;
             command ('Rotation x','transform.matrix.rotation.x','','','Set matrix rotation around x',@proc_transform_matrix_rotatex);
             command ('Rotation y','transform.matrix.rotation.y','','','Set matrix rotation around y',@proc_transform_matrix_rotatey);
             command ('Rotation z','transform.matrix.rotation.z','','','Set matrix rotation around z',@proc_transform_matrix_rotatez);
             _label ('Angle:');
             transform_matrix_rotation := _tooltip(_smalledit ('45'),'For degree or radian see Data≻File');
      _endbox;
      _hbox;
             command ('Mirror x','transform.matrix.mirror.x','','','Set matrix mirror along x',@proc_transform_matrix_mirrorx);
             command ('Mirror y','transform.matrix.mirror.y','','','Set matrix mirror along y',@proc_transform_matrix_mirrory);
             command ('Mirror z','transform.matrix.mirror.z','','','Set matrix mirror along z',@proc_transform_matrix_mirrorz);
             _label (' ');
             _label (' ');
      _endbox;
      _separator;
      _hbox;
             _vbox;
                   command ('Identity','transform.matrix.identity','','','Reset transformation matrix to identity matrix',@proc_transform_matrix_identity);
                   command ('Norm','transform.matrix.norm','','','Norm transformation matrix',@proc_transform_matrix_norm);
                   command ('Transpose','transform.matrix.transpose','','','Transpose transformation matrix',@proc_transform_matrix_transpose);
                   command ('Adjugate','transform.matrix.adjugate','','','Adjugate transformation matrix',@proc_transform_matrix_adjugate);
                   command ('Inverse','transform.matrix.inverse','','','Inverse matrix',@proc_transform_matrix_inverse);
                   { Special replace all upper commands }  macro_self.putprocedure ('transform.matrix.set','','','',@proc_transform_matrix_set);
             _endbox;
             _vbox;
                  _hbox; transform_matrix_1_1 := _smalledit ('1'); transform_matrix_2_1 := _smalledit ('0'); transform_matrix_3_1 := _smalledit ('0'); transform_matrix_4_1 := _smalledit ('0'); _endbox;
                  _hbox; transform_matrix_1_2 := _smalledit ('0'); transform_matrix_2_2 := _smalledit ('1'); transform_matrix_3_2 := _smalledit ('0'); transform_matrix_4_2 := _smalledit ('0'); _endbox;
                  _hbox; transform_matrix_1_3 := _smalledit ('0'); transform_matrix_2_3 := _smalledit ('0'); transform_matrix_3_3 := _smalledit ('1'); transform_matrix_4_3 := _smalledit ('0'); _endbox;
                  _hbox; transform_matrix_1_4 := _smalledit ('0'); transform_matrix_2_4 := _smalledit ('0'); transform_matrix_3_4 := _smalledit ('0'); transform_matrix_4_4 := _smalledit ('1'); _endbox;
             _endbox;
             _vbox;
                   transform_clipboard_digits := _smalledit ('5');
                   command ('Matrix','clipboard.matrix','','','Copy matrix direct to the system clipboard',@proc_get_matrix);
                           macro_self.putfunction ('clipboard.matrix','','','Copy matrix direct to a variable',@proc_get_matrix);
                   _hbox;
                         command ('M3','clipboard.matrix.3x3','','','Copy 3x3 matrix (scale & rotation) direct to the system clipboard',@proc_get_matrix3);
                                 macro_self.putfunction ('clipboard.matrix.3x3','','','Copy 3x3 matrix (scale & rotation) direct to a variable',@proc_get_matrix3);
                         command ('Move','clipboard.matrix.move','','','Copy vector (translation) direct to the system clipboard',@proc_get_vector);
                                 macro_self.putfunction ('clipboard.matrix.move','','','Copy vector (translation) direct to a variable',@proc_get_vector);
                   _endbox;
                   _separator;
                   _hbox;
                         command ('S','transform.eigen','','','Show eigenvectors of symmatrix',@proc_show_eigen);
                         _vbox;
                         command ('E-values','clipboard.matrix.e-values','','','Copy eigenvalues of symmatrix direct to the system clipboard',@proc_get_eigenvalues);
                                 macro_self.putfunction ('clipboard.matrix.e-values','','','Copy eigenvalues of symmatrix direct to a variable',@proc_get_eigenvalues);
                                 macro_self.putfunction ('clipboard.matrix.e-values.norm','','','Copy normed eigenvalues of symmatrix direct to a variable',@proc_get_eigenvalues_norm);
                                 macro_self.putfunction ('clipboard.matrix.e-values.westin','','','Copy westin plot of symmatrix direct to a variable',@proc_get_eigenvalues_westin);
                                 macro_self.putfunction ('clipboard.matrix.e-values.westin.rank','','','Copy westin rank plot of symmatrix direct to a variable',@proc_get_eigenvalues_westin_rank);
                         command ('E-vectors','clipboard.matrix.e-vectors','','','Copy eigenvectors of symmatrix direct to the system clipboard',@proc_get_eigenvectors);
                                 macro_self.putfunction ('clipboard.matrix.e-vectors','','','Copy eigenvectors of symmatrix direct to a variable',@proc_get_eigenvectors);
                         _endbox;
                   _endbox;
             _endbox;
      _endbox;
      _separator;
      _hbox;
             command ('Transform','transform.matrix','','','Transform (active) with matrix',@proc_transform_matrix);
             _label ('|');
             command ('det =','','','','Calculate determinate',@proc_transform_determinate); transform_det := _smalledit ('0');
             _label ('|');
             command ('Back transform','transform.matrix.back','','','Transform (passive) with inverse matrix',@proc_transform_matrix_back);
      _endbox;
_endbox;
_endpage;

_page ('Objects ');
_vbox;
_expand;
      _hbox;
            if table_long then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else if table_wide then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else if table_special then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 command ('(F4) Screen XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end
            else
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); {macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);}
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); {macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);}
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); {macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt);}
                 command ('(F3) Screen YZ','','','','Choice YZ-screen',@proc_screen_yz); {macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);}
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); {macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt);}
            end;
       _endbox;
      _label ('<i>Note: Operations works only on selected screens!</i>');
      _label ('<i>(With exception of center and scale)</i>');
      _separator;
      _hbox;
            command ('_Center objects','transform.center.objects','','','Center all single objects',@proc_transform_center_objects);
            _label ('Step to center:');
            _hbox;
            _shrink;
                    transform_step_center := _smalledit('100'); _label ('%');
            _endbox;
      _endbox;
      _separator;
      _hbox;
            command ('Scale objects','transform.scale.objects','','','Scale all single objects',@proc_scale_objects);
            _label ('Step:'); transform_scale2 := _edit('<1, 1, 1, 1>');
            command ('InvScale objects','transform.invscale.objects','','','Inverse scale all single objects',@proc_invscale_objects);
      _endbox;
      _separator;
      _hbox;
            command (@xpm_redo,'transform.rotate.objects.right','','','Rotate right all single objects',@proc_rotate_objects_right); { for compatibility }
            _label ('Rotation:'); transform_rotate := _tooltip(_smalledit('45'),'For degree or radian see Data≻File');
            command (@xpm_undo,'transform.rotate.objects.left','','','Rotate left all single objects',@proc_rotate_objects_left); { for compatibility }
            { Special replace upper commands }  macro_self.putprocedure ('transform.rotate.objects','','','',@proc_rotate_objects);
      _endbox;
      _separator;
      _label ('<i>Note: All operations work on single objects!</i>');
_endbox;
_endpage;

_page ('Axes ');
_vbox;
_expand;
      _hbox;
            command ('Clear x','transform.clear.x','','','Clear x-axis to 0',@proc_transform_clear_x);
            command ('Clear y','transform.clear.y','','','Clear y-axis to 0',@proc_transform_clear_y);
            command ('Clear z','transform.clear.z','','','Clear z-axis to 0',@proc_transform_clear_z);
            command ('Clear t','transform.clear.t','','','Clear t-axis to 0',@proc_transform_clear_t);
      _endbox;
      _separator;
      _hbox;
            command ('Mirror x','transform.mirror.x','','','Mirror layer on x-axis',@proc_transform_mirror_x);
            command ('Mirror y','transform.mirror.y','','','Mirror layer on y-axis',@proc_transform_mirror_y);
            command ('Mirror z','transform.mirror.z','','','Mirror layer on z-axis',@proc_transform_mirror_z);
            command ('Mirror t','transform.mirror.t','','','Mirror layer on t-axis',@proc_transform_mirror_t);
      _endbox;
      _separator;
      _hbox;
            command ('Abs x','transform.abs.x','','','Absolute values on x-axis',@proc_transform_abs_x);
            command ('Abs y','transform.abs.y','','','Absolute values on y-axis',@proc_transform_abs_y);
            command ('Abs z','transform.abs.z','','','Absolute values on z-axis',@proc_transform_abs_z);
            command ('Abs t','transform.abs.t','','','Absolute values on t-axis',@proc_transform_abs_t);
      _endbox;
      _separator;
      _hbox;
            command ('Swap x-y','transform.swap.xy','','','Swap x with y',@proc_transform_swap_xy); macro_self.putprocedure ('transform.swap.yx','','','Swap y with x',@proc_transform_swap_xy);
            command ('Swap x-z','transform.swap.xz','','','Swap x with z',@proc_transform_swap_xz); macro_self.putprocedure ('transform.swap.zx','','','Swap z with x',@proc_transform_swap_xz);
            command ('Swap y-z','transform.swap.yz','','','Swap y with z',@proc_transform_swap_yz); macro_self.putprocedure ('transform.swap.zy','','','Swap z with y',@proc_transform_swap_yz);
      _endbox;
      _hbox;
            command ('Swap x-t','transform.swap.xt','','','Swap x with t',@proc_transform_swap_xt); macro_self.putprocedure ('transform.swap.tx','','','Swap t with x',@proc_transform_swap_xt);
            command ('Swap y-t','transform.swap.yt','','','Swap y with t',@proc_transform_swap_yt); macro_self.putprocedure ('transform.swap.ty','','','Swap t with y',@proc_transform_swap_yt);
            command ('Swap z-t','transform.swap.zt','','','Swap z with t',@proc_transform_swap_zt); macro_self.putprocedure ('transform.swap.tz','','','Swap t with z',@proc_transform_swap_zt);
      _endbox;
      _separator;
      _hbox;
            command ('Rotate left','transform.rol','','','Rotate left (x,y,z,t) -> (y,z,t,x)',@proc_transform_rol);
            command ('Flip','transform.flip','','','Flip (x,y,z,t) -> (t,z,y,x)',@proc_transform_flip);
            command ('Rotate right','transform.ror','','','Rotate right (x,y,z,t) -> (t,x,y,z)',@proc_transform_ror);
      _endbox;
      _separator;
      _label ('<i>Note: For boolean operations see bool|layer!</i>');
_endbox;
_endpage;

_page ('A≻ ');
_vbox;
_expand;
      _hbox;
            command ('1/x','transform.inv.x','','','Inverse from values on x-axis',@proc_transform_inv_x);
            command ('1/y','transform.inv.y','','','Inverse from values on y-axis',@proc_transform_inv_y);
            command ('1/z','transform.inv.z','','','Inverse from values on z-axis',@proc_transform_inv_z);
            command ('1/t','transform.inv.t','','','Inverse from values on t-axis',@proc_transform_inv_t);
      _endbox;
      _separator;
      _hbox;
            command ('Ln x','transform.ln.x','','','Natural logarithm from values on x-axis',@proc_transform_ln_x);
            command ('Ln y','transform.ln.y','','','Natural logarithm from values on y-axis',@proc_transform_ln_y);
            command ('Ln z','transform.ln.z','','','Natural logarithm from values on z-axis',@proc_transform_ln_z);
            command ('Ln t','transform.ln.t','','','Natural logarithm from values on t-axis',@proc_transform_ln_t);
      _endbox;
      _hbox;
            command ('Log x','transform.log.x','','','Logarithm from values on x-axis',@proc_transform_log_x);
            command ('Log y','transform.log.y','','','Logarithm from values on y-axis',@proc_transform_log_y);
            command ('Log z','transform.log.z','','','Logarithm from values on z-axis',@proc_transform_log_z);
            command ('Log t','transform.log.t','','','Logarithm from values on t-axis',@proc_transform_log_t);
      _endbox;
      _hbox;
            _label (' ');
            _label ('Base:');
            transform_log_exp_base := _tooltip (_edit('10'),'Base for log and exp');
            _label (' ');
      _endbox;
      _hbox;
            command ('Exp x','transform.exp.x','','','Exponentiation from values on x-axis',@proc_transform_exp_x);
            command ('Exp y','transform.exp.y','','','Exponentiation from values on y-axis',@proc_transform_exp_y);
            command ('Exp z','transform.exp.z','','','Exponentiation from values on z-axis',@proc_transform_exp_z);
            command ('Exp t','transform.exp.t','','','Exponentiation from values on t-axis',@proc_transform_exp_t);
      _endbox;
      _hbox;
            command ('Exp e x','transform.e.x','','','Exponentiation of e from values on x-axis',@proc_transform_e_x);
            command ('Exp e y','transform.e.y','','','Exponentiation of e from values on y-axis',@proc_transform_e_y);
            command ('Exp e z','transform.e.z','','','Exponentiation of e from values on z-axis',@proc_transform_e_z);
            command ('Exp e t','transform.e.t','','','Exponentiation of e from values on t-axis',@proc_transform_e_t);
      _endbox;
_endbox;
_endpage;

_page ('Align ');
_vbox;
_expand;
      _hbox;
            command ('Center','','','','Center layer',@proc_transform_center); { see transform_center }
            command ('Center x','transform.center.x','','','Center on x-axis',@proc_transform_center_x);
            command ('Center y','transform.center.y','','','Center on y-axis',@proc_transform_center_y);
            command ('Center z','transform.center.z','','','Center on z-axis',@proc_transform_center_z);
            command ('Center t','transform.center.t','','','Center on t-axis',@proc_transform_center_t);
      _endbox;
      _separator;
      _hbox;
            command ('Align +','transform.align.+','','','Align layer to positve field',@proc_transform_align_p);
            command ('Align x','transform.align.x','','','Align on x-axis',@proc_transform_align_px);
            command ('Align y','transform.align.y','','','Align on y-axis',@proc_transform_align_py);
            command ('Align z','transform.align.z','','','Align on z-axis',@proc_transform_align_pz);
            command ('Align t','transform.align.t','','','Align on t-axis',@proc_transform_align_pt);
      _endbox;
      _separator;
      _hbox;
            command ('Align -','transform.align.-','','','Align layer to negative field',@proc_transform_align_n);
            command ('Align -x','transform.align.-x','','','Align on -x-axis',@proc_transform_align_nx);
            command ('Align -y','transform.align.-y','','','Align on -y-axis',@proc_transform_align_ny);
            command ('Align -z','transform.align.-z','','','Align on -z-axis',@proc_transform_align_nz);
            command ('Align -t','transform.align.-t','','','Align on -t-axis',@proc_transform_align_nt);
      _endbox;
      _separator;
      _hbox;
            _label (' ');
            command ('Align begin','transform.align.begin','','','Align begin of line',@proc_transform_align_begin);
            command ('Align end','transform.align.end','','','Align end of line',@proc_transform_align_end);
            _label (' ');
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _label ('Min:'); transform_norm_min := _smalledit('1');
                  _label ('Max:'); transform_norm_max := _smalledit('100');
            _endbox;
            _hbox;
                  command ('Set min x','transform.min.x','','','Set x-axis values to min',@proc_transform_min_x);
                  command ('Set min y','transform.min.y','','','Set y-axis values to min',@proc_transform_min_y);
                  command ('Set min z','transform.min.z','','','Set z-axis values to min',@proc_transform_min_z);
                  command ('Set min t','transform.min.t','','','Set t-axis values to min',@proc_transform_min_t);
            _endbox;
            _hbox;
                  command ('Norm x','transform.norm.x','','','Norm x-axis',@proc_transform_norm_x);
                  command ('Norm y','transform.norm.y','','','Norm y-axis',@proc_transform_norm_y);
                  command ('Norm z','transform.norm.z','','','Norm z-axis',@proc_transform_norm_z);
                  command ('Norm t','transform.norm.t','','','Norm t-axis',@proc_transform_norm_t);
            _endbox;
            _hbox;
                  command ('Set max x','transform.max.x','','','Set x-axis values to max',@proc_transform_max_x);
                  command ('Set max y','transform.max.y','','','Set y-axis values to max',@proc_transform_max_y);
                  command ('Set max z','transform.max.z','','','Set z-axis values to max',@proc_transform_max_z);
                  command ('Set max t','transform.max.t','','','Set t-axis values to max',@proc_transform_max_t);
            _endbox;
      _endbox;
_endbox;
_endpage;

_page ('Effects ');
_vbox;
_expand;
      _hbox;
            _label (' ');
            _label ('Center:'); transform_effects_center := _edit('<0, 0, 0, 0>');
            _label (' ');
      _endbox;
      _hbox;
            _label ('Direction:'); transform_effects_direction := _edit('<1, 1, 1, 1>');
            _label ('Fallout angle:'); transform_effects_fallout_angle := _tooltip(_smalledit('10'),'For degree or radian see Data≻File');
      _endbox;
      _hbox;
            _label ('  c:'); transform_c := _smalledit('0');
            _label ('  x:'); transform_x := _smalledit('2');
      _endbox;
      _hbox;
            _label ('x^2:'); transform_x2 := _smalledit('0');
            _label ('x^3:'); transform_x3 := _smalledit('0');
      _endbox;
      _hbox;
            _label (' ');
            command ('Shear','transform.shear','','','Shear elements in direction',@proc_transform_shear);
            command ('Explode','transform.explode','','','Explode elements in direction with fallout angle',@proc_transform_explode);
            _label (' ');
      _endbox;
_endbox;
_endpage;
