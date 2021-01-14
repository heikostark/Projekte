{ *********************************** Mouse ********************************** }
{ *********************************** Moved ********************************** }

function screen_xy_moved (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var x,y : gtk_int;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          x := round(TGDK_EventMotion(event^).x);
          y := round(TGDK_EventMotion(event^).y);
          if (TGDK_EventMotion(event^).is_hint = 1) then gdk_window_get_pointer(TGDKEventMotion(event^).window, @x, @y, nil);
          if screen = 1 then
             if (x <> oldx) or (y <> oldy) then short_drawing (true);
     end;
     screen_xy_moved := gtk_true;
end;

function screen_xz_moved (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var x,y : gtk_int;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          x := round(TGDK_EventMotion(event^).x);
          y := round(TGDK_EventMotion(event^).y);
          if (TGDK_EventMotion(event^).is_hint = 1) then gdk_window_get_pointer(TGDKEventMotion(event^).window, @x, @y, nil);
          if screen = 2 then
             if (x <> oldx) or (y <> oldy) then short_drawing (true);
     end;
     screen_xz_moved := gtk_true;
end;

function screen_xt_moved (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var x,y : gtk_int;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          x := round(TGDK_EventMotion(event^).x);
          y := round(TGDK_EventMotion(event^).y);
          if (TGDK_EventMotion(event^).is_hint = 1) then gdk_window_get_pointer(TGDKEventMotion(event^).window, @x, @y, nil);
          if screen = 4 then
             if (x <> oldx) or (y <> oldy) then short_drawing (true);
     end;
     screen_xt_moved := gtk_true;
end;

function screen_yz_moved (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var x,y : gtk_int;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          x := round(TGDK_EventMotion(event^).x);
          y := round(TGDK_EventMotion(event^).y);
          if (TGDK_EventMotion(event^).is_hint = 1) then gdk_window_get_pointer(TGDKEventMotion(event^).window, @x, @y, nil);
          if screen = 3 then
             if (x <> oldx) or (y <> oldy) then short_drawing (true);
     end;
     screen_yz_moved := gtk_true;
end;

function screen_zt_moved (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var x,y : gtk_int;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          x := round(TGDK_EventMotion(event^).x);
          y := round(TGDK_EventMotion(event^).y);
          if (TGDK_EventMotion(event^).is_hint = 1) then gdk_window_get_pointer(TGDKEventMotion(event^).window, @x, @y, nil);
          if screen = 5 then
             if (x <> oldx) or (y <> oldy) then short_drawing (true);
     end;
     screen_zt_moved := gtk_true;
end;

{ ************************************ Mouse ********************************* }
{ *********************************** Scrolled ******************************* }

function screen_xy_scrolled (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var intern_bool_radius : real;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          if TGdk_EventScroll(event^).direction = GDK_SCROLL_Up then
           begin
                if screen = 1 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)+5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end
           else if TGdk_EventScroll(event^).direction = GDK_SCROLL_down then
           begin
                if screen = 1 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)-5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end;
      end;
     screen_xy_scrolled := gtk_true;
end;


function screen_xz_scrolled (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var intern_bool_radius : real;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          if TGdk_EventScroll(event^).direction = GDK_SCROLL_Up then
           begin
                if screen = 2 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)+5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end
           else if TGdk_EventScroll(event^).direction = GDK_SCROLL_down then
           begin
                if screen = 2 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)-5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end;
      end;
     screen_xz_scrolled := gtk_true;
end;

function screen_xt_scrolled (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var intern_bool_radius : real;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          if TGdk_EventScroll(event^).direction = GDK_SCROLL_Up then
           begin
                if screen = 4 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)+5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end
           else if TGdk_EventScroll(event^).direction = GDK_SCROLL_down then
           begin
                if screen = 4 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)-5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end;
      end;
     screen_xt_scrolled := gtk_true;
end;

function screen_yz_scrolled (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var intern_bool_radius : real;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          if TGdk_EventScroll(event^).direction = GDK_SCROLL_Up then
           begin
                if screen = 3 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)+5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end
           else if TGdk_EventScroll(event^).direction = GDK_SCROLL_down then
           begin
                if screen = 3 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)-5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end;
      end;
     screen_yz_scrolled := gtk_true;
end;

function screen_zt_scrolled (Widget,event,data : gtk_pointer) : gtk_boolean; cdecl;
var intern_bool_radius : real;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) and not (_getpage(subnote_boolean) = 4) then
     begin
          if TGdk_EventScroll(event^).direction = GDK_SCROLL_Up then
           begin
                if screen = 5 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)+5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end
           else if TGdk_EventScroll(event^).direction = GDK_SCROLL_down then
           begin
                if screen = 5 then
                begin
                     intern_bool_radius := (_getreal(bool_radius)*coord_factor.x)-5;
                     if intern_bool_radius < 5.0 then intern_bool_radius := 5;
                     if intern_bool_radius > 200.0 then intern_bool_radius := 200;
                     _setedit (bool_radius,getstring(intern_bool_radius/coord_factor.x));
                     short_drawing (true);
                end;
           end;
      end;
     screen_zt_scrolled := gtk_true;
end;

{ ************************************ Mouse ********************************* }
{ *********************************** Pressed ******************************** }

var p_image : utf16chars;
    p_size : complexnat;

procedure p_o_image_xy (macro : pointer);
var area : Tgtk_widget;
    screen_shot : trgba;
begin
     area := Default(tgtk_widget);
     screen_shot := Default(trgba);

     _cursor_watch;
     if p_image <> '' then
     begin
          screen_shot.init;
          if p_size = Czeronat then p_size := getcomplexnat (getfilename (p_image));
          limit (p_size,gcn(10,10),gcn(10000,10000));
          area.window := area_xy^.window;
          area.allocation.width := p_size.x;
          area.allocation.height := p_size.y;
          newdraw (@area,xy,screen_shot,0);
          screen_shot.save (p_image);
          screen_shot.done;

          tmacro(macro^).writeredo ('screenshot.xy','"'+p_image+'"'+' '+getstring(p_size));
     end;
     _cursor_arrow;
end;

procedure proc_image_xy_1 (macro : gtk_pointer); cdecl;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
          p_image := tmacro(macro^).getparameter(1);
          p_size := getcomplexnat(tmacro(macro^).getparameter(2));
          p_o_image_xy (macro);
     end;
end;

procedure proc_image_xy_b (p1,macro : gtk_pointer); cdecl;
begin
     p_size.x := _getnat (t_snapshot_xsize);
     p_size.y := _getnat (t_snapshot_ysize);
{$ifdef MSWINDOWS}
          p_image := 'image-xy.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xy,macro);
{$else}
          p_image := 'image-xy.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xy,macro);
{$endif}
end;

procedure proc_image_xy (macro : gtk_pointer); cdecl;
begin
     p_size := Czeronat;
{$ifdef MSWINDOWS}
          p_image := '1000x1000_image-xy.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xy,macro);
{$else}
          p_image := '1000x1000_image-xy.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xy,macro);
{$endif}
end;

function screen_xy_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (_getpage(note) = boolnote) then
     begin
          if screen = 1 then
          begin
               case (TGdk_EventButton(event^).state and $F) of { only first four bits }
                    (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
                    begin
                         if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
                    else
                    begin
                         if TGdk_EventButton(event^).button = 1 then
                         begin
                              case _getpage(subnote_boolean) of
                                   1 : edit_cursor_erase_p (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                                   2 : edit_cursor_erase_s (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                                   3 : edit_cursor_erase_l (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                                   4 : { mesh };
                                   5 : edit_cursor_erase_o (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                                   6 : {layer};
                              end;
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xy,xy,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               end;
          end
          else
          begin
               screen := 1;
               calculating;
               updating;
               short_drawing (false);
          end;
     end
     else if (TGdk_EventButton(event^).state and $F) <> 0 then proc_image_xy (macro);
     screen_xy_pressed := gtk_true;
end;

{ ***** }

procedure p_o_image_xz (macro : pointer);
var area : tgtk_widget;
    screen_shot : trgba;
begin
     area := Default(tgtk_widget);
     screen_shot := Default(trgba);

     _cursor_watch;
     if p_image <> '' then
     begin
          screen_shot.init;
          if p_size = Czeronat then p_size := getcomplexnat (getfilename (p_image));
          limit (p_size,gcn(10,10),gcn(10000,10000));
          area.window := area_xz^.window;
          area.allocation.width := p_size.x;
          area.allocation.height := p_size.y;
          newdraw (@area,xz,screen_shot,0);
          screen_shot.save (p_image);
          screen_shot.done;

          tmacro(macro^).writeredo ('screenshot.xz','"'+p_image+'"'+' '+getstring(p_size));
     end;
     _cursor_arrow;
end;

procedure proc_image_xz_1 (macro : gtk_pointer); cdecl;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
          p_image := tmacro(macro^).getparameter(1);
          p_size := getcomplexnat(tmacro(macro^).getparameter(2));
          p_o_image_xz (macro);
     end;
end;

procedure proc_image_xz_b (p1,macro : gtk_pointer); cdecl;
begin
     p_size.x := _getnat (t_snapshot_xsize);
     p_size.y := _getnat (t_snapshot_ysize);
{$ifdef MSWINDOWS}
          p_image := 'image-xz.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xz,macro);
{$else}
          p_image := 'image-xz.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xz,macro);
{$endif}
end;

procedure proc_image_xz (macro : gtk_pointer); cdecl;
begin
          p_size := Czeronat;
{$ifdef MSWINDOWS}
          p_image := '1000x1000_image-xz.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xz,macro);
{$else}
          p_image := '1000x1000_image-xz.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xz,macro);
{$endif}
end;

function screen_xz_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) then
     begin
          if screen = 2 then
          begin
               case (TGdk_EventButton(event^).state and $F) of { only first four bits }
                    (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
                    begin
                         if TGdk_EventButton(event^).button = 2 then
                         begin
                               if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 4 then { mesh }
                               else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                               run_hidehide_macro (widget,macro);
                               calculating;
                               updating;
                               drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
                    else
                    begin
                         if TGdk_EventButton(event^).button = 1  then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_erase_p (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_erase_s (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_erase_l (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_erase_o (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 2 then
                         begin
                               if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 4 then { mesh }
                               else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                               calculating;
                               updating;
                               drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xz,xz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               end;
          end
          else
          begin
               screen := 2;
               calculating;
               updating;
               short_drawing (false);
          end;
      end
      else if (TGdk_EventButton(event^).state and $F) <> 0 then proc_image_xz (macro);
      screen_xz_pressed := gtk_true;
end;

{ ***** }

procedure p_o_image_xt (macro : pointer);
var area : tgtk_widget;
    screen_shot : trgba;
begin
     area := Default(tgtk_widget);
     screen_shot := Default(trgba);

     _cursor_watch;
     if p_image <> '' then
     begin
          screen_shot.init;
          if p_size = Czeronat then p_size := getcomplexnat (getfilename (p_image));
          limit (p_size,gcn(10,10),gcn(10000,10000));
          area.window := area_xt^.window;
          area.allocation.width := p_size.x;
          area.allocation.height := p_size.y;
          newdraw (@area,xt,screen_shot,0);
          screen_shot.save (p_image);
          screen_shot.done;

          tmacro(macro^).writeredo ('screenshot.xt','"'+p_image+'"'+' '+getstring(p_size));
     end;
     _cursor_arrow;
end;

procedure proc_image_xt_1 (macro : gtk_pointer); cdecl;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
          p_image := tmacro(macro^).getparameter(1);
          p_size := getcomplexnat(tmacro(macro^).getparameter(2));
          p_o_image_xt (macro);
     end;
end;

procedure proc_image_xt_b (p1,macro : gtk_pointer); cdecl;
begin
     p_size.x := _getnat (t_snapshot_xsize);
     p_size.y := _getnat (t_snapshot_ysize);
{$ifdef MSWINDOWS}
          p_image := 'image-xt.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xt,macro);
{$else}
          p_image := 'image-xt.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xt,macro);
{$endif}
end;

procedure proc_image_xt (macro : gtk_pointer); cdecl;
begin
          p_size := Czeronat;
{$ifdef MSWINDOWS}
          p_image := '1000x1000_image-xt.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xt,macro);
{$else}
          p_image := '1000x1000_image-xt.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_xt,macro);
{$endif}
end;

function screen_xt_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) then
     begin
          if screen = 4 then
          begin
               case (TGdk_EventButton(event^).state and $F) of { only first four bits }
                    (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
                    begin
                         if TGdk_EventButton(event^).button = 2 then
                         begin
                               if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 4 then { mesh }
                               else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                               run_hidehide_macro (widget,macro);
                               calculating;
                               updating;
                               drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
                    else
                    begin
                         if TGdk_EventButton(event^).button = 1  then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_erase_p (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_erase_s (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_erase_l (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_erase_o (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 2 then
                         begin
                               if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                               else if _getpage(subnote_boolean) = 4 then { mesh }
                               else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                               calculating;
                               updating;
                               drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_xt,xt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               end;
          end
          else
          begin
               screen := 4;
               calculating;
               updating;
               short_drawing (false);
          end;
      end
      else if (TGdk_EventButton(event^).state and $F) <> 0 then proc_image_xt (macro);
      screen_xt_pressed := gtk_true;
end;

{ ***** }

procedure p_o_image_yz (macro : pointer);
var area : tgtk_widget;
    screen_shot : trgba;
begin
     area := Default(tgtk_widget);
     screen_shot := Default(trgba);

     _cursor_watch;
     if p_image <> '' then
     begin
          screen_shot.init;
          if p_size = Czeronat then p_size := getcomplexnat (getfilename (p_image));
          limit (p_size,gcn(10,10),gcn(10000,10000));
          area.window := area_yz^.window;
          area.allocation.width := p_size.x;
          area.allocation.height := p_size.y;
          newdraw (@area,yz,screen_shot,0);
          screen_shot.save (p_image);
          screen_shot.done;

          tmacro(macro^).writeredo ('screenshot.yz','"'+p_image+'"'+' '+getstring(p_size));
     end;
     _cursor_arrow;
end;

procedure proc_image_yz_1 (macro : gtk_pointer); cdecl;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
          p_image := tmacro(macro^).getparameter(1);
          p_size := getcomplexnat(tmacro(macro^).getparameter(2));
          p_o_image_yz (macro);
     end;
end;

procedure proc_image_yz_b (p1,macro : gtk_pointer); cdecl;
begin
     p_size.x := _getnat (t_snapshot_xsize);
     p_size.y := _getnat (t_snapshot_ysize);
{$ifdef MSWINDOWS}
          p_image := 'image-yz.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_yz,macro);
{$else}
          p_image := 'image-yz.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_yz,macro);
{$endif}
end;

procedure proc_image_yz (macro : gtk_pointer); cdecl;
begin
     p_size := Czeronat;
{$ifdef MSWINDOWS}
          p_image := '1000x1000_image-yz.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_yz,macro);
{$else}
          p_image := '1000x1000_image-yz.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_yz,macro);
{$endif}
end;

function screen_yz_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) then
     begin
          if screen = 3 then
          begin
               case (TGdk_EventButton(event^).state and $F) of { only first four bits }
                    (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
                    begin
                         if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
                    else
                    begin
                         if TGdk_EventButton(event^).button = 1 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_erase_p (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_erase_s (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_erase_l (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_erase_o (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_yz,yz,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               end;
          end
          else
          begin
               screen := 3;
               calculating;
               updating;
               short_drawing (false);
          end;
     end
     else if (TGdk_EventButton(event^).state and $F) <> 0 then proc_image_yz (macro);
     screen_yz_pressed := gtk_true;
end;

{ ***** }

procedure p_o_image_zt (macro : pointer);
var area : tgtk_widget;
    screen_shot : trgba;
begin
     area := Default(tgtk_widget);
     screen_shot := Default(trgba);

     _cursor_watch;
     if p_image <> '' then
     begin
          screen_shot.init;
          if p_size = Czeronat then p_size := getcomplexnat (getfilename (p_image));
          limit (p_size,gcn(10,10),gcn(10000,10000));
          area.window := area_zt^.window;
          area.allocation.width := p_size.x;
          area.allocation.height := p_size.y;
          newdraw (@area,zt,screen_shot,0);
          screen_shot.save (p_image);
          screen_shot.done;

          tmacro(macro^).writeredo ('screenshot.zt','"'+p_image+'"'+' '+getstring(p_size));
     end;
     _cursor_arrow;
end;

procedure proc_image_zt_1 (macro : gtk_pointer); cdecl;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
          p_image := tmacro(macro^).getparameter(1);
          p_size := getcomplexnat(tmacro(macro^).getparameter(2));
          p_o_image_zt (macro);
     end;
end;

procedure proc_image_zt_b (p1,macro : gtk_pointer); cdecl;
begin
     p_size.x := _getnat (t_snapshot_xsize);
     p_size.y := _getnat (t_snapshot_ysize);
{$ifdef MSWINDOWS}
          p_image := 'image-zt.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_zt,macro);
{$else}
          p_image := 'image-zt.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_zt,macro);
{$endif}
end;

procedure proc_image_zt (macro : gtk_pointer); cdecl;
begin
     p_size := Czeronat;
{$ifdef MSWINDOWS}
          p_image := '1000x1000_image-zt.bmp';
          _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_zt,macro);
{$else}
          p_image := '1000x1000_image-zt.ppm';
          _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All files:*.*',@p_o_image_zt,macro);
{$endif}
end;

function screen_zt_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     if (_getpage(note) = boolnote) and into (_getpage(subnote_boolean),1,5) then
     begin
          if screen = 5 then
          begin
               case (TGdk_EventButton(event^).state and $F) of { only first four bits }
                    (GDK_SHIFT_MASK or GDK_CONTROL_MASK) : { Shift + Strg }
                    begin
                         if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              run_hidehide_macro (widget,macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
                    else
                    begin
                         if TGdk_EventButton(event^).button = 1 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_erase_p (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_erase_s (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_erase_l (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_erase_o (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 2 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_move_p (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_move_s (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_move_l (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_move_o (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end
                         else if TGdk_EventButton(event^).button = 3 then
                         begin
                              if _getpage(subnote_boolean) = 1 then edit_cursor_copy_p (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 2 then edit_cursor_copy_s (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 3 then edit_cursor_copy_l (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro)
                              else if _getpage(subnote_boolean) = 4 then { mesh }
                              else if _getpage(subnote_boolean) = 5 then edit_cursor_copy_o (area_zt,zt,round(TGdk_EventButton(event^).x),round(TGdk_EventButton(event^).y),macro);
                              calculating;
                              updating;
                              drawing;
                         end;
                    end;
               end;
          end
          else
          begin
               screen := 5;
               calculating;
               updating;
               short_drawing (false);
          end;
     end
     else if (TGdk_EventButton(event^).state and $F) <> 0 then proc_image_zt (macro);
     screen_zt_pressed := gtk_true;
end;

{ ***** }

procedure p_o_image_histo (macro : pointer);
var c : complexnat;
begin
     c := getcomplexnat (getfilename (p_image));
     limit (c,gcn(100,100),gcn(5000,5000));
     {screen_histo.resize (c.x,c.y);
     screen_histo.render;}
     screen_histo.done;
     screen_histo.init (c.x,c.y);
     case stattype of
          1 :
          begin
               if _getcheckbutton (togglegrouped) then
               begin
                    screen_histo.left ('grouped '+statobjects);
                    screen_histo.bottom (statname+' [units]');
                    screen_histo.setstyle (2);
                    if _getnat (geometry_groups) > 1 then
                    screen_histo.grouped (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred,_getnat(geometry_groups));
               end
               else
               begin
                    screen_histo.left (statname+' [units]');
                    screen_histo.bottom ('sorted '+statobjects);
                    screen_histo.setstyle (5);
                    screen_histo.histogram (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
               end;
          end;
          2,3 :
          begin
               screen_histo.left (statname+' [units]');
               screen_histo.bottom (statobjects);
               screen_histo.setstyle (5);
               screen_histo.histogram (cstat[6],cstat[5],cstat[4],cstat[3],cstat[2],cstat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
          end;
     end;
     screen_histo.save (p_image); { render itself }
end;

function screen_histo_pressed (Widget,event,macro : gtk_pointer) : gtk_boolean; cdecl;
begin
     {$ifdef MSWINDOWS}
               p_image := getstring(screen_histo.sizex)+'x'+getstring(screen_histo.sizey)+'graph.bmp';
               _savefile (p_image,'new-file','bmp','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All vectorimages:*.svg|All files:*.*',@p_o_image_histo,macro);
     {$else}
               p_image := getstring(screen_histo.sizex)+'x'+getstring(screen_histo.sizey)+'graph.ppm';
               _savefile (p_image,'new-file','ppm','All images:*.bmp;*.png;*.ppm;*.tga;*.tif|All vectorimages:*.svg|All files:*.*',@p_o_image_histo,macro);
     {$endif}
     screen_histo_pressed := gtk_true;
end;

