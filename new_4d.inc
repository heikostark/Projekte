{ ************************** Hyper Field ************************************* }

procedure l_formula_point_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   finput^.newpoint (gh(xcounter,ycounter,zcounter,tcounter));
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_point_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.point.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                      getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                      getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                      getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends));
          _cursor_arrow;
     end;
end;

procedure l_formula_vector_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
    h,nvector : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          nvector := _gethyper (formula4_vector,macro,13);
          togglerandom := _getradiobutton (togglerandomvector4,macro,14);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   h := gh(xcounter,ycounter,zcounter,tcounter);
                                   finput^.newpoint (h);
                                   if togglerandom then finput^.newpoint (h+gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t))
                                                   else finput^.newpoint (h+nvector);
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_vector_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.vector.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                            getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                            getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                            getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.vector.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                            getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                            getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                            getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_normal_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
    h,nvector : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          nvector := _gethyper (formula4_vector,macro,13);
          togglerandom := _getradiobutton (togglerandomvector4,macro,14);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   h := gh(xcounter,ycounter,zcounter,tcounter);
                                   finput^.newpoint (h);
                                   if togglerandom then finput^.newpoint (h+norm(gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t)))
                                                   else finput^.newpoint (h+norm(nvector));
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_normal_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.normal.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                            getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                            getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                            getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.normal.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                            getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                            getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                            getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_sown_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep,o,l,p : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          dummy.clear;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                  if finput^.getobjectlength > 0 then
                                   begin
                                        for o := 1 to finput^.getobjectlength do
                                        begin
                                             if finput^.getobjectlinelength (o) > 0 then
                                             begin
                                                  for l := 1 to finput^.getobjectlinelength (o) do
                                                  begin
                                                       if finput^.getlinepointlength (o,l) > 0 then
                                                       begin
                                                            for p := 1 to finput^.getlinepointlength (o,l) do
                                                            begin
                                                                 dummy.newpoint (gh(xcounter,ycounter,zcounter,0)+finput^.getobject(o,l,p));
                                                            end;
                                                            dummy.newline (finput^.getmaterial (o,l)); { newline }
                                                       end;
                                                  end;
                                             end;
                                        end;
                                   end;
                                  tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_sown_hyperfield');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.sown.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                    getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                    getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                    getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends));

          _cursor_arrow;
     end;
end;

{ ************************** Random Hyper Field ****************************** }

procedure l_formula_random_point_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   finput^.newpoint (gh(xcounter+(random*(2*xfactor)-xfactor),ycounter+(random*(2*yfactor)-yfactor),zcounter+random*(2*zfactor)-zfactor,tcounter+random*(2*tfactor)-tfactor));
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_point_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.random.point.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                            getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                            getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                            getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends));
          _cursor_arrow;
     end;
end;

procedure l_formula_random_vector_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    togglerandom : boolean;
    lx,ly,lz,lt : integer;
    nvector,h : hyper;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          nvector := _gethyper (formula4_vector,macro,13);
          togglerandom := _getradiobutton (togglerandomvector4,macro,14);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   h := gh(xcounter+(random*(2*xfactor)-xfactor),ycounter+(random*(2*yfactor)-yfactor),zcounter+random*(2*zfactor)-zfactor,tcounter+random*(2*tfactor)-tfactor);
                                   finput^.newpoint (h);
                                   if togglerandom then finput^.newpoint (h+gh(((2*random-1)*nvector.x),((2*random-1)*nvector.y),((2*random-1)*nvector.z),((2*random-1)*nvector.t)))
                                                   else finput^.newpoint (h+nvector);
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_vector_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.random.vector.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                                   getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                                   getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                                   getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.random.vector.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                                   getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                                   getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                                   getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_random_normal_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
    nvector,h : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          nvector := _gethyper (formula4_vector,macro,13);
          togglerandom := _getradiobutton (togglerandomvector4,macro,14);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   h := gh((random*(2*xfactor)-xfactor),(random*(2*yfactor)-yfactor),random*(2*zfactor)-zfactor,random*(2*tfactor)-tfactor);
                                   finput^.newpoint (h);
                                   if togglerandom then finput^.newpoint (h+norm(gh(((2*random-1)*nvector.x),((2*random-1)*nvector.y),((2*random-1)*nvector.z),((2*random-1)*nvector.t))))
                                                   else finput^.newpoint (h+norm(nvector));
                                   finput^.newline (0); { newline }
                                   tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_normal_hyperfield');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.random.normal.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                                   getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                                   getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                                   getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.random.normal.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                                   getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                                   getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                                   getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_random_sown_hyperfield (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,tstep,o,l,p : integer;
    xfactor,yfactor,zfactor,tfactor,xcounter,ycounter,zcounter,tcounter : real;
    xsteps,ysteps,zsteps,tsteps,xbegins,ybegins,zbegins,tbegins,xends,yends,zends,tends : real;
    lx,ly,lz,lt : integer;
begin
     xsteps := _getreal (formula4_xstep,macro,2);
     ysteps := _getreal (formula4_ystep,macro,5);
     zsteps := _getreal (formula4_zstep,macro,8);
     tsteps := _getreal (formula4_tstep,macro,11);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) and (tsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula4_xbegin,macro,1);
          xends := _getreal (formula4_xend,macro,3);
          ybegins := _getreal (formula4_ybegin,macro,4);
          yends := _getreal (formula4_yend,macro,6);
          zbegins := _getreal (formula4_zbegin,macro,7);
          zends := _getreal (formula4_zend,macro,9);
          tbegins := _getreal (formula4_tbegin,macro,10);
          tends := _getreal (formula4_tend,macro,12);

          dummy.clear;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          tstep := round((tends-tbegins)/tsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) and (tstep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         zfactor := (zends-zbegins)/zstep;
                         zcounter := zbegins;
                         for lz := 1 to zstep+1 do
                         begin
                              tfactor := (tends-tbegins)/tstep;
                              tcounter := tbegins;
                              for lt := 1 to tstep+1 do
                              begin
                                   if finput^.getobjectlength > 0 then
                                   begin
                                        for o := 1 to finput^.getobjectlength do
                                        begin
                                             if finput^.getobjectlinelength (o) > 0 then
                                             begin
                                                  for l := 1 to finput^.getobjectlinelength (o) do
                                                  begin
                                                       if finput^.getlinepointlength (o,l) > 0 then
                                                       begin
                                                            for p := 1 to finput^.getlinepointlength (o,l) do
                                                            begin
                                                                 dummy.newpoint (gh(xcounter,ycounter,zcounter,0)+finput^.getobject(o,l,p));
                                                            end;
                                                            dummy.newline (finput^.getmaterial(o,l)); { newline }
                                                       end;
                                                  end;
                                             end;
                                        end;
                                   end;
                                  tcounter := tcounter + tfactor;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_random_sown_hyperfield');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.random.sown.hyperfield',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                           getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                           getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+
                                                           getstring(tbegins)+' '+getstring(tsteps)+' '+getstring(tends));
          _cursor_arrow;
     end;
end;
