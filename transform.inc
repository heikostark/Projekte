{ **************************************************************************** }
{ ******************************** Transform********************************** }
{ **************************************************************************** }

{ **************************************************************************** }

procedure proc_transform_object (p1,macro : gtk_pointer); cdecl;
begin inc (input); if input > 6 then input := 1; updating; end;

procedure proc_transform_objectedit (p1,macro : gtk_pointer); cdecl;
begin inc (inputedit); if inputedit > 6 then inputedit := 1; updating; end;

procedure proc_refresh (p1,macro : gtk_pointer); cdecl;
begin _cursor_watch; updating; drawing; _cursor_arrow; end;

procedure proc_screen (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     inc (screen);
     if screen > 5 then screen := 1;
     updating;
     short_drawing (false);
     case screen of
         1 : tmacro(macro^).writereundo ('screen.xy',old);
         2 : tmacro(macro^).writereundo ('screen.xz',old);
         4 : tmacro(macro^).writereundo ('screen.xt',old);
         3 : tmacro(macro^).writereundo ('screen.yz',old);
         5 : tmacro(macro^).writereundo ('screen.zt',old);
     end;
     _cursor_arrow;
end;

procedure proc_screen_xy (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     screen := 1;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('screen.xy',old);
     _cursor_arrow;
end;

procedure proc_screen_xz (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     screen := 2;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('screen.xz',old);
     _cursor_arrow;
end;

procedure proc_screen_xt (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     screen := 4;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('screen.xt',old);
     _cursor_arrow;
end;

procedure proc_screen_yz (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     screen := 3;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('screen.yz',old);
     _cursor_arrow;
end;

procedure proc_screen_zt (p1,macro : gtk_pointer); cdecl;
var old : utf16;
begin
     _cursor_watch;
     case screen of
         1 : old := 'screen.xy';
         2 : old := 'screen.xz';
         4 : old := 'screen.xt';
         3 : old := 'screen.yz';
         5 : old := 'screen.zt';
         else old := '';
     end;
     screen := 5;
     updating;
     short_drawing (false);
     tmacro(macro^).writereundo ('screen.zt',old);
     _cursor_arrow;
end;

{ ********************************* Clear ************************************ }

procedure proc_transform_clear_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(0,v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.clear.x');
     _cursor_arrow;
end;

procedure proc_transform_clear_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,0,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.clear.y');
     _cursor_arrow;
end;

procedure proc_transform_clear_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,0,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.clear.z');
     _cursor_arrow;
end;

procedure proc_transform_clear_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,0));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.clear.t');
     _cursor_arrow;
end;

{ ****************************** Spiegeln ************************************ }

procedure proc_transform_mirror_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(-1,1,1,1)*my^.getpoint(z));
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.mirror.x','transform.mirror.x');
     _cursor_arrow;
end;

procedure proc_transform_mirror_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,-1,1,1)*my^.getpoint(z));
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.mirror.y','transform.mirror.y');
     _cursor_arrow;
end;

procedure proc_transform_mirror_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,1,-1,1)*my^.getpoint(z));
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.mirror.z','transform.mirror.z');
     _cursor_arrow;
end;

procedure proc_transform_mirror_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,1,1,-1)*my^.getpoint(z));
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.mirror.t','transform.mirror.t');
     _cursor_arrow;
end;

{ ****************************** Absolute ************************************ }

procedure proc_transform_abs_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(abs(v.x),v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.abs.x');
     _cursor_arrow;
end;

procedure proc_transform_abs_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,abs(v.y),v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.abs.y');
     _cursor_arrow;
end;

procedure proc_transform_abs_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,abs(v.z),v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.abs.z');
     _cursor_arrow;
end;

procedure proc_transform_abs_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,abs(v.t)));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.abs.t');
     _cursor_arrow;
end;

{ ********************************** Inverse ********************************* }

procedure proc_transform_inv_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             if v.x <> 0.0 then my^.putpoint (z,gethyper(1/(v.x),v.y,v.z,v.t))
                           else my^.putpoint (z,gethyper(0,v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.inv.x','transform.inv.x');
     _cursor_arrow;
end;

procedure proc_transform_inv_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             if v.y <> 0.0 then my^.putpoint (z,gethyper(v.x,1/(v.y),v.z,v.t))
                           else my^.putpoint (z,gethyper(v.x,0,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.inv.y','transform.inv.y');
     _cursor_arrow;
end;

procedure proc_transform_inv_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             if v.z <> 0.0 then my^.putpoint (z,gethyper(v.x,v.y,1/(v.z),v.t))
                           else my^.putpoint (z,gethyper(v.x,v.y,0,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.inv.z','transform.inv.z');
     _cursor_arrow;
end;

procedure proc_transform_inv_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             if v.t <> 0.0 then my^.putpoint (z,gethyper(v.x,v.y,v.z,1/(v.t)))
                           else my^.putpoint (z,gethyper(v.x,v.y,v.z,0));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.inv.t','transform.inv.t');
     _cursor_arrow;
end;

{ ********************************** Ln ************************************* }

procedure proc_transform_ln_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(ln(v.x),v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.ln.x');
     _cursor_arrow;
end;

procedure proc_transform_ln_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,ln(v.y),v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.ln.y');
     _cursor_arrow;
end;

procedure proc_transform_ln_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,ln(v.z),v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.ln.z');
     _cursor_arrow;
end;

procedure proc_transform_ln_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,ln(v.t)));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.ln.t');
     _cursor_arrow;
end;

{ ********************************** Log ************************************* }

procedure proc_transform_log_x (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(log(base,v.x),v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.log.x',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_log_y (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,ln(v.y),v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.log.y',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_log_z (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,ln(v.z),v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.log.z',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_log_t (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,ln(v.t)));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.log.t',getstring(base));
     _cursor_arrow;
end;

{ ********************************** exp ************************************* }

procedure proc_transform_exp_x (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(power(base,v.x),v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.exp.x',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_exp_y (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,power(base,v.y),v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.exp.y',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_exp_z (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,power(base,v.z),v.t));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.exp.z',getstring(base));
     _cursor_arrow;
end;

procedure proc_transform_exp_t (p1,macro : gtk_pointer); cdecl;
var base : integer;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,power(base,v.t)));
        end;
end;
begin
     _cursor_watch;
     base := _getnat (transform_log_exp_base);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.exp.t',getstring(base));
     _cursor_arrow;
end;

{ ********************************** exp ************************************* }

procedure proc_transform_e_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(exp(v.x),v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.e.x');
     _cursor_arrow;
end;

procedure proc_transform_e_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,exp(v.y),v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.e.y');
     _cursor_arrow;
end;

procedure proc_transform_e_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,exp(v.z),v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.e.z');
     _cursor_arrow;
end;

procedure proc_transform_e_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.z,exp(v.t)));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.e.t');
     _cursor_arrow;
end;

{ ********************************** Swap ************************************ }

procedure proc_transform_swap_xy (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.y,v.x,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.xy','transform.swap.xy');
     _cursor_arrow;
end;

procedure proc_transform_swap_xz (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.z,v.y,v.x,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.xz','transform.swap.xz');
     _cursor_arrow;
end;

procedure proc_transform_swap_xt (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.t,v.y,v.z,v.x));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.xt','transform.swap.xt');
     _cursor_arrow;
end;

procedure proc_transform_swap_yz (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.z,v.y,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.yz','transform.swap.yz');
     _cursor_arrow;
end;

procedure proc_transform_swap_yt (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.t,v.z,v.y));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.yt','transform.swap.yt');
     _cursor_arrow;
end;

procedure proc_transform_swap_zt (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.x,v.y,v.t,v.z));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.swap.zt','transform.swap.zt');
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_transform_rol (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.y,v.z,v.t,v.x));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.rol','transform.ror');
     _cursor_arrow;
end;

procedure proc_transform_flip (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.t,v.z,v.y,v.x));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.flip','transform.flip');
     _cursor_arrow;
end;

procedure proc_transform_ror (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gethyper(v.t,v.x,v.y,v.z));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.ror','transform.rol');
     _cursor_arrow;
end;

{ ****************************** Skalieren *********************************** }

procedure proc_scale (p1,macro : gtk_pointer); cdecl;
var v : hyper;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (v);
end;
begin
     _cursor_watch;
     v := _gethyper (transform_scale,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.scale',getstring(v),'transform.invscale',getstring(v));
     _cursor_arrow;
end;

procedure proc_scale_pivot (p1,macro : gtk_pointer); cdecl;
var v : hyper;
procedure run (my : pcloud);
var u : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          u := v*centerall+centerall;
          my^.mul (v);
          my^.add (-1*u);
     end;
end;
begin
     _cursor_watch;
     v := _gethyper (transform_scale,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.scale.pivot',getstring(v),'transform.invscale.pivot',getstring(v));
     _cursor_arrow;
end;

procedure proc_invscale (p1,macro : gtk_pointer); cdecl;
var v,w : hyper;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (v);
end;
begin
     _cursor_watch;
     w := _gethyper (transform_scale,macro,1);
     v := 1/w;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.invscale',getstring(w),'transform.scale',getstring(w));
     _cursor_arrow;
end;

procedure proc_invscale_pivot (p1,macro : gtk_pointer); cdecl;
var v,w : hyper;
procedure run (my : pcloud);
var u : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          u := v*centerall+centerall;
          my^.mul (v);
          my^.add (-1*u);
     end;
end;
begin
     _cursor_watch;
     w := _gethyper (transform_scale,macro,1);
     v := 1 /w;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.invscale.pivot',getstring(w),'transform.scale.pivot',getstring(w));
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_gigascale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (1000000000*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.gigascale','','transform.nanoscale','');
     _cursor_arrow;
end;

procedure proc_megascale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (1000000*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.megascale','','transform.microscale','');
     _cursor_arrow;
end;

procedure proc_kiloscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (1000*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.kiloscale','','transform.milliscale','');
     _cursor_arrow;
end;

procedure proc_hectoscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (100*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.hectoscale','','transform.centiscale','');
     _cursor_arrow;
end;

procedure proc_decascale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (10*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.decascale','','transform.deciscale','');
     _cursor_arrow;
end;

procedure proc_deciscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (0.1*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.deciscale','','transform.decascale','');
     _cursor_arrow;
end;

procedure proc_centiscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (0.01*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.centiscale','','transform.hectoscale','');
     _cursor_arrow;
end;

procedure proc_milliscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (0.001*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.milliscale','','transform.kiloscale','');
     _cursor_arrow;
end;

procedure proc_microscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (0.000001*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.microscale','','transform.megascale','');
     _cursor_arrow;
end;

procedure proc_nanoscale (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.mul (0.000000001*Hnorm);
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.nanoscale','','transform.gigascale','');
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_scale_objects (p1,macro : gtk_pointer); cdecl;
var v : hyper;
procedure run (my : pcloud);
var z,o,l,p : integer;
    list : tpolyhyper;
    u : hyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getobjectlength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    u := list.get(o)-v*list.get(o);
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              my^.putobject (o,l,p,v*my^.getobject(o,l,p)+u);
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     _cursor_watch;
     v := _gethyper (transform_scale2,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.scale.objects',getstring(v),'transform.invscale.objects',getstring(v));
     _cursor_arrow;
end;

procedure proc_invscale_objects (p1,macro : gtk_pointer); cdecl;
var v,w : hyper;
procedure run (my : pcloud);
var z,o,l,p : integer;
    list : tpolyhyper;
    u : hyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getobjectlength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    u := list.get(o)-v*list.get(o);
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              my^.putobject (o,l,p,v*my^.getobject(o,l,p)+u);
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     _cursor_watch;
     w := _gethyper (transform_scale2,macro,1);
     v := 1/w;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.invscale.objects',getstring(w),'transform.scale.objects',getstring(w));
     _cursor_arrow;
end;

{ ****************************** Bewegen ************************************* }

procedure move (x,y : real);
var v : hyper;
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.add (v);
end;
begin
     case screen of
          1 : v := gh (x,y,0,0);
          2 : v := gh (x,0,y,0);
          4 : v := gh (x,0,0,y);
          3 : v := gh (0,x,y,0);
          5 : v := gh (0,0,x,y);
          else v := Hzero;
     end;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure movel (p1,macro : gtk_pointer); cdecl;
var step : real;
begin
     _cursor_watch;
     step := _getreal (transform_move,macro,1);
     move (-1*step,0);
     case screen of
          1 : tmacro(macro^).writereundo ('transform.move',getstring(gv(-1*step,0,0)),'transform.move',getstring(gv(step,0,0)));
          2 : tmacro(macro^).writereundo ('transform.move',getstring(gv(-1*step,0,0)),'transform.move',getstring(gv(step,0,0)));
          4 : tmacro(macro^).writereundo ('transform.move',getstring(gv(-1*step,0,0)),'transform.move',getstring(gv(step,0,0)));
          3 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,-1*step,0)),'transform.move',getstring(gv(0,step,0)));
          5 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,-1*step)),'transform.move',getstring(gv(0,0,step)));
     end;
     _cursor_arrow;
end;

procedure mover (p1,macro : gtk_pointer); cdecl;
var step : real;
begin
     _cursor_watch;
     step := _getreal (transform_move,macro,1);
     move (step,0);
     case screen of
          1 : tmacro(macro^).writereundo ('transform.move',getstring(gv(step,0,0)),'transform.move',getstring(gv(-1*step,0,0)));
          2 : tmacro(macro^).writereundo ('transform.move',getstring(gv(step,0,0)),'transform.move',getstring(gv(-1*step,0,0)));
          4 : tmacro(macro^).writereundo ('transform.move',getstring(gv(step,0,0)),'transform.move',getstring(gv(-1*step,0,0)));
          3 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,step,0)),'transform.move',getstring(gv(0,-1*step,0)));
          5 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,step)),'transform.move',getstring(gv(0,0,-1*step)));
     end;
     _cursor_arrow;
end;

procedure moveu (p1,macro : gtk_pointer); cdecl;
var step : real;
begin
     _cursor_watch;
     step := _getreal (transform_move,macro,1);
     move (0,step);
     case screen of
          1 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,step,0)),'transform.move',getstring(gv(0,-1*step,0)));
          2 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,step)),'transform.move',getstring(gv(0,0,-1*step)));
          4 : tmacro(macro^).writereundo ('transform.move',getstring(gh(0,0,0,step)),'transform.move',getstring(gh(0,0,0,-1*step)));
          3 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,step)),'transform.move',getstring(gv(0,0,-1*step)));
          5 : tmacro(macro^).writereundo ('transform.move',getstring(gh(0,0,0,step)),'transform.move',getstring(gh(0,0,0,-1*step)));
     end;
     _cursor_arrow;
end;

procedure moved (p1,macro : gtk_pointer); cdecl;
var step : real;
begin
     _cursor_watch;
     step := _getreal (transform_move,macro,1);
     move (0,-1*step);
     case screen of
          1 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,-1*step,0)),'transform.move',getstring(gv(0,step,0)));
          2 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,-1*step)),'transform.move',getstring(gv(0,0,step)));
          4 : tmacro(macro^).writereundo ('transform.move',getstring(gh(0,0,0,-1*step)),'transform.move',getstring(gh(0,0,0,step)));
          3 : tmacro(macro^).writereundo ('transform.move',getstring(gv(0,0,-1*step)),'transform.move',getstring(gv(0,0,step)));
          5 : tmacro(macro^).writereundo ('transform.move',getstring(gh(0,0,0,-1*step)),'transform.move',getstring(gh(0,0,0,step)));
     end;
     _cursor_arrow;
end;

{ *** Special *** }

procedure move_rel (v : hyper);
procedure run (my : pcloud);
begin
     if my^.getpointlength > 0 then my^.add (v);
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_move (p1,macro : gtk_pointer); cdecl; { only command }
var step : hyper;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(1) then
     begin
          step := gethyper (tmacro(macro^).getparameter(1));
          move_rel (step);
          tmacro(macro^).writereundo ('transform.move',getstring(step),'transform.move',getstring(-1*step));
     end;
     _cursor_arrow;
end;

{ ****************************** Rotieren ************************************ }

procedure rotation (center : hyper;rot : real);
procedure run (my : pcloud);
var z : integer;
    u,v,winkel: hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             u := v-center;
             case screen of
                  1 : begin
                           winkel := rotatezt (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  2 : begin
                           winkel := rotateyt (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  4 : begin
                           winkel := rotateyz (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  3 : begin
                           winkel := rotatext (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  5 : begin
                           winkel := rotatexy (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
             end;
        end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
end;

procedure rotl (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     rotation (Hzero,radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,radian*deg)),'transform.rotate',getstring(gv(0,0,-1*radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,radian*deg,0)),'transform.rotate',getstring(gv(0,-1*radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,radian*deg)),'transform.rotate',getstring(gv(0,0,-1*radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(radian*deg,0,0)),'transform.rotate',getstring(gv(-1*radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(radian*deg,0,0)),'transform.rotate',getstring(gv(-1*radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,radian)),'transform.rotate',getstring(gv(0,0,-1*radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,radian,0)),'transform.rotate',getstring(gv(0,-1*radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,radian)),'transform.rotate',getstring(gv(0,0,-1*radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(radian,0,0)),'transform.rotate',getstring(gv(-1*radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(radian,0,0)),'transform.rotate',getstring(gv(-1*radian,0,0)));
     end;
     _cursor_arrow;
end;

procedure rotr (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     rotation (Hzero,-1*radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,-1*radian*deg)),'transform.rotate',getstring(gv(0,0,radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,-1*radian*deg,0)),'transform.rotate',getstring(gv(0,radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,-1*radian*deg)),'transform.rotate',getstring(gv(0,0,radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(-1*radian*deg,0,0)),'transform.rotate',getstring(gv(radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(-1*radian*deg,0,0)),'transform.rotate',getstring(gv(radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,-1*radian)),'transform.rotate',getstring(gv(0,0,radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,-1*radian,0)),'transform.rotate',getstring(gv(0,radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(0,0,-1*radian)),'transform.rotate',getstring(gv(0,0,radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(-1*radian,0,0)),'transform.rotate',getstring(gv(radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate',getstring(gv(-1*radian,0,0)),'transform.rotate',getstring(gv(radian,0,0)));
     end;
     _cursor_arrow;
end;

procedure rotol (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     rotation (centerall,radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,radian*deg)),'transform.rotate.pivot',getstring(gv(0,0,-1*radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,radian*deg,0)),'transform.rotate.pivot',getstring(gv(0,-1*radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,radian*deg)),'transform.rotate.pivot',getstring(gv(0,0,-1*radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(radian*deg,0,0)),'transform.rotate.pivot',getstring(gv(-1*radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(radian*deg,0,0)),'transform.rotate.pivot',getstring(gv(-1*radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,radian)),'transform.rotate.pivot',getstring(gv(0,0,-1*radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,radian,0)),'transform.rotate.pivot',getstring(gv(0,-1*radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,radian)),'transform.rotate.pivot',getstring(gv(0,0,-1*radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(radian,0,0)),'transform.rotate.pivot',getstring(gv(-1*radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(radian,0,0)),'transform.rotate.pivot',getstring(gv(-1*radian,0,0)));
     end;
     _cursor_arrow;
end;

procedure rotor (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     rotation (centerall,-1*radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,-1*radian*deg)),'transform.rotate.pivot',getstring(gv(0,0,radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,-1*radian*deg,0)),'transform.rotate.pivot',getstring(gv(0,radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,-1*radian*deg)),'transform.rotate.pivot',getstring(gv(0,0,radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(-1*radian*deg,0,0)),'transform.rotate.pivot',getstring(gv(radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(-1*radian*deg,0,0)),'transform.rotate.pivot',getstring(gv(radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,-1*radian)),'transform.rotate.pivot',getstring(gv(0,0,radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,-1*radian,0)),'transform.rotate.pivot',getstring(gv(0,radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(0,0,-1*radian)),'transform.rotate.pivot',getstring(gv(0,0,radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(-1*radian,0,0)),'transform.rotate.pivot',getstring(gv(radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(gv(-1*radian,0,0)),'transform.rotate.pivot',getstring(gv(radian,0,0)));
     end;
     _cursor_arrow;
end;

procedure rotationobjects (rot : real);
procedure run (my : pcloud);
var z,o,l,p : integer;
    u,v,winkel: hyper;
    list : tpolyhyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getobjectlength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              v := my^.getobject (o,l,p);
                              u := v-list.get(o);
                              case screen of
                                   1 : begin
                                            winkel := rotatezt (u,rot);
                                            my^.putobject (o,l,p,list.get(o)+winkel);
                                       end;
                                   2 : begin
                                            winkel := rotateyt (u,rot);
                                            my^.putobject (o,l,p,list.get(o)+winkel);
                                       end;
                                   4 : begin
                                            winkel := rotateyz (u,rot);
                                            my^.putobject (o,l,p,list.get(o)+winkel);
                                       end;
                                   3 : begin
                                            winkel := rotatext (u,rot);
                                            my^.putobject (o,l,p,list.get(o)+winkel);
                                       end;
                                   5 : begin
                                            winkel := rotatexy (u,rot);
                                            my^.putobject (o,l,p,list.get(o)+winkel);
                                       end;
                              end;
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
end;

procedure proc_rotate_objects_left (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotate,macro,1)*rad { inptu to radian }
                      else radian := _getreal (transform_rotate,macro,1);
     rotationobjects (radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,radian*deg)),'transform.rotate.objects',getstring(gv(0,0,-1*radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,radian*deg,0)),'transform.rotate.objects',getstring(gv(0,-1*radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,radian*deg)),'transform.rotate.objects',getstring(gv(0,0,-1*radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(radian*deg,0,0)),'transform.rotate.objects',getstring(gv(-1*radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(radian*deg,0,0)),'transform.rotate.objects',getstring(gv(-1*radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,radian)),'transform.rotate.objects',getstring(gv(0,0,-1*radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,radian,0)),'transform.rotate.objects',getstring(gv(0,-1*radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,radian)),'transform.rotate.objects',getstring(gv(0,0,-1*radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(radian,0,0)),'transform.rotate.objects',getstring(gv(-1*radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(radian,0,0)),'transform.rotate.objects',getstring(gv(-1*radian,0,0)));
     end;
     _cursor_arrow;
end;

procedure proc_rotate_objects_right (p1,macro : gtk_pointer); cdecl;
var radian : real;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotate,macro,1)*rad { inptu to radian }
                      else radian := _getreal (transform_rotate,macro,1);
     rotationobjects (-1*radian);
     calculating;
     updating;
     drawing;
     if format.degree then
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,-1*radian*deg)),'transform.rotate.objects',getstring(gv(0,0,radian*deg)));
          2 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,-1*radian*deg,0)),'transform.rotate.objects',getstring(gv(0,radian*deg,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,-1*radian*deg)),'transform.rotate.objects',getstring(gv(0,0,radian*deg)));
          3 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(-1*radian*deg,0,0)),'transform.rotate.objects',getstring(gv(radian*deg,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(-1*radian*deg,0,0)),'transform.rotate.objects',getstring(gv(radian*deg,0,0)));
     end
     else
     case screen of
          1 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,-1*radian)),'transform.rotate.objects',getstring(gv(0,0,radian)));
          2 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,-1*radian,0)),'transform.rotate.objects',getstring(gv(0,radian,0)));
          4 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(0,0,-1*radian)),'transform.rotate.objects',getstring(gv(0,0,radian)));
          3 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(-1*radian,0,0)),'transform.rotate.objects',getstring(gv(radian,0,0)));
          5 : tmacro(macro^).writereundo ('transform.rotate.objects',getstring(gv(-1*radian,0,0)),'transform.rotate.objects',getstring(gv(radian,0,0)));
     end;
     _cursor_arrow;
end;

{ *** Special *** }

procedure rotate_rel (center : hyper;rot : hyper);
procedure run (my : pcloud);
var z : integer;
    v,u : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             u := v-center;
             u := rotatext (u,rot.x);
             u := rotateyt (u,rot.y);
             u := rotatezt (u,rot.z);
             my^.putpoint (z,center+u);
        end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_rotate (p1,macro : gtk_pointer); cdecl; { only command }
var radian : hyper;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(1) then
     begin
          if format.degree then radian := gethyper (tmacro(macro^).getparameter(1))*rad { input to radian }
                           else radian := gethyper (tmacro(macro^).getparameter(1));
          rotate_rel (Hzero,radian);
          if format.degree then tmacro(macro^).writereundo ('transform.rotate',getstring(radian*deg),'transform.rotate',getstring(-1*radian*deg))
                           else tmacro(macro^).writereundo ('transform.rotate',getstring(radian),'transform.rotate',getstring(-1*radian));
     end;
     _cursor_arrow;
end;

procedure proc_rotate_pivot (p1,macro : gtk_pointer); cdecl; { only command }
var radian : hyper;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(1) then
     begin
          if format.degree then radian := gethyper (tmacro(macro^).getparameter(1))*rad { input to radian }
                           else radian := gethyper (tmacro(macro^).getparameter(1));
          rotate_rel (centerall,radian);
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(radian*deg),'transform.rotate.pivot',getstring(-1*radian*deg))
                           else tmacro(macro^).writereundo ('transform.rotate.pivot',getstring(radian),'transform.rotate.pivot',getstring(-1*radian));
     end;
     _cursor_arrow;
end;

{ ****************************** matrix rotation ***************************** }

procedure rotate_vector (rot : real;vec : vector);
procedure run (my : pcloud);
var z : integer;
    u : hyper;
    v : vector;
    m : matrix3;
begin
     m := liball.rotate_vector (vec,rot);
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             u := my^.getpoint(z);
             v := liball.rotate (gv(u.x,u.y,u.z),m);
             my^.putpoint (z,gh(v,u.t)); { save u.t }
        end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
end;

procedure rotate_rel_vector (center : hyper;rot : real;vec : vector);
procedure run (my : pcloud);
var z : integer;
    m : matrix4;
    u : hyper;
    v : vector;
begin
     m := rel_rotate_vector (vec,rot,gv(center.x,center.y,center.z));
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             u := my^.getpoint(z);
             v := relativerotate (gv(u.x,u.y,u.z),m);
             my^.putpoint (z,gh(v,u.t)); { save u.t }
        end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
end;

procedure rotvl (p1,macro : gtk_pointer); cdecl;
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad  { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     vec := _getvector (transform_vector,macro,2);
     rotate_vector (radian,vec);
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(radian*deg)+' '+getstring(vec),'transform.rotate.vector',getstring(-1*radian*deg)+' '+getstring(vec))
                      else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(radian)+' '+getstring(vec),'transform.rotate.vector',getstring(-1*radian)+' '+getstring(vec));
     _cursor_arrow;
end;

procedure rotvr (p1,macro : gtk_pointer); cdecl;
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad  { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     vec := _getvector (transform_vector,macro,2);
     rotate_vector (-1*radian,vec);
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(-1*radian*deg)+' '+getstring(vec),'transform.rotate.vector',getstring(radian*deg)+' '+getstring(vec))
                      else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(-1*radian)+' '+getstring(vec),'transform.rotate.vector',getstring(radian)+' '+getstring(vec));
     _cursor_arrow;
end;

procedure rotvol (p1,macro : gtk_pointer); cdecl;
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad  { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     vec := _getvector (transform_vector,macro,2);
     rotate_rel_vector (centerall,radian,vec);
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(radian*deg)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(-1*radian*deg)+' '+getstring(vec))
                      else tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(radian)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(-1*radian)+' '+getstring(vec));
     _cursor_arrow;
end;

procedure rotvor (p1,macro : gtk_pointer); cdecl;
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if format.degree then radian := _getreal (transform_rotation,macro,1)*rad  { input to radian }
                      else radian := _getreal (transform_rotation,macro,1);
     vec := _getvector (transform_vector,macro,2);
     rotate_rel_vector (centerall,-1*radian,vec);
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(-1*radian*deg)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(radian*deg)+' '+getstring(vec))
                      else tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(-1*radian)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(radian)+' '+getstring(vec));
     _cursor_arrow;
end;

{ *** Special *** }

procedure proc_rotate_vector (p1,macro : gtk_pointer); cdecl; { only command }
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(2) then
     begin
          if format.degree then radian := getreal (tmacro(macro^).getparameter(1))*rad { input to radian }
                           else radian := getreal (tmacro(macro^).getparameter(1));
          vec := getvector (tmacro(macro^).getparameter(2));
          rotate_vector (radian,vec);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(radian*deg)+' '+getstring(vec),'transform.rotate.vector',getstring(-1*radian*deg)+' '+getstring(vec))
                           else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(radian)+' '+getstring(vec),'transform.rotate.vector',getstring(-1*radian)+' '+getstring(vec));
     end;
     _cursor_arrow;
end;

procedure proc_rotate_pivot_vector (p1,macro : gtk_pointer); cdecl; { only command }
var radian : real;
    vec : vector;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(2) then
     begin
          if format.degree then radian := getreal (tmacro(macro^).getparameter(1))*rad { input to radian }
                           else radian := getreal (tmacro(macro^).getparameter(1));
          vec := getvector (tmacro(macro^).getparameter(2));
          rotate_rel_vector (centerall,radian,vec);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(radian*deg)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(-1*radian*deg)+' '+getstring(vec))
                           else tmacro(macro^).writereundo ('transform.rotate.pivot.vector',getstring(radian)+' '+getstring(vec),'transform.rotate.pivot.vector',getstring(-1*radian)+' '+getstring(vec));
     end;
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_rotate_swap (p1,macro : gtk_pointer); cdecl; { only command }
var v1,v2 : vector;
begin
     v1 := _getvector (transform_vector1,macro,1);
     v2 := _getvector (transform_vector2,macro,2);
     _setedit (transform_vector1,getstring(v2));
     _setedit (transform_vector2,getstring(v1));
     tmacro(macro^).writereundo ('transform.rotate.swap','transform.rotate.swap');
end;

procedure proc_rotate_to (p1,macro : gtk_pointer); cdecl; { only command }
var radian : real;
    v1,v2,vec : vector;
begin
     _cursor_watch;
     v1 := _getvector (transform_vector1,macro,1);
     v2 := _getvector (transform_vector2,macro,2);
     if (v1 <> v2) and (v1 <> Vzero) and (v2 <> Vzero) then
     begin
          vec := cross (v1,v2);
          radian := fullangle (v1,v2,vec);
          rotate_vector (radian,vec);
          calculating;
          updating;
          drawing;
          tmacro(macro^).writereundo ('transform.rotate.to',getstring(v1)+' '+getstring(v2),'transform.rotate.to',getstring(v2)+' '+getstring(v1));
     end;
     _cursor_arrow;
end;

procedure proc_rotate_pivot_to (p1,macro : gtk_pointer); cdecl; { only command }
var radian : real;
    v1,v2,vec : vector;
begin
     _cursor_watch;
     v1 := _getvector (transform_vector1,macro,1);
     v2 := _getvector (transform_vector2,macro,2);
     if (v1 <> v2) and (v1 <> Vzero) and (v2 <> Vzero) then
     begin
          vec := cross (v1,v2);
          radian := fullangle (v1,v2,vec);
          rotate_rel_vector (centerall,radian,vec);
          calculating;
          updating;
          drawing;
          tmacro(macro^).writereundo ('transform.rotate.pivot.to',getstring(v1)+' '+getstring(v2),'transform.rotate.pivot.to',getstring(v2)+' '+getstring(v1));
     end;
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure rotate_objects_rel (rot : hyper);
procedure run (my : pcloud);
var z,o,l,p : integer;
    u,v : hyper;
    list : tpolyhyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getobjectlength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              v := my^.getobject (o,l,p);
                              u := v-list.get(o);
                              u := rotatext (u,rot.x);
                              u := rotateyt (u,rot.y);
                              u := rotatezt (u,rot.z);
                              my^.putobject (o,l,p,list.get(o)+u);
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_rotate_objects (p1,macro : gtk_pointer); cdecl; { only command }
var radian : hyper;
begin
     _cursor_watch;
     if tmacro(macro^).checkparameter(1) then
     begin
          if format.degree then radian := gethyper (tmacro(macro^).getparameter(1))*rad { input to radian }
                           else radian := gethyper (tmacro(macro^).getparameter(1));
          rotate_objects_rel (radian);
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.objects',getstring(radian*deg),'transform.rotate.objects',getstring(-1*radian*deg))
                           else tmacro(macro^).writereundo ('transform.rotate.objects',getstring(radian),'transform.rotate.objects',getstring(-1*radian));
     end;
     _cursor_arrow;
end;

{ **************************************************************************** }
{ **************************** Transform + *********************************** }
{ **************************************************************************** }

procedure setmatrix (m4 : matrix4);
begin
     _setedit (transform_matrix_1_1,getstring(m4[1].x));
     _setedit (transform_matrix_1_2,getstring(m4[1].y));
     _setedit (transform_matrix_1_3,getstring(m4[1].z));
     _setedit (transform_matrix_1_4,getstring(m4[1].t));

     _setedit (transform_matrix_2_1,getstring(m4[2].x));
     _setedit (transform_matrix_2_2,getstring(m4[2].y));
     _setedit (transform_matrix_2_3,getstring(m4[2].z));
     _setedit (transform_matrix_2_4,getstring(m4[2].t));

     _setedit (transform_matrix_3_1,getstring(m4[3].x));
     _setedit (transform_matrix_3_2,getstring(m4[3].y));
     _setedit (transform_matrix_3_3,getstring(m4[3].z));
     _setedit (transform_matrix_3_4,getstring(m4[3].t));

     _setedit (transform_matrix_4_1,getstring(m4[4].x));
     _setedit (transform_matrix_4_2,getstring(m4[4].y));
     _setedit (transform_matrix_4_3,getstring(m4[4].z));
     _setedit (transform_matrix_4_4,getstring(m4[4].t));
end;

procedure getmatrix (var m4 : matrix4);
begin
     m4[1].x := _getreal (transform_matrix_1_1);
     m4[1].y := _getreal (transform_matrix_1_2);
     m4[1].z := _getreal (transform_matrix_1_3);
     m4[1].t := _getreal (transform_matrix_1_4);

     m4[2].x := _getreal (transform_matrix_2_1);
     m4[2].y := _getreal (transform_matrix_2_2);
     m4[2].z := _getreal (transform_matrix_2_3);
     m4[2].t := _getreal (transform_matrix_2_4);

     m4[3].x := _getreal (transform_matrix_3_1);
     m4[3].y := _getreal (transform_matrix_3_2);
     m4[3].z := _getreal (transform_matrix_3_3);
     m4[3].t := _getreal (transform_matrix_3_4);

     m4[4].x := _getreal (transform_matrix_4_1);
     m4[4].y := _getreal (transform_matrix_4_2);
     m4[4].z := _getreal (transform_matrix_4_3);
     m4[4].t := _getreal (transform_matrix_4_4);
end;

procedure getmacro_matrix (var m4 : matrix4;macro : pointer;n : integer);
begin
     if tmacro(macro^).running then
     begin
          m4 := getmatrix4 (tmacro(macro^).getparameter (n));
     end
     else
     begin
          m4[1].x := _getreal (transform_matrix_1_1);
          m4[1].y := _getreal (transform_matrix_1_2);
          m4[1].z := _getreal (transform_matrix_1_3);
          m4[1].t := _getreal (transform_matrix_1_4);

          m4[2].x := _getreal (transform_matrix_2_1);
          m4[2].y := _getreal (transform_matrix_2_2);
          m4[2].z := _getreal (transform_matrix_2_3);
          m4[2].t := _getreal (transform_matrix_2_4);

          m4[3].x := _getreal (transform_matrix_3_1);
          m4[3].y := _getreal (transform_matrix_3_2);
          m4[3].z := _getreal (transform_matrix_3_3);
          m4[3].t := _getreal (transform_matrix_3_4);

          m4[4].x := _getreal (transform_matrix_4_1);
          m4[4].y := _getreal (transform_matrix_4_2);
          m4[4].z := _getreal (transform_matrix_4_3);
          m4[4].t := _getreal (transform_matrix_4_4);
     end;
     setmatrix (m4);
end;

procedure proc_transform_matrix_set (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new macro values or old gui values }
     getmacro_matrix (m4,macro,1);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_move_set (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    m : vector;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m := getvector (_getedit(transform_matrix_set,macro,1));
     n4 := M4norm;
     n4[4] := gh(m,1);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_move_reset (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4[4].x := 0;
     m4[4].y := 0;
     m4[4].z := 0;
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_scale_set (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    m : vector;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m := getvector (_getedit(transform_matrix_set,macro,1));
     n4[1] := gh(m.x,0,0,0);
     n4[2] := gh(0,m.y,0,0);
     n4[3] := gh(0,0,m.z,0);
     n4[4] := gh(0,0,0,1);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_scale_norm (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4[1] := norm(m4[1]);
     m4[2] := norm(m4[2]);
     m4[3] := norm(m4[3]);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_shearxy (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    m : complex;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m := getcomplex (_getedit(transform_matrix_set2,macro,1));
     n4 := M4norm;
     n4[3] := gh(m.x,m.y,1,0);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_shearxz (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    m : complex;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m := getcomplex (_getedit(transform_matrix_set2,macro,1));
     n4 := M4norm;
     n4[2] := gh(m.x,1,m.y,0);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_shearyz (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    m : complex;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m := getcomplex (_getedit(transform_matrix_set2,macro,1));
     n4 := M4norm;
     n4[1] := gh(1,m.x,m.y,0);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_rotatex (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    r : real;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     if format.degree then r := _getreal(transform_matrix_rotation,macro,1)*rad { input to radian }
                      else r := _getreal(transform_matrix_rotation,macro,1);
     n4[1] := gh(1,0,0,0);
     n4[2] := gh(0,cos(r),sin(r),0);
     n4[3] := gh(0,-1*sin(r),cos(r),0);
     n4[4] := gh(0,0,0,1);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_rotatey (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    r : real;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     if format.degree then r := _getreal(transform_matrix_rotation,macro,1)*rad { input to radian }
                      else r := _getreal(transform_matrix_rotation,macro,1);
     n4[1] := gh(cos(r),0,-1*sin(r),0);
     n4[2] := gh(0,1,0,0);
     n4[3] := gh(sin(r),0,cos(r),0);
     n4[4] := gh(0,0,0,1);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_rotatez (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
    r : real;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     if format.degree then r := _getreal(transform_matrix_rotation,macro,1)*rad { input to radian }
                      else r := _getreal(transform_matrix_rotation,macro,1);
     n4[1] := gh(cos(r),sin(r),0,0);
     n4[2] := gh(-1*sin(r),cos(r),0,0);
     n4[3] := gh(0,0,1,0);
     n4[4] := gh(0,0,0,1);
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_mirrorx (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
          n4 := M4norm;
     n4[1].x := -1;
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_mirrory (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     n4 := M4norm;
     n4[2].y := -1;
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_mirrorz (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4,n4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     n4 := M4norm;
     n4[3].z := -1;
     m4 := join (m4,n4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_identity (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4 := M4norm;
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_norm (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4 := norm (m4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_transpose (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4 := transpose (m4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_adjugate (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4 := adjugate (m4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

procedure proc_transform_matrix_inverse (p1,macro : gtk_pointer); cdecl;
var u,v : utf16;
    m4 : matrix4;
begin
     _cursor_watch;
     { get old }
     getmatrix (m4);
     v := getstring(m4);
     { get new }
     m4 := inverse (m4);
     setmatrix (m4);
     u := getstring(m4);
     { ready }
     updating;
     tmacro(macro^).writereundo ('transform.matrix.set',u,'transform.matrix.set',v);
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_get_matrix (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     s :=  '('+getstring(m4[1],d)+';'+getstring(m4[2],d)+';'+getstring(m4[3],d)+';'+getstring(m4[4],d)+')';
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_matrix3 (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3 : matrix3;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3(m4);
     s :=  '('+getstring(m3[1],d)+';'+getstring(m3[2],d)+';'+getstring(m3[3],d)+')';
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_vector (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     s :=  getstring(gv(m4[4].x,m4[4].y,m4[4].z),d);
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_eigenvalues (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3 : matrix3;
    sm3 : symmatrix3;
    v : vector;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then v := eigenvalues2 (sm3)
                             else v := Vzero;
     {writeln (eigenvalues (sm3));}
     s := getstring(v,d);
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_eigenvalues_norm (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3 : matrix3;
    sm3 : symmatrix3;
    v : vector;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then v := norm(eigenvalues2 (sm3))
                             else v := Vzero;
     s := getstring(v,d);
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_eigenvalues_westin (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3 : matrix3;
    sm3 : symmatrix3;
    v,w : vector;
    m : real;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then
     begin
          v := eigenvalues2 (sm3);
          m := (v.x+v.y+v.z);
          if m <> 0.0 then w := gv((v.x-v.y)/m,2*(v.y-v.z)/m,3*v.z/m)
                      else w := Vzero;
     end
     else w := Vzero;
     s := getstring(w,d);
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_eigenvalues_westin_rank (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3 : matrix3;
    sm3 : symmatrix3;
    v,w : vector;
    m : real;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then
     begin
          v := eigenvalues2 (sm3);
          m := (v.x+v.y+v.z);
          if m <> 0.0 then
          begin
               w := gv((v.x-v.y)/m,2*(v.y-v.z)/m,3*v.z/m);
               if w.z >= 0.5 then begin w.x := 0; w.y := 0; end;
               if w.y >= 0.5 then begin w.x := 0; w.z := 0; end;
               if w.x >= 0.5 then begin w.y := 0; w.z := 0; end;
          end
          else w := Vzero;
     end
     else w := Vzero;
     s := getstring(w,d);
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_get_eigenvectors (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    d : integer;
    m4 : matrix4;
    m3,n3 : matrix3;
    sm3 : symmatrix3;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then n3 := eigenvectors2 (sm3)
                             else n3 := M3zero;
     {writeln (eigenvectors (sm3));}
     s :=  '('+getstring(n3[1],d)+';'+getstring(n3[2],d)+';'+getstring(n3[3],d)+')';
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_show_eigen (p1,macro : gtk_pointer); cdecl;
var m4 : matrix4;
    m3,n3 : matrix3;
    sm3 : symmatrix3;
    v : vector;
begin
     _cursor_watch;
     getmatrix (m4);
     m3 := getmatrix3 (m4);
     sm3 := getsymmatrix3 (m3);
     if m3 = getmatrix3(sm3) then
     begin
          eigen2 (sm3,v,n3);
          finput^.newpoint(Hzero);
          finput^.newpoint(gh(norm(n3[1])*v.x,0));
          finput^.newline(0);
          finput^.newpoint(Hzero);
          finput^.newpoint(gh(norm(n3[2])*v.y,0));
          finput^.newline(0);
          finput^.newpoint(Hzero);
          finput^.newpoint(gh(norm(n3[3])*v.z,0));
          finput^.newline(0);
          finput^.newobject ('Eigen');
          calculating;
          updating;
          drawing;
     end;
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_transform_matrix (p1,macro : gtk_pointer); cdecl;
var m4 : matrix4;
    u,v : hyper;
    m : utf16;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             u := my^.getpoint(z);
             v := u;
             v.t := 1;
             v := transform (v,m4);
             my^.putpoint (z,gh(v.x,v.y,v.z,u.t));
        end;
end;
begin
     _cursor_watch;
     { get new macro values or old gui values }
     getmatrix (m4);
     m := getstring(m4);
     { ready }
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     m4 := inverse (m4);
     tmacro(macro^).writereundo ('transform.matrix',m,'transform.matrix',getstring(m4));
     _cursor_arrow;
end;

procedure proc_transform_determinate (p1,macro : gtk_pointer); cdecl;
var d : integer;
    m4 : matrix4;
begin
     _cursor_watch;
     d := limit (_getnat(transform_clipboard_digits),0,50);
     getmatrix (m4);
     _setedit (transform_det,getstring(det(m4),d));
     _cursor_arrow;
end;

procedure proc_transform_matrix_back (p1,macro : gtk_pointer); cdecl;
var m4 : matrix4;
    u,v : hyper;
    m : utf16;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             u := my^.getpoint(z);
             v := u;
             v.t := 1;
             v := transform (v,m4);
             my^.putpoint (z,gh(v.x,v.y,v.z,u.t));
        end;
end;
begin
     _cursor_watch;
     { get new macro values or old gui values }
     getmatrix (m4);
     m := getstring(m4);
     { ****** }
     m4 := inverse (m4);
     { ready }
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.matrix',getstring(m4),'transform.matrix',m);
     _cursor_arrow;
end;

{ ********************************** Center ********************************** }

procedure proc_transform_center (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-centerall);
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.center','','transform.move',getstring(centerall));
     _cursor_arrow;
end;

procedure proc_transform_center_objects (p1,macro : gtk_pointer); cdecl;
var step : real;
procedure run (my : pcloud);
var z,o,l,p : integer;
    list : tpolyhyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getobjectlength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              my^.putobject (o,l,p,my^.getobject(o,l,p)-(list.get(o)*step));
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     _cursor_watch;
     step := _getreal (transform_step_center,macro,1)/100;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.center.objects',getstring(step*100));
     _cursor_arrow;
end;

{ *************************** Global-Balance ********************************* }

procedure proc_transform_globalbalance (p1,macro : gtk_pointer); cdecl;
var mybalance : real;
    mymax,myvector : vector;
procedure run (f : pcloud);
var p1,p2,sp1,sp2 : integer;
    d,n : real;
    h : hyper;
begin
     if f^.getpointlength > 1 then
     begin
          d := 0;
          sp1 := 1;
          sp2 := 2;
          for p1 := 1 to f^.getpointlength-1 do
          begin
               for p2 := p1+1 to f^.getpointlength do
               begin
                    n := getlength((f^.getpoint (p1)-f^.getpoint(p2)));
                    if d < n then
                    begin
                         sp1 := p1;
                         sp2 := p2;
                         d := n;
                    end;
               end;
               progress ('Calculate neighbors (points)',p1/f^.getpointlength);
          end;
          progress;
          if d > getlength(mymax) then
          begin
               h := f^.getpoint (sp1)-f^.getpoint (sp2);
               mymax := gv (h.x,h.y,h.z);
          end;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     mymax := Vzero;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     myvector := cross (mymax,Vright);
     mybalance := fullangle (mymax,Vright,myvector);
     if (myvector <> Vzero) and (mybalance <> 0) then
     begin
          if format.degree then _setedit (transform_rotation,getstring(mybalance*deg))
                           else _setedit (transform_rotation,getstring(mybalance));
          _setedit (transform_vector,getstring(myvector));
          rotate_vector (mybalance,myvector);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance*deg)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance*deg)+' '+getstring(myvector))
                           else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance)+' '+getstring(myvector));
     end;
     _cursor_arrow;
end;

procedure proc_transform_fast_globalbalance (p1,macro : gtk_pointer); cdecl;
var mybalance : real;
    mymax,myvector : vector;
procedure run (f : pcloud);
var p1,p2,sp1,sp2,i : integer;
    d,n : real;
    h : hyper;
begin
     if f^.getpointlength > 1 then
     begin
          d := 0;
          sp1 := 1;
          sp2 := 2;
          for p1 := 1 to f^.getpointlength do
          begin
               for i := 1 to (f^.getpointlength div 20) { 5% } do
               begin
                    p2 := random (f^.getpointlength);
                    n := getlength((f^.getpoint (p1)-f^.getpoint(p2)));
                    if d < n then
                    begin
                         sp1 := p1;
                         sp2 := p2;
                         d := n;
                    end;
               end;
               progress ('Calculate neighbors (5% points)',p1/f^.getpointlength);
          end;
          progress;
          if d > getlength(mymax) then
          begin
               h := f^.getpoint (sp1)-f^.getpoint (sp2);
               mymax := gv (h.x,h.y,h.z);
          end;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     mymax := Vzero;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     myvector := cross (mymax,Vright);
     mybalance := fullangle (mymax,Vright,myvector);
     if (myvector <> Vzero) and (mybalance <> 0) then
     begin
          if format.degree then _setedit (transform_rotation,getstring(mybalance*deg))
                           else _setedit (transform_rotation,getstring(mybalance));
          _setedit (transform_vector,getstring(myvector));
          rotate_vector (mybalance,myvector);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance*deg)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance*deg)+' '+getstring(myvector))
                           else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance)+' '+getstring(myvector));
     end;
     _cursor_arrow;
end;

{ ****************************** Local-Balance ******************************* }

procedure proc_transform_localbalance (p1,macro : gtk_pointer); cdecl;
var mylen,mybalance : real;
    mymax,myvector : vector;
procedure run (my : pcloud);
var u,v : hyper;
    p : vector;
    p1,p2 : integer;
begin
     if my^.getpointlength > 1 then
     begin
          for p1 := 1 to my^.getpointlength-1 do
          begin
               for p2 := p1+1 to my^.getpointlength do
               begin
                    case screen of
                         1 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(u.x-v.x,u.y-v.y,0);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                             end;
                         2 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(u.x-v.x,0,u.z-v.z);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                             end;
                         4 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.x-v.x,u.t-v.t);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                         3 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.y-v.y,u.z-v.z);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                         5 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.z-v.z,u.t-v.t);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                    end;
               end;
               progress ('Calculate local neighbors (points)',p1/my^.getpointlength);
          end;
          progress;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     mylen := 0; mymax := Vzero;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     case screen of
          1 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          2 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          4 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          3 : begin myvector := cross (mymax,Vup); mybalance := fullangle (mymax,Vup,myvector); end;
          5 : begin myvector := cross (mymax,Vnear); mybalance := fullangle (mymax,Vnear,myvector); end;
          else begin myvector := Vzero; mybalance := 0; end;
     end;
     if (not into(myvector,Vnorm*-0.000000001,Vnorm*0.000000001)) and (mybalance <> 0) then
     begin
          if format.degree then _setedit (transform_rotation,getstring(mybalance*deg))
                           else _setedit (transform_rotation,getstring(mybalance));
          _setedit (transform_vector,getstring(myvector));
          rotate_vector (mybalance,myvector);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance*deg)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance*deg)+' '+getstring(myvector))
                           else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance)+' '+getstring(myvector));
     end;
     _cursor_arrow;
end;

procedure proc_transform_fast_localbalance (p1,macro : gtk_pointer); cdecl;
var mylen,mybalance : real;
    mymax,myvector : vector;
procedure run (my : pcloud);
var u,v : hyper;
    p : vector;
    p1,p2,i : integer;
begin
     if my^.getpointlength > 1 then
     begin
          for p1 := 1 to my^.getpointlength do
          begin
               for i := 1 to (my^.getpointlength div 20) { 5% } do
               begin
                    p2 := random (my^.getpointlength);
                    case screen of
                         1 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(u.x-v.x,u.y-v.y,0);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                             end;
                         2 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(u.x-v.x,0,u.z-v.z);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                             end;
                         4 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.x-v.x,u.t-v.t);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                         3 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.y-v.y,u.z-v.z);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                         5 : begin
                                  u := my^.getpoint (p1);
                                  v := my^.getpoint (p2);
                                  p := gv(0,u.z-v.z,u.t-v.t);
                                  if mylen < getlength(p) then
                                  begin
                                       mylen := getlength(p);
                                       mymax := p;
                                  end;
                              end;
                    end;
               end;
               progress ('Calculate local neighbors (5% points)',p1/my^.getpointlength);
          end;
          progress;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     mylen := 0; mymax := Vzero;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     case screen of
          1 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          2 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          4 : begin myvector := cross (mymax,Vright); mybalance := fullangle (mymax,Vright,myvector); end;
          3 : begin myvector := cross (mymax,Vup); mybalance := fullangle (mymax,Vup,myvector); end;
          5 : begin myvector := cross (mymax,Vnear); mybalance := fullangle (mymax,Vnear,myvector); end;
          else begin myvector := Vzero; mybalance := 0; end;
     end;
     if (not into(myvector,Vnorm*-0.000000001,Vnorm*0.000000001)) and (mybalance <> 0) then
     begin
          if format.degree then _setedit (transform_rotation,getstring(mybalance*deg))
                           else _setedit (transform_rotation,getstring(mybalance));
          _setedit (transform_vector,getstring(myvector));
          rotate_vector (mybalance,myvector);
          calculating;
          updating;
          drawing;
          if format.degree then tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance*deg)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance*deg)+' '+getstring(myvector))
                           else tmacro(macro^).writereundo ('transform.rotate.vector',getstring(mybalance)+' '+getstring(myvector),'transform.rotate.vector',getstring(-1*mybalance)+' '+getstring(myvector));
     end;
     _cursor_arrow;
end;

{ ****************************** Max-Balance ********************************* }

procedure proc_transform_maxxbalance (p1,macro : gtk_pointer); cdecl;
var p,n : integer;
procedure run (my : pcloud);
var u : hyper;
    x : integer;
begin
     if my^.getpointlength >  0 then
     begin
          for x := 1 to my^.getpointlength do
          begin
               u := my^.getpoint (x);
               case screen of
                    1 : if u.x < 0 then inc (n) else inc (p);
                    2 : if u.x < 0 then inc (n) else inc (p);
                    4 : if u.x < 0 then inc (n) else inc (p);
                    3 : if u.y < 0 then inc (n) else inc (p);
                    5 : if u.z < 0 then inc (n) else inc (p);
               end;
          end;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     p := 0;
     n := 0;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     if p < n then
     begin
          _setedit (transform_rotation,getstring(180));
          _update;
          _cursor_arrow;
          rotl (p1,macro);
          tmacro(macro^).writeredo ('// transform.balance.maxx');
     end
     else _cursor_arrow;
end;

procedure proc_transform_maxybalance (p1,macro : gtk_pointer); cdecl;
var p,n : integer;
procedure run (my : pcloud);
var u : hyper;
    x : integer;
begin
     if my^.getpointlength >  0 then
     begin
          for x := 1 to my^.getpointlength do
          begin
               u := my^.getpoint (x);
               case screen of
                    1 : if u.y < 0 then inc (n) else inc (p);
                    2 : if u.z < 0 then inc (n) else inc (p);
                    4 : if u.t < 0 then inc (n) else inc (p);
                    3 : if u.z < 0 then inc (n) else inc (p);
                    5 : if u.t < 0 then inc (n) else inc (p);
               end;
          end;
     end;
end;
begin
     _cursor_watch;
{ Balance }
     p := 0;
     n := 0;
     if ref_state[1] then run (@red);
     _update;
     if ref_state[2] then run (@green);
     _update;
     if ref_state[3] then run (@blue);
     _update;
     if ref_state[4] then run (@yellow);
     _update;
     if ref_state[5] then run (@cyan);
     _update;
     if ref_state[6] then run (@purple);
     _update;
{ Rotation }
     if p < n then
     begin
          _setedit (transform_rotation,getstring(180));
          _update;
          _cursor_arrow;
          rotl (p1,macro);
          tmacro(macro^).writeredo ('// transform.balance.maxy');
     end
     else _cursor_arrow;
end;

{ *************************** Center + Balance ******************************* }

procedure proc_transform_adjust (p1,macro : gtk_pointer); cdecl;
begin
     ifdraw := false;
     proc_transform_center (p1,macro);
     proc_transform_globalbalance (p1,macro);
     proc_screen_yz (p1,macro);
     proc_transform_localbalance (p1,macro);
     proc_transform_maxybalance (p1,macro); // drawing olny if nesessary
     proc_screen_xy (p1,macro);
     proc_transform_maxxbalance (p1,macro); // drawing olny if nesessary
     ifdraw := true;
     calculating;
     updating;
     drawing;
end;

procedure proc_transform_adjust_fast (p1,macro : gtk_pointer); cdecl;
begin
     ifdraw := false;
     proc_transform_center (p1,macro);
     proc_transform_fast_globalbalance (p1,macro);
     proc_screen_yz (p1,macro);
     proc_transform_fast_localbalance (p1,macro);
     proc_transform_maxybalance (p1,macro); // drawing olny if nesessary
     proc_screen_xy (p1,macro);
     proc_transform_maxxbalance (p1,macro); // drawing olny if nesessary
     ifdraw := true;
     calculating;
     updating;
     drawing;
end;

{ **************************************************************************** }

procedure proc_transform_adjust_lines (p1,macro : gtk_pointer); cdecl;
var mylen,mybalance : real;
    b : integer;
    c : complex;
procedure runc (my : pcloud); { Center }
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-centerall);
        end;
end;
procedure runb (my : pcloud); { Balance }
var u,v : hyper;
    p : complex;
    x,y,o,l : integer;
begin
     if my^.getobjectlength > 1 then
     begin
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength (o) do
                    begin
                         if my^.getlinepointlength (o,l) > 1 then
                         begin
                              for x := 1 to my^.getlinepointlength (o,l)-1 do
                                  for y := x+1 to my^.getlinepointlength (o,l) do
                                  begin
                                       case screen of
                                            1 : begin
                                                     u := my^.getobject (o,l,x);
                                                     v := my^.getobject (o,l,y);
                                                     p := gc(u.x-v.x,u.y-v.y);
                                                     if mylen < getlength(p) then
                                                     begin
                                                          mylen := getlength(p);
                                                          c := p;
                                                     end;
                                                end;
                                            2 : begin
                                                     u := my^.getobject (o,l,x);
                                                     v := my^.getobject (o,l,y);
                                                     p := gc(u.x-v.x,u.z-v.z);
                                                     if mylen < getlength(p) then
                                                     begin
                                                          mylen := getlength(p);
                                                          c := p;
                                                     end;
                                                end;
                                            4 : begin
                                                     u := my^.getobject (o,l,x);
                                                     v := my^.getobject (o,l,y);
                                                     p := gc(u.x-v.x,u.t-v.t);
                                                     if mylen < getlength(p) then
                                                     begin
                                                          mylen := getlength(p);
                                                          c := p;
                                                     end;
                                                 end;
                                            3 : begin
                                                     u := my^.getobject (o,l,x);
                                                     v := my^.getobject (o,l,y);
                                                     p := gc(u.y-v.y,u.z-v.z);
                                                     if mylen < getlength(p) then
                                                     begin
                                                          mylen := getlength(p);
                                                          c := p;
                                                     end;
                                                 end;
                                            5 : begin
                                                     u := my^.getobject (o,l,x);
                                                     v := my^.getobject (o,l,y);
                                                     p := gc(u.z-v.z,u.t-v.t);
                                                     if mylen < getlength(p) then
                                                     begin
                                                          mylen := getlength(p);
                                                          c := p;
                                                     end;
                                                 end;
                                       end;
                                  end;
                         end;
                    end;
               end;
          end;
     end;

end;
begin
     _cursor_watch;
     for b := 1 to 6 do
     begin
{ Center }
          if state[1] then runc (@red);
          _update;
          if state[2] then runc (@green);
          _update;
          if state[3] then runc (@blue);
          _update;
          if state[4] then runc (@yellow);
          _update;
          if state[5] then runc (@cyan);
          _update;
          if state[6] then runc (@purple);
          _update;
          calculating;
          _update;
{ Balance }
          mylen := 0; c := Czero;
          if ref_state[1] then runb (@red);
          _update;
          if ref_state[2] then runb (@green);
          _update;
          if ref_state[3] then runb (@blue);
          _update;
          if ref_state[4] then runb (@yellow);
          _update;
          if ref_state[5] then runb (@cyan);
          _update;
          if ref_state[6] then runb (@purple);
          _update;
{ Rotation }
          mybalance := -1*fullangle(c,Cright,Cup);
          if format.degree then _setedit (transform_rotation,getstring(mybalance*deg))
                           else _setedit (transform_rotation,getstring(mybalance));
          rotation (centerall,mybalance);
          _update;
          calculating;
          _update;
          inc (screen);
          if screen > 3 then screen := 1;
     end;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.adjust.lines');
     _cursor_arrow;
end;

{ ****************************** matrix rotation ***************************** }

procedure rotation_matrix (m : matrix3);
procedure run (my : pcloud);
var z : integer;
    u : hyper;
    v : vector;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             u := my^.getpoint(z);
             v := rotate (gv(u.x,u.y,u.z),m);
             my^.putpoint (z,gh(v,u.t));
        end;
end;
begin
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
end;

{ ***** }

procedure proc_transform_rotate_xyz (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_xyz (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.xyz',getstring(vec*deg),'transform.rotate.zyx',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.xyz',getstring(vec),'transform.rotate.zyx',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_xzy (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_xzy (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.xzy',getstring(vec*deg),'transform.rotate.yzx',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.xzy',getstring(vec),'transform.rotate.yzx',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_yxz (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_yxz (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.yxz',getstring(vec*deg),'transform.rotate.zxy',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.yxz',getstring(vec),'transform.rotate.zxy',getstring(-1*vec));
     _cursor_arrow;
end;
procedure proc_transform_rotate_yzx (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_yzx (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.yzx',getstring(vec*deg),'transform.rotate.xzy',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.yzx',getstring(vec),'transform.rotate.xzy',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_zxy (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_zxy (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.zxy',getstring(vec*deg),'transform.rotate.yxz',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.zxy',getstring(vec),'transform.rotate.yxz',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_zyx (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_cardan,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_cardan,macro,1);
     rotation_matrix (rotate_zyx (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.zyx',getstring(vec*deg),'transform.rotate.xyz',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.zyx',getstring(vec),'transform.rotate.xyz',getstring(-1*vec));
     _cursor_arrow;
end;

{ ****** }

procedure proc_transform_rotate_xyx (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_xyx (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.xyx',getstring(vec*deg),'transform.rotate.xyx',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.xyx',getstring(vec),'transform.rotate.xyx',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_xzx (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_xzx (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.xzx',getstring(vec*deg),'transform.rotate.xzx',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.xzx',getstring(vec),'transform.rotate.xzx',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_yxy (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_yxy (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.yxy',getstring(vec*deg),'transform.rotate.yxy',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.yxy',getstring(vec),'transform.rotate.yxy',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_yzy (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_yzy (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.yzy',getstring(vec*deg),'transform.rotate.yzy',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.yzy',getstring(vec),'transform.rotate.yzy',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_zxz (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_zxz (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.zxz',getstring(vec*deg),'transform.rotate.zxz',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.zxz',getstring(vec),'transform.rotate.zxz',getstring(-1*vec));
     _cursor_arrow;
end;

procedure proc_transform_rotate_zyz (p1,macro : gtk_pointer); cdecl;
var vec : vector;
begin
     _cursor_watch;
     if format.degree then vec := _getvector (transform_euler,macro,1)*rad { input to radian }
                      else vec := _getvector (transform_euler,macro,1);
     rotation_matrix (rotate_zyz (vec.x,vec.y,vec.z));
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writereundo ('transform.rotate.zyz',getstring(vec*deg),'transform.rotate.zyz',getstring(-1*vec*deg))
                      else tmacro(macro^).writereundo ('transform.rotate.zyz',getstring(vec),'transform.rotate.zyz',getstring(-1*vec));
     _cursor_arrow;
end;

{ ********************************* Align ************************************ }

{proc_transform_center}
procedure proc_transform_center_x (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x-centerall.x,v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.center.x','','transform.move',getstring(gh(centerall.x,0,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_center_y (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y-centerall.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.center.y','','transform.move',getstring(gh(0,centerall.y,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_center_z (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z-centerall.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.center.z','','transform.move',getstring(gh(0,0,centerall.z,0)));
     _cursor_arrow;
end;

procedure proc_transform_center_t (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z,v.t-centerall.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.center.t','','transform.move',getstring(gh(0,0,0,centerall.t)));
     _cursor_arrow;
end;

procedure proc_transform_align_p (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-minall);
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.+','','transform.move',getstring(minall));
     _cursor_arrow;
end;

procedure proc_transform_align_px (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x-minall.x,v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.x','','transform.move',getstring(gh(minall.x,0,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_py (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y-minall.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.y','','transform.move',getstring(gh(0,minall.y,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_pz (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z-minall.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.z','','transform.move',getstring(gh(0,0,minall.z,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_pt (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z,v.t-minall.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.t','','transform.move',getstring(gh(0,0,0,minall.t)));
     _cursor_arrow;
end;

procedure proc_transform_align_n (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-maxall);
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.-','','transform.move',getstring(maxall));
     _cursor_arrow;
end;

procedure proc_transform_align_nx (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x-maxall.x,v.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.-x','','transform.move',getstring(gh(maxall.x,0,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_ny (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y-maxall.y,v.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.-y','','transform.move',getstring(gh(0,maxall.y,0,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_nz (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z-maxall.z,v.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.-z','','transform.move',getstring(gh(0,0,maxall.z,0)));
     _cursor_arrow;
end;

procedure proc_transform_align_nt (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh (v.x,v.y,v.z,v.t-maxall.t));
        end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writereundo ('transform.align.-t','','transform.move',getstring(gh(0,0,0,maxall.t)));
     _cursor_arrow;
end;

{ ********************************* Align line ******************************* }

procedure proc_transform_align_begin (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var o,l,p : integer;
    center : hyper;
begin
     if my^.getobjectlength > 0 then
     begin
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         begin
                              center := my^.getobject(o,l,1);
                              for p := 1 to my^.getlinepointlength(o,l) do
                              begin
                                   my^.putobject(o,l,p,my^.getobject(o,l,p)-center);
                              end;
                         end;
                    end;
               end;
          end;
     end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.align.begin');
     _cursor_arrow;
end;

procedure proc_transform_align_end (p1,macro : gtk_pointer); cdecl;
procedure run (my : pcloud);
var o,l,p : integer;
    center : hyper;
begin
     if my^.getobjectlength > 0 then
     begin
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         begin
                              center := my^.getobject(o,l,my^.getlinepointlength(o,l));
                              for p := 1 to my^.getlinepointlength(o,l) do
                              begin
                                   my^.putobject(o,l,p,my^.getobject(o,l,p)-center);
                              end;
                         end;
                    end;
               end;
          end;
     end;
end;
begin
     _cursor_watch;
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.align.end');
     _cursor_arrow;
end;

{ ************************************* Min ********************************** }

procedure proc_transform_min_x (p1,macro : gtk_pointer); cdecl;
var mymin : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.x := mymin;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.min.x',getstring(mymin));
     _cursor_arrow;
end;

procedure proc_transform_min_y (p1,macro : gtk_pointer); cdecl;
var mymin : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.y := mymin;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.min.y',getstring(mymin));
     _cursor_arrow;
end;

procedure proc_transform_min_z (p1,macro : gtk_pointer); cdecl;
var mymin : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.z := mymin;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.min.z',getstring(mymin));
     _cursor_arrow;
end;

procedure proc_transform_min_t (p1,macro : gtk_pointer); cdecl;
var mymin : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.t := mymin;
{               write (v); write (' ');}
               my^.putpoint (z,v);
{               writeln (my^.getpoint(z));}
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
{     writeln (mymin);}
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.min.t',getstring(mymin));
     _cursor_arrow;
end;

{ ************************************ Norm ********************************** }

procedure proc_transform_norm_x (p1,macro : gtk_pointer); cdecl;
var mymin,mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
    _min,_max : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          _min := my^.min;
          _max := my^.max;
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.x := minmax (_min.x,_max.x,v.x,mymin,mymax);
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     mymax := _getreal (transform_norm_max,macro,2);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.norm.x',getstring(mymin)+' '+getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_norm_y (p1,macro : gtk_pointer); cdecl;
var mymin,mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
    _min,_max : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          _min := my^.min;
          _max := my^.max;
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.y := minmax (_min.y,_max.y,v.y,mymin,mymax);
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     mymax := _getreal (transform_norm_max,macro,2);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.norm.y',getstring(mymin)+' '+getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_norm_z (p1,macro : gtk_pointer); cdecl;
var mymin,mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
    _min,_max : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          _min := my^.min;
          _max := my^.max;
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.z := minmax (_min.z,_max.z,v.z,mymin,mymax);
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     mymax := _getreal (transform_norm_max,macro,2);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.norm.z',getstring(mymin)+' '+getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_norm_t (p1,macro : gtk_pointer); cdecl;
var mymin,mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
    _min,_max : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          _min := my^.min;
          _max := my^.max;
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.t := minmax (_min.t,_max.t,v.t,mymin,mymax);
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymin := _getreal (transform_norm_min,macro,1);
     mymax := _getreal (transform_norm_max,macro,2);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.norm.t',getstring(mymin)+' '+getstring(mymax));
     _cursor_arrow;
end;

{ ************************************* Max ********************************** }

procedure proc_transform_max_x (p1,macro : gtk_pointer); cdecl;
var mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.x := mymax;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymax := _getreal (transform_norm_max,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.max.x',getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_max_y (p1,macro : gtk_pointer); cdecl;
var mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.y := mymax;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymax := _getreal (transform_norm_max,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.max.y',getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_max_z (p1,macro : gtk_pointer); cdecl;
var mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.z := mymax;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymax := _getreal (transform_norm_max,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.max.z',getstring(mymax));
     _cursor_arrow;
end;

procedure proc_transform_max_t (p1,macro : gtk_pointer); cdecl;
var mymax : real;
procedure run (my : pcloud);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          for z := 1 to my^.getpointlength do
          begin
               v := my^.getpoint(z);
               v.t := mymax;
               my^.putpoint (z,v);
          end;
     end;
end;
begin
     _cursor_watch;
     mymax := _getreal (transform_norm_max,macro,1);
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.max.t',getstring(mymax));
     _cursor_arrow;
end;

{ ********************************* Effects ********************************** }

procedure proc_transform_shear (p1,macro : gtk_pointer); cdecl;
var e_center,e_direction : hyper;
    poly : tpolynom;
procedure run (my : pcloud);
var o,l,p : integer;
    u,v : hyper;
begin
     if my^.getobjectlength > 0 then
     begin
          dummy.clear;
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         begin
                              for p := 1 to my^.getlinepointlength(o,l) do
                              begin
                                   u := my^.getobject(o,l,p);
                                   v := u-e_center;
                                   if not inv (v,e_direction) then
                                   begin
                                        dummy.newpoint (u+poly.polynom(getlength(v)));
                                   end
                                   else dummy.newpoint (u);
                              end;
                              dummy.newline (my^.getmaterial (o,l));
                         end;
                    end;
               end;
          end;
          dummy.newobject ('shear');
          my^.replace (dummy);
     end;
end;
begin
     poly := Default(tpolynom);

     _cursor_watch;
     e_center  := _gethyper (transform_effects_center,macro,1);
     e_direction := _gethyper (transform_effects_direction,macro,2);
     poly.init (4);
     poly.put (1,_getreal (transform_c,macro,3));
     poly.put (2,_getreal (transform_x,macro,4));
     poly.put (3,_getreal (transform_x2,macro,5));
     poly.put (4,_getreal (transform_x3,macro,6));
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     dummy.clear;
     _update;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('transform.shear',getstring(e_center)+' '+getstring(e_direction)+' '+
                                        getstring(poly.get (1))+' '+getstring(poly.get(2))+' '+getstring(poly.get(3))+' '+getstring(poly.get(4)));
     poly.done;
     _cursor_arrow;
end;

procedure proc_transform_explode (p1,macro : gtk_pointer); cdecl;
var e_fallout_angle : real;
    e_center,e_direction : hyper;
    poly : tpolynom;
procedure run (my : pcloud);
var z,o,l,p : integer;
    list : tpolyhyper;
    v : hyper;
begin
     list := Default(tpolyhyper);

     if my^.getobjectlength > 0 then
     begin
          list.init (my^.getlinelength);
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         begin
                              z := 0;
                              for p := 1 to my^.getlinepointlength(o,l) do
                              begin
                                   list.put (l,my^.getobject(o,l,p)+list.get(l));
                                   inc (z);
                              end;
                              if z <> 0 then list.put (l,list.get(l)/z);
                         end;
                    end;
               end;
          end;
          dummy.clear;
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         begin
                              v := list.get(l)-e_center;
                              if getangle (gv(v.x,v.y,v.z),gv(e_direction.x,e_direction.y,e_direction.z)) <= e_fallout_angle then
                              begin
                                   for p := 1 to my^.getlinepointlength(o,l) do
                                   begin
                                        dummy.newpoint (my^.getobject(o,l,p)+((poly.polynom (getlength(v))*v)-v));
                                        my^.markpoint (o,l,p);
                                   end;
                                   dummy.newline (my^.getmaterial (o,l));
                              end;
                         end;
                    end;
               end;
          end;
          dummy.newobject ('explode');
          my^.erasemarked;
          my^.append (dummy);
          list.done;
     end;
end;
begin
     poly := Default(tpolynom);

     _cursor_watch;
     e_center  := _gethyper (transform_effects_center,macro,1);
     e_direction := _gethyper (transform_effects_direction,macro,2);
     if format.degree then e_fallout_angle := _getreal (transform_effects_fallout_angle,macro,3)/2*rad { input to radian }
                      else e_fallout_angle := _getreal (transform_effects_fallout_angle,macro,3)/2;
     poly.init (4);
     poly.put (1,_getreal (transform_c,macro,4));
     poly.put (2,_getreal (transform_x,macro,5));
     poly.put (3,_getreal (transform_x2,macro,6));
     poly.put (4,_getreal (transform_x3,macro,7));
     if state[1] then run (@red);
     _update;
     if state[2] then run (@green);
     _update;
     if state[3] then run (@blue);
     _update;
     if state[4] then run (@yellow);
     _update;
     if state[5] then run (@cyan);
     _update;
     if state[6] then run (@purple);
     dummy.clear;
     _update;
     calculating;
     updating;
     drawing;
     if format.degree then tmacro(macro^).writeredo ('transform.explode',getstring(e_center)+' '+getstring(e_direction)+' '+getstring(2*e_fallout_angle*deg)+' '+
                                                     getstring(poly.get (1))+' '+getstring(poly.get(2))+' '+getstring(poly.get(3))+' '+getstring(poly.get(4)))
                      else tmacro(macro^).writeredo ('transform.explode',getstring(e_center)+' '+getstring(e_direction)+' '+getstring(2*e_fallout_angle)+' '+
                                                     getstring(poly.get (1))+' '+getstring(poly.get(2))+' '+getstring(poly.get(3))+' '+getstring(poly.get(4)));;
     poly.done;
     _cursor_arrow;
end;
