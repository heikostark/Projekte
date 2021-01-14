{ **************************************************************************** }
{ *********************************** show ********************************* }
{ **************************************************************************** }

const format_pov : Tformat = (
             scientific_notation : false; {true: 1E3 false: 1000 – simpler }
             decimal_separator : true; {true: 1.234 (en) false: 1,234 (other)}
             digit_grouping : false; {true: 1,000,000 or 1.000.000 false: 1000000 – simpler}
             leading_zero : 0; { (1  0.1) or (01 00.1) or 001 or 0001 }
             trailing_zero : 0; { 1.000 or 1.00 or 1.0 or 1 }
             vector : false; {true: <1, 1, 1> false: 1, 1, 1}
             matrix : false; {true: [...]  false: ...}
      );

var p_o_show : utf16chars;

{ **************************************************************************** }

var sizemap : tpolyreal;
    colormap : tpolyhyper;

procedure initmap (n : integer);
var s : tpolycomplex;
    t : tpolyhyper;
    q,l,p,r : integer;
    a,b : complex;
    u,v : hyper;
    steps : integer;
begin
     s := Default(tpolycomplex);
     t := Default(tpolyhyper);

     steps := limit (n,1,99999);
     sizemap.init (steps);
     colormap.init (steps);

     s.init (6);
     s.put (1,gc(_getreal(editredmap),_getreal(editredradius)));
     s.put (2,gc(_getreal(editgreenmap),_getreal(editgreenradius)));
     s.put (3,gc(_getreal(editbluemap),_getreal(editblueradius)));
     s.put (4,gc(_getreal(edityellowmap),_getreal(edityellowradius)));
     s.put (5,gc(_getreal(editcyanmap),_getreal(editcyanradius)));
     s.put (6,gc(_getreal(editpurplemap),_getreal(editpurpleradius)));
     s.sortx;
     p := 0;
     for q := 1 to 6 do if into(s.get(q).x,0,1) then inc (p);
     if steps < p then
     begin
          steps := p;
          writeln ('Attention, to less steps!');
     end;
     for q := 1 to 5 do
     begin
          a := s.get (q);
          if q < 6 then b := s.get(q+1) else b.x := -1;
          if into (a.x,0,1) and into (b.x,0,1) then
          begin
               u.x := a.y;
               v.x := b.y;
               p := round(a.x*(steps-1))+1; { position }
               l := round((b.x-a.x)*(steps-1)); { length }
               for r := 0 to l do sizemap.put (p+r,u.x*(1-r/l)+v.x*(r/l));
          end
          else if into (a.x,0,1) then
          begin
               u.x := a.y;
               p := round(a.x*(steps-1))+1; { position }
               if (steps-p) >= 0 then
               begin
                    for r := 0 to (steps-p) do sizemap.put (p+r,u.x);
               end;
          end;
     end;
     s.done;

     s.init (6);
     t.init (6);
     s.put (1,gc(_getreal(editredmap),1)); t.put (1,_getcolort(editred)/$FFFF);
     s.put (2,gc(_getreal(editgreenmap),2)); t.put (2,_getcolort(editgreen)/$FFFF);
     s.put (3,gc(_getreal(editbluemap),3)); t.put (3,_getcolort(editblue)/$FFFF);
     s.put (4,gc(_getreal(edityellowmap),4)); t.put (4,_getcolort(edityellow)/$FFFF);
     s.put (5,gc(_getreal(editcyanmap),5)); t.put (5,_getcolort(editcyan)/$FFFF);
     s.put (6,gc(_getreal(editpurplemap),6)); t.put (6,_getcolort(editpurple)/$FFFF);
     s.sortx;
     for q := 1 to 6 do
     begin
          a := s.get(q);
          if q < 6 then b := s.get(q+1) else b.x := -1;
          if into (a.x,0,1) and into (b.x,0,1) then
          begin
               u := t.get(round(a.y));
               v := t.get(round(b.y));
               p := round(a.x*(steps-1))+1; { position }
               l := round((b.x-a.x)*(steps-1)); { length }
               for r := 0 to l do
               begin
                    colormap.put (p+r,u*(1-r/l)+v*(r/l));
               end;
          end
          else if into (a.x,0,1) then
          begin
               u := t.get(round(a.y));
               p := round(a.x*(steps-1))+1; { position }
               if (steps-p) >= 0 then
               begin
                    for r := 0 to (steps-p) do
                    begin
                         colormap.put (p+r,u);
                    end;
               end;
          end;
     end;
     t.done;
     s.done;
{$ifdef debug}
     for q := 1 to steps do writeln (getstring(sizemap.get(q)));
     writeln;
     for q := 1 to steps do writeln (getstring(colormap.get(q)));
{$endif}
end;

procedure donemap;
begin
     sizemap.done;
     colormap.done;
end;

function getsizemap (min,max,t : real) : real;
var n : integer;
begin
     if min < max then
     begin
          n := trunc(minmax (min,max,t,1,sizemap.length));
          getsizemap := sizemap.get (n);
     end
     else getsizemap := 0;
end;

function getcolormap (min,max,t : real) : hyper;
var n : integer;
begin
     if min < max then
     begin
          n := trunc(minmax (min,max,t,1,colormap.length));
          getcolormap := colormap.get (n);
     end
     else getcolormap := Hzero;
end;

{ ********************************* Addons *********************************** }

procedure proc_show_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (show_povray_min,getstring(minall));
     _setedit (show_povray_max,getstring(maxall));
end;

procedure proc_show_set_dimension_min (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (show_povray_min,getstring(minall));
end;

procedure proc_show_set_dimension_max (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (show_povray_max,getstring(maxall));
end;

procedure addons (const name: utf16);
var pov : twritepov;
    glob,s,t : utf16;
    radius : real;
    xc,yc,zc,x,y,z : integer;
    v,u,axismin,axismax : vector;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     if name <> '' then
     begin
          case _getitem (show_povray_camera) of
               0 : s := 'front';
               1 : s := 'back';
               2 : s := 'left';
               3 : s := 'right';
               4 : s := 'down';
               5 : s := 'up';
               6 : s := 'aroundx';
               7 : s := 'aroundy';
               8 : s := 'aroundz';
               9 : s := 'plus';
               10 : s := 'minus';
               else s := '?';
          end;
          if pov.save (name+'.pov') then
          begin
               if _getradiobutton (togglecamera1) then pov.camera(s,gv(centerall.x,centerall.y,centerall.z),getlength(1.5*maxall-centerall));
               if _getradiobutton (togglecamera2) then pov.cameras(s,gv(centerall.x,centerall.y,centerall.z),getlength(1.5*maxall-centerall));
               if _getradiobutton (togglecamera3) then pov.orthocameras(s,gv(centerall.x,centerall.y,centerall.z),getlength(1.1*maxall-minall));

               if _getcheckbutton (togglesky1) then pov.sky(_getcolor (editsky1)/$FFFF);
               case _getitem (show_povray_sky) of
                    0 : v := gv (1,0,0);
                    1 : v := gv (0,1,0);
                    else v := gv (0,0,1);
               end;
               if _getcheckbutton (togglesky2) then pov.sky(v,_getcolor (editsky1)/$FFFF,_getcolor (editsky2)/$FFFF);

               if _getradiobutton (togglepointlights) then pov.write(pov.pointlights(gv(centerall.x,centerall.y,centerall.z),getlength(3*maxall-centerall),pov.rgb(_getcolor (editlight)/$FFFF)));
               if _getradiobutton (togglespotlights) then pov.write(pov.spotlights(gv(centerall.x,centerall.y,centerall.z),getlength(3*maxall-centerall),pov.rgb(_getcolor (editlight)/$FFFF)));
               if _getradiobutton (togglepointlight) then pov.pointlight(s,gv(centerall.x,centerall.y,centerall.z),getlength(3*maxall-centerall),pov.rgb(_getcolor (editlight)/$FFFF));
               if _getradiobutton (togglespotlight) then pov.spotlight(s,gv(centerall.x,centerall.y,centerall.z),getlength(3*maxall-centerall),pov.rgb(_getcolor (editlight)/$FFFF));
               if _getradiobutton (togglearealights) then pov.arealight(s,gv(centerall.x,centerall.y,centerall.z),getlength(3*maxall-centerall),pov.rgb(_getcolor (editlight)/$FFFF));

               axismin := _getvector (show_povray_min);
               axismax := _getvector (show_povray_max);
{ Axis }
               if _getcheckbutton (toggleaxis) then
               begin
                    glob := '';
                    radius := getlength(axismax-axismin)/100/10;
                    glob := glob + pov.sphere (Vzero,radius,'');
                    if _getcheckbutton (toggleaxisx) and (axismin.x < 0) then glob := glob + pov.cylinder (Vzero,gv(axismin.x-10*radius,0,0),radius,'');
                    if _getcheckbutton (toggleaxisx) and (axismax.x > 0) then
                    begin
                         glob := glob + pov.cylinder (Vzero,gv(axismax.x,0,0),radius,'');
                         glob := glob + pov.cone (gv(axismax.x+10*radius,0,0),gv(axismax.x,0,0),4*radius,'');
                    end;
                    if _getcheckbutton (toggleaxisy) and (axismin.y < 0) then glob := glob + pov.cylinder (Vzero,gv(0,axismin.y-10*radius,0),radius,'');
                    if _getcheckbutton (toggleaxisy) and (axismax.y > 0) then
                    begin
                         glob := glob + pov.cylinder (Vzero,gv(0,axismax.y,0),radius,'');
                         glob := glob + pov.cone (gv(0,axismax.y+10*radius,0),gv(0,axismax.y,0),4*radius,'');
                    end;
                    if _getcheckbutton (toggleaxisz) and (axismin.z < 0) then glob := glob + pov.cylinder (Vzero,gv(0,0,axismin.z-10*radius),radius,'');
                    if _getcheckbutton (toggleaxisz) and (axismax.z > 0) then
                    begin
                         glob := glob + pov.cylinder (Vzero,gv(0,0,axismax.z),radius,'');
                         glob := glob + pov.cone (gv(0,0,axismax.z+10*radius),gv(0,0,axismax.z),4*radius,'');
                    end;
                    pov.write (pov.union(glob+pov.pigment(_getcolort(editaxis)/$FFFF)));
               end;
{ Axis ticks }
               if _getcheckbutton (toggleaxis) and _getcheckbutton (toggleticks) then
               begin
                    glob := '';
                    radius := getlength(axismax-axismin)/100/10;
                    v := _getvector (show_povray_ticks);
                    u := _getvector (show_povray_ticks_size);

                    if _getcheckbutton (toggleaxisx) and (axismin.x < 0) then
                    begin
                         x := trunc(axismin.x/v.x);
                         if x < 0 then
                         begin
                              if _getcheckbutton (toggleaxisy) then for xc := x to -1 do glob := glob + pov.cylinder (gv(xc*v.x,-1*u.y,0),gv(xc*v.x,u.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for xc := x to -1 do glob := glob + pov.cylinder (gv(xc*v.x,0,-1*u.z),gv(xc*v.x,0,u.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisx) and (axismax.x > 0) then
                    begin
                         x := trunc(axismax.x/v.x);
                         if x > 0 then
                         begin
                              if _getcheckbutton (toggleaxisy) then for xc := 1 to x do glob := glob + pov.cylinder (gv(xc*v.x,-1*u.y,0),gv(xc*v.x,u.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for xc := 1 to x do glob := glob + pov.cylinder (gv(xc*v.x,0,-1*u.z),gv(xc*v.x,0,u.z),radius,'');
                         end;
                    end;

                    if _getcheckbutton (toggleaxisy) and (axismin.y < 0) then
                    begin
                         y := trunc(axismin.y/v.y);
                         if y < 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for yc := y to -1 do glob := glob + pov.cylinder (gv(-1*u.x,yc*v.y,0),gv(u.x,yc*v.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for yc := y to -1 do glob := glob + pov.cylinder (gv(0,yc*v.y,-1*u.z),gv(0,yc*v.y,u.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisy) and (axismax.y > 0) then
                    begin
                         y := trunc(axismax.y/v.y);
                         if y > 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for yc := 1 to y do glob := glob + pov.cylinder (gv(-1*u.x,yc*v.y,0),gv(u.x,yc*v.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for yc := 1 to y do glob := glob + pov.cylinder (gv(0,yc*v.y,-1*u.z),gv(0,yc*v.y,u.z),radius,'');
                         end;
                    end;

                    if _getcheckbutton (toggleaxisz) and (axismin.z < 0) then
                    begin
                         z := trunc(axismin.z/v.z);
                         if z < 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for zc := z to -1 do glob := glob + pov.cylinder (gv(-1*u.x,0,zc*v.z),gv(u.x,0,zc*v.z),radius,'');
                              if _getcheckbutton (toggleaxisy) then for zc := z to -1 do glob := glob + pov.cylinder (gv(0,-1*u.y,zc*v.z),gv(0,u.y,zc*v.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisz) and (axismax.z > 0) then
                    begin
                         z := trunc(axismax.z/v.z);
                         if z > 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for zc := 1 to z do glob := glob + pov.cylinder (gv(-1*u.x,0,zc*v.z),gv(u.x,0,zc*v.z),radius,'');
                              if _getcheckbutton (toggleaxisy) then for zc := 1 to z do glob := glob + pov.cylinder (gv(0,-1*u.y,zc*v.z),gv(0,u.y,zc*v.z),radius,'');
                         end;
                    end;

                    pov.write (pov.union(glob+pov.pigment(_getcolort(editticks)/$FFFF)));
               end;
{ Raster }
               if _getcheckbutton (toggleraster) then
               begin
                    glob := '';
                    radius := getlength(axismax-axismin)/100/10;
                    v := _getvector (show_povray_raster);

                    if _getcheckbutton (toggleaxisx) and (axismin.x < 0) then
                    begin
                         x := trunc(axismin.x/v.x);
                         if x < 0 then
                         begin
                              if _getcheckbutton (toggleaxisy) then for xc := x to -1 do glob := glob + pov.cylinder (gv(xc*v.x,axismin.y,0),gv(xc*v.x,axismax.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for xc := x to -1 do glob := glob + pov.cylinder (gv(xc*v.x,0,axismin.z),gv(xc*v.x,0,axismax.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisx) and (axismax.x > 0) then
                    begin
                         x := trunc(axismax.x/v.x);
                         if x > 0 then
                         begin
                              if _getcheckbutton (toggleaxisy) then for xc := 1 to x do glob := glob + pov.cylinder (gv(xc*v.x,axismin.y,0),gv(xc*v.x,axismax.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for xc := 1 to x do glob := glob + pov.cylinder (gv(xc*v.x,0,axismin.z),gv(xc*v.x,0,axismax.z),radius,'');
                         end;
                    end;

                    if _getcheckbutton (toggleaxisy) and (axismin.y < 0) then
                    begin
                         y := trunc(axismin.y/v.y);
                         if y < 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for yc := y to -1 do glob := glob + pov.cylinder (gv(axismin.x,yc*v.y,0),gv(axismax.x,yc*v.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for yc := y to -1 do glob := glob + pov.cylinder (gv(0,yc*v.y,axismin.z),gv(0,yc*v.y,axismax.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisy) and (axismax.y > 0) then
                    begin
                         y := trunc(axismax.y/v.y);
                         if y > 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for yc := 1 to y do glob := glob + pov.cylinder (gv(axismin.x,yc*v.y,0),gv(axismax.x,yc*v.y,0),radius,'');
                              if _getcheckbutton (toggleaxisz) then for yc := 1 to y do glob := glob + pov.cylinder (gv(0,yc*v.y,axismin.z),gv(0,yc*v.y,axismax.z),radius,'');
                         end;
                    end;

                    if _getcheckbutton (toggleaxisz) and (axismin.z < 0) then
                    begin
                         z := trunc(axismin.z/v.z);
                         if z < 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for zc := z to -1 do glob := glob + pov.cylinder (gv(axismin.x,0,zc*v.z),gv(axismax.x,0,zc*v.z),radius,'');
                              if _getcheckbutton (toggleaxisy) then for zc := z to -1 do glob := glob + pov.cylinder (gv(0,axismin.y,zc*v.z),gv(0,axismax.y,zc*v.z),radius,'');
                         end;
                    end;
                    if _getcheckbutton (toggleaxisz) and (axismax.z > 0) then
                    begin
                         z := trunc(axismax.z/v.z);
                         if z > 0 then
                         begin
                              if _getcheckbutton (toggleaxisx) then for zc := 1 to z do glob := glob + pov.cylinder (gv(axismin.x,0,zc*v.z),gv(axismax.x,0,zc*v.z),radius,'');
                              if _getcheckbutton (toggleaxisy) then for zc := 1 to z do glob := glob + pov.cylinder (gv(0,axismin.y,zc*v.z),gv(0,axismax.y,zc*v.z),radius,'');
                         end;
                    end;

                    pov.write (pov.union(glob+pov.pigment(_getcolort(editraster)/$FFFF)));
               end;

               if lowercase(getfileextension (name)) <> 'inc' then t := name + '.inc'
                                                              else t := name;
               pov.include(getfile (t));  { Scene }

               pov.done;
          end;
     end;
end;

{ ******************************** Sphere ************************************ }

procedure p_o_spheres;
var pov : twritepov;
procedure run (f : pcloud;radius : real;color : hyper);
var x : integer;
begin
     if f^.getpointlength > 0 then
     begin
          case _getitem (show_povray_group) of
               1 : pov.merge;
               2 : pov.difference;
               3 : pov.intersection;
               4 : pov.blob (_getnat(show_povray_threshold));
               { 0 and } else pov.union;
          end;

          case _getitem (show_povray_group) of
               4 :
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         pov.write (pov.sphere (f^.getpoint(x),radius,1,'')); { strength 1 for blobs }
                    end;
               end;
               else { 0,1,2,3 and else }
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         pov.write (pov.sphere (f^.getpoint(x),radius,''));
                    end;
               end;
          end;

          if color.t = 1 then pov.ende (pov.pigment(gv(color.x,color.y,color.z)))
                         else pov.ende (pov.pigment(color));
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres);
end;

{ **************************************************************************** }

procedure p_o_spheres_mat;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var o,l,p : integer;
    color : vector;
begin
     glob := '';
     if f^.getobjectlength > 0 then
     begin
          for o := 1 to f^.getobjectlength do
          begin
               if f^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to f^.getobjectlinelength (o) do
                    begin
                         color := hex2rgb (f^.getmaterial(o,l)) / $FF;
                         if f^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to f^.getlinepointlength (o,l) do
                              begin
                                   case _getitem (show_povray_group) of
                                        4 : glob := glob + pov.sphere (f^.getobject(o,l,p),f^.getobject(o,l,p).t,1,pov.pigment(color)); { strength 1 for blobs }
                                        { 0,1,2,3 and else } else glob := glob + pov.sphere (f^.getobject(o,l,p),f^.getobject(o,l,p).t,pov.pigment(color));
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
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
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_mat (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_mat);
end;

procedure p_o_spheres_obj;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var o,l,p : integer;
    color : vector;
    s : utf16;
begin
     glob := '';
     if f^.getobjectlength > 0 then
     begin
          for o := 1 to f^.getobjectlength do
          begin
               s := f^.getname(o);
               if pos ('$',s) > 0 then
               begin
                    color := hex2rgb (gethex (copy(s,pos('$',s)+1,6))) / $FF;
               end
               else color := gv (1,1,1);
               if f^.getobjectlinelength (o) > 0 then
               begin
                    for l := 1 to f^.getobjectlinelength (o) do
                    begin
                         if f^.getlinepointlength (o,l) > 0 then
                         begin
                              for p := 1 to f^.getlinepointlength (o,l) do
                              begin
                                   case _getitem (show_povray_group) of
                                        4 : glob := glob + pov.sphere (f^.getobject(o,l,p),f^.getobject(o,l,p).t,1,pov.pigment(color)); { strength 1 for blobs }
                                        { 0,1,2,3 and else } else glob := glob + pov.sphere (f^.getobject(o,l,p),f^.getobject(o,l,p).t,pov.pigment(color));
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
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
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_obj (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_obj);
end;

{ **************************************************************************** }

procedure p_o_spheres_t;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;color : hyper);
var x : integer;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          case _getitem (show_povray_group) of
               4 :
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).t,1,''); { strength 1 for blobs }
                    end;
               end;
               else { 0,1,2,3 and else }
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).t,'');
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 :
               begin
                    if color.t = 1 then pov.write (pov.merge(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.merge(glob+pov.pigment(color)));
               end;
               2 :
               begin
                    if color.t = 1 then pov.write (pov.difference(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.difference(glob+pov.pigment(color)));
               end;
               3 :
               begin
                    if color.t = 1 then pov.write (pov.intersection(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.intersection(glob+pov.pigment(color)));
               end;
               4 : { blob }
               begin
                    if color.t = 1 then pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(color)));
               end;
               { 0 and } else { union }
               begin
                    if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.union(glob+pov.pigment(color)));
               end;
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_t (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_t);
end;

procedure p_o_spheres_z;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;color : hyper);
var x : integer;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          case _getitem (show_povray_group) of
               4 :
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).z,1,''); { strength 1 for blobs }
                    end;
               end;
               else { 0,1,2,3 and else }
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).z,'');
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 :
               begin
                    if color.t = 1 then pov.write (pov.merge(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.merge(glob+pov.pigment(color)));
               end;
               2 :
               begin
                    if color.t = 1 then pov.write (pov.difference(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.difference(glob+pov.pigment(color)));
               end;
               3 :
               begin
                    if color.t = 1 then pov.write (pov.intersection(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.intersection(glob+pov.pigment(color)));
               end;
               4 : { blob }
               begin
                    if color.t = 1 then pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(color)));
               end;
               { 0 and } else { union }
               begin
                    if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.union(glob+pov.pigment(color)));
               end;
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_z (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_z);
end;

procedure p_o_spheres_y;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;color : hyper);
var x : integer;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          case _getitem (show_povray_group) of
               4 :
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).y,1,''); { strength 1 for blobs }
                    end;
               end;
               else { 0,1,2,3 and else }
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).y,'');
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 :
               begin
                    if color.t = 1 then pov.write (pov.merge(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.merge(glob+pov.pigment(color)));
               end;
               2 :
               begin
                    if color.t = 1 then pov.write (pov.difference(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.difference(glob+pov.pigment(color)));
               end;
               3 :
               begin
                    if color.t = 1 then pov.write (pov.intersection(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.intersection(glob+pov.pigment(color)));
               end;
               4 : { blob }
               begin
                    if color.t = 1 then pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(color)));
               end;
               { 0 and } else { union }
               begin
                    if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.union(glob+pov.pigment(color)));
               end;
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_y (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_y);
end;

procedure p_o_spheres_x;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;color : hyper);
var x : integer;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          case _getitem (show_povray_group) of
               4 :
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).x,1,''); { strength 1 for blobs }
                    end;
               end;
               else { 0,1,2,3 and else }
               begin
                    for x := 1 to f^.getpointlength do
                    begin
                         glob := glob + pov.sphere (f^.getpoint(x),f^.getpoint(x).x,'');
                    end;
               end;
          end;
          case _getitem (show_povray_group) of
               1 :
               begin
                    if color.t = 1 then pov.write (pov.merge(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.merge(glob+pov.pigment(color)));
               end;
               2 :
               begin
                    if color.t = 1 then pov.write (pov.difference(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.difference(glob+pov.pigment(color)));
               end;
               3 :
               begin
                    if color.t = 1 then pov.write (pov.intersection(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.intersection(glob+pov.pigment(color)));
               end;
               4 : { blob }
               begin
                    if color.t = 1 then pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.blob(_getnat(show_povray_threshold),glob+pov.pigment(color)));
               end;
               { 0 and } else { union }
               begin
                    if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                                   else pov.write (pov.union(glob+pov.pigment(color)));
               end;
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format.decimal_separator := true;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_spheres_x (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_spheres_x);
end;

{ ************************* Color Sphere ************************************* }

procedure p_o_color_spheres;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;size : real);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,size,1,pov.pigment(getcolormap(min.t,max.t,v.t))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,size,pov.pigment(getcolormap(min.t,max.t,v.t)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
          if state[1] then run (@red,_getreal(editredradius));
          _update;
          if state[2] then run (@green,_getreal(editgreenradius));
          _update;
          if state[3] then run (@blue,_getreal(editblueradius));
         _update;
          if state[4] then run (@yellow,_getreal(edityellowradius));
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius));
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius));
           donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_spheres (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_color_spheres);
end;

{ ******************************** Size Sphere ******************************* }

procedure p_o_size_spheres;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;color : hyper);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,getsizemap (min.t,max.t,v.t),1,pov.pigment(gv(color.x,color.y,color.z))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(gv(color.x,color.y,color.z)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_size_spheres (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_size_spheres);
end;

{ ******************************** Both Sphere ******************************* }

procedure p_o_both_spheres;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,getsizemap (min.t,max.t,v.t),1,pov.pigment(getcolormap(min.t,max.t,v.t))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(getcolormap(min.t,max.t,v.t)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_both_spheres (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_both_spheres);
end;

{ ********************************* Sphere Axis ****************************** }

procedure p_o_color_spheres_t;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,v.t,1,pov.pigment(getcolormap(min.t,max.t,v.t))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,v.t,pov.pigment(getcolormap(min.t,max.t,v.t)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_spheres_t (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-shperes','pov','Povray-files:*.pov|All files:*.*',@p_o_color_spheres_t);
end;

procedure p_o_color_spheres_z;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,v.z,1,pov.pigment(getcolormap(min.z,max.z,v.z))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,v.z,pov.pigment(getcolormap(min.z,max.z,v.z)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_spheres_z (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_color_spheres_z);
end;

procedure p_o_color_spheres_y;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,v.y,1,pov.pigment(getcolormap(min.y,max.y,v.y))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,v.y,pov.pigment(getcolormap(min.y,max.y,v.y)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_spheres_y (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_color_spheres_y);
end;

procedure p_o_color_spheres_x;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud);
var x : integer;
    v : hyper;
    min,max : hyper;
begin
     glob := '';
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for x := 1 to f^.getpointlength do
          begin
               v := f^.getpoint(x);
               case _getitem (show_povray_group) of
                    4 : glob := glob + pov.sphere (v,v.x,1,pov.pigment(getcolormap(min.x,max.x,v.x))); { strength 1 for blobs }
                    { 0,1,2,3 and else } else glob := glob + pov.sphere (v,v.x,pov.pigment(getcolormap(min.x,max.x,v.x)));
               end;
          end;
          case _getitem (show_povray_group) of
               1 : pov.write (pov.merge(glob));
               2 : pov.write (pov.difference(glob));
               3 : pov.write (pov.intersection(glob));
               4 : { blob } pov.write (pov.blob(_getnat(show_povray_threshold),glob));
               { 0 and } else { union } pov.write (pov.union(glob));
          end;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_spheres_x (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-spheres';
     _savefile (p_o_show,'new-spheres','pov','Povray-files:*.pov|All files:*.*',@p_o_color_spheres_x);
end;

{ **************************************************************************** }
{ ******************************** Vectors *********************************** }
{ **************************************************************************** }

procedure p_o_vectors;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;radius : real;color : hyper);
var z,bl,l : integer;
    v,u,d,d1,d4 : hyper;
    subglob : utf16;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         u := f^.getline (z,bl+1);
                         d := u-v;
                         d1 := norm(d)*radius;
                         d4 := 4*d1;
                         if d <> Hzero then
                         begin
                              if d > d4 then
                              begin
                                   subglob := subglob + pov.cylinder (v,u-d4,radius,'');
                                   subglob := subglob + pov.cylinder (u-d4,u,2*radius,0,'');
                              end
                              else
                              begin
                                   subglob := subglob + pov.cylinder (v,u,(2*radius)*(getlength(d)/getlength(d4)),0,'');
                              end;
                         end;
                    end;
                    if color.t = 1 then glob := glob + subglob
                                   else glob := glob + pov.merge (subglob);
               end
               else if l = 1 then glob := glob + pov.sphere (f^.getline (z,1),radius,'');
          end;
          if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                         else pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_vectors (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-vectors';
     _savefile (p_o_show,'new-vectors','pov','Povray-files:*.pov|All files:*.*',@p_o_vectors);
end;

{ ********************************* Arrows *********************************** }

procedure p_o_arrows;
var pov : twritepov;
    glob : utf16;
procedure run (f : pcloud;radius : real;color : hyper);
var z,bl,l : integer;
    v,u,d,dh2,d1,d4,d8 : hyper;
    subglob : utf16;
begin
     glob := '';
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         u := f^.getline (z,bl+1);
                         d := u-v;
                         dh2 := (v+u)/2;
                         d1 := norm(d)*radius;
                         d4 := 4*d1;
                         d8 := 8*d1;
                         if d <> Hzero then
                         begin
                              if d > d8 then
                              begin
                                   subglob := subglob + pov.cylinder (dh2-d4,dh2+d4,2*radius,0,'');
                              end
                              else
                              begin
                                   subglob := subglob + pov.cylinder (v,u,(2*radius)*(getlength(d)/getlength(d8)),0,'');
                              end;
                         end;
                    end;
                    if color.t = 1 then glob := glob + subglob
                                   else glob := glob + pov.merge (subglob);
               end
               else if l = 1 then glob := glob + pov.sphere (f^.getline(z,1),radius,'');
          end;
         if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                        else pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_arrows (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-arrows';
     _savefile (p_o_show,'new-arrows','pov','Povray-files:*.pov|All files:*.*',@p_o_arrows);
end;

{ ******************************** Lines ************************************ }

procedure p_o_lines;
var pov : twritepov;
procedure run (f : pcloud;radius : real;color : hyper);
var z,bl,l : integer;
    v : hyper;
    subglob : utf16;
begin
     if f^.getpointlength > 0 then
     begin
          pov.union;
          for z := 1 to f^.getlinelength do
          begin
               progress  ('  Write Lines.',z/f^.getlinelength);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         subglob := subglob + pov.sphere (v,radius,'');
                         subglob := subglob + pov.cylinder (v,f^.getline(z,bl+1),radius,'');
                    end;
                    subglob := subglob + pov.sphere (f^.getline(z,l),radius,'');
                    if color.t = 1 then pov.write(subglob)
                                   else pov.write(pov.merge (subglob));
               end
               else if l = 1 then pov.write(pov.sphere (f^.getline(z,1),radius,''));
          end;
          progress;
          if color.t = 1 then pov.write (pov.pigment(gv(color.x,color.y,color.z)))
                         else pov.write (pov.pigment(color));
          pov.ende;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_lines (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-lines';
     _savefile (p_o_show,'new-lines','pov','Povray-files:*.pov|All files:*.*',@p_o_lines);
end;

{ ************************** Color Lines ************************************* }

procedure p_o_color_lines;
var pov : twritepov;
    mel : twritemaya;
procedure run_pov (f : pcloud;radius : real);
var z,bl,l : integer;
    v : hyper;
    min,max : hyper;
    subglob : utf16;
begin
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          pov.union;
          for z := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',z/f^.getlinelength);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         subglob := subglob + pov.sphere (v,radius,pov.pigment(getcolormap(min.t,max.t,v.t)));
                         subglob := subglob + pov.cylinder (v,f^.getline(z,bl+1),radius,pov.pigment(getcolormap(min.t,max.t,v.t)));
                    end;
                    subglob := subglob + pov.sphere (f^.getline(z,l),radius,pov.pigment(getcolormap(min.t,max.t,f^.getline(z,l).t)));
                    pov.write(pov.union (subglob));
               end
               else if l = 1 then pov.write(pov.sphere (f^.getline(z,1),radius,pov.pigment(getcolormap(min.t,max.t,f^.getline(z,1).t))));
          end;
          progress;
          pov.ende;
     end;
end;
procedure run_uvel (f : pcloud;radius : real);
var l,p,len : integer;
    h : hyper;
    v,u : vector;
    min,max : hyper;
begin
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    mel.comment ('Begin of line.');
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    for p := 1 to len-1 do
                    begin
                         h := f^.getline(l,p+1);
                         u := gv(h.x,h.y,h.z);
                         mel.meshssphere ('l'+getstring(l)+'_p'+getstring(p),radius,v,norm(v-u));
                         mel.select('l'+getstring(l)+'_p'+getstring(p)+'.map[0:438]');
                         mel.raw ('polyEditUV -r off -v 0;');
                         mel.setuv ('',0.5,0.5,1,0); {polyEditUV -pu 0.5 -pv 0.5 -su 1 -sv 0 ;}
                         mel.assignuv ('',0,h.t); {polyEditUV -u 0 -v 0.3 }

                         mel.meshscylinder ('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1),radius,getlength(v-u),(v+u)/2,norm(v-u)); { uv 20 1 1 }
                         mel.select('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1)+'.map[0:81]');
                         mel.raw ('polyEditUV -r off -v 0;');
                         mel.setuv ('',0.5,0.5,1,0); {polyEditUV -pu 0.5 -pv 0.5 -su 1 -sv 0 ;}
                         mel.assignuv ('',0,h.t); {polyEditUV -u 0 -v 0.3 }
                         v := u;
                    end;
                    h := f^.getline(l,len-1);
                    u := gv(h.x,h.y,h.z);
                    mel.meshssphere ('l'+getstring(l)+'_p'+getstring(len),radius,v,norm(v-u));
                    mel.select('l'+getstring(l)+'_p'+getstring(len)+'.map[0:438]');
                    mel.raw ('polyEditUV -r off -v 0;');
                    mel.setuv ('',0.5,0.5,1,0); {polyEditUV -pu 0.5 -pv 0.5 -su 1 -sv 0 ;}
                    mel.assignuv ('',0,h.t); {polyEditUV -u 0 -v 0.3 }

                    mel.selectpart ('l'+getstring(l)+'_');
                    mel.polyunion('l'+getstring(l));
                    mel.comment ('End of line.');
               end
               else if len = 1 then
               begin
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    mel.meshssphere ('l'+getstring(l),radius,v,gv(1,0,0));
                    mel.select('l'+getstring(l)+'.map[0:438]');
                    mel.raw ('polyEditUV -r off -v 0;');
                    mel.setuv ('',0.5,0.5,1,0); {polyEditUV -pu 0.5 -pv 0.5 -su 1 -sv 0 ;}
                    mel.assignuv ('',0,h.t); {polyEditUV -u 0 -v 0.3 }
               end;
          end;
          progress;
     end;
end;
procedure run_uvtel (f : pcloud;radius : real);
var l,p,len : integer;
    h : hyper;
    v,u : vector;
    min,max : hyper;
begin
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    mel.comment ('Begin of line.');
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    for p := 1 to len-1 do
                    begin
                         h := f^.getline(l,p+1);
                         u := gv(h.x,h.y,h.z);
                         mel.meshscylinder ('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1),radius,getlength(v-u),(v+u)/2,norm(v-u),10,1,0); { uv reduced and no caps  }
                         mel.select('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1)+'.map[0:81]');
                         mel.raw ('polyEditUV -r off -v 0;');
                         mel.setuv ('',0.5,0.5,1,0); {polyEditUV -pu 0.5 -pv 0.5 -su 1 -sv 0 ;}
                         mel.assignuv ('',0,h.t); {polyEditUV -u 0 -v 0.3 }
                         v := u;
                    end;
                    h := f^.getline(l,len-1);
                    u := gv(h.x,h.y,h.z);
                    mel.selectpart ('l'+getstring(l)+'_');
                    mel.polyunion('l'+getstring(l));
                    mel.comment ('End of line.');
               end;
          end;
          progress;
     end;
end;
procedure run_mel (f : pcloud;radius : real);
var l,p,len : integer;
    value : real;
    h : hyper;
    v,u : vector;
    w : hypernat;
    min,max : hyper;
    color : tpolyvectornat;
begin
     color := Default(tpolyvectornat);

     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          color.init;
          for len := 0 to colormap.length do
          begin
               value := min.t + ((max.t-min.t)/colormap.length)*len;
               w := round(255*getcolormap(min.t,max.t,value));
               if into (w.x,0,255) and into (w.y,0,255) and into (w.z,0,255) then
               if color.search(gvn(w.x,w.y,w.z)) = 0 then
               begin
                    mel.phong ('Phong_'+gethexcolor (w),getcolormap(min.t,max.t,value));
                    color.push (gvn(w.x,w.y,w.z));
               end;
          end;
          color.done;

          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    mel.comment ('Begin of line.');
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    for p := 1 to len-1 do
                    begin
                         h := f^.getline(l,p+1);
                         u := gv(h.x,h.y,h.z);
                         mel.meshssphere ('l'+getstring(l)+'_p'+getstring(p),radius,v,norm(v-u));
                         mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                         mel.meshscylinder ('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1),radius,getlength(v-u),(v+u)/2,norm(v-u));
                         mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                         v := u;
                    end;
                    h := f^.getline(l,len-1);
                    u := gv(h.x,h.y,h.z);
                    mel.meshssphere ('l'+getstring(l)+'_p'+getstring(len),radius,v,norm(v-u));
                    mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                    mel.selectpart ('l'+getstring(l)+'_');
                    mel.polyunion('l'+getstring(l));
                    mel.comment ('End of line.');
               end
               else if len = 1 then
               begin
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    mel.meshssphere ('l'+getstring(l),radius,v,gv(1,0,0));
                    mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
               end;
          end;
          progress;
     end;
end;
procedure run_nel (f : pcloud;radius : real);
var l,p,len : integer;
    value : real;
    h : hyper;
    v,u : vector;
    w : hypernat;
    min,max : hyper;
    color : tpolyvectornat;
begin
     color := Default(tpolyvectornat);

     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          color.init;
          for len := 0 to colormap.length do
          begin
               value := min.t + ((max.t-min.t)/colormap.length)*len;
               w := round(255*getcolormap(min.t,max.t,value));
               if into (w.x,0,255) and into (w.y,0,255) and into (w.z,0,255) then
               if color.search(gvn(w.x,w.y,w.z)) = 0 then
               begin
                    mel.phong ('Phong_'+gethexcolor (w),getcolormap(min.t,max.t,value));
                    color.push (gvn(w.x,w.y,w.z));
               end;
          end;
          color.done;

          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    mel.comment ('Begin of line.');
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    for p := 1 to len-1 do
                    begin
                         h := f^.getline(l,p+1);
                         u := gv(h.x,h.y,h.z);
                         mel.nurbssphere ('l'+getstring(l)+'_p'+getstring(p),radius,v,norm(v-u));
                         mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                         mel.nurbscylinder ('l'+getstring(l)+'_p'+getstring(p)+'_'+getstring(p+1),radius,getlength(v-u),(v+u)/2,norm(v-u));
                         mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                         v := u;
                    end;
                    h := f^.getline(l,len-1);
                    u := gv(h.x,h.y,h.z);
                    mel.nurbssphere ('l'+getstring(l)+'_p'+getstring(len),radius,v,norm(v-u));
                    mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
                    mel.selectpart ('l'+getstring(l)+'_');
                    mel.group ('l'+getstring(l));
                    mel.comment ('End of line.');
               end
               else if len = 1 then
               begin
                    h := f^.getline (l,1);
                    v := gv(h.x,h.y,h.z);
                    mel.nurbssphere ('l'+getstring(l),radius,v,gv(1,0,0));
                    mel.assignshader ('Phong_'+gethexcolor (round(255*getcolormap(min.t,max.t,h.t))));
               end;
          end;
          progress;
     end;
end;
procedure run_cel (f : pcloud;radius : real);
var l,p,len : integer;
    h : hyper;
    u : vector;
    min,max : hyper;
    list : tpolyvector;
begin
     list := Default(tpolyvector);

     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          list.init;
          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    for p := 1 to len do
                    begin
                         h := f^.getline(l,p);
                         u := gv(h.x,h.y,h.z);
                         list.push (u);
                    end;
                    mel.curve('l'+getstring(l),list);
               end;
               list.newlength(0);
          end;
          progress;
          list.done;
     end;
end;
procedure run_wcel (f : pcloud;radius : real);
var l,p,len : integer;
    min,max : hyper;
    list : tpolyhyper;
begin
     list := Default(tpolyhyper);

     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          list.init;
          for l := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',l/f^.getlinelength);
               len := f^.getalllinepointlength (l);
               if len > 1 then
               begin
                    for p := 1 to len do list.push (f^.getline(l,p));
                    mel.curve('l'+getstring(l),list);
               end;
               list.newlength(0);
          end;
          progress;
          list.done;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     if getfileextension (p_o_show) = 'wcel' then { for weight curves }
     begin
          p_o_show := getdirfilename (p_o_show)+'-wcurves.mel';
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_wcel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_wcel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_wcel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_wcel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_wcel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_wcel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else if getfileextension (p_o_show) = 'cel' then { for curves }
     begin
          p_o_show := getdirfilename (p_o_show)+'-curves.mel';
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_cel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_cel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_cel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_cel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_cel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_cel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else if getfileextension (p_o_show) = 'nel' then { for nurbs }
     begin
          p_o_show := getdirfilename (p_o_show)+'-nurbs.mel';
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_nel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_nel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_nel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_nel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_nel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_nel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else if getfileextension (p_o_show) = 'uvel' then { for uv-maps }
     begin
          p_o_show := getdirfilename (p_o_show)+'-uv.mel';
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_uvel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_uvel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_uvel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_uvel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_uvel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_uvel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else if getfileextension (p_o_show) = 'uvtel' then { for uv-maps and tubes without spheres }
     begin
          p_o_show := getdirfilename (p_o_show)+'-uv-tubes.mel';
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_uvtel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_uvtel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_uvtel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_uvtel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_uvtel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_uvtel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else if getfileextension (p_o_show) = 'mel' then { for meshes }
     begin
          if mel.save(p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_mel (@red,_getreal(editredradius));
               _update;
               if state[2] then run_mel (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_mel (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_mel (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_mel (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_mel (@purple,_getreal(editpurpleradius));
               donemap;
               mel.done;
          end;
     end
     else { for povray }
     begin
          addons (p_o_show);
          if pov.saveinc (p_o_show) then
          begin
               initmap (_getnat (show_povray_steps2));
               if state[1] then run_pov (@red,_getreal(editredradius));
               _update;
               if state[2] then run_pov (@green,_getreal(editgreenradius));
               _update;
               if state[3] then run_pov (@blue,_getreal(editblueradius));
               _update;
               if state[4] then run_pov (@yellow,_getreal(edityellowradius));
               _update;
               if state[5] then run_pov (@cyan,_getreal(editcyanradius));
               _update;
               if state[6] then run_pov (@purple,_getreal(editpurpleradius));
               donemap;
               pov.done;
          end;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_color_lines (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-lines';
     _savefile (p_o_show,'new-lines','pov','Povray-files:*.pov|Maya-files:*.mel|All files:*.*',@p_o_color_lines);
end;

{ ******************************** Size Lines ******************************** }

procedure p_o_size_lines;
var pov : twritepov;
procedure run (f : pcloud;color : hyper);
var z,bl,l : integer;
    v : hyper;
    min,max : hyper;
    subglob : utf16;
begin
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          pov.union;
          for z := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',z/f^.getlinelength);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         subglob := subglob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(gv(color.x,color.y,color.z)));
                         subglob := subglob + pov.cylinder (v,f^.getline(z,bl+1),getsizemap (min.t,max.t,v.t),pov.pigment(gv(color.x,color.y,color.z)));
                    end;
                    v := f^.getline(z,l);
                    subglob := subglob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(gv(color.x,color.y,color.z)));
                    pov.write(pov.union (subglob));
               end
               else if l = 1 then
               begin
                    v := f^.getline(z,1);
                    pov.write(pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(gv(color.x,color.y,color.z))));
               end;
          end;
          progress;
          pov.ende;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps2));
          if state[1] then run (@red,_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getcolort (editpurple)/$FFFF);
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_size_lines (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-lines';
     _savefile (p_o_show,'new-lines','pov','Povray-files:*.pov|All files:*.*',@p_o_size_lines);
end;

{ ******************************** Both Lines ******************************** }

procedure p_o_both_lines;
var pov : twritepov;
procedure run (f : pcloud);
var z,bl,l : integer;
    v : hyper;
    min,max : hyper;
    subglob : utf16;
begin
     min := f^.min;
     max := f^.max;
     if min = max then
     begin
          min := min-1;
          max := max+1;
     end;
     if f^.getpointlength > 0 then
     begin
          pov.union;
          for z := 1 to f^.getlinelength do
          begin
               progress  ('  Write lines.',z/f^.getlinelength);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    subglob := '';
                    for bl := 1 to l-1 do
                    begin
                         v := f^.getline (z,bl);
                         subglob := subglob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(getcolormap(min.t,max.t,v.t)));
                         subglob := subglob + pov.cylinder (v,f^.getline(z,bl+1),getsizemap (min.t,max.t,v.t),pov.pigment(getcolormap(min.t,max.t,v.t)));
                    end;
                    v := f^.getline(z,l);
                    subglob := subglob + pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(getcolormap(min.t,max.t,v.t)));
                    pov.write(pov.union (subglob));
               end
               else if l = 1 then
               begin
                    v := f^.getline(z,1);
                    pov.write(pov.sphere (v,getsizemap (min.t,max.t,v.t),pov.pigment(getcolormap(min.t,max.t,v.t))));
               end;
          end;
          progress;
          pov.ende;
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_steps2));
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
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_both_lines (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-lines';
     _savefile (p_o_show,'new-lines','pov','Povray-files:*.pov|All files:*.*',@p_o_both_lines);
end;

{ ******************************** Meshes ************************************ }

procedure p_o_meshes;
var pov : twritepov;
procedure run (f : pcloud;radius : real;color : hyper);
var z,bl,l : integer;
    glob,subglob : utf16;
    line : tpolyhyper;
    h1,h2,h3,h4,h5,h6,h7,h8 : hyper;
begin
     line := Default (tpolyhyper);

     glob := '';
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 3 then
               begin
                    if f^.getline (z,1) = f^.getline (z,l) then
                    begin
                         if l = 4 then
                         begin
                              glob := glob + pov.triangle (f^.getline(z,1),f^.getline(z,2),f^.getline(z,3),'');
                         end
                         else if l = 5 then
                         begin
                              subglob := pov.triangle (f^.getline(z,1),f^.getline(z,2),f^.getline(z,3),'');
                              glob := glob + subglob + pov.triangle (f^.getline(z,3),f^.getline(z,4),f^.getline(z,1),'');
                         end
                         else
                         begin
                              line.init (l);
                              for bl := 1 to l do
                              begin
                                   line.put (bl,f^.getline (z,bl));
                              end;
                              glob := glob + pov.polygon (line,'');
                              line.done;
                         end;
                    end
                    else if l = 8 then
                    begin
                         h1 := f^.getline (z,1);
                         h2 := f^.getline (z,2);
                         h3 := f^.getline (z,3);
                         h4 := f^.getline (z,4);
                         h5 := f^.getline (z,5);
                         h6 := f^.getline (z,6);
                         h7 := f^.getline (z,7);
                         h8 := f^.getline (z,8);
                         subglob := pov.triangle (h1,h2,h6,'') + pov.triangle (h6,h5,h1,'');
                         subglob := subglob + pov.triangle (h2,h3,h7,'') + pov.triangle (h7,h6,h2,'');
                         subglob := subglob + pov.triangle (h3,h4,h8,'') + pov.triangle (h8,h7,h3,'');
                         subglob := subglob + pov.triangle (h4,h1,h5,'') + pov.triangle (h5,h8,h4,'');
                         subglob := subglob + pov.triangle (h1,h2,h3,'') + pov.triangle (h3,h4,h1,'');
                         glob := glob + subglob + pov.triangle (h5,h6,h7,'') + pov.triangle (h7,h8,h5,'');
                    end
                    else if l = 6 then
                    begin
                         h1 := f^.getline (z,1);
                         h2 := f^.getline (z,2);
                         h3 := f^.getline (z,3);
                         h4 := f^.getline (z,4);
                         h5 := f^.getline (z,5);
                         h6 := f^.getline (z,6);
                         subglob := pov.triangle (h1,h2,h5,'') + pov.triangle (h5,h4,h1,'');
                         subglob := subglob + pov.triangle (h2,h3,h6,'') + pov.triangle (h6,h5,h2,'');
                         subglob := subglob + pov.triangle (h3,h1,h4,'') + pov.triangle (h4,h6,h3,'');
                         subglob := subglob + pov.triangle (h1,h2,h3,'');
                         glob := glob + subglob + pov.triangle (h4,h5,h6,'');
                    end
                    else if l = 4 then
                    begin
                         h1 := f^.getline (z,1);
                         h2 := f^.getline (z,2);
                         h3 := f^.getline (z,3);
                         h4 := f^.getline (z,4);
                         subglob := pov.triangle (h1,h2,h3,'');
                         subglob := subglob + pov.triangle (h2,h3,h4,'');
                         subglob := subglob + pov.triangle (h3,h1,h4,'');
                         glob := glob + subglob + pov.triangle (h4,h1,h2,'');
                    end;
               end else if l = 1 then glob := glob + pov.sphere (f^.getline(z,1),radius,'');
          end;
          if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                         else pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_meshes (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-meshes';
     _savefile (p_o_show,'new-meshes','pov','Povray-files:*.pov|All files:*.*',@p_o_meshes);
end;

{ ******************************* Polynominal ******************************** }

procedure proc_show_set_curvature (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (show_povray_range,'[0:2]');
end;

procedure proc_show_set_torsion (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (show_povray_range,'[-1:1]');
end;

{ ******************************** Curves ************************************ }

var po_fit : boolean;

procedure p_o_curves;
var pov : twritepov;
procedure run (f : pcloud;radius : real;color : hyper);
var v,u : hyper;
    z,bl,l : integer;
    line : tpolyhyper;
    linepoly : tpolynom4d;
    factor,counter :real;
    glob,subglob : utf16;
begin
     line := Default(tpolyhyper);
     linepoly := Default(tpolynom4d);

     glob := '';
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    line.init (l);
                    for bl := 1 to l do
                    begin
                         line.put (bl,f^.getline (z,bl));
                    end;
                    if l < _getitem(show_polynom_method)+1 then linepoly.init (l)
                                                           else linepoly.init (_getitem(show_polynom_method)+1);
                    if po_fit then linepoly.fit (line)
                              else linepoly.getpolynom (line);
                    l := _getnat(show_povray_resolution);
                    if l < 10 then l := 10;
                    factor := linepoly.pathlength/l;
                    counter := 0;
                    subglob := '';
                    u := Hzero;
                    for bl := 1 to l do
                    begin
                         v := linepoly.polynom (counter);
                         counter := counter + factor;
                         u := linepoly.polynom (counter);
                         subglob := subglob + pov.sphere (v,radius,'');
                         subglob := subglob + pov.cylinder (v,u,radius,'');
                    end;
                    subglob := subglob + pov.sphere (u,radius,'');
                    if color.t = 1 then glob := glob + subglob
                                   else glob := glob + pov.merge (subglob);
                    linepoly.done;
                    line.done;
               end
               else if l = 1 then glob := glob + pov.sphere (f^.getline(z,1),radius,'');
          end;
          if color.t = 1 then pov.write (pov.union(glob+pov.pigment(gv(color.x,color.y,color.z))))
                         else pov.write (pov.union(glob+pov.pigment(color)));
     end;
end;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          if state[1] then run (@red,_getreal(editredradius),_getcolort (editred)/$FFFF);
          _update;
          if state[2] then run (@green,_getreal(editgreenradius),_getcolort (editgreen)/$FFFF);
          _update;
          if state[3] then run (@blue,_getreal(editblueradius),_getcolort (editblue)/$FFFF);
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius),_getcolort (edityellow)/$FFFF);
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius),_getcolort (editcyan)/$FFFF);
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius),_getcolort (editpurple)/$FFFF);
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_curves (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-curves';
     po_fit := false;
     _savefile (p_o_show,'new-file','pov','Povray-files:*.pov|All files:*.*',@p_o_curves);
end;

procedure proc_show_curves_fit (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-curves';
     po_fit := true;
     _savefile (p_o_show,'new-curves','pov','Povray-files:*.pov|All files:*.*',@p_o_curves);
end;


{ ******************************** Curvature ********************************* }

procedure p_o_curvature;
var pov : twritepov;
  procedure run (f : pcloud;radius : real);
  var color : hyper;
      v,u : vector;
      z,bl,l : integer;
      line : tpolyvector;
      linepoly : tpolynom3d;
      linefunc : tcurveproperty3d;
      factor,counter,c :real;
      ra : range;
      glob,subglob : utf16;
    function setcolor (c : real) : hyper;
    begin
         setcolor := getcolormap (ra.min,ra.max,c);
    end;
  begin
       line := Default(tpolyvector);
       linepoly := Default(tpolynom3d);
       linefunc := Default(tcurveproperty3d);

       glob := '';
       if f^.getpointlength > 0 then
       begin
            ra := _getrange (show_povray_range);
            for z := 1 to f^.getlinelength do
            begin
                 l := f^.getalllinepointlength (z);
                 if l > 1 then
                 begin
                      line.init (l);
                      for bl := 1 to l do
                      begin
                           line.put (bl,htov(f^.getline (z,bl)));
                      end;
                      if l < _getitem(show_polynom_method)+1 then linepoly.init (l)
                                                             else linepoly.init (_getitem(show_polynom_method)+1);
                      if po_fit then linepoly.fit (line)
                                else linepoly.getpolynom (line);
                      linefunc.init (linepoly);
                      l := _getnat(show_povray_resolution);
                      if l < 10 then l := 10;
                      factor := linepoly.pathlength/l;
                      counter := 0;
                      subglob := '';
                      u := Vzero;
                      for bl := 1 to l do
                      begin
                           v := linepoly.polynom (counter);
                           c := linefunc.curvature (counter);
                           color := setcolor (c);
                           subglob := subglob + pov.sphere (v,radius,pov.pigment(color));
                           counter := counter + factor;
                           u := linepoly.polynom (counter);
                           c := (c+linefunc.curvature (counter))/2;
                           color := setcolor (c);
                           subglob := subglob + pov.cylinder (v,u,radius,pov.pigment(color));
                      end;
                      counter := counter + factor;
                      v := linepoly.polynom (counter);
                      c := linefunc.curvature (counter);
                      color := setcolor (c);
                      subglob := subglob + pov.sphere (u,radius,pov.pigment(color));
                      if color.t = 1 then glob := glob + subglob
                                     else glob := glob + pov.merge (subglob);
                      linefunc.done;
                      linepoly.done;
                      line.done;
                 end;
            end;
            pov.write (pov.union(glob));
       end;
  end;

begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_resolution));
          if state[1] then run (@red,_getreal(editredradius));
          _update;
          if state[2] then run (@green,_getreal(editgreenradius));
          _update;
          if state[3] then run (@blue,_getreal(editblueradius));
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius));
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius));
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius));
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_curvature (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-curvature';
     po_fit := false;
     _savefile (p_o_show,'new-curvature','pov','Povray-files:*.pov|All files:*.*',@p_o_curvature);
end;

procedure proc_show_curvature_fit (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-curvature';
     po_fit := true;
     _savefile (p_o_show,'new-curvature','pov','Povray-files:*.pov|All files:*.*',@p_o_curvature);
end;

{ ******************************** Torsion *********************************** }

procedure p_o_torsion;
var pov : twritepov;
  procedure run (f : pcloud;radius : real);
  var color : hyper;
      v,u : vector;
      z,bl,l : integer;
      line : tpolyvector;
      linepoly : tpolynom3d;
      linefunc : tcurveproperty3d;
      factor,counter,c :real;
      ra : range;
      glob,subglob : utf16;
    function setcolor (c : real) : hyper;
    begin
         setcolor := getcolormap (ra.min,ra.max,c);
    end;
  begin
       line := Default(tpolyvector);
       linepoly := Default(tpolynom3d);
       linefunc := Default(tcurveproperty3d);

       glob := '';
       if f^.getpointlength > 0 then
       begin
            ra := _getrange (show_povray_range);
            for z := 1 to f^.getlinelength do
            begin
                 l := f^.getalllinepointlength (z);
                 if l > 1 then
                 begin
                      line.init (l);
                      for bl := 1 to l do
                      begin
                           line.put (bl,htov(f^.getline (z,bl)));
                      end;
                      if l < _getitem(show_polynom_method)+1 then linepoly.init (l)
                                                             else linepoly.init (_getitem(show_polynom_method)+1);
                      if po_fit then linepoly.fit (line)
                                else linepoly.getpolynom (line);
                      linefunc.init (linepoly);
                      l := _getnat(show_povray_resolution);
                      if l < 10 then l := 10;
                      factor := linepoly.pathlength/l;
                      counter := 0;
                      subglob := '';
                      u := Vzero;
                      for bl := 1 to l do
                      begin
                           v := linepoly.polynom (counter);
                           c := linefunc.torsion (counter);
                           color := setcolor (c);
                           subglob := subglob + pov.sphere (v,radius,pov.pigment(color));
                           counter := counter + factor;
                           u := linepoly.polynom (counter);
                           c := (c+linefunc.torsion (counter))/2;
                           color := setcolor (c);
                           subglob := subglob + pov.cylinder (v,u,radius,pov.pigment(color));
                      end;
                      counter := counter + factor;
                      v := linepoly.polynom (counter);
                      c := linefunc.torsion (counter);
                      color := setcolor (c);
                      subglob := subglob + pov.sphere (u,radius,pov.pigment(color));
                      if color.t = 1 then glob := glob + subglob
                                     else glob := glob + pov.merge (subglob);
                      linefunc.done;
                      linepoly.done;
                      line.done;
                 end;
            end;
            pov.write (pov.union(glob));
       end;
  end;

begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     addons (p_o_show);
     if pov.saveinc (p_o_show) then
     begin
          initmap (_getnat (show_povray_resolution));
          if state[1] then run (@red,_getreal(editredradius));
          _update;
          if state[2] then run (@green,_getreal(editgreenradius));
          _update;
          if state[3] then run (@blue,_getreal(editblueradius));
          _update;
          if state[4] then run (@yellow,_getreal(edityellowradius));
          _update;
          if state[5] then run (@cyan,_getreal(editcyanradius));
          _update;
          if state[6] then run (@purple,_getreal(editpurpleradius));
          donemap;
          pov.done;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_torsion (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-torsion';
     po_fit := false;
     _savefile (p_o_show,'new-torsion','pov','Povray-files:*.pov|All files:*.*',@p_o_torsion);
end;

procedure proc_show_torsion_fit (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-torsion';
     po_fit := true;
     _savefile (p_o_show,'new-torsion','pov','Povray-files:*.pov|All files:*.*',@p_o_torsion);
end;

{ **************************************************************************** }

procedure p_o_write_objects (macro : pointer);
var pov : twritepov;
    u,v : hyper;
    l,r : integer;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     if finput^.getlinelength > 0 then
     begin
          addons (p_o_show);
          r := _getnat (show_povray_objects,macro,1);
          if pov.saveinc (p_o_show) then
          begin
               if r > 0 then
               begin
                    pov.declare ('objectcolor','pigment { color rgbt '+getstring(_getcolort(editred)/$FFFF)+' }');
                    pov.declare ('objectfinish','finish { phong 0.5 }');
                    for l := 1 to r do
                    begin
                         pov.declare ('object'+getstring(l),'#include "'+getstring(l)+'.inc"');
                    end;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if finput^.getalllinepointlength (l) = 2 then
                         begin
                              u := finput^.getline (l,1);
                              v := finput^.getline (l,2)-u;
                              pov.objects;
                                        pov.write (pov.tab('object'+getstring(random(r)+1)));
                                        pov.write (pov.tab(pov.translate(gv(u.x,u.y,u.z))));
                                        pov.write (pov.tab(pov.rotate(gv(v.x*180,v.y*180,v.z*180))));
                                        pov.write (pov.tab(pov.texture('objectcolor objectfinish')));
                              pov.ende;
                         end;
                    end;
               end;
               pov.done;
          end;
          tmacro(macro^).writeredo ('show.write.objects',getstring(r));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_write_objects (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-objects';
     _savefile (p_o_show,'new-objects','pov','Povray-files:*.pov|All files:*.*',@p_o_write_objects,macro);
end;

procedure p_o_write_objects_flip (macro : pointer);
var pov : twritepov;
    u,v : hyper;
    l,r : integer;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     if finput^.getlinelength > 0 then
     begin
          addons (p_o_show);
          r := _getnat (show_povray_objects,macro,1);
          if pov.saveinc (p_o_show) then
          begin
               if r > 0 then
               begin
                    pov.declare ('objectcolor','pigment { color rgbt '+getstring(_getcolort(editred)/$FFFF)+' }');
                    pov.declare ('objectfinish','finish { phong 0.5 }');
                    for l := 1 to r do
                    begin
                         pov.declare ('object'+getstring(l),'#include "'+getstring(l)+'.inc"');
                    end;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if finput^.getalllinepointlength (l) = 2 then
                         begin
                              u := finput^.getline (l,1);
                              v := finput^.getline (l,2)-u;
                              pov.objects;
                                        pov.write (pov.tab('object'+getstring(random(r)+1)));
                                        pov.write (pov.tab(pov.translate(gv(u.x,u.y,u.z))));
                                        pov.write (pov.tab(pov.rotate(gv(v.x*180,v.y*180,v.z*180))));
                                        if random (2) = 0 then u.x := -1 else u.x := 1;
                                        if random (2) = 0 then u.y := -1 else u.y := 1;
                                        if random (2) = 0 then u.z := -1 else u.z := 1;
                                        pov.write (pov.tab(pov.scale(gv(u.x,u.y,u.z))));
                                        pov.write (pov.tab(pov.texture('objectcolor objectfinish')));
                              pov.ende;
                         end;
                    end;
               end;
               pov.done;
          end;
          tmacro(macro^).writeredo ('show.write.flip.objects',getstring(r));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_write_objects_flip (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-objects';
     _savefile (p_o_show,'new-objects','pov','Povray-files:*.pov|All files:*.*',@p_o_write_objects_flip,macro);
end;

procedure p_o_write_objects_scale (macro : pointer);
var pov : twritepov;
    u,v : hyper;
    l,r : integer;
begin
     fillbyte (pov,sizeof(twritepov),0); { pov := Default(twritepov); }

     _cursor_watch;
     format.push;
     format := format_pov;
     if finput^.getlinelength > 0 then
     begin
          addons (p_o_show);
          r := _getnat (show_povray_objects,macro,1);
          if pov.saveinc (p_o_show) then
          begin
               if r > 0 then
               begin
                    pov.declare ('objectcolor','pigment { color rgbt '+getstring(_getcolort(editred)/$FFFF)+' }');
                    pov.declare ('objectfinish','finish { phong 0.5 }');
                    for l := 1 to r do
                    begin
                         pov.declare ('object'+getstring(l),'#include "'+getstring(l)+'.inc"');
                    end;
                    for l := 1 to finput^.getlinelength do
                    begin
                         if finput^.getalllinepointlength (l) = 2 then
                         begin
                              u := finput^.getline (l,1);
                              v := finput^.getline (l,2)-u;
                              pov.objects;
                                        pov.write (pov.tab('object'+getstring(random(r)+1)));
                                        pov.write (pov.tab(pov.translate(gv(u.x,u.y,u.z))));
                                        pov.write (pov.tab(pov.rotate(gv(v.x*180,v.y*180,v.z*180))));
                                        pov.write (pov.tab(pov.scale(liball.getlength(v))));
                                        pov.write (pov.tab(pov.texture('objectcolor objectfinish')));
                              pov.ende;
                         end;
                    end;
               end;
               pov.done;
          end;
          tmacro(macro^).writeredo ('show.write.scale.objects',getstring(r));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_show_write_objects_scale (p1,macro : gtk_pointer); cdecl;
begin
     p_o_show := '';
     if finput^.name <> '' then p_o_show := getdirfilename(finput^.name)+'-objects';
     _savefile (p_o_show,'new-objects','pov','Povray-files:*.pov|All files:*.*',@p_o_write_objects_scale,macro);
end;

{ **************************************************************************** }

procedure proc_show_povray_default (p1,macro : gtk_pointer); cdecl;
begin
     _setcolor (editred,gvn($FFFF, 0, 0));
     _setcolor (editgreen,gvn(0,$FFFF, 0));
     _setcolor (editblue,gvn(0,0,$FFFF));
     _setcolor (edityellow,gvn($FFFF, $FFFF, 0));
     _setcolor (editcyan,gvn(0, $FFFF, $FFFF));
     _setcolor (editpurple,gvn($FFFF, 0, $FFFF));
end;

procedure proc_show_povray_light (p1,macro : gtk_pointer); cdecl;
begin
     _setcolor (editred,gvn($FFFF, $8000, $8000));
     _setcolor (editgreen,gvn($8000,$FFFF, $8000));
     _setcolor (editblue,gvn($8000,$8000,$FFFF));
     _setcolor (edityellow,gvn($FFFF, $FFFF, $8000));
     _setcolor (editcyan,gvn($8000, $FFFF, $FFFF));
     _setcolor (editpurple,gvn($FFFF, $8000, $FFFF));
end;

procedure proc_show_povray_dark (p1,macro : gtk_pointer); cdecl;
begin
     _setcolor (editred,gvn($7FFF, 0, 0));
     _setcolor (editgreen,gvn(0,$7FFF, 0));
     _setcolor (editblue,gvn(0,0,$7FFF));
     _setcolor (edityellow,gvn($7FFF, $7FFF, 0));
     _setcolor (editcyan,gvn(0, $7FFF, $7FFF));
     _setcolor (editpurple,gvn($7FFF, 0, $7FFF));
end;

procedure proc_show_povray_quarter (p1,macro : gtk_pointer); cdecl;
begin
     _setalpha (editred, $3FFF);
     _setalpha (editgreen, $3FFF);
     _setalpha (editblue, $3FFF);
     _setalpha (edityellow, $3FFF);
     _setalpha (editcyan, $3FFF);
     _setalpha (editpurple, $3FFF);
end;

procedure proc_show_povray_half (p1,macro : gtk_pointer); cdecl;
begin
     _setalpha (editred, $7FFF);
     _setalpha (editgreen, $7FFF);
     _setalpha (editblue, $7FFF);
     _setalpha (edityellow, $7FFF);
     _setalpha (editcyan, $7FFF);
     _setalpha (editpurple, $7FFF);
end;

procedure proc_show_povray_half_quarter (p1,macro : gtk_pointer); cdecl;
begin
     _setalpha (editred, $AFFF);
     _setalpha (editgreen, $AFFF);
     _setalpha (editblue, $AFFF);
     _setalpha (edityellow, $AFFF);
     _setalpha (editcyan, $AFFF);
     _setalpha (editpurple, $AFFF);
end;

procedure proc_show_povray_full (p1,macro : gtk_pointer); cdecl;
begin
     _setalpha (editred, $FFFF);
     _setalpha (editgreen, $FFFF);
     _setalpha (editblue, $FFFF);
     _setalpha (edityellow, $FFFF);
     _setalpha (editcyan, $FFFF);
     _setalpha (editpurple, $FFFF);
end;

procedure proc_show_povray_rgb (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (editredmap,'0');
     _setedit (editgreenmap,'0.5');
     _setedit (editbluemap,'1');
     _setedit (edityellowmap,'-1');
     _setedit (editcyanmap,'-1');
     _setedit (editpurplemap,'-1');
end;

procedure proc_show_povray_rainbow (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (editredmap,'0');
     _setedit (editgreenmap,'0.4');
     _setedit (editbluemap,'0.8');
     _setedit (edityellowmap,'0.2');
     _setedit (editcyanmap,'0.6');
     _setedit (editpurplemap,'1');
end;

procedure proc_show_povray_curvature_color (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (editredmap,'1');
     _setedit (editgreenmap,'0');
     _setedit (editbluemap,'-1');
     _setedit (edityellowmap,'0.5');
     _setedit (editcyanmap,'-1');
     _setedit (editpurplemap,'-1');
end;

procedure proc_show_povray_torsion_color (p1,macro : gtk_pointer); cdecl;
begin
     _setedit (editredmap,'1');
     _setedit (editgreenmap,'0.5');
     _setedit (editbluemap,'0');
     _setedit (edityellowmap,'0.75');
     _setedit (editcyanmap,'0.25');
     _setedit (editpurplemap,'-1');
end;
