{ ******************************** Spheroid ************************************ }

procedure l_formula_point_spheroid (p1,macro : gtk_pointer); cdecl;
var xcenter,ycenter,zcenter,xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
    nradius : real;
    function radius (u,v : vector) : real;
    begin
         radius := getlength(v-u);
    end;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          xcenter := round(xbegins+((xends-xbegins)/2));
          ycenter := round(ybegins+((yends-ybegins)/2));
          zcenter := round(zbegins+((zends-zbegins)/2));

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);

          nradius := max(max((xends-xbegins)/2,(yends-ybegins)/2),(zends-zbegins)/2);

          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              if radius (gv(xcenter,ycenter,zcenter),gv(xcounter,ycounter,zcounter)) <= nradius then
                              begin
                                   finput^.newpoint (gh(xcounter,ycounter,zcounter,0));
                                   finput^.newline (0); { newline }
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_point_sphere');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.point.sphere',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                 getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                 getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends));
          _cursor_arrow;
     end;
end;

{ ******************************** Ellipsoid ********************************* }

procedure l_formula_point_ellipsoid (p1,macro : gtk_pointer); cdecl;
var steps,begins,ends : vector;
    lx,ly,lz : integer;
    diameter,eradius,center,factor,counter,newradius : vector;
    sinangley,sinanglez : real;
    step : vectornat;
begin
     steps.x := _getreal (formula3_xstep,macro,2);
     steps.y := _getreal (formula3_ystep,macro,5);
     steps.z := _getreal (formula3_zstep,macro,8);
     if (steps.x > 0) and (steps.y > 0) and (steps.z > 0) then
     begin
          _cursor_watch;
          begins.x := _getreal (formula3_xbegin,macro,1);
          ends.x := _getreal (formula3_xend,macro,3);
          begins.y := _getreal (formula3_ybegin,macro,4);
          ends.y := _getreal (formula3_yend,macro,6);
          begins.z := _getreal (formula3_zbegin,macro,7);
          ends.z := _getreal (formula3_zend,macro,9);

          diameter := ends-begins;
          eradius := diameter/2;
          center := begins+eradius;

          step.x := round(eradius.x/steps.x);
          if (step.x > 0) then
          begin
               factor.x := eradius.x/step.x;
               counter.x := 0;
               for lx := 0 to step.x-1 do
               begin
                    sinangley := abs(sin(arccos (counter.x/eradius.x)));
                    newradius.y := (eradius.y*sinangley);
                    step.y := round(newradius.y/steps.y);
                    if (step.y > 0) then
                    begin
                         factor.y := newradius.y/step.y;
                         counter.y := 0;
                         for ly := 0 to step.y-1 do
                         begin
                              sinanglez := abs(sin(arccos (counter.y/newradius.y)));
                              newradius.z := (eradius.z*sinangley*sinanglez);
                              step.z := round(newradius.z/steps.z);
                              if (step.z > 0) then
                              begin
                                   factor.z := newradius.z/step.z;
                                   counter.z := 0;
                                   for lz := 0 to step.z-1 do
                                   begin
                                        if counter = Vzero then
                                        begin
                                             finput^.newpoint (gh(center,0));
                                             finput^.newline (0); { newline }
                                        end
                                        else
                                        begin
                                             finput^.newpoint (gh(center+counter,0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(1,1,-1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(1,-1,1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(1,-1,-1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(-1,1,1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(-1,1,-1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(-1,-1,1)*counter),0));
                                             finput^.newline (0); { newline }
                                             finput^.newpoint (gh(center+(gv(-1,-1,-1)*counter),0));
                                             finput^.newline (0); { newline }
                                        end;
                                        counter.z := counter.z + factor.z;
                                   end;
                              end
                              else counter.z := 0;
                              counter.y := counter.y + factor.y;
                         end;
                    end
                    else counter.y := 0;
                    counter.x := counter.x + factor.x;
               end;
               finput^.newobject ('new_point_ellipsoid');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.point.ellipsoid',getstring(begins.x)+' '+getstring(steps.x)+' '+getstring(ends.x)+' '+
                                                    getstring(begins.y)+' '+getstring(steps.y)+' '+getstring(ends.y)+' '+
                                                    getstring(begins.z)+' '+getstring(steps.z)+' '+getstring(ends.z));
          _cursor_arrow;
     end;
end;

{ ******************************** Field ************************************* }

procedure l_formula_point_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              finput^.newpoint (gh(xcounter,ycounter,zcounter,0));
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_point_field');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.point.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends));
          _cursor_arrow;
     end;
end;

procedure l_formula_vector_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
    h,nvector : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          nvector := _gethyper (formula3_vector,macro,10);
          togglerandom := _getradiobutton (togglerandomvector3,macro,11);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              h := gh(xcounter,ycounter,zcounter,0);
                              finput^.newpoint (h);
                              if _getradiobutton (togglerandomvector3) then finput^.newpoint (h+gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t))
                                                                       else finput^.newpoint (h+nvector);
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_vector_field');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.vector.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                       getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.vector.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                       getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_normal_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
    h,nvector : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          nvector := _gethyper (formula3_vector,macro,10);
          togglerandom := _getradiobutton (togglerandomvector3,macro,11);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              h := gh(xcounter,ycounter,zcounter,0);
                              finput^.newpoint (h);
                              if togglerandom then finput^.newpoint (h+norm(gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t)))
                                              else finput^.newpoint (h+norm(nvector));
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_normal_field');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                       getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                       getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_sown_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,o,l,p : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          dummy.clear;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_sown_field');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.sown.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                               getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                               getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends));
          _cursor_arrow;
     end;
end;

{ ***************************** Random Field ********************************* }

procedure l_formula_random_point_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              finput^.newpoint (gh(xcounter+(random*(2*xfactor)-xfactor),ycounter+(random*(2*yfactor)-yfactor),zcounter+random*(2*zfactor)-zfactor,0));
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_point_field');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.random.point.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                        getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                        getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends));
          _cursor_arrow;
     end;
end;

procedure l_formula_random_vector_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
    nvector,h : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          nvector := _gethyper (formula3_vector,macro,10);
          togglerandom := _getradiobutton (togglerandomvector3,macro,11);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              h := gh(xcounter+(random*(2*xfactor)-xfactor),ycounter+(random*(2*yfactor)-yfactor),zcounter+random*(2*zfactor)-zfactor,0);
                              finput^.newpoint (h);
                              if togglerandom then finput^.newpoint (h+gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t))
                                              else finput^.newpoint (h+nvector);
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_vector_field');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.random.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                              getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                              getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.random.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                              getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                              getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_random_normal_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep : integer;
    xfactor,yfactor,zfactor,xcounter,ycounter,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
    nvector,h : hyper;
    togglerandom : boolean;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          nvector := _gethyper (formula3_vector,macro,10);
          togglerandom := _getradiobutton (togglerandomvector3,macro,11);

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              h := gh(xcounter+(random*(2*xfactor)-xfactor),ycounter+(random*(2*yfactor)-yfactor),zcounter+random*(2*zfactor)-zfactor,0);
                              finput^.newpoint (h);
                              if togglerandom then finput^.newpoint (h+norm(gh((2*random-1)*nvector.x,(2*random-1)*nvector.y,(2*random-1)*nvector.z,(2*random-1)*nvector.t)))
                                              else finput^.newpoint (h+norm(nvector));
                              finput^.newline (0); { newline }
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_normal_field');
          end;
          calculating;
          updating;
          drawing;
          if togglerandom then
          begin
               tmacro(macro^).writeredo ('formula.random.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                              getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                              getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector)+' '+getstring(togglerandom));
          end
          else
          begin
               tmacro(macro^).writeredo ('formula.random.normal.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                              getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                              getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends)+' '+getstring(nvector));
          end;
          _cursor_arrow;
     end;
end;

procedure l_formula_random_sown_field (p1,macro : gtk_pointer); cdecl;
var xstep,ystep,zstep,o,l,p : integer;
    xfactor,yfactor,zfactor,xc,xcounter,yc,ycounter,zc,zcounter,xsteps,ysteps,zsteps,xbegins,ybegins,zbegins,xends,yends,zends :real;
    lx,ly,lz : integer;
begin
     xsteps := _getreal (formula3_xstep,macro,2);
     ysteps := _getreal (formula3_ystep,macro,5);
     zsteps := _getreal (formula3_zstep,macro,8);
     if (xsteps > 0) and (ysteps > 0) and (zsteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula3_xbegin,macro,1);
          xends := _getreal (formula3_xend,macro,3);
          ybegins := _getreal (formula3_ybegin,macro,4);
          yends := _getreal (formula3_yend,macro,6);
          zbegins := _getreal (formula3_zbegin,macro,7);
          zends := _getreal (formula3_zend,macro,9);

          dummy.clear;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          zstep := round((zends-zbegins)/zsteps);
          if (xstep > 0) and (ystep > 0) and (zstep > 0) then
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
                              xc := xcounter+(random*(2*xfactor)-xfactor);
                              yc := ycounter+(random*(2*yfactor)-yfactor);
                              zc := zcounter+(random*(2*zfactor)-zfactor);
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
                                                            dummy.newpoint (gh(xc,yc,zc,0)+finput^.getobject(o,l,p));
                                                       end;
                                                       dummy.newline (finput^.getmaterial (o,l)); { newline }
                                                  end;
                                             end;
                                        end;
                                   end;
                              end;
                              zcounter := zcounter + zfactor;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_random_sown_field');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.random.sown.field',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends)+' '+
                                                       getstring(zbegins)+' '+getstring(zsteps)+' '+getstring(zends));
          _cursor_arrow;
     end;
end;
