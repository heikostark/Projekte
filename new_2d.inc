{ *********************************** Plane ********************************** }

procedure l_formula_point_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xcounter,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_point_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.point.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                getstring(point)+' '+getstring(normal)+' '+
                                                getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_triangle_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xcounter,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
                    begin
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter)),0));
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newline (0); { newline }
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_triangle_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.triangle.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                   getstring(point)+' '+getstring(normal)+' '+
                                                   getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_square_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xcounter,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
                    begin
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter)),0));
                         finput^.newpoint (gh(a+(b*(xcounter+xfactor))+(c*(ycounter+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_square_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.square.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                 getstring(point)+' '+getstring(normal)+' '+
                                                 getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_sown_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xcounter,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly,o,l,p : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          dummy.clear;

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
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
                                                       dummy.newpoint (gh(a+(b*(xcounter))+(c*(ycounter)),0)+finput^.getobject(o,l,p));
                                                  end;
                                                  dummy.newline (finput^.getmaterial(o,l)); { newline }
                                             end;
                                        end;
                                   end;
                              end;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_sown_plane');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.sown.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                               getstring(point)+' '+getstring(normal)+' '+
                                               getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }

procedure l_formula_random_point_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xcounter,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep+1 do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep+1 do
                    begin
                         finput^.newpoint (gh(a+(b*(xcounter+(random*(2*xfactor)-xfactor)))+(c*(ycounter+(random*(2*yfactor)-yfactor))),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_point_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.random.point.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                       getstring(point)+' '+getstring(normal)+' '+
                                                       getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_random_triangle_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xc,xcounter,yc,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
                    begin
                         xc := xcounter+(random*(2*xfactor)-xfactor);
                         yc := ycounter+(random*(2*yfactor)-yfactor);
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc)),0));
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc)),0));
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc)),0));
                         finput^.newline (0); { newline }
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc)),0));
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc+yfactor)),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_triangle_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.random.triangle.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                          getstring(point)+' '+getstring(normal)+' '+
                                                          getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_random_square_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xc,xcounter,yc,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
                    begin
                         xc := xcounter+(random*(2*xfactor)-xfactor);
                         yc := ycounter+(random*(2*yfactor)-yfactor);
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc)),0));
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc)),0));
                         finput^.newpoint (gh(a+(b*(xc+xfactor))+(c*(yc+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc+yfactor)),0));
                         finput^.newpoint (gh(a+(b*(xc))+(c*(yc)),0));
                         finput^.newline (0); { newline }
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               finput^.newobject ('new_random_square_plane');
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('formula.random.square.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                        getstring(point)+' '+getstring(normal)+' '+
                                                        getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;

procedure l_formula_random_sown_plane (p1,macro : gtk_pointer); cdecl;
var xstep,ystep : integer;
    xfactor,yfactor,xc,xcounter,yc,ycounter,xsteps,ysteps,xbegins,ybegins,xends,yends :real;
    lx,ly,o,l,p : integer;
    a,b,c,point,normal : vector;
begin
     xsteps := _getreal (formula2_xstep,macro,2);
     ysteps := _getreal (formula2_ystep,macro,7);
     if (xsteps > 0) and (ysteps > 0) then
     begin
          _cursor_watch;
          xbegins := _getreal (formula2_xbegin,macro,1);
          xends := _getreal (formula2_xend,macro,3);
          ybegins := _getreal (formula2_ybegin,macro,6);
          yends := _getreal (formula2_yend,macro,8);
          point := _getvector (formula2_point,macro,4);
          normal := _getvector (formula2_normal,macro,5);

          dummy.clear;

          if norm(normal) = gv (1,0,0) then a := gv (0,1,0)
                                       else a := gv (1,0,0);
          b := norm(cross (normal,a));
          c := norm(cross (normal,b));
          a := point;

          xstep := round((xends-xbegins)/xsteps);
          ystep := round((yends-ybegins)/ysteps);
          if (xstep > 0) and (ystep > 0) then
          begin
               xfactor := (xends-xbegins)/xstep;
               xcounter := xbegins;
               for lx := 1 to xstep do
               begin
                    yfactor := (yends-ybegins)/ystep;
                    ycounter := ybegins;
                    for ly := 1 to ystep do
                    begin
                         xc := xcounter+(random*(2*xfactor)-xfactor);
                         yc := ycounter+(random*(2*yfactor)-yfactor);
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
                                                       dummy.newpoint (gh(a+(b*(xc))+(c*(yc)),0)+finput^.getobject(o,l,p));
                                                  end;
                                                  dummy.newline (finput^.getmaterial(o,l)); { newline }
                                             end;
                                        end;
                                   end;
                              end;
                         end;
                         ycounter := ycounter + yfactor;
                    end;
                    xcounter := xcounter + xfactor;
               end;
               dummy.newobject ('new_random_sown_plane');
          end;
          cleanup (dummy);
          tmacro(macro^).writeredo ('formula.random.sown.plane',getstring(xbegins)+' '+getstring(xsteps)+' '+getstring(xends)+' '+
                                                      getstring(point)+' '+getstring(normal)+' '+
                                                      getstring(ybegins)+' '+getstring(ysteps)+' '+getstring(yends));
          _cursor_arrow;
     end;
end;
