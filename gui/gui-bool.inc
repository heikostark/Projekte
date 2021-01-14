{ *********************************** Bool **********************************  }

_page ('Info ');
_eventbox;
_backcolor ($FFFF,$FFFF,$BFFF);
      _vbox;
            _label ('<b>Bold</b> - Single selection - LMB');
            _label ('<span foreground="#FF8000">Color</span> - Multiple selection - RMB');
            _separator;
            _label ('<b>Source</b>');
            _label ('All operations work on a single selected source.');
            _label;
            _label ('<b>Destination</b>');
            _label ('Only copy and move have a single selected destination.');
            _label ('Only mask use destination as mask.');
            _label ('Always appended!');
            _separator;
            _label ('<i>Note: Only multiple selection of destinations have a focus.</i>');
            _label ('<i>Control + Click on screen (xy, xz, yz) to change the active screen.</i>');
            _label ('<i>Control + Shift + Click on screen to work (move, copy) and run active macro.</i>');
      _endbox;
_endbox;
_endpage;

_page ('Points ');
_vbox;
_expand;
      _hbox;
            if table_long then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.tx','','','',@proc_screen_xt);
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.tz','','','',@proc_screen_zt);
            end
            else if table_wide then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);
                 hidecommand ('(F2) XZ','','','','Choice XZ-screen',@proc_screen_xz); macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.tx','','','',@proc_screen_xt);
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);
                 command ('(F5) Screen ZT','','','','Choice ZT-screen',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.tz','','','',@proc_screen_zt);
            end
            else if table_special then
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);
                 command ('(F4) Screen XT','','','','Choice XT-screen',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.tx','','','',@proc_screen_xt);
                 hidecommand ('(F3) YZ','','','','Choice YZ-screen',@proc_screen_yz); macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.tz','','','',@proc_screen_zt);
            end
            else
            begin
                 command ('(F1) Screen XY','','','','Choice XY-screen',@proc_screen_xy); macro_self.putprocedure ('screen.xy','','','',@proc_screen_xy); macro_self.putprocedure ('screen.yx','','','',@proc_screen_xy);
                 command ('(F2) Screen XZ','','','','Choice XZ-screen',@proc_screen_xz); macro_self.putprocedure ('screen.xz','','','',@proc_screen_xz); macro_self.putprocedure ('screen.zx','','','',@proc_screen_xz);
                 hidecommand ('(F4) XT','','','','Choice XT-screen',@proc_screen_xt); macro_self.putprocedure ('screen.xt','','','',@proc_screen_xt); macro_self.putprocedure ('screen.tx','','','',@proc_screen_xt);
                 command ('(F3) Screen YZ','','','','Choice YZ-screen',@proc_screen_yz); macro_self.putprocedure ('screen.yz','','','',@proc_screen_yz); macro_self.putprocedure ('screen.zy','','','',@proc_screen_yz);
                 hidecommand ('(F5) ZT','','','','Choice ZT-screen',@proc_screen_zt); macro_self.putprocedure ('screen.zt','','','',@proc_screen_zt); macro_self.putprocedure ('screen.tz','','','',@proc_screen_zt);
            end;
      _endbox;
      _label ('<i>Note: Mouse button operations works only on selected screens!</i>');
      _separator;
      _hbox;
            _button (@xpm_left,@m3pl,@macro_self);
            _button (@xpm_leftleft,@m3pll,@macro_self);
            _button (@xpm_leftstop,@m3pls,@macro_self);
            _eventbox;
                      _cursor_pressed (@proc_point_values,@macro_self);
                      label_status_point2 := _label;
                      _tooltip (label_status_point2,'Edit point values');
                      { macro_self.putprocedure ('edit.point.values','','','',@proc_point_values); } { see edit }
            _endbox;
            _button (@xpm_rightstop,@m3prs,@macro_self);
            _button (@xpm_rightright,@m3prr,@macro_self);
            _button (@xpm_right,@m3pr,@macro_self);
      _endbox;
      _hbox;
            l_bool_subobject_left_p := _label;
            _vbox;
                  _label ('Area');
                  _label ('Point');
            _endbox;
            _label ('–≻');
            _vbox;
                  _label ('LMB'); macro_self.putprocedure ('bool.erase.cursor.point','','','',@proc_cursor_erase_point);
                  command ('Erase','bool.erase.point','','','Erase point',@proc_erase_point);
                  macro_self.putprocedure ('bool.erase.point.list','','','',@proc_erase_point_list);
            _endbox;
            _vbox;
                  _label ('   ');
                  command ('Mask','bool.mask.points','','','Mask points',@proc_mask_points);
            _endbox;
            _label ('|');
            _vbox;
                  _label ('MMB'); macro_self.putprocedure ('bool.move.cursor.point','','','',@proc_cursor_move_point);
                  command ('Move','bool.move.point','','','Move point',@proc_move_point);
            _endbox;
            _vbox;
                  _label ('RMB'); macro_self.putprocedure ('bool.copy.cursor.point','','','',@proc_cursor_copy_point);
                  command ('Copy','bool.copy.point','','','Copy point',@proc_copy_point);
            _endbox;
            _label('–≻');
            l_bool_subobject_right_p := _label;
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _vbox;
                        command ('Set','bool.points.set.minmax','','','Set min and max dimension',@proc_bool_points_set_dimension_minmax);
                  _endbox;
                  _vbox;
                        command ('Set min','bool.points.set.min','','','Set min dimension',@proc_bool_points_set_dimension_min);
                        command ('Set max','bool.points.set.max','','','Set max dimension',@proc_bool_points_set_dimension_max);
                  _endbox;
                  _vbox;
                        _label ('Dimension (min):');
                        _label ('Dimension (max):');
                  _endbox;
                  _vbox;
                        bool_points_dimension_min := _edit ('<-10, -10, -10, -10>');
                        bool_points_dimension_max := _edit ('<10, 10, 10, 10>');
                  _endbox;
            _endbox;
            _hbox;
                  command ('Erase','bool.erase.minmax.points','','','Erase [min..max] points',@proc_erase_minmax_points);
                  command ('Move','bool.move.minmax.points','','','Move [min..max] points',@proc_move_minmax_points);
                  command ('Copy','bool.copy.minmax.points','','','Copy [min..max] points',@proc_copy_minmax_points);
            _endbox;
      _endbox;
_endbox;
_endpage;

_page ('Segments ');
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
      _label ('<i>Note: Mouse button operations works only on selected screens!</i>');
      _separator;
      _hbox;
            l_bool_subobject_left_s := _label;
            _vbox;
                  _label ('Area');
            _endbox;
            _label ('–≻');
            _vbox;
                  _label ('LMB'); macro_self.putprocedure ('bool.erase.cursor.segment','','','',@proc_cursor_erase_segment);
                  _label ('Erase');
            _endbox;
            _label ('|');
            _vbox;
                  _label ('MMB'); macro_self.putprocedure ('bool.move.cursor.segment','','','',@proc_cursor_move_segment);
                  _label ('Move');
            _endbox;
            _vbox;
                  _label ('RMB'); macro_self.putprocedure ('bool.copy.cursor.segment','','','',@proc_cursor_copy_segment);
                  _label ('Copy');
            _endbox;
            _label('–≻');
            l_bool_subobject_right_s := _label;
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _vbox;
                        command ('Set','bool.segments.set.minmax','','','Set min and max dimension',@proc_bool_segments_set_dimension_minmax);
                  _endbox;
                  _vbox;
                        command ('Set min','bool.segments.set.min','','','Set min dimension',@proc_bool_segments_set_dimension_min);
                        command ('Set max','bool.segments.set.max','','','Set max dimension',@proc_bool_segments_set_dimension_max);
                  _endbox;
                  _vbox;
                        _label ('Dimension (min):');
                        _label ('Dimension (max):');
                  _endbox;
                  _vbox;
                        bool_segments_dimension_min := _edit ('<-10, -10, -10, -10>');
                        bool_segments_dimension_max := _edit ('<10, 10, 10, 10>');
                  _endbox;
            _endbox;
            _hbox;
                  command ('Erase','bool.erase.minmax.segments','','','Erase [min..max] segments',@proc_erase_minmax_segments);
                  command ('Move','bool.move.minmax.segments','','','Move [min..max] segments',@proc_move_minmax_segments);
                  command ('Copy','bool.copy.minmax.segments','','','Copy [min..max] segments',@proc_copy_minmax_segments);
            _endbox;
      _endbox;
      _separator;
      _label ('<b>A segment is a part of a line (with two points).</b>');
      _label ('<i>For vectors (two points line) see lines.</i>');
_endbox;
_endpage;

_page ('Lines ');
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
      _label ('<i>Note: Mouse button operations works only on selected screens!</i>');
      _separator;
      _hbox;
            _button (@xpm_left,@m3ll,@macro_self);
            _button (@xpm_leftleft,@m3lll,@macro_self);
            _button (@xpm_leftstop,@m3lls,@macro_self);
            _eventbox;
                      _cursor_pressed (@proc_line_material,@macro_self);
                      label_status_line2 := _label;
                      _tooltip (label_status_line2,'Edit line material');
                      { macro_self.putprocedure ('edit.line.material','','','',@proc_line_material); } { see edit }
            _endbox;
            _button (@xpm_rightstop,@m3lrs,@macro_self);
            _button (@xpm_rightright,@m3lrr,@macro_self);
            _button (@xpm_right,@m3lr,@macro_self);
      _endbox;
      _hbox;
            l_bool_subobject_left_l := _label;
            _vbox;
                  _label ('Area');
                  _label ('Line');
            _endbox;
            _label ('–≻');
            _vbox;
                  _label ('LMB'); macro_self.putprocedure ('bool.erase.cursor.line','','','',@proc_cursor_erase_line);
                  command ('Erase','bool.erase.line','','','Erase line',@proc_erase_line);
                  macro_self.putprocedure ('bool.erase.line.list','','','',@proc_erase_line_list);
                  macro_self.putprocedure ('bool.erase.material.list','','','',@proc_erase_material_list);
            _endbox;
            _vbox;
                  _label ('   ');
                  command ('Mask','bool.mask.lines','','','Mask lines by line materials',@proc_mask_lines);
            _endbox;
            _label ('|');
            _vbox;
                  _label ('MMB'); macro_self.putprocedure ('bool.move.cursor.line','','','',@proc_cursor_move_line);
                  command ('Move','bool.move.line','','','Move line',@proc_move_line);
            _endbox;
            _vbox;
                  _label ('RMB'); macro_self.putprocedure ('bool.copy.cursor.line','','','',@proc_cursor_copy_line);
                  command ('Copy','bool.copy.line','','','Copy line',@proc_copy_line);
            _endbox;
            _label('–≻');
            l_bool_subobject_right_l := _label;
      _endbox;
      _separator;
      _vbox;
            _hbox;
                  _vbox;
                        command ('Set','bool.lines.set.minmax','','','Set min and max dimension',@proc_bool_lines_set_dimension_minmax);
                  _endbox;
                  _vbox;
                        command ('Set min','bool.lines.set.min','','','Set min dimension',@proc_bool_lines_set_dimension_min);
                        command ('Set max','bool.lines.set.max','','','Set max dimension',@proc_bool_lines_set_dimension_max);
                  _endbox;
                  _vbox;
                        _label ('Dimension (min):');
                        _label ('Dimension (max):');
                  _endbox;
                  _vbox;
                        bool_lines_dimension_min := _edit ('<-10, -10, -10, -10>');
                        bool_lines_dimension_max := _edit ('<10, 10, 10, 10>');
                  _endbox;
            _endbox;
            _hbox;
                  command ('Erase','bool.erase.minmax.lines','','','Erase [min..max] lines',@proc_erase_minmax_lines);
                  command ('Move','bool.move.minmax.lines','','','Move [min..max] lines',@proc_move_minmax_lines);
                  command ('Copy','bool.copy.minmax.lines','','','Copy [min..max] lines',@proc_copy_minmax_lines);
            _endbox;
      _endbox;
      _separator;
      _hbox;
            _label ('Range:');
            bool_line_materials_left := _tooltip(_smalledit ('0'),'Min range value');
            bool_line_materials_right := _tooltip(_smalledit ('0'),'Min range value');
      _endbox;
      _hbox;
            l_bool_subobject2_left_l := _label;
            _vbox;
                  _label ('lengths');
                  _label ('materials');
            _endbox;
            _label ('–≻');
            _vbox;
                  command ('Erase','bool.erase.line.length','','','Erase lengths',@proc_erase_line_lengths);
                  command ('Erase','bool.erase.line.materials','','','Erase materials',@proc_erase_line_materials);
            _endbox;
            _label ('|');
            _vbox;
                  command ('Move','bool.move.line.lengths','','','Move lengths',@proc_move_line_lengths);
                  command ('Move','bool.move.line.materials','','','Move materials',@proc_move_line_materials);
            _endbox;
            _vbox;
                  command ('Copy','bool.copy.line.lengths','','','Copy lengths',@proc_copy_line_lengths);
                  command ('Copy','bool.copy.line.materials','','','Copy materials',@proc_copy_line_materials);
            _endbox;
            _label('–≻');
            l_bool_subobject2_right_l := _label;
      _endbox;
_endbox;
_endpage;

_page ('Mesh ');
_vbox;
_expand;
      _hbox;
            l_bool_subobject_left_mesh := _label;
            _vbox;
                  _label ('Mesh');
            _endbox;
            _label ('–≻');
            _vbox;
                  command ('Erase','bool.erase.mesh','','','Erase mesh with reference from destination',@proc_erase_mesh);
                  command ('Erase duplicates','bool.erase.duplicates','','','Erase duplicate mesh with reference from destination',@proc_erase_duplicates_between);
            _endbox;
            _label ('|');
            _vbox;
                  command ('Make outside','bool.make.outside.mesh','','','Make mesh to own object with reference from destination (outside sphere of element)',@proc_make_mesh);
                  command ('Make inside','bool.make.inside.mesh','','','Make mesh to own object with reference from destination (only inner sphere of element)',@proc_make2_mesh);
            _endbox;
            _label('-o');
            l_bool_subobject_right_mesh := _label;
      _endbox;
      _separator;
      _hbox;
            _label;
            command ('Split','bool.split.mesh','','','Split meshs in single objects',@proc_split_mesh);
            command ('Combine','','','','Combine meshs to a single object',@proc_objects_to_one_object); { from edit object }
            _label;
      _endbox;
      _separator;
      _label ('<b>A mesh is a special line,</b>');
      _label ('<b>which has connected ends.</b>');
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
      _textcolor (255,0,0);
      _label ('<i>Note: Mouse button operations works only on selected screens!</i>');
      _separator;
      _hbox;
            _button (@xpm_left,@m3ol,@macro_self);
            _button (@xpm_leftleft,@m3oll,@macro_self);
            _button (@xpm_leftstop,@m3ols,@macro_self);
            _eventbox;
                      _cursor_pressed (@proc_object_name,@macro_self);
                      label_status_object2 := _label;
                      _tooltip (label_status_object2,'Edit object name');
                      { macro_self.putprocedure ('edit.object.name','','','',@proc_object_name); } { see edit }
            _endbox;
            _button (@xpm_rightstop,@m3ors,@macro_self);
            _button (@xpm_rightright,@m3orr,@macro_self);
            _button (@xpm_right,@m3or,@macro_self);
      _endbox;
      _hbox;
            l_bool_subobject_left_o := _label;
            _vbox;
                  _label ('Area');
                  _label ('Object');
            _endbox;
            _label ('–≻');
            _vbox;
                  _label ('LMB'); macro_self.putprocedure ('bool.erase.cursor.object','','','',@proc_cursor_erase_object);
                  command ('Erase','bool.erase.object','','','Erase object',@proc_erase_object);
                  macro_self.putprocedure ('bool.erase.object.list','','','',@proc_erase_object_list);
                  macro_self.putprocedure ('bool.erase.name.list','','','',@proc_erase_name_list);
            _endbox;
            _vbox;
                  _label ('   ');
                  command ('Mask','bool.mask.objects','','','Mask objects by object names',@proc_mask_objects);
            _endbox;
            _label ('|');
            _vbox;
                  _label ('MMB'); macro_self.putprocedure ('bool.move.cursor.object','','','',@proc_cursor_move_object);
                  command ('Move','bool.move.object','','','Move object',@proc_move_object);
            _endbox;
            _vbox;
                  _label ('RMB'); macro_self.putprocedure ('bool.copy.cursor.object','','','',@proc_cursor_copy_object);
                  command ('Copy','bool.copy.object','','','Copy object',@proc_copy_object);
            _endbox;
            _label('–≻');
            l_bool_subobject_right_o := _label;
      _endbox;
      _separator;
      _hbox;
            _label;
            _label ('Pattern:');
            bool_object_named := _tooltip(_fulledit (''),'Pattern of object names (o1 o2)');
            _label;
      _endbox;
      _hbox;
            l_bool_subobject2_left_o := _label;
            _vbox;
                  _label ('objects');
            _endbox;
            _label ('–≻');
            _vbox;
                  command ('Erase','bool.erase.object.named','','','Erase objects',@proc_erase_object_named);
            _endbox;
            _label ('|');
            _vbox;
                  command ('Move','bool.move.object.named','','','Move objects',@proc_move_object_named);
            _endbox;
            _vbox;
                  command ('Copy','bool.copy.object.named','','','Copy objects',@proc_copy_object_named);
            _endbox;
            _label('–≻');
            l_bool_subobject2_right_o := _label;
      _endbox;
_endbox;
_endpage;

_page ('Layer ');
_vbox;
_expand;
      _hbox;
            l_bool_object_left := _label;
            _label ('Layer');
            _vbox;
                  _hbox;
                        _label ('–≻');
                  _endbox;
                  _hbox;
                        _label ('≺–');
                  _endbox;
            _endbox;
            _vbox;
                  _hbox;
                        command ('Erase','bool.erase.layer','','','Erase points, vectors or lines',@proc_erase_layer);
                        _label ('|');
                        command ('Move','bool.move.layer','','','Move points, vectors or lines',@proc_move_layer);
                        command ('Copy','bool.copy.layer','','','Copy points, vectors or lines',@proc_copy_layer);
                  _endbox;
                  _hbox;
                        command ('Swap','bool.swap.layer','','','Swap points, vectors or lines',@proc_swap_layer);
                  _endbox;
            _endbox;
            _label('–≻');
            l_bool_object_right := _label;
      _endbox;
      _separator;
      _hbox;
            edit_axis1 := _combobox;
                _item ('x-axis');
                _item ('y-axis');
                _item ('z-axis');
                _item ('t-axis');
            _endcombobox (0);
            _label ('–≻');
            command ('Clear','','','','Clear left axis and right axis',@proc_clear_axes);
            _label ('|');
            command ('Move','','','','Move left axis to right axis and clear left axis',@proc_move_axes);
            command ('Copy','','','','Copy left axis to right axis',@proc_copy_axes);
            command ('Swap','','','','Swap left axis with right axis',@proc_swap_axes);
            _label ('–≻');
            edit_axis2 := _combobox;
                _item ('x-axis');
                _item ('y-axis');
                _item ('z-axis');
                _item ('t-axis');
            _endcombobox (3);
      _endbox;
_endbox;
_endpage;

