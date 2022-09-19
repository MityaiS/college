program lab9;
var D:array [1..10, 1..10] of integer;
	i, n, m, j, md, nd: integer;
	fin, fout: Text;
	raw, col: boolean;
begin
	assign(fin, 'lab9_in.txt');
	try
	  Reset(fin);
	except 
    write('Похоже, что входного файла не существует');
  end;
	read(fin, n);
	read(fin, m);
	for i := 1 to n do
  begin
    for j := 1 to m do 
    begin
      read(fin, D[i,j]);
    end;
    readln(fin);
  end;
  close(fin);
  md := 0;
  col := True;
  while col do 
  begin
    nd := 1;
    md := md + 1;
    raw := True;
    while raw and (nd <> n + 1) do 
    begin
      if (D[nd,md] - 3) mod 10 <> 0 then raw := False;
      nd := nd + 1;
    end;
    if raw = True then col := False;
  end;
  assign(fout, 'lab9_out.txt');
  rewrite(fout);
  write(fout, 'Из матрицы ');
  for i := 1 to n do 
  begin
    for j := 1 to m do 
      write(fout, D[i,j] + ' ');
    writeln(fout);
  end;
  write(fout, 'Получаем ответ ', md);
  close(fout);
end.
  
      